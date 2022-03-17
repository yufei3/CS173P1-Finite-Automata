(a)Group Member: Yufei Zhao

(b)How I build my project: 
In this project, I created a data structure named DFA in dfa.c, and implemented the methods of DFA, such as DFA_get_transition, DFA_set_transition, and etc. I created a data structure named NFA in nfa.c, and implemented the methods as well. Besides, I implemented my translator that takes an NFA as its only parameter and returns a new instance of DFA, which accepts same language as the original NFA. 
My ideas: 
To create finite automaton data structure, I identify some characteristics of a automaton: transition table, number of states, and acceptance of each state. When I have a new NFA or DFA, I should indicate the number of states in the automaton, update transitions and acceptance of each state. That is what I do in main method to create NFA and DFA objects. Then when I have a input string, I can read this string character by character and find the path. 
To create the translator, I refer to the procedure that converts an NFA to the corresponding DFA. Given the set of starting states, for each label of NFA, I try to find the set of next states. And if this set of next states has not been used as the set of starting states, then I add this set to the "waiting list" of being a set of starting states. At the same time, I add appropriate transitions between the new DFA states and acceptance of states. 

(c)How to run my project's programs:
dfa.c data structure of dfa
nfa.c: data structure of nfa
tester.c: test file (contains main method) 

My main method is in tester.c. I use Clion. So, if you also use Clion, you can click run button to run tester.c to see the output. Or you can do it in your habitual way. For each DFA or NFA, I have a description of the pattern that it is supposed to match, so that you know what to try. If you run the program, I prompt you to enter an input string in the console for each DFA or NFA. And a line will be printed to tell whether the string is accepted or not. 

In the main method, I created 5 DFA objects and 4 NFA objects as required. They are in the order of question order (1a, 1b, ... 2d). 

And NFA n1 and NFA n2 can be used to test the translator. First, I test your input string with NFA normally. And then I convert NFA to DFA for n1 and n2. Then I ask you to enter you string again. And you can see the result of acceptance before and after is same. 

*For some methods, such as DFA_get_size, I only show their results for some NFA and DFA., because I am afraid that such results would disturb your check of more important parts.  

(d)Sample output
This DFA recognizes string happy.
Enter your string (enter 'quit' to exit): hopes
Your input string is hopes
Your string is not accepted.
size of DFA: 6

This DFA recognizes any string that starts with three 9's.
Enter your string (enter 'quit' to exit): 909999
Your input string is 909999
Your string is not accepted.

This DFA recognizes binary input with an even number of 1's.
Enter your string (enter 'quit' to exit): 11101
Your input string is 11101
Your string is accepted.

This DFA recognizes binary input with an odd number of 0’s and an even number of 1’s.
Enter your string (enter 'quit' to exit): 1000100
Your input string is 1000100
Your string is accepted.

This DFA recognizes binary input which starts with 1 and ends with 0.
Enter your string (enter 'quit' to exit): 1100010
Your input string is 1100010
Your string is accepted.

This NFA recognizes strings ending in ing.
Enter your string (enter 'quit' to exit): drinking
Your input string is drinking
Your string is accepted.
{0}{0,1}{0,2}{0,3}
Number of states in DFA: 4
Enter you input again: 
Enter your string (enter 'quit' to exit): drinking
Your input string is drinking
Your string is accepted.
Size of NFA: 4

This NFA recognizes strings containing ing.
Enter your string (enter 'quit' to exit): singis
Your input string is singis
Your string is accepted.
{0}{0,1}{0,2}{0,3}{0,1,3}{0,2,3}
Number of states in DFA: 6
Enter you input again: 
Enter your string (enter 'quit' to exit): singis
Your input string is singis
Your string is accepted.

This NFA recognizes strings more than one a,g,h,i,o,s,t,or w,or more than two n’s.
Enter your string (enter 'quit' to exit): wash
Your input string is wash
Your string is not accepted.

This NFA recognizes strings ending in either on or er.
Enter your string (enter 'quit' to exit): teacher
Your input string is teacher
Your string is accepted.
