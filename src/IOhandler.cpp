/*
 * IOhandler.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: Kelly Patrick Stanton
 */

#include "IOhandler.h"
#include <fstream>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <sstream>
using namespace std;
string IOhandler::outputFolder="";
IOhandler::IOhandler() {
	// TODO Auto-generated constructor stub

}

IOhandler::~IOhandler() {
	// TODO Auto-generated destructor stub
}

void IOhandler::printDoubleArrayToFile(double* array, int length, const char* fileName ){
	if(IOhandler::outputFolder!=""){
		ofstream outputFile (string(outputFolder+fileName).c_str());
		copy(array, array+length, ostream_iterator<double>(outputFile , "\n"));
	}
}
vector<double> IOhandler::readDoubleArrayFromFile(const char* fileName ){
	vector<double> array;
	ifstream inFile (string(fileName).c_str());
	string line;
	int ii = 0;
	while (getline(inFile, line))
	{
		array.push_back(atof(line.c_str()));
		++ii;
	}
	inFile.close();
	return array;
}

void IOhandler::debugPeaks(long windowSize, const Peaks& peaks){
	ofstream outputFile (string(outputFolder+"PeakDebug.txt").c_str());
	int iter =  min(100,(int)peaks.data.size());
	for(int ii =0; ii <iter; ++ii){
		outputFile<<peaks.data[ii].chr<<'\t';
		outputFile<<peaks.data[ii].pos<<'\t';
		outputFile<<peaks.data[ii].lpValue<<'\t';
		outputFile<<peaks.data[ii].betaAlt<<'\t';
		outputFile<<peaks.data[ii].isArtifact<<'\t';
		for(int jj = 0; jj < 2*windowSize; ++jj){
			outputFile<<peaks.data[ii].pstrand[jj]<<'\t';
		}
		for(int jj = 0; jj < 2*windowSize; ++jj){
			outputFile<<peaks.data[ii].mstrand[jj]<<'\t';
		}
		outputFile<<peaks.data[ii].localPeakPos.size()<<'\t';
		for(int jj = 0; jj < (int)peaks.data[ii].localPeakPos.size(); ++jj){
			outputFile<<peaks.data[ii].localPeakPos[jj]<<'\t';
		}
		outputFile<<endl;
	}
	outputFile.close();
}
vector<Peak> IOhandler::readPeaks(long windowSize){
	vector<Peak> peaks;
	ifstream inFile (string(outputFolder+"PeakDebug.txt").c_str());
	Peak peak;
	string line;
	int ii = 0;
	while (getline(inFile, line))
	{
		stringstream ss(line);
		ss>>peak.chr;
		ss>>peak.pos;
		ss>>peak.lpValue;
		ss>>peak.betaAlt;
		ss>>peak.isArtifact;
		peak.pstrand = new double[2*windowSize];
		for(int jj = 0; jj < 2*windowSize; ++jj){
			ss>>peak.pstrand[jj];
		}
		peak.mstrand = new double[2*windowSize];
		for(int jj = 0; jj < 2*windowSize; ++jj){
			ss>>peak.mstrand[jj];
		}
		long numLocalPeaks;
		ss>>numLocalPeaks;
		for(int jj = 0; jj < numLocalPeaks; ++jj){
			long localPeakPos;
			ss>>localPeakPos;
			peak.localPeakPos.push_back(localPeakPos);
		}
		peaks.push_back(peak);
		++ii;
	}
	inFile.close();
	return peaks;
}
