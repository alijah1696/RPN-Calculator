#include "RPNCalc.h"


RPNCalc::RPNCalc() : input(cin)
{   
    end_calc = false;
    not_user = false;
    stack = DatumStack();
}

RPNCalc::RPNCalc(istream &other_input) : input(other_input)
{
    end_calc = false;
    not_user = false;
    stack = DatumStack();
}

RPNCalc::~RPNCalc()
{
    stack.clear();
}

void RPNCalc::print_stack()
{
    vector<Datum> old_stack;

    int total_size = stack.size();
    cout << "\n |STACK|\n -------\n";
    for(int i = 0; i < total_size; i++){
        Datum elem = stack.top();
        string type = "";
        if(elem.isInt()) type = " : int";
        if(elem.isBool()) type = " : bool";
        if(elem.isRString()) type = " : rstring";
        cout << "  " << stack.top().toString() << type << endl;
        old_stack.push_back(stack.top());
        stack.pop();
    }
    cout << " -------\n";

    for(int i = (total_size - 1); i >= 0; i--){
        stack.push(old_stack.at(i));
    }
}

void RPNCalc::run()
{
    string word;
    while(not end_calc and (input >> word)){
        not_user = false;
        stringstream temp("");
        end_calc = not process_word(word, temp);
    }  
}

bool RPNCalc::process_word(string word, istream &u_input){
//checks if the program should quit
    int read_int;
    if(word == "quit"){
        cerr << "Thank you for using CalcYouLater.\n";
        return false;
    }
//for numbers
    else if(got_int(word, &read_int)){
        stack.push(Datum(read_int));
    }
//true or false bools
    else if(word == "#t"){
        stack.push(Datum(true));
    }
    else if(word == "#f"){
        stack.push(Datum(false));
    }
    else if(word == "{"){
        if(not_user) connect_brackets_file(u_input);
        else connect_brackets();
    }   
    else if(word == "print"){
        if(stack.size() > 0){
            cout << stack.top().toString() << endl;
        }else{
            cerr << "Error: empty_stack\n";
        }
    }  
    else if(isElement(word,"operators")){
        operators(word);
    }
    else if(isElement(word,"compare")){
        compare(word);
    }
    else if(word == "clear"){
        stack.clear();
    }   
    else if(word == "drop"){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
        }else{
            stack.pop();
        }
    }
    else if(word == "dup"){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
        }else{
            stack.push(stack.top());
        }
    }
    else if(word == "not"){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
        }else if(not stack.top().isBool()){
            stack.pop();
            cerr << "Error: datum_not_bool\n";
        }
        else{
            bool val = stack.top().getBool();
            stack.pop();
            stack.push(Datum(not val));
        }     
    }
    else if(word == "swap"){
        swap();
    }
    else if(word == "exec"){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
        }else if(not stack.top().isRString()){
            stack.pop();
            cerr << "Error: cannont execute non rstring\n";
        }
        else{
            Datum e = stack.top();
            stack.pop();
            exec(e);
        }     
    }
    else if(word == "if"){
        calc_if();
    }
    else if(word == "file"){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
        }else if(not stack.top().isRString()){
            stack.pop();
            cerr << "Error: file operand not rstring\n";
        }
        else{
            Datum e = stack.top();
            stack.pop();
            file(e);
        }     
    }
    else{
        cerr << word << ": unimplemented\n"; 
    }
    return true;
}

void RPNCalc::operators(string word){
    int num[2];
    for(int i = 0; i < 2; i++){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
            return;
        }else{
            if(stack.top().isInt()){
                if((word == "/" or word == "mod") 
                and stack.top().getInt() == 0){
                    stack.pop();
                    cerr << "Error: division by 0.\n";
                    return;   
                }
                num[i] = stack.top().getInt();
            }else{
                cerr << "Error: datum_not_int\n";
                stack.pop();
                return;
            }
            stack.pop();
        }
    } 
    if(word == "+") stack.push(Datum(num[1] + num[0]));
    if(word == "-") stack.push(Datum(num[1] - num[0]));
    if(word == "*") stack.push(Datum(num[1] * num[0]));
    if(word == "/") stack.push(Datum(num[1] / num[0]));
    if(word == "mod") stack.push(Datum(num[1] % num[0]));
}

void RPNCalc::compare(string word)
{
    vector<Datum> compares;
    for(int i = 0; i < 2; i++){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
            return;
        }
        else if(not stack.top().isInt()){
            cerr << "Error: datum_not_int\n";
            stack.pop();
            return;          
        }
        else{
            compares.push_back(stack.top());
            stack.pop();
        }
    }        
    Datum left = compares.at(1);
    Datum right = compares.at(0);
    compares.push_back(Datum(word));

    bool equal = (left == right);
    bool less = (left < right);
    bool greater(not equal or not less);

    bool r;
    if(word == "<") r = less;
    else if(word == "<=") r = (equal or less);
    else if(word == ">") r = greater;
    else if(word == ">=") r = (greater or equal);
    else r = equal;
    stack.push(Datum(r));
}

void RPNCalc::swap()
{
    vector<Datum> originals;
    for(int i = 0; i < 2; i++){
        if(stack.size() <= 0){
            cerr << "Error: empty_stack\n";
            return;
        }
        originals.push_back(stack.top());
        stack.pop();
    } 
    stack.push(originals.at(0));
    stack.push(originals.at(1));
}

bool RPNCalc::isElement(string word, string list)
{
    string operators[5] = {"+","-","*","/","mod"};
    string compare[5] = {"<",">","<=",">=","=="};

    if(list == "operators"){
        for(int i = 0; i < 5; i++){
            if(word == operators[i]) return true;
        }
    }
    else if(list == "compare"){
        for(int i = 0; i < 5; i++){
            if(word == compare[i]) return true;
        }
    }
    return false;
}

void RPNCalc::exec(Datum e)
{
    string word = e.getRString();
    stringstream s(rstring_to_string(word));
    while(not end_calc and (s >> word)){
        not_user = true;
        end_calc = not process_word(word, s);
    }     
}

void RPNCalc::calc_if()
{
        if(stack.size() <= 2){
            cerr << "Error: empty_stack\n";
            while(stack.size() > 0)stack.pop();
            return;
        }
        else{
            Datum f = stack.top();
            stack.pop();
            Datum t = stack.top();
            stack.pop();
            Datum condition = stack.top();
            stack.pop();

            if(not condition.isBool()){
                cerr << "Error: expected boolean in if branch\n";
                return;             
            }
            if(not t.isRString() or not f.isRString()){
                cerr << "Error: expected rstring in if branch\n";
                return;
            }
            if(condition.getBool())exec(t);
            else exec(f);
        }
}

void RPNCalc::file(Datum e)
{
    string file_name = rstring_to_string(e.getRString());
    ifstream inputFile(file_name);
    if (not inputFile.is_open()){
        cerr << ("Unable to read " + file_name + "\n");
        return;
    }

    string word;
    stringstream ss;
    while(inputFile >> word){
        ss << word << " ";
    }
    ss << " }";
    word = parseRString(ss);
    Datum f(word);
    exec(f);
}

void RPNCalc::connect_brackets()
{
    string word;
    string parse;
    bool cont = true;

    while(cont and (input >> word)){
        parse += word + " ";
        stringstream temp(parse);
        if(parseRString(temp) != "") cont = false;
    }
    stringstream temp(parse); 
    parse = (parseRString(temp)); 
    stack.push(Datum(parse));
}

void RPNCalc::connect_brackets_file(istream &u_input)
{
    string word;
    string parse;
    bool cont = true;
    while(cont and (u_input >> word)){
        parse += word + " ";
        stringstream temp(parse);
        if(parseRString(temp) != "") cont = false;
    }
    stringstream temp(parse);
    parse = (parseRString(temp)); 
    stack.push(Datum(parse));
}

bool RPNCalc::got_int(string s, int *resultp)
{
    /* Holds the first non-whitespace character after the integer */
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

string RPNCalc::rstring_to_string(string in)
{
    int new_len = in.length() - 2;
    string out = "";
    for(int i = 2; i < new_len; i ++){
        out += in[i];
    }
    return out;
}
