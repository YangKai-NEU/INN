#ifndef _EXP_H_
#define _EXP_H_

#include "Head.h"

class Exp {
public:

	/*
	* deal with the parameters, do exp
	*/
	void DealParameter(int argc, char* argv[]) {
		
		if(argc>=8){
			data_path=argv[1];
			EP_size=atoi(argv[2]);
			graph_path=argv[3];
			AIM_size=atoi(argv[4]);
			fingerThreshold=atof(argv[5]);
			TEST_TIMES=atoi(argv[6]);
			default_distance_ratio=atof(argv[7]);
		}else{
			data_path="../data/D3/Task_2_training_data.txt";
			EP_size=99;
			graph_path="../data/D3/graph.txt";
			AIM_size=5;
			fingerThreshold=99.0;
			TEST_TIMES=1000;
			default_distance_ratio=1;
		}
		
#ifdef _DEBUG_
		cout<<"parameters are shown as follows:"<<endl;
		cout<<"\tData:"<<data_path<<endl;
		cout<<"\tGraph:"<<graph_path<<endl;
		cout<<"\tEP:"<<EP_size<<endl;
		cout << "deal with the parameters successfully..." << endl;
#endif // _DEBUG_

	}

};

Exp *gExp = new Exp();

#endif
