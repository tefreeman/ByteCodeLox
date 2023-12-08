# Bytecode Lox Interpreter

## Overview
This project is a bytecode interpreter for the Lox language, implemented in C.

## Features
- **REPL Mode:** Interactive Read-Evaluate-Print-Loop for executing Lox code in a command-line interface.
- **File Execution:** Ability to execute Lox scripts from source files.
- **Bytecode Compilation:** Translates Lox source code into bytecode for efficient execution.
- **Error Handling:** Robust error reporting for compile-time and runtime errors.

## Installation

1. **Download the Repository**
   - First, download the repository containing the necessary files.

2. **Locate the Binary File**
   - Within the downloaded repository, there is a Windows x64 binary file named `Lox.exe`.

## Running the Application

After installation, you can run the `Lox` application in different modes using a terminal such as PowerShell or Command Prompt. Navigate to the directory of the downloaded repository to execute the following commands.


## Usage
After building the project, you can use the interpreter in two modes:

To run the interpreter in interactive mode, execute without any arguments:
```bash
./Lox
```
### Script Mode
```bash
./Lox path/to/your_script.lox
```

## Building Instructions for the Project
 Step-by-step guide on how to build the project using Microsoft Visual Studio.

## Prerequisites

- Microsoft C++/C Compiler (MSVC)
- C++17 Standard

## Steps

1. **Download the Repository**
   - Begin by downloading the repository from the provided link.

2. **Install Microsoft Visual Studio**
   - Download and install Microsoft Visual Studio for Windows or Mac from [Visual Studio's official website](https://visualstudio.microsoft.com/).

3. **Open the Project**
   - After installing Visual Studio, open the project by double-clicking the `.sln` file. This action should load the project along with all the necessary settings.

4. **Build the Project**
   - In the Visual Studio IDE, navigate to the `Build` tab located at the top of the window.
   - Select `Build Solution` from the dropdown menu. This step will compile and build the project.

5. **Locate the Executable**
   - Once the build process is complete, you can find the `Yisp.exe` file in the `Yisp/x64/Debug/` folder.
