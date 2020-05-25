/* -------------------------------------------
Name: Junrui Zhu/Danh Nguyen
# ID: 1585761 / 1592873
# CMPUT275, Winter 2019
# Assignment2 part1: Server
# -------------------------------------------*/
#include "dijkstra.h"
#include "wdigraph.h"
#include "digraph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include "heap.h"
#include <unordered_set>
#include <list>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

bool no_path_flag = true;


//Used to store coordinate of vertex
struct Point
{
	long long lat;
	long long lon;
	
};

//Used to stored the closest point and its coordinate
struct Starp{
	int iden;
	long long latt;
	long long lonn;	
};

//return the manhattan distance
long long manhattan(const Point& pt1, const Point& pt2){
	long long mdistance = abs(pt1.lon-pt2.lon) + abs(pt1.lat-pt2.lat);
	return mdistance;
}

//return a Starp type data which contain the closest point
Starp closestpoint(unordered_map<int, Point>& verteces, Point& in) {
	long long min_dist = 10000000000;
	int tracker = 0;
	Starp output;
	//Find the min manhatance distance 
	for (auto x: verteces) {
		Point temp_coor = x.second;
		long long temp_dist = abs(temp_coor.lon-in.lon) + abs(temp_coor.lat-in.lat);
		if (temp_dist < min_dist) {
			min_dist = temp_dist;
			tracker = x.first;
		}
		if (min_dist == 0) {
			output.iden = x.first;
			output.latt = x.second.lat;
			output.lonn = x.second.lon;
			return output;
		}
	}
	output.iden = tracker;
	output.latt = verteces[tracker].lat;
	output.lonn = verteces[tracker].lon;
	return output;
}

//Read the file name and stored data of the file into graph and points
void readGraph(string filename, WDigraph& graph, unordered_map<int, Point>& points){
	//read the text
	ifstream myfile (filename);
	string line;
	while(getline(myfile,line)){
		//Determine the data type is vertex or Edges
		if(line.compare(0,1,"V")==0){
			Point coordinate;
			int secondcom = line.find(",",2);
			int thirdcom = line.find(",",secondcom+1);
			string identifier = line.substr(2,secondcom-2);
			string latitude = line.substr(secondcom+1,thirdcom-2);
			string lontitude = line.substr(thirdcom+1,11);
			
			//convert string to int
			stringstream geek(identifier);
			int idennum = 0;
			geek>>idennum;

			//convert string to double
			double doulat = stod(latitude);
			double doulon = stod(lontitude);
			coordinate.lat = static_cast<long long>(doulat*100000);
			coordinate.lon = static_cast<long long>(doulon*100000);
			points.insert({idennum,coordinate});
			graph.addVertex(idennum);
		}
		else if(line.compare(0,1,"E")==0){
			int secondcom = line.find(",",2);
			string newedgestart = line.substr(2,secondcom-2);
			int newedgestartnum = 0;
			int newedgeendnum = 0;
			if(true){
				stringstream geek(newedgestart);
				geek>>newedgestartnum;
			}
			//Two if-statement because "geek()" need to be refresh before we stored new value
			if(true){			
				int thirdcom = 	line.find(",",secondcom+1);
				string newedgeendv = line.substr(secondcom+1,thirdcom-2);
				stringstream geek(newedgeendv);
				geek>>newedgeendnum;
			}
			//store edges
			auto firstpoint = points.find(newedgestartnum);
			auto secondpoint = points.find(newedgeendnum);
			long long mycost =  manhattan(firstpoint->second,secondpoint->second);
			graph.addEdge(newedgestartnum,newedgeendnum,mycost);
		}
	}
}


int main() {
	while (no_path_flag) { // Initially set to true, but will ready for user input again if no path found.
		//initiaize all data struct 
		WDigraph mygraph;
	    unordered_map<int, PIL> searchTree;
	    unordered_map<int, Point> vertexpoint;
	    unordered_map<int, long long> distance;


	    readGraph("edmonton-roads-2.0.1.txt" ,mygraph, vertexpoint);

	    //Store two input coordinate
	    Point startP,endP;
	    char request;
	    cin>>request;
	    if(request == 'R'){
	    	cin>>startP.lat;
	    	cin>>startP.lon;
	    	cin>>endP.lat;
	    	cin>>endP.lon;   
	    } 
	    Starp closeststar = closestpoint(vertexpoint, startP);
	    Starp closestend = closestpoint(vertexpoint, endP);

	    //Calling dijkstra to find the closest path tree
	    dijkstra(mygraph,closeststar.iden,searchTree);
	    
	    // read off a path
	    list<int> path;
	    if (searchTree.find(closestend.iden) == searchTree.end()) {
	       // cout << "Vertex " << closestend.iden << " not reachable from " << closeststar.iden << "\n";
	    	cout<<"N"<<" "<<path.size()<<endl;
	    	no_path_flag = true;
	    }
	    else {
	       int stepping = closestend.iden;
	       while (stepping != closeststar.iden) {
	         path.push_front(stepping);

	         // crawl up the search tree one step
	         stepping = searchTree[stepping].first;
	       }
	          path.push_front(closeststar.iden);
	    }

	    //Process of communicating with client;
	    cout<<"N"<<" "<<path.size()<<endl;
	    while(path.size()>=0){
	    	char receive;
	    	cin>>receive;
	    	if(receive == 'A' && path.size()>0){
	    		int o = path.front();
	    		cout<<"W"<<" "<<vertexpoint[o].lat<<" "<<vertexpoint[o].lon<<"\n";
	    		path.pop_front();
	    	}
	    	else{
	    		cout<<"E"<<"\n";
	    		no_path_flag = false; // This to tewrminate the program
	    		break;
	    	}
	    }
	    return 0;
	}
}
