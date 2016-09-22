if not exist TestBuild_64 mkdir TestBuild_64
pushd TestBuild_64

set _TOP0=%cd%\..\..
set _TOP=%_TOP0:\=/%

cmake -DTOP:DIR=%_TOP% %_TOP%/Build/Code/Projects/TestProject/ -DBUILD_ARCHITECTURE="X64"

popd