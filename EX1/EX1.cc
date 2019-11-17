#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double Darts(long n) {
    long i, k = 0;
    double x, y;
    srand((unsigned int)time(NULL));

    for(i = 0; i <= n; i++) {
        x = rand() * 1.0 / RAND_MAX;
        y = x;

        if((x * x + y * y) <= 1)
            k++;
    }
    return 4.0 * k / n;
}

int main() {
    long n;
    while(true){
        printf("please input your number: ");
        scanf("%ld", &n);
        printf("the result is : %lf\n", Darts(n));
    }
    return 0;
}