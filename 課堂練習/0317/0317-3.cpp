#include <iostream>
#include <string>
using namespace std;

string toDollarNumber(int value);

int main(){
    int value = 0;
    cin >> value;
    cout << toDollarNumber(value) << "\n";
}

string toDollarNumber(int value){
    string dollar("$"), temp = to_string(value);
    for(int i = 0; i < temp.length(); i++){
        dollar += temp[i];
        if((i + 1) % 3 == (temp.length() % 3) && ((i+1) != temp.length()))
            dollar += ",";
    }
    return dollar;
}
