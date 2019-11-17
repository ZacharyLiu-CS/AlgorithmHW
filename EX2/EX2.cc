#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef double(*func)(double x);

double func1(double x) {
    return sqrt(1 - x * x);
}

double HitorMiss(func f, long n) {
    long i, k = 0;
    double x, y;
    srand((unsigned int)time(NULL));

    for(i = 0; i <= n; i++) {
        x = rand() * 1.0 / RAND_MAX;
        y = rand() * 1.0 / RAND_MAX;

        if(y <= f(x))
            k++;
    }

    return k * 1.0 / n;
}

int main() {
    long n;
    while(true){
        printf("please input your number : ");
        scanf("%ld", &n);
        printf("the result is :%.10lf\n", 4 * HitorMiss(func1, n));
    }
    return 0;
}