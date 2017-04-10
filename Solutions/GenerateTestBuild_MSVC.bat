@echo off

IF [%1] EQU [] (
    echo Platform not specified
    exit /b
)

IF [%2] EQU [] (
    echo Visual studio toolset version is not specified
    exit /b
)

IF [%3] EQU [] (
    echo Visual studio toolset year is not specified
    exit /b
)

set gnrtVer=%2
set gnrtYear=%3
set gnrt=Visual Studio %gnrtVer% %gnrtYear%

if %1 EQU 32 (
    set arch=X32
) else (if %1 EQU 64 (
    set arch=X64
    set gnrt=%gnrt% Win64
) else (
    echo Invalid architecture specified %1
    exit /b
))

set folderName=TestBuild_%1_%gnrtVer%_%gnrtYear%

if not exist %folderName% mkdir %folderName%
pushd %folderName%

set _TOP0=%cd%\..\..
set _TOP=%_TOP0:\=/%

cmake -G"%gnrt%" -DTOP:DIR="%_TOP%" "%_TOP%/Projects/TestProject/build/" -DBUILD_ARCHITECTURE="%arch%"

popd