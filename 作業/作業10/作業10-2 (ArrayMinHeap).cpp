#include <iostream>
#include <cmath>
#include <vector>
using namespace::std;

void visit(int& item);

template<class ItemType>
class ArrayMinHeap{
private:
    static const int ROOT_INDEX = 0;
    static const int DEFAULT_CAPACITY = 100000;
    ItemType* items;
    int itemCount;
    
    int getLeftChildIndex(const int nodeIndex) const;
    int getRightChildIndex(const int nodeIndex) const;
    int getParentIndex(const int nodeIndex) const;
    bool isLeaf(int nodeIndex) const;
    void heapRebuild(int subTreeRootIndex);
    void heapCreate();
    
    void preorder(void visit(ItemType&), int subTreeRootIndex) const;
    void inorder(void visit(ItemType&), int subTreeRootIndex) const;
    void postorder(void visit(ItemType&), int subTreeRootIndex) const;
    
public:
    ArrayMinHeap(): itemCount(0) { items = new ItemType[DEFAULT_CAPACITY]; };
    ArrayMinHeap(const ItemType someArray[], const int arraySize);
    virtual ~ArrayMinHeap(){ delete [] items; };
    
    int getHeight() const;
    int getNumberOfNodes() const { return itemCount; };
    int getNumberOfLeafNodes() const;
    bool add(const ItemType& newData);
    bool removeRoot();
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
    return getLeftChildIndex(nodeIndex) > (itemCount - 1);
}

template<class ItemType>
void ArrayMinHeap<ItemType>::heapRebuild(int subTreeRootIndex){
    if(!isLeaf(subTreeRootIndex)){
        int smallerChildIndex = getLeftChildIndex(subTreeRootIndex);;
        
        if(getRightChildIndex(subTreeRootIndex) < itemCount){
            int rightChildIndex  = smallerChildIndex + 1;
            if(items[rightChildIndex] < items[smallerChildIndex]) // < or <= ?
                smallerChildIndex = rightChildIndex;
        }
        if(items[smallerChildIndex] < items[subTreeRootIndex]){ // < or <= ?
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
ArrayMinHeap<ItemType>::ArrayMinHeap(const ItemType someArray[], const int arraySize): itemCount(arraySize){
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
        if(items[parentIndex] <= items[newDataIndex])
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
bool ArrayMinHeap<ItemType>::removeRoot(){
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

template<class T>
void display(ArrayMinHeap<T>& heap);

int main(){
    
    /*
    vector<int> input;
    int n = 0;
    while (cin >> n) {
        input.push_back(n);
    }
    */
    
    vector<int> input = {6,9,7,10,3,2,1,5,8,4};
    
    ArrayMinHeap<int> heap;
    for(int i = 0; i < input.size(); i++){
        heap.add(input[i]);
    }
    display(heap);
    
    int removeNum = int(input.size())/2;
    for(int i = 0 ; i < removeNum; i++){
        heap.removeRoot();
    }
    cout << "** after removing " << removeNum << " nodes **\n";
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
