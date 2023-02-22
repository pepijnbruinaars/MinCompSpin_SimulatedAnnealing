## Community detection using Minimally Complex Models: Simulated annealing algorithm

This program allows to find community structures in binary data of up to 128 variables by using inference based on a class of spin models (maximum entropy models for binary data) called Minimally Complex Models (MCM). It is an alternative to another algorithm that can be found here: https://github.com/clelidm/MinCompSpin_Greedy. Details about MCMs can also be found there. 

The algorithm works by calculating the log-evidence $\log E$ for a given initial partition $C_i$ (community structure). It then proposes slight changes to the partition and calculates the difference in log-evidence $\Delta \log E$. If the new partition $C_{i+1}$ has a larger log-evidence $\Delta \log E > 0$, the new partition is accepted. If not, the partition is still accepted with probability $P(C_{i+1}=C_i)\sim \exp(\Delta \log E/T_A)$ where $T_A$ is the annealing temperature. This parameter controls how likely the new partition is accepted. At large values, this prevents getting stuck in local optima. During the search the annealing temperature is gradually lowered allowing the algorithm to converge to an optimal solution. See https://en.wikipedia.org/wiki/Simulated_annealing for more details.

The algorithm can change the partition in three ways:
- merge: two communities are merged into a single community
- split: a single community is split into two communities (not necessarily of the same size)
- switch: a node from one community is placed inside another community


## Requirements
The code uses C++ version 11.

## Installation

### Windows

The code can be compiled using the `compile.bat` batch file in the `main` folder. This creates an `saa.exe` executable file. Alternatively, the code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.exe`. There is an additional batch file `compile_and_run.bat` which is useful for testing purposes. It compiles the code and then runs an analysis.

### Linux / macOS

The code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.out`.

## Running the code

The code is run from the executable file `saa.exe` (on Windows) or `saa.out` (on Linux/Mac) in the `main` folder with the filename of the dataset as a required argument. The data is assumed to be in the `./input/data` folder and should end with `.dat` extension. The data should be encoded as binary strings, e.g. `11001110010` which are read from right to left. The maximum number of variables is 128.

### Example:

The `./input/data` folder contains several example datasets on 20, 40, 60, 80 and 100 variables. The `./input/comms` folder contains initial partitions for 20 and 100 variables.

To analyse the dataset `./input/data/DATAFILE_NAME.dat` run the command (for Linux/Mac, replace .exe with .out):

`saa.exe DATAFILE_NAME`

In this case, the initial partition is a random partition. Optionally, to load an initial partition, use:

`saa.exe DATAFILE_NAME -l PARTITION_NAME`

This partition should be located in the `./input/comms` folder and have the name `PARTITION_NAME.dat`.

## Important details

- In the current version, the number of variables `n` should be declared before compilation in `./main/header.h`.
- The parameter `EPSILON` in `./main/header.h` controls the minimum difference in log-evidence the best partition should have from the previous best in ordered to be considered the new best. Setting this to 0 can result in partitions that are equivalent up to permutation to be considered better due to tiny numerical differences. This can cause the algorithm to perform more iterations than strictly necessary.

