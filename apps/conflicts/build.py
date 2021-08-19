#!/usr/bin/python3
import argparse
import os
from pathlib import Path
from dataclasses import dataclass
from typing import Iterable, List, Optional 
from functools import reduce

@dataclass
class Params:
    source_files: List[Path]
    temp_dir: Path
    preprocess: bool
    collate: bool
    clang: bool
    opt: bool
    postprocess: bool
    minizinc: bool
    findmus: bool

def build(params: Params) -> None:
    pass

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
    opt: bool = args.opt
    postprocess: bool = args.post_process
    minizinc: bool = args.minizinc
    findmus: bool = args.minizinc_findmus
    files: List[Path] = args.files
    build_processes = [preprocess, collate, clang, opt, postprocess, minizinc, findmus]
    no_build_specified = reduce(lambda x, y: x and (not y), build_processes, True)
    if no_build_specified:
        preprocess = collate = clang = opt = postprocess = minizinc = findmus = True
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

    params = Params(source_files, temp_dir_, preprocess, collate, clang, opt, postprocess, minizinc, findmus)
    build(params)

if __name__ == '__main__':
    main()