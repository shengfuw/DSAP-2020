#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string dictPath = "/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/資料結構與與進階程式設計 程式碼/課堂練習/0317/dict.txt";
string logPath = "/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/資料結構與與進階程式設計 程式碼/課堂練習/0317/log.txt";
string makeStringLower(string word);

int main(){
    string target, word;
    cin >> target;
    word = makeStringLower(target);
    
    ifstream dictionary(dictPath);
    ofstream log(logPath, ios::out);
    
    if(!dictionary.eof()){
        string w;
        while(dictionary >> w){
            log << "Comparing " + target + " with " + w;
            if(w == word){
                log << "... Got it!";
                break;
            }
            else
                log << endl;
        }
    }
    
    dictionary.close();
    log.close();
    cout << "complete!\n";
}
string makeStringLower(string word){
    for(size_t i = 0; i < word.length(); i++)
        word[i] = tolower(word[i]);
    return word;
}

