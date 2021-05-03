

class MinHeap{
  private:
    int heap [6];
    int size;
  public:
    MinHeap();
    void heapify(int i);
    void insert(int val);
    void display();
    int min();

};