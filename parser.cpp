#include <string>
#include <sstream>
using namespace std;

string parseRString(istream& input) {
  string result;
  char c;
  int braceCount = 1;
  bool lastCharWasSpace = true;
  bool found_parse = false;
  
  while (input.get(c) and not found_parse) {
    if (c == '{') {
      braceCount++;
    }
    if (braceCount > 0) {
      if (c == ' ') {
        if (not lastCharWasSpace) {
          result += c;
        }
        lastCharWasSpace = true;
      } else if (c == '\n' or c == '\r') {
        if (lastCharWasSpace) {
          result += "";
        } else {
          result += ' ';
          lastCharWasSpace = true;
        }
      } else {
        result += c;
        lastCharWasSpace = false;
      }
    }
    if (c == '}') {
      braceCount--;
      if (braceCount == 0) {
        found_parse = true;
      }
    }
  }
  
  if (braceCount != 0) return "";
  return ("{ " + result);
}