/*
 * project1.c
 *
 *  Created on: Sep 9, 2020
 *      Author: rainyzhao
 */
#include<stdio.h>
#include<string.h>

//dfa tells the number associated string end in which state
int dfa=0;

//start state of 1a: recognize h
void DAstart(char c){
	if (c=='h'){
		dfa=1;
	}
	else dfa=-1;
}
//state1 of 1a: recognize a
void DAstate1(char c){
	if (c=='a'){
		dfa=2;
	}
	else dfa=-1;
}
//state2 of 1a: recognize p
void DAstate2(char c){
	if (c=='p'){
		dfa=3;
	}
	else dfa=-1;
}
//state3 of 1a: recognize p
void DAstate3(char c){
	if (c=='p'){
		dfa=4;
	}
	else dfa=-1;
}
//state4 of 1a: recognize y
void DAstate4(char c){
	if (c=='y'){
		dfa=5;
	}
	else dfa=-1;
}

//return 0 if reject, return 1 if accept
int AcceptHappy(char str[]){
	int i;
	int len=strlen(str);

	for (i=0; i<len; i++){
		if (dfa==0){
			DAstart(str[i]);
		}
		else if (dfa==1){
			DAstate1(str[i]);
		}
		else if (dfa==2){
			DAstate2(str[i]);
		}
		else if (dfa==3){
			DAstate3(str[i]);
		}
		else if (dfa==4){
			DAstate4(str[i]);
		}
		else return 0; //if dfa=-1, directly reject
	}
	if (dfa!=-1){ //test whether the last character is y
		return 1;
	}
	else return 0;
}



//int main(){
//
////  /*1a. Exactly 'happy'*/
////	char str[]="happy";
////	if (AcceptHappy(str)==1){
////		printf("Accepted");
////	}
////	else printf("Not Accepted");
//
//	DFA d1=new_DFA(6);
//	DFA_setTransition();



//}
