//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIcmpClient.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>
#include "perfgrap.h"
#include <Vcl.ExtCtrls.hpp>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#include <string>



#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")

class TForm1;

//---------------------------------------------------------------------------
class TForm1 : public TForm {
__published:	// Composants gérés par l'EDI
	TListBox *LbxLog;
	TButton *BtnStart;
	TButton *BtnStop;
	TEdit *EdLoopDelay;
	TPerformanceGraph *PerformanceGraph1;
	TTimer *LoopTimer;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *EdTimeOut;
	TLabel *Label3;
	TEdit *EdSensibility;
	TLabel *Label4;
	TEdit *EdAlarm;
	TCheckBox *CbAutostart;
	TCheckBox *CbHidden;
	TEdit *EdLogPath;
	TLabel *Label5;
	TEdit *EdUrl;
	TEdit *EdDelay;
	TLabel *Label6;
	TEdit *EdAutoSave;
	void __fastcall BtnStartClick(TObject *Sender);
	void __fastcall BtnStopClick(TObject *Sender);
	//void __fastcall ICmpCliReply(TComponent *ASender, TReplyStatus * const AReplyStatus);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LoopTimerTimer(TObject *Sender);
	void __fastcall ICCReply(TComponent *ASender, TReplyStatus * const AReplyStatus);



private:	// Déclarations utilisateur
   	TIdIcmpClient *ICC;

	bool Running;
	UnicodeString ComputerName;

	void __fastcall SaveLog(void);
	void __fastcall Reset(void);
	void __fastcall IntfOnOff(bool onoff);
	void __fastcall ReadUrls(void);
	void __fastcall Log(void);
		 __fastcall Ping(void);
	int __fastcall Ping2(void);

	UnicodeString SrcIPV4;
	UnicodeString DstIPV4;
	UnicodeString OldSrcIPV4;
	UnicodeString OldDstIPV4;
	unsigned int  Delay;
	unsigned int  Delaymin;
	unsigned int  Delaymax;
	unsigned int  Delayavg;
	unsigned int  Delaysum;
	unsigned int  Pingcpt;
	unsigned int  PingErr;
	unsigned int  OldDelay;

public:		// Déclarations utilisateur
	__fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
