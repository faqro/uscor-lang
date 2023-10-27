#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <iterator>
#include "datadef.h"

using namespace std;

AST branchParse(vector<string> *tokens, int *index) {
  AST astTreeReturn;
  astTreeReturn.subs.resize(0);

  bool branchedProgram = false;

  string tokenRead = (*tokens)[(*index)++];
  while ((*tokens)[*index] == "__") (*index)++;

  if (tokenRead == "(") {
    branchedProgram = true;
    astTreeReturn.data = (*tokens)[(*index)++];
    while ((*tokens)[*index] == "__") (*index)++;
  } else astTreeReturn.data = tokenRead;

  while (branchedProgram) {
    while ((*tokens)[*index] == "__") (*index)++;

    if ((*tokens)[(*index)] == ")") {
      branchedProgram = false;
      (*index)++;
    } else astTreeReturn.subs.push_back(branchParse(tokens, index));
  }
  return astTreeReturn;
}

AST parse(vector<string> *tokens) {
  AST astTreeReturn;
  astTreeReturn.subs.resize(0);
  astTreeReturn.data = "main";
  int index = 0;
  while (index < (*tokens).size()) astTreeReturn.subs.push_back(branchParse(tokens, &index));
  return astTreeReturn;
}

vector<string> getAstPrint(AST astTree) {
  vector<string> astReturn;
  astReturn.resize(1);
  astReturn[0] = astTree.data;
  for (int i = 0; i < astTree.subs.size(); i++) {
    vector<string> astSubsPrint = getAstPrint(astTree.subs[i]);
    for (int i2 = 0; i2 < astSubsPrint.size(); i2++) astSubsPrint[i2] = "  " + astSubsPrint[i2];
    astReturn.insert(end(astReturn), begin(astSubsPrint), end(astSubsPrint));
  } return astReturn;
}
void printAstTree(AST parsedProgram) {
  vector<string> printAST = getAstPrint(parsedProgram);
  for (int i = 0; i < printAST.size(); i++) cout << printAST[i] << endl;
}

#endif