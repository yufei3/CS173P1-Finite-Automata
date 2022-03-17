//
// Created by YUFEI ZHAO
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dfa.h"
#define Size 1

struct DFA{
    int nstates;
    int ** table;
    bool* acceptingStates;
};

DFA new_DFA(nstates){
//    printf("sizeof(int)=%ld, sizeof(int *)=%ld, sizeof(bool)=%ld\n",
//     sizeof(int), sizeof(int *), sizeof(bool));
//    printf("table row=%d, table column=%d, accept length=%d\n",
//           sizeof(int*)*nstates, sizeof(int)*128, sizeof(bool)*nstates);
    DFA this = (DFA)malloc(sizeof(struct DFA));
    this->nstates=nstates;
    //Table: r=nstates, c=128
    int** Table=(int**)malloc(sizeof(int*)*nstates);
    bool* accepted=(bool*)malloc(sizeof(bool)*nstates);
    for (int i=0; i<nstates; i++){
        accepted[i]=false;
        Table[i]=(int*)malloc(sizeof(int)*128);
    }
    for (int i=0; i<nstates; i++){ //num of rows: nstates
        for (int j=0; j<128; j++){ //num of columns: 128
            Table[i][j]=-1;
        }
    }
    this->table=Table;
    this->acceptingStates=accepted;
    return this;
}

void DFA_free(DFA dfa){
    if (dfa==NULL){
        return;
    }
    for (int i=0; i<dfa->nstates; i++){
        for (int j=0; j<128; j++){
            dfa->table[i][j]=-1;
        }
    }
    for (int i=0; i<dfa->nstates; i++){
        dfa->acceptingStates[i]=false;
    }
    free(dfa);
}

int DFA_get_size(DFA dfa){
    int size=dfa->nstates;
    return size;
}

int DFA_get_transition(DFA dfa, int src, char sym){
    return dfa->table[src][(int)sym];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst){
    dfa->table[src][(int)sym]=dst;
}

void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){
    for (int i=0; i<sizeof(str); i++){
        dfa->table[src][(int)str[i]]=dst;
    }
}

void DFA_set_transition_all(DFA dfa, int src, int dst){
    for (int i=0; i<128; i++){
        dfa->table[src][i]=dst;
    }
}

void DFA_set_accepting(DFA dfa, int state, bool value){
    dfa->acceptingStates[state]=value;
}

bool DFA_get_accepting(DFA dfa, int state){
    return dfa->acceptingStates[state];
}

bool DFA_execute(DFA dfa, char *input){
    int currentS=0; //current state; starts with initial state 0
    for (int i=0; i<strlen(input) && currentS>=0; i++){
        currentS=DFA_get_transition(dfa, currentS, input[i]);
        if (currentS<0){
            break;
        }
        //printf("From state: %d, To state: %d\n", i, currentS);
    }

    if (currentS<0 || DFA_get_accepting(dfa, currentS)==0){
        return false;
    }
    else return true;
}

void DFA_print(DFA dfa){
    //read input of unknown length:
    int current_size=Size;
    char *str=malloc(current_size); //let's keep str pointing to beginning of string...
    char *next_read=str; //and next_read pointing to where next character should go
    printf("\nEnter your string (enter 'quit' to exit): ");
    fgets(next_read, current_size, stdin);
    while (str[strlen(str)-1] != '\n'){ //if we got the whole string, the last char will be '\n'
        //printf("\nsize: %d, string: %s", strlen(str), str); //test the string that is already read
        current_size=strlen(str)+Size;
        str=realloc(str,current_size);
        next_read=str+strlen(str);
        fgets(next_read, Size+1, stdin);
    }
    str[strlen(str)-1]='\0';


    if (strcmp(str, "quit")==0){
        printf("\nYou exit.\n");
        return;
    }
    printf("Your input string is %s", str);

    if (DFA_execute(dfa, str)){
        printf("\nYour string is accepted.\n");
    }
    else {
        //printf("length: %s", strlen(str));
        printf("\nYour string is not accepted.\n");
    }
    free(str);
}

