// Build Implication Graph. For N variables, we wil have 2 nodes 2*i and 2*i +1 ( variable and its negation ).
// If a variable must be true (i|i) : Add (~i => i)
// If a variable must be false (~i|~i) : Add (i => ~i)
// Not both (~i|~j) : Add (i => ~j) and (j => ~i)
// Either one of them but not both (i^j): Add (i => ~j) and (j => ~i) and (~i => j) and (~j => i)
// Convert Oring to implications Ex : (i or j) <=> (~i => j) and (~j => i)
tarjanSCC();
bool valid = true;
for(int i=0;i<m;i++){
  if( in_scc[2*i] == in_scc[2*i+1] ){
    valid = false;
    break;
  }
}
if(!valid)
  return false;
//For each component in the reverse topological order, if its
//variables do not already have truth assignments, set all the terms
//in the component to be true. This also causes all of the terms in the
//complementary component to be set to false.
//Note: Tarjan SCC is assumed here as it orders the components
//in reverse topological order.
int values[2*m];
memset(values,-1,sizeof values);
for( auto scc: SCCs ){
  for(int i=0;i<(int)scc.size();i++){
    if( values[scc[i]] != -1 ) continue;
    values[scc[i]] = 1;
    values[scc[i]^1] = 0;
  }
}
// Printing assignment
for(int i=0;i<m;i++)
  cout << values[2*i] << endl;
