#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <bitset>
#include <cstring>

#include<iostream>
#include<fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#define MAX__UINT128 (__uint128_t)(-1)
#define MAX__UINT64 (__uint64_t)(-1)


using namespace std;

__uint64_t bigP;
__uint64_t bigPif; //biggest prime in file

vector<__uint128_t> a1v;
string filep="./data/primes.bin";
ofstream filepw(filep, ios::out | ios::binary | ios::app );

//BOF kmath

__uint128_t ui128pow( __uint128_t m, __uint128_t n) //128-bit pow
{
	__uint128_t o=m;

	while(n>1){
		n--;
		o*=m;
	}
	return o;
}

//table of 10s
__uint128_t tabp10[39]={ //10, 100 ... 10^39
	ui128pow(10,1),	ui128pow(10,2),	ui128pow(10,3),	ui128pow(10,4),	ui128pow(10,5),	ui128pow(10,6),	ui128pow(10,7),	ui128pow(10,8),	ui128pow(10,9),	ui128pow(10,10),	ui128pow(10,11),	ui128pow(10,12),	ui128pow(10,13),	ui128pow(10,14),	ui128pow(10,15),	ui128pow(10,16),	ui128pow(10,17),	ui128pow(10,18),	ui128pow(10,19),	ui128pow(10,20),	ui128pow(10,21),	ui128pow(10,22),	ui128pow(10,23),	ui128pow(10,24),	ui128pow(10,25),	ui128pow(10,26),	ui128pow(10,27),	ui128pow(10,28),	ui128pow(10,29),	ui128pow(10,30),	ui128pow(10,31),	ui128pow(10,32),	ui128pow(10,33),	ui128pow(10,34),	ui128pow(10,35),	ui128pow(10,36),	ui128pow(10,37),	ui128pow(10,38),	ui128pow(10,39)
};

//count digits
template <class T>
T ui128log10(T n)  
{  
    return 
		(n < tabp10[0] ? 0 :   
        (n < tabp10[1] ? 1 :   
        (n < tabp10[2] ? 2 :   
        (n < tabp10[3] ? 3 :   
        (n < tabp10[4] ? 4 :   
        (n < tabp10[5] ? 5 :   
        (n < tabp10[6] ? 6 :  
        (n < tabp10[7] ? 7 :  
        (n < tabp10[8] ? 8 :  
		(n < tabp10[9] ? 9 :   
        (n < tabp10[10] ? 10 :   
        (n < tabp10[11] ? 11 :   
        (n < tabp10[12] ? 12 :   
        (n < tabp10[13] ? 13 :   
        (n < tabp10[14] ? 14 :   
        (n < tabp10[15] ? 15 :  
        (n < tabp10[16] ? 16 :  
        (n < tabp10[17] ? 17 :  
		(n < tabp10[18] ? 18 :   
        (n < tabp10[19] ? 19 :   
        (n < tabp10[20] ? 20 :   
        (n < tabp10[21] ? 21 :   
        (n < tabp10[22] ? 22 :   
        (n < tabp10[23] ? 23 :   
        (n < tabp10[24] ? 24 :  
        (n < tabp10[25] ? 25 :  
        (n < tabp10[26] ? 26 :  
		(n < tabp10[27] ? 27 :   
        (n < tabp10[28] ? 28 :   
        (n < tabp10[29] ? 29 :   
        (n < tabp10[30] ? 30 :   
        (n < tabp10[31] ? 31 :   
        (n < tabp10[32] ? 32 :   
        (n < tabp10[33] ? 33 :  
        (n < tabp10[34] ? 34 :  
        (n < tabp10[35] ? 35 :  
		(n < tabp10[36] ? 36 :   
        (n < tabp10[37] ? 37 :
        	 tabp10[38]
		))))))))))))))))))))))))))))))))))))))
	;
}

template <class T>
T ui128pow10(T n) 
{
	return tabp10[n];
}


template <class T>
T fsqrt128(T N) //return floor(sqrt(N))
{ 
    T square = 1;
	T s=0;
	//find s that is s^3<N 
	for(__int64_t i=ui128log10(N)-2; i>=0; i--){ //test increment 10^i , 10^(i-1) ... 10^2, 10^1
		T inc = ui128pow10(i);
		while(s*s<N){
			s+=inc;
		}
		s-=inc;
	}
	while(square<N){ //1 increments
		s+=1;
		square=s*s;
	}
	if(s*s!=N){
		 s-=1;
	}
	return s;
	
}

int cArrayP(__uint64_t n){//test array divisors. 0==not prime, 1==prime, 2==in array, 3==bigger than bigP

	for(auto &P : a1v) //go through array of primes
	{
		if( n%__uint128_t( (P) ) == 0 ){
			if(n==P){
				return 2;
			}
			return 0;
		}

		if( P>fsqrt128(n) ){
			return 1;
		}
	}

	return 3;
}

//EOF kmath

//BOF write func

ifstream::pos_type filesize(string filename)
{
    ifstream in(filep, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}


void frst( string ffil="./data/primes.bin" ){ //file reset
	ofstream ffilrst(ffil, ios::out | ios::binary );
		ffilrst << "";
	ffilrst.close();
}

void writeP(__uint64_t n){
//	if( find(a1v.begin(), a1v.end(),n)==a1v.end() ){ //check if n is in array
		a1v.push_back(n); 
//		if(bigP<n){
			bigP=n;
//		}
//	}
}

string ui128tos(__uint128_t n){//128 uint to string
	string out = "";

	while(n!=0){
		out+=to_string( (__uint8_t)(n%10) );
		n/=10;
	}
	
	reverse(out.begin(), out.end());
	
	return out;
}

void wtofile(){
	for(auto &P : a1v) //go through array of primes
	{
		if(P<=bigPif){continue;} //skip if smaller than biggest prime in array

		string pstr = ui128tos(P);
		filepw << pstr; //write to file
		filepw << ',';
	}
}

//EOF write func


int main( int argc, char *argv[] ){
	frst();

	string str;
	ifstream filepr(filep, ios::in | ios::binary );
	filepr >> str;
	filepr.close();	
	
	stringstream ss(str);

	//assuming that the file includes all the primes smaller than last prime, sorted ascending
	if( filesize(filep) > 4 ){ //if string stream is bigger than 4 bytes (2,3,)
		for (int i; ss >> i;) {
			a1v.push_back(i);    
			if (ss.peek() == ',')
				ss.ignore();
		}

		bigP=a1v[a1v.size()-1];
		bigPif=bigP;
	}else{ //set two first primes if file is > 4B
		a1v.push_back(2);
		a1v.push_back(3);

		bigP=3;
		bigPif=0;
	}

	//clear
	ss.str("");

	cout << "size " << a1v.size() << " bigP " << bigP << "\n";

	int s=ceil(sqrt(13238717+1)); //check and write primes up to s, ceil sqrt(num)

	int si=bigP;
	if( si%2==0 ){ //make sure it's odd
		si-=1;
	}

	for(si;si<s;si+=2){ // bigP to s

		bool siisP =cArrayP(si);

		if(siisP==1){
			writeP(si);
		}

	}

	//find one more prime
	while(1){
		bool siisP =cArrayP(si);
		if(siisP==1){
			writeP(si);
			break;
		}
		si+=2;
	}


	wtofile();


	cout << "wrote " << a1v.size() << " primes\n";
	filepw.close();	
}
