#include <iostream>
#include <iomanip>
#include <set>

#include <cstdlib>
#include <ctime>
#include <sys/time.h>

using namespace std;

set<int> col, diag45, diag135;

bool backtrace(int startRow, int *Try, int nums) {
    int i, j;
    i = startRow;

    int startCol = 0;
    while (i < nums) {
        for (j = startCol; j < nums; j++) {
            if (col.find(j) == col.end() && diag45.find(j - i) == diag45.end() && diag135.find(j + i) == diag135.end()) {
                break;
            }
        }

        if (i == startRow && j == nums) {
            return false;
        }

        if (j < nums) {
            startCol = 0;
            Try[i] = j;
            col.insert(j);
            diag45.insert(j - i);
            diag135.insert(j + i);
            i++;
        } else {
            i--;
            int preCol = Try[i];
            col.erase(preCol);
            diag45.erase(preCol - i);
            diag135.erase(preCol + i);
            startCol = preCol + 1;
        }
    }

    return true;
}

bool QueenLv(int nums, int stepVegas) {
    int k = -1, nb, i, j;

    col.clear();
    diag45.clear();
    diag135.clear();

    int *Try = new int[nums]();

    if (stepVegas == 0) {
        bool flag = backtrace(0, Try, nums);
        delete [] Try;
        return flag;
    }

    do {
        nb = 0;

        for (i = 0; i < nums; i++) {
            if ((col.find(i) == col.end()) && (diag45.find(i - k - 1) == diag45.end()) && (diag135.find(i + k + 1) == diag135.end())) {
                nb++;
                if (rand() % nb == 0)
                    j = i;
            }
        }

        if (nb > 0) {
            k++;
            Try[k] = j;
            col.insert(j);
            diag45.insert(j - k);
            diag135.insert(j + k);
        }

    } while (nb != 0 && k + 1 < stepVegas);

    if (nb > 0) {
        bool flag = backtrace(k + 1, Try, nums);
        delete [] Try;
        return flag;
    }
    else
        return false;
}

int main() {
    int stepVegas, minStep, nums;
    int i, replayNums;
    struct timeval start, end;
    double duration, minDuration;

    replayNums = 10;
    srand((unsigned int)time(NULL));

    for (nums = 12; nums <= 20; nums++) {
        minDuration = 100000;
        for (stepVegas = 0; stepVegas <= nums; stepVegas++) {
            gettimeofday(&start, NULL);
            for (i = 0; i < replayNums; i++) {
                while (!QueenLv(nums, stepVegas))
                    ;
            }
            gettimeofday(&end, NULL);
            duration = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            duration /= replayNums;

            if (duration < minDuration) {
                minDuration = duration;
                minStep = stepVegas;
            }
            // cout << "nums:" << nums << " stepVegas:" << stepVegas;
            // cout << " duration:" << setprecision(15) << duration / replayNums << endl;
        }
        cout << "nums:" << nums << " minStep:" << minStep << " minDuration:" << minDuration << "s" << endl;
    }

    return 0;
}