# Hazelchain

A sick crypto that is simple to use and easy to understand whilst having a ton of functionality.

[![CMake](https://github.com/Shadow2ube/Hazelchain/actions/workflows/cmake.yml/badge.svg)](https://github.com/Shadow2ube/Hazelchain/actions/workflows/cmake.yml)

## Table of contents

1. [Design Goals](#Design-Goals)
2. [Running](#Running)

---

## Design Goals

Goals that were taken into consideration when developing Hazelchain, were that we wanted this to be a simple to use and
easy to understand cryptocurrency.

To distribute coins as well as reduce Hazelchain's carbon footprint, hazelchain was developed to be able to switch
between 2 consensus algorithms, both [proof of work](https://www.investopedia.com/terms/p/proof-work.asp)
and [proof of stake](https://www.investopedia.com/terms/p/proof-stake-pos.asp)

---

## Running

###### Warning: this was tested on Windows with MinGW-x86 and Ninja, results with other programs may vary

### Prerequisites:

- Windows:
    - Windows 7 or higher
    - git
- GNU/Linux:
    - git

### Steps:

1. Follow [these](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) steps to install Ninja
2. Add Ninja to your path
3. Download the [zip](https://github.com/Shadow2ube/Hazelchain/archive/refs/heads/master.zip) or clone the repository.
4. Extract the contents to an empty folder.
5. Download mingw x64
   from [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)
6. Run the bootstrapper (*Keep in mind the files to be downloaded might be large*)
    - If you're using linux:
        1. Open a bash
        2. Run `linux.sh`

    - If you're using Windows:
        2. Open Windows Powershell
        3. Run `windows.bat` in powershell

7. Open the project as a Cmake project in your preferred IDE
8. Set the cmake preset as CMakePresets.json
<<<<<<< HEAD
=======

---

## Contributing

In order to contribute to this repository you must do the following:

1. Work on as little files, methods or variables as possible to cut down on collisions
2. Please don't get mad if we don't merge your PR (there is most likely a reason)
3. If you spam us in any way for no good reason, you will be banned.
4. Try not to use boost when possible (trying to phase it out)
>>>>>>> 87e042af886b6790710d66c8010dc4a659051201

---
