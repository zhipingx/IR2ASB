// by: Zhiping

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iterator>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <stdint.h>
#include <assert.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>
#include <unistd.h>
#include <typeinfo>
#include <cstdlib>
#include <regex>

namespace LA {

  void debug(std::string str);

  const std::vector< std::string > ARGS = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
  const std::set< std::string > LIBS = { "allocate", "print", "array-error" };

  enum INS { VAR, N, LABEL, ELSE };

  enum TYPE { VOID, TUPLE, CODE, INT };

  class Type {
  public:
    int64_t type;
    int64_t arr_count;

    Type(std::string t);
  };

  struct Function;

  class Var {
  public:
    std::string name;
    LA::Type * type;  // include how many [] are there?
    std::vector< LA::Var * > ts;
    Var(std::string t, std::string n);
    Var(std::string & n, bool hasT=false);
    std::string toString();
  };

  class Instruction {
  public:
    std::string op;
    std::vector< LA::Var * > vars;

    virtual void toIR(std::ofstream &outputFile, LA::Function * currF) = 0;
    virtual std::vector<std::string> toEncode() = 0;
    virtual std::vector<std::string> toDecode() = 0;
  };

  class InsBr: public Instruction {
  public:
    InsBr(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();

  };

  class InsReturn: public Instruction {
  public:
    InsReturn(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsLength: public Instruction {
  public:
    InsLength(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsAssignCall: public Instruction {
  public:
    InsAssignCall(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsAssign: public Instruction {
  public:
    InsAssign(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsOpAssign: public Instruction {
  public:
    InsOpAssign(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsType: public Instruction {
  public:
    InsType(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsCall: public Instruction {
  public:
    InsCall(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsNewArray: public Instruction {
  public:
    InsNewArray(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  class InsNewTuple: public Instruction {
  public:
    InsNewTuple(std::vector<std::string> & v);
    void toIR(std::ofstream &outputFile, LA::Function * currF);
    std::vector<std::string> toEncode();
    std::vector<std::string> toDecode();
  };

  struct Function {
    Type * ret_type;
    std::string name;
    std::map< std::string, LA::Type * > type_map;
    std::vector< LA::Var * > arguments;
    std::vector< LA::Instruction * > inss;
  };

  struct Program {
    std::vector< LA::Function * > functions;
  };

  void printFunc(LA::Function & func);
}
