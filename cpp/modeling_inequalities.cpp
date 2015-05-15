/*
a0 - a1 ≤ c0 
a1 - a2 ≤ c1
..
ak - aq ≤ cx
- Map ai’s to graph nodes, and cx to graph edges. 
- Connect aq to ak with an edge with cost cx
- Create additional node connect it with all other nodes with edge of weight 0.
- Run shortest path algorithm, the answer is in the distance array.
- No solution if and only if there’s a negative weight cycle.
*/
