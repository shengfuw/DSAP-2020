#include<iostream>
#include<stdexcept>
using namespace std;

template<class ItemType>
class StackInterface{
public :
    virtual bool isEmpty() const = 0;
    virtual bool push(const ItemType& newEntry) = 0;
    virtual bool pop() = 0;
    virtual ItemType peek() const = 0;
};

template<typename ItemType>
class ArrayStack: public StackInterface<ItemType>{
private:
    static const int MAX_STACK = 1000;
    ItemType items[MAX_STACK];
    int top;
public:
    ArrayStack(): top(-1){ };
    bool isEmpty() const;
    bool push(const ItemType& newEntry);
    bool pop();
    ItemType peek() const throw(logic_error);
};

template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const{
    return top < 0;
}

template<typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry){
    bool result = false;
    if(top < MAX_STACK - 1){
        top++;
        items[top] = newEntry;
        result = true;
    }
    return result;
}

template<typename ItemType>
bool ArrayStack<ItemType>::pop(){
    bool result = false;
    if(!this->isEmpty()){
      top--;
      result = true;
    }
    return result;
}

template<typename ItemType>
ItemType ArrayStack<ItemType>::peek() const throw(logic_error){
    if(!this->isEmpty())
        return items[top];
    else
        throw logic_error("...");
}


int main(){
    string text;
    while (getline(cin, text)) {
        ArrayStack<string> aStack;
        for(int i = 0; i < text.length(); i++){
            if(text[i] == '<')
                aStack.pop();
            else{
                string s(1, text[i]);
                aStack.push(s);
            }
        }
        
        ArrayStack<string> bStack;
        while (!aStack.isEmpty()) {
            bStack.push(aStack.peek());
            aStack.pop();
        }
        
        while (!bStack.isEmpty()) {
            cout << bStack.peek();
            bStack.pop();
        }
        
        cout << "\n";
    }
}





