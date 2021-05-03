#include "MaxHeap.h"
#include <iostream>
using namespace std;

MaxHeap::MaxHeap(){
  size = 0;
}

void MaxHeap::heapify(int i){
  //if two child exist
  if (2*i+1<size &&2*i+2<size){
    //switch parent with greatest child
    if(heap[2*i+1]>heap[i] && heap[2*i+1]>heap[2*i+2]){
      int temp = heap[i];
      heap[i] = heap[2*i+1];
      heap[2*i+1] = temp;
    }else if(heap[2*i+2]>heap[i] && heap[2*i+2]>heap[2*i+1]){
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
  //if only one child exists
  else if(2*i+1<size){
    //if child is greater then switch
    if(heap[2*i+1]>heap[i]){
      int temp = heap[i];
      heap[i] = heap[2*i+1];
      heap[2*i+1] = temp;
    } else{
      return;
    }

    //if we are not at the root, then recurse
    if(i!=0){
      heapify((i-1)/2);
    }
  } 
  //if no children and not at root then recurse
  else{
    if(i!=0){
      heapify((i-1)/2);
    }
  }

}

void MaxHeap::insert(int val){
  heap[size] = val;
  size++;
  heapify(size-1);
}

int MaxHeap::max(){
  return heap[0];
}

void MaxHeap::display(){
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

