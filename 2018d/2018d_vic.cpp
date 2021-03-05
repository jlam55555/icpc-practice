  
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#define f(i,a,b) for(int i = a; i < b; i++)
#define para 500000
using namespace std;
double dpx[para+1][2];
double dpy[para+1];
int32_t main(){
    int p,k,index;
    double rt,rt2,rp,off,slo,z,y,temp,rp_cut,ans,dx,dy,dz;
    cin>>p;
    f(i,0,p){
        cin>>k>>rt>>rp>>off>>slo;
        rt2=rt*rt;
        index=0;
        z=2*rt;
        ans=0;
        while(z>0){
            temp=abs(z-rt);
            dpy[index]=sqrt(rt2-temp*temp);
            temp=abs(z-(rt+off));
            if(temp>rp) {
                dpx[index][0]=dpx[index][1]=dpy[index]=0;
                index++;
                z-=(2*rt/para);
                continue;
            }
            rp_cut=sqrt(rp*rp-temp*temp);
            temp=rp_cut*sqrt(1+slo*slo);
            dpx[index][0]=dpy[index]/slo-temp;
            dpx[index][1]=dpx[index][0]+2*temp;
            if(dpy[index-1]){
                dz=(2*rt/para);
                dz*=dz;
                dx=dpx[index-1][0]-dpx[index][0];
                dx*=dx;
                dy=dpy[index-1]-dpy[index];
                dy*=dy;
                ans+=sqrt(dz+dx+dy);
                dx=dpx[index-1][1]-dpx[index][1];
                dx*=dx;
                ans+=sqrt(dz+dx+dy);
            }
            index++;
            z-=(2*rt/para);
        }
        cout<<k<<" "<<ans<<endl;
    }
}