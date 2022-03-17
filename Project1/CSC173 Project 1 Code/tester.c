//
// Created by YUFEI ZHAO
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "nfa.h"
#include "dfa.h"

int main(){

    //DFA that recognizes string happy
    printf("This DFA recognizes string happy.");
    DFA d1=new_DFA(6);
    DFA_set_transition(d1, 0, 'h',1);
    DFA_set_transition(d1, 1, 'a',2);
    DFA_set_transition(d1, 2, 'p',3);
    DFA_set_transition(d1, 3, 'p',4);
    DFA_set_transition(d1, 4, 'y',5);
    DFA_set_accepting(d1, 5, true);
    DFA_print(d1);
    printf("size of DFA: %i\n", DFA_get_size(d1));
    DFA_free(d1);


    //DFA that recognizes any string that starts with three 9's; i.e: 999xxxxxx
    printf("\nThis DFA recognizes any string that starts with three 9's.");
    DFA d2=new_DFA(4);
    DFA_set_transition(d2, 0, '9', 1);
    DFA_set_transition(d2, 1, '9', 2);
    DFA_set_transition(d2, 2, '9', 3);
    DFA_set_transition_all(d2, 3, 3);
    DFA_set_accepting(d2, 3, true);
    DFA_print(d2);
    DFA_free(d2);


    //DFA that recognizes binary input with an even number of 1's
    printf("\nThis DFA recognizes binary input with an even number of 1's.");
    DFA d3=new_DFA(2);
    DFA_set_transition(d3, 0, '1', 1);
    DFA_set_transition(d3, 0, '0', 0);
    DFA_set_transition(d3, 1, '1', 0);
    DFA_set_transition(d3, 1, '0', 1);
    DFA_set_accepting(d3, 0, true);
    DFA_print(d3);
    DFA_free(d3);



    //DFA that recognizes binary input with an odd number of 0’s and an even number of 1’s
    printf("\nThis DFA recognizes binary input with an odd number of 0’s and an even number of 1’s.");
    DFA d4=new_DFA(4);
    DFA_set_transition(d4, 0, '0', 1);
    DFA_set_transition(d4, 0, '1', 3);
    DFA_set_transition(d4, 1, '0', 0);
    DFA_set_transition(d4, 1, '1', 2);
    DFA_set_transition(d4, 2, '0', 3);
    DFA_set_transition(d4, 2, '1', 1);
    DFA_set_transition(d4, 3, '0', 2);
    DFA_set_transition(d4, 3, '1', 0);
    DFA_set_accepting(d4, 1, true);
    DFA_print(d4);
    DFA_free(d4);


    //Design Part:
    //DFA that recognizes binary input which starts with 1 and ends with 0.
    printf("\nThis DFA recognizes binary input which starts with 1 and ends with 0.");
    DFA d5=new_DFA(3);
    DFA_set_transition(d5, 0, '1', 1);
    DFA_set_transition(d5, 1, '1', 1);
    DFA_set_transition(d5, 1, '0', 2);
    DFA_set_transition(d5, 2, '1', 1);
    DFA_set_transition(d5, 2, '0', 2);
    DFA_set_accepting(d5, 2, true);
    DFA_print(d5);
    DFA_free(d5);


    //NFA that recognizes strings ending in ing
    printf("\nThis NFA recognizes strings ending in ing.");
    NFA n1=new_NFA(4);
    NFA_add_transition_all(n1, 0, 0);
    NFA_add_transition(n1, 0, 'i', 1);
    NFA_add_transition(n1, 1, 'n', 2);
    NFA_add_transition(n1, 2, 'g', 3);
    NFA_set_accepting(n1, 3, true);
    NFA_print(n1);
    DFA trans1=NFA_translator(n1);
    printf("\nEnter you input again: ");
    DFA_print(trans1);
    printf("Size of NFA: %i\n", NFA_get_size(n1));
    NFA_free(n1);

    //NFA that recognizes strings containing ing
    printf("\nThis NFA recognizes strings containing ing.");
    NFA n2=new_NFA(4);
    NFA_add_transition_all(n2, 0, 0);
    NFA_add_transition(n2, 0, 'i', 1);
    NFA_add_transition(n2, 1, 'n', 2);
    NFA_add_transition(n2, 2, 'g', 3);
    NFA_add_transition_all(n2, 3, 3);
    NFA_set_accepting(n2, 3, true);
    NFA_print(n2);
    DFA trans2=NFA_translator(n2);
    printf("\nEnter you input again: ");
    DFA_print(trans2);


    //NFA that recognizes strings more than one a,g,h,i,o,s,t,or w,or more than two n’s
    printf("\nThis NFA recognizes strings more than one a,g,h,i,o,s,t,or w,or more than two n’s.");
    NFA n3=new_NFA(20);
    NFA_add_transition_all(n3, 0, 0);
    NFA_add_transition(n3, 0, 'a', 1);
    NFA_add_transition(n3, 0, 'g', 3);
    NFA_add_transition(n3, 0, 'h', 5);
    NFA_add_transition(n3, 0, 'i', 7);
    NFA_add_transition(n3, 0, 'n', 9);
    NFA_add_transition(n3, 0, 'o', 12);
    NFA_add_transition(n3, 0, 's', 14);
    NFA_add_transition(n3, 0, 't', 16);
    NFA_add_transition(n3, 0, 'w', 18);
    NFA_add_transition(n3, 1, 'a', 2);
    NFA_add_transition(n3, 3, 'g', 4);
    NFA_add_transition(n3, 5, 'h', 6);
    NFA_add_transition(n3, 7, 'i', 8);
    NFA_add_transition(n3, 9, 'n', 10);
    NFA_add_transition(n3, 10, 'n', 11);
    NFA_add_transition(n3, 12, 'o', 13);
    NFA_add_transition(n3, 14, 's', 15);
    NFA_add_transition(n3, 16, 't', 17);
    NFA_add_transition(n3, 18, 'w', 19);
    NFA_add_transition_str(n3, 1, "bcdefghijklmnopqrstuvwxyz", 1);
    NFA_add_transition_str(n3, 3, "abcdefhijklmnopqrstuvwxyz", 3);
    NFA_add_transition_str(n3, 5, "abcdefgijklmnopqrstuvwxyz", 5);
    NFA_add_transition_str(n3, 7, "abcdefghjklmnopqrstuvwxyz", 7);
    NFA_add_transition_str(n3, 9, "abcdefghijklmopqrstuvwxyz", 9);
    NFA_add_transition_str(n3, 10, "abcdefghijklmopqrstuvwxyz", 10);
    NFA_add_transition_str(n3, 12, "abcdefghijklmnpqrstuvwxyz", 12);
    NFA_add_transition_str(n3, 14, "abcdefghijklmnopqrtuvwxyz", 14);
    NFA_add_transition_str(n3, 16, "abcdefghijklmnopqrsuvwxyz", 16);
    NFA_add_transition_str(n3, 18, "abcdefghijklmnopqrstuvxyz", 18);
    NFA_set_accepting(n3, 2, true);
    NFA_set_accepting(n3, 4, true);
    NFA_set_accepting(n3, 6, true);
    NFA_set_accepting(n3, 8, true);
    NFA_set_accepting(n3, 11, true);
    NFA_set_accepting(n3, 13, true);
    NFA_set_accepting(n3, 15, true);
    NFA_set_accepting(n3, 17, true);
    NFA_set_accepting(n3, 19, true);
    NFA_print(n3);


    //Design Part
    //NFA that recognizes strings ending in either on or er
    printf("\nThis NFA recognizes strings ending in either on or er.");
    NFA n4=new_NFA(5);
    NFA_add_transition_all(n4, 0, 0);
    NFA_add_transition(n4, 0, 'o', 1);
    NFA_add_transition(n4, 1, 'n', 2);
    NFA_add_transition(n4, 0, 'e', 3);
    NFA_add_transition(n4, 3, 'r', 4);
    NFA_set_accepting(n4, 2, true);
    NFA_set_accepting(n4, 4, true);
    NFA_print(n4);


    //return 0;
}

