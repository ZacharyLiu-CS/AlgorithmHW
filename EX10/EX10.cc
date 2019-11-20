#include <bits/stdc++.h>
using namespace std;
int uniform(int start ,int end ,int time = 0){
    if(time == 1)
        return 1;
    else
        return rand()%(end -start);
}
int rootLV(int x , int p){
    int a = uniform(1,p-1);
    if( a*a%p == x)
        return a;
    else{

    }
}
#define Runtime 100000
int main(){
    srand((unsigned int)time(NULL));
    for(int i = 1; i < Runtime; i++){
        cout << "time: "<<i <<"->"<< uniform(1,Runtime) << endl;
    }
    return 0;

}