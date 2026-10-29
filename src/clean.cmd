@echo off

setlocal
pushd %~dp0

set _NUGET_CACHE=%USERPROFILE%\.nuget\packages
if "%NUGET_PACKAGES%" NEQ "" set _NUGET_CACHE=%NUGET_PACKAGES%

echo Cleaning...

if exist ..\build rd /s/q ..\build
if exist ..\packages rd /s/q ..\packages

if exist Directory.Packages.props (del Directory.Packages.props)
if exist global.json (del global.json)

if exist ..\Directory.Packages.props (del ..\Directory.Packages.props)
if exist ..\global.json (del ..\global.json)

if exist "%_NUGET_CACHE%\wixinternal.basebuildtasks.sources" rd /s/q "%_NUGET_CACHE%\wixinternal.basebuildtasks.sources"
if exist "%_NUGET_CACHE%\wixinternal.testsupport" rd /s/q "%_NUGET_CACHE%\wixinternal.testsupport"
if exist "%_NUGET_CACHE%\wixinternal.mstestsupport" rd /s/q "%_NUGET_CACHE%\wixinternal.mstestsupport"
if exist "%_NUGET_CACHE%\wixinternal.core.testpackage" rd /s/q "%_NUGET_CACHE%\wixinternal.core.testpackage"
if exist "%_NUGET_CACHE%\wixinternal.core.mstestpackage" rd /s/q "%_NUGET_CACHE%\wixinternal.core.mstestpackage"
if exist "%_NUGET_CACHE%\iswix.bal.wixext" rd /s/q "%_NUGET_CACHE%\iswix.bal.wixext"
if exist "%_NUGET_CACHE%\iswix.bootstrapperapplications.wixext" rd /s/q "%_NUGET_CACHE%\iswix.bootstrapperapplications.wixext"
if exist "%_NUGET_CACHE%\iswix.bootstrapperextensionapi" rd /s/q "%_NUGET_CACHE%\iswix.bootstrapperextensionapi"
if exist "%_NUGET_CACHE%\iswix.bextutil" rd /s/q "%_NUGET_CACHE%\iswix.bextutil"
if exist "%_NUGET_CACHE%\iswix.burn" rd /s/q "%_NUGET_CACHE%\iswix.burn"
if exist "%_NUGET_CACHE%\iswix.complus.wixext" rd /s/q "%_NUGET_CACHE%\iswix.complus.wixext"
if exist "%_NUGET_CACHE%\iswix.converters" rd /s/q "%_NUGET_CACHE%\iswix.converters"
if exist "%_NUGET_CACHE%\iswix.core" rd /s/q "%_NUGET_CACHE%\iswix.core"
if exist "%_NUGET_CACHE%\iswix.core.burn" rd /s/q "%_NUGET_CACHE%\iswix.core.burn"
if exist "%_NUGET_CACHE%\iswix.core.extensioncache" rd /s/q "%_NUGET_CACHE%\iswix.core.extensioncache"
if exist "%_NUGET_CACHE%\iswix.core.native" rd /s/q "%_NUGET_CACHE%\iswix.core.native"
if exist "%_NUGET_CACHE%\iswix.core.windowsinstaller" rd /s/q "%_NUGET_CACHE%\iswix.core.windowsinstaller"
if exist "%_NUGET_CACHE%\iswix.data" rd /s/q "%_NUGET_CACHE%\iswix.data"
if exist "%_NUGET_CACHE%\iswix.dependency.wixext" rd /s/q "%_NUGET_CACHE%\iswix.dependency.wixext"
if exist "%_NUGET_CACHE%\iswix.directx.wixext" rd /s/q "%_NUGET_CACHE%\iswix.directx.wixext"
if exist "%_NUGET_CACHE%\iswix.dtf.compression" rd /s/q "%_NUGET_CACHE%\iswix.dtf.compression"
if exist "%_NUGET_CACHE%\iswix.dtf.compression.cab" rd /s/q "%_NUGET_CACHE%\iswix.dtf.compression.cab"
if exist "%_NUGET_CACHE%\iswix.dtf.compression.zip" rd /s/q "%_NUGET_CACHE%\iswix.dtf.compression.zip"
if exist "%_NUGET_CACHE%\iswix.dtf.customaction" rd /s/q "%_NUGET_CACHE%\iswix.dtf.customaction"
if exist "%_NUGET_CACHE%\iswix.dtf.resources" rd /s/q "%_NUGET_CACHE%\iswix.dtf.resources"
if exist "%_NUGET_CACHE%\iswix.dtf.windowsinstaller" rd /s/q "%_NUGET_CACHE%\iswix.dtf.windowsinstaller"
if exist "%_NUGET_CACHE%\iswix.dtf.windowsinstaller.linq" rd /s/q "%_NUGET_CACHE%\iswix.dtf.windowsinstaller.linq"
if exist "%_NUGET_CACHE%\iswix.dtf.windowsinstaller.package" rd /s/q "%_NUGET_CACHE%\iswix.dtf.windowsinstaller.package"
if exist "%_NUGET_CACHE%\iswix.dutil" rd /s/q "%_NUGET_CACHE%\iswix.dutil"
if exist "%_NUGET_CACHE%\iswix.extensibility" rd /s/q "%_NUGET_CACHE%\iswix.extensibility"
if exist "%_NUGET_CACHE%\iswix.firewall.wixext" rd /s/q "%_NUGET_CACHE%\iswix.firewall.wixext"
if exist "%_NUGET_CACHE%\iswix.http.wixext" rd /s/q "%_NUGET_CACHE%\iswix.http.wixext"
if exist "%_NUGET_CACHE%\iswix.iis.wixext" rd /s/q "%_NUGET_CACHE%\iswix.iis.wixext"
if exist "%_NUGET_CACHE%\iswix.bootstrapperapplicationapi" rd /s/q "%_NUGET_CACHE%\iswix.bootstrapperapplicationapi"
if exist "%_NUGET_CACHE%\iswix.msmq.wixext" rd /s/q "%_NUGET_CACHE%\iswix.msmq.wixext"
if exist "%_NUGET_CACHE%\iswix.netfx.wixext" rd /s/q "%_NUGET_CACHE%\iswix.netfx.wixext"
if exist "%_NUGET_CACHE%\iswix.powershell.wixext" rd /s/q "%_NUGET_CACHE%\iswix.powershell.wixext"
if exist "%_NUGET_CACHE%\iswix.sdk" rd /s/q "%_NUGET_CACHE%\iswix.sdk"
if exist "%_NUGET_CACHE%\iswix.sql.wixext" rd /s/q "%_NUGET_CACHE%\iswix.sql.wixext"
if exist "%_NUGET_CACHE%\iswix.util.wixext" rd /s/q "%_NUGET_CACHE%\iswix.util.wixext"
if exist "%_NUGET_CACHE%\iswix.ui.wixext" rd /s/q "%_NUGET_CACHE%\iswix.ui.wixext"
if exist "%_NUGET_CACHE%\iswix.versioning" rd /s/q "%_NUGET_CACHE%\iswix.versioning"
if exist "%_NUGET_CACHE%\iswix.visualstudio.wixext" rd /s/q "%_NUGET_CACHE%\iswix.visualstudio.wixext"
if exist "%_NUGET_CACHE%\iswix.wcautil" rd /s/q "%_NUGET_CACHE%\iswix.wcautil"
if exist "%_NUGET_CACHE%\iswix" rd /s/q "%_NUGET_CACHE%\iswix"

popd
endlocal
