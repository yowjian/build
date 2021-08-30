# CLE Conflict Analyzer Tests

## Directory structure

The directory follows a similar structure as examples1-3. The `tests` directory
contains all of the different test directories for the conflict analyzer.

Each test directory contains three files:
1. A `.c` source file with some errors
2. A `output.json` which is the expected json output from the conflict analyzer
3. A `.py` which tests the expected output of building 
3. A `README.md` file which explains in "plain english" how the error or warning arises
    and suggested refactors

To copy an example, use the vscode tasks.

## Todos

- [ ] Description of test and expected result
e.g., known conflict calc_ewma multiply tainted should result in unsatisfiable and diagnostic pointing to issue where get_ewma calls calc_ewma 
- [x] Observed result
e.g., success, failed to catch known conflict X, partial success but CSV missing source level diagnostic info, PDG pass died
git checkout tags of various CLOSURE repos used
data:
- [x] C, LLVM, CLE-JSON
- [x] MZN including model and data, diagnostic CSV
- [x] text output of minizinc and findmus
- [ ] topology.json file produced
- [ ] diagnostic JSON file produced for sending to plugin
- [x] start and end date-time of test
- [x] time taken by each component
- [x] CLE preprocessing
- [x] collation to single file 
- [x] compilation to IR and linking
- [x] PDG opt pass
- [x] rest of input generation (Python)
- [x] minizinc
- [x] findmus
- [x] plugin response construction