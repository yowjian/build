#! /usr/bin/env python3
import argparse
from dataclasses import dataclass
import os
from shutil import copytree, move, rmtree
from pathlib import Path
from typing import Callable, Dict, Type, TypeVar, Union
import build
from capo.install import install as install_capo
from hal.install import install as install_hal
from mules.install import install as install_mules
import subprocess
import sys

@dataclass
class Args:
    output: Path

A = TypeVar('A')

def install(args: Type[Args]) -> None:
    def in_dir(path: Union[Path, str], f: Callable[[], A]) -> A:
        tmp = os.getcwd()
        os.chdir(str(path))
        a = f() 
        os.chdir(tmp)
        return a

    # Run install in each subdir (without python package)
    capo_env = in_dir('capo', lambda: install_capo(args))
    hal_env = in_dir('hal', lambda: install_hal(args)) 
    mules_env = in_dir('mules', lambda: install_mules(args))

    # Install python package 
    subprocess.run([sys.executable, '-m', 'pip', 'install', '.', '--target', args.output / 'python'])   

    # Collect env vars and put in closureenv
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
    args.output = args.output.resolve()
    args.output.mkdir(parents=True, exist_ok=True)
    build.build()
    install(args)
    
if __name__ == '__main__':
    main()