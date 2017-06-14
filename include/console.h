/**
 * @file   Iostream.h
 * @author xiaohai <xiaohaijin@outlook.com>
 * @date   Thu Jun  1 12:57:32 2017
 * 
 * @brief  The classes are used to generate
 *         a pretty console output and are created by xiaohai.
 */
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>

using namespace std;

namespace xiaohai
{
  
  /** 
   * This class is used to generate a promption.
   * 
   * @param Prompt 
   * @param Term 
   */
  template <typename T>
    class PROMPT
    {
    public:
      /// 
    PROMPT(const T &Prompt = "\033[3;32m", const T &Term = "\033[0m")
      : prompt(Prompt), term(Term) { }
      virtual ~PROMPT(){}

      /** 
       * output
       * @return os
       */
      ostream& operator()(ostream& os)
	{
	  os << prompt;
	  return os;
	}
  
      /** 
       * end the control console
       * @return term
       */
      inline const T& end() const
      {
	return term;
      }

    private:
      T prompt;
      T term;
    }; /// template class

  /** 
   * This class is used to generate a warning.
   * 
   * @param Warning 
   * @param Term 
   */
  template <typename T>
    class WARNING
    {
    public:
    WARNING(const T &Warning = "\033[3;33m", const T &Term = "\033[0m")
      : warning(Warning), term(Term) { }
      virtual ~WARNING(){}
  
      ostream& operator()(ostream& os)
	{
	  os << warning;
	  return os;
	}
      /// end the control console
      inline const T& end() const
      {
	return term;
      }
  
    private:
      T warning;
      T term;
    }; /// template class


  /** 
   * This class is used to generate a error.
   * 
   * @param Error 
   * @param Term 
   */
  template <typename T>
    class ERROR
    {
    public:
    ERROR(const T &Error = "\033[3;31m", const T &Term = "\033[0m")
      : error(Error), term(Term) { }
      virtual ~ERROR(){}
  
      ostream& operator()(ostream& os)
	{
	  os << error;
	  return os;
	}
      /// end the control console
      inline const T& end() const
      {
	return term;
      }
  
    private:
      T error;
      T term;
    }; /// template class


  void Title()
  {
    PROMPT<string> reminder;
    WARNING<string> warning;
    ERROR<string> error;
    /// first line
    reminder(cout) << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
		   << reminder.end() << endl;
    /// second line
    reminder(cout) << "#";
    error(cout)    << "                    Giant Dipole Resonance                 ";
    reminder(cout) << "#" << error.end() << endl;

    /// third line
    reminder(cout) << "#";
    error(cout)    << "                        Edition: 1.0                       ";
    reminder(cout) << "#" << error.end() << endl;

    /// fourth line
    reminder(cout) << "#";
    error(cout)    << "              Author: Liu huanling & Jin xiaohai           ";
    reminder(cout) << "#" << error.end() << endl;

    /// fifth line
    reminder(cout) << "#";
    error(cout)    << "               e-mail: liuhuanling@sinap.ac.cn             ";
    reminder(cout) << "#" << error.end() << endl;
  
    /// last line
    reminder(cout) << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
		   << reminder.end() << endl;
    // reminder(cout) << "      Giant Dipole Resonance      " << reminder.end() << endl;
  }
}

#endif /* CONSOLE_H */

