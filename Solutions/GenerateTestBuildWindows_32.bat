if not exist TestBuild_32 mkdir TestBuild_32
pushd TestBuild_32

set _TOP0=%cd%\..\..
set _TOP=%_TOP0:\=/%

cmake -G"Visual Studio 14 2015" -DTOP:DIR=%_TOP% %_TOP%/Build/Code/Projects/TestProject/ -DBUILD_ARCHITECTURE="X32"

popd