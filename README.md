## Developing WiX

### Prerequisites

Before building the WiX Toolset, ensure you have Visual Studio 2026 (18.6 or higher) with the following installed:

| Workloads |
| :-------- |
| ASP.NET and web development |
| .NET desktop development |
| Desktop development with C++ |

| Individual components |
| :-------------------- |
| .NET 10.0 Runtime (Long Term Support) |
| .NET Framework 4.8 SDK |
| .NET Framework 4.7.2 targeting pack |
| .NET Framework 4.6.2 targeting pack |
| MSVC Build Tools for ARM64/ARM64EC (Latest) |
| C++ Spectre-mitigated libraries for ARM64/ARM64EC (Latest MSVC) |
| C++ ATL for x64/x86 (Latest MSVC) |
| C++ ATL for ARM64/ARM64EC (Latest MSVC) |
| Git for Windows |

Also, download the latest [nuget.exe command-line tool](https://www.nuget.org/downloads) and place it in a directory on your path.

#### Getting started:

* [Fork the WiX repository](https://github.com/wixtoolset/wix/fork)
 into your own GitHub repository
* Clone the WiX repository from your fork (`git clone https://github.com/yourdomain/wix.git`)
 into the directory of your choice

#### To build the WiX toolset:

 * Start a VS2026 'Developer Command Prompt'
 * Change directory to the root of the cloned repository
 * Issue the command `devbuild` (or `devbuild release` if you want to create a release version)

#### Executing your newly built WiX toolset

 * `build\wix\Debug\publish\wix\wix --help` (Change `Debug` to `Release` if you built in release mode)

#### Pull request expectations

 * Pick an [outstanding WiX issue](https://github.com/wixtoolset/issues/issues?q=is%3Aissue+is%3Aopen+label%3A%22up+for+grabs%22) (or [create a new one](https://github.com/wixtoolset/issues/issues/new/choose)). Add a comment requesting that you be assigned to the issue. Wait for confirmation.
 * To create a pull request, [fork a new branch](https://github.com/wixtoolset/wix/fork) from the `main` branch
 * Make changes to effect whatever changed behavior is required for the pull request
 * Push the changes to your repository origin as needed
 * If the `main` branch has changed since you created your branch, rebase to the latest updates.
 * If needed (ie, you squashed or rebased), do a force push of your branch
 * Create a pull request with your branch against the WiX repository.

## Additional information

* Web site: https://www.firegiant.com/wixtoolset/
* Documentation [WiX Documentation](https://docs.firegiant.com/wixtoolset/)
* Issue Tracker: [GitHub Issues](https://github.com/wixtoolset/issues/issues)
* Discussions: [WiX Toolset Discussions](https://github.com/orgs/wixtoolset/discussions)
