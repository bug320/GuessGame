#include <iostream>
#include <strstream>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <iomanip>
#include <time.h>
#include "TableDesign.h"

typedef char TYPE;
typedef void (*FUNC)(TYPE);
typedef TableDesign<TYPE,FUNC>TTD;

const std::string start_info=  "游戏开始，数字已生成!!! "
               "按数字键录入数字 "
               "按P键提交猜想, "
               "按C键清空输入 "
               "按B键清除最后一位数字 "
               "按Q键退出游戏 "
               "请按任意键开始游戏 ";




///全局量
const int AIM_SIZE=4;
const int TIME_SIZE=7;
std::vector<char>_Aim;
std::vector<char>_Guess;
int _A=-1,_B=-1;
bool _bRun=false;
int _leftTime=TIME_SIZE;
///
bool _showAim=false;
bool init();///初始化游戏参数
void Add(int );///添加表
TYPE input();///获取出入
std::string check();///检查结果
void randAim();///随机产生目标数
bool &Running(){
	return _bRun;
}
int& Time(){
	return _leftTime;
}
void getAB(){//to do
    _A=0;
    _B=0;
    int i,j;
    for (i=j=0;i<AIM_SIZE;++i,++j)
        if (_Aim[i]==_Guess[i]) _A++;
    for (i=0;i<AIM_SIZE;++i){
        for (j=0;j<AIM_SIZE;j++){
            if (i!=j){
                if (_Aim[i]==_Guess[j]) {
                    _B++;
                    break;
                }
            }
        }
    }
}

void make_num(TYPE i){//处理数字输入
	if (_Guess.size()<AIM_SIZE)
		_Guess.push_back(i);
}
void make_quit(TYPE i){//处理退出输入
	Running()=false;
}
void make_post(TYPE i){//处理提交输入
	if (_Guess.size()==AIM_SIZE){
		--Time();
		getAB();
		_Guess.clear();
	}else{
		// do nothing
	}
}
void make_clear(TYPE i){//全清所有输入
	if (!_Guess.empty())
		_Guess.clear();
}
void make_back(TYPE i){//处理清理末一位输入
	if (!_Guess.empty())
	_Guess.pop_back();
}

std::string makeInfo(){

        std::strstream sout;
	    std::string output;

        sout<<"剩余回合数："<<_leftTime<<std::ends;
        sout<<std::ends<<"您的输入为："<<std::ends;
        if (!_Guess.empty()){


			for (std::vector<TYPE>::iterator it=_Guess.begin();it!=_Guess.end();it++)
			{
				sout<<*it;
			}
		}

        for (int i=0;i<AIM_SIZE-_Guess.size();++i)
            sout<<".";

        sout<<std::ends<<"A="<<_A<<",B="<<_B<<std::ends;
        sout>>output;

        return output;

}
std::string makeInfoEnd(){
std::strstream sout;
	std::string output;

    sout<<std::ends<<"目标数：";
    for (std::vector<TYPE>::iterator it=_Aim.begin();it!=_Aim.end();it++)
    {
        sout<<*it;
    }
    sout>>output;
    return output;
}
/*Mian*/
int main(){

	if (false==init())
	{
		std::cout<<"The Game initizates failed";
		exit(-1);

	}

    Add(0);
    std::cout<<start_info;
	while (Running()&&Time()>0)
	{
		TYPE ch=input();
		FUNC pfunc=TTD::instance()->pFunc(ch);
		if (NULL!=pfunc){
			pfunc(ch);
		}
        system("CLS");
        std::cout<<makeInfo();
        std::cout<<std::endl;
		std::string chInfo=check();
		if ("NULL"!=chInfo)
            std::cout<<chInfo;
	}//while

    std::cout<<std::endl;
	std::cout<<makeInfoEnd();

	return 0;
}
/*初始化*/
bool init(){
	_A=-1;
	_B=-1;
	randAim();
	_bRun=true;
	_showAim=false;
	return true;
}
/*获取输入*/
TYPE input(){
	TYPE chtmp;
	chtmp=getch();
	return chtmp;
}
/*检查*/
std::string check(){
	if (AIM_SIZE==_A&&0==_B){
        Running()=false;
		return std::string("YOU WINNER!");
	}
	if (Time()<=0){
        Running()=false;
		return "TIME OVER";
    }
	if (!Running()){
		return "GAME OVER";
	}
	return "NULL";
}
/*产生随机数*/
void randAim(){/*to do */
    size_t tm=time(0);
    if (!_Aim.empty())
        _Aim.clear();

   //产生第一位
    srand(tm);
    int tp=rand()%10;
    if (0==tp) ++tp;
    _Aim.push_back(tp+'0');

    //std::cout<<_Aim[0]<<" "<<(char)(tp+'0')<<std::endl;

    //产生第二位
    srand(tm+tp*100);
    do{
        tp=rand()%10;
        //std::cout<<tp;
    }while ((tp+'0')==_Aim[0]);
    _Aim.push_back(tp+'0');
    //std::cout<<tp<<std::endl;

    //产生第三位
    srand(tm+tp*100);
    do{
        tp=rand()%10;

    }while (((tp+'0')==_Aim[0])||((tp+'0')==_Aim[1]));
    _Aim.push_back((tp+'0'));
    //std::cout<<tp<<std::endl;

    //产生第四位
    srand(tm+tp*100);
    do{
        tp=rand()%10;
    }while (((tp+'0')==_Aim[0])||((tp+'0')==_Aim[1])||((tp+'0')==_Aim[2]));
    _Aim.push_back((tp+'0'));
    //std::cout<<tp<<std::endl;

    //std::cout<<std::endl;

    //for (std::vector<TYPE>::iterator it=_Aim.begin();it!=_Aim.end();it++)
    //{
    //   std::cout<<*it<<std::endl;
    //}

}///[
void Add(int event_size){//todo
	TTD::instance()->add('q',make_quit);
	TTD::instance()->add('Q',make_quit);
	TTD::instance()->add('c',make_clear);
	TTD::instance()->add('C',make_clear);
	TTD::instance()->add('B',make_back);
	TTD::instance()->add('b',make_back);
	TTD::instance()->add('p',make_post);
	TTD::instance()->add('Q',make_post);
	for (char i='0';i<='9';++i)
		TTD::instance()->add(char(i),make_num);
}
