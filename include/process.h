/**
 * @file   process.h
 * @author xiaohai <xiaohaijin@outlook.com>
 * @date   Sun Jun  4 16:16:15 2017
 * 
 * @brief  The head file is used to print
 *         process.
 */
namespace xiaohai
{
  void process(const int jentry, const int nentries)
  {
    /// progress
    static char str[100] = "#";
    unsigned int per_entry = 2 * (nentries / 100);
    if (jentry % per_entry == 0)
      {
	cout << "\033[47;36m";
	const int per = ceil(((static_cast<double>(jentry))/nentries ) * 100);
	cout << left << "progress:[" << setw(50) << str
	     << "] " << per << "%" << flush;
	strcat(str, "#");
	usleep(100000);
	cout << "\r" << flush;
	if (per >= 99)
	  {
	    cout << "\033[0m" << endl;
	  } 
      }
    /// progress
  }
}
