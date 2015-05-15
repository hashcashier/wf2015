// O(n^2), If you are getting segmentation faults because of MAXN,
// remove the class and use the code without class
class StableMarriage{
#define MAXN 1010

  int n;
  int pref[MAXN][MAXN];
  int order[MAXN][MAXN];
  public:

  StableMarriage(){}

  // Sets the p1's prefence value of p2
  // values should be from 0->n-1 without duplicates
  // 0 means the highest ranked, n-1 means the lowest
  // Men span from 0 -> n-1 , women span n-> 2*n-1
  void setPref(int p1, int p2, int val){
    pref[p1][p2] = val;
    order[p1][val] = p2;
  }

  void clear(){
    memset(pref,-1,sizeof pref);
    memset(order,-1,sizeof order);
  }

  // n : Number of pairs
  // Returns pair of matches (man, woman) where man [0,n-1] and women [n,2*n-1]
  vector< pair<int,int> > solve(int _n){
    n = _n;
    int manIdx[n];
    int match[2*n];
    memset(manIdx,0,sizeof manIdx);
    memset(match,-1,sizeof match);
    queue<int> free;
    for(int i=0;i<n;i++)
      free.push(i);
    while(!free.empty()){
      int curr = free.front();
      free.pop();
      while(true){
        int woman = order[curr][manIdx[curr]];
        manIdx[curr]++;
        if( match[woman] == -1 ){
          match[woman] = curr;
          match[curr] = woman;
          //cout << "Matched " << curr << " with " << woman << endl;
          break;
        }else if( pref[woman][curr] < pref[woman][match[woman]] ){
          //cout << "Matched " << curr << " with " << woman << " left " << match[woman]  << endl;
          free.push(match[woman]);
          match[match[woman]] = -1;
          match[woman] = curr;
          match[curr] = woman;
          break;
        }else{
          //cout << woman << " refused " << curr << endl;
          continue;
        }
      }
    }

    vector< pair<int,int> > ret;
    for(int i=0;i<n;i++){
      ret.push_back(make_pair(i,match[i]));
    }

    return ret;
  }
};
