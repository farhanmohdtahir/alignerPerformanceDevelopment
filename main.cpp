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
void calc(seqRef a, seqRef b, seqTest c, seqTest d, double &tp, double &fp, double &tn, double &fn, double &acc, double &sen, double &spec);
void print(string inFile, string outFile, double tp, double fp, double tn, double fn, double acc, double sen, double spec);
void help();


int main(int argc, char * argv []) {
	
	int opt=0; 
	string inFile="600a.txt", outFile="a.txt";
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
	string line="", z="", x="", v="", n="", line2="";
	ifstream in;
	in.open(inFile.c_str());
		while(getline(in, line)){
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

	while(i<c.baseTest.length()){
		if(a.baseRef[j]!='-'&&c.baseTest[i]!='-'){
			if(c.baseTest[i]==d.baseTest[i]){
				if(a.baseRef[j]==b.baseRef[j]) ++tp;
				else ++fp;
			}
			else{
				if(a.baseRef[j]!=b.baseRef[j])++tn;
				else ++fn;
			}
			++i;++j;					
			++refAlign;
		}
		else{
			if(a.baseRef[j]=='-')++j;
			if(c.baseTest[i]=='-')++i;
		}
	}
//		cout<<tp<<" "<<fp;
	acc=(tp+tn)/refAlign;
	sen=tp/(tp+fn);
	spec=tn/(tn+fp);	
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

//void help(){
//		cout<<"alignerReference"<<endl;
//	cout<<"Usage: ./ar -i inputFile -o outputFile"<<endl;
//	cout<<"-i [required argument] - name of input file (.txt)\n";
//	cout<<"-o [required argument] - name of output file (.txt)\n";
//	cout<<"Thank You\n";
//}

//    static struct option long_options[] = {
//        {"help",                       no_argument,       0,  'h' },
//        {"inputFile",              required_argument,     0,  'i' },
//        {"outputFile",             required_argument,     0,  'o' },                     
//        {0,                               0,              0,   0  }
//    };
//    
//    int long_index =0;
//    while ((opt = getopt_long_only(argc, argv,"", 
//                   long_options, &long_index )) != -1) {
//        switch (opt) {
//             case 'h' : help();option = true;
//                 break;
//             case 'i' : inFile = optarg;option = true;
//                 break;
//             case 'o' : outFile = optarg;option = true;
//                 break;                                                  
//             default: help(); 
//                 exit(EXIT_FAILURE);
//        }
//    }	
	
//  if (inFile!="" && outFile!="" ){
////}
//else{
//	help();
//}
