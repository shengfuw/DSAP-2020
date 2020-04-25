#include <iostream>
#include <string>
using namespace std;
 
const int capacity = 5000;
 
template<typename userT>
class userArray;//先宣告這樣user才能理解
 
void print(string outcome[], int n);
 
template<typename userT>
int getN(string merchantName, userArray<userT>& merchantArray);
 
//user
class user{
protected:
    string account;
    int traded_CNT; //交易次數
    string tradedTargets[capacity]; //交易的對象
    string tradedprodcut[capacity]; //交易的商品
    int gievenScores[capacity]; //別人給自己的評分
    int givingScores[capacity]; //給別人的評分
public:
    user(string account): account(account), traded_CNT(0) { };
    string getName() {return account;};
    int getCNT() {return traded_CNT;};
    void trade(string targetName, string product, int gievenScore, int givingScore);
};
 
void user::trade(string targetName, string product, int gievenScore, int givingScore){
    tradedTargets[traded_CNT] = targetName;
    tradedprodcut[traded_CNT] = product;
    gievenScores[traded_CNT] = gievenScore;
    givingScores[traded_CNT] = givingScore;
    traded_CNT++;
}
 
//customer
class customer: public user{
private:
public:
    customer(string account): user(account){ };
    void normalSearch(string product);
    template<typename T>
    bool VIPSearch0(string product, int miniN, userArray<T>& merchantArray);
    template<typename T>
    bool VIPSearch1(string product, int miniN, userArray<T>& merchantArray);
};
 
void customer::normalSearch(string product){
    string outcome[capacity];
    int bestScore = -1, outcome_CNT = 0;
     
    for(int i = 0; i < traded_CNT; i++){
        if(tradedprodcut[i] == product && givingScores[i] > bestScore)
            bestScore = givingScores[i];
    }
     
    for(int i = 0; i < traded_CNT; i++){
        if(tradedprodcut[i] == product && givingScores[i] == bestScore){
            outcome[outcome_CNT] = tradedTargets[i];
            outcome_CNT++;
        }
    }
     
    print(outcome, outcome_CNT);
}
 
template<typename T>
bool customer::VIPSearch0(string product, int miniN, userArray<T>& merchantArray){
    double sumScore = 0;
    for(int i = 0; i < traded_CNT; i++){
        sumScore += gievenScores[i];
    }
    double meanScore = 0;
    if(traded_CNT > 0)
        meanScore = sumScore / static_cast<double>(traded_CNT);
    
    if(traded_CNT < 3 || meanScore <= 3){
        cout << "reject\n";
        return 0;
    }
     
    int bestScore = -1, outcome_CNT = 0;
    string outcome[capacity];
     
    for(int i = 0; i < traded_CNT; i++){
        if(tradedprodcut[i] == product && givingScores[i] > bestScore && getN(tradedTargets[i], merchantArray) >= miniN)
            bestScore = givingScores[i];
    }
     
    for(int i = 0; i < traded_CNT; i++){
        if(tradedprodcut[i] == product && givingScores[i] == bestScore && getN(tradedTargets[i], merchantArray) >= miniN){
            outcome[outcome_CNT] = tradedTargets[i];
            outcome_CNT++;
        }
    }
    
    print(outcome, outcome_CNT);
    return 1;
}
 
template<typename T>
bool customer::VIPSearch1(string product, int miniN, userArray<T>& merchantArray){
    double sumScore = 0;
    for(int i = 0; i < traded_CNT; i++){
        sumScore += gievenScores[i];
    }
    double meanScore = 0;
    if(traded_CNT > 0)
        meanScore = sumScore / static_cast<double>(traded_CNT);
    
    if(traded_CNT < 3 || meanScore <= 3){
        cout << "reject\n";
        return 0;
    }
     
    double bestScore = -1;
    int outcome_CNT = 0;
    string outcome[capacity];
     
    for(int i = 0; i < merchantArray.user_CNT; i++){
        if(merchantArray[i]->hasProduct(product) == true && getN(merchantArray[i]->getName(), merchantArray) >= miniN && merchantArray[i]->getMeanScore() > bestScore){
            bestScore = merchantArray[i]->getMeanScore();
        }
    }
     
    for(int i = 0; i < merchantArray.user_CNT; i++){
        if(merchantArray[i]->hasProduct(product) == true && getN(merchantArray[i]->getName(), merchantArray) >= miniN && merchantArray[i]->getMeanScore() == bestScore){
            outcome[outcome_CNT] = merchantArray[i]->getName();
            outcome_CNT++;
        }
    }
     
    print(outcome, outcome_CNT);
    return 1;
}
 
 
//merchant
class merchant: public user{
private:
    int product_CNT;
    string productList[capacity];
public:
    merchant(string account): user(account){ product_CNT = 0; };
    void merchantAddProduct(string product);
    bool hasProduct(string product);
    double getMeanScore();
};
 
void merchant::merchantAddProduct(string product){
    productList[product_CNT] = product;
    product_CNT++;
}
 
bool merchant::hasProduct(string product){
    bool include = false;
    for(int i = 0; i < product_CNT; i++){
        if(productList[i] == product)
            include = true;
    }
    return include;
}
 
double merchant::getMeanScore(){
    double  sumScore = 0;
    for(int i = 0; i < traded_CNT; i++){
        sumScore += gievenScores[i];
    }
    if(traded_CNT != 0)
        return sumScore / static_cast<double>(traded_CNT);
    return 0;
 
}
 
//userArray
template<typename userT>
class userArray{
    template<typename T>
    friend int getN(string merchantName, userArray<T>& merchantArray);
     
    template<typename T>
    friend bool customer::VIPSearch1(string product, int miniN, userArray<T>& merchantArray);
 
private:
    int user_CNT;
    userT** userPtr;
public:
    userArray();
    ~userArray();
    bool addUser(string account);
    userT* operator[](int i);
};
 
template<typename userT>
userArray<userT>::userArray(){
    user_CNT = 0;
    userPtr = new userT*[capacity];
}
 
template<typename userT>
userArray<userT>::~userArray(){
    for(int i = 0; i < user_CNT; i++)
        delete userPtr[i];
    delete [] userPtr;
}
 
template<typename userT>
bool userArray<userT>::addUser(string account){
    bool add = true;
    for(int i = 0; i < user_CNT; i++){
        if(userPtr[i]->getName() == account)
            add = false;
    }
     
    if(add == true){
        userPtr[user_CNT] = new userT(account);
        user_CNT++;
    }
     
    return add;
}
 
template<typename userT>
userT* userArray<userT>::operator[](int i){
    return userPtr[i];
}


int main(){
    userArray<merchant> merchantArray;
    userArray<customer> customerArray;
    int customer_CNT = 0, merchant_CNT = 0;
     
    while(cin){
        char function = 0;
        cin >> function;
        switch (function) {
            case 'C':{
                string account;
                cin >> account;
                if(customerArray.addUser(account) == true)
                    customer_CNT++;
                break;
            }
            case 'M':{
                string account;
                cin >> account;
                if(merchantArray.addUser(account) == true)
                    merchant_CNT++;
                break;
            }
            case 'T':{
                string customerAccount, merchantAccount, product;
                int toM_score, toC_score;
                cin >> customerAccount >> merchantAccount >> product >> toM_score >> toC_score;
                for(int i = 0; i < customer_CNT; i++){
                    if(customerArray[i]->getName() == customerAccount)
                        customerArray[i]->trade(merchantAccount, product, toC_score, toM_score);
                }
                for(int i = 0; i < merchant_CNT; i++){
                    if(merchantArray[i]->getName() == merchantAccount)
                        merchantArray[i]->trade(customerAccount, product, toM_score, toC_score);
                }
                break;
            }
            case 'S':{
                cin.ignore();
                string text;
                getline(cin, text);
                 
                size_t found1 = text.find(" ");
                string customerAccount = text.substr(0, found1);
                size_t found2 = text.find(" ", found1 + 1);
                string product = text.substr(found1 + 1, found2 - found1 - 1);
                 
                if(found2 == string::npos){
                    for(int i = 0; i < customer_CNT; i++){
                        if(customerArray[i]->getName() == customerAccount)
                            customerArray[i]->normalSearch(product);
                    }
                }
                else{
                    found1 = text.find(" ", found2 + 1);
                    int miniN = stoi(text.substr(found2 + 1, found1 - found2 - 1));
                    int x = stoi(text.substr(found1 + 1, 1));
                    for(int i = 0; i < customer_CNT; i++){
                        if(customerArray[i]->getName() == customerAccount){
                            if(x == 0)
                                customerArray[i]->VIPSearch0(product, miniN, merchantArray);
                            else
                                customerArray[i]->VIPSearch1(product, miniN, merchantArray);
                        }
                    }
                }
                break;
            }
            case 'A':{
                string merchantAccount, product;
                cin >> merchantAccount >> product;
                for(int i = 0; i < merchant_CNT; i++){
                    if(merchantArray[i]->getName() == merchantAccount)
                        merchantArray[i]->merchantAddProduct(product);
                }
                break;
            }
            case 'P':{
                string productName;
                cin >> productName; //nothing happend?
                break;
            }
            default:
                break;
        }
    }
}

void print(string outcome[], int n){
    //sort
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j < i ; j++){
            if(outcome[j].compare(outcome[j+1]) > 0){
                string temp = outcome[j];
                outcome[j] = outcome[j+1];
                outcome[j+1] = temp;
            }
        }
    }
    //print
    if(n > 5)
        n = 5;
    for(int i = 0; i < n; i++){
        cout << outcome[i];
        if(i != n - 1)
            cout << " ";
    }
    cout << "\n";
}

template<typename userT>
int getN(string merchantName, userArray<userT>& merchantArray){
    for(int i = 0; i < merchantArray.user_CNT; i++){
        if(merchantArray[i]->getName() == merchantName)
            return merchantArray[i]->getCNT();
    }
    return 0;
}
