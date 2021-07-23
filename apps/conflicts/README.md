# CLE Conflict Analyzer Tests

## Directory structure

The directory follows a similar structure as examples1-3. The `.tests` directory
contains all of the different test directories for the conflict analyzer.

Each test directory contains three files:
1. A `.c` source file with some errors
2. A `output.json` which is the expected json output from the conflict analyzer
3. A `README.md` file which explains in "plain english" how the error or warning arises
    and suggested refactors

To copy an example, use the vscode tasks.