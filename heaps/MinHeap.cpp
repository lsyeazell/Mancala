#include "MinHeap.h"
#include <iostream>
using namespace std;

MinHeap::MinHeap(){
  size = 0;
}

//recursive method used for heap construction
void MinHeap::heapify(int i){
  //if both children nodes exist
  if (2*i+1<size &&2*i+2<size){

    //switch parent with smallest child
    if(heap[2*i+1]<heap[i] && heap[2*i+1]<heap[2*i+2]){
      int temp = heap[i];
      heap[i] = heap[2*i+1];
      heap[2*i+1] = temp;
    }else if(heap[2*i+2]<heap[i] && heap[2*i+2]<heap[2*i+1]){
      int temp = heap[i];
      heap[i] = heap[2*i+2];
      heap[2*i+2] = temp;
    } else{
      return;
    }

    //if we are not at the root, then recurse 
    if(i!=0){
      heapify((i-1)/2);
    }
  } 
  //if only one child node exists
  else if(2*i+1<size){
    //switch parent node with child if child is smaller
    if(heap[2*i+1]<heap[i]){
      int temp = heap[i];
      heap[i] = heap[2*i+1];
      heap[2*i+1] = temp;
    }else{
      return;
    }

    //if we are not at the root, then recurse
    if(i!=0){
      heapify((i-1)/2);
    }
  } 
  //if node has no children
  else{
    ////if we are not at the root, then recurse
    if(i!=0){
      heapify((i-1)/2);
    }
  }

}

//inserts val and calls heapify to fix heap structure
void MinHeap::insert(int val){
  heap[size] = val;
  size++;
  heapify(size-1);
}

//returns minimum value
int MinHeap::min(){
  return heap[0];
}

//prints heap
void MinHeap::display(){
  for(int i=0;i<size;i++){
    if (i==0){
      cout<<"   "<<heap[i]<<endl;
    }else if(i==1){
      cout<<" "<<heap[i]<<"   ";
    }else{
      cout<<heap[i]<<" ";
    }

    if(i==2||i==size-1){
      cout<<endl;
    }
  }
}

