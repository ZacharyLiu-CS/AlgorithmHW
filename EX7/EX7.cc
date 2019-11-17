#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#define N 10000000

int val[N],ptr[N];
int head=0;

int find(int val[],int length,int x){
	int i=0,flag=0;
	for(;i<length;i++){
		if(val[i]==x){
			flag=1;
			break;
		}
	}
	if(flag==1)
		return i;
	else
		return -1;
}

void init(int n){
	int i=0;
	for(;i<n;i++)
		val[i]=i;
	//shuffle
	int j=0,tmp=0;
	srand(time(0));
	for(i=0;i<n;i++){
		j=rand()%n;
		tmp=val[i];
		val[i]=val[j];
		val[j]=tmp;
	}
	//set ptr[],sort
	for(i=0;i<n;i++){
		ptr[i]=find(val,n,val[i]+1);
	}
	head=find(val,n,0);

}

int search(int x,int i){
	while(x > val[i])
		i=ptr[i];
	return i;
}

int A(int x){
	return search(x,head);
}

int B(int x,int n){
	int i=head;
	int max=val[i];
	int j=0,y=0;
	for (j = 0; j < sqrt(n); ++j){
		y=val[j];
		if(max < y && y<=x){
			i=j;
			max=y;
		}		
	}
	return search(x,i);
}

int C(int x,int n){
	int i=head;
	int max=val[i];
	int k=0,j=0,y=0;
	srand(time(0));
	for (k = 0; k < sqrt(n); ++k){
		j=rand()%n;
		y=val[j];
		if(max < y && y<=x){
			i=j;
			max=y;
		}		
	}
	return search(x,i);
}
int D(int x,int n){
	srand(time(0));
	int i=rand()%n;
	int y=val[i];
	if(x<y)
		return search(x,head);
	else if(x>y)
		return search(x,ptr[i]);
	else
		return i;
}



int main() {
	int n=0,x=0;
	printf("please input n=");
	scanf("%d",&n);
	init(n);
	clock_t start,end;
	int index=-1;
	while(true){
		printf("please input the number you want to search (0~n-1):");
		scanf("%d",&x);

		index=-1;
		start=clock();
		index=A(x);
		end=clock();
		printf("A: its index is %d. use time: %ld ms\n",index,end-start);

		index=-1;
		start=clock();
		index=B(x,n);
		end=clock();
		printf("B: its index is %d. use time: %ld ms\n",index,end-start);

		index=-1;
		start=clock();
		index=C(x,n);
		end=clock();
		printf("C: its index is %d. use time: %ld ms\n",index,end-start);

		index=-1;
		start=clock();
		index=D(x,n);
		end=clock();
		printf("D: its index is %d. use time: %ld ms\n",index,end-start);
}

	return 0;
}
