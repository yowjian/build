# CLOSURE Example: Test2

## Cross Domain Topology

* Enclaves: 2 (Orange, Purple)

## Security Intent

* Variable `a` in `get_a()` is in ORANGE and can be shared with PURPLE
* Variable `b` in `get_b()` is in PURPLE and cannot be shared
* Calculated EWMA must be available on ORANGE side (for printing there)

## Dependencies

* CLE Version:
* Refactoring Methodology:
  
  * Refactoring of function needed for consistent security policy annotation; b can't be shared to orange so get_b and calc_ewma need to run on PURPLE. a blessed function will then convert the b to a value passable to orange.

* HAL API:
* DFDL/DAGR:

## Other Tools

None