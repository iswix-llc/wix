# WixToolset.BootstrapperApplications.wixext - Bootstrapper Applications WiX Toolset Extension

This WiX Extension provides the standard BootstrapperApplications provided by the WiX Toolset.

- WixStdBA ([WixStandardBootstrapperApplication](https://docs.firegiant.com/wix/schema/bal/wixstandardbootstrapperapplication/)), a bootstrapper application with support for custom themes
- WixIuiBA ([WixInternalUIBootstrapperApplication](https://docs.firegiant.com/wix/schema/bal/wixinternaluibootstrapperapplication/)), a bootstrapper application for showing internal UI of Windows Installer packages
- WixPreqBA ([WixPrerequisiteBootstrapperApplication](https://docs.firegiant.com/wix/schema/bal/wixprerequisitebootstrapperapplication/)), a secondary bootstrapper application for bootstrapping the prerequisites needed for a primary bootstrapper application

[Web Site][web] | [Documentation][docs] | [Issue Tracker][issues] | [Discussions][discussions]

## About this build

This package is part of IsWiX, a build of the [WiX Toolset](https://wixtoolset.org/) compiled from source at [chrpai/wix](https://github.com/chrpai/wix) and distributed under the [Microsoft Reciprocal License (MS-RL)](https://github.com/chrpai/wix/blob/main/LICENSE.TXT). It is not an official WiX Toolset release and is not affiliated with or endorsed by the WiX Toolset project. Package IDs use the `IsWiX.` prefix; assembly names and namespaces are unchanged. Please report problems with these packages at [chrpai/wix](https://github.com/chrpai/wix/issues).

## Getting started

Add the WiX Extension as a PackageReference to your .wixproj:

```
<Project Sdk="IsWiX.Sdk/7.0.1">
  <ItemGroup>
    <PackageReference Include="IsWiX.BootstrapperApplications.wixext" Version="7.0.1" />
  </ItemGroup>
</Project>
```

Then add the namespace and bootstrapper application of choice:

```
<Wix xmlns="http://wixtoolset.org/schemas/v4/wxs"
     xmlns:bal="http://wixtoolset.org/schemas/v4/wxs/bal">
  <Bundle BundleId="AcmeCorp.Example" Name="Example Bundle" Version="0.0.0.1" Manufacturer="ACME Corporation">
    <BootstrapperApplication>
      <bal:WixStandardBootstrapperApplication LicenseUrl="http://wixtoolset.org/about/license/" Theme="hyperlinkLicense" />
    </BootstrapperApplication>
  </Bundle>
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
