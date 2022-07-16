// ServiceManager.cpp: реализация CServiceManager

#include "pch.h"
#include "ServiceManager.h"


// CServiceManager



STDMETHODIMP CServiceManager::startSvc(INT* Error)
{
    *Error = 0;
    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // servicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 
   
    if (NULL == schSCManager)
    {
        *Error = GetLastError();
        return S_OK;
    }

    schService = OpenService(
        schSCManager,         // SCM database 
        serviceName,            // name of service 
        SERVICE_ALL_ACCESS);  // full access 

    if (schService == NULL)
    {
        *Error = GetLastError();
        CloseServiceHandle(schSCManager);
        return S_OK;
    }
   
    if (!StartService(
        schService,  // handle to service 
        0,           // number of arguments 
        NULL))      // no arguments 
    {
        *Error = GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return S_OK;
    }
  
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
    return S_OK;
}



STDMETHODIMP CServiceManager::get_name(BSTR* pVal)
{
    *pVal = serviceName.AllocSysString();

    return S_OK;
}


STDMETHODIMP CServiceManager::put_name(BSTR newVal)
{
    serviceName = newVal;

    return S_OK;
}
