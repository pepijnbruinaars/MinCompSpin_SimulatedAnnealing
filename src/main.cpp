#include "header.h"

int main(int argc, char **argv) {


	cout << "SIMULATED ANNEALING [STAND-ALONE VERSION - v20230513]\n" << endl;


	// ==== initialize RNG ====
 	random_device randDevice;
    srand(randDevice());
    // ========================


    // ==== declarations ======
    bool pload = false; // load partition
    bool rload = false;
    bool greedy = false;
    string fname, pname;
    // ========================


    // ==== default values ====
    unsigned int max_iterations = 50000;
    unsigned int max_no_improve = 10000;
    // ========================


    // ==== parse runtime arguments ====
    unsigned int n;
    sscanf(argv[1], "%d", &n);

    for (int i = 2; i < argc; i++) {

    	string arg = argv[i];

    	// input data
    	if (arg == "-i") {
    		fname = argv[i+1];
    		i++;
    		cout << "- input file: " << fname << endl;
    	}

    	// input partition
    	if (arg == "-p") {
    		pname = argv[i+1];
    		pload = true;
    		i++;
    		cout << "- input partition: " << pname << endl;
    	}

        // start from random partition
    	if (arg == "-r") {
    		rload = true;
    	}

        // perform greedy merhing
    	if (arg == "-g") {
    		greedy = true;
    	}

    	// maximum iterations
    	if (arg == "--max") {
    		max_iterations = stoi(argv[i+1]);
    		i++;
    	}

    	// stopping iterations
    	if (arg == "--stop") {
    		max_no_improve = stoi(argv[i+1]);
    		i++;
    	}
    }

    cout << "- max iterations (stop): ";
    cout << max_iterations;
    cout << " (" << max_no_improve << ")\n" << endl;
    // =================================

    // initialize partition and load data
    Partition p_struct(n);
    p_struct = get_data(fname, p_struct);

    if (pload) {
    	p_struct = load_partition(p_struct, pname);
    } else if (rload) {
    	p_struct = random_partition(p_struct);
    } else {
    	p_struct = independent_partition(p_struct);
    }



    if (greedy) {
        p_struct = greedy_merging(p_struct);
    }
    
    // main algorithm 
    p_struct = simulated_annealing(p_struct, max_iterations, max_no_improve);




	// print and save best partition
	string cpath = "../output/comms/" + fname + "_comms.dat";
	string spath = "../output/stats/" + fname + "_stats.dat";
	ofstream comm_file(cpath);
	ofstream stat_file(spath);
	stat_file << "best log-evidence: " << p_struct.best_log_evidence << endl;
    cout << "final log-evidence: " << p_struct.best_log_evidence << endl;
    cout << "final community: " << endl;
	for(unsigned int i = 0; i < n; i++){
		__uint128_t community = p_struct.best_partition[i];
		if (bit_count(community) > 0){
			cout << i << "\t" << int_to_bitstring(community, n) << " | size: " << bit_count(community) << endl;
			comm_file << int_to_bitstring(community, n) << endl;
		}
	}   
	comm_file.close(); 
	stat_file.close(); 

    return 0;

}