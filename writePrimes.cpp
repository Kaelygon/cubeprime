
#include "functions.h"

int main( int argc, char *argv[] ){
//	frst();

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

	cout << "Stored primes " << a1v.size() << " bigP " << bigP << "\n";

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

	cout << a1v.size() << " Stored primes\n";
	filepw.close();	
}
