#include "header.h"

Partition parse_community(Partition &p_struct, __uint128_t community, int i){

	p_struct.current_partition[i] = community;
	p_struct.partition_evidence[i] = icc_evidence(community, p_struct);
	p_struct.current_log_evidence += p_struct.partition_evidence[i];
	p_struct.occupied_partitions += (ONE << i);
	p_struct.nc++;
	if (bit_count(community) >= 2){
		p_struct.occupied_partitions_gt2_nodes += (ONE << i);
	}

	return p_struct;
}


Partition random_partition(Partition &p_struct) {

	__uint128_t community;
	__uint128_t assigned = 0;

	int i = 0;

	while(bit_count(assigned) < p_struct.n) {

		community = random_128_int(p_struct.n);
		community = community - (assigned & community);
		assigned += community;

		if (bit_count(community) > 0) {

			p_struct = parse_community(p_struct, community, i);

			cout << "New community: " << int_to_bitstring(community, p_struct.n) << endl;
			cout << "Log-evidence: " << p_struct.partition_evidence[i] << endl;
			cout << "Assigned nodes: " << int_to_bitstring(assigned, p_struct.n) << endl;
			cout << endl;
			i++;
		}
	}

	p_struct.best_log_evidence = p_struct.current_log_evidence;
	p_struct.best_partition = p_struct.current_partition;

	cout << "Generated " << p_struct.nc << " communities" << endl;
	cout << "Initial log-evidence: " << p_struct.current_log_evidence << endl;

	return p_struct;
}

Partition independent_partition(Partition &p_struct) {

	__uint128_t community;

	for (unsigned int i = 0; i < p_struct.n; i++) {

		community = (ONE << i);
		p_struct = parse_community(p_struct, community, i);

		cout << "New community: " << int_to_bitstring(community, p_struct.n) << endl;

	}

	p_struct.best_log_evidence = p_struct.current_log_evidence;
	p_struct.best_partition = p_struct.current_partition;

	cout << "Initial log-evidence: " << p_struct.current_log_evidence << endl;

	return p_struct;
}

Partition load_partition(Partition &p_struct, string pname) {

	p_struct.current_log_evidence = 0;

	string fpath = "../input/comms/" + pname + ".dat";
	string line;
	ifstream comm_file(fpath);
	__uint128_t community;
	int i = 0;
	while(getline(comm_file, line)){
		community = string_to_int(line, p_struct.n);
		p_struct = parse_community(p_struct, community, i);
		i++;
	}

	comm_file.close();

	p_struct.best_log_evidence = p_struct.current_log_evidence;
	p_struct.best_partition = p_struct.current_partition;
	
	cout << "Loaded " << p_struct.nc << " communities" << endl;
	cout << "Initial log-evidence: " << p_struct.current_log_evidence << endl;

	return p_struct;
}