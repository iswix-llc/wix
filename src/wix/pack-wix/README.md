# iswix - the IsWiX build of the WiX Toolset from the command-line

The `iswix` package provides the WiX Toolset as a .NET Tool, perfect for your command-line packaging pleasure (even if we recommend using the [IsWiX.Sdk][sdk]).

[Web Site][web] | [Documentation][docs] | [Issue Tracker][issues] | [Discussions][discussions]


## About this build

This package is part of IsWiX, a build of the [WiX Toolset](https://wixtoolset.org/) compiled from source at [iswix-llc/wix](https://github.com/iswix-llc/wix) and distributed under the [Microsoft Reciprocal License (MS-RL)](https://github.com/iswix-llc/wix/blob/main/LICENSE.TXT). It is not an official WiX Toolset release and is not affiliated with or endorsed by the WiX Toolset project. Package IDs use the `IsWiX.` prefix; assembly names and namespaces are unchanged. Please report problems with these packages at [iswix-llc/wix](https://github.com/iswix-llc/wix/issues).

## Before we begin

For most users, we recommend using the [IsWiX.Sdk][sdk] to build your installation packages instead of this command-line tool. The Sdk provides a better development experience than the command-line, especially as your project grows. The following is a quick example.

Example project file: `QuickStart.wixproj`
```
<Project Sdk="IsWiX.Sdk/8.0.0">
</Project>
```

Example source code: `QuickStart.wxs`
```
<Wix xmlns="http://wixtoolset.org/schemas/v4/wxs">
  <Package Id="AcmeCorp.QuickStart" Name="QuickStart Example" Manufacturer="ACME Corp" Version="0.0.1">
    <File Source="example.txt" />
  </Package>
</Wix>
```

Build your MSI from the command-line:
```
dotnet build
```


## Getting started

If you still decide to use this command-line tool instead of the [IsWiX.Sdk][sdk], install the latest version with:

```
dotnet tool install --global iswix
```

Verify it was successfully installed with:

```
iswix --version
```

For more information, see https://docs.firegiant.com/wix/using-wix/#command-line-net-tool. To read about available commands and switches, see https://docs.firegiant.com/wix/tools/wixexe/.


## Additional resources

* [WiX Website][web]
* [WiX Documentation][docs]
* [WiX Issue Tracker][issues]
* [WiX Discussions][discussions]


[web]: https://www.firegiant.com/wixtoolset/
[docs]: https://docs.firegiant.com/wixtoolset/
[issues]: https://github.com/wixtoolset/issues/issues
[discussions]: https://github.com/orgs/wixtoolset/discussions
[sdk]: https://www.nuget.org/packages/IsWiX.Sdk/
[osmf]: https://opensourcemaintenancefee.org/
[license]: https://github.com/wixtoolset/wix/blob/main/LICENSE.TXT
[eula]: https://github.com/wixtoolset/wix/blob/main/OSMFEULA.txt
