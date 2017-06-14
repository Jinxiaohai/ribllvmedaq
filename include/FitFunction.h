/**
 * @file   FitFunction.cpp
 * @author xiaohai <xiaohaijin@outlook.com>
 * @date   Thu Jun  8 09:21:55 2017
 * 
 * @brief  Fit Class for GDR.
 *         Created by xiaohai.
 */
#ifndef FITFUNCTION_H
#define FITFUNCTION_H

#include <string>
#include "console.h"
#include <iostream>
using namespace std;

namespace xiaohai
{
  class LineFit
  {
  public:
  LineFit(string SOMEREMINDER="Linear fitting is in progress......")
    : someReminder(SOMEREMINDER){ }
    virtual ~LineFit(){ }
    virtual double operator()(double *x, double *p)
    {
      PROMPT<string> tishi;
      tishi(cout) << someReminder << tishi.end() << endl;
      return p[1]*x[0] + p[0];
    }
  private:
    string someReminder;
  };
}

#endif /* FITFUNCTION_H */
