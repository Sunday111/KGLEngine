call "%VS140COMNTOOLS%\VsDevCmd.bat"
devenv %1 /Upgrade
msbuild %1 /p:Configuration=%2