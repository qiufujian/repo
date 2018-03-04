#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;
int main(){
    int P[100];
    int T[100];
    int G1[100];
    int G2[100];
    int G3[100];
    int GJ[100];
    int num=0;
    while(scanf("%d %d",&P[num],&T[num])!= EOF){
        int temp1,temp2,temp3,temp4;
        cin>>temp1>>temp2>>temp3>>temp4;
        if( temp1<=P[num] && temp2 <= P[num] && temp3 <=P[num] && temp4<=P[num]
            && temp1 >=0 && temp2 >=0 && temp3 >=0 && temp4>=0){
            G1[num]=temp1;
            G2[num]=temp2;
            G3[num]=temp3;
            GJ[num]=temp4;
            num++;
        }
       else
           continue;//所有分数必须在[0-P]之间
    }
    double avg;
    for(int i=0;i<num;i++){//针对每个问题进行成绩处理
        if(abs(G1[i]-G2[i]) <= T[i]){
            avg = double(G1[i]+G2[i])/2;
        }
        else{//如果前面两位专家给的分数差别太大
            if(abs(G1[i]-G3[i])<=T[i] && abs(G2[i]-G3[i])<=T[i]){
                avg = double(max(max(G1[i],G2[i]),G3[i]));
            }
            else if(abs(G1[i]-G3[i])>T[i] && abs(G2[i]-G3[i])>T[i]){
                avg = double(GJ[i]);
            }
            else{//G3要么与G1差不多，要么与G2差不多
                if(abs(G1[i]-G3[i])<=T[i]){
                   avg = double(G1[i]+G3[i])/2;
                }else if(abs(G2[i]-G3[i])<=T[i]){
                    avg = double(G2[i]+G3[i])/2;
                }
            }

        }
       cout<<setiosflags(ios::fixed)<<setprecision(1);
       cout<<avg<<endl;
    }
    return 0;
}
