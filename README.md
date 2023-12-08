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

  
## Test and Validation
  - Fib.lox located inside the `/tests/trevor/` folder.

```plaintext
class Test {
 init(name) {
    this.name = name;
 }

 printName() {
    print this.name;
 }

 printStr(string) {
    print string;
 }

}

class Fib < Test {
 init(name, doRecursion) {
    super.init(name);
    this.doRecursion = doRecursion;
 }

 fibTestTo(n) {
    if (this.doRecursion) {
        super.printStr("Recursion method enabled");
    }
    for (var a = 1; a < n; a = a + 1) {
        if (this.doRecursion) {
            super.printStr(this.fib(a));
        } else {
            super.printStr(this.fibRecursive(a));
        }
    }
 }

 fib(n) {
    var a = 0;
    var b = 1;
    var c;
    var i;

    if(n == 0)
        return a;
    for(i = 2; i <= n; i = i + 1) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
 }

 fibRecursive(num) {
    if(num < 2) {
        return num;
    }
    else {
        return fibRecursive(num-1) + fibRecursive(num - 2);
    }
 }
}

// Fibonacci table =  https://r-knott.surrey.ac.uk/Fibonacci/fibtable.html 
// 0=1,1=1,2=1,3=2,3=3,4=3,5=5,6=8,7=13,8=21,9=34,10=55

var test = Fib("Trevor Fib test", true);

test.printName();

test.fibTestTo(10);

print test.fib(29); // 514229
print test.fib(80); // 23416728348467685 
print test.fib(300); // 222232244629420445529739893461909967206666939096499764990979600
```
Output was 

```plaintext
Trevor Fib test
Recursion method enabled
1
1
2
3
5
8
13
21
34
514229
2.34167e+16
2.22232e+62
```

