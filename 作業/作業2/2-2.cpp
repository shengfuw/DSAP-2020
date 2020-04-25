#include <iostream>
#include <string>
using namespace std;

//記錄每筆資料
class DATA{
private:
    int tag, words_cnt, sentence_cnt;
    double averge;
    string text;
public:
    DATA(int tag, string text);
    double getAverge();
    int getTag();
};

DATA::DATA(int tag, string text): tag(tag), text(text){
    words_cnt = 1;
    sentence_cnt = 0;
    averge = 0;
    for(int i = 0; i < text.length(); i++){
        if(text[i] == ' ')
            words_cnt++;
        if(text[i] == ',' || text[i] == '.' ||text[i] == ';' ||text[i] == '!' ||text[i] == '?'){
            if(i == text.length())
                sentence_cnt++;
            else{
                if(isdigit(text[i+1]) == false|| isdigit(text[i-1]) == false)
                sentence_cnt++;
            }
        }
    }
    averge = static_cast<double>(words_cnt) / static_cast<double>(sentence_cnt);
}

double DATA::getAverge(){
    return averge;
}

int DATA::getTag(){
    return tag;
}


//資料集
class DATA_array{
protected:
    int cnt, num;
    DATA** DATAPtr;
public:
    DATA_array(int num);
    ~DATA_array();
    bool add(int tag, string text);
};

DATA_array::DATA_array(int num): cnt(0), num(num){
    DATAPtr = new DATA*[num];
}

DATA_array::~DATA_array(){
    for(int i = 0; i < num; i++)
        delete DATAPtr[i];
    delete [] DATAPtr;
}

bool DATA_array::add(int tag, string text){
    if(cnt < num){
        DATAPtr[cnt] = new DATA(tag, text);
        cnt++;
        return true;
    }
    else
        return false;
}

//訓練資料集
class trainDATA_array: public DATA_array{
private:
public:
    trainDATA_array(int num): DATA_array(num){ };
    int outcome();
};

int trainDATA_array::outcome(){
    //find range of averge
    double miniAverge = 100000, maxAverge = -1;
    for(int i = 0; i < num; i++){
        if(DATAPtr[i]->getAverge() < miniAverge)
            miniAverge = DATAPtr[i]->getAverge();
        if(DATAPtr[i]->getAverge() > maxAverge)
            maxAverge = DATAPtr[i]->getAverge();
    }
    //find critical value that cause least errors
    int criticalValue = miniAverge, miniError = num + 1;
    for(int i = miniAverge; i <= maxAverge; i++){
        int error = 0;
        for(int j = 0; j < num; j++){
            if(DATAPtr[j]->getAverge() < i && DATAPtr[j]->getTag() == 2)
                error++;
            if(DATAPtr[j]->getAverge() >= i && DATAPtr[j]->getTag() == 1)
                error++;
        }
        if(error < miniError){
            miniError = error;
            criticalValue = i;
        }
    }
    return criticalValue;
}
    

//驗證資料集
class testDATA_array: public DATA_array{
private:
public:
    testDATA_array(int num): DATA_array(num){ };
    int outcome(int criticalValue);
};

int testDATA_array::outcome(int criticalValue){
    int error = 0;
    for(int i = 0; i < num; i++){
        if(DATAPtr[i]->getAverge() < criticalValue && DATAPtr[i]->getTag() == 2)
            error++;
        if(DATAPtr[i]->getAverge() >= criticalValue && DATAPtr[i]->getTag() == 1)
            error++;
    }
    return error;
}



int main(){
    int train_num = 0, test_num = 0;
    cin >> train_num >> test_num;
    trainDATA_array train(train_num);
    testDATA_array test(test_num);
    
    for(int i = 0; i < train_num + test_num; i++){
        string input, text;
        int tag = 0 ;
        getline(cin, input, ';');
        tag = stoi(input);
        getline(cin, input);
        text = input;
        if(i < train_num)
            train.add(tag, text);
        else
            test.add(tag, text);
    }
    
    int criticalValue = train.outcome();
    cout << criticalValue << "," << test.outcome(criticalValue);
}

測試一波
