#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#define f(i,a,b) for(int i = a; i < b; i++)
using namespace std;
long long dp[51][51];

int32_t main(){
    int p,in1,in2,leg,s1,s2;
    long long sum,temp;
    f(i,0,51)   dp[i][0]=dp[i][i]=1;
    f(i,2,51)   f(j,1,i+1)    dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
    cin>>p;
    f(i,0,p){
        cin>>in1>>in2;
        leg=in2/2;
        s2=leg/2;
        s1=leg-(2*s2);
        sum=temp=0;
        while(s2>=s1)   temp=dp[s1+s2][s2], sum+=temp*temp, s2-=1,s1+=2;
        cout<<in1<<" "<<sum<<endl;
    }
}