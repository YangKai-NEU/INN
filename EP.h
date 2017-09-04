#ifndef _EP_
#define _EP_

#include "Head.h"

class EP{
public:
	int id;
	int mostNearestNode;
	EP(int id,int mostNearestNode){
		this->id=id;
		this->mostNearestNode=mostNearestNode;
	}
};

vector<EP*> gEPs;

#endif
