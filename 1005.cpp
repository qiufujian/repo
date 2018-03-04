#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
using namespace std;
struct Apply{
    int GE;
    int GI;
    int choice[5];
    int pos;
    bool operator <(const Apply &that){
        return this->GE+this->GI<that.GE+that.GI;
    }
};
void Desc_sort(Apply *app,int length);
int main(){
    int N[1000];
    int M[1000];
    int K[1000];
    int **Q;
    int num=0;
    Apply **app;
    Q = new int*[1000];//�洢����ѧУ��ָ�꣺quota
    app = new Apply*[1000];
    while(scanf("%d %d %d",&N[num],&M[num],&K[num])!=EOF){
        Q[num] = new int[M[num]];
        for(int i=0;i<M[num];i++){
            cin>>Q[num][i];//�������ѧУ��ָ��
        }
        app[num] = new Apply[N[num]];
        for(int i=0;i<N[num];i++){
            cin>>app[num][i].GE>>app[num][i].GI;
            for(int j=0;j<K[num];j++){
                cin>>app[num][i].choice[j];
            }
            app[num][i].pos = i;
        }
      num++;//¼�����е�����
    }
    int **R;
    int *quota;
    int **score;
    int **willing;
    for(int i=0;i<num;i++){
        quota = new int[M[i]];//��¼ÿ��ѧУʵ¼ȡ����
        memset(quota,0,sizeof(int)*M[i]);
        Desc_sort(app[i],N[i]);//���������밴�ճɼ�����
        R =new int*[M[i]];
        score = new int*[M[i]];
        willing = new int*[M[i]];
        for(int k=0;k<M[i];k++){
            R[k] = new int[20];//����ÿ��ѧУ���20��ָ��
            score[k] = new int[20];
            willing[k] = new int[20];
            memset(R[k],-1,sizeof(int)*20);
            memset(score[k],0,sizeof(int)*20);
            memset(willing[k],0,sizeof(int)*20);
        }
        for(int j=0;j<N[i];j++){
            for(int m=0;m<K[i];m++){//��ÿ��ѧ��������ѡ�����ɸѡ
                if(Q[i][app[i][j].choice[m]]>0){
                    R[app[i][j].choice[m]][quota[app[i][j].choice[m]]] = app[i][j].pos;
                    score[app[i][j].choice[m]][quota[app[i][j].choice[m]]] = app[i][j].GE+app[i][j].GI;
                    willing[app[i][j].choice[m]][quota[app[i][j].choice[m]]]=m;
                    Q[i][app[i][j].choice[m]]--;
                    quota[app[i][j].choice[m]]++;
                    break;
                }else{
                    int current_core = app[i][j].GE+app[i][j].GI;
                    int mark = app[i][j].choice[m];//ѧ����������ѧУ���
                    int last_score = score[mark][quota[mark]-1];
                    int last_willing = willing[mark][quota[mark]-1];
                    if(current_core >= last_score && last_willing >=m ){
                        R[mark][quota[mark]] = app[i][j].pos;
                        score[mark][quota[mark]] = app[i][j].GE+app[i][j].GI;
                        willing[mark][quota[mark]]=m;
                        quota[mark]++;
                        break;
                    }
                }
            }
        }
       for(int y=0;y<M[i];y++) {
           sort(R[y],R[y]+quota[y]);
           if(quota[y] == 0){
            cout<<endl;
           }
           else{
           for(int z=0;z<quota[y]-1;z++){
               if(R[y][z] == -1)
                   cout<<" "<<" ";
               else
                   cout<<R[y][z]<<" ";
           }
           if(R[y][quota[y]-1] == -1)
               cout<<" "<<endl;
           else
               cout<<R[y][quota[y]-1]<<endl;
       }
       }
       for(int x=0;x<M[i];x++){
        delete score[x];
        delete R[x];
       }
    }
    return 0;
}
void Desc_sort(Apply *app,int length){
    int pos;
    struct Apply my_max;
    struct Apply temp;
    bool flag;
    for(int i=0;i<length-1;i++){
        flag=false;
        my_max=app[i];//����������
        int j;
        for(j=i+1;j<length;j++){
            if(my_max<app[j]){
                my_max = app[j];
                pos=j;
                flag = true;
            }
        }
        if(flag){//����н�������
        temp=app[i];
        app[i] = my_max;
        app[pos]=temp;
        }
    }
}
