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
	int debug=1; //1=print some 2=print all
	
	if( argc>1 ){
		tc = stoi(argv[1]);
	}
	if( argc>2 ){
		cc = stoi(argv[2]);
	}
	if( argc>3 ){
		debug = stoi(argv[3]);
	}

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

	static const __uint128_t s=1000+1; //check set [t,s[ 		//if t=0, total checked values approx: s^3/3. Because if a>s/3 then a^3+b^3+c^3>s^3. All the possible combinations are done when a>s/3 
	static const __uint128_t t=0;

	//calculate C range offsets per thread
	static const int cend=s+-cc; //C end
	static const int cinc=1+tc; //C increment

	//pre-generate cubes
	for(__uint128_t i=0;i<s;i+=1){
		a2v.push_back(i*i*i);
	}

	bigP=a1v[a1v.size()-1]; //biggest prime

	if(debug>1){
		cout << "#size " << a2v.size() << " cubes \n";
		cout << "#size " << a1v.size() << " bigP " << bigP << "\n";

		if(bigP<=fsqrt128(s)){
			cout << "#Prime list may not be sufficient\n";
		}
	}

	static const __uint128_t s3=s*s*s; //s^3
	
	__uint64_t found=0; 

	clock_t st=clock();
	
	//init vars
	__uint128_t o,m,mo,out,n;
	__uint64_t a,b,c;
	int mod9,isP;

//	int counter=0;

	for(a=t;true;a++){// A

		o=a2v[a];
		if(o>s3){break;}
		for(__uint64_t b=a+1;b<s;b++){// B

			m=a2v[b]; //get cube from vector
			mo=m+o; //A^3+B^3 //mo%9 = 0,1,2,7,8

			if(mo>s3){break;}
			for( //apply offsets per thread
				c= b+1+cc	;
				c< cend		;
				c+=cinc
			){// C
			
				if( !isodd(a+b+c) ){continue;} //Can not be even

				n=a2v[c];
				out = (mo+n); //A^3+B^3+C^3
				
				mod9 = fastmod(out,9);
				if(mod9!=1 && mod9!=8){continue;} //always true (P^3=A^3+B^3+C^3)%9 = 1,8

				__uint64_t iPC=binCube(out); //binary search cube

				if(iPC!=0){

					isP=cArrayP(iPC); //check prime

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
if(debug>0){
	cout << "#took: " << int(clock()-st) << "\n";
	cout << "#found: " << found << "\n";
}
	filepw.close();
}