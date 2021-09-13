#!/usr/bin/python3
import os
from types import ModuleType
import build
import sys
import argparse
import importlib
import json
from pathlib import Path
from datetime import datetime, timedelta
from typing import Any, Dict, List, Union



test_dir = Path('.') / 'tests' 
runs_dir = Path('.') / 'test-runs'

def main() -> None:
    parser = argparse.ArgumentParser(description="""Test CLE Project""")
    parser.add_argument('--tests', type=str, nargs="*", default=[]) 
    args = parser.parse_args()
    tests: List[str] = args.tests
    if len(tests) == 0:
        tests = next(os.walk(test_dir), [])[1]

    cur_run = datetime.now().strftime("%Y-%m-%d-%H-%M-%S")

    if not runs_dir.exists():
        os.mkdir(runs_dir)

    os.mkdir(runs_dir / cur_run)    
    modules : Dict[str, Any] = {}
    for test in tests:
        sys.path.append(str(test_dir / test))
        modules[test] = importlib.import_module(test)

    timings : Dict[str, Dict[str, timedelta]] = {}
    results : Dict[str, Any] = {}
    for test in tests:
        print(f'Starting test: {test}')
        src_files = [ Path(test_dir / test / file) for file in list(next(os.walk(test_dir / test), [])[2]) if file.endswith('.c') ]
        os.mkdir(runs_dir / cur_run / test)
        if hasattr(modules[test], "build"):
            output, timing = modules[test].build(runs_dir / cur_run / test, src_files)
        else:
            output, timing = build.build(build.Params(src_files, temp_dir=runs_dir / cur_run / test, 
                preprocess=True, collate=True, clang=True, clang_args="", link=True,
                opt=True, clejson2zinc=True, minizinc=True, findmus=True, 
                preprocessor_script=build.preprocessor_script,
                clejson2zinc_script=build.clejson2zinc_script,
                collator_script=build.collator_script,
                pdg_so=build.pdg_so,
                minizinc_model_dir=build.minizinc_model_dir
                ))
        timings[test] = timing
        if hasattr(modules[test], 'test'):
            results[test] = modules[test].test(output)
        print('')


    total_time = timedelta(0) 
    for test, timing in timings.items():
        for time in timing.values():
            total_time += time
    timings_ : Dict[str, Union[Dict[str, str], str]] = { test: { step: str(time) for step, time in timing.items() } for test, timing in timings.items() }
    timings_['total'] = str(total_time)
    with open(runs_dir / cur_run / 'timings.json', 'w') as f:
        f.write(json.dumps(timings_, indent=4))
    with open(runs_dir / cur_run / 'results.json', 'w') as f:
        f.write(json.dumps(results, indent=4))




if __name__ == '__main__':
    main()