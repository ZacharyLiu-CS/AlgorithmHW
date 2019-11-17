#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef int (*search_func) (int);

int *val, *ptr, n, head;
int *choosen;

int search(int x, int i) {
    while(x > val[i] && i != -1)
        i = ptr[i];

    return i;
}

int a(int x) {
    return search(x, head);
}

int b(int x) {
    int i = head, j;
    int max = val[i], y;
    int sqrtN = (int) sqrt(n);

    for (j = 0; j < sqrtN; j++) {
        y = val[j];

        if (y > max && y <= x) {
            i = j;
            max = y;
        }
    }

    return search(x, i);
}

void prepareForC(int l) {
    int *used = (int *) malloc(sizeof(int) * n);
    memset(used, 0, sizeof(int) * n);

    int i, choose;

    for (i = 0; i < l; i++) {
        choose = rand() % n;

        if (used[choose] == 0) {
            used[choose] = 1;
            choosen[i] = choose;

        } else {
            do {
                choose++;

                if (choose >= n)
                    choose %= n;
            } while(used[choose] == 1);

            used[choose] = 1;
            choosen[i] = choose;
        }
    }

    free(used);
}

int c(int x) {
    int i = head, j;
    int max = val[i], y;
    int sqrtN = (int) sqrt(n);

    prepareForC(sqrtN);
    for (j = 0; j < sqrtN; j++) {
        y = val[choosen[j]];

        if (y > max && y <= x) {
            i = choosen[j];
            max = y;
        }
    }

    return search(x, i);
}

int d(int x) {
    int i = rand() % n;
    int y = val[i];

    if (x < y)
        return search(x, head);

    else if (x > y)
        return search(x, ptr[i]);

    else
        return i;
}

void initArrays() {
    int i, j, k, tmp;
    for (i = 0; i < n; i++) {
        val[i] = i;
    }

    for (i = 0; i < n / 2; i++) {
        j = rand() % n;
        k = rand() % n;

        tmp = val[j];
        val[j] = val[k];
        val[k] = tmp;
    }

    int pre;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (val[j] == i)
                break;
        }
        if (i == 0) {
            head = j;
            pre = head;
        }
        else {
            ptr[pre] = j;
            pre = j;
        }
    }
    ptr[pre] = -1;

}

void run(search_func func, int replayCount) {
    int i;
    for (i = 0; i < replayCount; i++) {
        int x = rand() % n;
        func(x);
    }
}

int main() {
    struct timeval start, finish;
    double duration;

    int i, replayCount;
    printf("Input array size:\n");
    scanf("%d", &n);
    printf("Input replay count:\n");
    scanf("%d", &replayCount);
    srand((unsigned int)time(NULL));

    val = (int *) malloc(sizeof(int) * n);
    ptr = (int *) malloc(sizeof(int) * n);
    choosen = (int *) malloc(sizeof(int) * n);

    initArrays();

    gettimeofday(&start, NULL);
    run(a, replayCount);
    gettimeofday(&finish, NULL);

    duration = (finish.tv_sec - start.tv_sec) + (finish.tv_usec - start.tv_usec) / 1000000.0;
    duration /= replayCount;
    printf("Algorithm A run time: %lfs\n", duration);

    gettimeofday(&start, NULL);
    run(b, replayCount);
    gettimeofday(&finish, NULL);

    duration = (finish.tv_sec - start.tv_sec) + (finish.tv_usec - start.tv_usec) / 1000000.0;
    duration /= replayCount;
    printf("Algorithm B run time: %lfs\n", duration);

    gettimeofday(&start, NULL);
    run(c, replayCount);
    gettimeofday(&finish, NULL);

    duration = (finish.tv_sec - start.tv_sec) + (finish.tv_usec - start.tv_usec) / 1000000.0;
    duration /= replayCount;
    printf("Algorithm C run time: %lfs\n", duration);

    gettimeofday(&start, NULL);
    run(d, replayCount);
    gettimeofday(&finish, NULL);

    duration = (finish.tv_sec - start.tv_sec) + (finish.tv_usec - start.tv_usec) / 1000000.0;
    duration /= replayCount;
    printf("Algorithm D run time: %lfs\n", duration);

    free(val);
    free(ptr);
    free(choosen);
    return 0;
}