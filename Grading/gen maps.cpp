#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

int main(){
    
    for(int f = 101; f <= 200; f++){
        int map[50][50] = {0};
        
        for(int i = 0; i < 50; i++){
            map[0][i] = -1;
            map[i][0] = -1;
            map[49][i] = -1;
            map[i][49] = -1;
        }
        
        srand(time(NULL));
        
        int blocksNUM = rand() % 45 + 1;
        //cout << blocksNUM << "\n";
        
        for(int i = 0; i < blocksNUM; i++){
            int blockPOSX = rand() % 49 + 1;
            int blockPOSY = rand() % 49 + 1;
            map[blockPOSX][blockPOSY] = -1;
        }
        
        int targetsNUM = rand() % 10 + 1;
        //cout << targetsNUM << "\n";
        for(int i = 0; i < blocksNUM; i++){
            int targetPOSX = rand() % 49 + 1;
            int targetPOSY = rand() % 49 + 1;
            map[targetPOSX][targetPOSY] = rand() % 6 + 1 ;
        }
        
        /*
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                cout << setw(2) << map[i][j] << " ";
            }
            cout << "\n";
        }
        */
        
        ofstream out;
        string fileName = "/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/資料結構與進階程式設計/Grading/map/maps/map_" + to_string(f);
        out.open(fileName);
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 50; j++){
                out << map[i][j];
                if(j < 49)
                    out << " ";
                else if(i < 49)
                    out << "\n";
            }
        }
    }
    cout << "complete\n";
}
