#ifndef DATUM_STACK_H
#define DATUM_STACK_H

#include <string>
#include <vector>
#include "Datum.h"  
using namespace std;

class DatumStack{
public:
//constructors
    DatumStack();
    DatumStack(Datum arr[], int size);
    ~DatumStack();
//accessors
    bool isEmpty();
    int size();
    Datum top();
    void pop();
    void push(Datum d);
//mutators
    void clear();
private:
    vector<Datum> datum_stack;
};
#endif