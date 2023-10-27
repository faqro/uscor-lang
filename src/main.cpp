/* USCOR PROGRAMMING LANGUAGE - AN ESOTERIC PROGRAMMING LANGUAGE MADE BY FARAAZ JAN */

#include "lexer.h"
#include "generator.h"
#include "parser.h"

#include <filesystem>
#include <unistd.h>

// using namespace std;

ifstream fileRead;
ofstream fileOut;

bool fexists(string path) {
  string filepath = {path};
  return filesystem::exists(filepath);
}

string fileWithoutExtension(string fileNameIn) {
  bool containsExtension=false;
  for(int iDot=0;iDot<fileNameIn.length();iDot++) {
    if(fileNameIn[iDot]=='.') containsExtension=true;
  } if(!containsExtension) return fileNameIn;
  while(fileNameIn[fileNameIn.length()-1]!='.') fileNameIn.pop_back();
  fileNameIn.pop_back();
  return fileNameIn;
}

int main(int argc, char *argv[]) {
  char *fvalue;
  int c;
  opterr = 0;

  bool CLICommand=false;
  string inputFileURL;
  bool outputSpecified=false;
  string outputFileURL;
  bool produceCpp=false;

  while ((c = getopt (argc, argv, "o:i:c:")) != -1) {
    switch (c) {
      case 'i':
        CLICommand=true;
        inputFileURL=optarg;
        break;
      case 'o':
        outputSpecified=true;
        outputFileURL=optarg;
        break;
      case 'c':
        produceCpp=true;
        break;
      case '?':
        if (optopt == 'i' || optopt == 'o') {
          cout<<"Options -%i and -%o require an argument.\n";
          return 0;
        } else if (optopt == 'c') {
          produceCpp=true;
        } else if (isprint (optopt)) {
          cout << "Unknown option -"<<(char)optopt<<"\n";
          return 0;
        } else {
          cout << "Unknown option character -"<<(char)optopt<<"\n";
          return 0;
        }
      default:
        break;
    }
  }

  cout<<"USCOR PROGRAMMING LANGUAGE\nMADE BY FARAAZ JAN\n\nNote: you must have the GNU C++ compiler for this compiler to work.\n\n";

  if(!CLICommand) {
    cout<<"Address of .usc file: ";
    cin>>inputFileURL;
    cout<<"\n";
  }

  fileRead.open(inputFileURL, ios::in);
  if(!fileRead.is_open()) {
    cout<<"File does not exist. Verify you have entered the file name correctly.\n\n";
    return 0;
  }

  string inputFileName;

  if(!outputSpecified) {
    inputFileName=fileWithoutExtension(inputFileURL);
  } else {
    inputFileName=fileWithoutExtension(outputFileURL);
  }
  
  cout<<"Running lexer... ";
  vector<string> tokens = lexer(&fileRead);
  fileRead.close();

  cout<<"done!\n\nParsing... ";
  AST parsedProgram = parse(&tokens);
  //printAstTree(parsedProgram);
  cout<<"done!\n\n";

  fileOut.open(inputFileName+".cpp", ios::out);
  cout<<"Transpiling... ";
  generateHeaders(&fileOut);
  generateMainCode(&fileOut,&parsedProgram);
  fileOut.flush();
  fileOut.close();
  cout<<"done!\n\nCompiling with g++... ";
  
  string execCmd = "g++ -o "+inputFileName+".exe "+inputFileName+".cpp";
  system(execCmd.c_str());

  if(fexists(inputFileName+".cpp")&&fexists(inputFileName+".exe")) {
    if(!produceCpp) {
      filesystem::remove(inputFileName+".cpp");
      cout<<"done!\n\nOutput file at \""<<inputFileName<<".exe\"";
    } else {
      cout<<"done!\n\nOutput file at \""<<inputFileName<<".exe\" and \""+inputFileName+".cpp\"";
    }
  } else {
    cout<<"unsuccessful.\n\nPlease verify that GNU Compiler Collection is installed.\n\n";
  }
}