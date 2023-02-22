#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <map>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const unsigned int n = 100;
const __int128_t ONE = 1; // 128-bit representation of 1
const double EPSILON = 1e-4; // minimum change in log-evidence 

struct Partition {

	double T; // annealing temperature
	double current_log_evidence = 0;
	double best_log_evidence = 0;

	unsigned int N = 0; // number of samples in dataset
	unsigned int nc = 0; // current number of communities 

	__int128_t occupied_partitions = 0; // occupied communities (with at least one node)
	__int128_t occupied_partitions_gt2_nodes = 0; // communities with at least two nodes (for split and switch)
	
	map<__int128_t, unsigned int> data;
	vector<__int128_t> current_partition = vector<__int128_t>(n);
	vector<__int128_t> best_partition = vector<__int128_t>(n);
	vector<double> partition_evidence = vector<double>(n); // log-evidence for each community 
};

// function declarations
bool DoubleSame(double a, double b);

// bit manipulation stuff
unsigned int bit_count(__int128_t number);
unsigned int randomBitIndex(__int128_t number);
string int_to_bitstring(__int128_t number, unsigned int r);
__int128_t string_to_int(string nstring);
__int128_t random_128_int(unsigned int k);

// evidence calculation
map<__int128_t, unsigned int> build_pdata(map<__int128_t, unsigned int> &data, __int128_t community);
double icc_evidence(__int128_t community, Partition &p_struct);

// partitions and data
Partition get_data(string fname, Partition &p_struct);
Partition random_partition(Partition &p_struct);
Partition load_partition(Partition &p_struct, string pname);
Partition parse_community(Partition &p_struct, __int128_t community, int i);

// proposal functions
Partition merge_partition(Partition &p_struct);
Partition split_partition(Partition &p_struct);
Partition switch_partition(Partition &p_struct);









