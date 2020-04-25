#include <iostream>
#include <string>
using namespace std;

int main(){
    string sentence;
    getline(cin, sentence);
    int num = 0;
    for(size_t i = 0; i < sentence.length(); i++){
        if(ispunct(sentence[i]))
            num++;
    }
    cout << num << "\n";
}
