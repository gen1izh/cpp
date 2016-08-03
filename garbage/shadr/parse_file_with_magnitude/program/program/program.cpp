#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {

	if ( argc <= 1) {
		cout<<"Incorrect params!";
		return 0;
	}

	ifstream input_file(argv[1]);
	if (!input_file) {
		cout << "Cannot open file.\n";
		return 1;
	}

	vector<string> arr;
	string in_str;

	 while( getline( input_file, in_str ) ) {
		arr.push_back( in_str );
	 }

	input_file.close();

	vector<string>::iterator it;

	cout << " file dump " << endl;
	//for ( it = arr.begin(); it != arr.end(); ++it ) {
	//	cout << *it << endl;
	//}
	cout << " end file dump " << endl;

	cout << " start calculate square " << endl;

	const char* is_analyz_name; 


	//for ( it = arr.begin(); it != arr.end(); ++it ) {
	it = arr.begin();

		string str = *it;
		is_analyz_name = 0; 
		is_analyz_name =  find( &str[0], &str[3], '/' );
		if ( *is_analyz_name == '/' ) {
			cout << "Analyz name "<< str << endl;
			cout << "res "<< *is_analyz_name << endl;
		}
	//}

	return 0;
}

