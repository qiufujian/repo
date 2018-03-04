#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
int Merge(long * s1,int length1,long *s2,int length2);
int main(){
    int N1[100];//序列1的大小
    long int **S;
    int num=0;
    S = new long* [100];
    while(scanf("%d",&N1[num]) != EOF){
        S[num] = new long[N1[num]];
        for(int i=0;i<N1[num];i++){
            cin>>S[num][i];
        }
        num++;
    }
        for(int i=0;i<num;i=i+2){
            cout<<Merge(S[i],N1[i],S[i+1],N1[i+1])<<endl;
        }

    return 0;
}
int Merge(long *s1,int length1,long *s2,int length2){
    long *s3 = new long[length1+length2];
    int start1=0,start2=0;
    int i=0;
    for(i=0;i<length1+length2;i++){
        if(s1[start1] < s2[start2]){
            if(start1 >= length1){
                break;
            }
            s3[i]=s1[start1++];
        }else{
            if(start2>=length2){
                break;
            }
            s3[i]=s2[start2++];
        }
    }
    if(start1 >= length1){//序列1结束，直接把序列2补上去
        for(int j=start2;j<length2;j++){
            s3[i++] = s2[j];
        }
    }else{//序列2结束，直接把序列1补上去
        for(int j=start1;j<length1;j++){
            s3[i++] = s1[j];
        }
    }
    return s3[(length1+length2-1)/2];
}
