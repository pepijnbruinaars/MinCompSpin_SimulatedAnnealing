#include "header.h"
#include <time.h>
#include <ctime> 
#include <ratio>
#include <chrono>

int main(int argc, char **argv) {


	// initialize RNG
	random_device randDevice;
    srand(randDevice());

    bool pload = false; // load partition
    string fname, pname;
    unsigned int max_iterations = 50000;
    unsigned int max_no_improve = 10000;

    // runtime arguments
    unsigned int n;
    sscanf(argv[1], "%d", &n);

    for (int i = 2; i < argc; i++) {

    	string arg = argv[i];

    	if (arg == "-i") {
    		fname = argv[i+1];
    		i++;
    		cout << "input file: " << fname << endl;
    	}

    	if (arg == "-p") {
    		pname = argv[i+1];
    		pload = true;
    		i++;
    		cout << "input partition: " << fname << endl;
    	}

    	if (arg == "--max") {
    		max_iterations = stoi(argv[i+1]);
    		i++;
    	}

    	if (arg == "--stop") {
    		max_no_improve = stoi(argv[i+1]);
    		i++;
    	}
    }

    cout << "max iterations (stop): " << max_iterations << " (" << max_no_improve << ")" << endl;

    // initialize partition and load data
    Partition p_struct(n);
    p_struct = get_data(fname, p_struct);

    if (pload) {
    	p_struct = load_partition(p_struct, pname);
    } else {
    	p_struct = random_partition(p_struct);
    }

    

    unsigned int f;
    unsigned int iterations = 0;
    unsigned int steps_since_improve = 0;

    // annealing parameters
    double T0 = 100; // initial annealing temperature
    p_struct.T = T0;
    unsigned int update_schedule = 100; // number of iterations at same annealing temperature
	// unsigned int max_no_improve = 10000; // max. iterations without improvement in log-evidence
	// unsigned int max_iterations = 50000; // max. total iterations

	// performance
    auto start = chrono::system_clock::now();

    for (unsigned int i = 0; i < max_iterations; i++){

    	iterations++;

    	// check for limit cases 
    	if (p_struct.nc == n){
    		f = 0; // always merge if all independent communities
    	} else if (p_struct.nc == 1){
    		f = 1; // always split if one big community
    	} else {
    		f = rand()/(RAND_MAX/3);
    	}

    	// choose proposal function
		switch(f){
		case 0: 
			p_struct = merge_partition(p_struct);
			break;
		case 1:
			p_struct = split_partition(p_struct);
			break;
		case 2:
			p_struct = switch_partition(p_struct);
			break;
		}

		// update annealing temperature
		if (i % update_schedule == 0){
			p_struct.T = T0 / (1 + log(1 + i));
		}

		// compare and update best log-evidence
		if ((p_struct.current_log_evidence > p_struct.best_log_evidence) && !(DoubleSame(p_struct.current_log_evidence, p_struct.best_log_evidence))){
			p_struct.best_log_evidence = p_struct.current_log_evidence;
			p_struct.best_partition = p_struct.current_partition;
			cout << "Best log-evidence: " << p_struct.current_log_evidence << "\t@T = " << p_struct.T << endl;
			steps_since_improve = 0;
		} else {
			steps_since_improve++;
		}

		// stop if no improvement 
		if (steps_since_improve > max_no_improve){
			cout << "Maximum iterations without improvement reached." << endl;
			break;
		}

    }

    // performance 
    auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "Iterations per second: " << static_cast <double> (iterations) / elapsed.count() << endl;

	// print and save best partition
	string cpath = "../output/comms/" + fname + "_comms.dat";
	string spath = "../output/stats/" + fname + "_stats.dat";
	ofstream comm_file(cpath);
	ofstream stat_file(spath);
	stat_file << "best log-evidence:" << p_struct.best_log_evidence << endl;
	for(unsigned int i = 0; i < n; i++){
		__uint128_t community = p_struct.best_partition[i];
		if (bit_count(community) > 0){
			cout << int_to_bitstring(community, n) << " " << bit_count(community) << endl;
			comm_file << int_to_bitstring(community, n) << endl;
		}
	}   

	comm_file.close(); 
	stat_file.close(); 

    return 0;

}