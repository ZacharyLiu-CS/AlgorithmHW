#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef double(*func)(double x);

double func1(double x) {
    return x*x*(-1.0);
}
double getRandom(double a, double b){
    double start = a < b? a:b;
    double end = a > b? a:b;
    return random()*(end - start)/RAND_MAX + start;
}
double HitorMiss(func f, long n, double start, double end) {
    long i, k = 0;
    double x, y;
    srand((unsigned int)time(NULL));
    for(i = 0; i <= n; i++) {
        x = getRandom(start,end);
        y = getRandom(f(start),f(end));
        if(abs(y) <= abs(f(x)))
            k++;
    }

    return (end - start) * abs(f(end) - f(start)) *k * 1.0 / n;
}

int main() {
    long n;
    printf("please input your number : \n");
    scanf("%ld", &n);
     printf("the result is : %lf\n", HitorMiss(func1, n, 3, 9));
    return 0;
}