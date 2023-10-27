#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include "datadef.h"

using namespace std;

string generator(AST astTree, bool includeEndBrackets);

string dataTypeGet(AST astTree) {
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
  else return "NULL1";
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
      else if(dataTypeTo=="bool") return "strToBool("+generator(astTree.subs[2],false)+")";
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
    return "strcmp("+generator(astTree.subs[0],false)+", "+generator(astTree.subs[1],false)+")";
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
    if(includeEndBrackets) return "return 0;";
    else return "return 0";
  } else if(astTree.data=="system_break") {
    if(includeEndBrackets) return "break;";
    else return "break";
  } else if(astTree.data=="math_random_seed") {
    if(includeEndBrackets) return "srand(" + generator(astTree.subs[0],false) + ");";
    else return "srand(" + generator(astTree.subs[0],false) + ")";
  } else if(astTree.data=="system_run_cpp") {
    if(astTree.subs[0].data.length()>=2&&astTree.subs[0].data[0]==34&&astTree.subs[0].data[astTree.subs[0].data.length()]==34) {
      string cppCode=astTree.subs[0].data;
      return cppCode.substr(1, cppCode.size() - 2);
    } else {
      return "";
    }
  } else if(astTree.data=="string_substr") {
    return "substr("+generator(astTree.subs[0],false)+", "+generator(astTree.subs[1],false)+", "+generator(astTree.subs[2],false)+")";
  } else if(astTree.data=="string_find") {
    return "strfind("+generator(astTree.subs[0],false)+","+generator(astTree.subs[1],false)+")";
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
  } else if(astTree.data=="string_length") {
    return "strlen("+generator(astTree.subs[0],false)+")";
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
    if(includeEndBrackets) return "seek(&"+generator(astTree.subs[0],false)+", '"+generator(astTree.subs[1],false)+"', "+generator(astTree.subs[2],false)+");";
    return "seek(&"+generator(astTree.subs[0],false)+", '"+generator(astTree.subs[1],false)+"', "+generator(astTree.subs[2],false)+")";
  } else if(astTree.data=="system_io_file_close") {
    if(includeEndBrackets) return generator(astTree.subs[0],false)+".close();";
    else return generator(astTree.subs[0],false)+".close()";
  } else if(astTree.data=="system_io_file_open") {
    string fileAt = generator(astTree.subs[0],false);
    if(includeEndBrackets) return fileAt+".open("+generator(astTree.subs[1],false)+", ((strfind(typeid("+fileAt+").name(), \"ifstream\")>=0) ? ifstream::in : ofstream::out));";
    else return fileAt+".open("+generator(astTree.subs[1],false)+", ((strfind(typeid("+fileAt+").name(), \"ifstream\")>=0) ? ifstream::in : ofstream::out))";
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
  } else return astTree.data;
}
void generateHeaders(ofstream *fileOutput) {
  (*fileOutput)<<"#include <iostream>"<<endl;
  (*fileOutput)<<"#include <cmath>"<<endl;
  (*fileOutput)<<"#include <string.h>"<<endl;
  (*fileOutput)<<"#include <fstream>"<<endl;
  (*fileOutput)<<"#include <vector>"<<endl;
  (*fileOutput)<<endl<<"using namespace std;"<<endl<<endl;
  (*fileOutput)<<"int strfind(string s1, string s2) {return s1.find(s2);}"<<endl;
  (*fileOutput)<<"string substr(string s1, int i1, int i2) {return s1.substr(i1, i2);}"<<endl;
  (*fileOutput)<<"bool strToBool(string s) {for(int i=0;i<s.length();i++) {s[i]=tolower(s[i]);}return(s!=\"false\"&&s!=\"0\"&&s!=\"\");}"<<endl;
  (*fileOutput)<<"int strcmp(string s1, string s2) {return s1.compare(s2);}"<<endl;
  (*fileOutput)<<"void seek(ifstream *fileInput, char type, int number) {if(type=='b') (*fileInput).seekg(number, ios::beg); else if(type=='e') (*fileInput).seekg(number, ios::end); else (*fileInput).seekg(number, ios::cur);}"<<endl;
}
void generateMainCode(ofstream *fileOutput, AST *astRead) {
  (*fileOutput)<<endl<<"int main() {"<<endl;
  for(int ind = 0; ind < (*astRead).subs.size(); ind++) (*fileOutput)<<" "<<generator((*astRead).subs[ind],true)<<endl;
  (*fileOutput)<<"}";
}

#endif