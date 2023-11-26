#include "Model.h"

using std::string;

namespace s21 {
double Model::Lexeme::calculateLex(double const &arg1) {
  double res{0};
  if (_type == _OPER_2) {
    throw std::invalid_argument("Error: 1 argument given, needs 2 arguments");
  } else {
    if (_name == "ln")
      res = log(arg1);
    else if (_name == "log")
      res = log10(arg1);
    else if (_name == "sqrt")
      res = sqrt(arg1);
    else if (_name == "tan")
      res = tan(arg1);
    else if (_name == "sin")
      res = sin(arg1);
    else if (_name == "cos")
      res = cos(arg1);
    else if (_name == "atan")
      res = atan(arg1);
    else if (_name == "asin")
      res = asin(arg1);
    else if (_name == "acos")
      res = acos(arg1);
    else if (_name == "!")
      res = -1.0 * arg1;
    else
      throw std::invalid_argument("Error: wrong function name");
  }
  return res;
}
double Model::Lexeme::calculateLex(double const &arg1, double const &arg2) {
  double res{0};
  if (_type != _OPER_2) {
    throw std::invalid_argument("Error: 2 arguments given, needs 1 argument");
  } else {
    if (_name == "+")
      res = arg2 + arg1;
    else if (_name == "-")
      res = arg2 - arg1;
    else if (_name == "*")
      res = arg2 * arg1;
    else if (_name == "/")
      res = arg2 / arg1;
    else if (_name == "^")
      res = pow(arg2, arg1);
    else if (_name == "mod")
      res = fmod(arg2, arg1);
    else
      throw std::invalid_argument("Error: wrong function name");
  }
  return res;
}

void Model::readStr(const string &line) {
  // std::cout << "readStr = " << line << std::endl;
  if (line.length() == 0) throw std::invalid_argument("Error: No input");
  size_t len = 0;
  std::string prev = "";
  while (!_st.empty()) _st.pop();
  while (!_qu.empty()) _qu.pop();
  while (!qu_inp.empty()) qu_inp.pop();
  // std::cout << str << std::endl;
  std::string pattern =
      "x|cos|sin|tan|acos|asin|atan|sqrt|ln|log|\\(|\\)|\\+|-|"
      "\\*|\\/|mod|\\^|[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?";
  std::regex r(pattern);
  for (std::sregex_iterator i =
           std::sregex_iterator(line.begin(), line.end(), r);
       i != std::sregex_iterator(); ++i) {
    std::smatch m = *i;
    len += m.str().length();
    if (m.str()[0] >= '0' && m.str()[0] <= '9') {
      const std::string oldLocale = std::setlocale(LC_NUMERIC, nullptr);
      std::setlocale(LC_NUMERIC, "C");
      qu_inp.push(Lexeme(std::stod(m.str())));
      std::setlocale(LC_NUMERIC, oldLocale.c_str());
      prev = "0";
    } else {
      if (m.str() == "-") {
        if (prev == "0" || prev == ")" || prev == "x")
          qu_inp.push(Lexeme("-"));
        else
          qu_inp.push(Lexeme("!"));
      } else {
        qu_inp.push(Lexeme(m.str()));
      }
      prev = m.str();
    }
  }
  if (len != line.length())
    throw std::invalid_argument("Error: wrong expression");
}

std::queue<Model::Lexeme> Model::sortQueue() {
  while (!qu_inp.empty()) {
    // Пока не все токены обработаны:
    //  Прочитать токен.
    Lexeme lex = qu_inp.front();
    qu_inp.pop();
    //  Если токен — число, то добавить его в очередь вывода.
    if (lex.isNum() || lex._name == "x") {
      {
        _qu.push(lex);
      }
      //  Если токен — функция, то поместить его в стек.
      //  Если токен — открывающая скобка, то положить его в стек.
    } else if (lex._type == _OPEN_BR || lex._type == _FUNC) {
      _st.push(lex);
      //  Если токен — закрывающая скобка:
    } else if (lex._type == _CLOSE_BR) {
      //  Пока токен на вершине стека не открывающая скобка
      //     Переложить оператор из стека в выходную очередь.
      //     Если стек закончился до того, как был встречен токен открывающая
      //     скобка, то в выражении пропущена скобка.
      // Выкинуть открывающую скобку из стека, но не добавлять в очередь вывода.
      // Если токен на вершине стека — функция, переложить её в выходную
      // очередь.
      while (!_st.empty() && _st.top()._type != _OPEN_BR) {
        Lexeme _top_stack = _st.top();
        _st.pop();
        _qu.push(_top_stack);
        if (_st.empty()) throw std::invalid_argument("Error: missing parenthesis");
      }
      if (!_st.empty() && _st.top()._type == _OPEN_BR) {
        _st.pop();
      } else {
        if (_st.empty()) throw std::invalid_argument("Error: missing parenthesis");
      }
      // Если токен — оператор op1, то:
      // Пока присутствует на вершине стека токен оператор op2, чей приоритет
      // выше или равен приоритету op1, и при равенстве приоритетов op1 является
      // левоассоциативным:
      //     Переложить op2 из стека в выходную очередь;
      // Положить op1 в стек.
      // } else if (lex._type == _OPER_1 || lex._type == _OPER_2) {
    } else if (lex._type == _OPER_2) {
      while (!_st.empty() &&
             (_st.top()._type == _FUNC ||
              (_st.top()._type == _OPER_1 && _st.top()._prec == lex._prec) ||
              (_st.top()._type == _OPER_2 && _st.top()._prec >= lex._prec))) {
        Lexeme _top_stack = _st.top();
        _st.pop();
        _qu.push(_top_stack);
      }
      _st.push(lex);
    } else if (lex._type == _OPER_1) {
      _st.push(lex);
    } else {
      while (!_st.empty()) {
        Lexeme _top_stack = _st.top();
        _st.pop();
        _qu.push(_top_stack);
      }
    }
  }
  // Если больше не осталось токенов на входе:
  // Пока есть токены операторы в стеке:
  //     Если токен оператор на вершине стека — открывающая скобка, то в
  //     выражении пропущена скобка. Переложить оператор из стека в выходную
  //     очередь.
  while (!_st.empty()) {
    if (_st.top()._type == _OPEN_BR) {
      throw std::invalid_argument("Error: missing parenthesis");
    }
    Lexeme _top_stack = _st.top();
    _st.pop();
    _qu.push(_top_stack);
  }
  return _qu;
}

double Model::calculateQueue(std::queue<Lexeme> _qu, double x = 0) {
  double res = 0;
  while (!_st.empty())
    _st.pop();
  while (!_qu.empty()) {
    Lexeme lex(_qu.front());
    _qu.pop();
    if (lex._name == "x") {
      lex._value = x;
      _st.push(lex);
    } else if (lex.isNum()) {
      _st.push(lex);
    } else {
      if (lex._type == _OPEN_BR || lex._type == _FUNC || lex._type == _OPER_1) {
        if (_st.empty())
          throw std::invalid_argument("Error: wrong expression");
        if (_st.top().isNum()) {
          double val1 = _st.top()._value;
          _st.pop();
          res = lex.calculateLex(val1);
        }
      } else {
        if (_st.empty())
          throw std::invalid_argument("Error: wrong expression");
        if (_st.top().isNum()) {
          double val1 = _st.top()._value;
          _st.pop();
          if (_st.empty())
            throw std::invalid_argument("Error: wrong expression");
          if (_st.top().isNum()) {
            double val2 = _st.top()._value;
            _st.pop();
            res = lex.calculateLex(val1, val2);
          } else {
            throw std::invalid_argument("Error: wrong expression");
          }
        }
      }
      _st.push(Lexeme(res));
    }
  }
  if (_st.empty())
    throw std::invalid_argument("Error: wrong expression");
  res = _st.top()._value;
  _st.pop();
  return res;
}

double Model::makeCalc(string line) {
  // std::cout << "line = " << line << std::endl;
  readStr(line);
  std::queue<Lexeme> tmp_qu = sortQueue();
  // std::cout << "tmp_qu = " << tmp_qu.size() << std::endl;
  double res = calculateQueue(tmp_qu);
  // std::cout << "res = " << res << std::endl;
  return res;
}

}  // namespace s21