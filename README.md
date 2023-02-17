## Requirements
The code uses C++11 version.

## Installation

### Windows

The code can be compiled using the `compile.bat` batch file in the `main` folder. This creates an `saa.exe` executable file. Alternatively, the code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.exe`.

### Linux / macOS

The code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.out`.

## How to run

The code is run from the executable file `saa.exe` (on Windows) or `saa.out` (on Linux/Mac) in the `main` folder with the filename of the dataset as an additional argument. The data is assumed to be in the `data` folder and should end with `.dat` extension. The data should be encoded as binary strings, e.g. `11001110010` which are read from right to left.

### Example:

In the `data` folder, there are some example datasets on 20 variables. The `comms` folder contains an example partition.

To analyse the dataset `./data/HG19_k6_mu0.00_(20,4,5)_B0.55_N1000_00.dat` run the command (for Linux/Mac, replace .exe with .out)

`saa.exe HG19_k6_mu0.00_(20,4,5)_B0.55_N1000_00`

In this case, the initial partition is a random partition. Alternatively, to load an initial partition, use

`saa.exe HG19_k6_mu0.00_(20,4,5)_B0.55_N1000_00 -l my_partition`

This partition should be located in the `comms` folder and have the name `my_partition.dat`.

