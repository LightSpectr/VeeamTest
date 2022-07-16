// ServiceManager.h: объявление CServiceManager

#pragma once
#include "resource.h"       // основные символы
#include <tchar.h>
#include <windows.h>
#include <atlstr.h>

#include "ServiceControlCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CServiceManager

class ATL_NO_VTABLE CServiceManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceManager, &CLSID_ServiceManager>,
	public IDispatchImpl<IServiceManager, &IID_IServiceManager, &LIBID_ServiceControlCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CServiceManager()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CServiceManager)
	COM_INTERFACE_ENTRY(IServiceManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

private:
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	CString serviceName;
	INT LastError;
	INT CurrentState;
	INT ExitCode;
	INT CheckPoint;
	INT WaitHint;
public:



	STDMETHOD(startSvc)();
	STDMETHOD(stopSvc)();

	STDMETHOD(get_ServiceName)(BSTR* pVal);
	STDMETHOD(put_ServiceName)(BSTR newVal);
	STDMETHOD(get_LastError)(INT* pVal);
	STDMETHOD(get_CurrentState)(INT* pVal);
	STDMETHOD(get_ExitCode)(INT* pVal);
	STDMETHOD(get_CheckPoint)(INT* pVal);
	STDMETHOD(get_WaitHint)(INT* pVal);
	
	
};

OBJECT_ENTRY_AUTO(__uuidof(ServiceManager), CServiceManager)
