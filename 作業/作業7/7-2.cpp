#include<iostream>
#include<stdexcept>
#include<cmath>
using namespace std;

//ADT: Stack
template<class ItemType>
class StackInterface{
public :
    virtual bool isEmpty() const = 0;
    virtual bool push(const ItemType& newEntry) = 0;
    virtual bool pop() = 0;
    virtual ItemType peek() const = 0;
};


//Array-based Stack
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

int precedence(const string op);// +,- < *,/ < ^

template <typename T>
void operation(ArrayStack<T>& operands, string op);

int main(){

    string text;
    while (getline(cin, text)) {
        text += " ";
        size_t cur = 0;
        size_t pos = text.find(" ", cur);
        
        ArrayStack<int> operands; //數字
        ArrayStack<string> operators; //運算符號
        
        //stage 1:
        while(pos != string::npos){
            string temp = text.substr(cur, pos - cur);
            if(temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^"){
                if(!operators.isEmpty()){
                    string opB = operators.peek();
                    while (precedence(temp) <= precedence(opB) && operators.pop()) {
                        operation(operands, opB);
                        if(!operators.isEmpty())
                            opB = operators.peek();
                    }
                }
                operators.push(temp);
            }
            else{
                int num = stoi(temp);
                operands.push(num);
            }
            
            cur = pos + 1;
            pos = text.find(" ", cur);
        }
        
        //stage 2:
        while (!operators.isEmpty()) {
            string op = operators.peek();
            operators.pop();
            operation(operands, op);
        }
        
        //outcome:
        cout << operands.peek() << "\n";
    }
}

int precedence(const string op){
    if(op == "+" || op == "-")
        return 1;
    else if(op == "*" || op == "/")
        return 2;
    else if(op == "^")
        return 3;
    else
        throw logic_error("...");
}

template <typename T>
void operation(ArrayStack<T>& operands, string op){
    
    int num2 = operands.peek();
    operands.pop();
    int num1 = operands.peek();
    operands.pop();
    
    if(op == "+")
        operands.push(num1 + num2);
    else if(op == "-")
        operands.push(num1 - num2);
    else if(op == "*")
        operands.push(num1 * num2);
    else if(op == "/" && num2 != 0)
        operands.push(num1 / num2);
    else if(op == "^")
        operands.push(pow(num1, num2));
}
