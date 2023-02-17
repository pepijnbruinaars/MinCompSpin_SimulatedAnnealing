## Requirements
The code uses C++11 version.

## Installation

### Windows

The code can be compiled using the `compile.bat` batch file in the `main` folder. This creates an `saa.exe` executable file. Alternatively, the code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.exe`. There is an additional batch file `compile_and_run.bat` which is useful for testing purposes. It compiles the code and then runs an analysis.

### Linux / macOS

The code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.out`.

## How to run

The code is run from the executable file `saa.exe` (on Windows) or `saa.out` (on Linux/Mac) in the `main` folder with the filename of the dataset as an additional argument. The data is assumed to be in the `data` folder and should end with `.dat` extension. The data should be encoded as binary strings, e.g. `11001110010` which are read from right to left.

### Example:

The `data` folder contains an example dataset on 20 variables. The `comms` folder contains an example partition.

To analyse the dataset `./data/my_data.dat` run the command (for Linux/Mac, replace .exe with .out)

`saa.exe my_data`

In this case, the initial partition is a random partition. Alternatively, to load an initial partition, use

`saa.exe my_data -l my_partition`

This partition should be located in the `comms` folder and have the name `my_partition.dat`.

