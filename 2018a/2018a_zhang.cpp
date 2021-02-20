#include <iostream>

using namespace std;

int main() {
	int temp;
	int rows;
	int dump,target;
	cin>>rows;
	for(int ind=0;ind<rows;ind++){
		int masscount[4]={0};
		cin>>dump>>target;
		for(int i=0;i<10;i++){
			cin>>temp;
			masscount[temp]++;
		}
		int sum=0;
		for(int k=3;k>0;k--){
			sum+=masscount[k]*k;
			if(sum>target){
				temp=(target-sum)%k;
				sum-=k*(++temp);
			}
		}
		cout<<(ind+1)<<" "<<((sum==target)?"YES":"NO")<<endl;
	}
}