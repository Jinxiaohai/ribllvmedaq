////////////////////////////////////////////////
// Some Userdefined functions used for 
// Online program.
// Han Jianlong (08/2012)
////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "TROOT.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TF1.h"
#include "TList.h"
#include "TOnlineFrame.h"
#include "TOnline.h"

void def_TH1F(int hid, const char *hname, int bins, float xmin, float xmax);
void hfill1(int hid, float value, float weight);
void def_TH2F(int hid, const char *hname, int xbins, float xmin, float xmax, int ybins, float ymin, float ymax);
void hfill2(int hid, float x, float y, float weight);
extern int  GetRawData(int Crate, int Geo, int channel);
extern void HBOOK1(int id, const char *title, int nxbin, float xlow, float xup, float vmx);
extern void HBOOK2(int id, const char *title, int nxbin, float xlow, float xup, int nybin, float ylow, float yup, float vmx);
extern void HF1(int id, float x, float weight);
extern void HF2(int id, float x, float y, float weight);
extern bool HEXIST(int ihist);


void UserTH_Init()
{
	//For safety, use only 'def_TH1F()' and 'def_TH2F()' in this function
	def_TH1F(1001, "T2-T1", 250, -50, 350.);
	def_TH1F(1002, "tofcal", 400, 0., 400.);
	def_TH1F(1003, "dE", 4000, 0.5, 4000.5);
	def_TH1F(1004, "dEcal", 200, 0.5, 80.5);
	def_TH2F(1005, "Tof-dE", 250, 50., 400.,300, 0, 4096.);
        def_TH2F(1006, "Tofcal_dEcal", 120, 160, 240, 180, 0, 90);
	def_TH2F(2001, "Tofcal-dsi1cal-cut",100,169,184,50,2,5);//added by shicz
	def_TH2F(2003, "Tofcal-dsi1cal",200,150,250,100,10,50);//added by shicz	
	def_TH1F(2004, "dsi1",200, 10, 3500.);//added by wangyuting
	def_TH2F(2005, "Tof-dsi1", 150, 0, 150., 500, 500, 3000.);//added by wangyuting
	def_TH2F(2006, "si1_posi", 16, 0, 16., 16, 0, 16.);//added by wangyuting
	def_TH2F(2007, "si2_posi", 16, 0, 16., 16, 0, 16.);//added by wangyuting
	def_TH2F(2008, "si4_posi", 16, 0, 16., 16, 0, 16.);//added by wangyuting
	def_TH2F(2009,"si3_si2",406,0,4096,406,0,4096);//added by wangyuting
	def_TH2F(2010,"si4_si3",406,0,4096,406,0,4096);//added by wangyuting
}

void UserTH_Fill() 
{
	//GetRawData(Crate, Geo, channel), channel:[0, ..]
	int T1 = GetRawData(1, 16, 0);
	int T2 = GetRawData(1, 16, 1);
			
//*******added by wangyuting****************************
       int si1[32];
       for(int i=0;i<32;i++)
       {
         si1[i]=GetRawData(1,4,i);
       }
        int si4[32];
       for(int i=0;i<32;i++)
       {
         si4[i]=GetRawData(1,8,i);
       }
       
       int si3[4];
       for(int i=0;i<4;i++)
       {
         si3[i]=GetRawData(1,10,i);
       }
      
      int si2[32];
       for(int i=0;i<16;i++)
       {
         si2[i]=GetRawData(1,6,i);
       
     
         if(i<8)
         {
              si2[i+16]=GetRawData(1,6,23-i);
         }
         else
         { 
             si2[i+16]=GetRawData(1,6,39-i);
         }
      }

//*******added by wangyuting*************************
 
//**************************added by wangyuting************************************
    int si1_p_max=si1[0],si1_p_max_index=0,
        si1_n_max=si1[0],si1_n_max_index=0;
    for(int i=0;i<16;i++)
    {
      if(si1[i]>si1_p_max)
      {
        si1_p_max=si1[i];
	si1_p_max_index=i;
      }
    if(si1[i+16]>si1_n_max)
      {
        si1_n_max=si1[i+16];
	si1_n_max_index=i;
      }
   }
    int si4_p_max=si4[0],si4_p_max_index=0,
        si4_n_max=si4[0],si4_n_max_index=0;
    for(int i=0;i<16;i++)
    {
      if(si4[i]>si4_p_max)
      {
        si4_p_max=si4[i];
	si4_p_max_index=i;
      }
    if(si4[i+16]>si4_n_max)
      {
        si4_n_max=si4[i+16];
	si4_n_max_index=i;
      }
   }

int si2_p_max=si2[0],si2_p_max_index=0,
        si2_n_max=si2[0],si2_n_max_index=0;
    for(int i=0;i<16;i++)
    {
      if(si2[i]>si2_p_max)
      {
        si2_p_max=si2[i];
	si2_p_max_index=i;
      }
    if(si2[i+16]>si2_n_max)
      {
        si2_n_max=si2[i+16];
	si2_n_max_index=i;
      }
   }
 int si3_max=si3[0],si3_max_index=0;
    for(int i=0;i<4;i++)
    {
      if(si3[i]>si3_max)
      {
        si3_max=si3[i];
	si3_max_index=i;
      }
   }
  
//************************end added by wangyuting*******************************
	
	
	int t21 = T2-T1;                     hfill1(1001, t21, 1);
	float tofcal = (T2-T1)*0.30702 + 157.124;  hfill1(1002, tofcal, 1);
	
	
	int de = GetRawData(1, 14, 0);       hfill1(1003, de, 1);
	float decal = de*0.02878 -1.59115;         hfill1(1004, decal, 1);
	
	
	hfill2(1005, t21, de, 1);
   //*******added by wangyuting***********************
   float si1shicz;
   si1shicz=si1_p_max*0.01107*1.4-0.68859-0.51;
   if(tofcal>169&&tofcal<184&&si1shicz>2&&si1shicz<5) hfill2(2001,tofcal,si1shicz,1);//added by shicz
   if(t21>0&&si1_p_max>100) hfill2(2003,tofcal,si1_p_max*0.01107*1.4-0.68859-0.51,1);//added by shicz
   hfill1(2004,si1_p_max,1);
   hfill2(2005,t21,si1_p_max,1);
 // if(t21>72.36&&t21<84.08&&si1_p_max>1589.14&&si1_p_max<1992.53&&si1_n_max>250)
  if(si1_p_max>250&&si1_n_max>250)
   {
     hfill2(2006,si1_p_max_index,si1_n_max_index,1); 
   }

 // if(t21>72.36&&t21<84.08&&si1_p_max>1589.14&&si1_p_max<1992.53&&si2_p_max>250&&si2_n_max>250)
  if(si2_p_max>100&&si2_n_max>100)
   {
     hfill2(2007,15-si2_n_max_index,si2_p_max_index,1); 
   }
  // if(t21>72.36&&t21<84.08&&si1_p_max>1589.14&&si1_p_max<1992.53&&si4_n_max>250)
   if(si4_p_max>100&&si4_n_max>100)
   {
     hfill2(2008,si4_p_max_index,si4_n_max_index,1); 
   }
  if(si3_max>250&&si2_p_max>250)
   {
     hfill2(2009,si3_max,si2_p_max,1); 
   }
  if(si4_p_max>250&&si3_max>250)
   {
     hfill2(2010,si4_p_max,si3_max,1); 
   }

//*********ended by wangyuting***********************
	hfill2(1006, tofcal, decal, 1);

}

void OnlineUserFunction(TOnlineFrame *onl)
{
	//TF1 *func1 = new TF1("func1","sqrt(-x*x-10*x)-5" , -10, 0);
	//TF1 *func2 = new TF1("func1","-sqrt(-x*x-10*x)-5", -10, 0);

	//if(onl->datafile->Get("h272") )
	//{
	//	TList *thfunclist = ( (TH1*)(onl->datafile->Get("h272") ) )->GetListOfFunctions();
	//	if(thfunclist)
	//	{
	//		thfunclist->Add(func1);
	//		thfunclist->Add(func2);
	//	}
	//}

}

//capsulize of 'TH1F()', for safety
void def_TH1F(int hid, const char *hname, int bins, float xmin, float xmax)
{
	if( HEXIST(hid) )
	{
		cout << "Histogram ID: " << hid << " (mod_id*100+ch_num) already exist." << endl;
		return;
	}
	else
	{
		char name[30];
		strncpy(name, hname, sizeof(name));
		HBOOK1(hid, name, bins, xmin, xmax, 0.);
	}
}

//capsulize of 'TH2F()', for safety
void def_TH2F(int hid, const char *hname, int xbins, float xmin, float xmax, int ybins, float ymin, float ymax)
{
	if( HEXIST(hid) )
	{
		cout << "Histogram ID: " << hid << " (mod_id*100+ch_num) already exist. " << endl;
		return;
	}
	else
	{
		char name[30];
		strncpy(name, hname, sizeof(name));
		HBOOK2(hid, name, xbins, xmin, xmax, ybins, ymin, ymax, 0.);
	}
}

//capsulize of 'TH1F::Fill(....)', for safety
void hfill1(int hid, float value, float weight=1.)
{
	if(HEXIST(hid)) HF1(hid, value, weight);
}

//capsulize of 'TH2F::Fill(....)', for safety
void hfill2(int hid, float x, float y, float weight = 1.)
{
	if(HEXIST(hid)) HF2(hid, x, y, weight);
}
