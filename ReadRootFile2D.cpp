///////////////////////////////////////////////
// An Raw2ROOT.cpp: main() of Raw2ROOT, used
// for offline data analysis.
// Han Jianlong (08/2012)
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
using namespace std;

//const string gDataPath = "DAQDataPath";








void PrintUsage(char *name);

int main(int argc, char *argv[])
{
        string rawlist, rawfile;
	string dfname;
	unsigned int evtana=0;
	unsigned int startn=0;
	fstream listf;
	vector<string> rawdfname;
	bool inter = false;
	TTree *tree = 0;
	TFile *rfile = 0;
	char hname[200],htitle[200],filenm[200];
        float CsIPed[] = {791.224,  733.772,  716.835,  752.535,  740.792,  754.421,  785.629,  757.22,  
                         739.371,  753.769,  754.408,  742.717,  776.927,  772.875,  741.235,  730.316,  
                         749.794,  786.005,  782.26,  736.172,  736.419,  746.37,  761.024,  763.659,  
                         787.169,  734.829,  728.259,  761.132,  759.596,  763.009,  738.832,  766.617,  
                         738.109,  751.077,  722.741,  744.124,  732.656,  742.131,  706.622,  732.266,  
                         769.737,  711.194,  708.261,  733.68,  732.049,  738.579,  721.986,  740.498,  
                         747.381,  735.941,  733.564,  747.507,  764.418,  744.072,  699.297,  742.641,  
                         760.289,  752.968,  740.611,  752.148,  710.252,  743.344,  738.181,  749.896};	
        float StSiJThr[16] = {66.3503,  18.8228,  47.8497,  20.9574,  37.6425,  59.59,  34.9703,  53.3155,  
                         55.4295,  26.5014,  39.3096,  58.5759,  64.7845,  26.2401,  55.5407,  49.6467};
        float StSiOThr[16] = {86.2438,  46.0111,  70.3495,  64.9409,  82.8725,  61.7663,  59.014,  41.7415,  
                         86.8275,  71.0645,  82.4644,  52.2838,  68.0827,  44.6543,  87.3318,  42.1333};
float StSiJCali[16][2] = {
-0.531595,  0.018054,  
0.290962,  0.0182303,  
-0.177645,  0.0179291,  
0.2904,  0.0181098,  
0.00194314,  0.0183419,  
-0.361781,  0.0180004,  
0.0444717,  0.0182675,  
-0.253003,  0.0182711,  
-0.229327,  0.0176175,  
0.255263,  0.0179991,  
0.0596223,  0.0181894,  
-0.267419,  0.0181743,  
-0.357636,  0.0178602,  
0.265927,  0.0183105,  
-0.269501,  0.0183474,  
-0.138062,  0.0176564};

float StSiOCali[16][2] = {
-0.899932,  0.0183196,  
-0.113776,  0.0181846,  
-0.599779,  0.0182771,  
-0.403109,  0.01824,  
-0.720776,  0.0181904,  
-0.42725,  0.0184066,  
-0.396009,  0.0181221,  
0.49317,  0.0172697,  
-0.908054,  0.0179679,  
-0.633511,  0.0183386,  
-0.823064,  0.017952,  
-0.283395,  0.0176819,  
-0.60907,  0.0181285,  
-0.144706,  0.017986,  
-0.861611,  0.0181782,  
-0.240838,  0.0179486};

// postion parameters for SiStrip and CsI
float posxCsI[64]={-3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5, -3.5,
                   -2.5, -2.5, -2.5, -2.5, -2.5, -2.5, -2.5, -2.5,               
		   -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5,
                   -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,- 0.5,
                    0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,
                    1.5,  1.5,  1.5,  1.5,  1.5,  1.5,  1.5,  1.5,
                    2.5,  2.5,  2.5,  2.5,  2.5,  2.5,  2.5,  2.5,
                    3.5,  3.5,  3.5,  3.5,  3.5,  3.5,  3.5,  3.5};
                  
                    
float posyCsI[64]={-3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,
				   -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5};
                   
                   
float posxStSi[16]={-7.5,-6.5,-5.5,-4.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5};
float posyStSi[16]={-7.5,-6.5,-5.5,-4.5,-3.5,-2.5,-1.5,-0.5,7.5,6.5,5.5,4.5,3.5,2.5,1.5,0.5};
//float posySiSt[16]={0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,-0.5,-1.5,-2.5,-3.5,-4.5,-5.5,-6.5,-7.5};
                                
	TFile fout("/home/vip/data/ppac201407/20140815.root","recreate");
	fout.cd();
        TH2F *h2SiCsIF[64],*h2SiCsIS[64];

        for(int i=0;i<64;i++) {
                sprintf(hname,"h2SiCsI%dFast",i+1);
                h2SiCsIF[i]=new TH2F(hname,hname,200,-0.5,4099.5,200,-1.0,49);
                sprintf(hname,"h2SiCsI%dSlow",i+1);
                h2SiCsIS[i]=new TH2F(hname,hname,200,-0.5,4099.5,200,-1.0,49);
        }
//	
	TModV785N *vmod104 = new TModV785N(); // Square Si at 0
	TModV775N *vmod105 = new TModV775N(); // Timing for TOF && PPAC
	TModV775N *vmod106 = new TModV775N(); // Timing for TOF && PPAC
	TModV775N *vmod107 = new TModV775N(); // Timing for PPAC
	TModV775N *vmod108 = new TModV775N(); // Timing for 10 neutrons at 0-9, for trigger at 10
	TModV785  *vmod110 = new TModV785();  // ADC for 16+16 StSi 
	TModV792  *vmod112 = new TModV792();  // QDC for 10 neutron slow(?) gate
	TModV792  *vmod113 = new TModV792();  // QDC for 10 neutron total(?) gate
	TModV792  *vmod115 = new TModV792();  // 32 CsI QDC Fast
	TModV792  *vmod116 = new TModV792();  // 32 CsI QDC Fast
	TModV792  *vmod118 = new TModV792();  // 32 CsI QDC Slow
	TModV792  *vmod119 = new TModV792();  // 32 CsI QDC Slow
// Loop on file	
        int totalsel;
        totalsel=0;
        for (int ifile=210;ifile<211;ifile++) {
        if(ifile<10) sprintf(filenm,"/home/vip/data/ppac201407/data/Li9Pb208000%d.root",ifile);
        else if(ifile<100) sprintf(filenm,"/home/vip/data/ppac201407/data/Li9Pb20800%d.root",ifile);
        else sprintf(filenm,"/home/vip/data/ppac201407/data/Li9Pb2080%d.root",ifile);
        if(gSystem->AccessPathName(filenm)) {
                printf("no data existing for %s\n",filenm);
                continue;
        }
   cout<<filenm<<endl;     
        TFile f(filenm) ;
	TTree *fChain = (TTree*)gFile->Get("RawData");//fChain can be a TChain
	TBranch *bran103 = 0;
	TBranch *bran104 = 0;
	TBranch *bran106 = 0;
	TBranch *bran107 = 0;
	TBranch *bran108 = 0;
	TBranch *bran110 = 0;
	TBranch *bran112 = 0;
	TBranch *bran113 = 0;
	TBranch *bran115 = 0;
	TBranch *bran116 = 0;
	TBranch *bran118 = 0;
	TBranch *bran119 = 0;
	fChain->SetBranchAddress("Mod104_TModV785N", &vmod104, &bran104);
	fChain->SetBranchAddress("Mod106_TModV775N", &vmod106, &bran106);
	fChain->SetBranchAddress("Mod107_TModV775N", &vmod107, &bran107);
	fChain->SetBranchAddress("Mod110_TModV785",  &vmod110, &bran110);
	fChain->SetBranchAddress("Mod115_TModV792",  &vmod115, &bran115);
	fChain->SetBranchAddress("Mod116_TModV792",  &vmod116, &bran116);
	fChain->SetBranchAddress("Mod118_TModV792",  &vmod118, &bran118);
	fChain->SetBranchAddress("Mod119_TModV792",  &vmod119, &bran119);
	Long64_t nentries = fChain->GetEntriesFast();
	cout << "nentries=" << nentries << endl;
	int MulStSiJ,MulStSiO,MulCsIF,MulCsIS,iSelEvt,iCsIF[64],iCsIS[64],i0;
	float Threshold,EStSiJ[16],EStSiO[16],xStSi[16],yStSi[16],chCsIF[64],xCsIF[64],yCsIF[64],chCsIS[64],xCsIS[64],yCsIS[64];
	iSelEvt=0;
	float ESiJ,ESiO,EtotJ,EtotO;



    //    for(int ientry=0;ientry<nentries;ientry++) 
   for (Long64_t ientry=0; ientry<5;ientry++)

{
        	Long64_t jentry = fChain->LoadTree(ientry);
	        if (jentry < 0) break;
	        fChain->GetEntry(ientry); 
		//do some analysis
		int t1 = vmod107->chdata[0];
		int t2 = vmod107->chdata[1];
		int tof = t2-t1;
		int dE = vmod104->chdata[0];
cout <<" chdata 0 "<< vmod106->chdata[0]<<"  chdata 5 "<< vmod106->chdata[5]<<"    chdata10 "<< vmod106->chdata[10] << endl;
                if((tof<-740&&tof>-790&&dE>800&&dE<1100)) continue;
// Fill 1D histograms for Si and CsI and do some multiplicity analysis
		MulStSiJ=0;
		MulStSiO=0;
		EtotJ=0;
		EtotO=0;
		for(int i=0;i<16;i++) {
		        ESiJ=vmod110->chdata[i]*StSiJCali[i][1]+StSiJCali[i][0];
		        EtotJ+=ESiJ;
		        ESiO=vmod110->chdata[i+16]*StSiOCali[i][1]+StSiOCali[i][0];
		        EtotO+=ESiO;
        		if(ESiJ>0.9) {
                		EStSiJ[MulStSiJ]=ESiJ;
                		xStSi[MulStSiJ]=posxStSi[i]*3;
                		MulStSiJ++;
        		}
        		if(ESiO>0.9) {
                		EStSiO[MulStSiO]=ESiO;
                		yStSi[MulStSiO]=posyStSi[i]*3;
                		MulStSiO++;
         		}
		
		}
		MulCsIF=0;
		MulCsIS=0;
		for(int i=0;i<32;i++) {
               		if(vmod115->chdata[i]>100) {
               		        chCsIF[MulCsIF]=vmod115->chdata[i];
               		        xCsIF[MulCsIF]=posxCsI[i]*25;                        
               		        yCsIF[MulCsIF]=posyCsI[i]*25;
               		        iCsIF[MulCsIF]=i;
               		        MulCsIF++;
               		}
               		if(vmod116->chdata[i]>100) {
               		        chCsIF[MulCsIF]=vmod116->chdata[i];
               		        xCsIF[MulCsIF]=posxCsI[i+32]*25;
               		        yCsIF[MulCsIF]=posyCsI[i+32]*25;
               		        iCsIF[MulCsIF]=i+32;
               		        MulCsIF++;
               		}
        		if(i!=3) {
                		if(vmod118->chdata[i]>150) {
                		        chCsIS[MulCsIS]=vmod118->chdata[i];
                		        xCsIS[MulCsIS]=posxCsI[i]*25;                        
                       		        yCsIS[MulCsIS]=posyCsI[i]*25;
                		        iCsIS[MulCsIS]=i;
                		        MulCsIS++;
                		}
                		if(vmod119->chdata[i]>150) {
                		        chCsIS[MulCsIS]=vmod119->chdata[i];
                		        xCsIS[MulCsIS]=posxCsI[i+32]*25;
                		        yCsIS[MulCsIS]=posyCsI[i+32]*25;
                		        iCsIS[MulCsIS]=i+32;
                		        MulCsIS++;
                		}
                	}
        		
		}
//                if(MulStSiJ==1&&MulStSiO==1&&MulCsIS==1) {
                for(int i=0;i<MulCsIF;i++) {
                        i0=iCsIF[i];
                        for(int j=0;j<MulStSiJ;j++) {
       		                h2SiCsIF[i0]->Fill(chCsIF[i],EStSiJ[j],1.0);
       		        }
                }       		        
       		for(int i=0;i<MulCsIS;i++) {        
       		        i0=iCsIS[0];
       		        for(int j=0;j<MulStSiJ;j++) {
       		                h2SiCsIS[i0]->Fill(chCsIS[i],EStSiJ[j],1.0);
       		        }
                }
//                }
       /*    if( MulCsIF>=3&&MulCsIS>=3)
	 {
//                if(MulStSiJ==1&&MulStSiO==1&&MulCsIS==1) {
                        iSelEvt++;
                        cout << "ievent=" << ientry << endl;
                        cout << "CsI" << endl;
                        for(int i=0;i<MulCsIF;i++) {
                                cout <<"CsI Fast" << i << ":  "<< chCsIF[i] << " x=" << xCsIF[i] << " y=" << yCsIF[i] <<endl;
                        }
                        for(int i=0;i<MulCsIS;i++) {
                                cout <<"CsI Slow" << i << ":  "<< chCsIS[i] << " x=" << xCsIS[i] << " y=" << yCsIS[i] <<endl;
                        }
                        cout << "StSiJ:" << endl;
                        cout << "EtotJ=" << EtotJ << endl;
                        for(int i=0;i<MulStSiJ;i++) {
                                cout << "StSiJ" << i << ":  " << EStSiJ[i] << " x=" << xStSi[i] << endl;
                        }
                        cout << "StSiO:" << endl;
                        cout << "EtotO=" << EtotO << endl;
                        for(int i=0;i<MulStSiO;i++) {
                                cout << "StSiO" << i << ":  " << EStSiO[i] << " y=" << yStSi[i] << endl;
                        }
                        cout << endl;
                }
            */    

	}
	totalsel+=iSelEvt;
       	cout << "ifile=" << ifile<< " iSelEvt=" << iSelEvt << endl;
       	cout << endl;	
       	f.Close();
       	}
       	cout << "total selected events=" << totalsel << endl;
       	fout.cd();
       	fout.Write();
       	fout.Close();
       	
	return 0;
}

void PrintUsage(char *name){
	cout<<"Usage: "<<name<<"  "<<endl;
	cout<<"\t Interactive mode." << endl;
	cout<<"Usage: "<<name<<" listfilename "<<endl;
	cout<<"\t 'listfilename' is a text file contains the 'raw data file names'.";
	cout<<endl;
}
