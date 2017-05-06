#include <fstream>
#include <string>
#include <iomanip>
#include <getopt.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; 

struct seqRef{
	string baseRef;
};

struct seqTest{
	string baseTest;
};

void input(string inFile, seqRef & a, seqRef & b, seqTest & c, seqTest & d);
/*
This function is to read reference alignment sequence and alignment sequence from
PSA programs from input file and transfer it to program's string variable
@parameter inFile: receive filename of input file
@parameter a: return alignment sequence of reference sequence in reference alignment sequence
@parameter b: return alignment sequence of simulated sequence in reference alignment sequence
@parameter c: return alignment sequence of reference sequence in PSA programs alignment sequence
@parameter d: return alignment sequence of simulated sequence in PSA programs alignment sequence 
*/

void calc(seqRef a, seqRef b, seqTest c, seqTest d, double &tp, double &fp, double &tn, double &fn, 
double &acc, double &sen, double &spec);
/*
This function is to calculate the accuracy, sensitivity and specificity of 
PSA programs alignment result in respect to reference alignment sequence
@parameter a: receive alignment sequence of reference sequence in reference alignment sequence
@parameter b: receive alignment sequence of simulated sequence in reference alignment sequence
@parameter c: receive alignment sequence of reference sequence in PSA programs alignment sequence
@parameter d: receive alignment sequence of simulated sequence in PSA programs alignment sequence
@parameter tp: return number of true positives
@parameter fp: return number of false positives
@parameter tn: return number of true negatives
@parameter fn: return number of false negatives
@parameter acc: return accuracy result
@parameter sen: return sensitivity result
@parameter spec: return specificity resut
*/
void print(string inFile, string outFile, double tp, double fp, double tn, double fn, double acc, 
double sen, double spec);
/*
This function is to print the result of accuracy, sensitivity and specificity of PSA programs
into output file
@parameter inFile: receive filename of input file
@parameter outFile: receive filename of output file
@parameter tp: receive number of true positives
@parameter fp: receive number of false positives
@parameter tn: receive number of true negatives
@parameter fn: receive number of false negatives
@parameter acc: receive accuracy result
@parameter sen: receive sensitivity result
@parameter spec: receive specificity resut
*/

int main(int argc, char * argv []) {
	
	int opt=0; 
	string inFile="", outFile="";
	seqRef a, b;
	seqTest c, d;
	double tp=0, tn=0, fp=0, fn=0;
	double acc=0, sen=0, spec=0;
	bool option=false;
	
cout<<"input file (.txt): ";
cin>>inFile;
cout<<"output file (.txt): ";
cin>>outFile;
	
	input(inFile, a, b, c, d);
	calc(a, b, c, d, tp, fp, tn, fn, acc, sen, spec);
	print(inFile, outFile, tp, fp, tn, fn, acc, sen, spec);

	return 0;
}

void input(string inFile, seqRef & a, seqRef & b, seqTest & c, seqTest & d){
	int secBase=0;
	string line="";
	ifstream in;
	in.open(inFile.c_str());
		while(getline(in, line)){  //transfer sequence from file into string variable
		if(line=="") secBase+=1; 
		else{
			if (secBase==0){
				a.baseRef+=line;
			}
			else if (secBase==1){
				b.baseRef+=line;
			}
			else if (secBase==2){
				c.baseTest+=line;
			}
			else{
				d.baseTest+=line;
			}	
		}
	}
	in.close();	
}

void calc(seqRef a, seqRef b, seqTest c, seqTest d, double &tp, double &fp, double &tn, double &fn, double &acc, double &sen, double &spec){
	int refAlign=0;
	int i=0, j=0;

	while(i<d.baseTest.length()){	//calculate tp, fp, tn and fn number
		if(b.baseRef[j]!='-'&&d.baseTest[i]!='-'){
			if(d.baseTest[i]==c.baseTest[i]){
				if(b.baseRef[j]==a.baseRef[j]) ++tp;
				else ++fp;
			}
			else{
				if(b.baseRef[j]!=a.baseRef[j])++tn;
				else ++fn;
			}
			++i;++j;					
			++refAlign;
		}
		else{
			if(b.baseRef[j]=='-')++j;
			if(d.baseTest[i]=='-')++i;
		}
	}
	acc=(tp+tn)/refAlign;	//calculate accuracy
	sen=tp/(tp+fn);			//calculate sensitivity
	spec=tn/(tn+fp);		//calculate specificity
}

void print(string inFile, string outFile, double tp, double fp, double tn, double fn, double acc, double sen, double spec){
	ofstream out;
	out.open(outFile.c_str());
	out<<"This is the performance file for alignment in "<<inFile<<endl<<endl;
	
	out<<"number of true positive: "<<fixed<<setprecision(0)<<tp<<endl;
	out<<"number of false positive: "<<fixed<<setprecision(0)<<fp<<endl;
	out<<"number of true negative: "<<fixed<<setprecision(0)<<tn<<endl;
	out<<"number of false negative: "<<fixed<<setprecision(0)<<fn<<endl<<endl;
	
	out<<"Accuracy: "<<fixed<<setprecision(2)<<acc<<endl;
	out<<"Sensitivity: "<<fixed<<setprecision(2)<<sen<<endl;
	out<<"Specificity: "<<fixed<<setprecision(2)<<spec<<endl<<endl;
	out.close();
}
