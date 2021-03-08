#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#define f(i,a,b) for(int i = a; i < b; i++)
using namespace std;
long long dp[51];

int32_t main(){
    int p,in1,in2,leg,s1,s2;
    long long sum,temp;
    dp[0]=2,dp[1]=1;
    f(i,2,51)   dp[i]=dp[i-1]+dp[i-2];
    cin>>p;
    f(i,0,p){
        cout<<dp[i];
        ((i+1)%7==0)? cout<<'\n':cout<<' ';
    }
}