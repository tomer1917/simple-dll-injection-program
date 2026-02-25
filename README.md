# Simple DLL Injection Program

An educational C++ project demonstrating how to build a dynamic link library (DLL) and inject it into a running Windows process (`mspaint.exe`) using standard Windows API functions.

## 📌 Overview
This repository contains two separate components:
1. **The Payload (DLL):** A custom C++ library that executes a simple action (like showing a message box or modifying window attributes) the moment it is loaded into memory.
2. **The Injector (Executable):** A C++ console application that finds the target process, allocates memory inside it, writes the DLL path, and forces the process to load the library via `CreateRemoteThread`.

## ⚙️ Prerequisites
* Windows OS (64-bit)
* Visual Studio (with "Desktop development with C++" workload installed)

## 🛠️ How to Build
1. Open the solution file (`.sln`) in Visual Studio.
2. At the top of the Visual Studio window, ensure your build configuration is set to **Release** and your architecture is set to **x64**. 
   *(Note: The injector and the DLL must be compiled for the exact same architecture as the target process).*
3. Go to the top menu and select **Build > Build Solution**.
4. Both the compiled `.dll` and `.exe` files will be generated in your output folder (usually `x64\Release\`).

## 🚀 How to Use
1. **Important:** Before running, you must open `myInjector.cpp` and update the `dllPath` variable to point to the exact location of your compiled DLL on your computer. Rebuild the injector after doing this.
2. Open **MS Paint** (`mspaint.exe`) and leave it running in the background.
3. Run the compiled Injector executable.
4. If successful, the console will print a confirmation and the DLL payload will execute inside MS Paint.

## ⚠️ Disclaimer
This project was created strictly for educational purposes to understand Windows memory management and process execution. It should only be used on applications and systems you own or have explicit permission to test.
