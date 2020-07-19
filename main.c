#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//本代码对应的学号为2019101404
//仓促完成，代码质量不高，仅供参考

int myhead= -1, myneck = -1, direction= -1, myshield= -1; //头位置，脖子位置，方向，道具数。

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

int danger(int togo)
{
    if(togo==1)//将要往上走
    {
        if((myhead>=0&&myhead<40)||direction==3)
        {
            return 1;
        }
    }
    if(togo==3)
    {
        if((myhead>=40*29&&myhead<40*30)||direction==1)
        {
            return 1;
        }
    }
    if(togo==0)
    {
        if(myhead%40==0||direction==2)
        {
            return 1;
        }
    }
    if(togo==2)
    {
        if((myhead%40==39&&myhead>0)||direction==0)
        {
            return 1;
        }
    }
    return 0;
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
    myshield = shieldNums(map[myneck]); //根据脖子的数值获得道具数量
    //if(myshield >=1){return 4;}//如果拥有的道具超过两个，直接放道具。

    for(int i=0;i<=4;i++) //选一个能走的方向，走
    {
        if(danger(i)==0) return i;
    }

    return 0; //哪个方向都不能走，那就随便走一个0吧，来世再见。
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
