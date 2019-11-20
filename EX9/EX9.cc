#include <bits/stdc++.h>

std::deque<int> backtrace(int start , int queen_num, std::set<int> col,
                          std::set<int> diag45, std::set<int> diag135,
                          std::deque<int> _try_queen);
std::deque<int> leagcy_backtree(int queen_num);
std::deque<int>  QueensLV(int queen_num,int stepVegas);
std::deque<int> leagcy_QueensLV(int queen_num);


int main(){
    srand((unsigned int) time(NULL));

    // backtree run time
    std::cout << "this is backtree funciton result:" << std::endl;
    auto resultBT = leagcy_backtree(20);
    for (auto i =resultBT.begin();i != resultBT.end() ; i++)
        std::cout << *i << "";
    std::cout << std::endl;

    // add lasVegas to backtree
    auto resultLV = QueensLV(20,13);
    for (auto i =resultLV.begin();i != resultLV.end() ; i++)
        std::cout << *i << "";
    std::cout << std::endl;


    // pure LasVegas function
    resultLV = leagcy_QueensLV(20);
    for (int i =0; i < resultLV.size(); i++)
        std::cout << resultLV[i] << "";
    std::cout << std::endl;


}

int uniform(int start ,int end ,int time = 0){
    if(time == 1)
        return 1;
    else if (rand()%(end -start) == 0)
        return 1;
    else
        return 0;
}
std::deque<int> backtrace(int start , int queen_num, std::set<int> col,
                          std::set<int> diag45, std::set<int> diag135,
                          std::deque<int> _try_queen){
    std::deque<int> try_queen(_try_queen);
    int i = start==0? 1: start;
    int col_number = 1;
    while(i <= queen_num){
        for(; col_number <= queen_num; col_number++){
            if(col.count(col_number) == 0 && diag45.count(i-col_number) == 0 && diag135.count(i+col_number) == 0 ) {
                try_queen.push_back(col_number);
                col.insert(col_number); diag45.insert(i-col_number); diag135.insert(i+col_number);
                i++;
                col_number = 0;
            }
        }
        if(i <= queen_num){
            i--;
            if(try_queen.empty()){
                try_queen.push_front(-1);
                return try_queen;
            }
            int wrong_col_placement = try_queen.back();
            try_queen.pop_back();
            col.erase(wrong_col_placement); diag45.erase(i-wrong_col_placement); diag135.erase(i+wrong_col_placement);
            col_number = wrong_col_placement+1;
        }
    }

    return try_queen;
}
std::deque<int> leagcy_backtree(int queen_num){
    std::set<int> col,diag45,diag135;
    std::deque<int> try_queen;
    int start = 1;
    return backtrace(start,queen_num,col,diag45,diag135,try_queen);
}
std::deque<int>  QueensLV(int queen_num,int stepVegas){
    std::set<int> col,diag45,diag135;
    std::deque<int> try_queen;
    int repeatnum = 1;
    while(true) {
        col.clear();diag45.clear();diag135.clear();try_queen.clear();
        int k = 0;
        int nb = 0;
        do {
            nb = 0;
            int j = 0;
            int times = 1;
            for (int i = 1; i <= queen_num; i++) {
                if (col.count(i) == 0 && diag45.count(i - k - 1) == 0 && diag135.count(i + k + 1) == 0) {
                    nb += 1;
                    if (uniform(1, nb, times) == 1) j = i;
                    times++;
                }
            }
            if (nb > 0) {
                k += 1;
                try_queen.push_back(j);
                col.insert(j);
                diag45.insert(j - k);
                diag135.insert(j + k);
            }
        } while (!(nb == 0 || k == queen_num || k == stepVegas));
        if (nb > 0) {
            if( k == stepVegas) {
                try_queen =  backtrace(k + 1, queen_num, col, diag45, diag135, try_queen);
                if(try_queen.front() == -1) {
                    repeatnum ++;
                    continue;
                }
            }
            return try_queen;
        }

    }
}

std::deque<int> leagcy_QueensLV(int queen_num){
    std::set<int> col,diag45,diag135;
    std::deque<int> try_queen;
    int repeatnum = 1;
    while(true) {
        col.clear();diag45.clear();diag135.clear();try_queen.clear();
        int k = 0;
        int nb = 0;
        do {
            nb = 0;
            int j = 0;
            int times = 1;
            for (int i = 1; i <= queen_num; i++) {
                if (col.count(i) == 0 && diag45.count(i - k - 1) == 0 && diag135.count(i + k + 1) == 0) {
                    nb += 1;
                    if (uniform(1, nb, times) == 1) j = i;
                    times++;
                }
            }
            if (nb > 0) {
                k += 1;
                try_queen.push_back(j);
                col.insert(j);
                diag45.insert(j - k);
                diag135.insert(j + k);
            }
        } while (!(nb == 0 || k == queen_num ));
        if (nb > 0) {
            return try_queen;
        }
        repeatnum ++;
    }
}



