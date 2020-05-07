#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class PrecondViolatedExcep : public logic_error{
public:
   PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep

PrecondViolatedExcep::PrecondViolatedExcep(const string& message): logic_error("Precondition Violated Exception: " + message){
}

template<class ItemType>
class SortedListInterface{
public:
   /** Inserts an entry into this sorted list in its proper order
       so that the list remains sorted.
    @pre  None.
    @post  newEntry is in the list, and the list is sorted.
    @param newEntry  The entry to insert into the sorted list. */
   virtual void insertSorted(const ItemType& newEntry) = 0;
   
   /** Removes the first or only occurrence of the given entry from this
       sorted list.
    @pre  None.
    @post  If the removal is successful, the first occurrence of the
       given entry is no longer in the sorted list, and the returned
       value is true. Otherwise, the sorted list is unchanged and the
       returned value is false.
    @param anEntry  The entry to remove.
    @return  True if removal is successful, or false if not. */
   virtual bool removeSorted(const ItemType& anEntry) = 0;
   
   /** Gets the position of the first or only occurrence of the given
       entry in this sorted list. In case the entry is not in the list,
       determines where it should be if it were added to the list.
    @pre  None.
    @post  The position where the given entry is or belongs is returned.
       The sorted list is unchanged.
    @param anEntry  The entry to locate.
    @return  Either the position of the given entry, if it occurs in the
       sorted list, or the position where the entry would occur, but as a
       negative integer. */
   virtual int getPosition(const ItemType& anEntry) = 0;
   
   // The following methods are the same as those given in ListInterface
   // in Listing 8-1 of Chapter 8 and are completely specified there.
   
   /** Sees whether this list is empty. */
   virtual bool isEmpty() const = 0;
   
   /** Gets the current number of entries in this list. */
   virtual int getLength() const = 0;
   
   /** Removes the entry at a given position from this list. */
   virtual bool remove(int position) = 0;
   
   /** Removes all entries from this list. */
   virtual void clear() = 0;
   
   /** Gets the entry at the given position in this list. */
   virtual ItemType getEntry(int position) const = 0;
}; // end SortedListInterface

template<class ItemType>
class Node{
private:
  ItemType item;
  Node<ItemType>* next;
public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
  void setItem(const ItemType& anItem);
  void setNext(Node<ItemType>* nextNodePtr);
  ItemType getItem() const ;
  Node<ItemType>* getNext() const ;
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr){
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr){
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
                item(anItem), next(nextNodePtr){
}

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem){
  item = anItem;
}

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr){
  next = nextNodePtr;
}

template<class ItemType>
ItemType Node<ItemType>::getItem() const{
  return item;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const{
  return next;
}


template<class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>{
private:
   Node<ItemType>* headPtr; // Pointer to first node in the chain
   int itemCount;           // Current count of list items
   
   // Locates the node that is before the node that should or does
   // contain the given entry.
   // @param anEntry  The entry to find.
   // @return  Either a pointer to the node before the node that contains
   //    or should contain the given entry, or nullptr if no prior node exists.
   Node<ItemType>* getNodeBefore(const ItemType& anEntry) const;
   
   // Locates the node at a given position within the chain.
   Node<ItemType>* getNodeAt(int position) const;
   
   // Returns a pointer to a copy of the chain to which origChainPtr points.
   Node<ItemType>* copyChain(const Node<ItemType>* origChainPtr);
   
public:
   LinkedSortedList();
   LinkedSortedList(const LinkedSortedList<ItemType>& aList);
   virtual ~LinkedSortedList();

   void insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& newEntry) const;
   
   // The following methods are the same as given in ListInterface:
   bool isEmpty() const;
   int getLength() const;
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);
}; // end LinkedSortedList

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList){
    headPtr = copyChain(aList.headPtr);
}  // end copy constructor

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList(){
   clear();
}  // end destructor

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const{
   return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove){
      Node<ItemType>* curPtr = nullptr;
      if (position == 1){
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
      }
      else{
         // Find node that is before the one to delete
         Node<ItemType>* prevPtr = getNodeAt(position - 1);
         
         // Point to node to delete
         curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  // end if
      
      // Return node to system
      curPtr->setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}  // end remove

template<class ItemType>
void LinkedSortedList<ItemType>::clear(){
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep){
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet){
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else{
      string message = "getEntry() called with an empty list or invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end getEntry

template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry){
   Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
   Node<ItemType>* prevPtr = getNodeBefore(newEntry);
   
   if (isEmpty() || (prevPtr == nullptr)){ // Add at beginning
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
   }
   else{ // Add after node before
      Node<ItemType>* aftPtr = prevPtr->getNext();
      newNodePtr->setNext(aftPtr);
      prevPtr->setNext(newNodePtr);
   } // end if
   
   itemCount++;
} // end insertSorted

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& newEntry){
    //??
    return false;
}


template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(const Node<ItemType>* origChainPtr){
    Node<ItemType>* copiedChainPtr;
    if (origChainPtr == nullptr){
        copiedChainPtr = nullptr;
        itemCount = 0;
    }
    else{
        // Build new chain from given one
        copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
        copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
        itemCount++;
    }  // end if
   
    return copiedChainPtr;
}  // end copyChain

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const{
   Node<ItemType>* curPtr = headPtr;
   Node<ItemType>* prevPtr = nullptr;
   
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem())){
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
   } // end while
   
   return prevPtr;
} // end getNodeBefore

int main(){
    
}  // end main




