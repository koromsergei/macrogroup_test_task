#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

	void readIniFile()
	{	
		ifstream fin;
		try
		{
			fin.open("test.ini");
			string line;

			//while (getline(fin, line))
			//{
			
			getline(fin, input_pipeline, '\0');
			getline(fin, temp_con, '\0');
			getline(fin, temp_anc, '\0');
			//line = "";
				
			//}

				
				

		}

		
		catch (const ifstream::failure& ex)
		{
			cout << ex.what() << endl;
			cout << ex.code() << endl;
		}
		
		fin.close();
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
	cout << a.temp_con << endl;
	cout << a.temp_anc << endl;
	return 0;
}
