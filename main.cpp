/* USCOR PROGRAMMING LANGUAGE - AN ESOTERIC PROGRAMMING LANGUAGE MADE BY FARAAZ JAN */

#include "lexer.h"
#include "generator.h"
#include "parser.h"


// using namespace std;

ifstream fileRead("input.usc");
ofstream fileOut("outputUscorProgramMid.cpp");

int main() {
  cout<<"USCOR PROGRAMMING LANGUAGE\nMADE BY FARAAZ JAN\n\nNote: you must have the GNU C++ compiler for this compiler to work.\n\nRunning lexer... ";
  vector<string> tokens = lexer(&fileRead);
  fileRead.close();

  cout<<"done!\n\nParsing... ";
  AST parsedProgram = parse(&tokens);

  printAstTree(parsedProgram);

  cout<<"done!\n\nTranspiling... ";
  
  generateHeaders(&fileOut);
  generateMainCode(&fileOut,&parsedProgram);

  fileOut.flush();
  fileOut.close();
  cout<<"done!\n\nCompiling... ";
  
  system("g++ -o outputUscorProgram.exe outputUscorProgramMid.cpp");
  
  cout<<"done!\n\n";
}