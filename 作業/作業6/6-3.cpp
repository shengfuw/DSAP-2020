#include <iostream>
#include <string>
using namespace std;

const int MAX_NODE = 2000;

bool dfs(int** graph, int V, int s, int t, int visited[]);
int augmentingPath(int** graph, int V);

int main(){
    int nodeCnt = 0;
    cin >> nodeCnt;
    
    //adjustment matrix
    int** graph = new int*[2 * nodeCnt + 2];
    for(int i = 0; i < 2 * nodeCnt + 2; i++){
        graph[i] = new int[2 * nodeCnt + 2];
        for(int j = 0; j < 2 * nodeCnt + 2; j++)
            graph[i][j] = 0;
    }
    
    //trans to bipartite matching
    for(int i = 1; i <= nodeCnt; i++)
        graph[0][i] = 1;
    
    for(int i = nodeCnt + 1; i <= 2 * nodeCnt; i++)
        graph[i][2*nodeCnt+1] = 1;
    
    
    //data input
    string input;
    cin >> input;
    input += ";";

    int n = 1;
    size_t found = input.find(';'), last = 0;
    while(found != string::npos){
        string test = input.substr(last, found - last);
        last = found + 1;
        found = input.find(';', last);
        if(test != ""){
            test += ",";
            size_t f = test.find(','), l = 0;
            while(f != string::npos){
                string node = test.substr(l, f - l);
                l = f + 1;
                f = test.find(',', l);
                int u = stoi(node) + nodeCnt;
                graph[n][u] = 1;
            }
        }
        n++;
    }
    
    //find maximum flow
    cout << augmentingPath(graph, (2 * nodeCnt + 1)) << "\n";
}

bool dfs(int **graph, int nodeCNT, int s, int t, int visited[]){

    if(graph[s][t] == 1){
        graph[s][t] = 0;
        graph[t][s] = 1;
        return true;
    }
        
    for(int i = 0; i <= nodeCNT; i++){
        if(graph[s][i] == 1 && visited[i] == 0){
            visited[i] = 1;
            if(dfs(graph, nodeCNT, i, t, visited) == true){
                graph[i][s] = 1;
                graph[s][i] = 0;
                return true;
            }
        }
    }
    return false;
}

int augmentingPath(int **graph, int nodeCNT){
    /*
    for(int i = 0; i <= nodeCNT; i++){
        for(int j = 0; j <= nodeCNT; j++){
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "============\n";
    */
    
    int maxFlow = 0;
    bool hasRoad = true;
    while(hasRoad){
        for(int i = 0; i <= nodeCNT; i++){
            if(graph[0][i] == 1){
                
                int visited[MAX_NODE] = {0};
                visited[0] = 1;
                visited[i] = 1;
                
                if(dfs(graph, nodeCNT, i, nodeCNT, visited)){
                    graph[0][i] = 0;
                    graph[i][0] = 1;
                    maxFlow++;
                    break;
                }
            }
            if(i == nodeCNT)
                hasRoad = false;
        }
    }
    
    /*
    for(int i = 0; i <= nodeCNT; i++){
        for(int j = 0; j <= nodeCNT; j++){
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "============\n";
    */
     
    return maxFlow;
}
