class MaxHeap{
  private:
    int heap [6];
    int size;
  public:
    MaxHeap();
    void heapify(int i);
    void insert(int val);
    void display();
    int max();

};