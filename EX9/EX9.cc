#include <bits/stdc++.h>
#include <chrono>

typedef std::deque<int> (*func) (int,int);
std::deque<int> backtrace(int start , int queen_num, std::set<int> col,
                          std::set<int> diag45, std::set<int> diag135,
                          std::deque<int> _try_queen);
std::deque<int> legacy_backtree(int queen_num,int useless = 0);
std::deque<int>  QueensLV(int queen_num,int stepVegas);
std::deque<int> leagcy_QueensLV(int queen_num,int useless = 0);
long long calculate_time(func f,int run_times,int param_a,int param_b = 0);
int main(){
    srand((unsigned int) time(NULL));
    int repeat_num = 20;
    int queen_start = 12;
    int queen_end = 20;

    // backtree run time
    std::cout << "this is backtree funciton result:" << std::endl;
    long long unitconversion = 1000000;
    printf("queen_num       |");
    for(int queen_num = queen_start;queen_num <= queen_end; queen_num++) {
        printf("   %2d      |",queen_num);
    }
    printf("\nbacktree time   |");
    for(int queen_num = queen_start;queen_num <= queen_end; queen_num++) {
        long long used_time = calculate_time(legacy_backtree, repeat_num, queen_num);
        printf("%.7fs |" ,used_time/(unitconversion*1.0));

    }
    printf("\nlasVegas time   |");
    for(int queen_num = queen_start;queen_num <= queen_end; queen_num++) {
        long long used_time = calculate_time(leagcy_QueensLV, repeat_num, queen_num);
        printf("%.7fs |" ,used_time/(unitconversion*1.0));
    }
    printf("\nmixVegas time   |");

    int minSteps[queen_end-queen_start+1];
    for(int queen_num = queen_start;queen_num <= queen_end; queen_num++) {
        long long  minTime = LLONG_MAX;
        int minStep ;
        for(int stepVegas = 0; stepVegas < queen_num; stepVegas++){
            long long used_time = calculate_time(QueensLV, repeat_num, queen_num,stepVegas);
            if(used_time < minTime){
                minTime = used_time;
                minStep = stepVegas;
            }
        }
	    minSteps[queen_num -queen_start] = minStep;
        printf("%.7fs |" ,minTime/(unitconversion*1.0));
    }
    printf("\nmixVegas minStep|");
    for(int i = 0; i <= queen_end-queen_start; i++)
        printf("  %7d  |", minSteps[i]);
    printf("\n");
    return 0;

}

long long calculate_time(func f,int run_times,int param_a,int param_b){
    std::vector<long long> used_times;
    for(int i = 0; i < run_times; i++){
        long long start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        f(param_a,param_b);
        long long end = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        used_times.push_back(end - start);
    }
    std::sort(used_times.begin(),used_times.end());
    return used_times[run_times/2];
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
            if(try_queen.empty() || i < start){
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
std::deque<int> legacy_backtree(int queen_num,int){
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
std::deque<int> leagcy_QueensLV(int queen_num,int){
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




