#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10000
int isPrime[N], rabPrime[N];

void check(int val) {
    int i;
    for (i = val * 2; i < N; i += val)
        isPrime[i] = 0;
}

void realPrime() {
    int max = (int) sqrt(N), i, pre = 0;
    for (i = 0; i < N; i++)
        isPrime[i] = 1;
    isPrime[0] = isPrime[1] = 0;
    while (1) {
        i = pre + 1;
        while (!isPrime[i])
            i++;
        pre = i;
        if (i <= max)
            check(i);
        else
            break;
    }
}

int Btest(int a, int n) {
    int s = 0, t = n - 1, x;
    int i;

    while(t % 2 == 0) {
        s++;
        t /= 2;
    }

    x = 1;
    while (t > 0) {
        if (t % 2 == 1)
            x = (x * a) % n;
        t /= 2;
        a = (a * a) % n;
    }

    if(x == 1 || x == n - 1)
        return 1;

    for(i = 1; i < s; i++) {
        x = (x * x) % n;

        if(x == n - 1)
            return 1;
    }

    return 0;
}

int MillRab(int n) {
    int a = 2 + rand() % (n - 3);
    return Btest(a, n);
}

int RepeatMillRab(int n, int k) {
    int i;
    for(i = 0; i < k; i++) {
        if(!MillRab(n))
            return 0;
    }
    return 1;
}

void printPrimes() {
    int n = 5, i;
    // printf("2 3 ");

    for (i = 0; i < N; i++)
        rabPrime[i] = 0;
    rabPrime[2] = rabPrime[3] = 1;

    while(n <= N) {
        if(RepeatMillRab(n, log10(n))) {
            // printf("%d ", n);
            rabPrime[n] = 1;
        }
        n += 2;
    }
    // printf("\n");
}

int main() {
    srand((unsigned int)time(NULL));
    printPrimes();
    realPrime();

    int i;
    int falseCount = 0, count = 0;
    for (i = 0; i < N; i++) {
        if (rabPrime[i]) {
            count++;
            if (!isPrime[i])
                falseCount++;
        }
    }
    printf("false count: %d, millrab count: %d, false ratio: %lf\n", falseCount, count, falseCount * 1.0 / count);
    return 0;
}