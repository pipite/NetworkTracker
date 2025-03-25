//---------------------------------------------------------------------------

#pragma hdrstop

#include "Urls.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// -----------------------------------------------------
// CLASS XUrls
// -----------------------------------------------------
__fastcall XUrls::XUrls(TForm1 *form) {
	Form = form;
	//Urls =
}

__fastcall XUrls::~XUrls(void) {
	Clear();
}

unsigned __fastcall XUrls::GetCount(void) {
	return Urls.size();
}

void __fastcall XUrls::Clear(void) {
	unsigned int i;

	for (i = 0; i < Urls.size(); i++) delete Urls.at(i);
	Urls.erase(Urls.begin(), Urls.end());
}

XUrl* __fastcall XUrls::GetByIndex(unsigned index) {
	XUrl *p;

	if ( index < Urls.size() ) {
		p = Urls.at(index);
		return p;
	}
	return NULL;
}

XUrl* __fastcall XUrls::Find(UnicodeString name) {
	unsigned int i;

	for (i = 0; i < Urls.size(); i++) {
		if (Urls.at(i)->Name == name) {
			return Urls.at(i);
		}
	}
	return NULL;
}

XUrl* __fastcall XUrls::FindOrAdd(UnicodeString name) {
	XUrl *url;

	url = Find(name);
	if (url != NULL) {
		return url;
	}
	return Add(name);
}

XUrl* __fastcall XUrls::Add(UnicodeString name) {
	Urls.push_back(new XUrl(Form, name));
	return Urls.at(Urls.size() - 1);
}

void __fastcall XUrls::Remove(UnicodeString url) {
	unsigned int i;

	for (i = 0; i < Urls.size(); i++) {
		if (Urls.at(i)->Name == url) {
			delete Urls.at(i);
			Urls.erase(Urls.begin() + i);
			break;
		}
	}
}


void __fastcall XUrls::RemoveAll(void) {
	XUrl *url;
	unsigned i;

	for (i = 0; i < Urls.size(); i++) {
		url = Urls.at(i);
		Remove(url->Name);
		i--;
	}
}

// -----------------------------------------------------------------------------

__fastcall XUrl::XUrl(TForm1 *form, UnicodeString name) {
	Form      = form;
	ICC       = new TIdIcmpClient(NULL);
	ICC->PacketSize = 32;
	ICC->Port       = 0;
	ICC->Protocol   = 1;
	//ICC->IPVersion  = TIdPVersion::Id_IPv4;
	Name      = name;
	ICC->Host = name;
	ICC->ReceiveTimeout = Form->EdTimeOut->Text.ToInt();
	ICC->OnReply = ICCReply;
	Reset();
}

__fastcall XUrl::~XUrl(void) {
	delete ICC;
}

__fastcall XUrl::Ping(void) {
	try {
		ICC->Ping();
//		Sleep(2);
//		if (ICC->ReplyStatus->MsRoundTripTime > 1) {
//			Pingcpt++;
//			if ( ( abs((int)Delay - (int)OldDelay) >= Form->EdSensibility->Text.ToInt() ) || ( Pingcpt == 1) ) {
//				OldDelay = Delay;
//			}
//			Delay = ICC->ReplyStatus->MsRoundTripTime;
//			Delaysum += Delay;
//			Delayavg = (unsigned int) (Delaysum/Pingcpt);
//			if (Delay < Delaymin) Delaymin = Delay;
//			if ( (Delay > Delaymax) && (Delay < ICC->ReceiveTimeout) ) Delaymax = Delay;
//			PingErr = 0;
//		} else {
//			PingErr = 1;
//		}
//		OldSrcIPV4  = SrcIPV4;
//		OldDstIPV4  = DstIPV4;
//		SrcIPV4  = ICC->ReplyStatus->ToIpAddress;
//		DstIPV4  = ICC->ReplyStatus->FromIpAddress;
	} catch (...) {
		PingErr = 2;
	}
}

__fastcall XUrl::Reset(void) {
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
}

void __fastcall XUrl::ICCReply(TComponent *ASender, TReplyStatus * const AReplyStatus) {
	if (ICC->ReplyStatus->MsRoundTripTime > 1) {
		Pingcpt++;
		if ( ( abs((int)ICC->ReplyStatus->MsRoundTripTime - (int)OldDelay) >= Form->EdSensibility->Text.ToInt() ) || ( Pingcpt == 1) ) {
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

