

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for ServiceControlCOM.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ServiceControlCOM_i_h__
#define __ServiceControlCOM_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IServiceManager_FWD_DEFINED__
#define __IServiceManager_FWD_DEFINED__
typedef interface IServiceManager IServiceManager;

#endif 	/* __IServiceManager_FWD_DEFINED__ */


#ifndef __ServiceManager_FWD_DEFINED__
#define __ServiceManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class ServiceManager ServiceManager;
#else
typedef struct ServiceManager ServiceManager;
#endif /* __cplusplus */

#endif 	/* __ServiceManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IServiceManager_INTERFACE_DEFINED__
#define __IServiceManager_INTERFACE_DEFINED__

/* interface IServiceManager */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IServiceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4557e734-2814-4b45-bfb7-d074c5219b78")
    IServiceManager : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startSvc( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ServiceName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ServiceName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ INT *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentState( 
            /* [retval][out] */ INT *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ExitCode( 
            /* [retval][out] */ INT *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CheckPoint( 
            /* [retval][out] */ INT *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_WaitHint( 
            /* [retval][out] */ INT *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopSvc( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE chkStatus( 
            /* [out] */ BYTE *status) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AllSvcNames( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE clearMem( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServiceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServiceManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServiceManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServiceManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServiceManager * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startSvc )( 
            IServiceManager * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServiceName )( 
            IServiceManager * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServiceName )( 
            IServiceManager * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastError )( 
            IServiceManager * This,
            /* [retval][out] */ INT *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentState )( 
            IServiceManager * This,
            /* [retval][out] */ INT *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExitCode )( 
            IServiceManager * This,
            /* [retval][out] */ INT *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CheckPoint )( 
            IServiceManager * This,
            /* [retval][out] */ INT *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WaitHint )( 
            IServiceManager * This,
            /* [retval][out] */ INT *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopSvc )( 
            IServiceManager * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *chkStatus )( 
            IServiceManager * This,
            /* [out] */ BYTE *status);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllSvcNames )( 
            IServiceManager * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *clearMem )( 
            IServiceManager * This);
        
        END_INTERFACE
    } IServiceManagerVtbl;

    interface IServiceManager
    {
        CONST_VTBL struct IServiceManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServiceManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServiceManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServiceManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServiceManager_startSvc(This)	\
    ( (This)->lpVtbl -> startSvc(This) ) 

#define IServiceManager_get_ServiceName(This,pVal)	\
    ( (This)->lpVtbl -> get_ServiceName(This,pVal) ) 

#define IServiceManager_put_ServiceName(This,newVal)	\
    ( (This)->lpVtbl -> put_ServiceName(This,newVal) ) 

#define IServiceManager_get_LastError(This,pVal)	\
    ( (This)->lpVtbl -> get_LastError(This,pVal) ) 

#define IServiceManager_get_CurrentState(This,pVal)	\
    ( (This)->lpVtbl -> get_CurrentState(This,pVal) ) 

#define IServiceManager_get_ExitCode(This,pVal)	\
    ( (This)->lpVtbl -> get_ExitCode(This,pVal) ) 

#define IServiceManager_get_CheckPoint(This,pVal)	\
    ( (This)->lpVtbl -> get_CheckPoint(This,pVal) ) 

#define IServiceManager_get_WaitHint(This,pVal)	\
    ( (This)->lpVtbl -> get_WaitHint(This,pVal) ) 

#define IServiceManager_stopSvc(This)	\
    ( (This)->lpVtbl -> stopSvc(This) ) 

#define IServiceManager_chkStatus(This,status)	\
    ( (This)->lpVtbl -> chkStatus(This,status) ) 

#define IServiceManager_get_AllSvcNames(This,pVal)	\
    ( (This)->lpVtbl -> get_AllSvcNames(This,pVal) ) 

#define IServiceManager_clearMem(This)	\
    ( (This)->lpVtbl -> clearMem(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IServiceManager_INTERFACE_DEFINED__ */



#ifndef __ServiceControlCOMLib_LIBRARY_DEFINED__
#define __ServiceControlCOMLib_LIBRARY_DEFINED__

/* library ServiceControlCOMLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ServiceControlCOMLib;

EXTERN_C const CLSID CLSID_ServiceManager;

#ifdef __cplusplus

class DECLSPEC_UUID("b0c6ba7c-e601-4dc9-971e-8d4319fcd912")
ServiceManager;
#endif
#endif /* __ServiceControlCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


