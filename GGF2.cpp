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

const std::string start_info=  "��Ϸ��ʼ������������!!! "
               "�����ּ�¼������ "
               "��P���ύ����, "
               "��C��������� "
               "��B��������һλ���� "
               "��Q���˳���Ϸ "
               "�밴�������ʼ��Ϸ ";




///ȫ����
const int AIM_SIZE=4;
const int TIME_SIZE=7;
std::vector<char>_Aim;
std::vector<char>_Guess;
int _A=-1,_B=-1;
bool _bRun=false;
int _leftTime=TIME_SIZE;
///
bool _showAim=false;
bool init();///��ʼ����Ϸ����
void Add(int );///��ӱ�
TYPE input();///��ȡ����
std::string check();///�����
void randAim();///�������Ŀ����
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

void make_num(TYPE i){//������������
	if (_Guess.size()<AIM_SIZE)
		_Guess.push_back(i);
}
void make_quit(TYPE i){//�����˳�����
	Running()=false;
}
void make_post(TYPE i){//�����ύ����
	if (_Guess.size()==AIM_SIZE){
		--Time();
		getAB();
		_Guess.clear();
	}else{
		// do nothing
	}
}
void make_clear(TYPE i){//ȫ����������
	if (!_Guess.empty())
		_Guess.clear();
}
void make_back(TYPE i){//��������ĩһλ����
	if (!_Guess.empty())
	_Guess.pop_back();
}

std::string makeInfo(){

        std::strstream sout;
	    std::string output;

        sout<<"ʣ��غ�����"<<_leftTime<<std::ends;
        sout<<std::ends<<"��������Ϊ��"<<std::ends;
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

    sout<<std::ends<<"Ŀ������";
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
/*��ʼ��*/
bool init(){
	_A=-1;
	_B=-1;
	randAim();
	_bRun=true;
	_showAim=false;
	return true;
}
/*��ȡ����*/
TYPE input(){
	TYPE chtmp;
	chtmp=getch();
	return chtmp;
}
/*���*/
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
/*���������*/
void randAim(){/*to do */
    size_t tm=time(0);
    if (!_Aim.empty())
        _Aim.clear();

   //������һλ
    srand(tm);
    int tp=rand()%10;
    if (0==tp) ++tp;
    _Aim.push_back(tp+'0');

    //std::cout<<_Aim[0]<<" "<<(char)(tp+'0')<<std::endl;

    //�����ڶ�λ
    srand(tm+tp*100);
    do{
        tp=rand()%10;
        //std::cout<<tp;
    }while ((tp+'0')==_Aim[0]);
    _Aim.push_back(tp+'0');
    //std::cout<<tp<<std::endl;

    //��������λ
    srand(tm+tp*100);
    do{
        tp=rand()%10;

    }while (((tp+'0')==_Aim[0])||((tp+'0')==_Aim[1]));
    _Aim.push_back((tp+'0'));
    //std::cout<<tp<<std::endl;

    //��������λ
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
