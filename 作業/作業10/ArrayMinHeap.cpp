#include <iostream>
#include <cmath>
#include <vector>
using namespace::std;

void visit(int& item);

template<class ItemType>
class HeapInterface{
public:
    /** Sees whether this heap is empty.
     @return True if the heap is empty, or false if not. */
    virtual bool isEmpty() const = 0;
    
    /** Gets the number of nodes in this heap.
     @return The number of nodes in the heap. */
    virtual int getNumberOfNodes() const = 0;
    
    /** Gets the height of this heap.
     @return The height of the heap. */
    virtual int getHeight() const = 0;
    
    /** Gets the data that is in the root (top) of this heap.
     For a maxheap, the data is the largest value in the heap;
     for a minheap, the data is the smallest value in the heap.
     @pre The heap is not empty.
     @post The root’s data has been returned, and the heap is unchanged.
     @return The data in the root of the heap. */
    virtual ItemType peekTop() const = 0;
    
    /** Adds a new node containing the given data to this heap.
     @param newData The data for the new node.
     @post The heap contains a new node.
     @return True if the addition is successful, or false if not. */
    virtual bool add(const ItemType& newData) = 0;
    
    /** Removes the root node from this heap.
     @return True if the removal is successful, or false if not. */
    virtual bool remove() = 0;
    
    /** Removes all nodes from this heap. */
    virtual void clear() = 0;
}; // end HeapInterface

template<class ItemType>
class ArrayMinHeap : public HeapInterface<ItemType>{
private:
    static const int ROOT_INDEX = 0;        // Helps with readability
    static const int DEFAULT_CAPACITY = 500;
    ItemType* items;                        // Array of heap items
    int itemCount;                          // Current count of heap items
    //int maxItems;                         // Maximum capacity of the heap
    // ---------------------------------------------------------------------
    // Most of the private utility methods use an array index as a parameter
    // and in calculations. This should be safe, even though the array is an
    // implementation detail, since the methods are private.
    // ---------------------------------------------------------------------
    
    // Returns the array index of the left child (if it exists).
    int getLeftChildIndex(const int nodeIndex) const;
    
    // Returns the array index of the right child (if it exists).
    int getRightChildIndex(int nodeIndex) const;
    
    // Returns the array index of the parent node.
    int getParentIndex(int nodeIndex) const;
    
    // Tests whether this node is a leaf.
    bool isLeaf(int nodeIndex) const;
    
    // Converts a semiheap to a heap.
    void heapRebuild(int subTreeRootIndex);
    
    // Creates a heap from an unordered array.
    void heapCreate();
    
    void preorder(void visit(ItemType&), int subTreeRootIndex) const;
    void inorder(void visit(ItemType&), int subTreeRootIndex) const;
    void postorder(void visit(ItemType&), int subTreeRootIndex) const;
    
public:
    ArrayMinHeap(): itemCount(0) { items = new ItemType[DEFAULT_CAPACITY]; };
    ArrayMinHeap(const ItemType someArray[], const int arraySize);
    virtual ~ArrayMinHeap(){ delete items; };
    
    // HeapInterface Public Methods:
    bool isEmpty() const{ return itemCount == 0;};
    int getHeight() const;
    int getNumberOfNodes() const{ return itemCount; };
    int getNumberOfLeafNodes() const;
    ItemType peekTop() const;
    bool add(const ItemType& newData);
    bool remove();
    void clear(){ itemCount = 0; };
    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;
};

template<class ItemType>
int ArrayMinHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const{
    return (2 * nodeIndex) + 1;
}

template<class ItemType>
int ArrayMinHeap<ItemType>::getRightChildIndex(const int nodeIndex) const{
    return (2 * nodeIndex) + 2;
}

template<class ItemType>
int ArrayMinHeap<ItemType>::getParentIndex(const int nodeIndex) const{
    if(nodeIndex != 0)
        return (nodeIndex - 1) / 2;
    else
        return 0;
}

template<class ItemType>
bool ArrayMinHeap<ItemType>::isLeaf(int nodeIndex) const{
    if(getLeftChildIndex(nodeIndex) > itemCount - 1)
        return true;
    return false;
}

template<class ItemType>
void ArrayMinHeap<ItemType>::heapRebuild(int subTreeRootIndex){
    if(!isLeaf(subTreeRootIndex)){
        int smallerChildIndex = getLeftChildIndex(subTreeRootIndex);
        if(getRightChildIndex(subTreeRootIndex) < itemCount){
            int rightChildIndex  = smallerChildIndex + 1;
            if(items[rightChildIndex] < items[smallerChildIndex])
                smallerChildIndex = rightChildIndex;
        }
        if(items[smallerChildIndex] < items[subTreeRootIndex]){
            ItemType temp = items[subTreeRootIndex];
            items[subTreeRootIndex] = items[smallerChildIndex];
            items[smallerChildIndex] = temp;
            heapRebuild(smallerChildIndex);
        }
    }
}

template<class ItemType>
void ArrayMinHeap<ItemType>::heapCreate(){
   for (int index = itemCount / 2; index >= 0; index--){
      heapRebuild(index);
   }
}

template<class ItemType>
void ArrayMinHeap<ItemType>::preorder(void visit(ItemType&), int subTreeRootIndex) const{
    if (subTreeRootIndex < itemCount){
        visit(items[subTreeRootIndex]);
        preorder(visit, getLeftChildIndex(subTreeRootIndex));
        preorder(visit, getRightChildIndex(subTreeRootIndex));
    }
}

template<class ItemType>
void ArrayMinHeap<ItemType>::inorder(void visit(ItemType&), int subTreeRootIndex) const{
    if (subTreeRootIndex < itemCount){
        inorder(visit, getLeftChildIndex(subTreeRootIndex));
        visit(items[subTreeRootIndex]);
        inorder(visit, getRightChildIndex(subTreeRootIndex));
    }
}

template<class ItemType>
void ArrayMinHeap<ItemType>::postorder(void visit(ItemType&), int subTreeRootIndex) const{
    if (subTreeRootIndex < itemCount){
        postorder(visit, getLeftChildIndex(subTreeRootIndex));
        postorder(visit, getRightChildIndex(subTreeRootIndex));
        visit(items[subTreeRootIndex]);
    }
}

template<class ItemType>
ArrayMinHeap<ItemType>::ArrayMinHeap(const ItemType someArray[], const int arraySize):itemCount(arraySize){
   // Allocate the array
   items = new ItemType[2 * arraySize];
   
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   
   // Reorganize the array into a heap
   heapCreate();
}

template<class ItemType>
bool ArrayMinHeap<ItemType>::add(const ItemType& newData){
    items[itemCount] = newData;
    
    ItemType newDataIndex = itemCount;
    bool inPlace = false;
    
    while (!inPlace && newDataIndex > 0) {
        int parentIndex = getParentIndex(newDataIndex);
        if(items[newDataIndex] >= items[parentIndex])
            inPlace = true;
        else{
            ItemType temp = items[newDataIndex];
            items[newDataIndex] = items[parentIndex];
            items[parentIndex] = temp;
            newDataIndex = parentIndex;
        }
    }
    itemCount++;
    
    return inPlace;
}

template<class ItemType>
int ArrayMinHeap<ItemType>::getHeight() const{
    int height = pow(itemCount + 1, 0.5);
    if(pow(2, height) - 1 != itemCount)
        height++;
    return height;
}

template<class ItemType>
int ArrayMinHeap<ItemType>::getNumberOfLeafNodes() const{
    int numOfLeafNodes = 0;
    for(int i = 0; i < itemCount; i++){
        if(isLeaf(i))
            numOfLeafNodes++;
    }
    return numOfLeafNodes;
}

template<class ItemType>
ItemType ArrayMinHeap<ItemType>::peekTop() const{
   return items[0];
}

template<class ItemType>
bool ArrayMinHeap<ItemType>::remove(){
    if(itemCount == 0)
        return false;

    items[0] = items[itemCount - 1];
    itemCount--;
    heapRebuild(0);

    return true;
}

template<class ItemType>
void ArrayMinHeap<ItemType>::preorderTraverse(void visit(ItemType&)) const{
    preorder(visit, 0);
}

template<class ItemType>
void ArrayMinHeap<ItemType>::inorderTraverse(void visit(ItemType&)) const{
    inorder(visit, 0);
    
}

template<class ItemType>
void ArrayMinHeap<ItemType>::postorderTraverse(void visit(ItemType&)) const{
    postorder(visit, 0);
}

//void visit(int& item);

template<class T>
void display(ArrayMinHeap<T>& heap);

int main(){
    
    vector<int> input;
    int n = 0;
    while (cin >> n) {
        input.push_back(n);
    }
    
    //vector<int> input = {1,1,1,2,2};
    
    ArrayMinHeap<int> heap;
    for(int i = 0; i < input.size(); i++){
        heap.add(input[i]);
    }
    display(heap);
    
    int removeNum = int(input.size())/2;
    cout << "** after removing " << removeNum << " nodes **\n";
    for(int i = 0 ; i < removeNum; i++){
        heap.remove();
    }
    display(heap);
    
}

void visit(int& item){
    cout << " " << item;
}

template<class T>
void display(ArrayMinHeap<T>& heap){
    cout << "Preorder:";
    heap.preorderTraverse(visit);
    cout << "\n";
    cout << "Inorder:";
    heap.inorderTraverse(visit);
    cout << "\n";
    cout << "Postorder:";
    heap.postorderTraverse(visit);
    cout << "\n";
    cout << "Number of nodes: " << heap.getNumberOfNodes() << "\n";
    cout << "Number of leaf nodes: " << heap.getNumberOfLeafNodes() << "\n";
    cout << "Height: " << heap.getHeight() << "\n";
}
