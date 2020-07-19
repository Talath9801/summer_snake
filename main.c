#include<stdio.h>
#include<stdlib.h>
#include<time.h>




int myhead= -1, myneck = -1, direction= -1, myshield= -1; //头位置，脖子位置，方向，道具数。
int row,line;
//int score[4]={-1};
//int *scoreList[40*30];
struct option
{
    int _direc;
    int _score;
};
struct option myopt[4];
int valid(int pos)
{
    if(pos>=0&&pos<40*30)
        return 1;
    else return 0;
}

int addaround(int posi,int *map)
{
    int count=0;
    if(posi>=40)
    {
        int t=posi-40;
        if(map[t]==-100)
            count=+1000;
        else if(map[t]<=-1&&map[t]>=-5)
            count+=map[t]*(-100);
    }
    if(posi<40*29)
    {
        int t=posi+40;
        if(map[t]==-100)
            count=+1000;
        else if(map[t]<=-1&&map[t]>=-5)
            count+=map[t]*(-100);
    }
    if(posi%40==0)
    {
        int t=posi-1;
        if(map[t]==-100)
            count=+1000;
        else if(map[t]<=-1&&map[t]>=-5)
            count+=map[t]*(-100);
    }
    if(posi%40==39)
    {
        int t=posi+1;
        if(map[t]==-100)
            count=+1000;
        else if(map[t]<=-1&&map[t]>=-5)
            count+=map[t]*(-100);
    }
    return count;
}
int ifHead(int value)//判断一个格子的数值是否是头
{
    if(value >= 92310 && value <= 92314){return 1;}
    int negvalue = -value;
        if(negvalue >= 923100 && value <= 923102){return 1;}
        if(negvalue >= 923110 && value <= 923112){return 1;}
        if(negvalue >= 923120 && value <= 923122){return 1;}
        if(negvalue >= 923130 && value <= 923132){return 1;}
    else
        return 0;
}

int ifNeck(int value)//判断一个格子的数值是否是脖子
{
    if(value >= 19202310 && value <=  19202319){return 1;}
    return 0;
}

int shieldNums(int value)//shield
{
    if(value >=  19202310 && value <=  19202319){return value % 10;}
    if(value >=  192023110 && value <=  192023199){return 9;} //偷懒了，超过9一律按9处理
    return 0;
}

int oneDanger(int x)//判断单个格子的值是否安全
{
    if(x==0)
        return 0;
    if(x<=0&&x>=-10000)
        return 0;
    if(ifNeck(x)==1)
        return 0;
    if(x==1920231)
        return 0;
    return 1;

}

int danger(int togo,int *map)
{
    if(togo==1)//将要往上走
    {
        if((myhead>=0&&myhead<40)||direction==3)
        {
            return 1;
        }
        if(oneDanger(map[myhead-40])==1)
            return 1;
    }
    if(togo==3)//将要往下走
    {
        if((myhead>=40*29&&myhead<40*30)||direction==1)
        {
            return 1;
        }
        if(oneDanger(map[myhead+40])==1)
            return 1;
    }
    if(togo==0)//将要往左走
    {
        if(myhead%40==0||direction==2)
        {
            return 1;
        }
        if(oneDanger(map[myhead-1])==1)
            return 1;
    }
    if(togo==2)//将要往右走
    {
        if((myhead%40==39&&myhead>0)||direction==0)
        {
            return 1;
        }
        if(oneDanger(map[myhead+1])==1)
            return 1;
    }
    return 0;
}

void  calculate(int *map)
{
    for(int i=0;i<4;i++)
    {
         myopt[i]._score=0;//重置评分表
         myopt[i]._direc=i;
    }

    if(myhead>=40)//上方的格子
    {
        int temp=myhead-40;
        if(map[temp]==-100)
            myopt[1]._score+=10000;
        else if(map[temp]<=-1&&map[temp]>=-5)
            myopt[1]._score+=map[temp]*(-1000);
        myopt[1]._score+=addaround(temp,map);

    }
    if(myhead<40*29)//下方的格子
    {
        int temp=myhead+40;
        if(map[temp]==-100)
            myopt[3]._score+=10000;
        else if(map[temp]<=-1&&map[temp]>=-5)
            myopt[3]._score+=map[temp]*(-1000);
        myopt[3]._score+=addaround(temp,map);
    }
    if(myhead%40!=0)//左边的格子
    {
        int temp=myhead-1;
        if(map[temp]==-100)
            myopt[0]._score+=10000;
        else if(map[temp]<=-1&&map[temp]>=-5)
            myopt[0]._score+=map[temp]*(-1000);
        myopt[0]._score+=addaround(temp,map);
    }
    if(myhead%40!=39)//右边的格子
    {
        int temp=myhead+1;
        if(map[temp]==-100)
            myopt[2]._score+=10000;
        else if(map[temp]<=-1&&map[temp]>=-5)
            myopt[2]._score+=map[temp]*(-1000);
        myopt[2]._score+=addaround(temp,map);
    }
}

int judge(int * map)//读入当前地图之后输出一个方向
{
    //一行40个
    //首先找头，脖子，方向
    //int myhead= -1, myneck = -1, direction= -1, myshield= -1; //头位置，脖子位置，方向，道具数。
    for(int i=0; i< 30*40; i++){
        if(ifHead(map[i])){ //找头
            myhead= i;
            if(map[i] > 0){direction = map[i] % 10; }//非保护状态
            else{direction = (-map[i]) /10%10;}//保护状态
        }
        if(ifNeck(map[i])){myneck= i;}//找脖子
    }
    line=myhead%40;
    row=(myhead-line)/40;
    myshield = shieldNums(map[myneck]); //根据脖子的数值获得道具数量
    //if(myshield >=1){return 4;}//如果拥有的道具超过两个，直接放道具。


    calculate(map);//算分,保存到score数组中
    //不会死的情况下选分最高的
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<3-j;i++)
        {
            if(myopt[i]._score<myopt[i+1]._score)
            {
                int t;

                t=myopt[i]._direc;
                myopt[i]._direc=myopt[i+1]._direc;
                myopt[i+1]._direc=t;

                t=myopt[i]._score;
                myopt[i]._score=myopt[i+1]._score;
                myopt[i+1]._score=t;
            }
        }
    }
    for(int i=0;i<4;i++)
    {
        if(danger(myopt[i]._direc,map)==0)
            return myopt[i]._direc;
    }


    //还未考虑用盾牌的情况
    return 4; //哪个方向都不能走，那就随便走一个0吧，来世再见。
}

int main()
{
    int a[1200]; //存储地图
    for(int i = 0; i<1200; i++){
        scanf("%d",&a[i]); //读入地图
    }
    int des = judge(a); //你的算法，最终输出一个方向des
    printf("%d", des);
    return 0;
}
