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
    get_data(fname, p_struct);

    if (pload) {
    	load_partition(p_struct, pname);
    } else if (rload) {
    	random_partition(p_struct);
    } else {
    	independent_partition(p_struct);
    }

	// performance
    auto start = chrono::system_clock::now();


    // main algorithm 
    simulated_annealing(p_struct, max_iterations, max_no_improve);
    
	if (greedy) {
        greedy_merging(p_struct);
        cout << "- current log-evidence (after GMA): " << p_struct.current_log_evidence << endl;
        cout << "- best log-evidence (after GMA):    " << p_struct.best_log_evidence << endl;
    }

    cout << "- current log-evidence (after SAA): " << p_struct.current_log_evidence << endl;
    cout << "- best log-evidence (after SAA):    " << p_struct.best_log_evidence << endl;

	// performance
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end-start;
	cout << "\n- elapsed time: " << elapsed_seconds.count() << "s\n" << endl;

	// print and save best partition
	string cpath = "../output/comms/" + fname + "_comms.dat";
	string spath = "../output/stats/" + fname + "_stats.dat";
	ofstream comm_file(cpath);
	ofstream stat_file(spath);
	stat_file << "best log-evidence: " << p_struct.best_log_evidence << endl;
	stat_file << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
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