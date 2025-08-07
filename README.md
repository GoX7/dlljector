# DLL Injector 🚀

A minimalist yet powerful DLL injection tool for Windows, written in C++ using WinAPI.

![Windows](https://img.shields.io/badge/Windows-10%2B-0078D6?logo=windows)
![License](https://img.shields.io/badge/License-MIT-green)
![Architecture](https://img.shields.io/badge/arch-x86%20%7C%20x64-blue)

## Features ✨

- Cross-architecture support (32-bit and 64-bit)
- Process privilege verification
- Dynamic memory allocation in target process
- Remote thread creation via `LoadLibraryA`
- Clean error handling and logging

## Usage 💻

```bash
inject.exe <PID> <path_to_dll>
```

Example:
```bash
inject.exe 1337 C:\path\to\your.dll
```

## Building 🛠️

### Native Compilation (Windows)
```bash
# 32-bit (x86)
g++ -m32 inject.cpp -o inject_x86.exe -static -lpsapi

# 64-bit (x64)
g++ -m64 inject.cpp -o inject_x64.exe -static -lpsapi
```

### Cross-Compilation (from Linux)
```bash
# 32-bit (x86)
i686-w64-mingw32-g++ inject.cpp -o inject_x86.exe -static -lpsapi

# 64-bit (x64)
x86_64-w64-mingw32-g++ inject.cpp -o inject_x64.exe -static -lpsapi
```

## Requirements 📋

- Windows 10+ (target system)
- MinGW-w64 or Visual Studio (for compilation)
- Administrator privileges (for most processes)

## Limitations ⚠️

- 32-bit injector can only target 32-bit processes
- 64-bit injector can only target 64-bit processes
- May trigger antivirus software (false positives)

## License 📜

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
