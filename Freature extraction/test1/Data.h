#pragma once

#include <iostream>
#include <smfe\3d4dvec.h>
#include <smfe\config_global.h>
#include <string>
#include <boost\property_tree\xml_parser.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\foreach.hpp>//maybe not be used below
#include <vector>
#include <boost\typeof\typeof.hpp>
#include <smfe/feature/wavelet_features.h>
#include <smfe/feature/integral_calculus.h>
#include <smfe/feature/frequency_domain_features.h>
#include <smfe/feature/time_domain_features.h>
#include <smfe\feature\sensor_features.h>
#include <smfe\config_global.h>
#include <fstream>
#include "tinystr.h"
#include "tinyxml.h"
#include <math.h>
using namespace std;
using namespace smfe;




typedef struct Accelerator{
	vector<double> x;
	vector<double> y;
	vector<double> z;
}A;

typedef struct Rotate_Vector{
	vector<double> x;
	vector<double> y;
	vector<double> w;
	vector<double> z;
}RV;


typedef struct gyro{
	vector<double> x;
	vector<double> y;
	vector<double> z;
}G;

typedef struct magnetic{
	vector<double> x;
	vector<double> y;
	vector<double> z;
}M;

typedef struct gsm{
	vector<double> id;
	vector<double> dsm;
}GSM;

class Data
{
private:

	boost::property_tree::ptree pt;

	TiXmlDocument doc;


    void set_Tinyxml(const char* xml_path);
	void set_all_parameters();

	void set_Rovate_Vector(boost::property_tree::basic_ptree<string,string,less<string>> &j);
	void set_GSM_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j);
	void set_Magnetic_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j);
	void set_Gyro_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j);
	void set_Accelerator_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j);
	void features_extraction_into_vector(vector<double>& output,vector<double> input);
	template<class T>
	void features_extraction_into_vector(vector<double>& output, T &sensor,int i,int frames);
	template<class T>
	void features_extraction_into_vector(vector<double>& output, T &sensor, int i, int frames , int j);
	template<class T>
	void features_extraction_into_vector_range(vector<double>& output, T &sensor, int begin, int end);

	void features_extraction_into_vector_range(vector<double>& output, GSM &sensor, int begin, int end)
	{

		calculate_my_own(output, make_sub_range(sensor.dsm, begin, end));
		calculate_my_own(output, make_sub_range(sensor.id, begin, end));
	};


	void features_extraction_into_vecor(vector<double>& output, GSM &sensor,int i, int frames);
	void features_extraction_into_vecor(vector<double>& output, GSM &sensor, int i, int frames,int j);
	void calculate_using_smfe(vector<double> &output, vec &input);
	void calculate_my_own(vector<double> &output, vec &input);
	void convert_to_Eulerian_angle(bool reprojectAxis);

	void convert_to_world_axis();

	void output_range_windows_features(double winsize, double rate,double begin, double end, int fz, vector<vector<double>> &output);

	void calculate_range_features(int beginframe, int endframe,vector<double> &output);
	void output_windows_features(int min, double winsize, double rate, int fz, vector<vector<double>> &output, vector<pair<double, double>> &action);
    void calculate_range_features_normal(int beginframe, int endframe, vector<double> &output);

public:


	
	GSM gsm;
	M m;
	RV rv;
	G g;
	A a;
	int FZ = 100;
	double Winsize = 1;
	vector<string> label;
	vector<double> time;
	vector<pair<double, double>> turnleft;
	vector<pair<double, double>> turn;
	vector<pair<double, double>> acc;
	


public:
	Data(const char *xml_path);
	~Data();

	void Printf_RV()
	{
		for (auto i = rv.w.begin(); i != rv.w.end(); i++)
		{
			cout << *i<<endl;
		}
	}

	void output_5min_features(const string filename,int min,int fz);
	void output_window(const string filename, int fz, double windowsize,double rate);
	void output_5second_features(const string filename,int min,int fz);

	void Printf_label()
	{
		for (int i = 0; i < time.size(); i++)
		{
			cout << time[i] << " " << label[i]<<endl;
		}
	}


	

	void select_turn();
	void select_Acc();


	void output_driver_detection_turn_features(const string filename,double rate,double windowsize);
	void output_driver_detection_acc_features(const string filename, double rate,double windowsize);

	

};

