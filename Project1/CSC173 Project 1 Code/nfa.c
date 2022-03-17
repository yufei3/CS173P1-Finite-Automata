//
// Created by YUFEI ZHAO
//
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "nfa.h"
#include "dfa.h"
#include "LinkedList.h"
#define Size 1

struct NFA{
    int nstates;
    IntHashSet ** table;
    bool* acceptingStates;
    LinkedList Nlabels;
};

NFA new_NFA(nstates){
    NFA this = (NFA)malloc(sizeof(struct NFA));
    this->nstates=nstates;
    IntHashSet** Table=(IntHashSet**)malloc(sizeof(IntHashSet*)*nstates);
    bool* accepted=(bool*)malloc(sizeof(bool)*nstates);

    LinkedList labels=new_LinkedList();
    this->Nlabels=labels;

    for (int i=0; i<nstates; i++){
        accepted[i]=false;
        Table[i]=(IntHashSet*)malloc(sizeof(IntHashSet)*128);
    }

    for (int i=0; i<nstates; i++){ //num of rows: nstates
        for (int j=0; j<128; j++){ //num of columns: 128
            Table[i][j]=new_IntHashSet(nstates); //the set of transitionTo states is empty initially
        }
    }
    this->table=Table;
    this->acceptingStates=accepted;
    return this;
}

void NFA_free(NFA nfa){
    if (nfa==NULL){
        return;
    }
    for (int i=0; i<nfa->nstates; i++){
        for (int j=0; j<128; j++){
            nfa->table[i][j]=NULL;
        }
    }
    for (int i=0; i<nfa->nstates; i++){
        nfa->acceptingStates[i]=false;
    }
    free(nfa);
}

int NFA_get_size(NFA nfa){
    return nfa->nstates;
}

Set NFA_get_transitions(NFA nfa, int state, char sym){
    return nfa->table[state][(int)sym];
}
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    IntHashSet_insert(nfa->table[src][(int)sym], dst);
    LinkedList_add_at_front(nfa->Nlabels, sym);
}
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    for (int i=0; i<strlen(str); i++){
        IntHashSet_insert(nfa->table[src][(int)str[i]], dst);
        LinkedList_add_at_front(nfa->Nlabels, str[i]);
    }
}
void NFA_add_transition_all(NFA nfa, int src, int dst){
    for (int i=0; i<128; i++){
        IntHashSet_insert(nfa->table[src][i], dst);
        LinkedList_add_at_front(nfa->Nlabels, (char)i);
    }
}

void NFA_set_accepting(NFA nfa, int state, bool value){
    nfa->acceptingStates[state]=value;
}

bool NFA_get_accepting(NFA nfa, int state){
    return nfa->acceptingStates[state];
}

bool NFA_execute(NFA nfa, char *input){
    IntHashSet current=new_IntHashSet(nfa->nstates);
    IntHashSet_insert(current, 0); //current set of initial states; starts with only state 0

    //if current is empty, that means no next steps. Reject the string
    for (int i=0; i<strlen(input) && !IntHashSet_isEmpty(current); i++){
        IntHashSetIterator iterator = IntHashSet_iterator(current);
        IntHashSet temp=new_IntHashSet((nfa->nstates)); //store the next set of states
        while (IntHashSetIterator_hasNext(iterator)){ //each state in current set
            int state = IntHashSetIterator_next(iterator);
            //update the next set of states
            if (NFA_get_transitions(nfa, state, input[i])!=NULL){
                IntHashSet_union(temp, NFA_get_transitions(nfa, state, input[i]));
            }
            else return false;
        }

        current=temp; //replace the current initial set with the next initial set
        if (IntHashSet_isEmpty(current)){
            break;
        }
        //IntHashSet_free(temp);
        free(iterator);
    }

    if (IntHashSet_isEmpty(current)){
        return false;
    }
    IntHashSetIterator iterator = IntHashSet_iterator(current);
    while (IntHashSetIterator_hasNext(iterator)){
        int state = IntHashSetIterator_next(iterator);
        if (NFA_get_accepting(nfa, state)){
            return true;
        }
    }
    return false;
}

void NFA_print(NFA nfa){
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

    if (NFA_execute(nfa, str)){
        printf("\nYour string is accepted.\n");
    }
    else {
        printf("\nYour string is not accepted.\n");
    }
    free(str);
}


DFA NFA_translator(NFA nfa) {
    DFA dfa = new_DFA((int) pow((double) 2, (double) nfa->nstates));
    //when we turn NFA to DFA, the new DFA states are sets of NFA states
    //we use this dfaState to represent the new DFA states
    int dfaState = 0;

//    LinkedList acceptState=new_LinkedList();
//    for (int i=0; i<nfa->nstates; i++){
//        if (NFA_get_accepting(nfa, i)==true){
//            LinkedList_add_at_front(acceptState, i);
//        }
//    }

    /*IntHashSet S=new_IntHashSet(nfa->nstates);*/
    LinkedList labels = nfa->Nlabels;
    LinkedList transToSet = new_LinkedList(); //it contains several sets of states as nodes
    LinkedList PopSet = new_LinkedList(); //it contains sets of states that have already used as the set of src states

    IntHashSet i = new_IntHashSet(nfa->nstates);
    IntHashSet_insert(i, 0);  //it is a set that only contains the initial state
    LinkedList_add_at_front(transToSet, i);


    while (!LinkedList_isEmpty(transToSet)) {
        LinkedListIterator iteratorLabels = LinkedList_iterator(labels);
        //find a set of NFA states that has not used as S <initial set of states> in the conversion process
        IntHashSet currentSrc = LinkedList_pop(transToSet);
        while (LinkedList_contains(PopSet, currentSrc)) {
            IntHashSet currentSrc = LinkedList_pop(transToSet); //get the next set of states
        }
        LinkedList_add_at_end(PopSet, currentSrc);
        //If you want to ses the subset construction, you can uncomment the next line
        //printf("\nState %i: ", dfaState);
        IntHashSet_print(currentSrc);

        //for each label, use get transition function to find its set of dst states from the set of src states
        //and add all of the sets of dst states to translateToSet
        //in order to find the next set of initial states

        //go through each label, for each label go through all src states to find all dst states
        while (LinkedListIterator_hasNext(iteratorLabels)) { //find the dst states with all possible labels
            //temp: a set to store all possible dst states for single label with this set of src-set
            IntHashSet temp = new_IntHashSet(nfa->nstates);
            char label = LinkedListIterator_next(iteratorLabels);

            IntHashSetIterator currentIterator = IntHashSet_iterator(currentSrc);
            while (IntHashSetIterator_hasNext(currentIterator)) { //look every src states in the current src-set
                int src = IntHashSetIterator_next(currentIterator);
                IntHashSet_union(temp, NFA_get_transitions(nfa, src, label));
            }

            bool x=false; bool y=false;
            LinkedListIterator trans=LinkedList_iterator(transToSet);
            while (LinkedListIterator_hasNext(trans)) {
                IntHashSet pointer1=LinkedListIterator_next(trans);
               if (IntHashSet_equals(pointer1, temp)) {
                   x=true;
                   break;
               }
            }
            LinkedListIterator pops=LinkedList_iterator(PopSet);
            while (LinkedListIterator_hasNext(pops)) {
                IntHashSet pointer2=LinkedListIterator_next(pops);
                if (IntHashSet_equals(pointer2, temp)) {
                    y=true;
                    break;
                }
            }

            bool accept=false;
            IntHashSetIterator tempiter=IntHashSet_iterator((temp));
            while (IntHashSetIterator_hasNext(tempiter)){
                int state=IntHashSetIterator_next(tempiter);
                if (NFA_get_accepting(nfa, state)){
                    accept=true;
                    break;
                }
            }

            //if this subset of states is new, we add the subset to transToSet
            //then we add the transitions to DFA
            if (!x && !y && !IntHashSet_isEmpty(temp)) {
                LinkedList_add_at_end(transToSet, temp);
                //if how_many_states_later=0, then temp will become next S (1 state later)
                //if how_many_states_later=1, then temp will the next next S...(2 states later)
                int how_many_states_later = 0;
                bool tf = true;
                //find size of the transToSet LinkedList
                while (tf) {
                    if (IntHashSet_equals(LinkedList_elementAt(transToSet, how_many_states_later), temp)) {
                        break;
                    } else how_many_states_later++;
                }
                DFA_set_transition(dfa, dfaState, label, dfaState + how_many_states_later + 1);
                DFA_set_accepting(dfa, dfaState + how_many_states_later + 1, accept);
            }

            else if (!IntHashSet_isEmpty(temp) && (x||y)) {
                int to = 0;
                LinkedListIterator findTo = LinkedList_iterator(PopSet);
                while (LinkedListIterator_hasNext(findTo)) {
                    IntHashSet pointer = LinkedListIterator_next(findTo);
                    if (IntHashSet_equals(pointer, temp)) {
                        DFA_set_transition(dfa, dfaState, label, to);
                        DFA_set_accepting(dfa, to, accept);
                        break;
                    } else to++;
                }

            }
        }

        dfaState++;

    }
    printf("\nNumber of states in DFA: %i", dfaState);
    return dfa;
}





