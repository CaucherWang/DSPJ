#ifndef TRAVELMAP_H_
#define TRAVELMAP_H
#include<iostream>
#include<queue>
#include<string>
#include <stack>
#include<fstream>
#include<vector>
using namespace std;

struct Time
{
	int hour;
	int minutes;

	Time() {  hour = 0; minutes = 0; }
	Time(int a, int b) { hour = a; minutes = b; }

	friend bool operator==(const Time & a,const Time & b) { return b.hour == a.hour&&b.minutes == a.minutes; }
	friend bool operator>=(const Time & a,const Time & b) { return a > b || a == b; }
	friend bool operator<(const Time & b,const Time & a) { return b.hour < a.hour || (b.hour == a.hour&&b.minutes < a.minutes); }
	friend bool operator>(const Time & a,const Time & b){ return b<a; }
	friend bool operator<=(const Time & a, const Time & b) { return a < b || a == b; }
	void operator=(Time & b)
	{
		hour = b.hour;
		minutes = b.minutes;
	}

	friend Time & operator+(const Time & a, const Time & b) 
	{
		int total=   (b.hour + a.hour) * 60 + a.minutes + b.minutes;
		Time * p= new Time;
		p->hour = total / 60;
		p->minutes = total % 60;
		return *p;
	}
	friend Time & operator-(const Time & a, const Time & b)
	{
		Time *p = new Time;
		if (a >= b)
		{
			p->hour = a.hour - b.hour;
			if (a.minutes >= b.minutes)
				p->minutes = a.minutes - b.minutes;
			else
			{
				p->hour--;
				p->minutes = a.minutes + 60 - b.minutes;
			}
		}
		else
		{
			Time temp;
			temp.hour = a.hour + 24;
			temp.minutes = a.minutes;
			*p = temp - b;
		}
		return *p;
	}
};

const Time One_Day = { 24,0 };

struct Station
{
	bool start_day;	//0�����������1������ճ���
	int station_pos;
	Time start_time, arrive_time, duration;
	string number;
	double price;

	Station() { start_day = 0; station_pos = -1; price = 0; }
};

class TravelMap;

class City;

class Road
{
	friend class City;
	friend class TravelMap;
private:
	int ter_num;			//��ʾ�����������
	Time start_time, arrive_time, duration;		//�����εķ���ʱ�䣬����ʱ�䣬����ʱ��
	const string number;			//�������
	double price;			//��Ʊ��
	Road * next;
public:
	Road(int a,Time & b,Time & c,Time & d,const string & e,double f, Road *g=nullptr)
		:ter_num(a), start_time(b), arrive_time(c), duration(d), number(e), price(f), next(g) {;}
};

class City
{
	friend class TravelMap;
private:
	string name;	//����洢�ڵ��������Ϣ
	Road * adj;			//����洢�ڵ���ڽӱ�
public:
	City(string & a, Road * b = nullptr) :name(a), adj(b) { ; }
};

class TravelMap
{
private:	
	vector<City>Citylist;
	bool Type;		//0������·ͼ��1������ͼ
	int CityPos(string & cityname)const;	//�����������֣����س������
public:
	TravelMap( bool travel_method);		//travel_method��ͨ����,0����𳵣�1����ɻ�
	~TravelMap();

	bool AddCity( string & name);
	bool DestroyCity(string & name);
	void AddRoad();
	bool AddRoad(string & start,string & end,  string & num, 
		Time & start_time,Time & end_time, Time & duration_time, double price);
	void DestroyRoad();
	bool DestroyRoad(string & start, string & end);	//����㵽�յ�Ͽ�����·
	bool DestroyRoad(string & start,string & end, string & num);//������㡢�յ㡢����ɾ��һ��·
	bool DestroyRoad(string & start, string & end, Time & t);//�������,�յ㣬����ʱ��ɾ��һ��·
	
	void Display_city();
	void Display_road();
	int Lowest_Price_Road(string & start, string & end, Time & start_time)const;
	int Least_Time_Road(string & start, string & end, Time & start_time)const;
};

#endif