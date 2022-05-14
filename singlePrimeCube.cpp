//oeis A157026
//
//g++ -std=c++11 ./singlePrimeCube.cpp -o singlePrimeCube
//
//Finds P for P^3=A^3+B^3+C^3 where P is prime and A,B,C are unique positive integers
//singlePrimeCube [thread] [thread count] [start] [P]
//

using namespace std;

#include "functions.h"

int main( int argc, char *argv[] ){

	//threads
	int tc=0; //thread count
	int cc=0; //current thread
	__uint64_t tstart=0; //start
	__uint64_t tend=8191; //end
	
	if( argc>1 ){
		tc = stoi(argv[1]);
	}
	if( argc>2 ){
		cc = stoi(argv[2]);
	}
	if( argc>3 ){
		tstart = stoi(argv[3]);
	}
	if( argc>4 ){
		tend = stoi(argv[4]);
	}

	static const __uint128_t nuse=tend; //finds nuse for nuse^3=A^3+B^3+C^3 	//check set [t,s] 	//time increases proportionately s^2 //compute time,  i7 7800x @ 4.5, s^2/37.5/[threads]/10^6 seconds
	static const __uint128_t s=nuse+1; 
	static const __uint128_t t=tstart;

	//calculate A range offsets per thread
	static const __uint64_t asrt=cc; //A start
	static const __uint32_t ainc=1+tc; //A increment

	static const __uint128_t s3=s*s*s; //s^3
	static const __uint128_t nuSe3=nuse*nuse*nuse; //(s+1)^3
	
	__uint64_t found=0; 
	
	//init vars
	__uint128_t a3,b3,c3,ab3,abc3;
	__uint64_t a,b,c,upb,cur;

	clock_t st=clock();

	for(a=asrt;true;a+=ainc){// A //apply offsets per thread

		a3=a*a*a;
		if(a3>nuSe3){break;}
		if( (a)%256==0 ){
			cout << "#a[" << cc << "]: " << a << "\n";
		}
		
		for( b=a+1; b<s; b++){// B

			b3=b*b*b;
			ab3=a3+b3;

			if(ab3>nuSe3){break;}
			//C
				c=b+1;

				c3=c*c*c;
				if((ab3+c3)>nuSe3){break;}
				
				//binary search c3
				upb = nuse-1;	//upper bound
				cur = (c+upb)/2;	//current estimate
				while(c <= upb)
				{
					c3=cur*cur*cur;
					abc3=ab3+c3;
					if(abc3<nuSe3)
						c = cur+1;
					else if(abc3==nuSe3)
					{
						break;
					}else{
						upb = cur-1;
					}
					cur = (c+upb)/2;
				}

				if(abc3!=nuSe3){continue;}

				found++;
				cout 
					<< ui128tos(nuse)
					<< "^3 = "
					<< ui128tos(nuSe3)
					<< " = "
					<< " a:" << a
					<< " b:" << b
					<< " c:" << c
					<< "\n"	
				;							
			//EOF C
		}
	}
	
	cout << "#took: " << int(clock()-st) << "\n";
	cout << "#found: " << found << "\n";

	filepw.close();
}

