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
    
    /** Replaces the data item in the root of this binary tree
        with the given data, if the tree is not empty. However, if
        the tree is empty, inserts a new root node containing the
        given data into the tree.
     @pre  None.
     @post  The data in the root of the binary tree is as given.
     @param newData  The data for the root. */
    virtual void setRootData(const ItemType& newData) = 0;
   
    /** Adds a new node containing the given data to this binary tree.
     @param newData  The data for the new node.
     @post  The binary tree contains a new node.
     @return  True if the addition is successful, or false not. */
    virtual bool add(const ItemType& newData) = 0;
   
    /** Removes the node containing the given data item from this binary tree.
     @param data  The data value to remove from the binary tree.
     @return  True if the removal is successful, or false not. */
    //virtual bool remove(const ItemType& data) = 0;
   
    /** Removes all nodes from this binary tree. */
    //virtual void clear() = 0;
   
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

////////////////
///BinaryTree///
////////////////

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>{
private:
    BinaryNode<ItemType>* rootPtr;
protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
    int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;
    
    // Recursively deletes all nodes from the tree.
    void destroyTree(BinaryNode<ItemType>* subTreePtr);
    
    // Recursively adds a new node to the tree in a left/right fashion to keep the tree balanced.
    BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr);
   
    // Removes the target value from the tree by calling moveValuesUpTree to overwrite value with value from child.
    //BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success);
   
    // Copies values up the tree to overwrite value in current node until a leaf is reached; the leaf is then removed, since its value is stored in the parent.
    //BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);
   
    // Recursively searches for target value in the tree by using a preorder traversal.
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target, bool& success) const;
   
    // Copies the tree rooted at treePtr and returns a pointer to the copy.
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;
   
    // Recursive traversal helper methods:
    void preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
   
public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
    BinaryNodeTree();
    BinaryNodeTree(const ItemType& rootItem);
    BinaryNodeTree(const ItemType& rootItem, const BinaryNodeTree<ItemType>* leftTreePtr, const BinaryNodeTree<ItemType>* rightTreePtr);
    BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
    virtual ~BinaryNodeTree();
    
    //------------------------------------------------------------
    // Public BinaryTreeInterface Methods Section.
    //------------------------------------------------------------
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    ItemType getRootData() const throw(exception);
    void setRootData(const ItemType& newData);
    bool add(const ItemType& newData); // Adds a node
    //bool remove(const ItemType& data); // Removes a node
    //void clear();
    //ItemType getEntry(const ItemType& anEntry) const throw(exception);
    //bool contains(const ItemType& anEntry) const;
   
    //------------------------------------------------------------
    // Public Traversals Section.
    //------------------------------------------------------------
    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;
   
    //------------------------------------------------------------
    // Overloaded Operator Section.
    //------------------------------------------------------------
    BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
};

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const{
    if(subTreePtr == nullptr)
        return 0;
    else
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const{
    if(subTreePtr == nullptr)
        return 1;
    else
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr){
    if (subTreePtr != nullptr){
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr){
    if (subTreePtr == nullptr)
        return newNodePtr;
    else{
        BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
        BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();
        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){
            rightPtr = balancedAdd(rightPtr , newNodePtr);
            subTreePtr->setRightChildPtr(rightPtr);
       }
       else{
           leftPtr = balancedAdd(leftPtr, newNodePtr);
           subTreePtr->setLeftChildPtr(leftPtr);
       }
       return subTreePtr;
    }
}

/*
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success){
    
}
*/

/*
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target, bool& success) const{
    
}
*/

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const{
    
    BinaryNode<ItemType>* newTreePtr = nullptr;
    
    // Copy tree nodes during a preorder traversal
    if (treePtr != nullptr){
        // Copy node
        newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    }

    return newTreePtr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const{
    if (treePtr != nullptr){
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const{
    if (treePtr != nullptr){
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
    
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const{
    if (treePtr != nullptr){
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
    }
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree():rootPtr(nullptr) { };

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem){
    rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem, const BinaryNodeTree<ItemType>* leftTreePtr, const BinaryNodeTree<ItemType>* rightTreePtr){
    rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr), copyTree(rightTreePtr));
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& tree){
    rootPtr = copyTree(tree.rootPtr);
}

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree(){
    //destroyTree(rootPtr);
    //???
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const{
    return rootPtr == nullptr;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const{
    return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const{
    return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(exception){
    return rootPtr->getItem();
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData){
    rootPtr->setItem(newData);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData){
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = balancedAdd(rootPtr, newNodePtr);
    return true;
}

/*
template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data){
    
}
*/

/*
template<class ItemType>
void BinaryNodeTree<ItemType>::clear(){
    destroyTree(rootPtr);
}
*/

/*
template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(exception){
    
}
*/

/*
template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const{
    
}
*/

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const{
    preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const{
    inorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const{
    postorder(visit, rootPtr);
}


/*
template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree& rightHandSide){
}
*/

void visit(int& item);

int main(){
    
    BinaryNodeTree<int> tree;
    
    vector<int> input = {1,3,5,2,4,6};
    for(int i = 0; i < input.size(); i++){
        tree.add(input[i]);
    }
    
    cout << "Preorder:";
    tree.preorderTraverse(visit);
    cout << "\n";
    cout << "Inorder:";
    tree.inorderTraverse(visit);
    cout << "\n";
    cout << "Postorder:";
    tree.postorderTraverse(visit);
    cout << "\n";
}

void visit(int& item){
    cout << " " << item;
}
