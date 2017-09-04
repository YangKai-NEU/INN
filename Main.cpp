#include "Head.h"
#include "Util2D.h"
#include "Exp.h"
#include "Graphic.h"
#include "Timer.h"
#include "EP.h"

int main(int argc, char* argv[]){

	gExp->DealParameter(argc,argv);
	
	gGraphic->initGraph(new FileReader(data_path.c_str()),new FileReader(graph_path.c_str()));
	gGraphic->processEPs();
#ifdef _DEBUG_
	gGraphic->print();
#endif

	int correctCount=0;
	double timeCount=0;
	srand((unsigned)time(NULL));
	double totalError=0.0;
	for(int q=0;q<TEST_TIMES;q++){
	
#ifdef _DEBUG_
		if(q%100==0){
			cout<<q<<"\t";
		}
#endif
		vector<vector<int>/**/> result;
		long a=(long)rand();
		int start;
		vector<int> ends;
		start=gGraphic->prcessStartAndEnds(ends);

		/*
		cout<<start<<": ";
		for(int o=0;o<ends.size();o++){
			cout<<ends[o]<<" ";
		}
		cout<<endl;
		
		getchar();
		
		
		start=160;
		ends.clear();
		ends.push_back(87);
		ends.push_back(148);
		ends.push_back(168);
		ends.push_back(100);
		ends.push_back(29);
		
		cout<<"start="<<start<<"\t";
		cout<<"end=";
		for(int r=0;r<ends.size();r++){
			cout<<ends[r]<<" ";
		}
		cout<<endl;*/
		
		
		
		

		/*

		start=26;
		ends.clear();
		ends.push_back(118);
		ends.push_back(190);
		ends.push_back(73);
		ends.push_back(24);
		ends.push_back(55);

		cout<<start<<": ";
		for(int o=0;o<ends.size();o++){
			cout<<ends[o]<<" ";
		}
		cout<<endl;
		*/
		

		
		Timer *timer=new Timer();
		timer->SC();
		gGraphic->processPaths(start,ends,result);
		timer->EC();
		timeCount+=timer->DC();


		/*
		cout<<"start: "<<start<<endl;
		cout<<"end: ";
		for(int u=0;u<ends.size();u++){
			cout<<ends[u]<<" ";
		}
		cout<<endl;


		cout<<"size="<<result.size()<<endl;
		for(int i=0;i<result.size();i++){
			for(int j=0;j<result[i].size();j++){
				cout<<result[i][j]<<" ";
			}
			cout<<endl;
		}

		*/

		
		
		pair<int,double> seT=gGraphic->SP(start,result);
		timer->SC();
		//pair<int,double> proSET=gGraphic->SPPro(start,result);
		pair<int,double> proSET=gGraphic->L2(start,ends);

		timer->EC();
		timeCount+=timer->DC();
		delete timer;

		if(seT.first==proSET.first){
			correctCount++;
		}else{
			vector<int> tmp1;
			tmp1.push_back(seT.first);
			vector<int> tmp2;
			tmp2.push_back(proSET.first);
			double r1=gGraphic->SP(start,tmp1).second;
			double r2=gGraphic->SP(start,tmp2).second;
			totalError+=abs(r1-r2);
		}
	}
#ifdef _DEBUG_
	cout<<endl;

	cout<<"the correct rate is "<<correctCount*100.0/TEST_TIMES<<"%"<<endl;
	cout<<"the total time is "<<timeCount<<" ms on average"<<endl;
	if(TEST_TIMES-correctCount<=THRES){
		cout<<"the average distance is "<<totalError/(TEST_TIMES-correctCount)<<endl;
		cout<<"the average length of edge is "<<gGraphic->avgLen()<<endl;
	}
#endif
	
	cout<<TEST_TIMES<<"\t"<<AIM_size<<"\t"<<correctCount*100.0/TEST_TIMES<<"\t"<<timeCount<<"\t"<<(TEST_TIMES-correctCount<=THRES?0:totalError/(TEST_TIMES-correctCount))<<"\t"<<gGraphic->avgLen()<<endl;

	return 0;
}
