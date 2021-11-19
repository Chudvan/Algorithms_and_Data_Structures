#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
int max(int a, int b){
	if(a>=b) return a;
	else return b;
}
void suff(char* substr, int* suffarr){ 					    //Ф-я побочной таблицы суффиксов
	int i, k, s, Lsubstr=strlen(substr);;
	suffarr[Lsubstr-1]=Lsubstr;
	for(i=Lsubstr-2;i>=0;i--){
		s=0;
		for(k=i;k>=0;k--){
			if(substr[k]==substr[Lsubstr-1-s])s++;
			else break;
		}
		suffarr[i]=s;
	}
}
void suffdisp(char* substr, int* suffarr, int* suffdisparr){	//Ф-я таблицы смещений суффиксов (хороших суффиксов)
	int k, j, Lsubstr=strlen(substr);;
	for(j=Lsubstr-1; j>=0; j--){
		for(k=Lsubstr-1; k>=0; k--){
			if(suffarr[k]==Lsubstr-1-j){suffdisparr[j]=Lsubstr-1-k; break;}
			if((suffarr[k]==k+1)&&(k+1<Lsubstr-1-j)){suffdisparr[j]=Lsubstr-1-k; break;}
			if(k==0) suffdisparr[j]=Lsubstr;
		}
	}
}
void stoptable(char* substr, int* stoptablearr){					    //Ф-я таблицы смещений букв (плохих символов)
	int i, Lsubstr=strlen(substr);
	for(i=0; i<26; i++){
		stoptablearr[i]=Lsubstr;
	}
	for(i=0; i<Lsubstr-1;i++){
		stoptablearr[(int)substr[i]-97]=Lsubstr-1-i;
	}
}
int BoyerMoore(char* str, char* substr){
	int Lsubstr, Lstr, i=0, k, j=Lsubstr-1, count=0, *stoptablearr, *suffdisparr, *suffarr;
	Lsubstr=strlen(substr); Lstr=strlen(str);
	stoptablearr=(int*)malloc(26*sizeof(int)); if(stoptablearr==NULL){printf("Ошибка. Не удалось выделить память."); exit(2);}
	suffdisparr=(int*)malloc(Lsubstr*sizeof(int)); if(suffdisparr==NULL){printf("Ошибка. Не удалось выделить память."); exit(2);}
	suffarr=(int*)malloc(Lsubstr*sizeof(int)); if(suffarr==NULL){printf("Ошибка. Не удалось выделить память."); exit(2);}
	suff(substr, suffarr);
	suffdisp(substr, suffarr, suffdisparr);
	stoptable(substr, stoptablearr);
	while(i<=(Lstr-Lsubstr)){
		for(k=i;k>0;k--)printf(" ");
		printf("%s", substr);
		for(k=Lstr-Lsubstr-i;k>0;k--)printf(" ");
		j=Lsubstr-1;
		while(substr[j]==str[j+i]){
			j--;
			if(j==-1){
				count++;
				break;
			}
		}
		if(j==-1){i+=max(stoptablearr[(int)str[i]-97]-(Lsubstr-1-j), suffdisparr[0]); printf("1\n");}
		else{i+=max(stoptablearr[(int)str[j+i]-97]-(Lsubstr-1-j), suffdisparr[j]); printf("\n");}
	}
	return count;
}
int main(){
	setlocale(LC_ALL, "");
	int i=0, count;
	char c, *substr, *str;
	substr=(char*)malloc(15*sizeof(char));
	if(substr==NULL){
		printf("Ошибка. Невозможно выделить память.");
		exit(2);
	}
	printf("Введи искомую подстроку (не более 15 символов):\n"); //Вводим искомую подстроку
	for(i=0;i<15;i++){
		if(((c=getchar())>=97)&&(c<=122))substr[i]=c;
		else if(c=='\n'){substr[i]='\0'; break;}
		else{
			printf("\nОшибка. Допустимый алфафит: a-z.\n");
			free(substr);
			exit(1);
		}
	}
	str=(char*)malloc(100*sizeof(char));
	if(substr==NULL){
		printf("Ошибка. Невозможно выделить память.");
		exit(2);
	}
	printf("Введи строку в которой будет осуществлён поиск (не более 100 символов):\n");
	for(i=0;i<100;i++){
		if(((c=getchar())>=97)&&(c<=122)) str[i]=c;
		else if(c=='\n') {str[i]='\0'; break;}
		else{
			printf("\nОшибка. Допустимый алфафит: a-z.\n");
			free(substr);
			exit(1);
		}
	}
	count=BoyerMoore(str, substr);
	printf("Найдено совпадений: %d\n", count);
}
