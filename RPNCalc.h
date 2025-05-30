#ifndef RPNCALC_H
#define RPNCALC_H
#include "DatumStack.h" 
#include "parser.h" 
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;
class RPNCalc{
public:
//constructor & destructor
    RPNCalc();
    RPNCalc(istream &other_input);
    ~RPNCalc();  
//mutators
    void run();
private:
//helper fucntions

    //debugging
    void print_stack();

    //procssing
    bool process_word(string word, istream &u_input);
    void operators(string word);
    void compare(string word);
    void swap();
    bool isElement(string word, string list);
    void exec(Datum e);
    void calc_if();
    void file(Datum e);

    void connect_brackets();
    void connect_brackets_file(istream &input);
    bool got_int(string s, int *resultp);

    string rstring_to_string(string in);
    //variables
    bool end_calc;
    bool not_user;
    istream& input;
    DatumStack stack;
};
#endif