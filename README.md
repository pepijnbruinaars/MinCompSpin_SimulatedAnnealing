## Community detection using Minimally Complex Models: Simulated annealing algorithm

This program allows to find community structures in binary data by using inference based on a class of spin models (maximum entropy models for binary data) called Minimally Complex Models (MCM). It is an alternative to another algorithm that can be found here: https://github.com/clelidm/MinCompSpin_Greedy. Details about MCMs can also be found there. 

The algorithms works by calculating the log-evidence $\log E$ for a given initial partition $C_i$ (community structure). It then proposes slight changes to the partition and calculates the difference in log-evidence $\Delta \log E$. If the new partition $C_{i+1}$ has a larger log-evidence $\Delta \log E > 0$, the new partition is accepted. If not, the partition is still accepted with probability $P(C_{i+1}=C_i)\sim \exp(\Delta \log E/T_A)$ where $T_A$ is the annealing temperature. This parameter controls how likely the new partition is accepted. At large values, this prevents getting stuck in local optima. During the search the annealing temperature is gradually lowered allowing the algorithm to converge to an optimal solution. See https://en.wikipedia.org/wiki/Simulated_annealing for more details.


## Requirements
The code uses C++ version 11.

## Installation

### Windows

The code can be compiled using the `compile.bat` batch file in the `main` folder. This creates an `saa.exe` executable file. Alternatively, the code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.exe`. There is an additional batch file `compile_and_run.bat` which is useful for testing purposes. It compiles the code and then runs an analysis.

### Linux / macOS

The code can be compiled using the command `g++ -std=c++11 -O3 -Wall ./*.cpp -o saa.out`.

## Running the code

The code is run from the executable file `saa.exe` (on Windows) or `saa.out` (on Linux/Mac) in the `main` folder with the filename of the dataset as a required argument. The data is assumed to be in the `data` folder and should end with `.dat` extension. The data should be encoded as binary strings, e.g. `11001110010` which are read from right to left. Currently the maximum number of variables is 64.

### Example:

The `data` folder contains an example dataset on 20 variables. The `comms` folder contains an example partition.

To analyse the dataset `./data/my_data.dat` run the command (for Linux/Mac, replace .exe with .out):

`saa.exe my_data`

In this case, the initial partition is a random partition. Optionally, to load an initial partition, use:

`saa.exe my_data -l my_partition`

This partition should be located in the `comms` folder and have the name `my_partition.dat`.

## Important details

- In the current version, the number of variables `n` should be declared before compilation in `./data/header.h`.
- The parameter `EPSILON` controls the minimum difference in log-evidence the best partition should have from the previous best in ordered to be considered the new best. Setting this to 0 can result in partitions that are equivalent up to permutation to be considered better due to numerical inaccuracy. This can cause the algorithm to perform more iterations than strictly necessary.

