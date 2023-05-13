#include "header.h"

Partition get_data(string fname, Partition &p_struct) {

	// https://github.com/clelidm/MinCompSpin_Greedy

	__uint128_t state;
	string fpath = fname;
	string line, subline;
	ifstream myfile(fpath);

	while (getline(myfile, line)) {

		subline = line.substr(0, p_struct.n);
		state = string_to_int(subline, p_struct.n);
		p_struct.data[state]++;
		p_struct.N++;

	}

	myfile.close();

	cout << "loaded: " << fpath << endl;
	cout << p_struct.N << " samples" << endl;

	return p_struct;


}