/* 
 *
 * CS 15 Metro Sim
 * by Alijah Jackson 6/14/23
 * 
 * Tests if functions for metro sim run correctly
 *
 * 
 */
#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
using namespace std;

void stack_empty_declare(){
    DatumStack dstack;
}

void stack_array_declare(){
    Datum first(27);
    Datum second(true);
    Datum third("apple");
    Datum arr[3] = {first, second, third};

    DatumStack dstack(arr, 3);
    assert(dstack.top().getRString() == "apple");
    dstack.pop();
    assert(dstack.top().getBool());
    dstack.pop();
    assert(dstack.top().getInt() == 27);
}

void stack_empty(){
    DatumStack dstack;
    for(int i = 0; i < 5; i++){
        dstack.push(Datum(i));
    }
    
    dstack.clear();
    assert(dstack.isEmpty());
}

void stack_empty_top(){
    DatumStack dstack;
    try{
        dstack.top();
    }
    catch(runtime_error){
        assert(true);
        return;
    }
    assert(false);
}

void stack_empty_pop(){
    DatumStack dstack;
    try{
        dstack.pop();
    }
    catch(runtime_error){
        assert(true);
        return;
    }
    assert(false);
}

void parse_test(){
    stringstream s(" 4 5 + }");
    string expected = "{ 4 5 + }";
    assert(parseRString(s) == expected);
}

void parse_test_multiple_brackets(){
    stringstream s(" 2 7 - { 3 2 #t if } }");
    string expected = "{ 2 7 - { 3 2 #t if } }";
    assert(parseRString(s) == expected);
}

void parse_empty(){
    stringstream s("}");
    string expected = "{ }";
    assert(parseRString(s) == expected);
}

void parse_multiline(){
    ifstream s("multiline.txt");
    string expected = "{ 2ds l 3 z red green purple 3 }";
    assert(parseRString(s) == expected);
}

