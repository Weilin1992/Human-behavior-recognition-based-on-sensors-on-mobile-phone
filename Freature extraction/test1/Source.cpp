
/*
#include <iostream>
#include <smfe/feature/wavelet_features.h>
#include <smfe/feature/integral_calculus.h>
#include <smfe/feature/frequency_domain_features.h>
#include <smfe/feature/time_domain_features.h>
using namespace std;

#define print(x) cout << #x << " : " << x << endl

int main(int argc, char const* argv[])
{
	smfe::value_t d[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
	smfe::vec src = smfe::make_vec(d, 8);

	print(smfe::energy(src));
	print(smfe::kurtosis(src));
	print(smfe::get_nth_elem(src, 2));

	smfe::fm_vec fm_v = smfe::sorted_frequency_magnitude_vec(src, 1000);

	for (int i = 0; i < fm_v.size(); ++i) {
		cout << fm_v[i] << endl;
	}

	print(smfe::frequency_energy(fm_v));
	print(smfe::first_quater_frequency(fm_v));

	smfe::dwt_length_vec length;
	smfe::dwt_flag_vec flag;

	// using level 2 is will raise an error
	try {
		auto dwt_signal = smfe::dwt(src, "db2", 2, length, flag);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	auto dwt_signal = smfe::dwt(src, "db2", 1, length, flag);
	print(dwt_signal);
	print(smfe::dwt_detail_coeff(dwt_signal, length, 1));
	print(smfe::dwt_approximation_coeff(dwt_signal, length));

	// 第一层detail信号的能量
	print(smfe::dwt_energy(dwt_signal, length, 1));

	// 使用原始信号的能量对第一层detail信号的能量进行归一化处理
	print(smfe::dwt_normised_energy_using_signal_energy(smfe::energy(src), dwt_signal, length, 1));
	getchar();
	return 0;
}
*/

#include <iostream>
#include <string>
#include <boost\property_tree\xml_parser.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\foreach.hpp>//maybe not be used below
#include <vector>
#include <boost\typeof\typeof.hpp>
#include <fstream>
#include "Data.h"

using namespace std;

int main ()
{
	 /*
	 for (int i = 1; i <= 9; i++)
	 {

		 stringstream ss;
		 string s;
		 ss << i;
		 ss >> s;
		 //cout << s;
		 s = "n" + s + ".xml";
		 //cout << s;
	   Data xmldata(s.data());


	   xmldata.output_5min_features(s, 1, 30);
	   xmldata.output_5second_features(s, 1, 30);
	   cout <<s <<" success"<<endl<<endl;
	 }
        */
	/*
	for (int i = 1; i <= 50; i++)
	{

	stringstream ss;
	string s;
	ss << i;
	ss >> s;
	//cout << s;
	s = s + ".xml";
	//cout << s;
	Data xmldata(s.data());

	xmldata.output_window(s, 100, 10, 0.5);

	//xmldata.output_5min_features(s, 1, 30);
	//xmldata.output_5second_features(s, 1, 30);
	//cout <<s <<" success"<<endl<<endl;
	}
    */

	
	
	 for (int i = 1; i <= 35; i++)
	 {
		 stringstream ss;
		 string s;
		 ss << i;
		 ss >> s;
		 auto txt = s;
         s =  s + ".xml";
         Data xmldata(s.data());

		 
		 txt = txt + ".txt";
		 ifstream fin(txt, ios::in);
		 char line[1024] = { 0 };
		 string  time;
		 string label;


		 while (fin.getline(line, sizeof(line)))
		 {
			 stringstream word(line);
			 word >> time;
			 word >> label;
		
		 xmldata.time.push_back(atof(time.data())/100.0*5);
		 xmldata.label.push_back(label);

          }
		 fin.clear();
		 fin.close();
		 

		 //xmldata.output_5min_features(s, 1, 30);
		 //xmldata.output_5second_features(s, 1, 30);
		 xmldata.output_driver_detection_turn_features(s, 0.5,2.5);
		 xmldata.output_driver_detection_acc_features(s, 0.5,2.5);
		 cout <<s << " success" << endl << endl;

		 //xmldata.Printf_label();
	 }
	
	/*
	 string a = "zuo_a12_0.xml";
	 Data xmldata(a.data());
	 xmldata.output_5min_features(a, 1, 30);
	 getchar();
    */

}



