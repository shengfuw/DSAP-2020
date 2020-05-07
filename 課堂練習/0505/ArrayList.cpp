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
class ListInterface{
public:
   /** Sees whether this list is empty.
    @return True if the list is empty; otherwise returns false. */
   virtual bool isEmpty() const = 0;
   
   /** Gets the current number of entries in this list.
    @return The integer number of entries currently in the list. */
   virtual int getLength() const = 0;
   
   /** Inserts an entry into this list at a given position.
    @pre  None.
    @post  If 1 <= position <= getLength() + 1 and the insertion is
       successful, newEntry is at the given position in the list,
       other entries are renumbered accordingly, and the returned
       value is true.
    @param newPosition  The list position at which to insert newEntry.
    @param newEntry  The entry to insert into the list.
    @return  True if insertion is successful, or false if not. */
   virtual bool insert(int newPosition, const ItemType& newEntry) = 0;
   
   /** Removes the entry at a given position from this list.
    @pre  None.
    @post  If 1 <= position <= getLength() and the removal is successful,
       the entry at the given position in the list is removed, other
       items are renumbered accordingly, and the returned value is true.
    @param position  The list position of the entry to remove.
    @return  True if removal is successful, or false if not. */
   virtual bool remove(int position) = 0;
   
   /** Removes all entries from this list.
    @post  List contains no entries and the count of items is 0. */
   virtual void clear() = 0;
   
   /** Gets the entry at the given position in this list.
    @pre  1 <= position <= getLength().
    @post  The desired entry has been returned.
    @param position  The list position of the desired entry.
    @return  The entry at the given position. */
   virtual ItemType getEntry(int position) const = 0;
   
   /** Replaces the entry at the given position in this list.
    @pre  1 <= position <= getLength().
    @post  The entry at the given position is newEntry.
    @param position  The list position of the entry to replace.
    @param newEntry  The replacement entry. */
   virtual void setEntry(int position, const ItemType& newEntry) = 0;
}; // end ListInterface

template<class ItemType>
class ArrayList : public ListInterface<ItemType>{
private:
    static const int DEFAULT_CAPACITY = 5; // Small capacity to test for a full list
    ItemType items[DEFAULT_CAPACITY];      // Array of list items
    int itemCount;                         // Current count of list items
    int maxItems;                          // Maximum capacity of the list
   
public:
   ArrayList();
   // Copy constructor and destructor are supplied by compiler
   
   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();
   
   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);

   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   void setEntry(int position, const ItemType& newEntry)
                               throw(PrecondViolatedExcep);
}; // end ArrayList

template<class ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0), maxItems(DEFAULT_CAPACITY){
}  // end default constructor

template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int ArrayList<ItemType>::getLength() const{
   return itemCount;
}  // end getLength

template<class ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType& newEntry){
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1) &&
                       (itemCount < maxItems);
   if (ableToInsert){
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1)
      for (int pos = itemCount; pos >= newPosition; pos--)
         items[pos] = items[pos - 1];
         
      // Insert new entry
      items[newPosition - 1] = newEntry;
      itemCount++;  // Increase count of entries
   }  // end if
   
   return ableToInsert;
}  // end insert

template<class ItemType>
bool ArrayList<ItemType>::remove(int position){
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove){
      // Remove entry by shifting all entries after the one at
      // position toward the beginning of the array
      // (no shift if position == itemCount)
      for (int fromIndex = position, toIndex = fromIndex - 1; fromIndex < itemCount;
            fromIndex++, toIndex++)
         items[toIndex] = items[fromIndex];
         
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}  // end remove

template<class ItemType>
void ArrayList<ItemType>::clear(){
   itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep){
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
      return items[position - 1];
   else{
      string message = "getEntry() called with an empty list or invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end getEntry

template<class ItemType>
void ArrayList<ItemType>::setEntry(int position, const ItemType& newEntry) throw(PrecondViolatedExcep){
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
      items[position - 1] = newEntry;
   else{
      string message = "setEntry() called with an empty list or invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end setEntry

int main(){
    ListInterface<string>* listPtr = new ArrayList<string>();
    string data[] = {"one", "two", "three", "four", "five", "six"};
    cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 1 (true)\n";
    for (int i = 0; i < 6; i++){
        if (listPtr->insert(i + 1, data[i]))
            cout << "Inserted " << listPtr->getEntry(i + 1) << " at position " << (i + 1) << endl;
        else
            cout << "Cannot insert " << data[i] << " at position " << (i + 1) << endl;
    }  // end for
    
    cout << "list now has " << listPtr->getLength() << " elements\n";
    cout << "position 4 now is: " << listPtr->getEntry(4) << "\n";
    listPtr->remove(4);
    cout << "After removing position 4, position 4 is: " << listPtr->getEntry(4) << "\n";
    cout << "list now has " << listPtr->getLength() << " elements\n";
    
   return 0;
}  // end main

/*
 isEmpty: returns 1; should be 1 (true)
 Inserted one at position 1
 Inserted two at position 2
 Inserted three at position 3
 Inserted four at position 4
 Inserted five at position 5
 Cannot insert six at position 6
 list now has 5 elements
 position 4 now is: four
 After removing position 4, position 4 is: five
 list now has 4 elements
 */
