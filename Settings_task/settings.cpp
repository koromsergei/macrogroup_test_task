#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
//#include "ini.h"
//#include "INIReader.h"
#include <fstream>
#include "inipp.h"
#include <typeinfo>
#include <iterator>
#include <cassert>
#include <stack>
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

		const char delim = '}},{';

		ifstream is("test.ini");

		ini.parse(is);

		inipp::get_value(ini.sections[""], "input_pipeline", input_pipeline);
		inipp::get_value(ini.sections[""], "confidence", temp_con);
		inipp::get_value(ini.sections[""], "anchors", temp_anc);
		
		//input_pipeline
		input_pipeline = input_pipeline.substr(1, input_pipeline.length() - 2);

		// confidence
		confidence = toVector(temp_con);

		//anchors
		temp_anc = temp_anc.substr(1, temp_anc.length() - 2);
		cout << temp_anc << endl;

		/*
				stringstream ss(temp_anc);
		string temp_anc_str;

		while (getline(ss, temp_anc_str, delim))
		{
			cout << temp_anc_str ;
			anchors.push_back(toVectortwice(temp_anc_str));
		}
		*/


		int first_index = 0;
		int last_index = 0;


		for (int i = 1; i < temp_anc.size(); ++i)
		{
			if (temp_anc[i] == '{')
			{
				
				if (temp_anc[i - 1] == '{')
				{
					
					first_index = i - 1;
					//cout << first_index << endl;
				}
			}

			if (temp_anc[i] == '}')
			{
				
				if (temp_anc[i - 1] == '}')
				{
					
					last_index = i + 1;
					//cout << last_index << endl;
					//anchors.push_back(toVectortwice(temp_anc.substr(first_index, last_index)));
					cout << temp_anc.substr(first_index, last_index) << endl;
				}
			}


		}

		vector<vector<float>> a = toVectortwice("{{1, 2}, {3, 4}, {5, 6}}");

		return 0;
	}


	vector<float> toVector(string vec_str)
	{	
		vector<float> temp_vec;
		cout << vec_str << endl;
		vec_str = vec_str.substr(1, vec_str.length() - 2);
		
		const char delim = ',';
		istringstream iss(vec_str);
		string temp_str;

		while (getline(iss, temp_str, delim))
		{
			temp_vec.push_back(stof(temp_str));
		}
		
		return temp_vec;
	}




	vector<vector<float>> toVectortwice(string vec_str)
	{
		vector<vector<float>> temp_vec;
		vec_str = vec_str.substr(1, vec_str.length() - 2);
		cout << vec_str << endl;
		const char delim = '}, {';
		
		istringstream iss(vec_str);
		string temp_str;
		while (getline(iss, temp_str, delim))
		{
			cout << temp_str << endl;
			temp_vec.push_back(toVector(temp_str));
			
		}

		int first_index = 0;
		int last_index = 0;



		
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

	cout << a.input_pipeline << endl;
	//copy(a.confidence.begin(), a.confidence.end(), ostream_iterator<float>(cout, ", "));
	cout <<  endl;


	return 0;
}
