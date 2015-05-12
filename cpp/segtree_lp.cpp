class SegTree{
  public:
  vector<int> t;
  vector<int> u;
  int n;

  SegTree(int n2){
    t.assign(4*n2,0);
    u.assign(4*n2,0);
    n = n2;
    build();
  }

  void build(){

  }

  // This function varies with different usages
  void push(int index){
    if(u[index])
    {
      if(2*index < sz(t)){
        u[2*index] = 1;
        u[2*index + 1] = 1;
        t[2*index] = t[index];
        t[2*index + 1] = t[index];
      }
      u[index] = 0;
    }
  }

  int query2(int index, int L,int R,int i,int j)
  {
    if( L >=i && R<=j) return t[index];

    push(index);

    int mid = (L+R)/2;
    if(j<=mid)
        return query2(2*index, L, mid, i, j);
    else if(i>mid)
        return query2(2*index+1, mid+1, R, i, j);
    else{
      int p1 = query2(2*index , L , mid , i,j);
      int p2 = query2(2*index + 1 , mid + 1 , R , i,j);
      return max(p1,p2);
    }
  }

  void update2(int index , int l,int r ,int val , int L ,int R)
  {
    int mid = (L+R)/2;
    if(L>r || R<l) return;

    if(L==R)
    {
      t[index] = val;
      return;
    }
    if(L>=l && R<=r)
    {
      // This one also vaires with different usages
      t[index] = val;
      u[index]= 1;
      return;
    }

    push(index);

    update2(2*index + 1 , l , r , val , mid+1 , R);
    update2(2*index , l , r , val , L , mid);

    t[index] = max(t[2*index], t[2*index+1]);
  }

  int query(int from,int to){
    return query2(1, 0, n-1 , from, to);
  }

  void update(int from,int to,int val){
    return update2(1, from , to , val , 0 , n-1);
  }
};

int main(){
  SegTree a(10);
  a.update(0,5,1);
  a.update(5,9,2);
  cout << a.query(6,6) << endl;
}

