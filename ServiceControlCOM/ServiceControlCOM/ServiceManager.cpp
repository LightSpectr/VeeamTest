// ServiceManager.cpp: реализация CServiceManager

#include "pch.h"
#include "ServiceManager.h"


// CServiceManager


// Метод для запуска службы имя которой сохранено в serviceName
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

    // проверка статуса службы 

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

    // проверка что служба уже не запущена 

    if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
    {
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return S_FALSE;
    }

    // старт службы
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

    // ожидание старта и проверка что служба начала работу 

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

// Метод остановки службы имя которой сохранено в serviceName
STDMETHODIMP CServiceManager::stopSvc()
{
    LastError = 0;
    SERVICE_STATUS_PROCESS ssp;
    DWORD dwStartTime = GetTickCount();
    DWORD dwBytesNeeded;
    DWORD dwTimeout = 30000; // 30-second time-out
    DWORD dwWaitTime;

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        LastError = GetLastError();
        return E_FAIL;
    }


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

    // проверка что служба уже не остановлена 

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

    // остановка зависимых служб
    StopDependentServices();

    // остановка службы 

    if (!ControlService(
        schService,
        SERVICE_CONTROL_STOP,
        (LPSERVICE_STATUS)&ssp))
    {
        LastError = GetLastError();
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // ожидание остановки и проверка что служба закончила работу

    while (ssp.dwCurrentState != SERVICE_STOPPED)
    {
        Sleep(ssp.dwWaitHint);
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

        if (ssp.dwCurrentState == SERVICE_STOPPED)
            break;

        if (GetTickCount() - dwStartTime > dwTimeout)
        {
            CloseServiceHandle(schService);
            CloseServiceHandle(schSCManager);
            return E_FAIL;
        }
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

    return S_OK;
}



STDMETHODIMP CServiceManager::get_ServiceName(BSTR* pVal)
{
    bstrMem = serviceName.AllocSysString();
    *pVal = bstrMem;
    
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


BOOL CServiceManager::StopDependentServices() {
    DWORD i;
    DWORD dwBytesNeeded;
    DWORD dwCount;

    LPENUM_SERVICE_STATUS   lpDependencies = NULL;
    ENUM_SERVICE_STATUS     ess;
    SC_HANDLE               hDepService;
    SERVICE_STATUS_PROCESS  ssp;

    DWORD dwStartTime = GetTickCount();
    DWORD dwTimeout = 30000; // 30-second time-out

    // Pass a zero-length buffer to get the required buffer size.
    if (EnumDependentServices(schService, SERVICE_ACTIVE,
        lpDependencies, 0, &dwBytesNeeded, &dwCount))
    {
        // If the Enum call succeeds, then there are no dependent
        // services, so do nothing.
        return TRUE;
    }
    else
    {
        if (GetLastError() != ERROR_MORE_DATA)
            return FALSE; // Unexpected error

        // Allocate a buffer for the dependencies.
        lpDependencies = (LPENUM_SERVICE_STATUS)HeapAlloc(
            GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded);

        if (!lpDependencies)
            return FALSE;

        __try {
            // Enumerate the dependencies.
            if (!EnumDependentServices(schService, SERVICE_ACTIVE,
                lpDependencies, dwBytesNeeded, &dwBytesNeeded,
                &dwCount))
                return FALSE;

            for (i = 0; i < dwCount; i++)
            {
                ess = *(lpDependencies + i);
                // Open the service.
                hDepService = OpenService(schSCManager,
                    ess.lpServiceName,
                    SERVICE_STOP | SERVICE_QUERY_STATUS);

                if (!hDepService)
                    return FALSE;

                __try {
                    // Send a stop code.
                    if (!ControlService(hDepService,
                        SERVICE_CONTROL_STOP,
                        (LPSERVICE_STATUS)&ssp))
                        return FALSE;

                    // Wait for the service to stop.
                    while (ssp.dwCurrentState != SERVICE_STOPPED)
                    {
                        Sleep(ssp.dwWaitHint);
                        if (!QueryServiceStatusEx(
                            hDepService,
                            SC_STATUS_PROCESS_INFO,
                            (LPBYTE)&ssp,
                            sizeof(SERVICE_STATUS_PROCESS),
                            &dwBytesNeeded))
                            return FALSE;

                        if (ssp.dwCurrentState == SERVICE_STOPPED)
                            break;

                        if (GetTickCount() - dwStartTime > dwTimeout)
                            return FALSE;
                    }
                }
                __finally
                {
                    // Always release the service handle.
                    CloseServiceHandle(hDepService);
                }
            }
        }
        __finally
        {
            // Always free the enumeration buffer.
            HeapFree(GetProcessHeap(), 0, lpDependencies);
        }
    }
    return TRUE;

}

// проверка статуа службы 
STDMETHODIMP CServiceManager::chkStatus(BYTE* status)
{
    *status = -1;
    LastError = 0;
    SERVICE_STATUS_PROCESS ssStatus;
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
        SERVICE_QUERY_STATUS);  // full access 

    if (schService == NULL)
    {
        LastError = GetLastError();
        CloseServiceHandle(schSCManager);
        return E_FAIL;
    }

    // запись статуса

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

    // запись в переменую статус службы
    switch (ssStatus.dwCurrentState) {
        case SERVICE_STOPPED:

            *status = 0;
            break;
        case SERVICE_STOP_PENDING:

            *status = 1;
            break;
        case SERVICE_RUNNING:

            *status = 2;
            break;
        case SERVICE_START_PENDING:

            *status = 3;
            break;

        default:
            *status = -1;
            break;
    }

    CurrentState = ssStatus.dwCurrentState;
    ExitCode = ssStatus.dwWin32ExitCode;
    CheckPoint = ssStatus.dwCheckPoint;
    WaitHint = ssStatus.dwWaitHint;
    
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
    return S_OK;
}

// запись всех имен служеб через символ конца строки 
STDMETHODIMP CServiceManager::get_AllSvcNames(BSTR* pVal)
{
    std::string str;
    CString n;
    DWORD bytesNeeded = 0;
    DWORD numServices = 0;
    DWORD resumeHandle = 0;
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);

    if (!hSCManager)
    {
        LastError = GetLastError();
        return E_FAIL;
    }

    EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &bytesNeeded, &numServices, &resumeHandle);
    std::vector<BYTE> enumBuffer(bytesNeeded);
    LPENUM_SERVICE_STATUS pEnum = reinterpret_cast<LPENUM_SERVICE_STATUS>(enumBuffer.data());

    if (!EnumServicesStatus(hSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, pEnum, bytesNeeded, &bytesNeeded, &numServices, &resumeHandle)) {
        LastError = GetLastError();
        return E_FAIL;
    }
    
    for (DWORD idx = 0; idx < numServices; ++idx)
    {
        str += utf8_encode(pEnum[idx].lpServiceName) + '\n';
    }

    n = str.c_str();
    CloseServiceHandle(hSCManager);
    bstrMem = n.AllocSysString();
    *pVal = bstrMem;

    return S_OK;
}

std::string CServiceManager::utf8_encode(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}



STDMETHODIMP CServiceManager::clearMem()
{
    SysFreeString(bstrMem);

    return S_OK;
}
