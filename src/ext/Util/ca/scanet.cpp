// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

#include "precomp.h"


HRESULT GetDomainServerName(LPCWSTR pwzDomain, LPWSTR* ppwzServerName, ULONG flags)
{
    DWORD er = ERROR_SUCCESS;
    PDOMAIN_CONTROLLER_INFOW pDomainControllerInfo = NULL;
    HRESULT hr = S_OK;
    WCHAR pwzComputerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD cchComputerName = countof(pwzComputerName);

    hr = ::GetComputerNameW(pwzComputerName, &cchComputerName);
    ExitOnFailure(hr, "failed to obtain computer name");

    if (pwzDomain && *pwzDomain && 0!=lstrcmpiW(pwzComputerName, pwzDomain) && 0!=lstrcmpiW(L".", pwzDomain))
    {
        er = ::DsGetDcNameW(NULL, pwzDomain, NULL, NULL, flags, &pDomainControllerInfo);
        if (RPC_S_SERVER_UNAVAILABLE == er)
        {
            // MSDN says, if we get the above error code, try again with the "DS_FORCE_REDISCOVERY" flag
            er = ::DsGetDcNameW(NULL, pwzDomain, NULL, NULL, flags | DS_FORCE_REDISCOVERY, &pDomainControllerInfo);
        }

        if (ERROR_SUCCESS == er && pDomainControllerInfo->DomainControllerName)
        {
            // Skip the \\ prefix if present.
            if ('\\' == *pDomainControllerInfo->DomainControllerName && '\\' == *(pDomainControllerInfo->DomainControllerName + 1) )
            {
                hr = StrAllocString(ppwzServerName, pDomainControllerInfo->DomainControllerName + 2, 0);
            }
            else
            {
                hr = StrAllocString(ppwzServerName, pDomainControllerInfo->DomainControllerName, 0);
            }
            ExitOnFailure(hr, "failed to allocate memory for string");
        }
        else
        {
            // we won't report any potential string allocation failure, the domain failure is more interesting
            StrAllocString(ppwzServerName, pwzDomain, 0);
            hr = HRESULT_FROM_WIN32(er);
            ExitOnFailure(hr, "failed to contact domain %ls", pwzDomain);
        }
    }

LExit:
    if (pDomainControllerInfo)
    {
        ::NetApiBufferFree((LPVOID)pDomainControllerInfo);
    }
    return hr;
}
