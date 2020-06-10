There are two enclaves: one at level ORANGE, and another at level PURPLE for
all the cases below.  But there are different security intents in each case.
For each case, there will be a separate solution.

Case 1:

There are two enclaves: one at level ORANGE, and another at level PURPLE
Variable `a` in `get_a()` is in ORANGE and can be shared with PURPLE
Variable `b` in `get_b()` is in PURPLE and cannot be shared
Calculated EWMA must be available on PURPLE side (for printing there)

Case 2:

Variable `a` in `get_a()` is in ORANGE and can be shared with PURPLE
Variable `b` in `get_b()` is in PURPLE and cannot be shared
Calculated EWMA must be available on ORANGE side (for printing there)

Case 3:

Variable `a` in `get_a()` is in ORANGE and cannot be shared 
Variable `b` in `get_b()` is in ORANGE and cannot be shared 
EWMA is therefore computed on ORANGE and EWMA must be sharable to PURPLE.
Calculated EWMA must be available on PURPLE side (for printing there)


