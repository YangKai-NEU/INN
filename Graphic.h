#ifndef _GRAPHIC_
#define _GRAPHIC_

#include "Head.h"
#include "Fileprocessor.h"
#include "EP.h"

struct Compare {
	bool operator()(const pair<int, double> a, const pair<int, double> b) {
		return a.second > b.second;
	}
};

struct Node{
public:
	int id;
	vector<int> edges;
	vector<double> fingerprints;
	vector<int> dominateNodes;
	int dominateNode;
	bool isOut;
	double x,y;
	Node(int id,double x,double y){
		this->id=id;
		this->x=x;
		this->y=y;
		this->isOut=false;
		this->dominateNode=-1;
	}
};

struct Edge{
public:
	int id;
	int start;
	int end;
	double length;
	Edge(int id,int start,int end,double length){
		this->id=id;
		this->start=start;
		this->end=end;
		this->length=length;
	}
};

struct PNode{
public:
	vector<int> passedNodes;
	int id;
	bool has(int a){
		if(find(passedNodes.begin(),passedNodes.end(),a)!=passedNodes.end()){
			return true;
		}
		return false;
	}
	PNode(PNode* pre,int a){
		if(pre!=NULL){
			this->passedNodes=pre->passedNodes;
		}
		this->passedNodes.push_back(a);
		this->id=a;
	}
	void print(){
		for(int i=0;i<passedNodes.size();i++){
			cout<<passedNodes[i]<<" ";
		}
		cout<<endl;
	}
};

class Graphic{
public:
	vector<Node*> nodes;
	vector<Edge*> edges;
	map<pair<int,int>,bool> maps;
	Graphic(){}
	void initGraph(FileReader *fingerReader,FileReader *graphReader){
		nodes.push_back(new Node(0,-1,-1));
		int i;
		double x,y;
		double dis;
		int count=1;
		while((x=fingerReader->GetNextDouble())!=EOF){
			y=fingerReader->GetNextDouble();
			nodes.push_back(new Node(count,x,y));
			for(i=0;i<EP_size;i++){
				double tt=fingerReader->GetNextDouble();
				nodes[count]->fingerprints.push_back(abs(tt));
			}
			count++;
		}
		int id;
		int start,end;
		int order;
		int passDoor;
		count=0;
		while((id=graphReader->GetNextInt())!=EOF){
			start=graphReader->GetNextInt();
			end=graphReader->GetNextInt();
			order=graphReader->GetNextInt();
			passDoor=graphReader->GetNextInt();
			if(passDoor){
				if(start<end){
					maps[make_pair(start,end)]=true;
				}else{
					maps[make_pair(end,start)]=true;
				}
			}
			if(order==2){
				nodes[end]->dominateNodes.push_back(start);
				nodes[start]->dominateNode=end;
			}else if(order==1){
				nodes[start]->dominateNodes.push_back(start);
				nodes[start]->dominateNode=start;
			}else if(order==0){
				nodes[end]->isOut=true;
			}
			double length=Util2D::EuclideanDistance(nodes[start]->x,nodes[start]->y,nodes[end]->x,nodes[end]->y);
			edges.push_back(new Edge(count,start,end,length));
			edges.push_back(new Edge(count+1,end,start,length));
			nodes[start]->edges.push_back(count);
			nodes[end]->edges.push_back(count+1);
			count+=2;
		}
	}
	
	void print(){
		cout<<"graph info are shown as follows:"<<endl;
		cout<<"\tthere are "<<nodes.size()<<" nodes in the graph"<<endl;
		cout<<"\tthere are "<<edges.size()<<" edges in the graph"<<endl;
	}
	
	pair<int,double> SP(int start,const vector<int> &ends){
		pair<int,double> result=make_pair(-1,MAX_DOUBLE);
		int nSize=nodes.size();
		vector<bool> isEnd(nSize,false);
		int endSize=ends.size();
		for(int i=0;i<endSize;i++){
			isEnd[ends[i]]=true;
		}
		vector<double> currentLen(nSize,MAX_DOUBLE);
		priority_queue<pair<int,double>/**/,vector<pair<int,double>/**/>/**/,Compare> mqueue;
		currentLen[start]=0.0;
		mqueue.push(make_pair(start,0));
		while(!mqueue.empty()){
			pair<int,double> top=mqueue.top();
			mqueue.pop();
			if(isEnd[top.first]&&top.second<result.second){
				result=top;
			}
			Node *tNode=nodes[top.first];
			int eSize=tNode->edges.size();
			for(int i=0;i<eSize;i++){
				Edge *tEdge=edges[tNode->edges[i]];
				int tend=tEdge->end;
				if(currentLen[tend]>top.second+tEdge->length){
					currentLen[tend]=top.second+tEdge->length;
					mqueue.push(make_pair(tend,top.second+tEdge->length));
				}
			}
		}
		return result;
	}

	double SP(int start,int end){
		double result=MAX_DOUBLE;
		int nSize=nodes.size();
		vector<double> currentLen(nSize,MAX_DOUBLE);
		queue<pair<int,double>/**/> mqueue;
		currentLen[start]=0.0;
		mqueue.push(make_pair(start,0));
		while(!mqueue.empty()){
			pair<int,double> top=mqueue.front();
			mqueue.pop();
			if(top.first==end&&top.second<result){
				result=top.second;
			}
			Node *tNode=nodes[top.first];
			int eSize=tNode->edges.size();
			for(int i=0;i<eSize;i++){
				Edge *tEdge=edges[tNode->edges[i]];
				int tend=tEdge->end;
				if(currentLen[tend]>top.second+tEdge->length){
					currentLen[tend]=top.second+tEdge->length;
					mqueue.push(make_pair(tend,top.second+tEdge->length));
				}
			}
		}
		return result;
	}

	int prcessStartAndEnds(vector<int> &ends){
		int start;
		int nSize=nodes.size();
		long aa=(long)rand();
		start=aa%(nSize-1)+1;

		vector<int> snodes;
		for(int i=0;i<nSize;i++){
			int tSize=nodes[i]->dominateNodes.size();
			if(0==tSize){
				continue;
			}
			snodes.push_back(i);
		}
		if(0==snodes.size()){
			vector<int> tnodes;
			for(int i=1;i<nSize;i++){
				tnodes.push_back(i);
			}
			for(int i=0;i<AIM_size;i++){
				int tSize=tnodes.size();
				long a=(long)rand();
				int b=a%tSize;
				ends.push_back(tnodes[b]);
				tnodes.erase(tnodes.begin()+b);
			}
			return start;
		}
		vector<int> canNodes;
		for(int i=0;i<AIM_size;i++){
			int t=snodes.size();
			long a=(long)rand();
			int b=a%t;
			canNodes.push_back(snodes[b]);
			snodes.erase(snodes.begin()+b);
		}
		int cSize=canNodes.size();
		for(int i=0;i<cSize;i++){
			int t=nodes[canNodes[i]]->dominateNodes.size();
			long a=(long)rand();
			int b=a%t;
			ends.push_back(nodes[canNodes[i]]->dominateNodes[b]);
		}
		return start;
	}
	
	void processEPs(){
		int nSize=nodes.size();
		for(int i=0;i<EP_size;i++){
			double minDis=MAX_DOUBLE;
			int nodeID=-1;
			for(int j=1;j<nSize;j++){
				if(abs(nodes[j]->fingerprints[i]-fingerThreshold)<THRES){
					continue;
				}
				if(nodes[j]->fingerprints[i]<minDis){
					minDis=nodes[j]->fingerprints[i];
					nodeID=j;
				}
			}
#ifdef _DEBUG_
			cout<<minDis<<"\t";
#endif
			gEPs.push_back(new EP(i,nodeID));
		}
#ifdef _DEBUG_
		cout<<endl;
#endif
	}
	
	pair<int,double> SPPro(int start,const vector<vector<int>/*edges*/> &result){
		pair<int,double> fResult=make_pair(-1,MAX_DOUBLE);
		int rSize=result.size();
		for(int i=0;i<rSize;i++){
			double tResult=0;
			int tSize=result[i].size();
			
			double avgV=0;
			int count=0;
			vector<int> countNum(bucket_size,0);
			int bucketUnit=100/bucket_size;
			for(int j=0;j<tSize;j++){
				for(int k=0;k<EP_size;k++){
					
					if(abs(nodes[result[i][j]]->fingerprints[k]-fingerThreshold)<THRES){
						continue;
					}
					int tttt=nodes[result[i][j]]->fingerprints[k];
					
					countNum[tttt/bucketUnit]++;
				}
			}
			
			int maxaim=0;
			int aimaim;
			for(int j=0;j<bucket_size;j++){
				if(countNum[j]>maxaim){
					maxaim=countNum[j];
					aimaim=j;
				}
			}
			avgV=bucketUnit*aimaim+bucketUnit/2;
			
			
			for(int j=0;j<tSize-1;j++){
				
				double subV=MAX_DOUBLE;
				int pos;
				vector<int> tmpF;
				for(int k=0;k<EP_size;k++){
					if(abs(nodes[result[i][j]]->fingerprints[k]-fingerThreshold)<=THRES){
						continue;
					}
					tmpF.push_back(k);
				}
				
				for(int k=0;k<tmpF.size();k++){
					double ttt=abs(avgV-nodes[result[i][j]]->fingerprints[tmpF[k]]);
					if(ttt<subV){
						subV=ttt;
						pos=k;
					}
				}
				int result1=tmpF[pos];
				tmpF.erase(tmpF.begin()+pos);
				subV=MAX_DOUBLE;
				for(int k=0;k<tmpF.size();k++){
					double ttt=abs(avgV-nodes[result[i][j]]->fingerprints[tmpF[k]]);
					if(ttt<subV){
						subV=ttt;
						pos=k;
					}
				}
				int result2=tmpF[pos];
				
				double tmpp;

				double dis=Util2D::TriDistance(nodes[result[i][j]]->fingerprints[result1],nodes[result[i][j]]->fingerprints[result2],
					nodes[gEPs[result1]->mostNearestNode]->fingerprints[result2],nodes[gEPs[result2]->mostNearestNode]->fingerprints[result1],
					nodes[result[i][j+1]]->fingerprints[result1],nodes[result[i][j+1]]->fingerprints[result2]);

				if(result[i][j]<result[i][j+1]){
					if(maps.find(make_pair(result[i][j],result[i][j+1]))!=maps.end()){
						tmpp=default_distance_ratio*dis;
					}else{
						tmpp=dis;
					}
				}else{
					if(maps.find(make_pair(result[i][j+1],result[i][j]))!=maps.end()){
						tmpp=default_distance_ratio*dis;
					}else{
						tmpp=dis;
					}
				}
				tResult+=tmpp;
				
				//tResult+=Util2D::VecDistance(nodes[result[i][j]]->fingerprints,nodes[result[i][j+1]]->fingerprints);
			}
			if(tResult<fResult.second){
				fResult=make_pair(result[i][tSize-1],tResult);
			}
		}
		return fResult;
	}

	pair<int,double> SP(int start,const vector<vector<int>/*edges*/> &result){
		pair<int,double> fResult=make_pair(-1,MAX_DOUBLE);
		int rSize=result.size();
		for(int i=0;i<rSize;i++){
			double tResult=0;
			int tSize=result[i].size();
			for(int j=0;j<tSize-1;j++){
				tResult+=Util2D::EuclideanDistance(nodes[result[i][j]]->x,nodes[result[i][j]]->y,nodes[result[i][j+1]]->x,nodes[result[i][j+1]]->y);
			}
			
			if(tResult<fResult.second){
				fResult=make_pair(result[i][tSize-1],tResult);
			}
		}
		return fResult;
	}

	pair<int,double> L2(int start, vector<int> &ends){
		double minV=10000;
		int result=-1;
		for(int i=0;i<ends.size();i++){
			double tmp=Util2D::VecDistance(nodes[start]->fingerprints,nodes[ends[i]]->fingerprints);
			if(minV>tmp){
				minV=tmp;
				result=ends[i];
			}
		}
		return make_pair(result,minV);
	}
	
	void processPaths(int start,const vector<int> &ends,vector<vector<int>/*edges*/> &result){
		int nSize=nodes.size();
		vector<bool> isEnd(nSize,false);
		vector<bool> isDominated(nSize,false);
		int endSize=ends.size();
		for(int i=0;i<endSize;i++){
			//如果在一个房间则直接添加到结果
			if(nodes[start]->dominateNode!=-1&&nodes[start]->dominateNode==nodes[ends[i]]->dominateNode){
				vector<int> tmp;
				tmp.push_back(start);
				tmp.push_back(ends[i]);
				result.push_back(tmp);
			}else{
				isEnd[ends[i]]=true;
				if(nodes[ends[i]]->dominateNode!=-1){
					isDominated[nodes[ends[i]]->dominateNode]=true;
				}
			}
		}

		queue<PNode*> mqueue;
		mqueue.push(new PNode(NULL,start));
		while(!mqueue.empty()){
			PNode* top=mqueue.front();
			//top->print();
			//getchar();
			mqueue.pop();
			if(isEnd[top->id]){
				result.push_back(top->passedNodes);
				delete top;
				continue;
			}else if(nodes[top->id]->dominateNode!=-1&&isDominated[nodes[top->id]->dominateNode]){
				bool state=false;
				for(int u=0;u<endSize;u++){
					if(nodes[ends[u]]->dominateNode!=-1&&nodes[ends[u]]->dominateNode==nodes[top->id]->dominateNode){
						vector<int> tt=top->passedNodes;
						tt.push_back(ends[u]);
						result.push_back(tt);
						state=true;
					}
				}
				if(state){
					delete top;
					continue;
				}
			}
			Node *tmp=nodes[top->id];
			int nnSize=tmp->edges.size();
			for(int i=0;i<nnSize;i++){
				int t=edges[tmp->edges[i]]->end;
				
				if(!top->has(t)&&(nodes[t]->dominateNode==-1||nodes[t]->dominateNodes.size()!=0)){
					mqueue.push(new PNode(top,t));
				}
			}
			delete top;
		}
	}

	double avgLen(){
		double result=0;
		int eSize=edges.size();
		for(int i=0;i<eSize;i++){
			result+=edges[i]->length;
		}
		return result/eSize;
	}
};

Graphic *gGraphic=new Graphic();

#endif
