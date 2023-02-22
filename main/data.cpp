#include "header.h"

Partition get_data(string fname, Partition &p_struct) {

	// https://github.com/clelidm/MinCompSpin_Greedy

	__int128_t state;
	string fpath = "../input/data/" + fname + ".dat";
	string line, subline;
	ifstream myfile(fpath);

	while (getline(myfile, line)) {

		subline = line.substr(0,n);
		state = string_to_int(subline);
		p_struct.data[state]++;
		p_struct.N++;

	}

	myfile.close();

	cout << "loaded: " << fpath << endl;
	cout << p_struct.N << " samples." << endl;

	return p_struct;


}