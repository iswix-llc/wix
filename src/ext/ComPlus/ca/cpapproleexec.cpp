// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

#include "precomp.h"


// private structs

struct CPI_APPLICATION_ROLE_ATTRIBUTES
{
    int iActionType;
    int iActionCost;
    LPWSTR pwzKey;
    LPWSTR pwzName;
    LPWSTR pwzAppID;
    LPWSTR pwzPartID;
    CPI_PROPERTY* pPropList;
};

struct CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES
{
    int iActionType;
    int iActionCost;
    LPWSTR pwzKey;
    LPWSTR pwzRoleName;
    LPWSTR pwzAccount;
    LPWSTR pwzAppID;
    LPWSTR pwzPartID;
};


// prototypes for private helper functions

static HRESULT ReadApplicationRoleAttributes(
    LPWSTR* ppwzData,
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static void FreeApplicationRoleAttributes(
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static HRESULT CreateApplicationRole(
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static HRESULT RemoveApplicationRole(
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static HRESULT ReadUsersInApplicationRoleAttributes(
    LPWSTR* ppwzData,
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static void FreeUsersInApplicationRoleAttributes(
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static HRESULT CreateUsersInApplicationRole(
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );
static HRESULT RemoveUsersInApplicationRole(
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    );


// function definitions

HRESULT CpiConfigureApplicationRoles(
    LPWSTR* ppwzData,
    HANDLE hRollbackFile
    )
{
    HRESULT hr = S_OK;

    CPI_APPLICATION_ROLE_ATTRIBUTES attrs;
    ::ZeroMemory(&attrs, sizeof(attrs));

    // read action text
    hr = CpiActionStartMessage(ppwzData, FALSE);
    ExitOnFailure(hr, "Failed to send action start message");

    // get count
    int iCnt = 0;
    hr = WcaReadIntegerFromCaData(ppwzData, &iCnt);
    ExitOnFailure(hr, "Failed to read count");

    // write count to rollback file
    hr = CpiWriteIntegerToRollbackFile(hRollbackFile, iCnt);
    ExitOnFailure(hr, "Failed to write count to rollback file");

    for (int i = 0; i < iCnt; i++)
    {
        // read attributes from CustomActionData
        hr = ReadApplicationRoleAttributes(ppwzData, &attrs);
        ExitOnFailure(hr, "Failed to read attributes");

        // progress message
        hr = CpiActionDataMessage(1, attrs.pwzName);
        ExitOnFailure(hr, "Failed to send progress messages");

        if (S_FALSE == hr)
            ExitFunction();

        // write key to rollback file
        hr = CpiWriteKeyToRollbackFile(hRollbackFile, attrs.pwzKey);
        ExitOnFailure(hr, "Failed to write key to rollback file");

        // action
        switch (attrs.iActionType)
        {
        case atCreate:
            hr = CreateApplicationRole(&attrs);
            ExitOnFailure(hr, "Failed to create application role, key: %S", attrs.pwzKey);
            break;
        case atRemove:
            hr = RemoveApplicationRole(&attrs);
            ExitOnFailure(hr, "Failed to remove application role, key: %S", attrs.pwzKey);
            break;
        }

        // write completion status to rollback file
        hr = CpiWriteIntegerToRollbackFile(hRollbackFile, 1);
        ExitOnFailure(hr, "Failed to write completion status to rollback file");

        // progress
        hr = WcaProgressMessage(attrs.iActionCost, FALSE);
        ExitOnFailure(hr, "Failed to update progress");
    }

    hr = S_OK;

LExit:
    // clean up
    FreeApplicationRoleAttributes(&attrs);

    return hr;
}

HRESULT CpiRollbackConfigureApplicationRoles(
    LPWSTR* ppwzData,
    CPI_ROLLBACK_DATA* pRollbackDataList
    )
{
    HRESULT hr = S_OK;

    int iRollbackStatus;

    CPI_APPLICATION_ROLE_ATTRIBUTES attrs;
    ::ZeroMemory(&attrs, sizeof(attrs));

    // read action text
    hr = CpiActionStartMessage(ppwzData, NULL == pRollbackDataList);
    ExitOnFailure(hr, "Failed to send action start message");

    // get count
    int iCnt = 0;
    hr = WcaReadIntegerFromCaData(ppwzData, &iCnt);
    ExitOnFailure(hr, "Failed to read count");

    for (int i = 0; i < iCnt; i++)
    {
        // read attributes from CustomActionData
        hr = ReadApplicationRoleAttributes(ppwzData, &attrs);
        ExitOnFailure(hr, "Failed to read attributes");

        // rollback status
        hr = CpiFindRollbackStatus(pRollbackDataList, attrs.pwzKey, &iRollbackStatus);

        if (S_FALSE == hr)
            continue; // not found, nothing to rollback

        // progress message
        hr = CpiActionDataMessage(1, attrs.pwzName);
        ExitOnFailure(hr, "Failed to send progress messages");

        if (S_FALSE == hr)
            ExitFunction();

        // action
        switch (attrs.iActionType)
        {
        case atCreate:
            hr = CreateApplicationRole(&attrs);
            if (FAILED(hr))
                WcaLog(LOGMSG_STANDARD, "Failed to create application role, hr: 0x%x, key: %S", hr, attrs.pwzKey);
            break;
        case atRemove:
            hr = RemoveApplicationRole(&attrs);
            if (FAILED(hr))
                WcaLog(LOGMSG_STANDARD, "Failed to remove application role, hr: 0x%x, key: %S", hr, attrs.pwzKey);
            break;
        }

        // check rollback status
        if (0 == iRollbackStatus)
            continue; // operation did not complete, skip progress

        // progress
        hr = WcaProgressMessage(attrs.iActionCost, FALSE);
        ExitOnFailure(hr, "Failed to update progress");
    }

    hr = S_OK;

LExit:
    // clean up
    FreeApplicationRoleAttributes(&attrs);

    return hr;
}

HRESULT CpiConfigureUsersInApplicationRoles(
    LPWSTR* ppwzData,
    HANDLE hRollbackFile
    )
{
    HRESULT hr = S_OK;

    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES attrs;
    ::ZeroMemory(&attrs, sizeof(attrs));

    // read action text
    hr = CpiActionStartMessage(ppwzData, FALSE);
    ExitOnFailure(hr, "Failed to send action start message");

    // get count
    int iCnt = 0;
    hr = WcaReadIntegerFromCaData(ppwzData, &iCnt);
    ExitOnFailure(hr, "Failed to read count");

    // write count to rollback file
    hr = CpiWriteIntegerToRollbackFile(hRollbackFile, iCnt);
    ExitOnFailure(hr, "Failed to write count to rollback file");

    for (int i = 0; i < iCnt; i++)
    {
        // read attributes from CustomActionData
        hr = ReadUsersInApplicationRoleAttributes(ppwzData, &attrs);
        ExitOnFailure(hr, "Failed to read attributes");

        // progress message
        hr = CpiActionDataMessage(1, attrs.pwzRoleName);
        ExitOnFailure(hr, "Failed to send progress messages");

        if (S_FALSE == hr)
            ExitFunction();

        // write key to rollback file
        hr = CpiWriteKeyToRollbackFile(hRollbackFile, attrs.pwzKey);
        ExitOnFailure(hr, "Failed to write key to rollback file");

        // action
        switch (attrs.iActionType)
        {
        case atCreate:
            hr = CreateUsersInApplicationRole(&attrs);
            ExitOnFailure(hr, "Failed to create user in application role, key: %S", attrs.pwzKey);
            break;
        case atRemove:
            hr = RemoveUsersInApplicationRole(&attrs);
            ExitOnFailure(hr, "Failed to remove user from application role, key: %S", attrs.pwzKey);
            break;
        }

        // write completion status to rollback file
        hr = CpiWriteIntegerToRollbackFile(hRollbackFile, 1);
        ExitOnFailure(hr, "Failed to write completion status to rollback file");

        // progress
        hr = WcaProgressMessage(attrs.iActionCost, FALSE);
        ExitOnFailure(hr, "Failed to update progress");
    }

    hr = S_OK;

LExit:
    // clean up
    FreeUsersInApplicationRoleAttributes(&attrs);

    return hr;
}

HRESULT CpiRollbackConfigureUsersInApplicationRoles(
    LPWSTR* ppwzData,
    CPI_ROLLBACK_DATA* pRollbackDataList
    )
{
    HRESULT hr = S_OK;

    int iRollbackStatus;

    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES attrs;
    ::ZeroMemory(&attrs, sizeof(attrs));

    // read action text
    hr = CpiActionStartMessage(ppwzData, NULL == pRollbackDataList);
    ExitOnFailure(hr, "Failed to send action start message");

    // get count
    int iCnt = 0;
    hr = WcaReadIntegerFromCaData(ppwzData, &iCnt);
    ExitOnFailure(hr, "Failed to read count");

    for (int i = 0; i < iCnt; i++)
    {
        // read attributes from CustomActionData
        hr = ReadUsersInApplicationRoleAttributes(ppwzData, &attrs);
        ExitOnFailure(hr, "Failed to read attributes");

        // rollback status
        hr = CpiFindRollbackStatus(pRollbackDataList, attrs.pwzKey, &iRollbackStatus);

        if (S_FALSE == hr)
            continue; // not found, nothing to rollback

        // progress message
        hr = CpiActionDataMessage(1, attrs.pwzRoleName);
        ExitOnFailure(hr, "Failed to send progress messages");

        if (S_FALSE == hr)
            ExitFunction();

        // action
        switch (attrs.iActionType)
        {
        case atCreate:
            hr = CreateUsersInApplicationRole(&attrs);
            if (FAILED(hr))
                WcaLog(LOGMSG_STANDARD, "Failed to add user to application role, hr: 0x%x, key: %S", hr, attrs.pwzKey);
            break;
        case atRemove:
            hr = RemoveUsersInApplicationRole(&attrs);
            if (FAILED(hr))
                WcaLog(LOGMSG_STANDARD, "Failed to remove user from application role, hr: 0x%x, key: %S", hr, attrs.pwzKey);
            break;
        }

        // check rollback status
        if (0 == iRollbackStatus)
            continue; // operation did not complete, skip progress

        // progress
        hr = WcaProgressMessage(attrs.iActionCost, FALSE);
        ExitOnFailure(hr, "Failed to update progress");
    }

    hr = S_OK;

LExit:
    // clean up
    FreeUsersInApplicationRoleAttributes(&attrs);

    return hr;
}


// helper function definitions

static HRESULT ReadApplicationRoleAttributes(
    LPWSTR* ppwzData,
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    HRESULT hr = S_OK;

    hr = WcaReadIntegerFromCaData(ppwzData, &pAttrs->iActionType);
    ExitOnFailure(hr, "Failed to read action type");
    hr = WcaReadIntegerFromCaData(ppwzData, &pAttrs->iActionCost);
    ExitOnFailure(hr, "Failed to read action cost");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzKey);
    ExitOnFailure(hr, "Failed to read key");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzName);
    ExitOnFailure(hr, "Failed to read name");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzAppID);
    ExitOnFailure(hr, "Failed to read application id");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzPartID);
    ExitOnFailure(hr, "Failed to read partition id");
    hr = CpiReadPropertyList(ppwzData, &pAttrs->pPropList);
    ExitOnFailure(hr, "Failed to read properties");

    hr = S_OK;

LExit:
    return hr;
}

static void FreeApplicationRoleAttributes(
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    ReleaseStr(pAttrs->pwzKey);
    ReleaseStr(pAttrs->pwzName);
    ReleaseStr(pAttrs->pwzAppID);
    ReleaseStr(pAttrs->pwzPartID);

    if (pAttrs->pPropList)
        CpiFreePropertyList(pAttrs->pPropList);
}

static HRESULT CreateApplicationRole(
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    HRESULT hr = S_OK;

    ICatalogCollection* piRolesColl = NULL;
    ICatalogObject* piRoleObj = NULL;

    long lChanges = 0;

    // log
    WcaLog(LOGMSG_VERBOSE, "Creating application role, key: %S", pAttrs->pwzKey);

    // get roles collection
    hr = CpiGetRolesCollection(pAttrs->pwzPartID, pAttrs->pwzAppID, &piRolesColl);
    if (S_FALSE == hr)
        hr = HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    ExitOnFailure(hr, "Failed to get roles collection");

    // check if role exists
    hr = CpiFindCollectionObjectByName(piRolesColl, pAttrs->pwzName, &piRoleObj);
    ExitOnFailure(hr, "Failed to find role");

    if (S_FALSE == hr)
    {
        // create role
        hr = CpiAddCollectionObject(piRolesColl, &piRoleObj);
        ExitOnFailure(hr, "Failed to add role to collection");

        hr = CpiPutCollectionObjectValue(piRoleObj, L"Name", pAttrs->pwzName);
        ExitOnFailure(hr, "Failed to set role name property");
    }

    // properties
    hr = CpiPutCollectionObjectValues(piRoleObj, pAttrs->pPropList);
    ExitOnFailure(hr, "Failed to write properties");

    // save changes
    hr = piRolesColl->SaveChanges(&lChanges);
    if (COMADMIN_E_OBJECTERRORS == hr)
        CpiLogCatalogErrorInfo();
    ExitOnFailure(hr, "Failed to save changes");

    // log
    WcaLog(LOGMSG_VERBOSE, "%d changes saved to catalog, key: %S", lChanges, pAttrs->pwzKey);

    hr = S_OK;

LExit:
    // clean up
    ReleaseObject(piRolesColl);
    ReleaseObject(piRoleObj);

    return hr;
}

static HRESULT RemoveApplicationRole(
    CPI_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    HRESULT hr = S_OK;

    ICatalogCollection* piRolesColl = NULL;

    long lChanges = 0;

    // log
    WcaLog(LOGMSG_VERBOSE, "Removing application role, key: %S", pAttrs->pwzKey);

    // get roles collection
    hr = CpiGetRolesCollection(pAttrs->pwzPartID, pAttrs->pwzAppID, &piRolesColl);
    ExitOnFailure(hr, "Failed to get roles collection");

    if (S_FALSE == hr)
    {
        // roles collection not found
        WcaLog(LOGMSG_VERBOSE, "Unable to retrieve roles collection, nothing to delete, key: %S", pAttrs->pwzKey);
        ExitFunction1(hr = S_OK);
    }

    // remove
    hr = CpiRemoveCollectionObject(piRolesColl, NULL, pAttrs->pwzName, FALSE);
    ExitOnFailure(hr, "Failed to remove role");

    if (S_FALSE == hr)
    {
        // role not found
        WcaLog(LOGMSG_VERBOSE, "Role not found, nothing to delete, key: %S", pAttrs->pwzKey);
        ExitFunction1(hr = S_OK);
    }

    // save changes
    hr = piRolesColl->SaveChanges(&lChanges);
    if (COMADMIN_E_OBJECTERRORS == hr)
        CpiLogCatalogErrorInfo();
    ExitOnFailure(hr, "Failed to save changes");

    // log
    WcaLog(LOGMSG_VERBOSE, "%d changes saved to catalog, key: %S", lChanges, pAttrs->pwzKey);

    hr = S_OK;

LExit:
    // clean up
    ReleaseObject(piRolesColl);

    return hr;
}

static HRESULT ReadUsersInApplicationRoleAttributes(
    LPWSTR* ppwzData,
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    HRESULT hr = S_OK;

    hr = WcaReadIntegerFromCaData(ppwzData, &pAttrs->iActionType);
    ExitOnFailure(hr, "Failed to read action type");
    hr = WcaReadIntegerFromCaData(ppwzData, &pAttrs->iActionCost);
    ExitOnFailure(hr, "Failed to read action cost");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzKey);
    ExitOnFailure(hr, "Failed to read key");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzRoleName);
    ExitOnFailure(hr, "Failed to read role name");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzAccount);
    ExitOnFailure(hr, "Failed to read account name");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzAppID);
    ExitOnFailure(hr, "Failed to read application id");
    hr = WcaReadStringFromCaData(ppwzData, &pAttrs->pwzPartID);
    ExitOnFailure(hr, "Failed to read partition id");

    hr = S_OK;

LExit:
    return hr;
}

static void FreeUsersInApplicationRoleAttributes(
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    ReleaseStr(pAttrs->pwzKey);
    ReleaseStr(pAttrs->pwzRoleName);
    ReleaseStr(pAttrs->pwzAccount);
    ReleaseStr(pAttrs->pwzAppID);
    ReleaseStr(pAttrs->pwzPartID);
}

static HRESULT CreateUsersInApplicationRole(
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    HRESULT hr = S_OK;
    UINT er = ERROR_SUCCESS;

    ICatalogCollection* piUsrInRoleColl = NULL;
    ICatalogObject* piUsrInRoleObj = NULL;

    PSID pSid = NULL;
    long lChanges = 0;

    // log
    WcaLog(LOGMSG_VERBOSE, "Adding user to application role, key: %S", pAttrs->pwzKey);

    // get users in role collection
    hr = CpiGetUsersInRoleCollection(pAttrs->pwzPartID, pAttrs->pwzAppID, pAttrs->pwzRoleName, &piUsrInRoleColl);
    if (S_FALSE == hr)
        hr = HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    ExitOnFailure(hr, "Failed to get users in role collection");

    // get SID for account
    do {
        er = ERROR_SUCCESS;
        hr = CpiAccountNameToSid(pAttrs->pwzAccount, &pSid);
        if (HRESULT_FROM_WIN32(ERROR_NONE_MAPPED) == hr && !::MsiGetMode(WcaGetInstallHandle(), MSIRUNMODE_ROLLBACK))
        {
            WcaLog(LOGMSG_STANDARD, "Failed to lookup account name, hr: 0x%x, account: '%S'", hr, pAttrs->pwzAccount);
            er = WcaErrorMessage(msierrComPlusFailedLookupNames, hr, INSTALLMESSAGE_ERROR | MB_ABORTRETRYIGNORE, 0);
            switch (er)
            {
            case IDABORT:
                ExitFunction(); // exit with error code from CpiAccountNameToSid()
            case IDRETRY:
                break;
            case IDIGNORE:
            default:
                ExitFunction1(hr = S_OK);
            }
        }
        else
            ExitOnFailure(hr, "Failed to get SID for account");
    } while (IDRETRY == er);

    // find any existing entry
    hr = CpiFindUserCollectionObject(piUsrInRoleColl, pSid, NULL);
    if (HRESULT_FROM_WIN32(ERROR_NONE_MAPPED) == hr || HRESULT_FROM_WIN32(ERROR_SOME_NOT_MAPPED) == hr)
        WcaLog(LOGMSG_STANDARD, "Failed to lookup account names, hr: 0x%x", hr);
    else
        ExitOnFailure(hr, "Failed to find user in application role");

    if (S_OK == hr)
    {
        WcaLog(LOGMSG_VERBOSE, "User already assigned to application role, key: %S", pAttrs->pwzKey);
        ExitFunction(); // exit with hr = S_OK
    }

    // convert SID back to account name
    hr = CpiSidToAccountName(pSid, &pAttrs->pwzAccount);
    ExitOnFailure(hr, "Failed to convert SID to account name");

    // add user
    hr = CpiAddCollectionObject(piUsrInRoleColl, &piUsrInRoleObj);
    ExitOnFailure(hr, "Failed to add user in role to collection");

    hr = CpiPutCollectionObjectValue(piUsrInRoleObj, L"User", pAttrs->pwzAccount);
    ExitOnFailure(hr, "Failed to set role name property");

    // save changes
    hr = piUsrInRoleColl->SaveChanges(&lChanges);
    if (COMADMIN_E_OBJECTERRORS == hr)
        CpiLogCatalogErrorInfo();
    ExitOnFailure(hr, "Failed to save changes");

    // log
    WcaLog(LOGMSG_VERBOSE, "%d changes saved to catalog, key: %S", lChanges, pAttrs->pwzKey);

    hr = S_OK;

LExit:
    // clean up
    ReleaseObject(piUsrInRoleColl);
    ReleaseObject(piUsrInRoleObj);

    if (pSid)
        ::HeapFree(::GetProcessHeap(), 0, pSid);

    return hr;
}

static HRESULT RemoveUsersInApplicationRole(
    CPI_USER_IN_APPLICATION_ROLE_ATTRIBUTES* pAttrs
    )
{
    HRESULT hr = S_OK;
    UINT er = ERROR_SUCCESS;

    ICatalogCollection* piUsrInRoleColl = NULL;

    PSID pSid = NULL;
    long lChanges = 0;

    // log
    WcaLog(LOGMSG_VERBOSE, "Removing user from application role, key: %S", pAttrs->pwzKey);

    // get users in role collection
    hr = CpiGetUsersInRoleCollection(pAttrs->pwzPartID, pAttrs->pwzAppID, pAttrs->pwzRoleName, &piUsrInRoleColl);
    ExitOnFailure(hr, "Failed to get users in role collection");

    if (S_FALSE == hr)
    {
        // users in role collection not found
        WcaLog(LOGMSG_VERBOSE, "Unable to retrieve users in role collection, nothing to delete, key: %S", pAttrs->pwzKey);
        ExitFunction1(hr = S_OK);
    }

    // get SID for account
    do {
        er = ERROR_SUCCESS;
        hr = CpiAccountNameToSid(pAttrs->pwzAccount, &pSid);
        if (HRESULT_FROM_WIN32(ERROR_NONE_MAPPED) == hr && !::MsiGetMode(WcaGetInstallHandle(), MSIRUNMODE_ROLLBACK))
        {
            WcaLog(LOGMSG_STANDARD, "Failed to lookup account name, hr: 0x%x, account: '%S'", hr, pAttrs->pwzAccount);
            er = WcaErrorMessage(msierrComPlusFailedLookupNames, hr, INSTALLMESSAGE_ERROR | MB_ABORTRETRYIGNORE, 0);
            switch (er)
            {
            case IDABORT:
                ExitFunction(); // exit with error code from CpiAccountNameToSid()
            case IDRETRY:
                break;
            case IDIGNORE:
            default:
                ExitFunction1(hr = S_OK);
            }
        }
        else
            ExitOnFailure(hr, "Failed to get SID for account");
    } while (IDRETRY == er);

    // remove
    hr = CpiRemoveUserCollectionObject(piUsrInRoleColl, pSid);
    if (HRESULT_FROM_WIN32(ERROR_NONE_MAPPED) == hr || HRESULT_FROM_WIN32(ERROR_SOME_NOT_MAPPED) == hr)
    {
        WcaLog(LOGMSG_STANDARD, "Failed to lookup account names, hr: 0x%x", hr);
        hr = S_FALSE;
    }
    else
        ExitOnFailure(hr, "Failed to remove user");

    if (S_FALSE == hr)
    {
        // role not found
        WcaLog(LOGMSG_VERBOSE, "User not found for application role, nothing to delete, key: %S", pAttrs->pwzKey);
        ExitFunction1(hr = S_OK);
    }

    // save changes
    hr = piUsrInRoleColl->SaveChanges(&lChanges);
    if (COMADMIN_E_OBJECTERRORS == hr)
        CpiLogCatalogErrorInfo();
    ExitOnFailure(hr, "Failed to save changes");

    // log
    WcaLog(LOGMSG_VERBOSE, "%d changes saved to catalog, key: %S", lChanges, pAttrs->pwzKey);

    hr = S_OK;

LExit:
    // clean up
    ReleaseObject(piUsrInRoleColl);

    if (pSid)
        ::HeapFree(::GetProcessHeap(), 0, pSid);

    return hr;
}
