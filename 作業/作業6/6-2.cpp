#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_CNT = 1000;

int main(){
    int cnt = 0, upperBound = 0, weights[MAX_CNT] = {0};
    cin >> cnt >> upperBound;
    
    int** matrix = new int*[cnt];
    for(int i = 0; i < cnt; i++){
        matrix[i] = new int[upperBound + 1];
    }
    
    for(int i = 0; i < cnt; i++){
        cin >> weights[i];
    }
    
    //IMP = -1, NS = 0, S = 1
    for(int i = 0; i < cnt; i++){
        for(int j = 0; j <= upperBound; j++){
            matrix[i][j] = -1;
        }
    }
    
    //第一列一定是NS
    matrix[0][0] = 0;
    //跟自重量一樣一定是S
    matrix[0][weights[0]] = 1;

    //從first row開始跑，一個NS
    for(int i = 0; i < cnt - 1; i++){
        for(int j = 0; j <= upperBound; j++){
            if(matrix[i][j] >= 0){ //如果是S或是NS
                if(matrix[i+1][j] != 1) //貢獻正下方NS
                    matrix[i+1][j] = 0;
                if(j+weights[i+1] <= upperBound) //貢獻下row右邊移weight的地方S
                    matrix[i+1][j+weights[i+1]] = 1;
            }
        }
    }
    
    /*
    //print 結果
    for(int i = 0; i < cnt; i++){
        for(int j = 0; j <= upperBound; j++){
            cout <<  setw(2) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    */
    
    //如果不存在有物品集合滿足條件
    if(matrix[cnt-1][upperBound] == -1){
        cout << 0 << "\n";
        return 0;
    }
    
    //如果存在有物品集合滿足條件
    int outcomes[MAX_CNT] = {0}, outcomeCNT = 0, check = upperBound;
    for(int i = cnt - 1; i >= 0; i--){
        if(matrix[i][check] == 1){
            check -= weights[i];
            outcomes[outcomeCNT] = i + 1;
            outcomeCNT++;
        }
    }
    
    //sort outcome
    for(int i = outcomeCNT - 1; i >= 0; i--){
        for(int j = 0; j < i ; j++){
            if(outcomes[j] > outcomes[j+1]){
                int temp = outcomes[j];
                outcomes[j] = outcomes[j+1];
                outcomes[j+1] = temp;
            }
        }
    }
    
    //print outcome
    for(int i = 0; i < outcomeCNT; i++){
        cout << outcomes[i];
        if(i < outcomeCNT - 1)
            cout << ",";
        else
            cout << "\n";
    }
}
/*

4 6
2 3 4 5
 
4 16
8 3 4 5
1,2,4
 
4 16
8 3 4 6
0
 
4 5
2 3 4 5
4
*/

