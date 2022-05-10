//oeis A157026
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>   

#define MAX__UINT128 (__uint128_t)(-1)
#define MAX__UINT64 (__uint64_t)(-1)

typedef struct{ char buf[16]; } _128bit; //128-bit

using namespace std;

__uint64_t bigP;
vector<__uint128_t> a1v; //primes
vector<__uint128_t> a2v; //cubes : a2v[n]=n^3

//list of primes
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

int fmod(const int input, const int ceil) {
    // apply the modulo operator only when needed
    // (i.e. when the input is greater than the ceiling)
    return input >= ceil ? input % ceil : input;
    // NB: the assumption here is that the numbers are positive
}

static inline int isodd(int x) { return x & 1; }

//EOF kmath

//BOF read functions


string ui128tos(__uint128_t n){//128 uint to string
	string str = "";

	while(n!=0){
		str+=to_string( (__uint8_t)(n%10) );
		n/=10;
	}
	
	string inv = "";
	for( int i=str.size()-1;i>=0;i-- ){
		inv+=str[i];
	}

	return inv;
}

ifstream::pos_type filesize(string filename)
{
    ifstream in(filep, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

int cArrayP(__uint128_t n){//test vector divisors
	for(auto &P : a1v) //go through vector of primes
	{
		if( fmod(n,__uint128_t(P)) == 0 ){
			return 0;
		}else if( P>fsqrt128(n) ){
			return 1;
		}
	}
	return 3;
}

//cube root binary search vector
template <class T>
T binCube(T n)
{
	T r = 0;
	T l = a2v.size()-1;
	T m = (r+l)/2;
	while(r <= l)
	{
		T cp=a2v[m];
		if(cp<n)
			r = m+1;
		else if(cp==n)
		{
			return m;
		}else{
			l = m-1;
		}
		m = (r+l)/2;
	}
	
	return 0;
}

//EOF write functions

//brute logarithmic search 128-bit cube (slower than binary search)
template <class T>
T bruteCube(T n)
{
    T cube = 1;
	T s=0;
	//find s that is s^3<N 
	for(__int64_t i=ui128log10(n)-2; i>=0; i--){ //test increment 10^i , 10^(i-1) ... 10^2, 10^1
		T inc = ui128pow10(i);
		while(s*s*s<n){
			s+=inc;
		}
		s-=inc;
	}
	while(cube<n){ //1 increments
		s+=1;
		cube=s*s*s;
	}
	if(s*s*s!=n){
		 return 0;
	}
	return cube;
}

//13238717
//s=13238717+1 t=1
//Find primes form P^3=A^3+B^3+C^3 where P is prime and [ t < a,b,c = s ]
//pcube [thread] [thread count]
int main( int argc, char *argv[] ){

	//threads
	int tc=0; //thread count
	int cc=0; //current thread

	if( argv[1]!="" ){
		tc = stoi(argv[1]);
	}

	if( argv[2]!="" ){
		cc = stoi(argv[2]);
	}

	int tinc = tc; //thread increment
	int tsr = cc; //start offset
	int ten =-cc; //end offset

	//read and transfer prime file to str
	string str;
	ifstream filepr(filep, ios::in | ios::binary );
	filepr >> str;
	filepr.close();	
	
	stringstream ss(str);

	if( filesize(filep) > 4 ){ //if string stream is bigger than 4 bytes (2,3,)
		for (__uint64_t i; ss >> i;) { //Transfer file primes to a1v vector
			a1v.push_back(i);    
			if (ss.peek() == ',')
				ss.ignore();
		}
	}else{ //set two first primes if file is > 4B
		a1v.push_back(2);
		a1v.push_back(3);
	}

	//clear string
	ss.str("");

	__uint128_t s=20000+1; //check set [t,s[ 		//if t=0, total checked values, approx: s^2.5		//bigO x/9.5
	__uint128_t t=0;

	//pre-generate cubes
	for(__uint128_t i=0;i<s;i+=1){
		a2v.push_back(i*i*i);
	}

	bigP=a1v[a1v.size()-1]; //biggest prime

	cout << "size " << a2v.size() << " cubes \n";
	cout << "size " << a1v.size() << " bigP " << bigP << "\n";

	if(bigP<=fsqrt128(s)){
		cout << "Prime list may not be sufficient\n";
	}

	__uint128_t s3=s*s*s; //P^3
	
	__uint64_t found=0; 

	clock_t st=clock();
	
	for(__uint64_t a=t;1;a++){// A

		__uint128_t o=a2v[a];
		if(o>s3){break;}
		for(__uint64_t b=a+1;b<s;b++){// B

			__uint128_t m=a2v[b]; //get cube from vector
			__uint128_t mo=m+o; //A^3+B^3 //mo%9 = 0,1,2,7,8

			if(mo>s3){break;}
			for(__uint64_t //apply offsets per thread
				c=b+1	+tsr;
				c<s		+ten;
				c+=1	+tinc
			){// C
			
				if( !isodd(a+b+c) ){continue;} //Can not be even

				__uint128_t n=a2v[c];
				__uint128_t out = (mo+n); //A^3+B^3+C^3
				
				int mod9 = fmod(out,9);
				if(mod9!=1 && mod9!=8){continue;} //always true (P^3=A^3+B^3+C^3)%9 = 1,8

				__uint64_t iPC=binCube(out); //binary search cube

				if(iPC!=0){

					//check prime
					__uint64_t isP=cArrayP(iPC);

					if(
						isP>0
					){
						found++;

						cout 
							<< iPC
							<< "^3 = "
							<< ui128tos(out)
							<< " = "
							<< " a:" << a
							<< " b:" << b
							<< " c:" << c
							<< "\n"	
						;
					}
				}
			}
		}
	}

	cout << "took: " << int(clock()-st) << "\n";
	cout << "found: " << found << "\n";

	filepw.close();	
}