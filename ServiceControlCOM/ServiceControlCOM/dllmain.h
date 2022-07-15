// dllmain.h: объявление класса модуля.

class CServiceControlCOMModule : public ATL::CAtlDllModuleT< CServiceControlCOMModule >
{
public :
	DECLARE_LIBID(LIBID_ServiceControlCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SERVICECONTROLCOM, "{520defd6-ad15-429b-8a77-32491b91655b}")
};

extern class CServiceControlCOMModule _AtlModule;
