if not exist TestBuild mkdir TestBuild
pushd TestBuild

set _TOP0=%cd%\..\..
set _TOP=%_TOP0:\=/%

cmake -DTOP:DIR=%_TOP% %_TOP%/Build/Code/Projects/TestProject/ -DBUILD_ARCHITECTURE="X64"

popd