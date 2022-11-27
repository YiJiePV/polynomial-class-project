/*
	This file will not be graded, the purpose of it is to
	do tests on your code as you go along.
*/

#include "polynomial.h"

#include <iostream>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

int main(int argc, char* argv[]){
	cout << "Running the Main Program" << endl;

    stringstream buffer1;
	buffer1.str(
		"3 -1 2 0 -2.5"
	);

	Polynomial p(3);
	p.Read(buffer1);
	cout << p.ToString() << endl;
	p.Write(cout);
	cout << endl;

	cout << endl << endl;
	cout << (-p).ToString() << endl;

    cout << endl << endl;
    stringstream buffer2;
    buffer2.str(
            "2 5 1 2"
    );

    Polynomial x(2);
    x.Read(buffer2);
    cout << x.ToString() << endl;
    x.Write(cout);
    cout << endl;
    cout << (p / x).ToString() << endl;


	return 0;
}
