#ifndef DATADEF_H
#define DATADEF_H

#include <iostream>
#include <vector>

using namespace std;

class versionNumber {
  public:
    int majorVersion;
    int minorVersion;
    int buildVersion;
    versionNumber(int x, int y, int z) {
      majorVersion = x;
      minorVersion = y;
      buildVersion = z;
    }
    string versionString() {
      return to_string(majorVersion)+"."+to_string(minorVersion)+"."+to_string(buildVersion);
    }
};

int versionComparison(versionNumber a, versionNumber b) {
  //return -1 if A is newer than B, 1 is B is newer, or 0 is the same
  if(a.majorVersion>b.majorVersion) return -1;
  else if(a.majorVersion<b.majorVersion) return 1;
  else if(a.minorVersion>b.minorVersion) return -1;
  else if(a.minorVersion<b.minorVersion) return 1;
  else if(a.buildVersion>b.buildVersion) return -1;
  else if(a.buildVersion<b.buildVersion) return 1;
  else return 0;
}

struct AST {
  string data;
  vector<AST> subs;
};

#endif