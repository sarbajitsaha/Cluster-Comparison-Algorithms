#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

double count_c_in_k(vector<double> &c, vector<double> &k)
{
    vector<double> v_intersection;
    set_intersection(c.begin(), c.end(), k.begin(), k.end(), back_inserter(v_intersection));
    return v_intersection.size();
}

double H_X(vector<vector<double>> &xx, vector<vector<double>> &yy, double &N)
{
    double H_res=0.0;
    for(auto &x: xx)
    {
        double f=((double)x.size())/((double)N);
        if(f==0)
            continue;
        H_res-=f*log(f);
    }
    return H_res;
}

double H_XY(vector<vector<double>> &xx, vector<vector<double>> &yy, double &N)
{
    double H_res=0.0;
    for(auto &x: xx)
    {
        sort(x.begin(),x.end());
        for(auto &y: yy)
        {
            sort(y.begin(),y.end());
            double n_ck=count_c_in_k(x,y);
            if(n_ck==0)
                continue;
            double f1=((double)n_ck)/((double)N);
            double f2=((double)n_ck)/((double)y.size());
            H_res-=f1*log(f2);
        }
    }
    return H_res;
}

double V_measure(vector<vector<double>> &cc, vector<vector<double>> &kk, double &N)
{
    double h=1.0,c=1.0;
    double H_C=H_X(cc,kk,N);
    double H_K=H_X(kk,cc,N);
    if(H_C!=0)
        h=1-H_XY(cc,kk,N)/H_C;
    if(H_K!=0)
        h=1-H_XY(kk,cc,N)/H_K;
    return 2*h*c/(h+c);
}

void VI_NVI(vector<vector<double>> &cc, vector<vector<double>> &kk, double &N,double &ans_vi,double &ans_nvi)
{
    ans_vi=H_XY(cc,kk,N)+H_XY(kk,cc,N);
    cout<<"2"<<endl;
    double H_C=H_X(cc,kk,N);
    if(H_C==0)
        ans_nvi=H_X(kk,cc,N);
    else
        ans_nvi=ans_vi/H_C;
}

int main(int argc, char *argv[])
{
    double number_of_nodes = atoi(argv[1]); //number of nodes
    string original_file = argv[2]; //original file
    string predicted_file = argv[3]; //file which is to be compared
    string output_file = argv[4]; //file where the answer will be written

    vector<vector<double>> cc,kk;
    //original
    ifstream infile_o(original_file);
    ofstream fout(output_file);
    for(string line; getline(infile_o,line);)
    {
        stringstream ss(line);
        double temp;
        vector<double> vec_temp;
        while(ss>>temp){
            vec_temp.push_back(temp);
        }
        cc.push_back(vec_temp);
        //index++;
    }
    //predicted
    ifstream infile_p(predicted_file);
    for(string line; getline(infile_p,line);)
    {
        stringstream ss(line);
        double temp;
        vector<double> vec_temp;
        while(ss>>temp){
            vec_temp.push_back(temp);
        }
        kk.push_back(vec_temp);
    }
    cout<<"1"<<endl;
    double ans_vi = 0;
    double ans_nvi = 0;
    VI_NVI(cc,kk,number_of_nodes,ans_vi,ans_nvi);
    fout<<ans_vi<<endl<<ans_nvi<<endl;
    cout<<ans_vi<<endl<<ans_nvi<<endl;
    return 0;
}
