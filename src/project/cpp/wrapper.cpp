#include <iostream>

#include "Model.h"

// typedef char* (*DataReadyCallback)(char* buff);
// DataReadyCallback g_callback;

#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API
#endif

// API void set_callback(DataReadyCallback cb) { g_callback = cb; }

#ifdef __cplusplus
extern "C" {
#endif

API char* makeCalc(char* line) {
  const int BUFF_SIZE = 256;
  static char buff[BUFF_SIZE];
  s21::Model m;
  std::string s(line);
  try {
    double res = m.makeCalc(s);
    std::cout << line << "\t" << res << std::endl;
    snprintf(buff, BUFF_SIZE, "%f", res);
  } catch (std::exception& e) {
    snprintf(buff, BUFF_SIZE, "%s", e.what());
  }
  return buff;
}
#ifdef __cplusplus
}
#endif
