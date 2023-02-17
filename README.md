## Requirements
The code uses C++11 version.

## Installation

### Windows

The code can be compiled using the `compile.bat` batch file in the `main` folder. This creates an `saa.exe` executable file. Alternatively, the code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.exe`.

### Linux / macOS

The code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.out`.

## How to run

The code is run from the executable file `saa.exe` (on Windows) or `saa.out` (on Linux/Mac) in the `main` folder with the filename of the dataset as an additional argument. The data is assumed to be in the `data` folder and should end with `.dat` extension. 

### Example:

To analyse the dataset `./data/FILENAME.dat` run the command

`saa.exe FILENAME`


