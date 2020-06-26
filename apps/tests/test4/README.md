# CLOSURE Example: Test4

This example is almost the same as test3, with one significant difference : one-way /diode

## Directory Structure

* plain:       contains original unannotated application
* annotated:   contains annotations applied to plain to reflect security intent below
* refactored:  contains annotated code refactored for making security-compliant partitioning feasible
* divvied:     contains code divvied up into separate directories for each level/enclave as input for GEDL generation, followed by code autogeneration
* partitioned: contains fully paritioned sources with cross-domain RPCs, marshalling, serialization, tags, HAL API, etc.

## Cross Domain Topology

* Enclaves: 2 (Orange, Purple)
* Only a diode between orange and purple is available, only push

## Security Intent

* Variable `a` in `get_a()` is in ORANGE and cannot be shared 
* Variable `b` in `get_b()` is in ORANGE and cannot be shared 
* EWMA must therefore be computed on ORANGE; EWMA is sharable to PURPLE.
Calculated EWMA must be available on PURPLE side (for printing there)

## Dependencies

* CLE Version:
* Refactoring Methodology:
  
  * refactoring of function needed for consistent security policy annotation; ewma_main on purple, but touches non-shareable orange side vars  
* HAL API:
* DFDL/DAGR:

## Other Tools

None
