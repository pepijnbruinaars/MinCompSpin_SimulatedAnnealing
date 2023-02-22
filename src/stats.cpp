#include "header.h"

map<__int128_t, unsigned int> build_pdata(map<__int128_t, unsigned int> &data, __int128_t community) {

	map<__int128_t, unsigned int> pdata;
	map<__int128_t, unsigned int>::iterator it;

	int ks;
	__int128_t state, mask_state;

	for (it = data.begin(); it != data.end(); it++) {

		state = it -> first;
		ks = it -> second;

		mask_state = state & community;
		pdata[mask_state] += ks;
	}

	return pdata;
}

double icc_evidence(__int128_t community, Partition &p_struct){

	double logE = 0;
	int k;

	map<__int128_t, unsigned int> pdata = build_pdata(p_struct.data, community);
	map<__int128_t, unsigned int>::iterator it;

	unsigned int rank = bit_count(community);
	double rank_pow = (ONE << (rank - 1));

	double pf = lgamma(rank_pow) - lgamma(p_struct.N + rank_pow);

	logE += pf;
	for (it = pdata.begin(); it != pdata.end(); it ++){
			k = it -> second;
			logE += lgamma(k + 0.5) - lgamma(0.5);
		}

	return logE;
}