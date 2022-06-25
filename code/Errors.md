# Errors in ``graph.h``
## PRIM:
 + When calling ``prim 3 A``, process terminates with segmentation fault
   + ``less-than`` Operator in ``prioqueue.h`` somehow is called with one Entry beeing null
   + the first Entry is != null and contains the Data "D" with an infinite Priority.
 + **FIXED:** Problem was, that ``ventr[v]`` was ``null`` for the start node.
## SCC 
+ still delivers NO output!
+ problem seems to be with the call to or with dfs itself

## DFS
+ everything seems to work as intended, but still seems to deliver emtpy result
+ Maybe an error with call to the sortlisted dfs? 

## DIJKSTRA
+ Questionable Situation with in this example Graph 41 and startnode 0
  + one implementation results ````0 -> 15 -> 11 -> 10 15````
  + the other one results ````0 -> 4 -> 10 15````
  + **Both are valid ways to reach 10 from 0 with minimal weight**
  + Same thing with a few other startnodes
    + here node ``13``:
    + **OTHER IMPL:**
    ```
    ----------------------------------------
    Startknoten: 13
    ----------------------------------------
    13 -> 2 -> 7 -> 11 -> 1 11
    13 -> 2 -> 7 -> 18 -> 4 -> 10 12
    13 -> 2 -> 7 -> 11 9
    13 -> 6 -> 12 5
    13 0
    13 -> 8 -> 14 9
    13 -> 8 -> 15 9
    13 -> 6 -> 12 -> 3 -> 9 -> 16 15
    13 -> 2 -> 7 -> 18 -> 17 13
    13 -> 2 -> 7 -> 18 7
    13 -> 2 -> 19 8
    13 -> 2 4
    13 -> 6 -> 12 -> 3 10
    13 -> 2 -> 7 -> 18 -> 4 8
    13 -> 2 -> 7 -> 18 -> 4 -> 5 10
    13 -> 6 1
    13 -> 2 -> 7 5
    13 -> 8 8
    13 -> 6 -> 12 -> 3 -> 9 14
    ```
    + **MY IMPL:**
    ```
    ----------------------------------------
    Startknoten: 13
    ----------------------------------------
    13 -> 2 -> 7 -> 11 -> 0 13
    13 -> 2 -> 7 -> 11 -> 1 11
    13 -> 2 -> 7 -> 18 -> 4 -> 10 12
    13 -> 2 -> 7 -> 11 9
    13 -> 6 -> 12 5
    13 0
    13 -> 8 -> 14 9
    13 -> 8 -> 15 9
    13 -> 2 -> 7 -> 3 -> 9 -> 16 15
    13 -> 2 -> 7 -> 18 -> 17 13
    13 -> 2 -> 7 -> 18 7
    13 -> 2 -> 19 8
    13 -> 2 4
    13 -> 2 -> 7 -> 3 10
    13 -> 2 -> 7 -> 18 -> 4 8
    13 -> 2 -> 7 -> 18 -> 4 -> 5 10
    13 -> 6 1
    13 -> 2 -> 7 5
    13 -> 8 8
    13 -> 2 -> 7 -> 3 -> 9 14
    ```
# To - Do
## BFS
+ [ ] Validate
## DFS
+ [ ] Validate
+ [ ] Check for the empty ``res.seq``
## TOPSORT
+ [ ] Validate
+ [ ] checks suggest that we couldn't find all cycles
## SCC
+ [ ] Validate
+ [ ] Checks show NO returned data from the function
## PRIM
+ [ ] Validate
+ [ ] Checks show that it does not always find the shortest path
## BELLMAN - FORD
+ [ ] Validate
## DIJKSTRA
+ [ ] Validate
+ [ ] Checks point to something being wrong refer to the erorror description