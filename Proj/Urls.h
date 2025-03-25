//---------------------------------------------------------------------------

#ifndef UrlsH
#define UrlsH

#include <System.Classes.hpp>
#include <System.DateUtils.hpp>
#include <vector>
#include <system.types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIcmpClient.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>

class XUrls;
class XUrl;

#include "Main.h"

class XUrls {
	TForm1 *Form;
	unsigned __fastcall GetCount(void);

	public:
	std::vector <XUrl*> Urls;

			__fastcall XUrls(TForm1 *form);
			__fastcall ~XUrls(void);

	XUrl* __fastcall Find(UnicodeString name);
	XUrl* __fastcall FindOrAdd(UnicodeString name);
	XUrl* __fastcall Add(UnicodeString name);
	XUrl* __fastcall GetByIndex(unsigned index);
	void    __fastcall Remove(UnicodeString name);
	void    __fastcall RemoveAll();
	void    __fastcall Clear(void);

	__declspec(property(get = GetCount)) unsigned Count;
};

class XUrl {
	TForm1 *Form;
	TIdIcmpClient *ICC;

	public:
	UnicodeString Name;
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

			__fastcall XUrl(TForm1 *form, UnicodeString name);
			__fastcall ~XUrl(void);

			__fastcall Ping(void);
			__fastcall Reset(void);

	void __fastcall ICCReply(TComponent *ASender, TReplyStatus * const AReplyStatus);
};


//---------------------------------------------------------------------------
#endif
