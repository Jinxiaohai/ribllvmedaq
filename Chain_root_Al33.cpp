///////////////////////////////////////////////
// An Chain_root.cpp: main() of torootlevel2, used
// for offline data analysis.
// Kang Wang Modified (05/2016)
///////////////////////////////////////////////

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

using namespace std;

int main()
{
  TString filein;
  int StartNum,EndNum;
  cout<<"Please enter the start number:"<<endl;
  cin>>StartNum;
  cout<<"Please enter the end number:"<<endl;
  cin>>EndNum;

  TString raw_file;
  /// was comment by xiaohai.
  // raw_file="/home/daq/vme-single_201605/vmedata/2016gdr"; //input file name
  // TString root_out_name=Form("%s%04d_%04d.root",raw_file.Data(),StartNum,EndNum); 
  raw_file="/storage/third/ribllData/root/2016gdr";
  TString out_file="/storage/third/ribllData/output/2016gdr";
  TString root_out_name=Form("%s%04d_%04d.root", out_file.Data(), StartNum, EndNum);

  
  cout<<"The output root file is: "<<root_out_name.Data()<<endl;
  TFile *rootf=new TFile(root_out_name.Data(),"recreate");  ///output file
  TTree *ribll_gdr=new TTree("ribll_gdr","gdr");
  
  float scaler[32];
  float si1_60_p[16],si1_60_n[16],si2_60_p[16],si2_60_n[16],
        si3_qsd300[16],si4_1000_p[16],si4_1000_n[16];
  float csi_adc_1[16],csi_adc_2[16],csi_adc_3[16];
  float tof_si_tdc[16],csi_tdc_1[16],csi_tdc_2[16],csi_tdc_3[32];
  
  memset(scaler,      0,    sizeof(scaler));
  memset(si1_60_p,    0,    sizeof(si1_60_p));
  memset(si1_60_n,    0,    sizeof(si1_60_p));
  memset(si2_60_p,    0,    sizeof(si2_60_p));
  memset(si2_60_n,    0,    sizeof(si2_60_p));
  memset(si3_qsd300,  0,    sizeof(si3_qsd300));
  memset(si4_1000_p,  0,    sizeof(si4_1000_p));
  memset(si4_1000_n,  0,    sizeof(si4_1000_n));
  memset(csi_adc_1,   0,    sizeof(csi_adc_1));
  memset(csi_adc_2,   0,    sizeof(csi_adc_2));
  memset(csi_adc_3,   0,    sizeof(csi_adc_3));
  memset(tof_si_tdc,  0,    sizeof(tof_si_tdc));
  memset(csi_tdc_1,   0,    sizeof(csi_tdc_1));
  memset(csi_tdc_2,   0,    sizeof(csi_tdc_2));
  memset(csi_tdc_3,   0,    sizeof(csi_tdc_3));

  ribll_gdr->Branch("scaler",      scaler,      "scaler[32]/F"); 
  ribll_gdr->Branch("si1_60_p",    si1_60_p,    "si1_60_p[16]/F");
  ribll_gdr->Branch("si1_60_n",    si1_60_n,    "si1_60_n[16]/F");
  ribll_gdr->Branch("si2_60_p",    si2_60_p,    "si2_60_p[16]/F");
  ribll_gdr->Branch("si2_60_n",    si2_60_n,    "si2_60_n[16]/F");
  ribll_gdr->Branch("si3_qsd300",  si3_qsd300,  "si3_qsd300[16]/F");
  ribll_gdr->Branch("si4_1000_p",  si4_1000_p,  "si4_1000_p[16]/F");
  ribll_gdr->Branch("si4_1000_n",  si4_1000_n,  "si4_1000_n[16]/F");
  ribll_gdr->Branch("csi_adc_1",   csi_adc_1,   "csi_adc_1[16]/F");
  ribll_gdr->Branch("csi_adc_2",   csi_adc_2,   "csi_adc_2[16]/F");
  ribll_gdr->Branch("csi_adc_3",   csi_adc_3,   "csi_adc_3[16]/F");
  ribll_gdr->Branch("tof_si_tdc",  tof_si_tdc,  "tof_si_tdc[16]/F");
  ribll_gdr->Branch("csi_tdc_1",   csi_tdc_1,   "csi_tdc_1[16]/F");
  ribll_gdr->Branch("csi_tdc_2",   csi_tdc_2,   "csi_tdc_2[16]/F");
  ribll_gdr->Branch("csi_tdc_3",   csi_tdc_3,   "csi_tdc_3[32]/F");

  TH2F *h_TOF_deltaE_p=new TH2F("h_TOF_deltaE_p","h_TOF_deltaE_p",200,0,200,1800,800,2600);
  TH2F *h_TOF_deltaE_n=new TH2F("h_TOF_deltaE_n","h_TOF_deltaE_n",200,0,200,1800,800,2600);
  TH2F *h_si1_Al33_posi=new TH2F("h_si1_Al33_posi","h_si1_Al33_posi",16,0,16,16,0,16);
  TH2F *h_si2_Al33_posi=new TH2F("h_si2_Al33_posi","h_si2_Al33_posi",16,0,16,16,0,16);
  TH2F *h_si3_Al33_posi=new TH2F("h_si3_Al33_posi","h_si3_Al33_posi",2,0,2,2,0,2);
  TH2F *h_si4_Al33_posi=new TH2F("h_si4_Al33_posi","h_si4_Al33_posi",16,0,16,16,0,16);

// scaler  vmod103
  TH1F *h_scaler_T1=new TH1F("h_scaler_T1","h_scaler_T1",200,0,200);
  TH1F *h_scaler_T2=new TH1F("h_scaler_T2","h_scaler_T2",200,0,200);
  TH1F *h_scaler_T1_and_T2=new TH1F("h_scaler_T1&T2","h_scaler_T1&T2",200,0,200);
  TH1F *h_scaler_Gate=new TH1F("h_scaler_Gate","h_scaler_Gate",200,0,200);
  TH1F *h_scaler_Si1_P=new TH1F("h_scaler_Si1_P","h_scaler_Si1_P",200,0,200);
  TH1F *h_scaler_Si2_P=new TH1F("h_scaler_Si2_P","h_scaler_Si2_P",200,0,200);
  TH1F *h_scaler_Si4_P=new TH1F("h_scaler_Si4_P","h_scaler_Si4_P",200,0,200);
  TH1F *h_scaler_Si3=new TH1F("h_scaler_Si3","h_scaler_Si3",200,0,200);

// si1
  TH1F *h_si1_60_p[16];
  TH1F *h_si1_60_p_sum=new TH1F("h_Si1_60_P_sum","h_Si1_60_P_sum",4096,0,4096);
  TH1F *h_si1_60_n[16];
  TH1F *h_si1_60_n_sum=new TH1F("h_Si1_60_N_sum","h_Si1_60_N_sum",4096,0,4096);
  char si1_60_p_name[100];
  char si1_60_n_name[100];
  for (int i=0;i<16;i++)
  {
    sprintf(si1_60_p_name,"h_Si1_60_P%2d",i+1);
    h_si1_60_p[i]=new TH1F(si1_60_p_name,si1_60_p_name,4096,0,4096);
  }
   for (int i=0;i<16;i++)
  {
    sprintf(si1_60_n_name,"h_Si1_60_N%2d",i+1);
    h_si1_60_n[i]=new TH1F(si1_60_n_name,si1_60_n_name,4096,0,4096);
  }

// si2
  TH1F *h_si2_60_p[16];
  TH1F *h_si2_60_p_sum=new TH1F("h_Si2_60_P_sum","h_Si2_60_P_sum",4096,0,4096);
  TH1F *h_si2_60_n[16];
  TH1F *h_si2_60_n_sum=new TH1F("h_Si2_60_N_sum","h_Si2_60_N_sum",4096,0,4096);
  char si2_60_p_name[100];
  char si2_60_n_name[100];
  for (int i=0;i<16;i++)
  {
    sprintf(si2_60_p_name,"h_Si2_60_P%2d",i+1);
    h_si2_60_p[i]=new TH1F(si2_60_p_name,si2_60_p_name,4096,0,4096);
  }
  for (int i=0;i<16;i++)
  {
    sprintf(si2_60_n_name,"h_Si2_60_N%2d",i+1);
    h_si2_60_n[i]=new TH1F(si2_60_n_name,si2_60_n_name,4096,0,4096);
  }

// si4
  TH1F *h_si4_1000_p[16];
  TH1F *h_si4_1000_p_sum=new TH1F("h_Si4_1000_P_sum","h_Si4_1000_P_sum",4096,0,4096);
  TH1F *h_si4_1000_n[16];
  TH1F *h_si4_1000_n_sum=new TH1F("h_Si4_1000_N_sum","h_Si4_1000_N_sum",4096,0,4096);
  char si4_1000_p_name[100];
  char si4_1000_n_name[100];
  for (int i=0;i<16;i++)
  {
    sprintf(si4_1000_p_name,"h_Si4_1000_P%2d",i+1);
    h_si4_1000_p[i]=new TH1F(si4_1000_p_name,si4_1000_p_name,4096,0,4096);
  }
  for (int i=0;i<16;i++)
  {
    sprintf(si4_1000_n_name,"h_Si4_1000_N%2d",i+1);
    h_si4_1000_n[i]=new TH1F(si4_1000_n_name,si4_1000_n_name,4096,0,4096);
  }

// si3
  TH1F *h_si3_qsd300[16];
  TH1F *h_si3_qsd300_sum=new TH1F("h_Si3_qsd300_sum","h_Si3_qsd300_sum",4096,0,4096);
  char si3_qsd300_name[100];
  for (int i=0;i<4;i++)
  {
    sprintf(si3_qsd300_name,"h_Si3_qsd300_%2d",i+1);
    h_si3_qsd300[i]=new TH1F(si3_qsd300_name,si3_qsd300_name,4096,0,4096);
  }

// CsI, ADC
  TH1F *h_csi_adc[42];
  TH1F *h_csi_adc_sum=new TH1F("h_CsI_ADC_sum","h_CsI_ADC_sum",4096,0,4096);
  char csi_adc_name[100];
  for (int i=0;i<42;i++)
  {
    sprintf(csi_adc_name,"h_CsI_ADC_A%2d",i+1);
    h_csi_adc[i]=new TH1F(csi_adc_name,csi_adc_name,4096,0,4096);
  }

// TOF&Si, TDC
  TH1F *h_TOF_T1_TDC=new TH1F("h_TOF_T1_TDC","h_TOF_T1_TDC",4096,0,4096);
  TH1F *h_TOF_T2_TDC=new TH1F("h_TOF_T2_TDC","h_TOF_T2_TDC",4096,0,4096);
  TH1F *h_Si1_P_TDC=new TH1F("h_Si1_P_TDC","h_Si1_P_TDC",4096,0,4096);
  TH1F *h_Si2_P_TDC=new TH1F("h_Si2_P_TDC","h_Si2_P_TDC",4096,0,4096);
  TH1F *h_Si4_P_TDC=new TH1F("h_Si4_P_TDC","h_Si4_P_TDC",4096,0,4096);
  TH1F *h_Si3_TDC=new TH1F("h_Si3_TDC","h_Si3_TDC",4096,0,4096);

// CsI, TDC
  TH1F *h_csi_tdc[42];
  TH1F *h_csi_tdc_sum=new TH1F("h_CsI_TDC_sum","h_CsI_TDC_sum",4096,0,4096);
  char csi_tdc_name[100];
  for (int i=0;i<42;i++)
  {
    sprintf(csi_tdc_name,"h_CsI_TDC_A%2d",i+1);
    h_csi_tdc[i]=new TH1F(csi_tdc_name,csi_tdc_name,4096,0,4096);
  }

  float tof1=0;
  float tof2=0;
  float tof=0;
  int startentries=0;
  int totalentries=0;
  int count=0;
  int Al33_count=0;
  float dist=0.;
  float Al33_purity=0.;



for (int ii=StartNum;ii<=EndNum;ii++)
  {  //start file loop

  TFile *f;
  TString rootfile=Form("%s%04d.root",raw_file.Data(),ii);
  f=new TFile(rootfile.Data(),"read");
  cout<<"The current input root file is:  "<<rootfile<<endl;

  TTree *tree;                   //get the tree in *.root 
  tree=(TTree*)f->Get("RawData");
  Int_t nentries;
  nentries=(Int_t)tree->GetEntries();
  startentries=totalentries;
  totalentries=totalentries+nentries;
  cout<<"The entry number of current file is: "<<nentries<<endl;

  TBranch *bran103 = 0;
  TBranch *bran104 = 0;
  TBranch *bran106 = 0;
  TBranch *bran108 = 0;
  TBranch *bran110 = 0;
  TBranch *bran112 = 0;
  TBranch *bran114 = 0;
  TBranch *bran116 = 0;
  TBranch *bran118 = 0;
  TBranch *bran120 = 0;

  TModV830AC *vmod103 = new TModV830AC(); // 
  TModV785 *vmod104 = new TModV785();   //Si1 60um  
  TModV785 *vmod106 = new TModV785();   //Si2 60um
  TModV785 *vmod108 = new TModV785();   //Si4 100um
  TModV785 *vmod110 = new TModV785();   //QSD 300um
  TModV785 *vmod112 = new TModV785();   //
  TModV785N *vmod114 = new TModV785N();
  TModV775N *vmod116 = new TModV775N();
  TModV775 *vmod118 = new TModV775();
  TModV775 *vmod120 = new TModV775();

  tree->SetBranchAddress("Mod103_TModV830AC",&vmod103,&bran103);
  tree->SetBranchAddress("Mod104_TModV785",&vmod104,&bran104);
  tree->SetBranchAddress("Mod106_TModV785",&vmod106,&bran106);
  tree->SetBranchAddress("Mod108_TModV785",&vmod108,&bran108);
  tree->SetBranchAddress("Mod110_TModV785",&vmod110,&bran110);
  tree->SetBranchAddress("Mod112_TModV785",&vmod112,&bran112);
  tree->SetBranchAddress("Mod114_TModV785N",&vmod114,&bran114);
  tree->SetBranchAddress("Mod116_TModV775N",&vmod116,&bran116);
  tree->SetBranchAddress("Mod118_TModV775",&vmod118,&bran118);  
  tree->SetBranchAddress("Mod120_TModV775",&vmod120,&bran120);  

  for(int ievent =0; ievent<nentries; ievent++)//begin event loop
  {
    tree->GetEntry(ievent);

    tof1 =vmod116->chdata[0];
    tof2 = vmod116->chdata[1];
    tof = tof2- tof1;
    
    float si1_60_p_max_e=0;
    float si1_60_p_max_index=0;
    float si1_60_n_max_e=0;
    float si1_60_n_max_index=0;
    float si2_60_p_max_e=0;
    float si2_60_p_max_index=0;
    float si2_60_n_max_e=0;
    float si2_60_n_max_index=0;
    float si3_qsd300_max_e=0;
    float si3_qsd300_max_x=0;
    float si3_qsd300_max_y=0;
    float si4_1000_p_max_e=0;
    float si4_1000_p_max_index=0;
    float si4_1000_n_max_e=0;
    float si4_1000_n_max_index=0;

    for(int i=0;i<32;i++)    //scaler
    {
      scaler[i]=vmod103->chdata[i];

    }
    
    for(int i=0;i<16;i++)
    {
      si1_60_p[i]=vmod104->chdata[i];      //si1
      si1_60_n[i]=vmod104->chdata[i+16];
      if (si1_60_p[i]>si1_60_p_max_e)
      {
        si1_60_p_max_e=si1_60_p[i];
        si1_60_p_max_index=i;
      }
      if (si1_60_n[i]>si1_60_n_max_e)
      {
        si1_60_n_max_e=si1_60_n[i];
        si1_60_n_max_index=i;
      }

      si2_60_p[i]=vmod106->chdata[i];      //si2
      if(i<8)
      {
        si2_60_n[i]=vmod106->chdata[23-i];
      }
      else
      {
        si2_60_n[i]=vmod106->chdata[39-i];
      }
      if (si2_60_p[i]>si2_60_p_max_e)
      {
        si2_60_p_max_e=si2_60_p[i];
	si2_60_p_max_index=i;
      }
      if (si2_60_n[i]>si2_60_n_max_e)
      {
        si2_60_n_max_e=si2_60_n[i];
	si2_60_n_max_index=i;
      }

      si4_1000_p[i]=vmod108->chdata[i];    //si4
      si4_1000_n[i]=vmod108->chdata[i+16];
      if (si4_1000_p[i]>si4_1000_p_max_e)
      {
        si4_1000_p_max_e=si4_1000_p[i];
	si4_1000_p_max_index=i;
      }
      if (si4_1000_n[i]>si4_1000_n_max_e)
      {
        si4_1000_n_max_e=si4_1000_n[i];
	si4_1000_n_max_index=i;
      }

      si3_qsd300[i]=vmod110->chdata[i];   //si3
      if (i==0) 
      {
        si3_qsd300_max_e=si3_qsd300[i];
        si3_qsd300_max_x=0;
	si3_qsd300_max_y=0;
      }
      if (i==1&&si3_qsd300[i]>si3_qsd300_max_e)
      {
	  si3_qsd300_max_e=si3_qsd300[i];
	  si3_qsd300_max_x=1;
	  si3_qsd300_max_y=0;
      }
      if (i==2&&si3_qsd300[i]>si3_qsd300_max_e)
      {
	  si3_qsd300_max_e=si3_qsd300[i];
	  si3_qsd300_max_x=0;
	  si3_qsd300_max_y=1;
      }
      if (i==3&&si3_qsd300[i]>si3_qsd300_max_e)
      {
	  si3_qsd300_max_e=si3_qsd300[i];
	  si3_qsd300_max_x=1;
	  si3_qsd300_max_y=1;
      }
//    
//    if(ievent<10)
//      cout<<"si3_qsd300  "<<i<<"  "<<si3_qsd300[i]<<endl;
      csi_adc_1[i]=vmod110->chdata[i+16];     //CsI ADC
      csi_adc_2[i]=vmod112->chdata[i];
      csi_adc_3[i]=vmod112->chdata[i+16];
      
      tof_si_tdc[i]=vmod116->chdata[i];       //TOF, Si TDC

      csi_tdc_1[i]=vmod118->chdata[i];        //CsI TDC
      csi_tdc_2[i]=vmod118->chdata[i+16];
    }   // end 16 loop
     
     for(int i=0;i<32;i++) csi_tdc_3[i]=vmod120->chdata[i];

//      ribll_gdr->Fill();    //Output the new tree
//         end get data 

    dist=((si1_60_p_max_e-1775)/200)*((si1_60_p_max_e-1775)/200)+((tof-75)/8)*((tof-75)/8);
    if(dist<=1) 
    {
      if(si1_60_p_max_e>500&&si1_60_n_max_e>500) h_si1_Al33_posi->Fill(si1_60_p_max_index,si1_60_n_max_index);
      if(si2_60_p_max_e>500&&si2_60_n_max_e>500) h_si2_Al33_posi->Fill(15-si2_60_n_max_index,si2_60_p_max_index);
      if(si3_qsd300_max_e>500) h_si3_Al33_posi->Fill(si3_qsd300_max_x,si3_qsd300_max_y);
      for (int i=0;i<16;i++)
      {
        if(si4_1000_p_max_e>500) h_si4_Al33_posi->Fill(i,15-si4_1000_p_max_index);
      }
      
      // scaler
      h_scaler_T1->Fill(scaler[0]);
      h_scaler_T2->Fill(scaler[1]);
      h_scaler_T1_and_T2->Fill(scaler[2]);
      h_scaler_Gate->Fill(scaler[3]);
      h_scaler_Si1_P->Fill(scaler[4]);
      h_scaler_Si2_P->Fill(scaler[5]);
      h_scaler_Si4_P->Fill(scaler[6]);
      h_scaler_Si3->Fill(scaler[7]);

      // Si
      for (int i=0;i<16;i++)
      {
      //Si1
        if (si1_60_p_max_e>500&&si1_60_n_max_e>500)
	{
        h_si1_60_p[i]->Fill(si1_60_p[i]);
	h_si1_60_p_sum->Fill(si1_60_p[i]);
	h_si1_60_n[i]->Fill(si1_60_n[i]);
	h_si1_60_n_sum->Fill(si1_60_n[i]);
        }

      //Si2
        if (si2_60_p_max_e>500&&si2_60_n_max_e>500)
	{
        h_si2_60_p[i]->Fill(si2_60_p[i]);
	h_si2_60_p_sum->Fill(si2_60_p[i]);
	h_si2_60_n[i]->Fill(si2_60_n[i]);
	h_si2_60_n_sum->Fill(si2_60_n[i]);
        }

      //Si4
        if (si4_1000_n_max_e>500)
	{
        h_si4_1000_p[i]->Fill(si4_1000_p[i]);
	h_si4_1000_p_sum->Fill(si4_1000_p[i]);
	h_si4_1000_n[i]->Fill(si4_1000_n[i]);
	h_si4_1000_n_sum->Fill(si4_1000_n[i]);
	}
      }
      for (int i=0;i<4;i++)
      {
        if (si3_qsd300_max_e>500)
        {
        h_si3_qsd300[i]->Fill(si3_qsd300[i]);
	h_si3_qsd300_sum->Fill(si3_qsd300[i]);
        }
      }
      
      //CsI, ADC

      h_csi_adc[0]->Fill(csi_adc_1[0]);
      h_csi_adc[1]->Fill(csi_adc_1[9]);
      h_csi_adc[2]->Fill(csi_adc_1[12]);
      h_csi_adc[3]->Fill(csi_adc_1[3]);
      h_csi_adc[4]->Fill(csi_adc_1[11]);
      h_csi_adc[5]->Fill(csi_adc_1[5]);
      h_csi_adc[6]->Fill(csi_adc_1[6]);
      h_csi_adc[7]->Fill(csi_adc_1[7]);
      h_csi_adc[8]->Fill(csi_adc_1[8]);
      h_csi_adc[9]->Fill(csi_adc_1[1]);
      h_csi_adc[10]->Fill(csi_adc_1[10]);
      h_csi_adc[11]->Fill(csi_adc_1[2]);
      h_csi_adc[12]->Fill(csi_adc_1[13]);
      h_csi_adc[13]->Fill(csi_adc_1[4]);
      h_csi_adc[14]->Fill(csi_adc_1[14]);
      h_csi_adc[15]->Fill(csi_adc_1[15]);
      h_csi_adc[16]->Fill(csi_adc_2[0]);
      h_csi_adc[17]->Fill(csi_adc_2[9]);
      h_csi_adc[18]->Fill(csi_adc_2[13]);
      h_csi_adc[19]->Fill(csi_adc_2[3]);
      h_csi_adc[20]->Fill(csi_adc_2[4]);
      h_csi_adc[21]->Fill(csi_adc_2[5]);
      h_csi_adc[22]->Fill(csi_adc_2[6]);
      h_csi_adc[23]->Fill(csi_adc_2[14]);
      h_csi_adc[24]->Fill(csi_adc_2[8]);
      h_csi_adc[25]->Fill(csi_adc_2[15]);
      h_csi_adc[26]->Fill(csi_adc_2[10]);
      h_csi_adc[27]->Fill(csi_adc_2[1]);
      h_csi_adc[28]->Fill(csi_adc_2[2]);
      h_csi_adc[29]->Fill(csi_adc_2[12]);
      h_csi_adc[30]->Fill(csi_adc_2[7]);
      h_csi_adc[31]->Fill(csi_adc_3[11]);
      h_csi_adc[32]->Fill(csi_adc_3[0]);
      h_csi_adc[33]->Fill(csi_adc_3[8]);
      h_csi_adc[34]->Fill(csi_adc_3[9]);
      h_csi_adc[35]->Fill(csi_adc_3[3]);
      h_csi_adc[36]->Fill(csi_adc_3[1]);
      h_csi_adc[37]->Fill(csi_adc_3[2]);
      h_csi_adc[38]->Fill(csi_adc_3[10]);
      h_csi_adc[39]->Fill(csi_adc_3[4]);
      h_csi_adc[40]->Fill(csi_adc_3[12]);
      h_csi_adc[41]->Fill(csi_adc_3[13]);

      h_csi_adc_sum->Fill(csi_adc_1[0]);
      h_csi_adc_sum->Fill(csi_adc_1[9]);
      h_csi_adc_sum->Fill(csi_adc_1[12]);
      h_csi_adc_sum->Fill(csi_adc_1[3]);
      h_csi_adc_sum->Fill(csi_adc_1[11]);
      h_csi_adc_sum->Fill(csi_adc_1[5]);
      h_csi_adc_sum->Fill(csi_adc_1[6]);
      h_csi_adc_sum->Fill(csi_adc_1[7]);
      h_csi_adc_sum->Fill(csi_adc_1[8]);
      h_csi_adc_sum->Fill(csi_adc_1[1]);
      h_csi_adc_sum->Fill(csi_adc_1[10]);
      h_csi_adc_sum->Fill(csi_adc_1[2]);
      h_csi_adc_sum->Fill(csi_adc_1[13]);
      h_csi_adc_sum->Fill(csi_adc_1[4]);
      h_csi_adc_sum->Fill(csi_adc_1[14]);
      h_csi_adc_sum->Fill(csi_adc_1[15]);
      h_csi_adc_sum->Fill(csi_adc_2[0]);
      h_csi_adc_sum->Fill(csi_adc_2[9]);
      h_csi_adc_sum->Fill(csi_adc_2[13]);
      h_csi_adc_sum->Fill(csi_adc_2[3]);
      h_csi_adc_sum->Fill(csi_adc_2[4]);
      h_csi_adc_sum->Fill(csi_adc_2[5]);
      h_csi_adc_sum->Fill(csi_adc_2[6]);
      h_csi_adc_sum->Fill(csi_adc_2[14]);
      h_csi_adc_sum->Fill(csi_adc_2[8]);
      h_csi_adc_sum->Fill(csi_adc_2[15]);
      h_csi_adc_sum->Fill(csi_adc_2[10]);
      h_csi_adc_sum->Fill(csi_adc_2[1]);
      h_csi_adc_sum->Fill(csi_adc_2[2]);
      h_csi_adc_sum->Fill(csi_adc_2[12]);
      h_csi_adc_sum->Fill(csi_adc_2[7]);
      h_csi_adc_sum->Fill(csi_adc_3[11]);
      h_csi_adc_sum->Fill(csi_adc_3[0]);
      h_csi_adc_sum->Fill(csi_adc_3[8]);
      h_csi_adc_sum->Fill(csi_adc_3[9]);
      h_csi_adc_sum->Fill(csi_adc_3[3]);
      h_csi_adc_sum->Fill(csi_adc_3[1]);
      h_csi_adc_sum->Fill(csi_adc_3[2]);
      h_csi_adc_sum->Fill(csi_adc_3[10]);
      h_csi_adc_sum->Fill(csi_adc_3[4]);
//      h_csi_adc_sum->Fill(csi_adc_3[12]);  //the gain of A41 and of A42 is different from the others
//      h_csi_adc_sum->Fill(csi_adc_3[13]);

     //TOF&Si, TDC
      h_TOF_T1_TDC->Fill(tof_si_tdc[0]);
      h_TOF_T2_TDC->Fill(tof_si_tdc[1]);
      h_Si1_P_TDC->Fill(tof_si_tdc[2]);
      h_Si2_P_TDC->Fill(tof_si_tdc[3]);
      h_Si4_P_TDC->Fill(tof_si_tdc[4]);
      h_Si3_TDC->Fill(tof_si_tdc[5]);

     //CsI, TDC
      h_csi_tdc[0]->Fill(csi_tdc_1[0]);
      h_csi_tdc[1]->Fill(csi_tdc_1[9]);
      h_csi_tdc[2]->Fill(csi_tdc_1[12]);
      h_csi_tdc[3]->Fill(csi_tdc_1[3]);
      h_csi_tdc[4]->Fill(csi_tdc_1[11]);
      h_csi_tdc[5]->Fill(csi_tdc_1[5]);
      h_csi_tdc[6]->Fill(csi_tdc_1[6]);
      h_csi_tdc[7]->Fill(csi_tdc_1[7]);
      h_csi_tdc[8]->Fill(csi_tdc_1[8]);
      h_csi_tdc[9]->Fill(csi_tdc_1[1]);
      h_csi_tdc[10]->Fill(csi_tdc_1[10]);
      h_csi_tdc[11]->Fill(csi_tdc_1[2]);
      h_csi_tdc[12]->Fill(csi_tdc_1[13]);
      h_csi_tdc[13]->Fill(csi_tdc_1[4]);
      h_csi_tdc[14]->Fill(csi_tdc_1[14]);
      h_csi_tdc[15]->Fill(csi_tdc_1[15]);
      h_csi_tdc[16]->Fill(csi_tdc_2[0]);
      h_csi_tdc[17]->Fill(csi_tdc_2[9]);
      h_csi_tdc[18]->Fill(csi_tdc_2[13]);
      h_csi_tdc[19]->Fill(csi_tdc_2[3]);
      h_csi_tdc[20]->Fill(csi_tdc_2[4]);
      h_csi_tdc[21]->Fill(csi_tdc_2[5]);
      h_csi_tdc[22]->Fill(csi_tdc_2[6]);
      h_csi_tdc[23]->Fill(csi_tdc_2[14]);
      h_csi_tdc[24]->Fill(csi_tdc_2[8]);
      h_csi_tdc[25]->Fill(csi_tdc_2[15]);
      h_csi_tdc[26]->Fill(csi_tdc_2[10]);
      h_csi_tdc[27]->Fill(csi_tdc_2[1]);
      h_csi_tdc[28]->Fill(csi_tdc_2[2]);
      h_csi_tdc[29]->Fill(csi_tdc_2[12]);
      h_csi_tdc[30]->Fill(csi_tdc_2[7]);
      h_csi_tdc[31]->Fill(csi_tdc_3[11]);
      h_csi_tdc[32]->Fill(csi_tdc_3[0]);
      h_csi_tdc[33]->Fill(csi_tdc_3[8]);
      h_csi_tdc[34]->Fill(csi_tdc_3[9]);
      h_csi_tdc[35]->Fill(csi_tdc_3[3]);
      h_csi_tdc[36]->Fill(csi_tdc_3[1]);
      h_csi_tdc[37]->Fill(csi_tdc_3[2]);
      h_csi_tdc[38]->Fill(csi_tdc_3[10]);
      h_csi_tdc[39]->Fill(csi_tdc_3[4]);
      h_csi_tdc[40]->Fill(csi_tdc_3[12]);
      h_csi_tdc[41]->Fill(csi_tdc_3[13]);

      h_csi_tdc_sum->Fill(csi_tdc_1[0]);
      h_csi_tdc_sum->Fill(csi_tdc_1[9]);
      h_csi_tdc_sum->Fill(csi_tdc_1[12]);
      h_csi_tdc_sum->Fill(csi_tdc_1[3]);
      h_csi_tdc_sum->Fill(csi_tdc_1[11]);
      h_csi_tdc_sum->Fill(csi_tdc_1[5]);
      h_csi_tdc_sum->Fill(csi_tdc_1[6]);
      h_csi_tdc_sum->Fill(csi_tdc_1[7]);
      h_csi_tdc_sum->Fill(csi_tdc_1[8]);
      h_csi_tdc_sum->Fill(csi_tdc_1[1]);
      h_csi_tdc_sum->Fill(csi_tdc_1[10]);
      h_csi_tdc_sum->Fill(csi_tdc_1[2]);
      h_csi_tdc_sum->Fill(csi_tdc_1[13]);
      h_csi_tdc_sum->Fill(csi_tdc_1[4]);
      h_csi_tdc_sum->Fill(csi_tdc_1[14]);
      h_csi_tdc_sum->Fill(csi_tdc_1[15]);
      h_csi_tdc_sum->Fill(csi_tdc_2[0]);
      h_csi_tdc_sum->Fill(csi_tdc_2[9]);
      h_csi_tdc_sum->Fill(csi_tdc_2[13]);
      h_csi_tdc_sum->Fill(csi_tdc_2[3]);
      h_csi_tdc_sum->Fill(csi_tdc_2[4]);
      h_csi_tdc_sum->Fill(csi_tdc_2[5]);
      h_csi_tdc_sum->Fill(csi_tdc_2[6]);
      h_csi_tdc_sum->Fill(csi_tdc_2[14]);
      h_csi_tdc_sum->Fill(csi_tdc_2[8]);
      h_csi_tdc_sum->Fill(csi_tdc_2[15]);
      h_csi_tdc_sum->Fill(csi_tdc_2[10]);
      h_csi_tdc_sum->Fill(csi_tdc_2[1]);
      h_csi_tdc_sum->Fill(csi_tdc_2[2]);
      h_csi_tdc_sum->Fill(csi_tdc_2[12]);
      h_csi_tdc_sum->Fill(csi_tdc_2[7]);
      h_csi_tdc_sum->Fill(csi_tdc_3[11]);
      h_csi_tdc_sum->Fill(csi_tdc_3[0]);
      h_csi_tdc_sum->Fill(csi_tdc_3[8]);
      h_csi_tdc_sum->Fill(csi_tdc_3[9]);
      h_csi_tdc_sum->Fill(csi_tdc_3[3]);
      h_csi_tdc_sum->Fill(csi_tdc_3[1]);
      h_csi_tdc_sum->Fill(csi_tdc_3[2]);
      h_csi_tdc_sum->Fill(csi_tdc_3[10]);
      h_csi_tdc_sum->Fill(csi_tdc_3[4]);


      Al33_count++;
    }
    if(si1_60_p_max_e>500&&tof>0) 
    {
    h_TOF_deltaE_p->Fill(tof,si1_60_p_max_e);
    count++;
//    cout<<si1_60_p_max_e<<endl;
    }
    if(si1_60_n_max_e>500&&tof>0) h_TOF_deltaE_n->Fill(tof,si1_60_n_max_e);
  

  }//end event loop
    f->Close();
 } //end file loop
 // h_TOF_deltaE_p->Write();
 // h_TOF_deltaE_n->Write();
 // h_si1_Al33_posi->Write();
 // h_si2_Al33_posi->Write();
 // h_si3_Al33_posi->Write();
 // h_si4_Al33_posi->Write();
 // ribll_gdr->Write();
  rootf->Write();
  rootf->Close();
  Al33_purity=Al33_count*1.0/count;
  cout<<"Number of total entries:"<<totalentries<<endl;
  cout<<"Number of events:"<<count<<endl;
  cout<<"Number of Al33:"<<Al33_count<<endl;
  cout<<"Purity of Al33:"<<Al33_purity*100<<"%"<<endl;

}  //end main()
