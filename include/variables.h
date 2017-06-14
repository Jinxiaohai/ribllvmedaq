/**
 * @file   variables.h
 * @author xiaohai <xiaohaijin@outlook.com>
 * @date   Mon Jun  5 13:35:58 2017
 * 
 * @brief  some variables.
 */
#ifndef VARIABLES_H
#define VARIABLES_H

#include "TH1D.h"
#include "TSpectrum.h"

const unsigned int CHANNEL_16 = 16;
const unsigned int CHANNEL_32 = 32;
const unsigned int CHANNEL_4  = 4;
const unsigned int THRESHOLDENERGY = 200;  ///< channel

string inputFile;
string si1_outputFileP, si1_outputFileN;
string si2_outputFileP, si2_outputFileN;
string si4_outputFileP, si4_outputFileN;
string si3_outputFile;


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
TModV785   *vmod104 = new TModV785();	//Si1 60um
TModV785   *vmod106 = new TModV785();	//Si2 60um
TModV785   *vmod108 = new TModV785();	//Si4 100um
TModV785   *vmod110 = new TModV785();	//QSD 300um
TModV785   *vmod112 = new TModV785();	//
TModV785N  *vmod114 = new TModV785N();
TModV775N  *vmod116 = new TModV775N();
TModV775   *vmod118 = new TModV775();
TModV775   *vmod120 = new TModV775();

/// channel
double si1_60_p[CHANNEL_16], si1_60_n[CHANNEL_16];
double si2_60_p[CHANNEL_16], si2_60_n[CHANNEL_16];
double si3_qsd300[CHANNEL_16];
double si4_1000_p[CHANNEL_16], si4_1000_n[CHANNEL_16];

TH1D *h_si1_60_p[CHANNEL_16];
TH1D *h_si1_60_n[CHANNEL_16];
TH1D *h_si2_60_p[CHANNEL_16];
TH1D *h_si2_60_n[CHANNEL_16];
TH1D *h_si3_qsd300[CHANNEL_4];
TH1D *h_si4_1000_p[CHANNEL_16];
TH1D *h_si4_1000_n[CHANNEL_16];
TSpectrum *sp_1[CHANNEL_16];
TSpectrum *sn_1[CHANNEL_16];
TSpectrum *sp_2[CHANNEL_16];
TSpectrum *sn_2[CHANNEL_16];
TSpectrum *sp_4[CHANNEL_16];
TSpectrum *sn_4[CHANNEL_16];
TSpectrum *snp_3[CHANNEL_16];

/// char name
char hist_name[256];
char kedu_name[256];
char hist_name_p[256];
char hist_name_n[256];
char kedu_name_p[256];
char kedu_name_n[256];

TH1D *kedu_si1_60_p[CHANNEL_16];
TH1D *kedu_si1_60_n[CHANNEL_16];
TH1D *kedu_si2_60_p[CHANNEL_16];
TH1D *kedu_si2_60_n[CHANNEL_16];
TH1D *kedu_si3_qsd300[CHANNEL_16];
TH1D *kedu_si4_1000_p[CHANNEL_16];
TH1D *kedu_si4_1000_n[CHANNEL_16];

/// 幅值,总共13.
double pulse_in[13] = {1., 2., 5., 10., 14., 20., 24., 30., 42.85, 50.0, 60.0, 71.43, 85.71};

/// alpha energy (MeV)
double alphaEnergy[3] = {5.157, 5.486, 5.805};



#endif /* VARIABLES_H */
