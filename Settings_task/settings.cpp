#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
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
	private:
		string input_pipeline;
		vector<float> confidence;
		vector<vector<vector<float>>> anchors;


		string temp_con;
		string temp_anc;
	
	public:
	int readIniFile()
	{	
		inipp::Ini<char> ini;
		vector<vector<float>> anchors_unwrapped;

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




		int first_index = 0;
		int last_index = 0;


		for (int i = 1; i < temp_anc.size(); ++i)
		{
			if (temp_anc[i] == '{')
			{
				
				if (temp_anc[i - 1] == '{')
				{
					
					first_index = i - 1;

				}
			}

			if (temp_anc[i] == '}')
			{
				
				if (temp_anc[i - 1] == '}')
				{
					
					last_index = i + 1;
					anchors.push_back(toVectortwice(temp_anc.substr(first_index, last_index - first_index)));
				}
			}


		}


		return 0;
	}


	vector<float> toVector(string vec_str)
	{	
		vector<float> temp_vec;
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
		int first_index = 0;
		int last_index = 0;

		for (int i = 0; i < vec_str.size(); ++i)
		{
			if (vec_str[i] == '{')
			{

				first_index = i;
			}

			if (vec_str[i] == '}')
			{

				last_index = i + 1;
				temp_vec.push_back(toVector(vec_str.substr(first_index, last_index - first_index)));
			}

		}

			return temp_vec;

		
	}

	
	int setIniFile(string upd_input_pipeline, vector<float> upd_confidence, vector<vector<vector<float>>> upd_anchors)
	{
				
		

		std::ostringstream oss;
		std::copy(upd_confidence.begin(), prev(upd_confidence.end()), std::ostream_iterator<float>(oss, ", "));
		if (!upd_confidence.empty()) {
			oss << upd_confidence.back();
		}
		string str_upd_confidence = oss.str();
		

		ifstream fin;
		ofstream fout;

		try
		{
			fin.open("test.ini");
			fout.open("test.ini.backup");


			string s;
			while (getline(fin, s))
			{
				fout << s << endl;
			}
		}

		catch (const ifstream::failure& ex)
		{
			cout << ex.what() << endl;
		}



		
		fin.close();
		fout.close();

		// update test.ini

		ofstream out("test.ini");

		if (out.is_open())
		{
			out << "input_pipeline=" << "\"" << upd_input_pipeline << "\"" << endl;
			out << "confidence="<< "{" << str_upd_confidence << "}" << endl;

			string second_anch;
			string third_anch;

			for (int i = 0; i < upd_anchors.size(); i++) {


				for (int j = 0; j < upd_anchors[i].size(); j++)
				{
					std::ostringstream oss;
					std::copy(upd_anchors[i][j].begin(), prev(upd_anchors[i][j].end()), std::ostream_iterator<float>(oss, ", "));

					if (!upd_anchors[i][j].empty()) {
						oss << upd_anchors[i][j].back();
					}
					second_anch.append("{");
					second_anch.append(oss.str());
					second_anch.append("}, ");

					
				}
				second_anch.pop_back();
				second_anch.pop_back();
				third_anch.append("{");
				third_anch.append(second_anch);
				third_anch.append("}, ");
				
				second_anch = "";
			
			}
			third_anch.pop_back();
			third_anch.pop_back();
			out << "anchors=" << "{" << third_anch << "}" << endl;
			third_anch = "";
			
		}
		out.close();
		

		

		return 0;
	}

};


int main()
{
	Settings a;
	a.readIniFile();
	a.setIniFile("test", {1.1, 1.3}, { {{1, 2}, {3, 4}, {5, 6}},{{7, 8}, {9, 10}, {11, 12}} });
	return 0;
}
