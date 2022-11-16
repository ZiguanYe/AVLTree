#include <iostream>
#include <cstdlib>
#include "internal-range.h"
using namespace std;


Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;
Node* g;
Node* h;
Node* i;
Node* j;
Node* k;
Node* l;
Node* m;
Node* n;
Node* o;
Node* p;

void setNode(Node* n, int key, Node* left=NULL, Node* right=NULL, Node* p=NULL)
{
  n->key = key;
  n->left = left;
  n->right = right;
  n->parent = p;
}
/**
 *  root => NULL
 */
int test_empty()
{
  const char* t = " <empty=NULL> \n";
  int cnt = sumInternalRange(nullptr, 5, -10, 10);
  int exp = 0;
  if(exp != cnt){
    cout << "test_empty() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test_empty() passed" << endl;
    return 0;
  }

}

/**
        a
*/

int test_root_only()
{ 
  const char* t = " a \n";
  setNode(a,1,NULL,NULL);
  int cnt = sumInternalRange(a, 1, 0, 10);
  int exp = 1;
  if(exp != cnt){
    cout << "test_root_only() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test_root_only() passed" << endl;
    return 0;
  }

}

int test_depth0()
{ 
  const char* t = " a \n";
  setNode(a,1,NULL,NULL);
  int cnt = sumInternalRange(a, 0, 0, 10);
  int exp = 0;
  if(exp != cnt){
    cout << "test_depth0() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test_depth0() passed" << endl;
    return 0;
  }

}

/**
  a
 /  
b   
*/


int test_root_left()
{
  const char* t =
"  a \n\
 /   \n\
b    \n\
";

  setNode(b,1,NULL,NULL,a);
  setNode(a,2,b,NULL);
  int cnt = sumInternalRange(a, 2, 0, 5);
  int exp = 2;
  if(exp != cnt){
    cout << "test_root_left() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test_root_left() passed" << endl;
    return 0;
  }

}

/**
  a
 /  
b   
*/
int test_root_left_depth()
{
  const char* t =
"  a \n\
 /   \n\
b    \n\
";

  setNode(b,1,NULL,NULL,a);
  setNode(a,2,b,NULL);
  int cnt = sumInternalRange(a, 1, 0, 5);
  int exp = 1;
  if(exp != cnt){
    cout << "test_root_left_depth() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test_root_left_depth() passed" << endl;
    return 0;
  }

}

/**
  a
 /  
b   
*/
int test_root_left_range()
{
  const char* t =
"  a \n\
 /   \n\
b    \n\
";

  setNode(b,1,NULL,NULL,a);
  setNode(a,2,b,NULL);
  int cnt = sumInternalRange(a, 2, 1, 1);
  int exp = 1;
  if(exp != cnt){
    cout << "test_root_left_range() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test_root_left_range() passed" << endl;
    return 0;
  }

}

/**
  a
   \
    b
   / \
  c   d
     / \
    e   f
   / \
  g   h
 /
i
*/

int test1()
{
  const char* t =
"  a       \n\
   \\       \n\
    b      \n\
   / \\     \n\
  c   d    \n\
     / \\   \n\
    e   f  \n\
   / \\     \n\
  g   h    \n\
 /         \n\
i          \n\
";
  setNode(i,4,NULL,NULL,g);
  setNode(h,7,NULL,NULL,e);
  setNode(g,5,i,NULL,e);
  setNode(f,9,NULL,NULL,d);
  setNode(e,6,g,h,d);
  setNode(d,8,e,f,b);
  setNode(c,2,NULL,NULL,b);
  setNode(b,3,c,d,a);
  setNode(a,1,NULL,b);
  int cnt = sumInternalRange(a, 6, 2, 7);
  int exp = 6;
  if(exp != cnt){
    cout << "test1() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test1() passed" << endl;
    return 0;
  }

}


/**
  a
   \
    b
   / \
  c   d
     / \
    e   f
   / \
  g   h
 /
i
*/

int test1_depth()
{
  const char* t =
"  a       \n\
   \\       \n\
    b      \n\
   / \\     \n\
  c   d    \n\
     / \\   \n\
    e   f  \n\
   / \\     \n\
  g   h    \n\
 /         \n\
i          \n\
";
  setNode(i,4,NULL,NULL,g);
  setNode(h,7,NULL,NULL,e);
  setNode(g,5,i,NULL,e);
  setNode(f,9,NULL,NULL,d);
  setNode(e,6,g,h,d);
  setNode(d,8,e,f,b);
  setNode(c,2,NULL,NULL,b);
  setNode(b,3,c,d,a);
  setNode(a,1,NULL,b);
  int cnt = sumInternalRange(a, 4, 2, 7);
  int exp = 3;
  if(exp != cnt){
    cout << "test1_depth() failed - Expected: " << exp << " / Actual: " << cnt << endl;
    cout << "Tree used:\n" << t << endl;
    return 1;
  }
  else {
    cout << "test1_depth() passed" << endl;
    return 0;
  }

}

int main()
{
  a = new Node(1);
  b = new Node(2);
  c = new Node(3);
  d = new Node(4);
  e = new Node(5);
  f = new Node(6);
  g = new Node(7);
  h = new Node(8);
  i = new Node(9);
  j = new Node(10);
  k = new Node(11);
  l = new Node(12);
  m = new Node(13);
  n = new Node(14);
  o = new Node(15);
  p = new Node(16);
  int failed = 0;
  int total = 0;
  failed += test_empty();
  total++;
  failed += test_root_only();
  total++;
  failed += test_depth0();
  total++;
  failed += test_root_left();
  total++;
  failed += test_root_left_depth();
  total++;
  failed += test_root_left_range();
  total++;
  failed += test1();
  total++;
  failed += test1_depth();
  total++;
  return failed;
}
