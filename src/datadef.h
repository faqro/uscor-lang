#ifndef DATADEF_H
#define DATADEF_H

#include <iostream>
#include <vector>

using namespace std;

struct AST {
  string data;
  vector<AST> subs;
};

#endif