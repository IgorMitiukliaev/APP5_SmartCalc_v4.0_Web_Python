#pragma once

#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <regex>
#include <stack>
#include <string>

using std::string;

namespace s21 {
class Model {
 private:
  typedef enum {
    _FUNC = 0,
    _OPER_1 = 1,
    _OPER_2 = 2,
    _OPEN_BR = 3,
    _CLOSE_BR = 4,
  } LexType;

 public:
  Model() : str("") {}
  ~Model() { str.clear(); }

 public:
  class Lexeme {
   public:
    string _name;
    double _value;
    short unsigned _prec, _type;
    explicit Lexeme(const string &str) : _name(str), _value(0) {
      if (_name == "(") {
        _prec = 1;
        _type = _OPEN_BR;
      } else if (_name == ")") {
        _prec = 1;
        _type = _CLOSE_BR;
      } else if (_name == "+" || _name == "-") {
        _prec = 2;
        _type = _OPER_2;
      } else if (_name == "mod" || _name == "/" || _name == "*") {
        _prec = 3;
        _type = _OPER_2;
      } else if (_name == "^") {
        _prec = 4;
        _type = _OPER_2;
      } else if (_name == "ln" || _name == "log" || _name == "sqrt" ||
                 _name == "tan" || _name == "sin" || _name == "cos" ||
                 _name == "atan" || _name == "asin" || _name == "acos") {
        _prec = 4;
        _type = _FUNC;
      } else if (_name == "!") {
        _prec = 2;
        _type = _OPER_1;
      } else if (_name == "x") {
        _prec = 0;
      }
    }
    explicit Lexeme(const double &val)
        : _name(""), _value(val), _prec(0), _type(0) {}
    Lexeme(Lexeme const &l)
        : _name(l._name), _value(l._value), _prec(l._prec), _type(l._type) {}
    ~Lexeme() { _name.clear(); }
    double calculateLex(double const &arg1);
    double calculateLex(double const &arg1, double const &arg2);
    bool isNum() { return _prec == 0; }
  };
  std::queue<Lexeme> qu_inp, _qu;
  std::stack<Lexeme> _st;
  std::queue<Lexeme> sortQueue();
  double calculateQueue(std::queue<Lexeme> qu, double x);
  double calcDeposit(int term, double val, double interest, int reinvest,
                     time_t d_date, std::map<time_t, double> payments);
  void doNothing(char *value);
  void readStr(const string &line);
  double makeCalc(string line);

 private:
  int getDaysInMonth(int month, int year);
  string str;
};
}  // namespace s21
