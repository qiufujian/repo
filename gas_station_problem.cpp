#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>

#define MAX_PRICE 3000000.0             //定义最大价格

using namespace std;
struct station{
    int distance;//加油站距离起点距离
    double price;//单位汽油价格
};
void my_sort(station *mystation,int length);
int main(){
    int Cmax;//邮箱容量
    int dis;//目的地距离
    int per_dis;//每单位汽油可以行驶的距离
    int gas_num;//加油站数量
    double driv_dis;
    struct station sta[502];
    double dp[500]={0};
    double current_gas[502];//i表示从sta[i-1]离开之后油箱的油量
    bool flag,mark;
    while(cin>>Cmax>>dis>>per_dis>>gas_num){
        memset(dp,0,sizeof(dp));
        memset(current_gas,0,sizeof(current_gas));
        driv_dis=0;

        for(int i = 0;i<gas_num;i++){
            cin>>sta[i].price>>sta[i].distance;
        }
        sta[gas_num].distance = dis;
        sta[gas_num].price=MAX_PRICE;//加入目的地
        my_sort(sta,gas_num+1);

	   if(sta[0].distance !=0 || gas_num == 0){//如果起始没有加油站
	     cout<<setiosflags(ios::fixed)<<setprecision(2)<<"The maximum travel distance = 0.00"<<endl;
	     continue;
	   }
        for(int i=0;i<gas_num;){
            int j=i+1;
            flag = false;
            mark=false;
            int pos;
            while(sta[j].distance-sta[i].distance <= Cmax*per_dis && j < gas_num+1){
                mark=true;
                if(sta[j].price < sta[i].price){//在cmax*per_dis范围内寻找是否有比当前价格更低的
                    pos=j;                      //加油站
                    flag=true;
                    break;//只要找到一个加油站价格比当前便宜就立即停止
                }
                j++;
            }
            if(flag == true){ //找到比当前价格更低的加油站
                if(current_gas[i]*per_dis >= sta[pos].distance-sta[i].distance){
                    current_gas[pos]=current_gas[i]-double(sta[pos].distance-sta[i].distance)/double(per_dis);
                }
                else{
                    dp[i]+=(double(sta[pos].distance-sta[i].distance)/double(per_dis)-current_gas[i])*sta[i].price;
                    current_gas[pos] = 0;
                }
                i=pos;
            }

            if(flag == false && mark == true){//在一次加满油后的行驶范围内
                                              //没有找到比当前价格更低的加油站
                int last_distance = sta[gas_num].distance-sta[i].distance;
                if(Cmax * per_dis >=last_distance){//可以直接到达终点站
                if(current_gas[i]*per_dis >= last_distance){
                    dp[i]=0;
                    current_gas[gas_num]=current_gas[i]-(double)last_distance/(double)per_dis;
                }
                else {
                    dp[i]+=((double)last_distance/(double)per_dis-current_gas[i])*sta[i].price;
                    current_gas[gas_num]=0;
                }
                 break;
                }
                int k=i+1;//如果不可以直接到达终点站，则需要寻找后面相对最便宜的加油站
                double my_min = MAX_PRICE-1;
                int index;
                while(sta[k].distance - sta[i].distance <= Cmax * per_dis && k < gas_num){
                    if(my_min > sta[k].price){
                        my_min = sta[k].price;
                        index = k;
                    }
                    k++;
                }
                    dp[i]+=(Cmax-current_gas[i])*sta[i].price;
                    current_gas[index] = Cmax - (double)(sta[index].distance-sta[i].distance)/(double)per_dis;
                    i = index;
            }
            if(mark == false){
                driv_dis = sta[i].distance+Cmax*per_dis;
                cout<<setiosflags(ios::fixed)<<setprecision(2)<<"The maximum travel distance = "<<driv_dis<<endl;
                break;
            }
        }
        double result=0;
        for(int i=0;i<gas_num+1;i++){
           result+=dp[i];
        }
        if(mark != false)//如果可以到达，则输出最低价格
            cout<<setiosflags(ios::fixed)<<setprecision(2)<<result<<endl;
    }
   return 0;
}
//对所有的加油站按照价格从小到大排序
void my_sort(station *mystation,int length){
    int pos;
    int my_min;
    struct station temp;
    for(int i=0;i<length-1;i++){
        my_min=MAX_PRICE;//大于最大距离
        int j;
        for(j=i;j<length;j++){
            if(my_min>mystation[j].distance){
                my_min=mystation[j].distance;
                pos=j;
            }
        }
        //交换
        temp=mystation[i];
        mystation[i]= mystation[pos];
        mystation[pos]=temp;
    }
}
