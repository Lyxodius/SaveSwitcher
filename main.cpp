#include <Windows.h>
#include <cstdio>
#include <string>
#include <regex>
#include <filesystem>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    std::string path = R"(C:\Lyxodius\Emulation\PS3\dev_hdd0\home\00000001\savedata\)";

    std::string regularFilename = path + "BLES00932DEMONSS005";
    std::regex arnoldRegex(".+ - Arnold");
    std::regex simonRegex(".+ - Simon");

    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        std::string entryPath = entry.path().string();
        if (std::regex_search(entryPath, arnoldRegex)) {
            rename(regularFilename.c_str(), (regularFilename + " - Simon").c_str());
            rename((regularFilename + " - Arnold").c_str(), regularFilename.c_str());
            MessageBoxW(nullptr, L"Zu Arnold gewechselt.", L"SaveSwitcher", MB_ICONINFORMATION);
            break;
        } else if (std::regex_search(entryPath, simonRegex)) {
            rename(regularFilename.c_str(), (regularFilename + " - Arnold").c_str());
            rename((regularFilename + " - Simon").c_str(), regularFilename.c_str());
            MessageBoxW(nullptr, L"Zu Simon gewechselt.", L"SaveSwitcher", MB_ICONINFORMATION);
            break;
        }
    }
    return 0;
}
