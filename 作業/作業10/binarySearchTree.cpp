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


/////////////////////////
///BinaryTreeInterface///
/////////////////////////

template<class ItemType>
class BinaryTreeInterface{
public:
    /** Tests whether this binary tree is empty.
      @return True if the binary tree is empty, or false if not. */
     virtual bool isEmpty() const = 0;
    
     /** Gets the height of this binary tree.
      @return The height of the binary tree. */
     virtual int getHeight() const = 0;
    
     /** Gets the number of nodes in this binary tree.
      @return The number of nodes in the binary tree. */
     virtual int getNumberOfNodes() const = 0;
    
     /** Gets the data that is in the root of this binary tree.
      @pre  The binary tree is not empty.
      @post  The root’s data has been returned, and the binary tree is unchanged.
      @return  The data in the root of the binary tree. */
     virtual ItemType getRootData() const = 0;
    
     /** Replaces the data item in the root of this binary tree with the given data, if the tree is not empty. However, if the tree is empty, inserts a new root node containing the given data into the tree.
      @pre  None.
      @post  The data in the root of the binary tree is as given.
      @param newData  The data for the root. */
     //virtual void setRootData(const ItemType& newData) = 0;
    
     /** Adds a new node containing the given data to this binary tree.
      @param newData  The data for the new node.
      @post  The binary tree contains a new node.
      @return  True if the addition is successful, or false not. */
     virtual bool add(const ItemType& newData) = 0;
    
     /** Removes the node containing the given data item from this binary tree.
      @param data  The data value to remove from the binary tree.
      @return  True if the removal is successful, or false not. */
     virtual bool remove(const ItemType& data) = 0;
    
     /** Removes all nodes from this binary tree. */
     virtual void clear() = 0;
    
     /** Gets a specific entry in this binary tree.
      @post  The desired entry has been returned, and the binary tree is unchanged. If no such entry was found, an exception is thrown.
      @param anEntry  The entry to locate.
      @return  The entry in the binary tree that matches the given entry.
      @throw  NotFoundException if the given entry is not in the tree. */
     //virtual ItemType getEntry(const ItemType& anEntry) const throw(exception) = 0;
    
     /** Tests whether a given entry occurs in this binary tree.
      @post  The binary search tree is unchanged.
      @param anEntry  The entry to find.
      @return  True if the entry occurs in the tree, or false if not. */
     //virtual bool contains(const ItemType& anEntry) const = 0;
    
     /** Traverses this binary tree in preorder (inorder, postorder) and calls the function visit once for each node.
      @param visit A client-defined function that performs an operation on or with the data in each visited node. */
     virtual void preorderTraverse(void visit(ItemType&)) const = 0;
     virtual void inorderTraverse(void visit(ItemType&)) const = 0;
     virtual void postorderTraverse(void visit(ItemType&)) const = 0;
}; 


//////////////////////
///BinarySearchTree///
//////////////////////

template<class ItemType>
class BinarySearchTree: public BinaryTreeInterface<ItemType>{
private:
    BinaryNode<ItemType>* rootPtr;
    
protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr);
    int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
    int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;
    void getNumberOfLeafNodesHelper(BinaryNode<ItemType>* subTreePtr, int& leafCont) const;
    void preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void destroyTree(BinaryNode<ItemType>* subTreePtr);
    
    // Removes the given target value from the tree while maintaining a binary search tree.
    BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success);
    
    // Removes a given node from a tree while maintaining a binary search tree.
    BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);
    
    // Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
    // Sets inorderSuccessor to the value in this node.
    // Returns a pointer to the revised subtree.
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor);
    
    // Returns a pointer to the node containing the given value,or nullptr if not found.
    //BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const;
    
public:
    BinarySearchTree();
    BinarySearchTree(const ItemType& rootItem);
    BinarySearchTree(const BinarySearchTree<ItemType>& tree);
    virtual ~BinarySearchTree();
    

    bool isEmpty() const { return rootPtr == nullptr; };
    int getHeight() const;
    int getNumberOfNodes() const;
    int getNumberOfLeafNodes() const;
    ItemType getRootData() const;
    //void setRootData(const ItemType& newData);
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& data);
    virtual void clear() { destroyTree(rootPtr); };
    //ItemType getEntry(const ItemType& anEntry) const throw(exception);
    //bool contains(const ItemType& anEntry) const;
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
void BinarySearchTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr){
    if (subTreePtr != nullptr){
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success){
    if(subTreePtr == nullptr){
        success = false;
        return nullptr;
    }
    else if(subTreePtr->getItem() == target){
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else if(subTreePtr->getItem() > target){
        BinaryNode<ItemType>* tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
    else{
        BinaryNode<ItemType>* tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
        return subTreePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr){
    if(nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() == nullptr){
        delete nodePtr;
        nodePtr = nullptr;
        return nodePtr;
    }
    else if(nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() == nullptr){
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else if(nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr){
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else{
        ItemType inorderSuccessor;
        BinaryNode<ItemType>* tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), inorderSuccessor);
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(inorderSuccessor);
        return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor){
    if(subTreePtr->getLeftChildPtr() == nullptr){
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else{
        BinaryNode<ItemType>* tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
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
    destroyTree(rootPtr);

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
ItemType BinarySearchTree<ItemType>::getRootData() const{
    return rootPtr->getItem();
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData){
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& data){
    bool success = false;
    rootPtr = removeValue(rootPtr, data, success);
    return success;
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
    /*
    vector<int> input;
    int n = 0;
    while (cin >> n) {
        input.push_back(n);
    }
    */
    
    vector<int> input = {1,3,5,2,4,6};
    
    BinarySearchTree<int> tree;
    for(int i = 0; i < input.size(); i++){
        tree.add(input[i]);
    }
    display(tree);
    
    int removeNum = int(input.size())/2;
    cout << "** after removing " << removeNum << " nodes **\n";
    BinarySearchTree<int> tree2;
    for(int i = 0 ; i < removeNum; i++){
        tree.remove(input[i]);
    }
    display(tree);
    
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
