#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

double rand_index(int *c, int *k, int &n,ofstream &fout_a)
{
    double tp=0,tn=0;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(c[i]==c[j] && k[i]==k[j])
                tp++;
            else if(c[i]!=c[j] && k[i]!=k[j])
                tn++;
        }
    }
    double res = tp+tn;
    res/=(double)(n);
    res/=(double)(n-1);
    res*=2;
    fout_a<<res;
    return res;
}

int main(int argc, char *argv[])
{
    int number_of_nodes = atoi(argv[1]); //number of nodes
    string original_file = argv[2]; //original file
    string predicted_file = argv[3]; //file which is to be compared
    string ans_file = argv[4]; //file where the answer will be written
    int c[number_of_nodes],k[number_of_nodes];
    //original,
    ofstream fout_a(ans_file);
    ifstream infile_o(original_file);
    int index = 1;
    for(string line; getline(infile_o,line);)
    {
        stringstream ss(line);
        int temp;
        while(ss>>temp){
            c[temp] = index;
        }
        index++;
        //index++;
    }
    //predicted
    ifstream infile_p(predicted_file);
    index = 1;
    for(string line; getline(infile_p,line);)
    {
        stringstream ss(line);
        int temp;
        while(ss>>temp){
            k[temp] = index;
        }
        index++;
        //index++;
    }
    double ans = rand_index(c,k,number_of_nodes,fout_a);
    cout<<ans;
    return 0;
}
