#include <iostream>
#include <string>
using namespace std;

void makeStringLower(string& word);

int main(){
    int n = 0;
    string word;
    bool contain = false;
    cin >> n;
    cin >> word;
    makeStringLower(word);
    for(int i = 0; i < n; i++){
        string w;
        cin >> w;
        if(w == word){
            contain = true;
            break;
        }
    }
    
    cout << contain << "\n";
}
void makeStringLower(string& word){
    for(size_t i = 0; i < word.length(); i++){
        word[i] = tolower(word[i]);
    }
}

