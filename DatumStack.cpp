#include "DatumStack.h"
#include <stdexcept>

DatumStack::DatumStack()
{
    datum_stack.vector::clear();
}

DatumStack::DatumStack(Datum arr[], int size)
{
    for(int i = 0; i < size; i++){
        datum_stack.push_back(arr[i]);
    }
}

DatumStack::~DatumStack()
{
    datum_stack.vector::clear();  
}

bool DatumStack::isEmpty()
{
    return(datum_stack.vector::size() == 0);
}

int DatumStack::size()
{
    return datum_stack.vector::size();
}

Datum DatumStack::top()
{
    if(size() == 0){
        throw std::runtime_error("empty_stack");
    }

    return datum_stack.at((size() -1));
}

void DatumStack::pop()
{
    if(size() == 0){
        throw std::runtime_error("empty_stack");
    }

    datum_stack.pop_back();
}

void DatumStack::push(Datum d)
{
    datum_stack.push_back(d);
}

void DatumStack::clear()
{
    datum_stack.vector::clear();
}
