# Errors in ``graph.h``
## PRIM:
 + When calling ``prim 3 A``, process terminates with segmentation fault
   + ``less-than`` Operator in ``prioqueue.h`` somehow is called with one Entry beeing null
   + the first Entry is != null and contains the Data "D" with an infinite Priority.
 + **FIXED:** Problem was, that ``ventr[v]`` was ``null`` for the start node.