#include <Windows.h>

enum
{
    OK,
    FailedParsingCommandLineArgs,
    InvalidArgs,
    CouldNotFindApplication,
    CouldNotFindRunFunction
};

int CALLBACK WinMain(
    _In_ HINSTANCE /*hInstance*/,
    _In_ HINSTANCE /*hPrevInstance*/,
    _In_ LPSTR     /*lpCmdLine*/,
    _In_ int       /*nCmdShow*/
)
{
    int numArgs;

    LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &numArgs);

    if (szArglist == nullptr)
    {
        return FailedParsingCommandLineArgs;
    }

    HMODULE module = nullptr;

    if (numArgs < 2)
    {
        OPENFILENAMEW ofn;

        wchar_t szFile[MAX_PATH];

        // open a file name
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = L"DLL\0*.dll\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        GetOpenFileNameW(&ofn);

        module = LoadLibraryW(ofn.lpstrFile);
    }
    else
    {
        module = LoadLibraryW(szArglist[1]);
    }

    if (module == nullptr)
    {
        return CouldNotFindApplication;
    }

    using RunFunction = int(__cdecl *)();

    auto pRunFn = (RunFunction)(GetProcAddress(module, TEXT("KGL_Run")));

    if (pRunFn == nullptr)
    {
        return CouldNotFindRunFunction;
    }

    return pRunFn();
}