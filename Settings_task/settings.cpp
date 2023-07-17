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

		string temp_con;
		string temp_anc;

	int readIniFile()
	{	
		inipp::Ini<char> ini;
		vector<vector<float>> anchors_unwrapped;



		const char delim = '},{';

		ifstream is("test.ini");

		ini.parse(is);

		inipp::get_value(ini.sections[""], "input_pipeline", input_pipeline);
		inipp::get_value(ini.sections[""], "confidence", temp_con);
		inipp::get_value(ini.sections[""], "anchors", temp_anc);
		

		
		// input_pipeline
		input_pipeline = input_pipeline.substr(1, input_pipeline.length() - 1);


		// confidence
		confidence = toVector(temp_con);

		//anchors
		stringstream ss(temp_anc);
		string temp_anc_str;

		while (getline(ss, temp_anc_str, delim))
		{
			cout << temp_anc_str << endl;
			//anchors.push_back(toVectortwice(temp_anc_str));
		}
		return 0;
	}


	vector<float> toVector(string vec_str)
	{	
		vector<float> temp_vec;
		vec_str = vec_str.substr(1, vec_str.length() - 1);

		istringstream iss(vec_str);
		string buf;

		while (iss >> buf)
			temp_vec.push_back(atof(buf.c_str()));
		
		/*
				stringstream ss(vec_str);
		string temp_anc_str;
		const char delim = ', ';

		while (getline(ss, temp_anc_str, delim))
		{
			temp_vec2.push_back(stof(temp_anc_str));
		}

		*/
		
		return temp_vec;

	}


	vector<vector<float>> toVectortwice(string vec_str)
	{
		vector<vector<float>> temp_vec;

		temp_vec.push_back(toVector(vec_str));
		
		/*
				for (const std::vector<float>& v : temp_vec)
		{
			for (float x : v) std::cout << x << ' ';
			std::cout << std::endl;
		}
		
		*/

		return temp_vec;
	
	}


	
	void setIniFile()
	{
		/*добавить проверку на существование файлов*/
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

		catch (const ifstream::failure & ex)
		{
			cout << ex.what() << endl;
		}
		
		fin.close();
		fout.close();
		

	}


};


int main()
{
	Settings a;
	a.readIniFile();


	cout << "_________________________" << endl;
	cout << a.input_pipeline << endl;
	copy(a.confidence.begin(), a.confidence.end(), std::ostream_iterator<float>(std::cout, " "));
	cout << endl;
	cout << typeid(a.input_pipeline).name() << endl;
	cout << typeid(a.anchors).name() << endl;
	


	return 0;
}
