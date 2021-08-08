# Hazelchain

A sick crypto that is simple to use and easy to understand whilst having a ton of functionality.

[![CMake](https://github.com/Shadow2ube/Hazelchain/actions/workflows/cmake.yml/badge.svg)](https://github.com/Shadow2ube/Hazelchain/actions/workflows/cmake.yml)

## Table of contents

1. [Design Goals](#Design-Goals)
2. [Running](#Running)
3. [Contributing](#Contributing)

---

## Design Goals

Goals that were taken into consideration when developing Hazelchain, were that we wanted this to be a simple to use and
easy to understand cryptocurrency.

To distribute coins as well as reduce Hazelchain's carbon footprint, hazelchain was developed to be able to switch
between 2 concensus algorithms, both [proof of work](https://www.investopedia.com/terms/p/proof-work.asp)
and [proof of stake](https://www.investopedia.com/terms/p/proof-stake-pos.asp)

---

## Running

### Prerequisites:

- Windows:
    - Windows 7 or higher
    - git
- GNU/Linux:
    - git

### Steps:

1. download the [zip](https://github.com/Shadow2ube/Hazelchain/archive/refs/heads/master.zip) or clone the repository.
2. extract the contents to an empty folder.
3. Run the bootstrapper (*Keep in mind the files to be downloaded are large*)
    - If you're using linux:
        1. Open a bash
        2. Run `linux.sh`

    - If you're using Windows:
       2. Open Windows Powershell
       3. Run `windows.bat` in powershell

7. Optional: Add `dev/vcpkg` to path
8. Open and run the project as a Cmake project in your IDE.

---

## Contributing

In order to contribute to this repository you must do the following:

1. Work on little files, methods or variables as possible to cut down on collisions
2. Please don't get mad if we don't merge your PR (there is most likely a reason)
3. If you spam us in any way for no good reason, you will be banned.

---
