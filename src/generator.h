#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include <algorithm>
#include "datadef.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

versionNumber currentVersion(1, 2, 0);
versionNumber minimumCompatibleVersion(1, 1, 0);

char programSupported='u'; //u means unclear, y means yes, o means program is too old, n means program is too new



vector<string> listOfHeaders;
vector<string> globalDefinedMethods;

struct dataTypeKey {
  string uscorType; //the user-side Uscor data type to call
  string cMappedType; //the c data type to call it as.
};
vector<dataTypeKey> customDataTypes;

bool customDataTypeExists(string s) {
  for(int i = 0; i < customDataTypes.size(); i++) {
    if(customDataTypes[i].uscorType==s) return true;
  } return false;
}
dataTypeKey getCustomDataType(string s) {
  for(int i = 0; i < customDataTypes.size(); i++) {
    if(customDataTypes[i].uscorType==s) return customDataTypes[i];
  }
}


struct funcDictionary {
  string uscorCall; //the user-side Uscor function to call

  bool astReplace=false; //whether the function is a local AST replace function or a global c function

  string cppCall; //the c function to call if it is a c function. Note that global non-c functions also use this.
  bool hasParameters=true; //whether this is a function or just a piece of data

  AST astToReplace; //the AST branch to replace the function when it is called. All sub branches with the (lib_param__0), (lib_param__1), etc. will be replaced with paramters entered
};

vector<funcDictionary> functionDictionaryUscor;

bool hasCustomDefinition(string s) {
  for(int ind=0;ind<functionDictionaryUscor.size();ind++) {
    if(functionDictionaryUscor[ind].uscorCall==s) return true;
  } return false;
}

funcDictionary findFunctionCall(string s) {
  for(int ind=0;ind<functionDictionaryUscor.size();ind++) {
    if(functionDictionaryUscor[ind].uscorCall==s) return functionDictionaryUscor[ind];
  }
  funcDictionary failedFuncFind;
  failedFuncFind.uscorCall="USCOR_FIND_FAILED";
  return failedFuncFind;
}

string substr(string s1, int i1, int i2) {return s1.substr(i1, i2);}

string generator(AST astTree, bool includeEndBrackets);

string strToVal(string s) {
  s=s.substr(1, s.length()-2);

  for(int ind = 0; ind < s.length(); ind++) {
    if(s.length() > ind+1 &&s[ind]==92) {
      string replace;
      switch(s[ind+1]) {
        case 'a':
        replace="\a";
        break;

        case 'b':
        replace="\b";
        break;

        case 'n':
        replace="\n";
        break;

        case 'f':
        replace="\f";
        break;

        case 'r':
        replace="\r";
        break;

        case 't':
        replace="\t";
        break;

        case 'v':
        replace="\v";
        break;

        case 39:
        replace="\'";
        break;

        case 34:
        replace="\"";
        break;

        case 92:
        replace="\\";
        break;

        case 63:
        replace="\?";
        break;

        default:
        replace="";
        break;
      }
      s.replace(ind, 2, replace);
    }
  }

  return s;
}

AST replaceWithParameters(AST astIn, vector<AST> paramsIn) {
  for(int i = 0; i < astIn.subs.size(); i++) {
    if(astIn.subs[i].data=="param") {
      int paramNumber = stoi(astIn.subs[i].subs[0].data);
      astIn.subs[i]=paramsIn[paramNumber];
    } else {
      astIn.subs[i] = replaceWithParameters(astIn.subs[i], paramsIn);
    }
  } return astIn;
}

AST replaceWithSetupParameters(AST astIn) {
  for(int i = 0; i < astIn.subs.size(); i++) {
    if(astIn.subs[i].data=="param") {
      astIn.subs[i].data="uscor_lib_functions_param"+astIn.subs[i].subs[0].data;
      astIn.subs[i].subs.resize(0);
    } else {
      astIn.subs[i] = replaceWithSetupParameters(astIn.subs[i]);
    }
  } return astIn;
}

string dataTypeGet(AST astTree) {
  if(astTree.data=="data_ref") return dataTypeGet(astTree.subs[0])+" *";
  if(astTree.data=="data_vector") return "vector<"+dataTypeGet(astTree.subs[0])+">";
  string dataType=generator(astTree,false);
  if(dataType=="int") return "int";
  else if(dataType=="str") return "string";
  else if(dataType=="bool") return "bool";
  else if(dataType=="float") return "float";
  else if(dataType=="double") return "double";
  else if(dataType=="char") return "char";
  else if(dataType=="char16") return "char16_t";
  else if(dataType=="char32") return "char32_t";
  else if(dataType=="shint") return "short";
  else if(dataType=="lint") return "long";
  else if(dataType=="llint") return "long long";
  else if(dataType=="ushint") return "unsigned short";
  else if(dataType=="uint") return "unsigned int";
  else if(dataType=="ulint") return "unsigned long";
  else if(dataType=="ullint") return "unsigned long long";
  else if(dataType=="ldouble") return "long double";
  else if(dataType=="mt") return "void";
  else if(dataType=="NULL") return "NULL";
  else if(customDataTypeExists(dataType)) return getCustomDataType(dataType).cMappedType;
  else return "NULL";
}

string generator(AST astTree, bool includeEndBrackets=true) {
  if(astTree.data=="data_declare") {
    if(includeEndBrackets) return dataTypeGet(astTree.subs[0]) + " " + generator(astTree.subs[1],false) + ";";
    else return dataTypeGet(astTree.subs[0]) + " " + generator(astTree.subs[1],false);
  } else if(astTree.data=="data_type_conversion") {
    string dataTypeFrom = dataTypeGet(astTree.subs[0]);
    string dataTypeTo = dataTypeGet(astTree.subs[1]);
    if((dataTypeFrom=="char"||dataTypeFrom=="char16_t"||dataTypeFrom=="char32_t")&&dataTypeTo=="string") {
      return "string({"+generator(astTree.subs[2],false)+"})";
    } else if(dataTypeTo=="string") {
      return "to_string("+generator(astTree.subs[2],false)+")";
    } else if(dataTypeFrom=="string") {
      if(dataTypeTo=="int") return "stoi("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="bool") return "uscor_lib_integrated_func_strToBool("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="float") return "stof("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="double") return "stod("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="char") return "stoi("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="char16_t") return "stoi("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="char32_t") return "stoi("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="short") return "stoi("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="long") return "stol("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="long long") return "stoll("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="unsigned short") return "stoul("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="unsigned int") return "stoul("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="unsigned long") return "stoul("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="unsigned long long") return "stoull("+generator(astTree.subs[2],false)+")";
      else if(dataTypeTo=="long double") return "stold("+generator(astTree.subs[2],false)+")";
      else return "NULL2";
    } else {
      return dataTypeTo+"("+generator(astTree.subs[2],false)+")";
    }
  } else if(astTree.data=="math_mod") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "%" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="data_arr_declare") {
    string output = dataTypeGet(astTree.subs[0])+" "+generator(astTree.subs[1],false)+" ";
    for (int i1=2;i1<astTree.subs.size();i1++) output=output+"["+generator(astTree.subs[i1],false)+"]";
    if(includeEndBrackets) return output+";";
    else return output;
  } else if(astTree.data=="data_arr_specify") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output+"["+generator(astTree.subs[i1],false)+"]";
    } return output;
  } else if(astTree.data=="=") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "==" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="s=") {
    return "uscor_lib_integrated_func_strcmp("+generator(astTree.subs[0],false)+", "+generator(astTree.subs[1],false)+")";
  } else if(astTree.data=="!=") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "!=" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data==">") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + ">" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="<") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "<" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="<=") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "<=" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data==">=") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + ">=" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="system_or") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "||" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="system_and") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "&&" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="system_not") {
    return "(!"+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="+") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "+" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="-") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "-" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="/") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "/" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="*") {
    string output = generator(astTree.subs[0],false);
    for (int i1=1;i1<astTree.subs.size();i1++) {
      output=output + "*" + generator(astTree.subs[i1],false);
    } return "("+output+")";
  } else if(astTree.data=="system_exit") {
    string returnValueOut = "return";
    if(astTree.subs.size()>0) {
      if(!(astTree.subs[0].data=="mt")) returnValueOut=returnValueOut+" "+generator(astTree.subs[0],false);
    } else {
      returnValueOut=returnValueOut+" 0";
    }
    if(includeEndBrackets) return returnValueOut+";";
    else return returnValueOut;
  } else if(astTree.data=="system_break") {
    if(includeEndBrackets) return "break;";
    else return "break";
  } else if(astTree.data=="math_random_seed") {
    if(includeEndBrackets) return "srand(" + generator(astTree.subs[0],false) + ");";
    else return "srand(" + generator(astTree.subs[0],false) + ")";
  } else if(astTree.data=="system_run_cpp") {
    if(astTree.subs[0].data.length()>=2&&astTree.subs[0].data[0]==34&&astTree.subs[0].data[astTree.subs[0].data.length()]==34) {
      string cppCode=astTree.subs[0].data;
      return strToVal(cppCode);
    } else {
      return "";
    }
  } else if(astTree.data=="string_substr") {
    return "uscor_lib_integrated_func_substr("+generator(astTree.subs[0],false)+", "+generator(astTree.subs[1],false)+", "+generator(astTree.subs[2],false)+")";
  } else if(astTree.data=="string_find") {
    return "uscor_lib_integrated_func_strfind("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+")";
  } else if(astTree.data=="string_insert") {
    return "uscor_lib_integrated_func_strins("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+","+generator(astTree.subs[2],false)+")";
  } else if(astTree.data=="system_file_copy") {
    if(includeEndBrackets) return "filesystem::copy("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+", filesystem::copy_options::recursive);";
    else return "filesystem::copy("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+", filesystem::copy_options::recursive)";
  } else if(astTree.data=="system_file_rename") {
    if(includeEndBrackets) return "filesystem::rename(p / "+generator(astTree.subs[0],false)+", p / "+generator(astTree.subs[1],false)+");";
    else return "filesystem::rename(p / "+generator(astTree.subs[0],false)+", p / "+generator(astTree.subs[1],false)+")";
  } else if(astTree.data=="system_file_remove") {
    if(includeEndBrackets) return "filesystem::remove("+generator(astTree.subs[0],false)+");";
    else return "filesystem::remove("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="system_file_allremove") {
    if(includeEndBrackets) return "filesystem::remove_all("+generator(astTree.subs[0],false)+");";
    else return "filesystem::remove_all("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="system_file_createdir") {
    if(includeEndBrackets) return "filesystem::create_directories("+generator(astTree.subs[0],false)+");";
    else return "filesystem::create_directories("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="system_file_setdir") {
    if(includeEndBrackets) return "filesystem::current_path("+generator(astTree.subs[0],false)+");";
    else return "filesystem::current_path("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="system_file_exists") {
    return "filesystem::exists("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="system_file_tempdir") {
    return "filesystem::temp_directory_path()";
  } else if(astTree.data=="system_file_curdir") {
    return "filesystem::current_path()";
  } else if(astTree.data=="math_pow") {
    return "pow("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+")";
  } else if(astTree.data=="math_log") {
    return "(log("+generator(astTree.subs[0],false)+") / log("+generator(astTree.subs[1],false)+"))";
  } else if(astTree.data=="math_min") {
    return "min("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+")";
  } else if(astTree.data=="math_max") {
    return "max("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+")";
  } else if(astTree.data=="math_abs") {
    return "abs("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_floor") {
    return "floor("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_ceil") {
    return "ceil("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_round") {
    return "round("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_cos") {
    return "cos("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_sin") {
    return "sin("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_tan") {
    return "tan("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_acos") {
    return "acos("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_asin") {
    return "asin("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="math_atan") {
    return "atan("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="data_ref") {
    return "(&"+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="data_deref") {
    return "(*"+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="string_escape") {
    return strToVal(generator(astTree.subs[0],false));
  } else if(astTree.data=="string_length") {
    return "strlen("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="system_run_shell") {
    if(includeEndBrackets) return "uscor_lib_integrated_func_execComd("+generator(astTree.subs[0],false)+");";
    else return "uscor_lib_integrated_func_execComd("+generator(astTree.subs[0],false)+")";
  } else if(astTree.data=="data_arrv_size") {
    return generator(astTree.subs[0])+".size()";
  } else if(astTree.data=="data_arrv_push") {
    if(includeEndBrackets) return generator(astTree.subs[0])+".push_back("+generator(astTree.subs[1])+");";
    else return generator(astTree.subs[0])+".push_back("+generator(astTree.subs[1])+")";
  } else if(astTree.data=="data_arrv_insert") {
    if(includeEndBrackets) return generator(astTree.subs[0])+".insert("+generator(astTree.subs[0])+".begin()+"+generator(astTree.subs[1])+","+generator(astTree.subs[2])+");";
    else return generator(astTree.subs[0])+".insert("+generator(astTree.subs[0])+".begin()+"+generator(astTree.subs[1])+","+generator(astTree.subs[2])+")";
  } else if(astTree.data=="data_arrv_erase") {
    string output = generator(astTree.subs[0])+".erase("+generator(astTree.subs[0])+".begin()+"+generator(astTree.subs[1])+","+generator(astTree.subs[0])+".begin()+"+generator(astTree.subs[2])+")";
    if(includeEndBrackets) return output+";";
    else return output;
  } else if(astTree.data=="data_arrv_resize") {
    if(includeEndBrackets) return generator(astTree.subs[0])+".resize("+generator(astTree.subs[1])+");";
    else return generator(astTree.subs[0])+".resize("+generator(astTree.subs[1])+")";
  } else if(astTree.data=="data_arrv_pop") {
    if(includeEndBrackets) return generator(astTree.subs[0])+".pop_back();";
    else return generator(astTree.subs[0])+".pop_back()";
  } else if(astTree.data=="data_arr_group") {
    string output="{"+generator(astTree.subs[0]);
    for(int i3=1;i3<astTree.subs.size();i3++) {
      output = output+","+generator(astTree.subs[i3]);
    } return output+"}";
  } else if(astTree.data=="data_arrv_declare") {
    string declare = dataTypeGet(astTree.subs[0]);
    for(int i3=0;i3<stoi(astTree.subs[2].data);i3++) declare = "vector<"+declare+">";
    if(includeEndBrackets) return declare+" "+generator(astTree.subs[1])+";";
    else return declare+" "+generator(astTree.subs[1]);
  } else if(astTree.data=="system_io_file_pointer") {
    return generator(astTree.subs[0],false)+".tellg()";
  } else if(astTree.data=="system_io_file_pointer_move") {
    if(includeEndBrackets) return "uscor_lib_integrated_func_seek(&"+generator(astTree.subs[0],false)+", '"+generator(astTree.subs[1],false)+"', "+generator(astTree.subs[2],false)+");";
    return "uscor_lib_integrated_func_seek(&"+generator(astTree.subs[0],false)+", '"+generator(astTree.subs[1],false)+"', "+generator(astTree.subs[2],false)+")";
  } else if(astTree.data=="system_io_file_close") {
    if(includeEndBrackets) return generator(astTree.subs[0],false)+".close();";
    else return generator(astTree.subs[0],false)+".close()";
  } else if(astTree.data=="system_io_file_open") {
    string fileAt = generator(astTree.subs[0],false);
    if(includeEndBrackets) return fileAt+".open("+generator(astTree.subs[1],false)+", ((uscor_lib_integrated_func_strfind(typeid("+fileAt+").name(), \"ifstream\")>=0) ? ifstream::in : ofstream::out));";
    else return fileAt+".open("+generator(astTree.subs[1],false)+", ((uscor_lib_integrated_func_strfind(typeid("+fileAt+").name(), \"ifstream\")>=0) ? ifstream::in : ofstream::out))";
  } else if(astTree.data=="system_io_file_declare") {
    if(astTree.subs.size()==3) {
      if(astTree.subs[0].data=="ifs") {
        if(includeEndBrackets) return "ifstream "+generator(astTree.subs[1],false)+"("+generator(astTree.subs[2],false)+");";
        else return "ifstream "+generator(astTree.subs[1],false)+"("+generator(astTree.subs[2],false)+")";
      } else if(astTree.subs[0].data=="ofs") {
        if(includeEndBrackets) return "ofstream "+generator(astTree.subs[1],false)+"("+generator(astTree.subs[2],false)+");";
        else return "ofstream "+generator(astTree.subs[1],false)+"("+generator(astTree.subs[2],false)+")";
      } else return "";
    } else if(astTree.subs.size()==2) {
      if(astTree.subs[0].data=="ifs") {
        if(includeEndBrackets) return "ifstream "+generator(astTree.subs[1],false)+";";
        else return "ifstream "+generator(astTree.subs[1],false);
      } else if(astTree.subs[0].data=="ofs") {
        if(includeEndBrackets) return "ofstream "+generator(astTree.subs[1],false)+";";
        else return "ofstream "+generator(astTree.subs[1],false);
      } else return "";
    } else return "";
  } else if(astTree.data=="system_force") {
    return generator(astTree.subs[0],false)+";";
  } else if(astTree.data=="system_forcen") {
    return generator(astTree.subs[0],false);
  } else if(astTree.data=="math_pi") {
    return "M_PI";
  } else if(astTree.data=="math_e") {
    return "M_E";
  } else if(astTree.data=="math_random") {
    return "rand()";
  } else if(astTree.data=="system_io_input") {
    if(generator(astTree.subs[0],false)=="console") return "cin";
    else if(astTree.subs[0].data=="file"||astTree.subs[0].data=="file-"||astTree.subs[0].data=="file-="||astTree.subs[0].data=="file+") return generator(astTree.subs[1],false);
    else return "NULL3";
  } else if(astTree.data=="system_io_output") {
    if(generator(astTree.subs[0],false)=="console") return "cout";
    else if(astTree.subs[0].data=="file") return generator(astTree.subs[1],false);
    else return "NULL4";
  } else if(astTree.data=="system_while") {
    string output = "while ("+generator(astTree.subs[0],false)+"){";
    for(int i2=1;i2<astTree.subs.size();i2++) {
      output=output+generator(astTree.subs[i2],true);
    } return output+"}";
  } else if(astTree.data=="system_for") {
    string output = "for ("+generator(astTree.subs[0],false)+"; "+generator(astTree.subs[1],false)+"; "+generator(astTree.subs[2],false)+"){";
    for(int i2=3;i2<astTree.subs.size();i2++) {
      output=output+generator(astTree.subs[i2],true);
    } return output+"}";
  } else if(astTree.data=="system_ifelse") {
    return "if ("+generator(astTree.subs[0],false)+")"+generator(astTree.subs[1],true)+" else "+generator(astTree.subs[2],true);
  } else if(astTree.data=="system_cond") {
    return generator(astTree.subs[0],false)+" ? "+generator(astTree.subs[1],false)+" : "+generator(astTree.subs[2],true);
  } else if(astTree.data=="system_io_file_iseof") {
    return generator(astTree.subs[0],false)+".eof()";
  } else if(astTree.data=="system_io_file_isopen") {
    return generator(astTree.subs[0],false)+".is_open()";
  } else if(astTree.data=="system_run") {
    string output = "{";
    for(int i2=0;i2<astTree.subs.size();i2++) {
      output=output+generator(astTree.subs[i2],true);
    } return output+"}";
  } else if(astTree.data=="<<") {
    if(astTree.subs[1].data=="system_io_input") {
      if(astTree.subs[1].subs[0].data=="file+") {
        if(includeEndBrackets) return "getline("+generator(astTree.subs[1], false)+", "+generator(astTree.subs[0], false)+");";
        else return "getline("+generator(astTree.subs[1], false)+", "+generator(astTree.subs[0], false)+")";
      } else if(astTree.subs[1].subs[0].data=="file-") {
        if(includeEndBrackets) return generator(astTree.subs[1], false)+".get("+generator(astTree.subs[0], false)+");";
        else return generator(astTree.subs[1], false)+".get("+generator(astTree.subs[0], false)+")";
      } else if(astTree.subs[1].subs[0].data=="file-=") {
        if(includeEndBrackets) return generator(astTree.subs[0], false)+"="+generator(astTree.subs[1], false)+".peek();";
        else return generator(astTree.subs[0], false)+"="+generator(astTree.subs[1], false)+".peek()";
      } else {
        if(includeEndBrackets) return generator(astTree.subs[1], false) + ">>" + generator(astTree.subs[0], false)+";";
        else return generator(astTree.subs[1], false) + ">>" + generator(astTree.subs[0], false);
      }
    } else if(astTree.subs[0].data=="system_io_output") {
      if(includeEndBrackets) return generator(astTree.subs[0], false) + "<<" + generator(astTree.subs[1], false)+";";
      else return generator(astTree.subs[0], false) + "<<" + generator(astTree.subs[1], false);
    } else {
      if(includeEndBrackets) return generator(astTree.subs[0], false) + "=" + generator(astTree.subs[1], false)+";";
      else return generator(astTree.subs[0], false) + "=" + generator(astTree.subs[1], false);
    }
  } else if(astTree.data=="comment") {
    return "//"+astTree.subs[0].data;
  } else if (hasCustomDefinition(astTree.data)) {
    if(findFunctionCall(astTree.data).astReplace==false) {
      string cppReturnFunction;
      if(findFunctionCall(astTree.data).hasParameters) {
        cppReturnFunction= findFunctionCall(astTree.data).cppCall + "(";
        if(astTree.subs.size()>0) cppReturnFunction=cppReturnFunction+generator(astTree.subs[0], false);
        for (int i=1; i< astTree.subs.size(); i++) {
          cppReturnFunction=cppReturnFunction+", "+generator(astTree.subs[i], false);
        } cppReturnFunction=cppReturnFunction+")";
      } else {
        cppReturnFunction= findFunctionCall(astTree.data).cppCall;
      }

      if(includeEndBrackets) return cppReturnFunction+";";
      else return cppReturnFunction;
    } else {
      vector<AST> listOfInputParameters;
      listOfInputParameters.resize(0);
      for(int indexP = 0;indexP < astTree.subs.size();indexP++) {
        listOfInputParameters.push_back(astTree.subs[indexP]);
      }
      if(includeEndBrackets) return generator(replaceWithParameters(findFunctionCall(astTree.data).astToReplace, listOfInputParameters), true);
      else return generator(replaceWithParameters(findFunctionCall(astTree.data).astToReplace, listOfInputParameters), false);
    }
  } else return astTree.data;
}

void headerList(AST *astRead) {
  for(int i = 0; i < (*astRead).subs.size();) {
    if((*astRead).subs[i].data=="lib_cinclude") {
      for(int i2 = 0; i2 < (*astRead).subs[i].subs.size(); i2++) {
        if(count(listOfHeaders.begin(), listOfHeaders.end(), (*astRead).subs[i].subs[i2].data)<=0) {
          listOfHeaders.push_back((*astRead).subs[i].subs[i2].data);
        }
      }
      
      (*astRead).subs.erase((*astRead).subs.begin()+i);
    } else if((*astRead).subs[i].data=="lib_include") {
      for(int i2 = 0; i2 < (*astRead).subs[i].subs.size(); i2++) {
        ifstream readNextDependencies(strToVal((*astRead).subs[i].subs[i2].data));
        vector<string> tokensTemp = lexer(&readNextDependencies);
        readNextDependencies.close();

        AST parsedProgramTemp = parse(&tokensTemp);
        headerList(&parsedProgramTemp);
      }
      
      (*astRead).subs.erase((*astRead).subs.begin()+i);

    } else if((*astRead).subs[i].data=="lib_cdefine") {
      
      if((*astRead).subs[i].subs[0].data!="NULL") {
        funcDictionary tempPush;
        tempPush.uscorCall=(*astRead).subs[i].subs[0].data;
        tempPush.astReplace=false;
        string cppCallTemp=strToVal((*astRead).subs[i].subs[1].data);
        if(cppCallTemp[cppCallTemp.length()-1]==')'&&cppCallTemp[cppCallTemp.length()-2]=='(') {
          tempPush.cppCall=substr(cppCallTemp, 0, cppCallTemp.length()-2);
          tempPush.hasParameters=true;
        } else {
          tempPush.cppCall=cppCallTemp;
          tempPush.hasParameters=false;
        }
        functionDictionaryUscor.push_back(tempPush);
      }

      globalDefinedMethods.push_back(strToVal((*astRead).subs[i].subs[2].data));
      
      (*astRead).subs.erase((*astRead).subs.begin()+i);
    } else if((*astRead).subs[i].data=="lib_typedefine") {
      dataTypeKey tempPush;
      tempPush.uscorType=(*astRead).subs[i].subs[0].data;
      tempPush.cMappedType=strToVal((*astRead).subs[i].subs[1].data);

      if((*astRead).subs[i].subs[2].data!="NULL") {
        globalDefinedMethods.push_back(strToVal((*astRead).subs[i].subs[2].data));
      } customDataTypes.push_back(tempPush);
      
      (*astRead).subs.erase((*astRead).subs.begin()+i);
    } else if((*astRead).subs[i].data=="lib_gdefine") {

      funcDictionary tempPush;

      tempPush.uscorCall=(*astRead).subs[i].subs[0].data;
      tempPush.cppCall=(*astRead).subs[i].subs[0].data;
      tempPush.hasParameters=true;
      tempPush.astReplace=false;

      string myFunctionDefinition = dataTypeGet((*astRead).subs[i].subs[1]) + " " + (*astRead).subs[i].subs[0].data;
      myFunctionDefinition+='(';
      if(stoi((*astRead).subs[i].subs[2].data)>0) {
        myFunctionDefinition=myFunctionDefinition+dataTypeGet((*astRead).subs[i].subs[3])+" uscor_lib_functions_param0";
        for(int indexParamsRec=1;indexParamsRec < stoi((*astRead).subs[i].subs[2].data);indexParamsRec++) {
          myFunctionDefinition=myFunctionDefinition+", "+dataTypeGet((*astRead).subs[i].subs[indexParamsRec+3])+" uscor_lib_functions_param"+to_string(indexParamsRec);
        }
      } myFunctionDefinition=myFunctionDefinition+") {";

      for(int indexAct=stoi((*astRead).subs[i].subs[2].data)+3; indexAct<(*astRead).subs[i].subs.size();indexAct++) {
        myFunctionDefinition=myFunctionDefinition+"\n  "+generator(replaceWithSetupParameters((*astRead).subs[i].subs[indexAct]));
      } myFunctionDefinition=myFunctionDefinition+"\n}";

      globalDefinedMethods.push_back(myFunctionDefinition);
      
      functionDictionaryUscor.push_back(tempPush);

      
      (*astRead).subs.erase((*astRead).subs.begin()+i);
    } else if((*astRead).subs[i].data=="lib_ldefine") {

      funcDictionary tempPush;
      tempPush.astReplace=true;
      tempPush.uscorCall=(*astRead).subs[i].subs[0].data;
      tempPush.astToReplace=(*astRead).subs[i].subs[1];

      functionDictionaryUscor.push_back(tempPush);
      
      (*astRead).subs.erase((*astRead).subs.begin()+i);
    } else if((*astRead).subs[i].data=="require") {

      versionNumber compareVersions(stoi((*astRead).subs[i].subs[0].data), stoi((*astRead).subs[i].subs[1].data), stoi((*astRead).subs[i].subs[2].data));
      
      if(versionComparison(compareVersions, minimumCompatibleVersion)==1) programSupported='o';
      else if(programSupported!='o'&&versionComparison(compareVersions, currentVersion)==-1) programSupported='n';
      else if(programSupported!='o'&&programSupported!='n') programSupported='y';

      (*astRead).subs.erase((*astRead).subs.begin()+i);
    } else {
      headerList(&((*astRead).subs[i]));
      i++;
    }
  }
}

void generateHeaders(ofstream *fileOutput, AST *astRead) {
  listOfHeaders={"<iostream>", "<cmath>", "<string.h>", "<fstream>", "<vector>", "<filesystem>"};
  globalDefinedMethods.resize(0);
  functionDictionaryUscor.resize(0);
  customDataTypes.resize(0);
  
  headerList(astRead);
  for(int index=0;index<listOfHeaders.size();index++)
    (*fileOutput)<<"#include "<<listOfHeaders[index]<<endl;
  
  (*fileOutput)<<endl<<"using namespace std;"<<endl<<endl;
  (*fileOutput)<<"string uscor_lib_integrated_func_strins(string s1, int n, string s2) {s1.insert(n, s2);return s2;}"<<endl;
  (*fileOutput)<<"int uscor_lib_integrated_func_strfind(string s1, string s2) {return s1.find(s2);}"<<endl;
  (*fileOutput)<<"string uscor_lib_integrated_func_substr(string s1, int i1, int i2) {return s1.substr(i1, i2);}"<<endl;
  (*fileOutput)<<"bool uscor_lib_integrated_func_strToBool(string s) {for(int i=0;i<s.length();i++) {s[i]=tolower(s[i]);}return(s!=\"false\"&&s!=\"0\"&&s!=\"\");}"<<endl;
  (*fileOutput)<<"int uscor_lib_integrated_func_strcmp(string s1, string s2) {return s1.compare(s2);}"<<endl;
  (*fileOutput)<<"void uscor_lib_integrated_func_execComd(string s) {system(s.c_str());}"<<endl;
  (*fileOutput)<<"void uscor_lib_integrated_func_seek(ifstream *fileInput, char type, int number) {if(type=='b') (*fileInput).seekg(number, ios::beg); else if(type=='e') (*fileInput).seekg(number, ios::end); else (*fileInput).seekg(number, ios::cur);}"<<endl;
  for(int index=0;index<globalDefinedMethods.size();index++)
    (*fileOutput)<<globalDefinedMethods[index]<<endl;
}
void generateMainCode(ofstream *fileOutput, AST *astRead) {
  (*fileOutput)<<endl<<"int main() {"<<endl;
  for(int ind = 0; ind < (*astRead).subs.size(); ind++) (*fileOutput)<<"  "<<generator((*astRead).subs[ind],true)<<endl;
  (*fileOutput)<<"}";
}

#endif