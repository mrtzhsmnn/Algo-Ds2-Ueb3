# Errors in ``graph.h``
## PRIM:
 + When calling ``prim 3 A``, process terminates with segmentation fault
   + ``less-than`` Operator in ``prioqueue.h`` somehow is called with one Entry beeing null
   + the first Entry is != null and contains the Data "D" with an infinite Priority.
 + **FIXED:** Problem was, that ``ventr[v]`` was ``null`` for the start node.
 + **NEW ERROR:**  loooooooooooooong paths
   + Algorithm seemingly enjoys long walks, chooses the node with the lower number over the one with the shorter path
   + Problem: I have NO idea, how the hell this behaviour occurs, as I have implemented the algorithm exactly as described in the slides
   + **~~FIXED~~:** I found the error, the error are his slides.
   + **EDIT:** NOT FIXED!!!!
     + now my algorithm finds shorter paths and sometimes longer paths than the algorithm I test against
     + **KINDA FIXED:** variance occurs because variability brought in from the prioqueue, even the same implementation run twice delivers varying results.
## SCC 
+ ~~still delivers NO output!~~ **FIXED:** Problem was with the transpose function, and also a call to null in the inner while loop
+ now delivers output, that is right in ~~some~~ (edit):[ALL] cases
+ still no real idea how to fix it maybe need to check the starting-times aswell?
+ **FIXED:** checking starting times aswell was the answer

## TOPSORT:
+ not finding all cycles is a bad thing
  + **FIXED:**  I did them magic with the call to recursion
+ Now finding all cycles but still delivering the wrong solution
  + **FIXED:** with a complete redesign


## DFS
+ ~~everything seems to work as intended, but still seems to deliver emtpy result~~ **FIXED:** Problem was not with dfs
+ Maybe an error with call to the sortlisted dfs? (edit): NO

## DIJKSTRA
+ Questionable Situation with in this example Graph 41 and startnode 0
  + one implementation results ````0 -> 15 -> 11 -> 10 15````
  + the other one results ````0 -> 4 -> 10 15````
  + **Both are valid ways to reach 10 from 0 with minimal weight**
  + **KINDA FIXED:** variance occurs because variability brought in from the prioqueue, even the same implementation run twice delivers varying results.

# To - Do
## BFS
+ [ ] Validate
## DFS
+ [ ] Validate
+ [x] Check for the empty ``res.seq``
## TOPSORT
+ [ ] Validate
+ [x] checks suggest that we couldn't find all cycles
## SCC
+ [ ] Validate
+ [x] Checks show NO returned data from the function
+ [x] Now data is incorrect, fix that
## PRIM
+ [ ] Validate
+ [x] Checks show that it does not always find the shortest path and sometimes a shorter path :0
## BELLMAN - FORD
+ [ ] Validate
## DIJKSTRA
+ [ ] Validate
+ [x] Checks point to something being wrong, refer to the error description