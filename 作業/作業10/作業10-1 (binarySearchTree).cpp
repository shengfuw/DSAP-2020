#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

////////////////
///BinaryNode///
////////////////

template<class ItemType>
class BinaryNode{
private:
    ItemType item;
    BinaryNode<ItemType>* leftChildPtr;
    BinaryNode<ItemType>* rightChildPtr;

public:
    BinaryNode();
    BinaryNode(const ItemType& anItem);
    BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr);
    void setItem(const ItemType& anItem);
    ItemType getItem() const;
    bool isLeaf() const;
    BinaryNode<ItemType>* getLeftChildPtr() const;
    BinaryNode<ItemType>* getRightChildPtr() const;
    void setLeftChildPtr(BinaryNode<ItemType>* leftPtr);
    void setRightChildPtr(BinaryNode<ItemType>* rightPtr);
};

template<class ItemType>
BinaryNode<ItemType>::BinaryNode():leftChildPtr(nullptr), rightChildPtr(nullptr) { };

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem):leftChildPtr(nullptr), rightChildPtr(nullptr){
    this->item = anItem;
}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr):leftChildPtr(leftPtr), rightChildPtr(rightPtr){
    this->item = anItem;
}

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem){
    item = anItem;
}

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const{
    return item;
}

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const{
    return (leftChildPtr == nullptr && rightChildPtr == nullptr);
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNode<ItemType>::getLeftChildPtr() const{
    return leftChildPtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNode<ItemType>::getRightChildPtr() const{
    return rightChildPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType>* leftPtr){
    leftChildPtr = leftPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType>* rightPtr){
    rightChildPtr = rightPtr;
}


//////////////////////
///BinarySearchTree///
//////////////////////

template<class ItemType>
class BinarySearchTree{
private:
    BinaryNode<ItemType>* rootPtr;
    
protected:
    BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr);
    int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
    int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;
    void getNumberOfLeafNodesHelper(BinaryNode<ItemType>* subTreePtr, int& leafCont) const;
    void preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    
public:
    BinarySearchTree();
    BinarySearchTree(const ItemType& rootItem);
    BinarySearchTree(const BinarySearchTree<ItemType>& tree);
    virtual ~BinarySearchTree();
    int getHeight() const;
    int getNumberOfNodes() const;
    int getNumberOfLeafNodes() const;
    bool add(const ItemType& newEntry);
    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;
};

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr){
    if(subTreePtr == nullptr)
        return newNodePtr;
    else if(subTreePtr->getItem() > newNodePtr->getItem()) {
        BinaryNode<ItemType>* tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr); subTreePtr->setLeftChildPtr(tempPtr);
    }
    else {
        BinaryNode<ItemType>* tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr); subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const{
    if(subTreePtr == nullptr)
        return 0;
    else
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const{
    if(subTreePtr == nullptr)
        return 0;
    else
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}

template<class ItemType>
void BinarySearchTree<ItemType>::getNumberOfLeafNodesHelper(BinaryNode<ItemType>* subTreePtr, int& leafCount) const{
    if(subTreePtr != nullptr){
        if((subTreePtr->getLeftChildPtr() == nullptr &&  subTreePtr->getRightChildPtr() == nullptr)){
            leafCount++;
        }
        getNumberOfLeafNodesHelper(subTreePtr->getLeftChildPtr(), leafCount);
        getNumberOfLeafNodesHelper(subTreePtr->getRightChildPtr(), leafCount);
    }
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const{
    if (treePtr != nullptr){
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const{
    if (treePtr != nullptr){
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
    
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const{
    if (treePtr != nullptr){
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    }
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree():rootPtr(nullptr) { };

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem){
    rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree){
    rootPtr = copyTree(tree.rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree(){
    //destroyTree(rootPtr);

}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const{
    return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const{
    return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfLeafNodes() const{
    int count = 0;
    getNumberOfLeafNodesHelper(rootPtr, count);
    return count;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData){
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const{
    preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const{
    inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const{
    postorder(visit, rootPtr);
}

void visit(int& item);

template<class T>
void display(BinarySearchTree<T>& tree);

int main(){
    vector<int> input;
    int n = 0;
    while (cin >> n) {
        input.push_back(n);
    }
    
    //vector<int> input = {1,3,5,2,4,6};
    
    BinarySearchTree<int> tree1;
    for(int i = 0; i < input.size(); i++){
        tree1.add(input[i]);
    }
    display(tree1);
    
    int removeNum = int(input.size())/2;
    cout << "** after removing " << removeNum << " nodes **\n";
    BinarySearchTree<int> tree2;
    for(int i = removeNum ; i < input.size(); i++){
        tree2.add(input[i]);
    }
    display(tree2);
    
}

void visit(int& item){
    cout << " " << item;
}

template<class T>
void display(BinarySearchTree<T>& tree){
    cout << "Preorder:";
    tree.preorderTraverse(visit);
    cout << "\n";
    cout << "Inorder:";
    tree.inorderTraverse(visit);
    cout << "\n";
    cout << "Postorder:";
    tree.postorderTraverse(visit);
    cout << "\n";
    cout << "Number of nodes: " << tree.getNumberOfNodes() << "\n";
    cout << "Number of leaf nodes: " << tree.getNumberOfLeafNodes() << "\n";
    cout << "Height: " << tree.getHeight() << "\n";
}
