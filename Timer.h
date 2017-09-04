#ifndef _TIMER_H_
#define _TIMER_H_

#include "Head.h"

class Timer {
public:

	//start time and finish time
	struct timeval st, ft;
	struct timezone tz;
	
	/*
	* st the clock
	*/
	void SC() {
		gettimeofday(&this->st,&this->tz);
	}

	/*
	* ft the clock
	*/
	void EC() {
		gettimeofday(&this->ft,&this->tz);
	}

	/*
	* the duration in one process
	*/
	double DC() {
		double usec=this->ft.tv_usec - this->st.tv_usec;
		double sec=this->ft.tv_sec - this->st.tv_sec;
		return usec/1000+sec*1000;
	}
};

#endif
