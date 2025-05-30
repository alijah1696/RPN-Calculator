# RPN-Calculator
Reverse Polish Notion Calculator for Java
Author: Alijah Jackson

Purpuse: Create a calculator that can also import
functions similar to its own coding language

Acknoledgements: N/a

----------------------------------------------------------------------
FILES
----------------------------------------------------------------------
    DatumStack.h / .cpp: contains functions for handing stack of Datums

    RPNCalc.h/.cpp: calcular function for running and processing commands

    main.cpp: calls the calculator function

    Makefile: provides instructoins to compile the calcular
         -Compile using "make CalcYouLater"   -Run using ./CalcYouLater

    README: further breakdown of the program and information not mentioned
            in the original files.

    unit_tests.h: Provides testing cases for Datum and DatumStack

    fact.cylc/abs.cylc/fact.clyc/fib.cylc/multi_test.cylc/round.clyc:
        provides testing for the calculator function by testing math
        operators such as + and - and calc operators such as "not"
------------------------------------------------------------------------
BREAKDOWN
------------------------------------------------------------------------

Structure: this project made use of the stack meaning only the top element
           can be accessed first, allowing the debugging to easier put imp
           lemnting rpn commands harder as it far different from normal
           notation.


Testing: I tested the program by using the .cylc files and having severing debug
         commands(which were removed) that for example printed the entire stack
         and all its value and Datum type which was very useful for deubgging

Hours Spent: 27
