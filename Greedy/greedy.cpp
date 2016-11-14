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

double greedy_algo(vector<vector<double>> &cc, vector<vector<double>> &kk, double &n, ofstream &fa) //main algorithm
{
    double greedy_score = 0.0;
    int step = 0;
    for(auto &k: kk)
    {
        double temp = 0.0;
        for(auto &c: cc)
        {
            sort(c.begin(),c.end());
            sort(k.begin(),k.end());
            double f_c_k;
            f_c_k = count_c_in_k(c,k);
            temp = max(temp,f_c_k);
        }
        greedy_score += temp;
        step++;
    }
    greedy_score/=n;
    fa<<greedy_score;
    return greedy_score;
}

int main(int argc, char *argv[])
{
    double number_of_nodes = atoi(argv[1]); //number of nodes
    string original_file = argv[2]; //original file
    string predicted_file = argv[3]; //file which is to be compared
    string ans_file = argv[4]; //file where the answer will be written
    vector<vector<double>> cc,kk;

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
    double ans = greedy_algo(cc,kk,number_of_nodes,fout_a);
    cout<<ans;
    return 0;
}
