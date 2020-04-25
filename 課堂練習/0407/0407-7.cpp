#include<iostream>
#include<string>
using namespace std;

class BagInterface
{
public:
  virtual int getCurrentSize() const = 0;
  virtual bool isEmpty() const = 0;
  virtual bool add(const string& newEntry) = 0;
  virtual bool remove(const string& anEntry) = 0;
  virtual void clear() = 0;
  virtual int getFrequencyOf(const string& anEntry) const = 0;
  virtual bool contains(const string& anEntry) const = 0;
  virtual void print() const = 0;
};




class ArrayBag : public BagInterface
{
protected:
  static const int DEFAULT_CAPACITY = 6;
  string items[DEFAULT_CAPACITY];
  int itemCount;
  int maxItems;
  int getIndexOf(const string& target) const;

public:
  ArrayBag();
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const string& newEntry);
  bool remove(const string& anEntry);
  void clear();
  bool contains(const string& anEntry) const;
  int getFrequencyOf(const string& anEntry) const;
  void print() const;
};

ArrayBag::ArrayBag(): itemCount(0), maxItems(ArrayBag::DEFAULT_CAPACITY)
{
}

int ArrayBag::getCurrentSize() const
{
  return itemCount;
}

bool ArrayBag::isEmpty() const
{
  return itemCount == 0;
}

bool ArrayBag::add(const string& newEntry)
{
  bool hasRoomToAdd = (itemCount < maxItems);
  if (hasRoomToAdd)
  {
    items[itemCount] = newEntry;
    itemCount++;
  }
  return hasRoomToAdd;
}
 
bool ArrayBag::remove(const string& anEntry)
{
  int locatedIndex = getIndexOf(anEntry);
  bool canRemoveItem = (locatedIndex > -1);
  if(canRemoveItem)
  {
    itemCount--;
    items[locatedIndex] = items[itemCount];
  }
  return canRemoveItem;
}

void ArrayBag::clear()
{
  itemCount = 0;
}

int ArrayBag::getFrequencyOf(const string& anEntry) const
{
  int frequency = 0;
  int curIndex = 0;
  while(curIndex < itemCount)
  {
    if(items[curIndex] == anEntry)
      frequency++;
    curIndex++;
  }
  return frequency;
}

bool ArrayBag::contains(const string& anEntry) const
{
  return getIndexOf(anEntry) > -1;
}

void ArrayBag::print() const
{
  for(int i = 0; i < itemCount; i++)
    cout << items[i] << " ";
  cout << endl;
}

int ArrayBag::getIndexOf(const string& target) const
{
  bool found = false;
  int result = -1;
  int searchIndex = 0;
   
  while(!found && (searchIndex < itemCount))
  {
    if(items[searchIndex] == target)
    {
      found = true;
      result = searchIndex;
    }
    else
      searchIndex++;
  }
  return result;
}












class DistinctBag : public ArrayBag
{
private:
  bool removeAll(const string& anEntry);
public:
  DistinctBag();
  bool add(const string& newEntry);
};

DistinctBag::DistinctBag()
{
  this->itemCount = 0;
  this->maxItems = DEFAULT_CAPACITY;
}

bool DistinctBag::add(const string& newEntry)
{
  bool hasRoomToAdd = (this->itemCount < this->maxItems);
  bool exist = contains(newEntry);
  if(hasRoomToAdd && !exist)
  {
    this->items[this->itemCount] = newEntry;
    this->itemCount++;
    return true;
  }
  else
    return false;
}

bool DistinctBag::removeAll(const string& newEntry)
{
}

















void displayBag(DistinctBag& bag)
{
  cout << "The bag contains " << bag.getCurrentSize()
       << " items:" << endl;

  bag.print();

  cout << endl << endl;
}

void bagTester(DistinctBag& bag)
{
  cout << "isEmpty: returns " << bag.isEmpty()
       << "; should be 1 (true)" << endl;
  displayBag(bag);

  string items[] = {"one", "two", "five", "four", "five", "one"};
  cout << "Add 6 items to the bag: " << endl;
  for (int i = 0; i < 6; i++)
  {
    bag.add(items[i]);
  }
   
  displayBag(bag);

}

int main()
{
  DistinctBag bag;

  cout << "Testing the Array-Based Bag:" << endl;
  cout << "The initial bag is empty." << endl;
  bagTester(bag);
  cout << "All done!" << endl;

  return 0;
}
