#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
void ft4(int a, int *b, int n, int **B){
    int A[100], i=0, t=n-1, k=0, e=0, z=0;
    if(a>1){
		for(i=0;a!=1;i++){
			A[i]=a%2;
			if(A[i]==1){
				e++;
				if((i>0)&&(A[i-1]==0)){ z=0;}
				if(e==3) *b=1;
			}
			if(A[i]==0){
				z++;
				if((i>0)&&(A[i-1]==1)){ e=0;}
				if(z==2) *b=1;
			}
			a=a/2;
	    }
		A[i]=1; //��������, ��� i - ��������� ����������� ������� ������� A[]
	}
	e++; if(e==3) *b=1;
	if((*b)==0){
		if(i>0){ //�������, ������� ��������� ������ n=1
			while(k<=i){
				*((*B)+t)=A[k];		
				k++; t--;
			}
		}
		else{ //�������, ��� ������ n=1
			if(a==1) *((*B)+t)=1;
		}
	}
}
void ft3(int a, int *b){ //�-� ������� ���������� b=0, ���� ����� a - ������������������ ��� '111' � '00'
    int A[100], i, e=0, z=0;
    if(a>1){
		for(i=0;a!=1;i++){
			A[i]=a%2;
			if(A[i]==1){
				e++;
				if((i>0)&&(A[i-1]==0)){ z=0;}
				if(e==3) *b=1;
			}
			if(A[i]==0){
				z++;
				if((i>0)&&(A[i-1]==1)){ e=0;}
				if(z==2) *b=1;
			}
			a=a/2;
	    }
	}
	e++; if(e==3) *b=1;
}
void ft2(n){
	int i, t, b=0, *A, B[n];
	for(i=0;i<n;i++){
		B[i]=0;
	}
	double c=pow(2,n), d=pow(2,n-2);
	for(i=d;i<c;i++){
		A=(int *) calloc(n, sizeof(int));
		if(A==NULL){
			printf("������. ���������� �������� ������.\n");
			exit(1);
		}
		ft4(i, &b, n, &A);
		if(b==0){
			for(t=0;t<n;t++){
				printf("%d", A[t]);
				B[t]+=*(A+t);
			}
			printf("\n");
		}
		b=0;
	}
	for(i=0;i<n;i++)printf("%d ", B[i]);
	printf(" - ����� ���� �������������������.\n");
	free(A);
}
void ft1(n){
	int i, b=0, s=0;
	double c=pow(2,n), d=pow(2,n-2);
	for(i=d;i<c;i++){
		ft3(i, &b);
		if(b==0)s++;
		b=0;
	}
	printf("����� %d ������������������� ������������� ��������:\n", s);
}



void f(int *A){
		for(int i=0; i<10; i++) A[i]=i;
}




int main(){
	setlocale(LC_ALL, "");
	int n; printf("����� ���-�� ��������� � ������������������ n: "); scanf("%d", &n);
	if(n<1){
		while (n<1){
			printf("������. � ������������������ n ������ ���� �� ����� ������ ��������.\n����� ���-�� ��������� � ������������������ n: "); scanf("%d", &n);
		}
	}
  	ft1(n);
	ft2(n);
}
