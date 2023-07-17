#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "ini.h"
#include "INIReader.h"
#include <fstream>
#include "inipp.h"
#include <typeinfo>
#include <iterator>
#include <cassert>
#include <sstream>
using namespace std;



class Settings
{
	public:
		string input_pipeline;
		vector<float> confidence;
		vector<vector<vector<float>>> anchors;



	int readIniFile()
	{	
		inipp::Ini<char> ini;
	
		ifstream is("test.ini");

		ini.parse(is);

		inipp::get_value(ini.sections[""], "input_pipeline", input_pipeline);
		inipp::get_value(ini.sections[""], "confidence", confidence);
		inipp::get_value(ini.sections[""], "anchors", anchors);
				
		input_pipeline = input_pipeline.substr(1, input_pipeline.length() - 1);

		return 0;
	}

	
	int setIniFile(string upd_input_pipeline, vector<float> upd_confidence, vector<vector<vector<float>>> upd_anchors)
	{
		inipp::Ini<char> ini;

		ifstream fin;
		ofstream fout;

		fin.exceptions(ifstream::badbit | ifstream::failbit);
		fout.exceptions(ofstream::badbit | ofstream::failbit);

		try
		{
			fin.open("test.ini");
			fout.open("test.ini.backup");
			string i;
			while (fin >> i)
			{
				fout << i;
		
			}
		}

		catch (const ifstream::failure& ex)
		{
			cout << ex.what() << endl;
		}

		fin.close();
		fout.close();

		return 0;
	}


};


int main()
{
	Settings a;
	a.readIniFile();


	//cout << "_________________________" << endl;
	cout << a.input_pipeline << endl;
	//copy(a.confidence.begin(), a.confidence.end(), std::ostream_iterator<float>(std::cout, " "));
	//cout << endl;
	cout << typeid(a.input_pipeline).name() << endl;
	//cout << typeid(a.anchors).name() << endl;
		


	return 0;
}
