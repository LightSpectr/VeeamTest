// ServiceManager.cpp: реализация CServiceManager

#include "pch.h"
#include "ServiceManager.h"


// CServiceManager



STDMETHODIMP CServiceManager::StartService(TCHAR* SvcName)
{
    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // servicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    return S_OK;
}
