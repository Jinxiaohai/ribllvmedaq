/**
 * @file   Particle.cpp
 * @author xiaohai <xiaohaijin@outlook.com>
 * @date   Tue Jun  6 20:29:13 2017
 * 
 * @brief  The file was created to deat with some errors.
 *         
 */
#include <iostream>
#include <cmath>
#include <string>
using namespace std;


namespace xiaohai
{
  /** 
   * deal with the basic the errors.
   * Created by xiaohai.
   */
  class Exception
  {
  public:
    Exception(const string theMessage="Some errors have happened, please check it.")
      : message(theMessage){ }
    virtual string Zero() const
    {
      return message;
    }
    virtual string OpenError() const
    {
      return message;
    }
    virtual ~Exception(){ }

  private:
    string message;
  };
}
