/*
求解字符串的最长递减序列
注意区分序列与子串的区别
*/
#include<iostream>
#include <algorithm>
#include <string.h>
using namespace std;
void count_steps(int A[],int arr_length){ //计算最长递减子序列

    int pos;
    int counter=0;
    int result1[100]={0};
    int result2[100]={0};
    int dp[100]={0};
    dp[0]=1;
    int res;
    int mymax=0;
    bool mark;
    for(int i=1;i<=arr_length;i++){//求解最长递减子序列的长度
        res=0;
        mark=false;
        for(int j=0;j<=i;j++){
            if(A[j] > A[i]){
                dp[i]=dp[j]+1;
                if(res<dp[i]){
                   res = dp[i];
                   mark=true;
                }
            }
        }
        if(mark)
            dp[i]=res;
    }
    for(int i=0;i<=arr_length;i++){
        if(mymax<dp[i]){
            mymax=dp[i];
        }
    }
    for(int i=arr_length;i>=0;i--){//求解字符串的最长递减序列，构造最优解
        if(dp[i]== mymax){
            pos = i;
            result1[counter]=A[i];
            counter++;
            mymax--;
           }
    }
    for(int i=counter-1;i>=0;i--){//打印序列
        cout<<result1[i];
        if(i!=0)
            cout<<" ";
    }
    cout<<endl;
}
int main(){
    int length;
    int A[100];
    while(cin>>length){
        memset(A,0,sizeof(A));
        for(int i=0;i<length;i++)
            cin>>A[i];
        count_steps(A,length-1);
    }
    return 0;
}
