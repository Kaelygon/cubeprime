//oeis A157026

#include "functions.h"

//13238717
//s=13238717+1 t=1
//Find primes form P^3=A^3+B^3+C^3 where P is prime and [ t < a,b,c = s ]
//pcube [thread] [thread count]
int main( int argc, char *argv[] ){

	//threads
	int tc=0; //thread count
	int cc=0; //current thread
	int tstart=0; //start
	
	if( argc>1 ){
		tc = stoi(argv[1]);
	}
	if( argc>2 ){
		cc = stoi(argv[2]);
	}
	if( argc>3 ){
		tstart = stoi(argv[3]);
	}

	static const __uint128_t nuse = 13238717; //finds nuse for nuse^3=A^3+B^3+C^3
	static const __uint128_t s=nuse+1; //check set [t,s[ 		//time increases proportionately s^2 //compute time,  i7 7800x @ 4.5, s^2/37.5/[threads]/10^6 seconds
	static const __uint128_t t=tstart;

	//calculate C range offsets per thread
	static const int bend=s-cc; //B end
	static const int binc=1+tc; //B increment

	//pre-generate cubes
	for(__uint128_t i=0;i<s+1;i+=1){
		a2v.push_back(i*i*i);
	}

	static const __uint128_t s3=s*s*s; //s^3
	static const __uint128_t nuSe3=nuse*nuse*nuse; //s^3
	
	__uint64_t found=0; 
	
	//init vars
	__uint128_t a3,b3,c3,ab3,abc3;
	__uint64_t a,b,c,upb,cur;

	clock_t st=clock();

	for(a=t;true;a++){// A

		a3=a2v[a];
		if(a3>nuSe3){break;}
		if( !(a&111) ){
			cout << "#a[" << cc << "]: " << a << "\n";
		}
		for(
			b= a+1+cc	; //apply offsets per thread
			b< bend		;
			b+=binc
		){// B

			b3=a2v[b]; //get cube from vector
			ab3=a3+b3;

			if(ab3>nuSe3){break;}
			//C
				c=b+1;

				c3=a2v[c];
				if((ab3+c3)>nuSe3){break;}
				
				
				//binary search c3
				upb = a2v.size()-1;	//upper bound
				cur = (c+upb)/2;	//current estimate
				while(c <= upb)
				{
					c3=a2v[cur];
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

