#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

static const int HEAD_VAL = -1;
static const int NOT_FOUND = -(1<<30);

class node{
  public:
    int value;
    int level;
    int length;
    node* next;
    node* down;

    void init(int v,int lvl, int len,node* n,node* d){
      value = v;
      level = lvl;
      length = len;
      next = n;
      down = d;
    }

    node(int v,int lvl, int len,node* n,node* d){
      init(v,lvl,len,n,d);
    }

    node(int v,int lvl,node* n,node* d){
      init(v,lvl,-1,n,d);
    }
};

class SkipList{
  // In the main srand(time(NULL)); // VERY IMPORTANT!
  int size;
  node* head;

  double random()
  {
    double f = (double)(rand()%10000);
    return f/=10000.0;
  }

  int randomizeLevel(){
    int level = 0;
    while(level <= (head->level) && random() < 0.5)
      ++level;
    return level;
  }

  public:
  SkipList(){
    head = new node(HEAD_VAL,0,NULL,NULL);
    size = 0;
  }

  bool search(int val){
    node* cur = head;
    while(cur != NULL){
      if(cur->next == NULL || cur->next->value > val){
        cur = cur->down;
        continue;
      }else if(cur->next->value == val)
        return true;
      cur = cur->next;
    }
    return false;
  }

  bool add(int val){
    if(search(val))
      return false;
    int level = randomizeLevel();
    if(level > head->level){
      head = new node(HEAD_VAL, level, NULL, head);
    }
    node* cur = head;
    node* last = NULL;
    while(cur != NULL){
      if(cur->next == NULL || cur->next->value > val){
        if(level >= cur->level){
          node* toAdd = new node(val, cur->level, cur->next, NULL);
          if(last != NULL)
            last->down = toAdd;
          cur->next = toAdd;
          last = toAdd;
        }
        cur = cur->down;
        continue;
      }
      cur = cur->next;
    }
    ++size;
    return true;
  }

  void print(){
    node* cur = head;
    node* first = head;
    while(first != NULL){
      cur = first;
      cout << first->level << " ";
      while(cur != NULL){
        cout << cur->value << " ";
        cur = cur->next;
      }
      cout << endl;
      first = first->down;
    }
  }

  bool remove(int val){
    if(!search(val))
      return false;
    node* cur = head;
    while(cur != NULL){
      if(cur->next == NULL || cur->next->value >= val){
        if (cur->next != NULL && cur->next->value == val) {
          cur->next = cur->next->next;
        }
        cur = cur->down;
        continue;
      }
      cur = cur->next;
    }
    --size;
    if(head->next == NULL)
      head = head->down;
    return true;
  }
};

class IndexableSkipList{
  int size;
  node* head;

  IndexableSkipList(){
    size = 0;
    head = new node(HEAD_VAL,0,-1,NULL,NULL);
  }

  double random()
  {
    double f = (double)(rand()%10000);
    return f/=10000.0;
  }

  int randomizeLevel(){
    int level = 0;
    while(level <= (head->level) && random() < 0.5)
      ++level;
    return level;
  }

  public:
  int removeElement(int index){
    if (index < 0 || index >= size)
      return -1;
    //E removed = NULL;
    int removed;
    int cur_pos = -1;
    node *cur = head;
    while (cur != NULL) {
      if (cur->next != NULL && cur_pos + cur->length < index) {
        cur_pos += cur->length;
        cur = cur->next;
      } else {
        cur->length--;
        if(cur_pos + cur->length + 1 == index && cur->next != NULL){
          removed = cur->next->value;
          cur->length += (cur->next->length == -1 ? 0 : cur->next->length);
          cur->next = cur->next->next;
        }
        cur = cur->down;
      }
    }
    --size;
    if(size == 0){
      head = new node(HEAD_VAL, 0, -1, NULL, NULL);
    }
    return removed;
  }

  bool addElement(int val, int index) {
    if (index < 0 || index > size)
      return false;
    int level = randomizeLevel();
    if (level > head->level) {
      head = new node(HEAD_VAL, level, index, NULL, head);
    }
    int cur_pos = -1;
    node* cur = head;
    node* last = NULL;
    while (cur != NULL) {
      if (cur->next != NULL && cur_pos + cur->length < index) {
        cur_pos += cur->length;
        cur = cur->next;
      } else {
        cur->length++;
        if (level >= cur->level) {
          node* toAdd = new node(val, cur->level, 0, cur->next, NULL);
          if(last != NULL)
            last->down = toAdd;
          cur->next = toAdd;
          last = toAdd;
          toAdd->length = cur->length - (index - cur_pos);
          cur->length = index - cur_pos;
        }
        cur = cur->down;
      }
    }
    ++size;
    return true;
  }

  int getElementAtIndex(int index) {
    if (index < 0 || index >= size)
      return NOT_FOUND;
    node* cur = head;
    int cur_pos = -1;
    while (cur != NULL) {
      if (cur_pos == index)
        return cur->value;
      if (cur->next == NULL || cur_pos + cur->length > index) {
        cur = cur->down;
        continue;
      } else {
        cur_pos += cur->length;
        cur = cur->next;
      }
    }
    return -1;
  }

  void print() {
    node* cur = head;
    node* first = head;
    while (first != NULL) {
      cur = first;
      cout << first->level << " ";
      while (cur != NULL) {
        cout << "[" << cur->value << " " << cur->length << "] ";
        cur = cur->next;
      }
      cout << endl;
      first = first->down;
    }
  }
};

int main(){
  srand(time(NULL));
  SkipList list;
  for(int i=1;i<20;i++)
    list.add(i);
  list.print();
  list.remove(2);
  list.print();
}
