#include <iostream>
#include <cstdlib>
#include "equal-paths.h"
using namespace std;


Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;
Node* g; 

void setNode(Node* n, int key, Node* left=NULL, Node* right=NULL)
{
  n->key = key;
  n->left = left;
  n->right = right;
}

void test1(const char* msg)
{
  setNode(a,1,NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test2(const char* msg)
{
  setNode(a,1,b,NULL);
  setNode(b,2,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test3(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,NULL,NULL);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test4(const char* msg)
{
  setNode(a,1,NULL,c);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test5(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,NULL,d);
  setNode(c,3,NULL,NULL);
  setNode(d,4,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void testExample1(const char* msg) //should be true 
{
  setNode(a, 1, b, c); 
  setNode(b, 2, d, e); 
  setNode(c, 3, f, NULL); 
  setNode(d, 4, NULL, NULL); 
  setNode(e, 5, NULL, NULL); 
  setNode(f, 6, NULL, NULL); 
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void testExample2(const char* msg) //should be false 
{
  setNode(a, 1, b, c); 
  setNode(b, 2, d, e); 
  setNode(c, 3, NULL, NULL); 
  setNode(d, 4, NULL, NULL); 
  setNode(e, 5, NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl; 
}

void testExample3(const char* msg) //should be true 
{
  setNode(a, 1, b, c); 
  setNode(b, 2, d, NULL); 
  setNode(c, 3, e, NULL); 
  setNode(d, 4, NULL, NULL); 
  setNode(e, 5, NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl; 
}

void testExample4(const char* msg) //should be false 
{
  setNode(a, 1, b, c); 
  setNode(b, 2, d, e); 
  setNode(c, 3, f, NULL); 
  setNode(d, 4, NULL, NULL); 
  setNode(e, 5, g, NULL);
  setNode(f, 6, NULL, NULL); 
  setNode(g, 7, NULL, NULL); 
  cout << msg << ": " <<   equalPaths(a) << endl;
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

  test1("Test1");
  test2("Test2");
  test3("Test3");
  test4("Test4");
  test5("Test5");
  testExample1("TestExample1"); 
  testExample2("TestExample2");
  testExample3("TestExample3"); 
  testExample4("TestExample4"); 

  delete a;
  delete b;
  delete c;
  delete d;
  delete e; 
  delete f; 
  delete g; 
}

