<Project>
  <PropertyGroup>
    <CentralPackageTransitivePinningEnabled>true</CentralPackageTransitivePinningEnabled>
  </PropertyGroup>

  <ItemGroup>
    <PackageVersion Include="IsWiX.Dtf.Compression" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Dtf.Compression.Cab" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Dtf.CustomAction" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Dtf.Resources" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Dtf.WindowsInstaller" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Dtf.WindowsInstaller.Package" Version="{packageversion}" />

    <PackageVersion Include="WixInternal.TestSupport" Version="{packageversion}" />
    <PackageVersion Include="WixInternal.MSTestSupport" Version="{packageversion}" />
    <PackageVersion Include="WixInternal.TestSupport.Native" Version="{packageversion}" />
    <PackageVersion Include="WixInternal.BaseBuildTasks.Sources" Version="{packageversion}" />

    <PackageVersion Include="IsWiX.DUtil" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.WcaUtil" Version="{packageversion}" />

    <PackageVersion Include="IsWiX.BootstrapperApplicationApi" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.BootstrapperExtensionApi" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.WixStandardBootstrapperApplicationFunctionApi" Version="{packageversion}" />

    <PackageVersion Include="IsWiX.Data" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Extensibility" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Versioning" Version="{packageversion}" />

    <PackageVersion Include="IsWiX.Burn" Version="{packageversion}" />

    <PackageVersion Include="IsWiX.Core" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Core.Burn" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Core.WindowsInstaller" Version="{packageversion}" />
    <PackageVersion Include="WixInternal.Core.TestPackage" Version="{packageversion}" />
    <PackageVersion Include="WixInternal.Core.MSTestPackage" Version="{packageversion}" />

    <PackageVersion Include="IsWiX.Bal.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.BootstrapperApplications.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.ComPlus.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Dependency.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.NetFx.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.UI.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Util.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Firewall.wixext" Version="{packageversion}" />
    <PackageVersion Include="IsWiX.Msmq.wixext" Version="{packageversion}" />
  </ItemGroup>

  <ItemGroup>
    <PackageVersion Include="System.Diagnostics.PerformanceCounter" Version="8.0.1" />
    <PackageVersion Include="System.DirectoryServices" Version="8.0.0" />
    <PackageVersion Include="System.DirectoryServices.AccountManagement" Version="8.0.0" />
    <PackageVersion Include="System.Management" Version="8.0.0" />
    <PackageVersion Include="System.Reflection.Metadata" Version="8.0.1" />
    <PackageVersion Include="System.Text.Encoding.CodePages" Version="9.0.11" />
    <PackageVersion Include="System.Text.Json" Version="9.0.21" />

    <PackageVersion Include="System.IO.Compression" Version="4.3.0" />
    <PackageVersion Include="System.IO.FileSystem.AccessControl" Version="5.0.0" />
    <PackageVersion Include="System.Net.NetworkInformation" Version="4.3.0" />
    <PackageVersion Include="System.Security.Principal.Windows" Version="5.0.0" />

    <PackageVersion Include="Microsoft.AspNetCore.Owin" Version="8.0.21" />
    <PackageVersion Include="Microsoft.VisualStudio.Setup.Configuration.Native" Version="3.14.2075" />
    <PackageVersion Include="Microsoft.Win32.Registry" Version="5.0.0" />
  </ItemGroup>

  <!-- NuGet stack -->
  <ItemGroup>
    <PackageVersion Include="NuGet.Credentials" Version="6.13.2" />
    <PackageVersion Include="NuGet.Protocol" Version="6.13.2" />
    <PackageVersion Include="NuGet.Versioning" Version="6.13.2" />
  </ItemGroup>

  <!-- MSBuild (aligned with VS 17.14 toolset) -->
  <ItemGroup>
    <PackageVersion Include="Microsoft.Build.Utilities.Core" Version="17.14.28" />
  </ItemGroup>

  <!-- Keep the following versions in sync with internal\WixInternal.TestSupport.Native\packages.config -->
  <ItemGroup>
    <PackageVersion Include="Microsoft.SourceLink.GitHub" Version="10.0.401" />

    <PackageVersion Include="Microsoft.NET.Test.Sdk" Version="17.14.1" />
    <PackageVersion Include="xunit" Version="2.9.3" />
    <PackageVersion Include="xunit.runner.visualstudio" Version="2.8.2" />
    <PackageVersion Include="xunit.assert" Version="2.9.3" />
  </ItemGroup>

  <ItemGroup>
    <PackageVersion Include="MSTest.TestFramework" Version="4.0.1" />
  </ItemGroup>

  <ItemGroup>
    <PackageVersion Include="Microsoft.NET.Tools.NETCoreCheck.x86" Version="7.0.0" />
    <PackageVersion Include="Microsoft.NET.Tools.NETCoreCheck.x64" Version="7.0.0" />
    <PackageVersion Include="Microsoft.NET.Tools.NETCoreCheck.arm64" Version="7.0.0" />
  </ItemGroup>
</Project>
