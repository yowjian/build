from distutils.core import setup, Extension
from pathlib import Path
setup(
    name="closure",
    version="2.0.0",
    author="Benjamin Flin",
    author_email="benjamin.flin@peratonlabs.com",
    description="Compiler and Partitioner Optimizer (CAPO)",
    long_description="file: README.md",
    long_description_content_type="text/markdown",
    url = "https://github.com/gaps-closure/build",
    project_urls={
        "Bug Tracker": "https://github.com/gaps-closure/build/issues"
    },
    classifiers=["Programming Language :: Python :: 3"],
    install_requires=[
        f"capo @ file://localhost/{Path('./capo').resolve()} #egg=capo"
        f"hal @ file://localhost/{Path('./hal').resolve()} #egg=hal"
        f"mules @ file://localhost/{Path('./hal').resolve()} #egg=hal"
    ],
)