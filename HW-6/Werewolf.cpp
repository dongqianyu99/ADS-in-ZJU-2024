/*
bool BackTracking(int i){
    Found = false;
    if (i > N)
        return true;  // solved
    for (each xi in Si){  // Check if satisfies the restriction R
        OK = Check((x1, ..., xi), R);  // pruning
        if (OK){
            Count xi in;
            Found = BackTracking(i+1);
        if (!Found)
            undo(i);  // recover to (x1, ..., xi-1)
        }
        if (Found)
            break;
    }
    return Found;
}
*/


#include <cstdio>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int N, M, L;
int statement[105];
int state[105] = {0};  // 0 states for unknown

bool Check(int count){  // Check the restriction R
    int lier_cnt = 0;
    int human_lier = 0;
    int wolf_lier = 0;
    int wolf_cnt = 0;
    
    for (int i = 1; i <= N; i++){  // count the wolves
        if (state[i] == 2)
            wolf_cnt++;
    }

    for (int i = 1; i <= N; i++){  // count the liers and record their ID
        if (statement[i] > 0 && state[abs(statement[i])] == 2){
            lier_cnt++;
            if (state[i] == 1)
                human_lier++;
            else if (state[i] == 2)
                wolf_lier++;
        }
        if (statement[i] < 0 && state[abs(statement[i])] == 1){
            lier_cnt++;
            if (state[i] == 1)
                human_lier++;
            else if (state[i] == 2)
                wolf_lier++;
        }
    }

    if (count != 0){
        if (lier_cnt > L || wolf_cnt > M || wolf_lier == M)
            return false;
        else 
            return true;
    }
    else {
        if (lier_cnt == L && wolf_cnt == M && wolf_lier >= 1 && wolf_lier < M)
            return true;
        else 
            return false;
    }

}

bool FindWolves(int count){
    bool Found = false;
    if (count < 0)
        return true;
    bool OK = Check(count);
    if (OK) {  // change the state
        state[count] = 2;  // Option1: Wolf
        Found = FindWolves(count - 1);
        if (!Found) {  // if does not work, undo
            state[count] = 0;
        }
    }
    // finish checking option1
    if (!Found && OK) {
        state[count] = 1;  // Option2: Human
        Found = FindWolves(count - 1);
        if (!Found) {
            state[count] = 0;
        }
    }
    return Found;
}

int main(){
    cin >> N >> M >> L;
    queue<int> ans; 
    for (int i = 1; i <= N; i++)
        cin >> statement[i];
    
    if (!FindWolves(N))
        printf("No Solution\n");
    else {
        // for (int i = 1; i <= N; i++){
        //     printf("%d ", state[i]);
        // }
        for (int i = N; i >= 1; i--){
            if (state[i] == 2)
                ans.push(i);
        }
        // printf("%d\n", ans.size());
        for (int i = 1; i <= M; i++){
            if (i == 1)
                printf("%d", ans.front()), ans.pop();
            else
                printf(" %d", ans.front()), ans.pop();
        }
    }
    return 0;
}
