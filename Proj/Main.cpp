//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "perfgrap"
#pragma resource "*.dfm"


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	Running = false;
	ComputerName = GetEnvironmentVariable("COMPUTERNAME");
	ReadUrls();
	Delay     = 99999;
	Delaymin  = Delay;
	Delaymax  = 0;
	Delayavg  = 0;
	Delaysum  = 0;
	Pingcpt   = 0;
	OldDelay  = 99999;
	SrcIPV4   = "";
	DstIPV4   = "";
	PingErr   = 0;
	if (CbAutostart->Checked) BtnStartClick(NULL);
}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	BtnStopClick(NULL);
}

void __fastcall TForm1::SaveLog(void) {
	UnicodeString timestamp;
	timestamp = FormatDateTime(" yyyy_mm_dd hh_nn_ss", Now());
	LbxLog->Items->SaveToFile("NetworkPerf_" + ComputerName + timestamp + ".log");
	LbxLog->Items->Add("Log saved.");
}

void __fastcall TForm1::Reset(void) {
	LbxLog->Clear();
	LbxLog->Items->Add("Sensibility +/- " + EdSensibility->Text + " ms.  ---  TimeOut " + EdTimeOut->Text + " ms.");
}

void __fastcall TForm1::IntfOnOff(bool onoff) {
	EdLoopDelay->Enabled   = onoff;
	EdTimeOut->Enabled     = onoff;
	EdSensibility->Enabled = onoff;
	EdAlarm->Enabled       = onoff;
	BtnStart->Enabled      = onoff;
	BtnStop->Enabled       = !onoff;
}

void __fastcall TForm1::ReadUrls(void) {
	TStringList *ListUrl;
	UnicodeString s, s1, s2;

	ListUrl = new TStringList();

	if (FileExists("ListUrl.cfg")) {
		ListUrl->LoadFromFile("ListUrl.cfg");
	} else if (FileExists("ListUrl.cfg")) {
		ListUrl->LoadFromFile("ListUrl.cfg");
	}

	for (int i = 0; i < ListUrl->Count ; i++) {
		s = Trim(ListUrl->Strings[i]);
		if ( (s.Pos("#") != 1) && (s != "" ) ) {
			s1 = Trim(s.SubString(1,s.Pos("=")-1));
			s2 = Trim(s.SubString(s.Pos("=")+1,255));
			if (s1 == "LoopDelay") {
				EdLoopDelay->Text = s2;
			}
			if (s1 == "TimeOut")     EdTimeOut->Text = s2;
			if (s1 == "Autostart") {
				if (s2 == 0) CbAutostart->Checked = false;
				if (s2 == 1) CbAutostart->Checked = true;
			}
			if (s1 == "Sensibility") EdSensibility->Text = s2;
			if (s1 == "Alarm")       EdAlarm->Text = s2;
			if (s1 == "Autosave")    EdAutoSave->Text = s2;
			if (s1 == "Hidden") {
				if (s2 == 0) CbHidden->Checked = false;
				if (s2 == 1) CbHidden->Checked = true;
			}
			if (s1 == "URL/IP") {
				EdUrl->Text = s2;
			}
		}
	}

	if (CbHidden->Checked) { Form1->WindowState = wsMinimized; }

	delete ListUrl;
}

void __fastcall TForm1::BtnStartClick(TObject *Sender)
{
	if (!Running) {
		ReadUrls();
		Reset();
		IntfOnOff(false);
		LoopTimer->Interval = StrToInt(EdLoopDelay->Text);
		LoopTimer->Enabled = true;
	}
}

void __fastcall TForm1::BtnStopClick(TObject *Sender)
{
	LoopTimer->Enabled = false;
	while (Running);
	SaveLog();
	IntfOnOff(true);
}

void __fastcall TForm1::LoopTimerTimer(TObject *Sender)
{
	UnicodeString str;

	if (!Running) {
		Running = true;
		ICC                 = new TIdIcmpClient(NULL);
		ICC->PacketSize     = 32;
		ICC->Port           = 0;
		ICC->Protocol       = 1;
		ICC->Host           = EdUrl->Text;
		ICC->ReceiveTimeout = EdTimeOut->Text.ToInt();
		ICC->OnReply        = ICCReply;
		Ping();
		Log();
		delete ICC;
		Running = false;
	}
}

__fastcall TForm1::Ping(void) {
	try {
		ICC->Ping();
	} catch (...) {
		PingErr = 2;
	}
}

void __fastcall TForm1::ICCReply(TComponent *ASender, TReplyStatus * const AReplyStatus) {
	if (ICC->ReplyStatus->MsRoundTripTime > 1) {
		Pingcpt++;
		if ( ( abs((int)ICC->ReplyStatus->MsRoundTripTime - (int)OldDelay) >= EdSensibility->Text.ToInt() ) || ( Pingcpt == 1) ) {
			OldDelay = Delay;
			Delay = ICC->ReplyStatus->MsRoundTripTime;
		}

		Delaysum += Delay;
		Delayavg = (unsigned int) (Delaysum/Pingcpt);
		if (Delay < Delaymin) Delaymin = Delay;
		if ( (Delay > Delaymax) && (Delay < ICC->ReceiveTimeout) ) Delaymax = Delay;
		PingErr = 0;
	} else {
		PingErr = 1;
	}
	OldSrcIPV4  = SrcIPV4;
	OldDstIPV4  = DstIPV4;
	SrcIPV4  = ICC->ReplyStatus->ToIpAddress;
	DstIPV4  = ICC->ReplyStatus->FromIpAddress;
}


void __fastcall TForm1::Log(void) {
	UnicodeString str;

	EdDelay->Clear();

	if ( SrcIPV4 != OldSrcIPV4 ) {
		str = FormatDateTime("yyyy/mm/dd:hh.nn.ss", Now());
		str = str + " , Ip Change : Old IP = " + OldSrcIPV4 + " --> New IP =  " +  SrcIPV4;
		LbxLog->Items->Add(str);
	}

	if (Pingcpt > 0) {
		if ( ( abs((int)Delay - (int)OldDelay) >= EdSensibility->Text.ToInt() ) || ( SrcIPV4 != OldSrcIPV4) ) {
			str = FormatDateTime("yyyy/mm/dd:hh.nn.ss", Now());
			str = str + " , " + EdUrl->Text + " , " + SrcIPV4 + " , " + DstIPV4 + " , " + UnicodeString(OldDelay) + " to "+ UnicodeString(Delay) + " ms.";
			if ( Delay < 99999 ) LbxLog->Items->Add(str);
			if ( Delay < EdAlarm->Text.ToInt() ) {
			}
			OldDelay = Delay;
		}
	}
	EdDelay->Text = UnicodeString(Delay) + " ms.";

	if ( Delay < 99999 ) {
		if ( Delay < StrToInt(EdAlarm->Text) ) {
			PerformanceGraph1->DataPoint(clYellow, Delay);
		} else {
			PerformanceGraph1->DataPoint(clYellow, 100);
		}
	}
	PerformanceGraph1->Update();

	if ( Pingcpt >= EdAutoSave->Text.ToInt() ) {
		Pingcpt = 1;
		SaveLog();
	}
}

int __fastcall TForm1::Ping2(void) {
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

