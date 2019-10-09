# sat-solver-shl202

## 1. Project Overview
This project aims to implment a SAT Solver.



## 2. Compilation Instruction
To compile the code:  
  $ cd ./path/to/sat-solver-shl202/  
  $ make  

You should see a "solver.exe" file when compilation completes successfully.



## 3. Program Execution
To run the code:  
  $ ./solver.exe ./path/to/DIMACS/File.cnf [--time i] [--verbose]

Note: the executable file has been rename to "solver.exe" from "main.exe"

=============================
Example 1:  
  $ ./solver.exe ./sat-benchmarks/petite/total-ordering-5.cnf --time 5

Example 1 output:  
Time Limit: 5 (seconds)
Verbose: 0

unsat

=============================
Example 2:  
  $ ./solver.exe ./sat-benchmarks/petite/total-ordering-5.cnf --time 5 --verbose

Example 2 output:  
Time Limit: 5 (seconds)
Verbose: 1

unsat
Last Learned CLause:
3 

=============================
Example 3: 
  $ ./solver.exe ./sat-benchmarks/petite/graph-order-alt-5.cnf --time 5 --verbose

Example 3 output :
Time Limit: 5 (seconds)
Verbose: 1

sat
Satisfiable Assignment:
1 <- 1
2 <- 0
3 <- 1
4 <- 1
5 <- 0
6 <- 0
7 <- 0
8 <- 0
9 <- 1
10 <- 1
11 <- 1
12 <- 1
13 <- 0
14 <- 0
15 <- 0
16 <- 0
17 <- 0
18 <- 0
19 <- 0


=============================
Example 4: 
  $ ./solver.exe ./sat-benchmarks/petite/graph-order-15.cnf --time 5 --verbose

Example 4 output :
Time Limit: 5 (seconds)
Verbose: 1

unknown
Current Assignments:
1 <- 1
15 <- 0
2 <- 1
29 <- 0
30 <- 0
16 <- 0
3 <- 1
43 <- 0
45 <- 0
44 <- 0
31 <- 0
17 <- 0
4 <- 1
57 <- 0
60 <- 0
59 <- 0
58 <- 0
46 <- 0
32 <- 0
18 <- 0
5 <- 1
71 <- 0
75 <- 0
74 <- 0
73 <- 0
72 <- 0
61 <- 0
47 <- 0
33 <- 0
19 <- 0
6 <- 1
85 <- 0
90 <- 0
89 <- 0
88 <- 0
87 <- 0
86 <- 0
76 <- 0
62 <- 0
48 <- 0
34 <- 0
20 <- 0
7 <- 1
99 <- 0
105 <- 0
104 <- 0
103 <- 0
102 <- 0
101 <- 0
100 <- 0
91 <- 0
77 <- 0
63 <- 0
49 <- 0
35 <- 0
21 <- 0
8 <- 1
113 <- 0
120 <- 0
119 <- 0
118 <- 0
117 <- 0
116 <- 0
115 <- 0
114 <- 0
106 <- 0
92 <- 0
78 <- 0
64 <- 0
50 <- 0
36 <- 0
22 <- 0
9 <- 1
127 <- 0
10 <- 0
136 <- 0
122 <- 0
108 <- 0
94 <- 0
80 <- 0
66 <- 0
52 <- 0
38 <- 0
24 <- 0
141 <- 0
11 <- 0
137 <- 0
123 <- 0
109 <- 0
95 <- 0
81 <- 0
67 <- 0
53 <- 0
39 <- 0
25 <- 0
135 <- 0
134 <- 0
133 <- 0
132 <- 0
131 <- 0
130 <- 0
129 <- 0
128 <- 0
121 <- 0
107 <- 0
93 <- 0
79 <- 0
65 <- 0
51 <- 0
37 <- 0
23 <- 0
150 <- 1
149 <- 1
148 <- 1
147 <- 1
146 <- 1
145 <- 1
144 <- 1
143 <- 1
142 <- 1
151 <- 0
155 <- 0
12 <- 0
138 <- 0
124 <- 0
110 <- 0
96 <- 0
82 <- 0
68 <- 0
54 <- 0
40 <- 0
26 <- 0
165 <- 1



## 4. Results
The results of CDCLSolver on the petite benchmark with 2 minutes time limit can
be found in the main directory. Other than the unsatisfiable problems that are
hard for graph, all other benchmark can be solve in 2 minutes or less.

## 5. Updates
RandomSolver -- Updated Oct 17, 2017
DPLLSolver -- Updated Oct 31, 2017
DPLLSolver -- Minor bug fix (Nov 21, 2017)
ImplicationGraph -- Added to support up coming CDCLSolver (Nov 21, 2017)
ImplicationGraph -- Minor bug fix to print the Unique Implication Point rather
                    than the whole Implication Graph (Nov 28, 2017)
CDCLSolver -- Complete version of CDCLSolver (Updated Dec 7, 2017)



## 5. Contact Info
If you have any questions or comments about the project, feel free to contact  
me at:
 
shl202@ucsd.edu  

Please include "sat-solver-shl202" in the email subject. :)
