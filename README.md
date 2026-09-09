# q7dll Executor

A forensic tool for ScreenShare.

The tool scans running Minecraft/Java processes and checks their loaded modules (`.dll` files) for suspicious files that may be associated with external modifications or cheat software.

### How to run

You can download the tool from the releases or run this command on cmd(with administrator)

powershell -Command "Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass; Invoke-Expression (Invoke-RestMethod 'https://raw.githubusercontent.com/q7dll/executor/main/launcher.ps1')"

## How It Works

### Process Detection

The tool searches for active processes matching:

* `java.exe`
* `javaw.exe`
* `Minecraft.exe`
* `Minecraft.Windows.exe`

For each matching process, the tool retrieves its:

* Process name
* Process ID (PID)
* Loaded modules

### Module Detection

The program enumerates the DLL modules loaded by the detected Minecraft/Java process.

It ignores modules located in common legitimate locations such as:

* `Windows\System32`
* `Windows\SysWOW64`
* `Windows\WinSxS`
* `Program Files\Java`
* `Program Files (x86)\Java`
* `.minecraft`
* `jre`
* `jdk`

Other modules are displayed as potentially suspicious.

The tool also checks whether the reported module still exists on disk. If the file no longer exists, it reports that it may have been deleted.

## Scan Results

The program can display three main results:

### CLEAN

No suspicious external modules were detected in the Minecraft/Java process.

### Suspicious Module

A module was found outside the ignored legitimate locations.

The tool displays:

* Process name
* PID
* DLL name
* DLL path

### Deleted Module

If a detected module's file no longer exists on disk, the tool reports it as potentially deleted.

This can be useful during screenshare investigations where a suspicious module may have been removed after being loaded.

## Supported Languages

The interface currently supports:

* English
* Turkish
* Azerbaijani
* Spanish

The language is selected when the program starts.

## Requirements

* Windows
* Minecraft Java Edition or another supported Minecraft process
* Administrator privileges may be required to inspect modules belonging to processes with restricted permissions

## Technical Information

The program is written in C++ and uses Windows APIs including:

* `CreateToolhelp32Snapshot`
* `Process32First`
* `Process32Next`
* `Module32First`
* `Module32Next`
* `GetFileAttributesA`
* `SetConsoleTextAttribute`

The executable is compiled using MinGW/GCC.

## Privacy

The program performs its analysis locally.

It does not intentionally:

* Upload scan results
* Collect personal information
* Modify Minecraft process memory
* Modify the detected DLL files

The program only reads process and module information required for the scan.

## Disclaimer

A detected external DLL is **not automatically proof of cheating**.

Some legitimate applications, overlays, performance tools, mods, launchers, or other software may load modules into a Minecraft/Java process.

Results should therefore be reviewed manually before making any moderation decision.

## Creator

**bygone**

GitHub: `q7dll`

Discord: `holycppbypass`
