#include <iostream>
#include "MinHeap.h"
using namespace std;

int main() {
  MinHeap* myHeap = new MinHeap();
  myHeap->insert(5);
  myHeap->insert(2);
  myHeap->insert(3);
  myHeap->insert(4);
  myHeap->insert(1);
  myHeap->insert(6);
  myHeap->display();
  cout<<1<<endl;
  return 0;
}

