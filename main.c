#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//本代码对应的学号为2019101404
//仓促完成，代码质量不高，仅供参考

int judgeifHead(int value)//判断一个格子的数值是否是头
{
    if(value >= 92310 && value <= 92314){return 1;}
    /*int negvalue = -value;
    if(negvalue >= 940400 && value <= 940402){return 1;}
    if(negvalue >= 940410 && value <= 940412){return 1;}
    if(negvalue >= 940420 && value <= 940422){return 1;}
    if(negvalue >= 940430 && value <= 940432){return 1;}
    return 0;*/
    else
        return 0;
}

int judgeifBozi(int value)//判断一个格子的数值是否是脖子
{
    if(value >= 19202310 && value <=  19202319){return 1;}
    //if(value >=  191140410 && value <=  191140499){return 1;}
    return 0;
}

int judgeDaojuNums(int value)////判断当前拥有多少道具
{
    //if(value >=  19114040 && value <=  19114049){return value % 10;}
    //if(value >=  191140410 && value <=  191140499){return 9;} //偷懒了，超过9一律按9处理
    return 0;
}


int judge(int * map)//本算法实现了不会因为撞墙而死，当蛇拥有两个道具便无脑放一次道具。
{
    //一行40个
    //首先找头，脖子，方向
    int head_idx = -1, bozi_idx = -1, des = -1, daoju_nums = -1; //头位置，脖子位置，方向，道具数。
    for(int i=0; i< 30*40; i++){
        if(judgeifHead(map[i])){ //此格是否为头?
            head_idx = i;
            if(map[i] > 0){des = map[i] % 10; }
            else{des = (-map[i]) /10%10;}
        }
        if(judgeifBozi(map[i])){bozi_idx = i;}//此格是否为脖子
    }
    daoju_nums = judgeDaojuNums(map[bozi_idx]); //根据脖子的数值获得道具数量
    if(daoju_nums > 2){return 4;}//如果拥有的道具超过两个，直接放道具。

    //printf("%d %d %d\n",head_idx,bozi_idx, des);
    int cannotgo[4] = {0}; //使用排除法，记录哪些方向不能走。
    if ((head_idx >= 0 && head_idx < 40) || des == 3){cannotgo[1] = 1;  }//有墙，或此时正往下走，则不能往上走
    if((head_idx >= 40 * 29 && head_idx < 40 * 30 ) || des == 1) {cannotgo[3] = 1; }////有墙，或此时正往上走，则不能往下走
    if ((head_idx % 40 == 0) || des == 2)  {cannotgo[0] = 1; }////有墙，或此时正往右走，则不能往左走
    if((head_idx % 39 == 0 && head_idx > 0) || des == 0)  {cannotgo[2] = 1; } ////有墙，或此时正往左走 ，不能往右走

    for(int i=0; i<4; i++) //选一个能走的方向，走
    {
        if(!cannotgo[i]) return i;
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
