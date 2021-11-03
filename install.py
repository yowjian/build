#! /usr/bin/env python3
import argparse
from dataclasses import dataclass
import os
from shutil import copytree, move, rmtree
from pathlib import Path
from typing import Dict, Type
import build
from capo.install import install as install_capo
from hal.install import install as install_hal
from mules.install import install as install_mules
import subprocess

@dataclass
class Args:
    output: Path

def install(args: Type[Args]) -> None:
    args.output = args.output.resolve()
    os.chdir('capo') 
    capo_env = install_capo(args)
    os.chdir('..') 
    move(str(args.output / 'python' / 'bin'), str(args.output / 'python' / 'bin-tmp'))
    os.chdir('hal') 
    hal_env = install_hal(args)
    os.chdir('..') 
    copytree(str(args.output / 'python' / 'bin-tmp'), str(args.output / 'python' / 'bin'), dirs_exist_ok=True)
    rmtree(str(args.output / 'python' / 'bin-tmp'))
    move(str(args.output / 'python' / 'bin'), str(args.output / 'python' / 'bin-tmp'))
    os.chdir('mules') 
    mules_env = install_mules(args)
    os.chdir('..') 
    copytree(str(args.output / 'python' / 'bin-tmp'), str(args.output / 'python' / 'bin'), dirs_exist_ok=True)
    rmtree(str(args.output / 'python' / 'bin-tmp'))
    copytree('emu', str(args.output / 'emu'))
    env_vars = {**mules_env, **hal_env, **capo_env}
    out_etc = Path(args.output) / 'etc'
    out_etc.mkdir(parents=True, exist_ok=True)
    with open(out_etc / 'closureenv', 'w') as env_f:  
        for (k, v) in env_vars.items():
            if k == "PATH" or k == "PYTHONPATH":
                env_f.write(f"export {k}={v}:${k}\n")
        env_f.write(f"export CLOSURE_INSTALL_PATH={args.output}\n")


def main() -> None: 
    parser = argparse.ArgumentParser('install.py') 
    parser.add_argument('--output', '-o', default=False, help="Output directory", type=Path, required=True)
    args = parser.parse_args(namespace=Args)
    args.output.mkdir(parents=True, exist_ok=True)
    build.build()
    install(args)
    
if __name__ == '__main__':
    main()