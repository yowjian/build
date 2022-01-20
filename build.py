#! /usr/bin/env python3
import argparse
import subprocess
import os
from dataclasses import dataclass
from pathlib import Path
from capo.C.build import build as build_capo
from capo.C.build import clean as clean_capo
from hal.build import build as build_hal
from hal.build import clean as clean_hal
from mules.build import build as build_mules
from mules.build import clean as clean_mules


@dataclass
class Args:
    clean: bool


def build() -> None:
    os.chdir('capo/C')
    build_capo()
    os.chdir('../..')
    os.chdir('hal')
    build_hal()
    os.chdir('..')
    os.chdir('mules')
    build_mules()
    os.chdir('..')


def clean() -> None:
    os.chdir('capo/C')
    clean_capo()
    os.chdir('../..')
    os.chdir('hal')
    clean_hal()
    os.chdir('..')
    os.chdir('mules')
    clean_mules()
    os.chdir('..')


def submodules() -> None:
    subprocess.run(['git', 'submodule', 'init'])
    subprocess.run(['git', 'submodule', 'update'])


def main() -> None:
    parser = argparse.ArgumentParser('build.py')
    parser.add_argument('--clean', '-c', action='store_true', default=False)
    args = parser.parse_args(namespace=Args)
    submodules()
    if args.clean:
        clean()
    else:
        build()


if __name__ == '__main__':
    main()

