#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#define PI acos(-1)


template <typename T>
int SetCount(vector<T> X) {
    int k = 0;
    set<T> S;
    while(S.insert(X[rand()%X.size()]).second)k++;
    return 2*k*k/PI;
}

int main() {
    vector<int>X;
	int set_size, repeat_count;
	printf("please input size of set : \n");
	scanf("%d",&set_size);
	printf("please input replay count : \n");
    scanf("%d",&repeat_count);
	for (int i = 0; i < set_size; i++)		//init set x
		X.push_back(i);
	
	int sum = 0;
    srand((unsigned int)time(NULL));
	for (int i = 0; i < repeat_count; i++)
		sum += SetCount(X);
	printf("the result is %d \n",  sum / repeat_count );
	return 0;
}
