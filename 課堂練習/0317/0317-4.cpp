#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//string filePath = "/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/資料結構與與進階程式設計 程式碼/課堂練習/0317/dict.txt";

void makeStringLower(string& word);

int main(){
    string word;
    bool contain = false;
    cin >> word;
    makeStringLower(word);
    
    string filePath;
    cin.ignore(); //先cin再getline要加cin.ignore()
    getline(cin, filePath);
    
    ifstream dictionary;
    dictionary.open(filePath);
    if(dictionary){
        string w;
        while(dictionary >> w){
            //cout << w << "\n";
            if(w == word){
                contain = 0;
                break;
            }
        }
    }
    dictionary.close();
    
    cout << contain << "\n";
}
void makeStringLower(string& word){
    for(size_t i = 0; i < word.length(); i++){
        word[i] = tolower(word[i]);
    }
}

