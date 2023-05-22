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
    string fname, pname, cpath, spath;
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
			cpath = "./output/comms/" + fname + "_comms.dat";
			spath = "./output/stats/" + fname + "_stats.dat";
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
	int n_unique_samples = p_struct.data.size();
	double entropy = log2((double) n_unique_samples);
    if (pload) {
    	load_partition(p_struct, pname);
    } else if (rload) {
    	random_partition(p_struct);
    } else {
    	independent_partition(p_struct);
    }

	// performance
    auto start = chrono::system_clock::now();
	auto stats_file = ofstream(spath);
	// If the file exists, delete it
	if (stats_file) {
		stats_file.close();
		remove(spath.c_str());
	}

    // main algorithm 
    simulated_annealing(p_struct, max_iterations, max_no_improve, spath);
    
	if (greedy) {
        greedy_merging(p_struct, spath);
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
	ofstream comm_file(cpath);
	stats_file.open(spath, ios_base::app);
	stats_file << "-----Final Results-----" << endl;
	stats_file << "best log-evidence (Final): " << p_struct.best_log_evidence << endl;
	stats_file << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
	stats_file << "unique samples: " << n_unique_samples << endl;
	stats_file << "entropy: " << entropy << endl;
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
	stats_file.close(); 

    return 0;

}