#include <iostream>
#include <unordered_map>
using namespace std;

int subprime(int n){
    for(int i=2;i<n;i++){
        if(!(n%i))
            return n/i;
    }
    return n;
}
int main() {
    int i,j,k,lo,dump,n,a0,a1;
    int data[1000]={0};
    cin>>lo;
    for(i =0;i<lo;i++){
        cin>>dump>>n>>a0>>a1;
        for(j=2;j<n;j++){
            data[j]=subprime(data[j-1]+data[j-2]);
            for(k=0;k<=2;k++){

            }
        }
    }
}
