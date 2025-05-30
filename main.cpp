#include "string"
#include <vector>
#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include "RPNCalc.h"
#include <iostream>
using namespace std;

int main(){
    RPNCalc calc(std::cin);
    calc.run();
    return 0;
}