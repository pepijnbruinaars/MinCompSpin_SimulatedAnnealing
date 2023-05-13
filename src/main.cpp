#include "header.h"

int main(int argc, char **argv) {

	cout << "SIMULATED ANNEALING [STAND-ALONE VERSION, UNUSED_BITS]" << endl;

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
    		cout << "input partition: " << pname << endl;
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
    	// p_struct = random_partition(p_struct);
    	p_struct = independent_partition(p_struct);
    }

    // main algorithm 
    p_struct = simulated_annealing(p_struct, max_iterations, max_no_improve);



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