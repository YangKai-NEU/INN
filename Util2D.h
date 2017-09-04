#ifndef _UTIL2D_
#define _UTIL2D_

#include "Head.h"

class Util2D{
public:
	static double EuclideanDistance(double x1,double y1,double x2,double y2){
		return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}

	static double TriDistance(double t1,double t2,double b1,double b2,double l1,double r1){
		
		double result=0;
		double bottomLen=(b1+b2)/2;
		result+=t1*t1;
		result+=l1*l1;
		double cos2=t1*t1+bottomLen*bottomLen-t2*t2;
		cos2/=(2*t1*bottomLen);
		cos2=acos(cos2);
		double cos1=l1*l1+bottomLen*bottomLen-r1*r1;
		cos1/=(2*l1*bottomLen);
		cos1=acos(cos1);
		result-=2*t1*l1*cos(cos2-cos1);
		return sqrt(result);
	}
	
	static double VecDistance(vector<double> d1,vector<double> d2){
		double result=0;
		for(int i=0;i<EP_size;i++){
			result+=(d1[i]-d2[i])*(d1[i]-d2[i]);
		}
		
		return sqrt(result);
	}
};

#endif
