class Node{
  public:
  int key,priority,size;
  Node* left ,*right;
  Node(int k,int p,int s,Node *l,Node*r)
  {
    key = k;
    priority = p;
    size = s;
    left = l;
    right = r;
  }
};

class Treap{
  // srand(time(NULL)) in main. VERY IMPORTANT
  Node* nill;
  Node* root;

  void update(Node* root){
    if(root != nill){
      root->size = root->left->size + 1 + root->right->size;
    }
  }

  Node * rotate_left(Node* root){
    Node* T = root->right;
    root->right = T->left;
    T->left = root;
    update(T->left);
    update(T);
    return T;
  }

  Node * rotate_right(Node* root){
    Node* T = root->left;
    root->left = T->right;
    T->right = root;
    update(T->right);
    update(T);
    return T;
  }

  Node* balance (Node* root){
    if(root->priority < root->left->priority)
      return rotate_right(root);
    if(root->priority < root->right->priority)
      return rotate_left(root);
    return root;
  }
  
  Node* _insert(int k,Node* root){
    if(root == nill) {
      return new Node(k,rand(),1,nill,nill);
    }
    if(k < root->key) {
      root->left = _insert(k,root->left);
    }
    if(k > root->key) {
      root->right = _insert(k,root->right);
    }
    update(root);
    return balance(root);
  }

  Node* _erase(int k,Node* root){
    if(root == nill) {
      return root;
    }
    if(k < root->key){
      root->left = _erase(k,root->left);
      update(root);
      return root;
    }
    if(k > root->key){
      root->right = _erase(k,root->right);
      update(root);
      return root;
    }
    if(root->left == nill && root->right == nill) {
      delete root;
      return nill;
    }else {
      if(root->left->priority < root->right->priority) {
        root = rotate_left(root);
      }else {
        root = rotate_right(root);
      }
      return _erase(k,root);
    }
  }

  int _kth(int k, Node* root){
    if( k < root->left->size )
      return _kth(k,root->left);
    if(k > root->left->size)
      return _kth(k-(root->left->size)-1,root->right);
    return root->key;
  }

  int _count(int k,Node* root){
    if(root == nill)
      return 0;
    if(k < root->key)
      return _count(k,root->left);
    if(k > root->key)
      return root->left->size + 1 + _count(k,root->right);
    return root->left->size;
  }

  public:
  Treap(){
    nill = new Node(0,-1,0,NULL,NULL);
    root = nill;
  }

  void insert(int k){
    root = _insert(k,root);
  }

  void erase(int k){
    root = _erase(k,root);
  }

  // return the k-th smallest element (0-based)
  // Check the size first
  int kth(int k){
    return _kth(k,root);
  }

  // return the number of elements smaller than x
  int count(int k){
    return _count(k,root);
  }

  int size(){
    return root->size;
  }

};
