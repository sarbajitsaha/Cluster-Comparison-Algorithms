#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

double count_c_in_k(vector<double> &c, vector<double> &k) //count how many elements of vector c are in vector k 
{
    vector<double> v_intersection;
    set_intersection(c.begin(), c.end(), k.begin(), k.end(), back_inserter(v_intersection));
    return v_intersection.size();
}

double recall(vector<double> &c, vector<double> &k) //recall function
{
    double res = count_c_in_k(c,k)/((double)c.size());
    return res;
}

double precision(vector<double> &c, vector<double> &k) //precision function
{
    double res = (double)count_c_in_k(c,k)/((double)k.size());
    return res;
}

double f_score_algo(vector<vector<double>> &cc, vector<vector<double>> &kk, double &N, ofstream &fa) 
{
    double f_score = 0.0;
    int step = 0;
    for(auto &c: cc)
    {
        double temp = 0.0;
        for(auto &k: kk)
        {
            sort(c.begin(),c.end());
            sort(k.begin(),k.end());
            double rec = recall(c,k);
            double prec = precision(c,k);
            double f_c_k;
            if(rec==0 && prec==0)
                f_c_k = 0;
            else
                f_c_k = (double)(2*rec*prec)/(double)(rec+prec);
            temp = max(temp,f_c_k);
        }
        temp = temp*c.size();
        f_score += temp;
        step++;
    }
    f_score/=N;
    fa<<f_score;
    return f_score;
}

void display_vec(vector<vector<double>> v)
{
    for (auto &c: v)
    {
        for(auto &i: c)
            cout<<i<<" ";
        cout<<endl;
    }
}

int main(int argc, char *argv[])
{
    double number_of_nodes = atoi(argv[1]); //number of nodes
    string original_file = argv[2]; //original file
    string predicted_file = argv[3]; //file which is to be compared
    string ans_file = argv[4]; //file where the answer will be written
    vector<vector<double>> cc,kk; //2d vectors

    ofstream fout_a(ans_file);

    //original
    ifstream infile_o(original_file);
    for(string line; getline(infile_o,line);)
    {
        stringstream ss(line);
        double temp;
        vector<double> vec_temp;
        while(ss>>temp){
            vec_temp.push_back(temp);
        }
        cc.push_back(vec_temp);
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
    double ans = f_score_algo(cc,kk,number_of_nodes,fout_a); //main algorithm
    cout<<ans;
    return 0;
}
