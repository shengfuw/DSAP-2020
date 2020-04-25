#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

template<typename ItemType>
class BagInterface
{
public:
  virtual int getCurrentSize() const = 0;
  virtual bool isEmpty() const = 0;
  virtual bool add(const ItemType& newEntry) = 0;
  virtual bool remove(const ItemType& anEntry) = 0;
  virtual void clear() = 0;
  virtual int getFrequencyOf(const ItemType& anEntry) const = 0;
  virtual bool contains(const ItemType& anEntry) const = 0;
  virtual vector<ItemType> toVector() const = 0;
  virtual void removeAll(const ItemType& anEntry) = 0;
  virtual int getTypeCount() = 0;
};









template<class ItemType>
class Node
{
private:
  ItemType item;
  Node<ItemType>* next;
public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
  void setItem(const ItemType& anItem);
  void setNext(Node<ItemType>* nextNodePtr);
  ItemType getItem() const;
  Node<ItemType>* getNext() const;
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
                item(anItem), next(nextNodePtr)
{
}

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
}

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
  next = nextNodePtr;
}

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
  return item;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
  return next;
}









template<class ItemType>
class LinkedBag : public BagInterface<ItemType>
{
private:
  Node<ItemType>* headPtr; // Pointer to first node
  int itemCount;           // Current count of bag items
   
  // Returns either a pointer to the node containing a given entry
  // or the null pointer if the entry is not in the bag.
  Node<ItemType>* getPointerTo(const ItemType& target) const;
public:
  LinkedBag();
  LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
  virtual ~LinkedBag();                       // Destructor should be virtual
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const ItemType& newEntry);
  bool remove(const ItemType& anEntry);
  void clear();
  bool contains(const ItemType& anEntry) const;
  int getFrequencyOf(const ItemType& anEntry) const;
  vector<ItemType> toVector() const;
  void removeAll(const ItemType& anEntry);
  int getTypeCount();
};

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
  itemCount = aBag->itemCount;
  Node<ItemType>* origChainPtr = aBag->headPtr; // Points to nodes in original chain
   
  if(origChainPtr == nullptr)
    headPtr = nullptr;  // Original bag is empty; so is copy
  else
  {
    // Copy first node
    headPtr = new Node<ItemType>();
    headPtr->setItem(origChainPtr->getItem());
     
    // Copy remaining nodes
    Node<ItemType>* newChainPtr = headPtr; // Last-node pointer
    while(origChainPtr != nullptr)
    {
      origChainPtr = origChainPtr->getNext(); // Advance pointer
        
      // Get next item from original chain
      ItemType nextItem = origChainPtr->getItem();
         
      // Create a new node containing the next item
      Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
      // Link new node to end of new chain
      newChainPtr->setNext(newNodePtr);
         
      // Advance pointer to new last node
      newChainPtr = newChainPtr->getNext();
    }
      
    newChainPtr->setNext(nullptr); // Flag end of new chain
  }
}

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
  clear();
}

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
  return itemCount == 0;
}

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
  return itemCount;
}

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
  // Add to beginning of chain: new node references rest of chain;
  // (headPtr is null if chain is empty)
  Node<ItemType>* newNodePtr = new Node<ItemType>();
  newNodePtr->setItem(newEntry);
  newNodePtr->setNext(headPtr);  // New node points to chain

  headPtr = newNodePtr;          // New node is now first node
  itemCount++;
   
  return true;
}

template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
  vector<ItemType> bagContents;
  Node<ItemType>* curPtr = headPtr;
  while ((curPtr != nullptr))
  {
    bagContents.push_back(curPtr->getItem());
    curPtr = curPtr->getNext();
  }
  return bagContents;
}

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
  Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
  bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
  if (canRemoveItem)
  {
    // Copy data from first node to located node
    entryNodePtr->setItem(headPtr->getItem());
     
    // Delete first node
    Node<ItemType>* nodeToDeletePtr = headPtr;
    headPtr = headPtr->getNext();
     
    // Releasing the space to the system
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;
     
    itemCount--;
  }

  return canRemoveItem;
}

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
  Node<ItemType>* nodeToDeletePtr = headPtr;
  while (headPtr != nullptr)
  {
    headPtr = headPtr->getNext();
    
    // Releasing the space to the system
    nodeToDeletePtr->setNext(nullptr);
    delete nodeToDeletePtr;
     
    nodeToDeletePtr = headPtr;
  }
  // headPtr is nullptr; nodeToDeletePtr is nullptr
  
  itemCount = 0;
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
  int frequency = 0;
  Node<ItemType>* curPtr = headPtr;
  while(curPtr != nullptr)
  {
    if(anEntry == curPtr->getItem())
      frequency++;
    curPtr = curPtr->getNext();
  }
   
  return frequency;
}

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
  return (getPointerTo(anEntry) != nullptr);
}

// private
// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
  bool found = false;
  Node<ItemType>* curPtr = headPtr;
   
  while (!found && (curPtr != nullptr))
  {
    if (anEntry == curPtr->getItem())
      found = true;
    else
      curPtr = curPtr->getNext();
  }
   
  return curPtr;
}

template<class ItemType>
void LinkedBag<ItemType>::removeAll(const ItemType& anEntry)
{
  Node<ItemType>* cur = this->headPtr;
  while(cur != nullptr)
  {
    if(cur->getItem() == anEntry)
    {
      // Copy data from first node to located node
      cur->setItem(headPtr->getItem());
       
      // Delete first node
      Node<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();
       
      // Releasing the space to the system
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
       
      itemCount--;
      cur = headPtr;
    }
    else
      cur = cur->getNext();
  }
}

template<class ItemType>
int LinkedBag<ItemType>::getTypeCount()
{
// for each item in bag
//   if this item is "new"
//     add it into another bag
//     counter++
// return counter

// create an empty local bag A
// counter = 0
// for each item in this bag
//   if this item is "new", i.e., it is not in A
//     add it into A
//     counter++
// return counter

  LinkedBag<ItemType> b;
  
  Node<ItemType>* cur = headPtr;
  while(cur != nullptr)
  {
    if(b.contains(cur->getItem()) == false)
      b.add(cur->getItem());
    cur = cur->getNext();
  }
  
  return b.itemCount;
}










void displayBag(BagInterface<string>* bagPtr)
{
  cout << "The bag contains " << bagPtr->getCurrentSize()
       << " items:" << endl;
  vector<string> bagItems = bagPtr->toVector();
   
  int numberOfEntries = (int)bagItems.size();
  for(int i = 0; i < numberOfEntries; i++)
    cout << bagItems[i] << " ";
  cout << endl << endl;
}

void bagTester(BagInterface<string>* bagPtr)
{
  displayBag(bagPtr);

  string items[] = {"one", "two", "three", "one", "five", "one"};
  cout << "Add 6 items to the bag: " << endl;
  for (int i = 0; i < 6; i++)
  {
    bagPtr->add(items[i]);
  }
  displayBag(bagPtr);
  cout << "type count: " << bagPtr->getTypeCount() << endl;
  
  bagPtr->removeAll("one");
  displayBag(bagPtr);
  cout << "type count: " << bagPtr->getTypeCount() << endl;
}











int main()
{
  LinkedBag<string>* bagPtr = new LinkedBag<string>();
  
  cout << "The initial bag is empty." << endl;
  bagTester(bagPtr);
  delete bagPtr;
  bagPtr = nullptr;
  cout << "All done!" << endl;
   
  return 0;
}

 
