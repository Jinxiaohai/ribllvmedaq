#include "TApplication.h"
#include "TDAQApplication.h"
#include "TConfig.h"
#include "TDataFileReader.h"
#include "TDataAnalyser.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TMath.h"
#include "TVector3.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFormula.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TStyle.h"
#include "TText.h"
#include "TLatex.h"
#include "TLine.h"
#include "TPad.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TBranch.h"
#include "TStopwatch.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TF1.h"
#include "TMinuit.h"
#include "TChain.h"
#include "TSpectrum.h"

#include "TBoard.h"
#include "TModV830AC.h"
#include "TModV785.h"
#include "TModV785N.h"
#include "TModV775.h"
#include "TModV775N.h"
#include "TModV792.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <map>
#include<cstdlib>
#include <algorithm>

/// was added by xiaohai.
#include "./include/console.h"
#include "./include/histgram.h"
#include "./include/process.h"
#include "./include/generate.h"
#include "./include/variables.h"
#include "./include/FitFunction.h"
#include "./include/Exception.h"

using namespace std;

int main(int argc,char **argv)
{
  /// print the title.
  xiaohai::Title();

  /// generate a chain.
  string inputFile;
  string si1_outputFileP, si1_outputFileN;
  string si2_outputFileP, si2_outputFileN;
  string si4_outputFileP, si4_outputFileN;
  // string si1_outputFileP, si1_outputFileN;
  if (argc > 1) inputFile = argv[1];
  else inputFile = "../input/input.list";

  if (argc > 2) si1_outputFileP = argv[2];
  else si1_outputFileP = "../output/si1_60_p_outputData.txt";
  if (argc > 3) si1_outputFileN = argv[3];
  else si1_outputFileN = "../output/si1_60_n_outputData.txt";

  if (argc > 4) si2_outputFileP = argv[4];
  else si2_outputFileP = "../output/si2_60_p_outputData.txt";
  if (argc > 5) si2_outputFileN = argv[5];
  else si2_outputFileN = "../output/si2_60_n_outputData.txt";

  if (argc > 6) si4_outputFileP = argv[6];
  else si4_outputFileP = "../output/si4_1000_p_outputData.txt";
  if (argc > 7) si4_outputFileN = argv[7];
  else si4_outputFileN = "../output/si4_1000_n_outputData.txt";

  TChain *fChain = new TChain("RawData");
  xiaohai::GetChain(inputFile, fChain);

  Int_t nentries = (Int_t)fChain->GetEntries();
  cout<<"All the entry number: "<<nentries<<endl;

  /**
   * vmod104 Si1 60um
   * vmod106 Si2 60um
   * vmod108 Si4 100um
   * vmod110 QSD 300um
   */
  fChain->SetBranchAddress("Mod103_TModV830AC", &vmod103, &bran103);
  fChain->SetBranchAddress("Mod104_TModV785",   &vmod104, &bran104);
  fChain->SetBranchAddress("Mod106_TModV785",   &vmod106, &bran106);
  fChain->SetBranchAddress("Mod108_TModV785",   &vmod108, &bran108);
  fChain->SetBranchAddress("Mod110_TModV785",   &vmod110, &bran110);
  fChain->SetBranchAddress("Mod112_TModV785",   &vmod112, &bran112);
  fChain->SetBranchAddress("Mod114_TModV785N",  &vmod114, &bran114);
  fChain->SetBranchAddress("Mod116_TModV775N",  &vmod116, &bran116);
  fChain->SetBranchAddress("Mod118_TModV775",   &vmod118, &bran118);
  fChain->SetBranchAddress("Mod120_TModV775",   &vmod120, &bran120);

  /// definiton
  for(unsigned int i = 0; i != CHANNEL_16; i++)
    {
      /// Si3
      if(i < 4)
	{
	  sprintf(hist_name,"si3_qsd300%d",i);
	  sprintf(kedu_name, "kedu_si3_qsd300%d", i);
	  h_si3_qsd300[i] = new TH1D(hist_name, hist_name, 4095, 1, 4095);
	  kedu_si3_qsd300[i] = new TH1D(kedu_name, kedu_name, 4095, 1, 4095);
	}
      /// Si1
      sprintf(hist_name_p,"si1_60_p%d", i);
      sprintf(hist_name_n,"si1_60_n%d", i);      
      sprintf(kedu_name_p, "kedu_si1_60_p%d", i);
      sprintf(kedu_name_n, "kedu_si1_60_n%d", i);
      h_si1_60_p[i] = new TH1D(hist_name_p, hist_name_p, 4095, 1, 4095);
      h_si1_60_n[i] = new TH1D(hist_name_n, hist_name_n, 4095, 1, 4095);
      kedu_si1_60_p[i] = new TH1D(kedu_name_p, kedu_name_p, 4095, 1, 4095);
      kedu_si1_60_n[i] = new TH1D(kedu_name_n, kedu_name_n, 4095, 1, 4095);      
      /// Si2
      sprintf(hist_name_p,"si2_60_p%d", i);
      sprintf(hist_name_n,"si2_60_n%d", i);      
      sprintf(kedu_name_p, "kedu_si2_60_p%d", i);
      sprintf(kedu_name_n, "kedu_si2_60_n%d", i);
      h_si2_60_p[i] = new TH1D(hist_name_p, hist_name_p, 4095, 1, 4095);
      h_si2_60_n[i] = new TH1D(hist_name_n, hist_name_n, 4095, 1, 4095);
      kedu_si2_60_p[i] = new TH1D(kedu_name_p, kedu_name_p, 4095, 1, 4095);
      kedu_si2_60_n[i] = new TH1D(kedu_name_n, kedu_name_n, 4095, 1, 4095);      
      /// Si4
      sprintf(hist_name_p, "si4_1000_p%d", i);
      sprintf(hist_name_n, "si4_1000_n%d", i);
      sprintf(kedu_name_p, "kedu_si4_1000_p%d", i);      
      sprintf(kedu_name_n, "kedu_si4_1000_n%d", i);      
      h_si4_1000_p[i] = new TH1D(hist_name_p, hist_name_p, 4095, 1, 4095);
      h_si4_1000_n[i] = new TH1D(hist_name_n, hist_name_n, 4095, 1, 4095);
      kedu_si4_1000_p[i] = new TH1D(kedu_name_p, kedu_name_p, 4095, 1, 4095);
      kedu_si4_1000_n[i] = new TH1D(kedu_name_n, kedu_name_n, 4095, 1, 4095);

      sp_1[i] = new TSpectrum(16);
      sn_1[i] = new TSpectrum(16);
      sp_2[i] = new TSpectrum(16);
      sn_2[i] = new TSpectrum(16);
      sp_4[i] = new TSpectrum(16);
      sn_4[i] = new TSpectrum(16);
    }
    


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      /// progress
      xiaohai::process(jentry, nentries);

      Long64_t ientry = fChain->LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      
      /// vmod104, first Si
      for (unsigned int i = 0; i != CHANNEL_16; ++i)
      	{
	  if (vmod104->chdata[i] > 100)
	    {
	      si1_60_p[i] = vmod104->chdata[i];
	      h_si1_60_p[i]->Fill(si1_60_p[i]);
	    }
          if (vmod104->chdata[i+CHANNEL_16] > 100)
            {
              si1_60_n[i] = vmod104->chdata[i+CHANNEL_16];
              h_si1_60_n[i]->Fill(si1_60_n[i]);
            }
      	}
      /// vmod106, second Si
      for (unsigned int i = 0; i != CHANNEL_16; ++i)
      	{
          if (vmod106->chdata[i] > 100)
            {
              si2_60_p[i] = vmod106->chdata[i];
              h_si2_60_p[i]->Fill(si2_60_p[i]);
            }
      	  if (i < 8)
      	    {
              if (vmod106->chdata[23-i] > 100)
                {
                  si2_60_n[i] = vmod106->chdata[23-i];
                  h_si2_60_n[i]->Fill(si2_60_n[i]);
                }
      	    }
      	  else
      	    {
              if (vmod106->chdata[39-i] > 100)
                {
                  si2_60_n[i] = vmod106->chdata[39-i];
                  h_si2_60_n[i]->Fill(si2_60_n[i]);
                }
      	    }
      	}
      /// vmod108, fourth Si
      for (unsigned int i = 0; i != CHANNEL_16; ++i)
      	{
          if (vmod108->chdata[i] > 100)
            {
              si4_1000_p[i] = vmod108->chdata[i];
              h_si4_1000_p[i]->Fill(si4_1000_p[i]);
            }
          if (vmod108->chdata[i+CHANNEL_16] > 100)
            {
              si4_1000_n[i] = vmod108->chdata[i+CHANNEL_16];
              h_si4_1000_n[i]->Fill(si4_1000_n[i]);
            }
      	}
      /// vmod110, third Si
      for (unsigned int i = 0; i != CHANNEL_16; ++i)
      	{
          if (vmod110->chdata[i] > 100)
            {
              si3_qsd300[i] = vmod110->chdata[i];
            }
	  if (i < 4)
	    {
	      h_si3_qsd300[i]->Fill(si3_qsd300[i]);
	    }
      	}
    }
  
  //////////////////////////////////////////////////////////////////////  
  /// deal with si1_60_p
  ofstream si1_60_p_outputData(si1_outputFileP);
  si1_60_p_outputData << setw(20) <<  "Si1 p number" << "   "
                      << setw(20) << "first parameter" << "   "
                      << setw(20) << "second parameter" << "   "
                      << setw(20) << "X-axis intercept"
                      << endl;
  for (unsigned i = 0; i != CHANNEL_16; ++i)
    {
      sp_1[i]->Search(h_si1_60_p[i], 1, "same", 0.05);
      const int PEAKS = sp_1[i]->GetNPeaks();
      double *X = new double[PEAKS];
      for (int j = 0; j != PEAKS; ++j)
  	{
  	  X[j] = *(sp_1[i]->GetPositionX()+j);
  	}
      sort(X, X+PEAKS);
      // for (int j = 0; j != PEAKS; ++j)
      for (int j = 0; j != 6; ++j)
  	{
  	  kedu_si1_60_p[i]->Fill(X[j], pulse_in[j]);
  	}
      xiaohai::LineFit *linefit = new xiaohai::LineFit();
      TF1 *fitfunc = new TF1("fitfunc", linefit, 1, 4095, 2);
      kedu_si1_60_p[i]->Fit(fitfunc);
      /// Set Points.
      fitfunc->SetNpx(1000);
      si1_60_p_outputData << setw(20) << i << "   "
                          << setw(20) << fitfunc->GetParameter(0) << "   "
                          << setw(20) << fitfunc->GetParameter(1) << "   "
                          << setw(20) << -(fitfunc->GetParameter(0))/fitfunc->GetParameter(1)
                          << endl;
      delete [] X;
      delete fitfunc;
      delete linefit;
    }
  si1_60_p_outputData.close();

  
  /// deal with si1_60_n
  ofstream si1_60_n_outputData(si1_outputFileN);
  si1_60_n_outputData << setw(20) <<  "Si1 n number" << "   "
                      << setw(20) << "first parameter" << "   "
                      << setw(20) << "second parameter" << "   "
                      << setw(20) << "X-axis intercept"
                      << endl;
  for (unsigned i = 0; i != CHANNEL_16; ++i)
    {
      sn_1[i]->Search(h_si1_60_n[i], 1, "same", 0.05);
      const int PEAKS = sn_1[i]->GetNPeaks();
      double *X = new double[PEAKS];
      for (int j = 0; j != PEAKS; ++j)
  	{
  	  X[j] = *(sn_1[i]->GetPositionX()+j);
  	}
      sort(X, X+PEAKS);
      // for (int j = 0; j != PEAKS; ++j)
      for (int j = 0; j != 6; ++j)
  	{
  	  kedu_si1_60_n[i]->Fill(X[j], pulse_in[j]);
  	}
      xiaohai::LineFit *linefit = new xiaohai::LineFit();
      TF1 *fitfunc = new TF1("fitfunc", linefit, 1, 4095, 2);
      kedu_si1_60_n[i]->Fit(fitfunc);
      /// Set Points.
      fitfunc->SetNpx(1000);
      si1_60_n_outputData << setw(20) << i << "   "
                          << setw(20) << fitfunc->GetParameter(0) << "   "
                          << setw(20) << fitfunc->GetParameter(1) << "   "
                          << setw(20) << -(fitfunc->GetParameter(0))/fitfunc->GetParameter(1)
                          << endl;
      delete [] X;
      delete fitfunc;
      delete linefit;
    }
  si1_60_n_outputData.close();
  //////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////  
  /// deal with si2_60_p
  ofstream si2_60_p_outputData(si2_outputFileP);
  si2_60_p_outputData << setw(20) <<  "Si2 p number" << "   "
                      << setw(20) << "first parameter" << "   "
                      << setw(20) << "second parameter" << "   "
                      << setw(20) << "X-axis intercept"
                      << endl;
  for (unsigned i = 0; i != CHANNEL_16; ++i)
    {
      sp_2[i]->Search(h_si2_60_p[i], 1, "same", 0.05);
      const int PEAKS = sp_2[i]->GetNPeaks();
      double *X = new double[PEAKS];
      for (int j = 0; j != PEAKS; ++j)
  	{
  	  X[j] = *(sp_2[i]->GetPositionX()+j);
  	}
      sort(X, X+PEAKS);
      // for (int j = 0; j != PEAKS; ++j)
      for (int j = 0; j != 6; ++j)
  	{
  	  kedu_si2_60_p[i]->Fill(X[j], pulse_in[j]);
  	}
      xiaohai::LineFit *linefit = new xiaohai::LineFit();
      TF1 *fitfunc = new TF1("fitfunc", linefit, 1, 4095, 2);
      kedu_si2_60_p[i]->Fit(fitfunc);
      /// Set Points.
      fitfunc->SetNpx(1000);
      si2_60_p_outputData << setw(20) << i << "   "
                          << setw(20) << fitfunc->GetParameter(0) << "   "
                          << setw(20) << fitfunc->GetParameter(1) << "   "
                          << setw(20) << -(fitfunc->GetParameter(0))/fitfunc->GetParameter(1)
                          << endl;
      delete [] X;
      delete fitfunc;
      delete linefit;
    }
  si2_60_p_outputData.close();

  
  /// deal with si2_60_n
  ofstream si2_60_n_outputData(si2_outputFileN);
  si2_60_n_outputData << setw(20) <<  "Si2 n number" << "   "
                      << setw(20) << "first parameter" << "   "
                      << setw(20) << "second parameter" << "   "
                      << setw(20) << "X-axis intercept"
                      << endl;
  for (unsigned i = 0; i != CHANNEL_16; ++i)
    {
      sn_2[i]->Search(h_si2_60_n[i], 1, "same", 0.05);
      const int PEAKS = sn_2[i]->GetNPeaks();
      double *X = new double[PEAKS];
      for (int j = 0; j != PEAKS; ++j)
  	{
  	  X[j] = *(sn_2[i]->GetPositionX()+j);
  	}
      sort(X, X+PEAKS);
      // for (int j = 0; j != PEAKS; ++j)
      for (int j = 0; j != 6; ++j)
  	{
  	  kedu_si2_60_n[i]->Fill(X[j], pulse_in[j]);
  	}
      xiaohai::LineFit *linefit = new xiaohai::LineFit();
      TF1 *fitfunc = new TF1("fitfunc", linefit, 1, 4095, 2);
      kedu_si2_60_n[i]->Fit(fitfunc);
      /// Set Points.
      fitfunc->SetNpx(1000);
      si2_60_n_outputData << setw(20) << i << "   "
                          << setw(20) << fitfunc->GetParameter(0) << "   "
                          << setw(20) << fitfunc->GetParameter(1) << "   "
                          << setw(20) << -(fitfunc->GetParameter(0))/fitfunc->GetParameter(1)
                          << endl;
      delete [] X;
      delete fitfunc;
      delete linefit;
    }
  si2_60_n_outputData.close();
  //////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////  
  /// deal with si4_1000_p
  ofstream si4_1000_p_outputData(si4_outputFileP);
  si4_1000_p_outputData << setw(20) <<  "Si4 p number" << "   "
                      << setw(20) << "first parameter" << "   "
                      << setw(20) << "second parameter" << "   "
                      << setw(20) << "X-axis intercept"
                      << endl;
  for (unsigned i = 0; i != CHANNEL_16; ++i)
    {
      sp_4[i]->Search(h_si4_1000_p[i], 1, "same", 0.05);
      const int PEAKS = sp_4[i]->GetNPeaks();
      double *X = new double[PEAKS];
      for (int j = 0; j != PEAKS; ++j)
  	{
  	  X[j] = *(sp_4[i]->GetPositionX()+j);
  	}
      sort(X, X+PEAKS);
      // for (int j = 0; j != PEAKS; ++j)
      for (int j = 0; j != 6; ++j)
  	{
  	  kedu_si4_1000_p[i]->Fill(X[j], pulse_in[j]);
  	}
      xiaohai::LineFit *linefit = new xiaohai::LineFit();
      TF1 *fitfunc = new TF1("fitfunc", linefit, 1, 4095, 2);
      kedu_si4_1000_p[i]->Fit(fitfunc);
      /// Set Points.
      fitfunc->SetNpx(1000);
      si4_1000_p_outputData << setw(20) << i << "   "
                          << setw(20) << fitfunc->GetParameter(0) << "   "
                          << setw(20) << fitfunc->GetParameter(1) << "   "
                          << setw(20) << -(fitfunc->GetParameter(0))/fitfunc->GetParameter(1)
                          << endl;
      delete [] X;
      delete fitfunc;
      delete linefit;
    }
  si4_1000_p_outputData.close();

  
  /// deal with si4_1000_n
  ofstream si4_1000_n_outputData(si4_outputFileN);
  si4_1000_n_outputData << setw(20) <<  "Si4 n number" << "   "
                      << setw(20) << "first parameter" << "   "
                      << setw(20) << "second parameter" << "   "
                      << setw(20) << "X-axis intercept"
                      << endl;
  for (unsigned i = 0; i != CHANNEL_16; ++i)
    {
      sn_4[i]->Search(h_si4_1000_n[i], 1, "same", 0.05);
      const int PEAKS = sn_4[i]->GetNPeaks();
      double *X = new double[PEAKS];
      for (int j = 0; j != PEAKS; ++j)
  	{
  	  X[j] = *(sn_4[i]->GetPositionX()+j);
  	}
      sort(X, X+PEAKS);
      // for (int j = 0; j != PEAKS; ++j)
      for (int j = 0; j != 6; ++j)
  	{
  	  kedu_si4_1000_n[i]->Fill(X[j], pulse_in[j]);
  	}
      xiaohai::LineFit *linefit = new xiaohai::LineFit();
      TF1 *fitfunc = new TF1("fitfunc", linefit, 1, 4095, 2);
      kedu_si4_1000_n[i]->Fit(fitfunc);
      /// Set Points.
      fitfunc->SetNpx(1000);
      si4_1000_n_outputData << setw(20) << i << "   "
                          << setw(20) << fitfunc->GetParameter(0) << "   "
                          << setw(20) << fitfunc->GetParameter(1) << "   "
                          << setw(20) << -(fitfunc->GetParameter(0))/fitfunc->GetParameter(1)
                          << endl;
      delete [] X;
      delete fitfunc;
      delete linefit;
    }
  si4_1000_n_outputData.close();
  //////////////////////////////////////////////////////////////////////
  
  

  TFile *saveFile = new TFile("../output/result.root", "RECREATE");

  for (unsigned int i = 0; i != CHANNEL_16; ++i)
    {
      h_si1_60_p[i]->Write();
      h_si1_60_n[i]->Write();
      h_si2_60_p[i]->Write();
      h_si2_60_n[i]->Write();
      h_si4_1000_p[i]->Write();
      h_si4_1000_n[i]->Write();
      
      kedu_si1_60_p[i]->Write();
      kedu_si1_60_n[i]->Write();
      kedu_si2_60_p[i]->Write();
      kedu_si2_60_n[i]->Write();
      kedu_si4_1000_p[i]->Write();
      kedu_si4_1000_n[i]->Write();
      if (i < 4)
	{
	  h_si3_qsd300[i]->Write();
	  // kedu_si3_qsd300[i]->Write();
	}      
    }

  // saveFile->Write();
  return 0;
}
