#include "Data.h"
#include <math.h>
Data::Data(const char *xml_path)
{
	set_Tinyxml(xml_path);
	set_all_parameters();
	convert_to_world_axis();
	convert_to_Eulerian_angle(false);
}


Data::~Data()
{
}

void Data::set_all_parameters()
{
	/*
	boost::property_tree::ptree child = pt.get_child("session.threads.thread.channels");
	for (auto i = child.begin(); i != child.end(); ++i)
	{
		auto j = i->second.get_child("frames");
		auto name = i->second.get_child("name");
		if (name.get_value<string>() == "r")
		{
			set_Rovate_Vector(j);
		}
		else if (name.get_value<string>() == "a")
		{
			set_Accelerator_Vector(j);
		}
		else if (name.get_value<string>() == "bsss")
		{
			set_GSM_Vector(j);
		}
		else if (name.get_value<string>() == "g")
		{
			set_Gyro_Vector(j);
		}
		else if (name.get_value<string>() == "m")
		{
			set_Magnetic_Vector(j);
		}

		
		for (auto k = j.begin(); k != j.end(); ++k)
		{
			auto t = k->second.get_child("value.w");
		}
		
	}
   */
	double val;
	int count;
	doc.FirstChildElement("CaptureSession")->FirstChildElement("Nodes")->FirstChildElement("Node")->QueryIntAttribute("frames", &count);
	TiXmlElement* dataElement = doc.FirstChildElement("CaptureSession")->FirstChildElement("Nodes")->FirstChildElement("Node")->FirstChildElement("Data");
	for (int i = 0; i < count; i++)
	{
	  dataElement->QueryDoubleAttribute("Ax", &val);
	  a.x.push_back(val);
	  dataElement->QueryDoubleAttribute("Ay", &val);
	  a.y.push_back(val);
	  dataElement->QueryDoubleAttribute("Az", &val);
	  a.z.push_back(val);
	  dataElement->QueryDoubleAttribute("Gx", &val);
	  g.x.push_back(val);
	  dataElement->QueryDoubleAttribute("Gy", &val);
	  g.y.push_back(val);
	  dataElement->QueryDoubleAttribute("Gz", &val);
	  g.z.push_back(val);
	  dataElement->QueryDoubleAttribute("Mx", &val);
	  m.x.push_back(val);
	  dataElement->QueryDoubleAttribute("My", &val);
	  m.y.push_back(val);
	  dataElement->QueryDoubleAttribute("Mz", &val);
	  m.z.push_back(val);
	  dataElement->QueryDoubleAttribute("Rx", &val);
	  rv.x.push_back(val);
	  dataElement->QueryDoubleAttribute("Ry", &val);
	  rv.y.push_back(val);
	  dataElement->QueryDoubleAttribute("Rz", &val);
	  rv.z.push_back(val);
	  dataElement->QueryDoubleAttribute("Rw", &val);
	  rv.w.push_back(val);
	  dataElement->QueryDoubleAttribute("kBSSSy", &val);
	  gsm.dsm.push_back(val);
	  dataElement->QueryDoubleAttribute("kBSSSx", &val);
	  gsm.id.push_back(val);
	  dataElement = dataElement->NextSiblingElement();
	}

	//convert_to_Eulerian_angle(false);
	//cout << "set all parameters success" << endl;
}

void Data::set_Tinyxml(const char *xml_path)
{
	//boost::property_tree::xml_parser::read_xml(xml_path, pt);
	doc.LoadFile(xml_path);
	//cout << "read success" << endl;
}

void Data::set_Rovate_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j)
{
	for (auto k = j.begin(); k != j.end(); k++)
	{

		auto t = k->second.get_child("value.w");
		rv.w.push_back(t.get_value < double>());

		t = k->second.get_child("value.x");
		rv.x.push_back(t.get_value<double>());

		t = k->second.get_child("value.y");
		rv.y.push_back(t.get_value<double>());

		t = k->second.get_child("value.z");
		rv.z.push_back(t.get_value<double>());

	}

}

void Data::set_GSM_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j)
{
	for (auto k = j.begin(); k != j.end(); k++)
	{

	
		auto t = k->second.get_child("value.x");
		gsm.id.push_back(t.get_value<double>());

		t = k->second.get_child("value.y");
		gsm.dsm.push_back(t.get_value<double>());


	}
}

void Data::set_Magnetic_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j)
{
	for (auto k = j.begin(); k != j.end(); k++)
	{
		auto t = k->second.get_child("value.x");
		m.x.push_back(t.get_value<double>());

		t = k->second.get_child("value.y");
		m.y.push_back(t.get_value<double>());

		t = k->second.get_child("value.z");
		m.z.push_back(t.get_value<double>());
	}
}

void Data::set_Gyro_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j)
	{
		for (auto k = j.begin(); k != j.end(); k++)
		{

			

			auto t = k->second.get_child("value.x");
			g.x.push_back(t.get_value<double>());

			t = k->second.get_child("value.y");
			g.y.push_back(t.get_value<double>());

			t = k->second.get_child("value.z");
			g.z.push_back(t.get_value<double>());

		}
	}

void Data::set_Accelerator_Vector(boost::property_tree::basic_ptree<string, string, less<string>> &j)
	{
		for (auto k = j.begin(); k != j.end(); k++)
		{
			auto t = k->second.get_child("value.x");
			a.x.push_back(t.get_value<double>());

			t = k->second.get_child("value.y");
			a.y.push_back(t.get_value<double>());

			t = k->second.get_child("value.z");
			a.z.push_back(t.get_value<double>());
		}
	}

template<class T>
void Data::features_extraction_into_vector(vector<double>& output, T &sensor,int i, int frames)
{
	calculate_using_smfe(output, make_sub_range(sensor.x, i * frames, (i + 1) * frames));
	calculate_using_smfe(output, make_sub_range(sensor.y, i * frames, (i + 1) * frames));
	calculate_using_smfe(output, make_sub_range(sensor.z, i * frames, (i + 1) * frames));
}

template<class T>
void Data::features_extraction_into_vector(vector<double>& output, T &sensor, int i, int frames,int j)
{
	calculate_using_smfe(output, make_sub_range(sensor.x, i * frames + j * 150, i * frames + (j + 1) * 150));
	calculate_using_smfe(output, make_sub_range(sensor.y, i * frames + j * 150, i * frames + (j + 1) * 150));
	calculate_using_smfe(output, make_sub_range(sensor.z, i * frames + j * 150, i * frames + (j + 1) * 150));
}

template<class T>
void Data::features_extraction_into_vector_range(vector<double>& output, T &sensor, int begin, int end)
{
	calculate_using_smfe(output, make_sub_range(sensor.x, begin, end));
	calculate_using_smfe(output, make_sub_range(sensor.y, begin, end));
	calculate_using_smfe(output, make_sub_range(sensor.z, begin, end));
}

template<>
void Data::features_extraction_into_vector(vector<double>& output, GSM &sensor, int i,int frames)
{
	calculate_my_own(output, make_sub_range(sensor.dsm, i * frames, (i + 1) * frames));
	calculate_my_own(output, make_sub_range(sensor.id, i * frames, (i + 1) * frames));
}

template<>
void Data::features_extraction_into_vector(vector<double>& output, GSM &sensor, int i, int frames,int j)
{
	calculate_my_own(output, make_sub_range(sensor.dsm, i * frames + j * 150, i * frames+(j + 1) * 150));
	calculate_my_own(output, make_sub_range(sensor.id, i * frames + j * 150, i* frames + (j + 1) * 150));
}

void Data::calculate_using_smfe(vector<double> &output, vec &input)
{

	//cout << "begin caluculate" << endl;
	output.push_back(skewness(input));
	output.push_back(kurtosis(input));
	output.push_back(quartile_deviation(input));
	output.push_back(mean_absolute_deviation(input));
	output.push_back(sma(input));
	output.push_back(energy(input));
	//output.push_back(entropy();
	output.push_back(power(input));
	output.push_back(norm(input));
	output.push_back(rms(input));
	output.push_back(var(input));
	output.push_back(stddev(input));
	output.push_back(max(input));
	output.push_back(min(input));
	output.push_back(mean(input));
	output.push_back(median(input));
	output.push_back(first_quater(input));
	output.push_back(third_quater(input));
	output.push_back(abs(min(input)));
	output.push_back(abs(max(input)));
	output.push_back(abs(mean(input)));
	output.push_back(abs(median(input)));
	fm_vec tmpinput = sorted_frequency_magnitude_vec(input, 30);
	output.push_back(principal_frequency(tmpinput));
	output.push_back(median_frequency(tmpinput));
	output.push_back(first_quater_frequency(tmpinput));
	output.push_back(third_quater_frequency(tmpinput));
	output.push_back(frequency_energy(tmpinput));
	//output.push_back(frequency_domain_entropy(tmpinput));
	//cout << "calculate 1 channel success" << endl;
	//velocity(a.x);
	

}

void Data::calculate_my_own(vector<double> &output, vec &input)
{
	int num_of_id = 1;
	auto k = *input.begin();
	for (auto i = input.begin(); i != input.end(); i++)
	{
		if (k != *i)
		{
			k = *i;
			num_of_id++;
		}
	}
	output.push_back(num_of_id);
	//cout << "id" << num_of_id << endl;
}

void Data::output_5min_features(const string filename, int min,int fz){
	ofstream fout;
	
	vector<double> all;
    
	int length = a.x.size();
	for (int i = 0; i < length / 9000; i++)
	{
		stringstream ss;
		string s;
		ss << i;
		ss >> s;

		fout.open(filename+s+".txt");
		features_extraction_into_vector(all, a, i,9000);
		features_extraction_into_vector(all, g, i,9000);
		features_extraction_into_vector(all, m, i,9000);
		//features_extraction_into_vector(all, rv, i,9000);
		features_extraction_into_vector(all, gsm, i,9000);

		for (auto i = all.begin(); i != all.end(); i++)
		{
			fout << *i << " ";
		}
		all.clear();
		fout.close();
		//cout << filename + s + ".txt" << " success" << endl;
	}
}

void Data::output_window(const string filename, int fz, double windowsize,double rate)
{
	FZ = fz;
	Winsize = windowsize;
	ofstream fout;
	
	int length = a.x.size();
	for (int i = 0; i < length / (FZ * 60 * 5); i++)
	{
		vector<vector<double>> all;
		stringstream ss;
		string s;
		ss << i;
		ss >> s;
		int beginframe = i*FZ * 60 * 5;
		int endframe = (i + 1)*FZ * 60 * 5;
		vector<double> result;
		fout.open(filename + s + ".txt");
		while ((beginframe + Winsize*fz) <= endframe)
		{
			calculate_range_features_normal(beginframe, beginframe + Winsize*fz, result);
			beginframe = beginframe + Winsize*fz*(1 - rate);
			all.push_back(result);
			result.clear();
		}

		for (auto ii = all.begin(); ii < all.end(); ii++)
		{
			for (auto j = ii->begin(); j < ii->end(); j++)
			{
				fout << *j << " ";
			}
			fout << endl;
		}
		fout.close();
	}
	


}

void Data::output_5second_features(const string filename, int min,int fz)
{
	ofstream fout;
	vector<double> all;
	int length = a.x.size();
	
	for (int i = 0; i < length/9000;i++)
	{
		stringstream ss;
		string s;
		ss << i;
		ss >> s;

		fout.open(filename + s +"5s" + ".txt");
		for (int j = 0; j < 9000/150; j++)
		{
			features_extraction_into_vector(all, a, i, 9000, j);
			features_extraction_into_vector(all, g, i, 9000, j);
			features_extraction_into_vector(all, m, i, 9000, j);
			//features_extraction_into_vector(all, rv, i, 9000, j);
			features_extraction_into_vector(all, gsm, i, 9000, j);
			for (auto i = all.begin(); i != all.end(); i++)
			{
				fout << *i << " ";
			}
		fout << endl;
		all.clear();
		}

		fout.close();
		//cout << filename + s + ".txt" << " success" << endl;
		

	}
	



}

void Data::output_driver_detection_turn_features(const string filename,double rate,double windowsize)
{
	Winsize = windowsize;
	select_turn();
	ofstream fout;
	int length = a.x.size();
	vector<vector<double>> output;
	for (int i = 0; i < length / (FZ * 5 * 60); i++)
	{

		stringstream ss;
		string s;
		ss << i;
		ss >> s;
		fout.open(filename +"turnfeature" + s + ".txt");



		output_windows_features(i, Winsize, rate, FZ, output, turn);
		for (auto i = output.begin(); i < output.end(); i++)
		{
			for (auto j = i->begin(); j < i->end(); j++)
			{
				fout << *j << " ";
			}
			fout << endl;
		}
		fout.close();
	}

}
void Data::output_driver_detection_acc_features(const string filename, double rate,double windowsize)
{
	Winsize = windowsize;
	select_Acc();
	ofstream fout;
	int length = a.x.size();
	vector<vector<double>> output;
	for (int i = 0; i < length / (FZ * 5 * 60); i++)
	{

		stringstream ss;
		string s;
		ss << i;
		ss >> s;
		fout.open(filename + "accfeature" + s + ".txt");

		output_windows_features(i, Winsize, rate, FZ, output, acc);
		for (auto i = output.begin(); i < output.end(); i++)
		{
			for (auto j = i->begin(); j < i->end(); j++)
			{
				fout << *j << " ";
			}
			fout << endl;
		}
		fout.close();
	}

}
void Data::convert_to_Eulerian_angle(bool reprojectAxis)
{
	vec q;

	for (auto w = rv.w.begin(); w != rv.w.end(); w++)
	{
		auto x = rv.x.begin();
		auto y = rv.y.begin();
		auto z = rv.z.begin();

		q = make_4dvec(*w, *x, *y, *z);
		*x = get_yaw(q, reprojectAxis);
		*y = get_pitch(q, reprojectAxis);
		*z = get_roll(q, reprojectAxis);

		x++;
		y++;
		z++;
	}


}


void Data::convert_to_world_axis()
{

	double Acc[3][3];
	double aa[1][3];
	for (int i = 0; i < rv.w.size(); i++)
	{ 
		Acc[0][0] = 1 - 2 * rv.y[i] * rv.y[i] - 2 * rv.z[i] * rv.z[i];
		Acc[0][1] = 2 * rv.x[i] * rv.y[i] + 2 * rv.w[i] * rv.z[i];
		Acc[0][2] = 2 * rv.x[i] * rv.z[i] - 2 * rv.w[i] * rv.y[i];
		Acc[1][0] = 2 * rv.x[i] * rv.y[i] - 2 * rv.w[i] * rv.z[i];
		Acc[1][1] = 1 - 2 * rv.x[i] * rv.x[i] - 2 * rv.z[i] * rv.z[i];
		Acc[1][2] = 2 * rv.y[i] * rv.z[i] + 2 * rv.w[i] * rv.x[i];
		Acc[2][0] = 2 * rv.x[i] * rv.z[i] + 2 * rv.w[i] * rv.y[i];
		Acc[2][1] = 2 * rv.y[i] * rv.z[i] - 2 * rv.w[i] * rv.x[i];
		Acc[2][2] = 1 - 2 * rv.x[i] * rv.x[i] - 2 * rv.y[i] * rv.y[i];
	

	
		aa[0][0] = a.x[i];
		aa[0][1] = a.y[i];
		aa[0][2] = a.z[i];

		aa[0][0] = a.x[i] * Acc[0][0] + a.y[i] * Acc[0][1] + a.z[i] * Acc[0][2];
		aa[0][1] = a.x[i] * Acc[1][0] + a.y[i] * Acc[1][1] + a.z[i] * Acc[1][2];
		aa[0][2] = a.x[i] * Acc[2][0] + a.y[i] * Acc[2][1] + a.z[i] * Acc[2][2];
		
		a.x[i] = aa[0][0];
		a.y[i] = aa[0][1];
		a.z[i] = aa[0][1] - 9.8;
	
		double qw,qx,qy,qz;
		qw = rv.w[i];
		qx = rv.x[i] + rv.x[i] * 0.5*g.x[i];
		qy = rv.y[i] + rv.y[i] * 0.5*g.y[i];
		qz = rv.z[i] + rv.z[i] * 0.5*g.z[i];

		double angle = acos(qw);
		g.x[i] = qx / sin(angle);
		g.y[i] = qy / sin(angle);
		g.z[i] = qz / sin(angle);
		
}



}

void Data::output_windows_features(int min ,double winsize,double rate, int fz, vector<vector<double>> &output, vector<pair<double,double>>& action)
{
	
	//cout << "yi?"<<endl;
	//cout << action[0].first;
	for (auto i = action.begin(); i < action.end(); i++)
	{
		//cout << "aaa" << endl;
		if (i->first>=min*60*5 && i->second<=(min+1)*60*5)
		output_range_windows_features(winsize, rate,i->first, i->second, fz, output);
	}

}

void Data::output_range_windows_features(double winsize, double rate, double begin, double end, int fz, vector<vector<double>> &output)
{
	int beginframe = begin * fz;
	int endframe = end * fz;
	vector<double> result;
	while ((beginframe + winsize*fz) <= endframe)
	{
		calculate_range_features_normal(beginframe, beginframe + winsize*fz, result);
		beginframe = beginframe + winsize*fz*(1 - rate);
		output.push_back(result);
		result.clear();
	}
}

void Data::calculate_range_features(int beginframe,int endframe,vector<double> &output)
{
	features_extraction_into_vector_range(output, a, beginframe, endframe);
	features_extraction_into_vector_range(output, g, beginframe, endframe);
	features_extraction_into_vector_range(output, m, beginframe, endframe);
}


void Data::select_turn()
{

	for (int i = 0; i < time.size(); i++)
	{
		if (label[i] == "turnleft" || label[i] == "turnright")
			turn.push_back(make_pair(time[i], time[i + 1]));
	}

}


void Data::select_Acc()
{

	for (int i = 0; i < time.size(); i++)
	{
		if (label[i] == "Accelerate" || label[i] == "Decelerate")
			acc.push_back(make_pair(time[i], time[i + 1]));
	}

}

void Data::calculate_range_features_normal(int beginframe, int endframe, vector<double> &output)
{
	features_extraction_into_vector_range(output, a, beginframe, endframe);
	features_extraction_into_vector_range(output, g, beginframe, endframe);
	features_extraction_into_vector_range(output, m, beginframe, endframe);
	features_extraction_into_vector_range(output, gsm, beginframe, endframe);
}
