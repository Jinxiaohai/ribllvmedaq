/**
 * @file   generate.h
 * @author xiaohai <xiaohaijin@outlook.com>
 * @date   Mon Jun  5 12:10:31 2017
 * 
 * @brief  generate a chain.
 */
#ifndef GENERATE_H
#define GENERATE_H

namespace xiaohai
{
  void GetChain(const string InputFile, TChain *&chain)
  {
    const char* inputFile = InputFile.c_str();
    char FileList[1024];
    /// data list 的处理方式
    if ((static_cast<string>(inputFile)).find(".list") != string::npos)
      {
	ifstream input_data(inputFile);
	if (!input_data)
	  {
	    cerr << "parameter error !" << endl;
	  }
	for (;input_data.good();)
	  {
	    input_data.getline(FileList,512);
	    if  ( input_data.good() )
	      {
		/// test the file is ok.
		TFile *ftmp = new TFile(FileList);
		if(!ftmp || !(ftmp->IsOpen()) || !(ftmp->GetNkeys()))
		  {
		    cout << "The root file " << FileList << " is broken." << endl;
		  }
		else
		  {
		    cout << FileList << endl;
		    chain->Add(FileList);
		  }
		delete ftmp;
	      }
	  }
	input_data.close();
      }
    else if((static_cast<string>(inputFile)).find(".root") != string::npos)
      {
	/// test the file is ok.
	TFile *ftmp = new TFile(inputFile);
	if(!ftmp || !(ftmp->IsOpen()) || !(ftmp->GetNkeys()))
	  {
	    cout << "The root file " << FileList << " is broken." << endl;
	  }
	else
	  {
	    cout << inputFile << endl;
	    chain->Add(inputFile);
	  }
	delete ftmp;
      }
    else
      {
	cerr << "parameter is error, please check it." << endl;
      }
  }
}

#endif /* GENERATE_H */
