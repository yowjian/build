# CLOSURE Example: Test3

## Cross Domain Topology

* Enclaves: 2 (Orange, Purple)

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