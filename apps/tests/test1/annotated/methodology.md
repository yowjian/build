# CLE Annotations
- Change PURPLE to indicate non-shareable for e case-1. Otherwise said 'oneway' which disagreees with intent.
   -- CLE FIX: CLE to say that no CDF means non-shareable
   


# Conflilct Analysis
xline 24: (Warning): Function `get_a` utilizes ORANGE labeled data, but `get_a` is not annotated. Assuming `get_a` and return value also ORANGE. 
xline 32: (Warning): Function `get_b` utilizes PURPLE labeled data, but `get_b` is not annotated. Assuming `get_b` and return value also PURPLE.
(Note: above are warnings because the return value comes from the annotated variable, so the return security type can be inferred)
line 43: (Warning): Assignment between unannotated variable `a` and ORANGE return type of `get_a`. `a` tainted as ORANGE.
line 44: (Warning): Assignment between unannotated variable `b` and PURPLE return type of `get_b`. `b` tainted as PURPLE.
line 45: (Error):   Function `calc_ewma` called with arguments of different levels.
line 45: (Error):   Label of evaluated expression cannot be determined for assignment to 'c'
line 45: (Error):   Function `calc_ewma` passed nonshareable argument `b`. Function annotation required to certify no unintended leaks (return value, static/global taint).

1. build graph
2. propagate label taints based on graph connectivity
2a. apportion functionality to clusters, one per level (a level can have multiple labels)
3. look for conflicts [at each node and edge, test for all supported conflicts]
   - enter main
   - enter ewma main -- tainted putple
   - x part of ewma_main -- tainted purple
   - x assigned return of get_a
   - get_a is tainted orange
   - assignment is a conflict

  if we continue: calc_ewma is called with arguments one of which is conflicted (and in this case, also different levels)

  [Alternatively, while clustering we started with get_a
   get_a is orange
   get_a return is assinged to x, so let's color x orange
   x is in scope of ewma_main
   ewma_main contains ewma which is purple, so function is tainted purple
   X1: variable x tainted orange is in function tainted purple
   But more user-firenly message would be:
   X2: x is assigned a value tained orange while x belongs to purple
  ]


ewma_main(purple) ---- x (purple) --X-- get_a (orange)
ewma_main(purple) --X1-- x (orange) -------- get_a (orange)
                    \_______X2______/




Actual Error/Warnings
line 42: (Error):   ewma_main tainted with label 'PURPLE', variable 'x' tainted PURPLE, get_a is tainted with O 

# Methodology
0. Lables in partiiotned program are only those that pertain to that level
1. Functions/variables/basic blocks annotated for a certain level only reside in that level
2. variables annotated as shareable oneway must xdc_async_send the value upon each update; corresponding xdc_blocking_recv on remote
   - optimize by putting the send/recv at end of basic blocks if sequential accesses occur
3. Rename remote variables with __shdw___ prepended

# Refactoring
0a. Begin work on two files for each level
0b. add #include <xdcomms.h> to both files
1. Create global HAL pub sockets for oneway variables, named <orig var name>_xdc_pub_sock, set to NULL
2. Initalize HAL sockets in main (6mo demo checked for null on each use, if null it created the socket)
3. each update to a needs to be sent

Program is deterministic, single thread of control
When partitioned, it is not tolerant to loss and sensitive to out of order


Synchronous

ORANGE (acts as slave)
- keep ORANGE tag (drop PURPLE tag definition)
- response struct which will be tagged (include sec,mux,typ details for HAL config gen) 
- get_a()
- new main function with server that waits for and responds to RPC on get_a()

PURPLE (acts as master)
- PURPLE tag
- get_b()
- rpc_get_a() client function which reuests and waits for response
- modified ewma_main which calls rpc_get_a instead of get_a
  
Asynchronous 1 (not recommended, but similar to 6 month demo)
Both sides run loop
  - one side does get_a and sends (i,a) to the other side
  - other side does get_b, matches with correct (i,a) and calculates ewma

Asynchronous 2
right waits for a from other side
left gets a sends to right
right waits, gets b, calculates ewma
loop

// Modify CLE to suppport provenance
// Verification tools must track provenance across multiple domains
//ctag level purple
// -- cdf can share to orange, can share to green (no sharing with yellow)
struct foo A;

/ / when data crosses boundary from purple to orange
// data must be tagged again
// with new label FOO
// level purple, provenance orange, can share to orange, can share to green
(carry over cdfs to receive side to preserve provenance)
