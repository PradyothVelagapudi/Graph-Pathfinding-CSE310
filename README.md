Final project for CSE 310 Data Structures and Algorithms

Uses Stack and Heap data structures to implement common pathfinding algorithms
on weighted and unweighted graphs.

Usage: ./PJ3 <InputFile> <GraphType> <Flag>
<GraphType> = "DirectedGraph" or "UndirectedGraph"
<Flag> = 1 to place new nodes at front of adjacency lists, 2 to place at rear
Format of input file:
The first line contains two positive
integers, representing the number of vertices n and number of edges m, respectively. Each of the
next m lines has the following format: `edgeIndex u v w(u, v)` 
where u is the start vertex of edge (u, v), v is the end vertex of edge (u, v), w(u, v) is the weight
of edge (u, v), and edgeIndex is the index of edge (u, v).

Instructions:
Stop: Stops execution
PrintADJ: Prints adjacency lists for all vertices
SinglePair <source> <destination>: Applies Dijkstra's algorithm to compute shortest path from source vertex to destination
SingleSource <source>: Applies Dijkstra's algorithm to compute shortest paths from source vertex to all reachable vertices
PrintLength <u> <v>: Prints length of shortest path between vertices. Only valid if u = source and v = destination in most recent SinglePair or SingleSource execution
PrintPath <u> <v>: Prints shortest path between vertices. Only valid if u = source and v = destination in most recent SinglePair or SingleSource execution
Invalid Instruction: Will display error message

