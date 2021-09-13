from pathlib import Path
from typing import Dict, List, Tuple
import build as build_


def build(temp_dir: Path, src_files: List[Path]) -> Tuple[build_.BuildOutput, build_.BuildTimings]:
    return build_.build(build_.Params(src_files, temp_dir=temp_dir, 
                preprocess=True, collate=True, clang=True, clang_args="", link=True,
                opt=True, clejson2zinc=True, minizinc=False, findmus=False, 
                preprocessor_script=build_.preprocessor_script,
                clejson2zinc_script=build_.clejson2zinc_script,
                collator_script=build_.collator_script,
                pdg_so=build_.pdg_so,
                minizinc_model_dir=build_.minizinc_model_dir
        ))

def test(out: build_.BuildOutput) -> bool:
    stdout, stderr, retcode = out['clejson2zinc']
    return b'function taints' in stdout
