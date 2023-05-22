#include "header.h"
#include <time.h>
#include <ctime> 
#include <ratio>
#include <chrono>

void simulated_annealing(Partition &p_struct, 
	unsigned int max_iterations, 
	unsigned int max_no_improve,
	string spath
	) {

	cout << "\n- running simulated annealing algorithm\n" << endl; 

	unsigned int f;
    unsigned int iterations = 0;
    unsigned int steps_since_improve = 0;

    // annealing parameters
    double T0 = 100; // initial annealing temperature
    p_struct.T = T0;
    unsigned int update_schedule = 100; // number of iterations at same annealing temperature

	// performance and stats
    auto start = chrono::system_clock::now();
	int n_accepted_partitions = 0;
	int n_merges = 0;
	int n_accepted_merges = 0;
	int n_splits = 0;
	int n_accepted_splits = 0;
	int n_switches = 0;
	int n_accepted_switches = 0;
	int latest_operation = 0;

    for (unsigned int i = 0; i < max_iterations; i++){

    	iterations++;

    	// check for limit cases 
    	if (p_struct.nc == p_struct.n){
    		f = 0; // always merge if all independent communities
    	} else if (p_struct.nc == 1){
    		f = 1; // always split if one big community
    	} else {
    		f = rand()/(RAND_MAX/3);
    	}

    	// choose proposal function
		switch(f){
		case 0: 
			merge_partition(p_struct);
			n_merges++;
			latest_operation = 0;
			break;
		case 1:
			split_partition(p_struct);
			n_splits++;
			latest_operation = 1;
			break;
		case 2:
			switch_partition(p_struct);
			n_switches++;
			latest_operation = 2;
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

			cout << "best log-evidence: " << p_struct.best_log_evidence << "\t@T = " << p_struct.T << "\ti = " << i << endl;
			
			steps_since_improve = 0;
			n_accepted_partitions++;
			if (latest_operation == 0){
				n_accepted_merges++;
			} else if (latest_operation == 1){
				n_accepted_splits++;
			} else {
				n_accepted_switches++;
			}
		} else {
			steps_since_improve++;
		}

		// stop if no improvement 
		if (steps_since_improve > max_no_improve){
			cout << "\n- maximum iterations without improvement reached" << endl;
			break;
		}
    }

    // performance 
    auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << "- iterations per second: " << static_cast <double> (iterations) / elapsed.count() << "\n" << endl;

	// at completion, make sure current partition is equal to best partition
	p_struct.current_log_evidence = p_struct.best_log_evidence;
	p_struct.current_partition = p_struct.best_partition;

	// append stats to file
	ofstream stats_file;
	stats_file.open(spath, ios_base::app);
	stats_file << "-----Simulated annealing-----" << endl;
	stats_file << "iterations: " << iterations << endl;
	stats_file << "iterations per second: " << static_cast <double> (iterations) / elapsed.count() << endl;
	stats_file << "runtime: " << elapsed.count() << "s" << endl;
	stats_file << "best log-evidence: " << p_struct.best_log_evidence << endl;
	stats_file << "accepted partitions: " << n_accepted_partitions << endl;
	stats_file << "attempted merges: " << n_merges << endl;
	stats_file << "attempted splits: " << n_splits << endl;
	stats_file << "attempted switches: " << n_switches << endl;
	stats_file << "accepted merges: " << n_accepted_merges << endl;
	stats_file << "accepted splits: " << n_accepted_splits << endl;
	stats_file << "accepted switches: " << n_accepted_switches << endl;
	stats_file.close();
}