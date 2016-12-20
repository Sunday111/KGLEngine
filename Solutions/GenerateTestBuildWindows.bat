@echo off

IF [%1] EQU [] (
    echo Platform not specified
    exit /b
)

set gnrt=Visual Studio 14 2015

if %1 EQU 32 (
    set arch=X32
) else (if %1 EQU 64 (
    set arch=X64
    set gnrt=%gnrt% Win64
) else (
    echo Invalid architecture specified %1
    exit /b
))

if not exist TestBuild_%1 mkdir TestBuild_%1
pushd TestBuild_%1

set _TOP0=%cd%\..\..
set _TOP=%_TOP0:\=/%

cmake -G"%gnrt%" -DTOP:DIR="%_TOP%" "%_TOP%/Projects/TestProject/" -DBUILD_ARCHITECTURE="%arch%"

popd