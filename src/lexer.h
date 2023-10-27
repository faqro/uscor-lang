#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

bool endsOnEscape(string s) {
  for(int i = 0; i<s.length(); i++) {
    if(s[i]==92) {
      if(i+2==s.length()) return true;
      else i++;
    }
  } return false;
}

vector<string> lexer(ifstream *fileReadIn) {
  vector<string> programTokens;
  programTokens.resize(0);

  typedef istreambuf_iterator<char> buf_iter;
  for (buf_iter i(*fileReadIn), e; i != e; ++i){
    char c = *i;
    if (programTokens.size() > 0 && programTokens[programTokens.size() - 1][0] == 34 && (programTokens[programTokens.size() - 1].length()==1||programTokens[programTokens.size() - 1] [programTokens[programTokens.size() - 1].length() - 1] != 34||endsOnEscape(programTokens[programTokens.size() - 1]))) {
      programTokens[programTokens.size() - 1] += c;
    } else if (programTokens.size() > 0 && programTokens[programTokens.size() - 1].length()==1 && programTokens[programTokens.size() - 1][0] == 39) {
      programTokens[programTokens.size() - 1] += c;
    } else if (c == '(') programTokens.push_back("(");
    else if (c == ')') programTokens.push_back(")");
    else if (c == '_') {
      if (programTokens[programTokens.size() - 1] == "" || programTokens[programTokens.size() - 1] == "_")
        programTokens[programTokens.size() - 1] += '_';
      else programTokens.push_back("_");
    } else if (c > 32) {
      if (programTokens.size()<=0 || programTokens[programTokens.size() - 1] == "_" || programTokens[programTokens.size() - 1] == "__" || programTokens[programTokens.size() - 1] == "(" || programTokens[programTokens.size() - 1] == ")")
        programTokens.push_back(string(1, c));
      else programTokens[programTokens.size() - 1] += c;
    }
  }
  for (int i = 0; i < programTokens.size();) {
    if (i < programTokens.size() - 2 && programTokens[i + 1] == "_") {
      programTokens[i] = programTokens[i] + "_" + programTokens[i + 2];
      programTokens.erase(programTokens.begin() + i + 1, programTokens.begin() + i + 3);
    } else i++;
  } return programTokens;
}

#endif