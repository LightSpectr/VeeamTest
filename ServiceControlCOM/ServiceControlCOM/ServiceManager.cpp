// ServiceManager.cpp: реализация CServiceManager

#include "pch.h"
#include "ServiceManager.h"


// CServiceManager



STDMETHODIMP CServiceManager::startSvc()
{
    LastError = 0;
    SERVICE_STATUS_PROCESS ssStatus;
    DWORD dwOldCheckPoint;
    DWORD dwStartTickCount;
    DWORD dwWaitTime;
    DWORD dwBytesNeeded;



    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // servicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 
   
    if (NULL == schSCManager)
    {
        LastError = GetLastError();
        return E_FAIL;
    }

    schService = OpenService(
        schSCManager,         // SCM database 
        serviceName,            // name of service 
        SERVICE_ALL_ACCESS);  // full access 

    if (schService == NULL)
    {
        LastError = GetLastError();
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // Check the status in case the service is not stopped. 

    if (!QueryServiceStatusEx(
        schService,                     // handle to service 
        SC_STATUS_PROCESS_INFO,         // information level
        (LPBYTE)&ssStatus,             // address of structure
        sizeof(SERVICE_STATUS_PROCESS), // size of structure
        &dwBytesNeeded))              // size needed if buffer is too small
    {
        LastError = GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // Check if the service is already running. 

    if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
    {
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return S_FALSE;
    }

   
    if (!StartService(
        schService,  // handle to service 
        0,           // number of arguments 
        NULL))      // no arguments 
    {
        LastError = GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // Check the status until the service is no longer start pending. 

    if (!QueryServiceStatusEx(
        schService,                     // handle to service 
        SC_STATUS_PROCESS_INFO,         // info level
        (LPBYTE)&ssStatus,             // address of structure
        sizeof(SERVICE_STATUS_PROCESS), // size of structure
        &dwBytesNeeded))              // if buffer too small
    {
        LastError = GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // Save the tick count and initial checkpoint.

    dwStartTickCount = GetTickCount();
    dwOldCheckPoint = ssStatus.dwCheckPoint;

    while (ssStatus.dwCurrentState == SERVICE_START_PENDING)
    {
        // Do not wait longer than the wait hint. A good interval is 
        // one-tenth the wait hint, but no less than 1 second and no 
        // more than 10 seconds. 

        dwWaitTime = ssStatus.dwWaitHint / 10;

        if (dwWaitTime < 1000)
            dwWaitTime = 1000;
        else if (dwWaitTime > 10000)
            dwWaitTime = 10000;

        Sleep(dwWaitTime);

        // Check the status again. 

        if (!QueryServiceStatusEx(
            schService,             // handle to service 
            SC_STATUS_PROCESS_INFO, // info level
            (LPBYTE)&ssStatus,             // address of structure
            sizeof(SERVICE_STATUS_PROCESS), // size of structure
            &dwBytesNeeded))              // if buffer too small
        {
            LastError = GetLastError();
            break;
        }

        if (ssStatus.dwCheckPoint > dwOldCheckPoint)
        {
            // Continue to wait and check.

            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
        }
        else
        {
            if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
            {
                // No progress made within the wait hint.
                break;
            }
        }
    }

    CurrentState = ssStatus.dwCurrentState;
    ExitCode = ssStatus.dwWin32ExitCode;
    CheckPoint = ssStatus.dwCheckPoint;
    WaitHint = ssStatus.dwWaitHint;
   
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

    if (ssStatus.dwCurrentState == SERVICE_RUNNING)
    {
        return S_OK;
    }
    else
    {
        return E_ABORT;
    }

}


STDMETHODIMP CServiceManager::stopSvc()
{
    SERVICE_STATUS_PROCESS ssp;
    DWORD dwStartTime = GetTickCount();
    DWORD dwBytesNeeded;
    DWORD dwTimeout = 30000; // 30-second time-out
    DWORD dwWaitTime;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        LastError = GetLastError();
        return E_FAIL;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,         // SCM database 
        serviceName,            // name of service 
        SERVICE_STOP |
        SERVICE_QUERY_STATUS |
        SERVICE_ENUMERATE_DEPENDENTS);

    if (schService == NULL)
    {
        LastError = GetLastError();
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // Make sure the service is not already stopped.

    if (!QueryServiceStatusEx(
        schService,
        SC_STATUS_PROCESS_INFO,
        (LPBYTE)&ssp,
        sizeof(SERVICE_STATUS_PROCESS),
        &dwBytesNeeded))
    {
        LastError = GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    if (ssp.dwCurrentState == SERVICE_STOPPED || ssp.dwCurrentState == SERVICE_STOP_PENDING)
    {
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return S_FALSE;
    }

    
    return S_OK;
}



STDMETHODIMP CServiceManager::get_ServiceName(BSTR* pVal)
{
    *pVal = serviceName.AllocSysString();

    return S_OK;
}


STDMETHODIMP CServiceManager::put_ServiceName(BSTR newVal)
{
    serviceName = newVal;

    return S_OK;
}


STDMETHODIMP CServiceManager::get_LastError(INT* pVal)
{
    *pVal = LastError;

    return S_OK;
}


STDMETHODIMP CServiceManager::get_CurrentState(INT* pVal)
{
    *pVal = CurrentState;

    return S_OK;
}


STDMETHODIMP CServiceManager::get_ExitCode(INT* pVal)
{
    *pVal = ExitCode;

    return S_OK;
}


STDMETHODIMP CServiceManager::get_CheckPoint(INT* pVal)
{
    *pVal = CheckPoint;

    return S_OK;
}


STDMETHODIMP CServiceManager::get_WaitHint(INT* pVal)
{
    *pVal = WaitHint;

    return S_OK;
}
