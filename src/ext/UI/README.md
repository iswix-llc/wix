# WixToolset.UI.wixext - UI WiX Toolset Extension

This WiX Extension provides support for standard internal MSI UI.

[Web Site][web] | [Documentation][docs] | [Issue Tracker][issues] | [Discussions][discussions]


## About this build

This package is part of IsWiX, a build of the [WiX Toolset](https://wixtoolset.org/) compiled from source at [iswix-llc/wix](https://github.com/iswix-llc/wix) and distributed under the [Microsoft Reciprocal License (MS-RL)](https://github.com/iswix-llc/wix/blob/main/LICENSE.TXT). It is not an official WiX Toolset release and is not affiliated with or endorsed by the WiX Toolset project. Package IDs use the `IsWiX.` prefix; assembly names and namespaces are unchanged. Please report problems with these packages at [iswix-llc/wix](https://github.com/iswix-llc/wix/issues).

## Getting started

Add the WiX Extension as a PackageReference to your .wixproj:

```
<Project Sdk="IsWiX.Sdk/8.0.0">
  <ItemGroup>
    <PackageReference Include="IsWiX.UI.wixext" Version="8.0.0" />
  </ItemGroup>
</Project>
```

Then add the extension's namespace:

```
<Wix xmlns="http://wixtoolset.org/schemas/v4/wxs"
     xmlns:ui="http://wixtoolset.org/schemas/v4/wxs/ui">

  ..
</Wix>
```

## Additional resources

* [WiX Website][web]
* [WiX Documentation][docs]
* [WiX Issue Tracker][issues]
* [WiX Discussions][discussions]


[web]: https://www.firegiant.com/wixtoolset/
[docs]: https://docs.firegiant.com/wixtoolset/
[issues]: https://github.com/wixtoolset/issues/issues
[discussions]: https://github.com/orgs/wixtoolset/discussions
[sdk]: https://www.nuget.org/packages/WixToolset.Sdk/
[osmf]: https://opensourcemaintenancefee.org/
[license]: https://github.com/wixtoolset/wix/blob/main/LICENSE.TXT
[eula]: https://github.com/wixtoolset/wix/blob/main/OSMFEULA.txt
