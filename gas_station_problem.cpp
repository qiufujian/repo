#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>

#define MAX_PRICE 3000000.0             //�������۸�

using namespace std;
struct station{
    int distance;//����վ����������
    double price;//��λ���ͼ۸�
};
void my_sort(station *mystation,int length);
int main(){
    int Cmax;//��������
    int dis;//Ŀ�ĵؾ���
    int per_dis;//ÿ��λ���Ϳ�����ʻ�ľ���
    int gas_num;//����վ����
    double driv_dis;
    struct station sta[502];
    double dp[500]={0};
    double current_gas[502];//i��ʾ��sta[i-1]�뿪֮�����������
    bool flag,mark;
    while(cin>>Cmax>>dis>>per_dis>>gas_num){
        memset(dp,0,sizeof(dp));
        memset(current_gas,0,sizeof(current_gas));
        driv_dis=0;

        for(int i = 0;i<gas_num;i++){
            cin>>sta[i].price>>sta[i].distance;
        }
        sta[gas_num].distance = dis;
        sta[gas_num].price=MAX_PRICE;//����Ŀ�ĵ�
        my_sort(sta,gas_num+1);

	   if(sta[0].distance !=0 || gas_num == 0){//�����ʼû�м���վ
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
                if(sta[j].price < sta[i].price){//��cmax*per_dis��Χ��Ѱ���Ƿ��бȵ�ǰ�۸���͵�
                    pos=j;                      //����վ
                    flag=true;
                    break;//ֻҪ�ҵ�һ������վ�۸�ȵ�ǰ���˾�����ֹͣ
                }
                j++;
            }
            if(flag == true){ //�ҵ��ȵ�ǰ�۸���͵ļ���վ
                if(current_gas[i]*per_dis >= sta[pos].distance-sta[i].distance){
                    current_gas[pos]=current_gas[i]-double(sta[pos].distance-sta[i].distance)/double(per_dis);
                }
                else{
                    dp[i]+=(double(sta[pos].distance-sta[i].distance)/double(per_dis)-current_gas[i])*sta[i].price;
                    current_gas[pos] = 0;
                }
                i=pos;
            }

            if(flag == false && mark == true){//��һ�μ����ͺ����ʻ��Χ��
                                              //û���ҵ��ȵ�ǰ�۸���͵ļ���վ
                int last_distance = sta[gas_num].distance-sta[i].distance;
                if(Cmax * per_dis >=last_distance){//����ֱ�ӵ����յ�վ
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
                int k=i+1;//���������ֱ�ӵ����յ�վ������ҪѰ�Һ����������˵ļ���վ
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
        if(mark != false)//������Ե���������ͼ۸�
            cout<<setiosflags(ios::fixed)<<setprecision(2)<<result<<endl;
    }
   return 0;
}
//�����еļ���վ���ռ۸��С��������
void my_sort(station *mystation,int length){
    int pos;
    int my_min;
    struct station temp;
    for(int i=0;i<length-1;i++){
        my_min=MAX_PRICE;//����������
        int j;
        for(j=i;j<length;j++){
            if(my_min>mystation[j].distance){
                my_min=mystation[j].distance;
                pos=j;
            }
        }
        //����
        temp=mystation[i];
        mystation[i]= mystation[pos];
        mystation[pos]=temp;
    }
}
