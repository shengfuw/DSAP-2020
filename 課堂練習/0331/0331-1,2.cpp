#include <iostream>
using namespace std;

template<typename varType>
class MyVector2D{
template<typename varType1, typename varType2>
friend bool operator==(const MyVector2D<varType1>& u, const MyVector2D<varType2>& v);
private:
    varType x;
    varType y;
public:
    MyVector2D() : x(0), y(0) {};
    MyVector2D(varType x, varType y) : x(x), y(y) {};
    void print() const;
    bool operator==(const MyVector2D& v) const;
};

template<typename varType>
void MyVector2D<varType>::print() const {
    cout << "(" << this->x << ", " << this->y << ")\n";
}

template<typename varType>
bool MyVector2D<varType>::operator==(const MyVector2D& v) const {
    if(this->x == v.x && this->y == v.y)
        return true;
    else
        return false;
}

template<typename varType1, typename varType2>
bool operator==(const MyVector2D<varType1>& u, const MyVector2D<varType2>& v){
    if(u.x == v.x && u.y == v.y)
        return true;
    else
        return false;
}

int main() {
    MyVector2D<int> u(1.2, 2.3);
    MyVector2D<double> v(1.4, 2.6);
    u.print();
    v.print();
    
    if(u == v)
        cout << "Equal!\n";
    else
        cout << "Unequal!\n";
    return 0;
}
