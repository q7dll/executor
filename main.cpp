```cpp
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <algorithm>

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool Contains(const std::string& str, const std::string& substr) {
    std::string a = str, b = substr;
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a.find(b) != std::string::npos;
}

int main() {
    SetConsoleTitleA("q7dll Executor");
    SetConsoleOutputCP(CP_UTF8);

    SetColor(13);
    std::cout << R"(
  ███████╗██╗  ██╗███████╗ ██████╗██╗   ██╗████████╗ ██████╗ ██████╗ 
  ██╔════╝╚██╗██╔╝██╔════╝██╔════╝██║   ██║╚══██╔══╝██╔═══██╗██╔══██╗
  █████╗   ╚███╔╝ █████╗  ██║     ██║   ██║   ██║   ██║   ██║██████╔╝
  ██╔══╝   ██╔██╗ ██╔══╝  ██║     ██║   ██║   ██║   ██║   ██║██╔══██╗
  ███████╗██╔╝ ██╗███████╗╚██████╗╚██████╔╝   ██║   ╚██████╔╝██║  ██║
  ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═╝
)" << std::endl;

    SetColor(9);
    std::cout << "                       discord: holycppbypass" << std::endl;
    SetColor(13);
    std::cout << "                       github: q7dll" << std::endl;

    SetColor(8);
    std::cout << "\n---------------------------------------------------------------\n" << std::endl;

    SetColor(15);
    std::cout << "What language do you want to continue?\n";
    std::cout << "1-English\n";
    std::cout << "2-Turkish\n";
    std::cout << "3-Azerbaijan\n";
    std::cout << "4-Español\n";
    std::cout << "> ";

    int lang = 1;
    std::cin >> lang;
    if (lang < 1 || lang > 4) lang = 1;
    std::cin.ignore();

    std::string scanning, adminMsg, dllTag, procTag, dllNameTag;
    std::string sdMsg, noMc, cleanMsg, pauseHint;

    if (lang == 2) {
        scanning = "Taranıyor";
        adminMsg = "Yonetici olarak çalıştır.";
        dllTag = "[!] .dll";
        procTag = "    Islem: ";
        dllNameTag = "    DLL:   ";
        sdMsg = "    [diskten silinmiş (sd ihtimali)] ";
        noMc = "Minecraft açık değil.";
        cleanMsg = "Temiz.";
        pauseHint = "Devam etmek için bir tuşa basın...";
    } else if (lang == 3) {
        scanning = "Axtarılır";
        adminMsg = "Sistemi yönətici olaraq başlat.";
        dllTag = "[!] .dll";
        procTag = "    Proses: ";
        dllNameTag = "    DLL:    ";
        sdMsg = "    [diskden silinib (sd ehtimali)] ";
        noMc = "Minecraft açıq deyil.";
        cleanMsg = "Temiz.";
        pauseHint = "Davam etmək üçün bir düyməyə basın...";
    } else if (lang == 4) {
        scanning = "Escaneando";
        adminMsg = "Ejecuta como administrador.";
        dllTag = "[!] .dll";
        procTag = "    Proceso: ";
        dllNameTag = "    DLL:     ";
        sdMsg = "    [eliminado del disco (posible Self Destruct)] ";
        noMc = "Minecraft no esta abierto.";
        cleanMsg = "Limpio.";
        pauseHint = "Pulsa una tecla para continuar...";
    } else {
        scanning = "Scanning";
        adminMsg = "Run as administrator.";
        dllTag = "[!] .dll";
        procTag = "    Process: ";
        dllNameTag = "    DLL:     ";
        sdMsg = "    [deleted from disk (possible Self destruct)] ";
        noMc = "Minecraft is not open.";
        cleanMsg = "Clean.";
        pauseHint = "Press any key to continue...";
    }

    std::cout << "\n";

    for (int i = 0; i <= 100; i += 2) {
        std::cout << "\r" << scanning << ": [";
        int p = i / 2;
        for (int j = 0; j < 50; ++j) {
            if (j < p) std::cout << "=";
            else if (j == p) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] %" << i << " ";
        Sleep(20);
    }
    std::cout << "\n\n";

    bool foundAny = false;
    bool foundMc = false;

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        SetColor(12);
        std::cout << adminMsg << std::endl;
        system("pause");
        return 1;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            std::string processName = pe32.szExeFile;

            if (Contains(processName, "javaw.exe") || Contains(processName, "java.exe") ||
                Contains(processName, "Minecraft.Windows.exe") || Contains(processName, "Minecraft.exe")) {

                foundMc = true;
                DWORD pid = pe32.th32ProcessID;

                HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
                if (hModuleSnap == INVALID_HANDLE_VALUE) continue;

                MODULEENTRY32 me32;
                me32.dwSize = sizeof(MODULEENTRY32);

                if (Module32First(hModuleSnap, &me32)) {
                    do {
                        std::string modulePath = me32.szExePath;
                        std::string moduleName = me32.szModule;

                        if (!Contains(modulePath, "Windows\\System32") &&
                            !Contains(modulePath, "Windows\\SysWOW64") &&
                            !Contains(modulePath, "Windows\\WinSxS") &&
                            !Contains(modulePath, "Program Files\\Java") &&
                            !Contains(modulePath, "Program Files (x86)\\Java") &&
                            !Contains(modulePath, ".minecraft") &&
                            !Contains(modulePath, "jre") &&
                            !Contains(modulePath, "jdk")) {

                            DWORD fileAttr = GetFileAttributesA(modulePath.c_str());
                            bool fileExists = (fileAttr != INVALID_FILE_ATTRIBUTES);

                            SetColor(12);
                            std::cout << dllTag << std::endl;
                            SetColor(15);
                            std::cout << procTag << processName << " (PID: " << pid << ")" << std::endl;
                            std::cout << dllNameTag << moduleName << std::endl;

                            if (fileExists) {
                                SetColor(14);
                                std::cout << "    " << modulePath << std::endl;
                            } else {
                                SetColor(12);
                                std::cout << sdMsg << modulePath << std::endl;
                            }
                            std::cout << "    -------------------------------------------------------" << std::endl;
                            foundAny = true;
                        }
                    } while (Module32Next(hModuleSnap, &me32));
                }
                CloseHandle(hModuleSnap);
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);

    if (!foundMc) {
        SetColor(12);
        std::cout << noMc << std::endl;
    } else if (!foundAny) {
        SetColor(10);
        std::cout << cleanMsg << std::endl;
    }

    SetColor(15);
    system("pause");
    return 0;
}
```
