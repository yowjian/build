#!/usr/bin/python3
import argparse
import os
import subprocess
import json
from pathlib import Path
from dataclasses import dataclass
from typing import Iterable, List, Optional, Dict
from functools import reduce
from datetime import datetime, timedelta

@dataclass
class Params:
    source_files: List[Path]
    temp_dir: Path
    preprocess: bool
    collate: bool
    clang: bool
    clang_args: List[str]
    link: bool
    opt: bool
    postprocess: bool
    minizinc: bool
    findmus: bool
    preprocessor_script: Path
    collator_script: Path
    postprocessor_script: Path
    minizinc_model_dir: Path
    pdg_so: Path

def build(params: Params) -> None:

    def output_to_file(file_name: str, out) -> None:
        with open(params.temp_dir / f'{file_name}.stdout.txt', 'wb') as out_f:
            if out.stdout:
                out_f.write(out.stdout)
        with open(params.temp_dir / f'{file_name}.stderr.txt', 'wb') as err_f:
            if out.stderr:
                err_f.write(out.stderr)

    if not params.temp_dir.exists():
        os.mkdir(params.temp_dir)

    timings: Dict[str, timedelta] = {}

    if params.preprocess:
        start_time = datetime.now()
        for file in params.source_files: 
            out = subprocess.run(['python3',  params.preprocessor_script, '-L', '-f', file.resolve()], capture_output=True)  
            output_to_file(f'{file.name}.preprocessor', out)
            os.rename(file.with_suffix('.mod.c'), params.temp_dir / f'{file.name}')
            os.rename(file.with_suffix('.c.clemap.json'), (params.temp_dir / f'{file.name}').with_suffix('.clemap.json'))
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['preprocessor'] = time_delta

    if params.collate:
        start_time = datetime.now()
        args = ['python3', str(params.collator_script), str(params.temp_dir / 'clemap.json')]
        args.extend([ f.name for f in params.source_files ])
        out = subprocess.run(args, cwd=params.temp_dir, capture_output=True)
        output_to_file('collator', out)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['collate'] = time_delta
    
    if params.clang:
        start_time = datetime.now()
        for file in params.source_files:
            args = ['clang', '-g', '-c', '-emit-llvm', str(file.resolve())]
            args.extend(params.clang_args)
            out = subprocess.run(args, capture_output=True, cwd=params.temp_dir)
            output_to_file(f'{file.name}.clang', out)
            if out.returncode != 0:
                print('clang compilation failed:\n\t' + " ".join(args))
                exit(1)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['clang'] = time_delta

    if params.link:
        start_time = datetime.now()
        args = ['llvm-link']
        args.extend([ str(params.temp_dir.resolve() / file.with_suffix('.bc').name) for file in params.source_files ])
        args.extend(['-o', 'out.bc'])
        out = subprocess.run(args, cwd=params.temp_dir, capture_output=True)
        output_to_file('link', out)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['link'] = time_delta
    
    if params.opt:
        start_time = datetime.now()
        args = ['opt', '-load', str(params.pdg_so.resolve()), '-minizinc']
        with open(params.temp_dir / 'out.bc', 'rb') as bc_f:
            bc = bc_f.read()
        out = subprocess.run(args, input=bc, cwd=params.temp_dir, capture_output=True)
        output_to_file('opt', out)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['opt'] = time_delta

    if params.postprocess:
        start_time = datetime.now()
        args = ['python3', str(params.postprocessor_script), '-f', 'clemap.json']
        out = subprocess.run(args, cwd=params.temp_dir, capture_output=True)
        output_to_file('postprocess', out)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['postprocess'] = time_delta

    if params.minizinc:
        start_time = datetime.now()
        args = ['minizinc', '--solver', 'Gecode']
        args.extend([ str(params.minizinc_model_dir / 'conflict_analyzer_constraints.mzn'), str(params.minizinc_model_dir / 'conflict_variable_declerations.mzn')])
        args.extend(['pdg_instance.mzn', 'cle_instance.mzn', 'enclave_instance.mzn'])
        out = subprocess.run(args, cwd=params.temp_dir, capture_output=True)
        output_to_file('minizinc', out)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['minizinc'] = time_delta

    if params.findmus:
        start_time = datetime.now()
        args = ['minizinc', '--solver', 'findmus', '--subsolver', 'Gecode', '--output-human', '--depth', '3']
        args.extend([ str(params.minizinc_model_dir / 'conflict_analyzer_constraints.mzn'), str(params.minizinc_model_dir / 'conflict_variable_declerations.mzn')])
        args.extend(['pdg_instance.mzn', 'cle_instance.mzn', 'enclave_instance.mzn'])
        out = subprocess.run(args, cwd=params.temp_dir, capture_output=True)
        output_to_file('findmus', out)
        end_time = datetime.now()
        time_delta = end_time - start_time
        timings['findmus'] = time_delta



    with open(params.temp_dir / 'timings.json', 'w') as time_f:
        timings_ = { k: str(v) for k, v in timings.items() }
        total : timedelta = timedelta(0)
        for t in timings.values():
            total += t
        timings_['total'] = str(total)
        time_f.write(json.dumps(timings_, indent=4))
        

def main() -> None:
    parser = argparse.ArgumentParser(description='Build a CLE Project') 
    parser.add_argument('--source-dir', type=Path, help="""
    Optional source directory. If added, it will invalidate any positional arguments given""")
    parser.add_argument('--temp-dir', type=Path, help="""
    Optional temp directory. Defaults to .cle-work under the source directory if given""")
    parser.add_argument('--pre-process', action='store_true', help="""
    Run CLE preprocessor""")
    parser.add_argument('--collate', action='store_true', help="""
    Run CLE json collater""")
    parser.add_argument('--clang', action='store_true', help="""
    Runs clang to generate LLVM""")
    parser.add_argument('--clang-args', type=str, nargs='*', help="""
    Arguments to pass to clang""")
    parser.add_argument('--link', action='store_true', help="""
    Runs the LLVM linker""")
    parser.add_argument('--opt', action='store_true', help="""
    Runs opt with minizinc""")
    parser.add_argument('--post-process', action='store_true', help="""
    Runs post processing on opt output for minizinc""")
    parser.add_argument('--minizinc', action='store_true', help="""
    Runs minizinc model using Gecode.""")
    parser.add_argument('--minizinc-findmus', action='store_true', help="""
    Runs minizinc model using findmus.""")
    parser.add_argument('files', metavar='FILES', nargs='*', type=Path, help='Source .c and .h Files')
    args = parser.parse_args()
    source_dir: Optional[Path] = args.source_dir
    temp_dir: Optional[Path] = args.temp_dir
    preprocess: bool = args.pre_process
    collate: bool = args.collate
    clang: bool = args.clang
    link: bool = args.link
    opt: bool = args.opt
    postprocess: bool = args.post_process
    minizinc: bool = args.minizinc
    findmus: bool = args.minizinc_findmus
    files: List[Path] = args.files
    clang_args: List[str] = args.clang_args if args.clang_args else []
    build_processes = [preprocess, collate, clang, link, opt, postprocess, minizinc, findmus]
    no_build_specified = reduce(lambda x, y: x and (not y), build_processes, True)
    if no_build_specified:
        preprocess = collate = clang = link = opt = postprocess = minizinc = findmus = True
    if source_dir:
        def flatten(l: Iterable[List[str]]) -> List[str]: 
            def extend(x, y): 
                x.extend(y)
                return x
            return reduce(extend, l, [])
        source_files = \
            list(
                map(Path, 
                    filter(lambda x: x.endswith('.c') or x.endswith('.h'),
                        flatten(
                            map(lambda x: x[2], os.walk(source_dir))))))
    else: 
        source_files = args.files 

    if not temp_dir:
        if source_dir:
            temp_dir_ = source_dir / '.cle-work' 
        else:
            temp_dir_ = Path('.cle-work')

    preprocessor_script = Path(os.path.realpath(__file__)).cwd() / 'closure' / 'capo' / 'conflict_analyzer' / 'scripts' / 'qd_cle_preprocessor.py'
    collator_script = Path('/opt/closure/scripts/join_clemaps.py') 
    postprocessor_script = Path(os.path.realpath(__file__)).cwd() / 'closure' / 'capo' / 'conflict_analyzer' / 'scripts' / 'CLEJson2zinc.py'
    minizinc_model_dir = Path(os.path.realpath(__file__)).cwd() / 'closure' / 'capo' / 'conflict_analyzer' / 'constraints'
    pdg_so = Path(os.path.realpath(__file__)).cwd() / 'closure' / 'program-dependence-graph' / 'build' / 'libpdg.so'
    params = Params(source_files, temp_dir_, preprocess, collate, clang, clang_args, link, opt, postprocess, minizinc, findmus,
        preprocessor_script, collator_script, postprocessor_script, minizinc_model_dir, pdg_so)
    build(params)

if __name__ == '__main__':
    main()