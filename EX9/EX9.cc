#include <bits/stdc++.h>
using namespace std;

int uniform(int start ,int end ,int time){
    if(time == 1)
        return 1;
    else if (rand()%(end -start) == 0)
        return 1;
    else
        return 0;
}
vector<int>  QueensLv(int queen_num){
    vector<bool> col(queen_num+1,true),diag45(2*queen_num,true),diag135(2*queen_num+1,true);
    vector<int> try_queen(queen_num+1);
    int k = 0;
    int nb = 0;
    do{
        nb = 0;
        int j = 0;
        for (int i = 1; i <= queen_num; i++){
            int time = 1;
            if(col[i] && diag45[i-k-1 + queen_num] && diag135[i+k+1] ){
                nb+=1;
                if(uniform(1,nb,time) == 1){
                    j=i;
                }
                time++;
            }
        }
        if(nb > 0){
            k += 1;
            try_queen[k] = j;
            col[j] = false;
            diag45[j-k + queen_num] = false;
            diag135[j+k] = false;
        }
    }while(nb == 0 || k == queen_num);
    if (nb > 0){
        return try_queen;
    }
}



int main(){
    auto result = QueensLv(8);
    for (int i =1; i < result.size(); i++)
        cout << result[i]<< "";
    cout << endl;
}
