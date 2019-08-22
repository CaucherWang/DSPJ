#include "TravelMap.h"

int TravelMap::CityPos(string & cityname)const
{
	for (int i = 0; i < Citylist.size(); ++i)
		if (Citylist[i].name == cityname)	return i;
	return -1;
}

TravelMap::TravelMap(bool travel_method)
{
	Type = travel_method;
	ifstream fin;
	if (travel_method)				//���ݲ�ͬ�Ľ�ͨ��ʽ�򿪲�ͬ���ļ�
		fin.open("flightnet.txt");
	else
		fin.open("railnet.txt");
	string temp;
	getline(fin, temp);			//������һ�б�ͷ

	int hour_t, minute_t, hour_tt, minute_tt, hour_ttt, minute_ttt, t;
	double price_t;
	Time start_t, stop_t, duration_t;
	while (fin.good())
	{
		string number_t, dep_t, dep_tt, ter_t, ter_tt;
		if (!(fin >> number_t))
			break;
		fin >> dep_tt;
		if (travel_method == 0)			//����txt�ļ�ÿ����վ�����ķ�λ��Ҫȥ��������"�Ϻ���"�ĳ�"�Ϻ�"
		{
			t = dep_tt.find("��");
			if (t >= 4)
			{
				for (int i = 0; i < t; ++i)
					dep_t.push_back(dep_tt[i]);
			}
			else if ((t = dep_tt.find("��")) >= 4)
			{
				for (int i = 0; i < t; ++i)
					dep_t.push_back(dep_tt[i]);
			}
			else if ((t = dep_tt.find("��")) >= 4)
			{
				for (int i = 0; i < t; ++i)
					dep_t.push_back(dep_tt[i]);
			}
			else if ((t = dep_tt.find("��")) >= 4)
			{
				for (int i = 0; i < t; ++i)
					dep_t.push_back(dep_tt[i]);
			}
			else dep_t = dep_tt;
		}
		else dep_t = dep_tt;
		if (dep_tt == "������")	dep_t = "����";
		if (dep_tt == "�Ͼ���")	dep_t = "�Ͼ�";
		if (dep_tt == "������")	dep_t = "����";
		if (dep_tt == "������")	dep_t = "����";
		if (dep_tt == "��ݸ��")	dep_t = "��ݸ";


		fin >> hour_t;	fin.get();	fin >> minute_t;
		start_t.hour = hour_t; start_t.minutes = minute_t;
		fin >> ter_tt;
		if (travel_method==0)
		{
			t = ter_tt.find("��");
			if (t >= 4)
			{
				for (int i = 0; i < t; ++i)
					ter_t.push_back(ter_tt[i]);
			}
			else if ((t = ter_tt.find("��")) >= 4)
			{
				for (int i = 0; i < t; ++i)
					ter_t.push_back(ter_tt[i]);
			}
			else if ((t = ter_tt.find("��")) >= 4)
			{
				for (int i = 0; i < t; ++i)
					ter_t.push_back(ter_tt[i]);
			}
			else if ((t = ter_tt.find("��")) >= 4)
			{
				for (int i = 0; i < t; ++i)
					ter_t.push_back(ter_tt[i]);
			}
			else ter_t = ter_tt;
		}
		else ter_t = ter_tt;
		if (ter_tt == "������")	ter_t = "����";
		if (ter_tt == "�Ͼ���")	ter_t = "�Ͼ�";
		if (ter_tt == "������")	ter_t = "����";
		if (ter_tt == "������")	ter_t = "����";
		if (ter_tt == "��ݸ��")	ter_t = "��ݸ";

		fin >> hour_tt;	fin.get();	fin >> minute_tt;
		fin >> hour_ttt;	fin.get();	fin >> minute_ttt;
		fin >> price_t;
		stop_t.hour = hour_tt; stop_t.minutes = minute_tt;
		duration_t = stop_t - start_t;
		if (CityPos(dep_t) == -1)
			AddCity(dep_t);
		if (CityPos(ter_t) == -1)
			AddCity(ter_t);
		AddRoad(dep_t, ter_t, number_t, start_t, stop_t, duration_t, price_t);
		fin.get();
	}
}

TravelMap::~TravelMap()
{
	Road * p;
	for (int i = 0; i < Citylist.size(); ++i)
	{
		p = Citylist[i].adj;
		while (p)
		{
			Citylist[i].adj = p->next;
			delete p;
			p = Citylist[i].adj;
		}
	}
}

bool TravelMap::AddCity( string & name)
{
	if (CityPos(name) == -1)	//ԭ��û�иó��������֮
	{
		Citylist.push_back(name);
		return true;
	}
	else return false;		//ͼ�����иó������޷����
}

bool TravelMap::DestroyCity(string & name)
{
	int des_pos = CityPos(name);
	if (des_pos == -1)	return false;
	Road * p;
	for (int i = 0; i < Citylist.size(); ++i)	//���������г�����ɾȥ�������
	{
		if(i==des_pos)	continue;
		DestroyRoad(Citylist[i].name, name);	//ɾ���������е���ɾ�����е�·��
		p = Citylist[i].adj;
		while (p)
		{
			if (p->ter_num > des_pos)			//���ĳ����·�ߵ��յ���Ų�С�ڱ�ɾ��������ţ������-1
				p->ter_num--;
			p = p->next;
		}
	}
	auto iter = Citylist.begin() + des_pos;		//�ӳ����б�ɾȥname
	Citylist.erase(iter);
	return true;
}

void TravelMap::AddRoad()
{
	cout << endl << endl << endl << endl << endl;
	string  start, end, num;
	Time start_t, end_t, dur;
	double cost;
	cout << "������������·����㣺";
	string temp; int t;
	cin >> temp; cin.get(); start = temp;
	cout << "������������·���յ㣺";
	cin >> temp; cin.get(); end = temp;
	cout << "������������·�ĳ��κ�/����ţ�";
	cin >> temp; cin.get(); num = temp;
	cout << "������������·�ĳ���ʱ�䣨��ʽ��8:45)��";
	cin >> t; cin.get(); start_t.hour = t;
	cin >> t; cin.get(); start_t.minutes = t;
	cout << "������������·�ĵ���ʱ�䣨��ʽ��8:45)��";
	cin >> t; cin.get(); end_t.hour = t;
	cin >> t; cin.get(); end_t.minutes = t;
	dur = end_t - start_t;
	cout << "������Ʊ�ۣ�";
	cin >> cost; cin.get();
	bool tag;
	tag=AddRoad(start, end, num, start_t, end_t, dur,cost);
	if (tag)		cout << "��ӳɹ�!" << endl;
	else	cout << "���в���ʧ��!" << endl;

	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=����������·             **\n";
	cout << "                     **          0=�����ϼ��˵�             **\n";
	cout << "                     ***************************************\n";
	cout << "                                   ���ѡ��";
	int choice;
	cin >> choice;
	if (choice)	AddRoad();
	else
		system("CLS");
}

bool TravelMap::AddRoad(string & start,string & end,string & num, 
	Time & start_time, Time & end_time, Time & duration_time, double price)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	if (start_pos == -1 || end_pos == -1)	return false;
	Road * n= new Road(end_pos, start_time, end_time, duration_time, num, price);
	n->next = Citylist[start_pos].adj;			//��n���뵽�ڽӱ����ĵ�һ��λ��
	Citylist[start_pos].adj = n;
	return true;
}

void TravelMap::DestroyRoad()
{
	cout << endl << endl << endl << endl << endl;
	cout << "\n\n\n\n";
	cout << "                     ****************************************************\n";
	cout << "                     **          1=��ʼ���ء�Ŀ�ĵ�ɾ��                   **\n";
	cout << "                     **          2=��ʼ���ء�Ŀ�ĵء����κ�ɾ��             **\n";
	cout << "                     **          3=��ʼ���ء�Ŀ�ĵء�����ʱ��ɾ��           **\n";
	cout << "                     **          0=�����ϼ��˵�                          **\n";
	cout << "                     ****************************************************\n";
	cout << "                                   ���ѡ��";
	int choice;
	cin >> choice;
	string  start, end, num;
	Time start_t;
	cout << "������ɾ����·����㣺";
	string temp; int t;
	cin >> temp; cin.get(); start = temp;
	cout << "������ɾ����·���յ㣺";
	cin >> temp; cin.get(); end = temp;
	bool t1;
	switch (choice)
	{
	case 0:return;
	case 1:t1=DestroyRoad(start, end); break;
	case 2:	cout << "������ɾ����·�ĳ��κţ�";
		cin >> temp; cin.get(); num = temp;
		t1=DestroyRoad(start, end, num); break;
	case 3:	cout << "������ɾ����·�ĳ���ʱ�䣨��ʽ��8:45)��";
		cin >> t; cin.get(); start_t.hour = t;
		cin >> t; cin.get(); start_t.minutes = t;
		t1=DestroyRoad(start, end, start_t); break;
	}
	if (t1)
		cout << "ɾ���ɹ���" << endl;
	else
		cout << "���в����ڣ�ɾ��ʧ�ܣ�" << endl;

	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=����ɾ����·             **\n";
	cout << "                     **          0=�����ϼ��˵�             **\n";
	cout << "                     ***************************************\n";
	cout << "                                   ���ѡ��";
	int newchoice;
	cin >> newchoice;
	if (newchoice)	DestroyRoad();
	else
		system("CLS");
}

bool TravelMap::DestroyRoad(string & start,string & end)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	if (start_pos == -1 || end_pos == -1)	return false;
	bool tag = false;
	Road * p = Citylist[start_pos].adj, *q;
	while (p&&p->ter_num==end_pos)
	{
		tag = true;
		Citylist[start_pos].adj = p->next;
		delete p;
		p = Citylist[start_pos].adj;
	}
	if (p == nullptr)	return tag;
	q = p; p = p->next;
	while (p)
	{
		if (p->ter_num==end_pos)
		{
			tag = true;
			q->next = p->next;
			delete p;
			p = q->next;
		}
		else
		{
			q = p; p = p->next;
		}
	}
	return tag;
}

bool TravelMap::DestroyRoad(string & start,string & end,string & num)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	if (start_pos == -1 || end_pos == -1)	return false;
	bool tag = false;
	Road * p = Citylist[start_pos].adj, *q;
	while (p && p->number == num&&p->ter_num==end_pos)
	{
		tag = true;
		Citylist[start_pos].adj = p->next;
		delete p;
		p = Citylist[start_pos].adj;
	}
	if (p == nullptr)	return tag;
	q = p; p = p->next;
	while (p)
	{
		if (p->number == num&&p->ter_num==end_pos)
		{
			tag = true;
			q->next = p->next;
			delete p;
			p = q->next;
		}
		else
		{
			q = p; p = p->next;
		}
	}
	return tag;
}

bool TravelMap::DestroyRoad(string & start,string & end, Time & t)
{
	int start_pos = CityPos(start), end_pos = CityPos(end);
	if (start_pos == -1 || end_pos == -1)	return false;
	bool tag = false;
	Road * p = Citylist[start_pos].adj, *q;
	while (p && p->start_time==t&&p->ter_num==end_pos)
	{
		tag = true;
		Citylist[start_pos].adj = p->next;
		delete p;
		p = Citylist[start_pos].adj;
	}
	if (p == nullptr)	return tag;
	q = p; p = p->next;
	while (p)
	{
		if (p->start_time==t&&p->ter_num==end_pos)
		{
			tag = true;
			q->next = p->next;
			delete p;
			p = q->next;
		}
		else
		{
			q = p; p = p->next;
		}
	}
	return tag;
}

void TravelMap::Display_city()
{
	cout << "ALL CITIES ";
	if (Type)	cout << " IN FLIGHTNET:";
	else cout << "IN RAILNET:";
	for (int i = 0; i < 5; ++i)
		cout << endl;
	for (int i = 0; i < 100; ++i)
		cout << '*';
	cout << endl;
	for (int i = 0; i < Citylist.size(); ++i)
	{
		cout << Citylist[i].name << '\t' << '\t';
		if (Citylist[i].name.size() < 8)
			cout << '\t';
		if ((i+1) % 5 == 0)	
			cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 100; ++i)
		cout << '*';
	for (int i = 0; i < 5; ++i)
		cout << endl;
}

void TravelMap::Display_road()
{
	cout << "ALL ROADS:";
	for (int i = 0; i < 5; ++i)
		cout << endl;
	for (int i = 0; i < 100; ++i)
		cout << '*';
	cout << endl;
	cout << "�г���\t\t\t" << "���\t\t" << "�յ�\t\t" << "����ʱ��\t" 
		<< "����ʱ��\t" << ";��ʱ��\t" << "Ʊ��\t" << endl;
	for (int i = 0; i < Citylist.size(); ++i)
	{
		Road * p = Citylist[i].adj;
		while (p)
		{
			cout << p->number << '\t';
			if (p->number.size() < 8)	cout << '\t' << '\t';
			else if (p->number.size() < 16)	cout << '\t';
			cout << Citylist[i].name << '\t';
			if (Citylist[i].name.size() < 8)	cout << '\t';
			cout << Citylist[p->ter_num].name << '\t';
			if (Citylist[p->ter_num].name.size() < 8)	cout << '\t';
			if (p->start_time.hour < 10)	cout << "0";
			cout << p->start_time.hour << "��";
			if (p->start_time.minutes < 10)	cout << "0";
			cout<< p->start_time.minutes << '\t' << "     ";
			if (p->arrive_time < p->start_time)
				cout << "���� ";
			if (p->arrive_time.hour < 10)	cout << "0";
			cout << p->arrive_time.hour << "��";
			if (p->arrive_time.minutes < 10)	cout << "0";
			cout << p->arrive_time.minutes;
			if (!(p->arrive_time < p->start_time))
				cout<< '\t' << "        ";
			else
				cout<< "        ";
			if (p->duration.hour < 10)	cout << "0";
			cout << p->duration.hour << "��";
			if (p->duration.minutes < 10)	cout << "0";
			cout<< p->duration.minutes<<'\t' << "        " << p->price << endl;
			p = p->next;
		}
	}
	for (int i = 0; i < 100; ++i)
		cout << '*';
	cout << endl;
	for (int i = 0; i < 5; ++i)
		cout << endl;
}

int TravelMap::Lowest_Price_Road(string & start, string & end, Time & start_time)const
{
	int start_pos = CityPos(start);
	int end_pos = CityPos(end);
	if (start_pos == -1 || end_pos == -1)	return -1;
	int size = Citylist.size();
	bool * done = new bool[size];
	double * cost = new double[size];
	vector<Station>path(size);

	for (int i = 0; i < size; ++i)
	{
		done[i] = false;
		cost[i] = INT_MAX;
	}
	done[start_pos] = true;
	cost[start_pos] = 0;

	Road * p = Citylist[start_pos].adj;
	while (p)
	{
		Station t;
		t.station_pos = start_pos;
		t.number = p->number;
		t.price = p->price;
		if (p->start_time < start_time)
			t.start_day = 1;
		else
			t.start_day = 0;
		t.arrive_time = p->arrive_time;
		t.duration = p->duration;
		t.start_time = p->start_time;
		
		cost[p->ter_num] = p->price;
		path[p->ter_num] = t;

		p = p->next;
	}

	for (int i = 1; i < size; ++i)
	{
		double min = INT_MAX;
		int index = -1;
		for (int j = 0; j < size; ++j)
			if (!done[j] && cost[j] < min)
			{
				min = cost[j]; 
				index = j;
			}
		if(index==-1)	break;
		done[index] = true;

		Road * p = Citylist[index].adj;
		while (p)
		{
			if (!done[p->ter_num])
			{
				double new_cost = cost[index] + p->price;
				if (new_cost < cost[p->ter_num])
				{
					cost[p->ter_num] = new_cost;
					Station t;
					t.number = p->number;
					t.price = p->price;
					t.arrive_time = p->arrive_time;
					t.start_time = p->start_time;
					t.station_pos = index;
					t.duration = p->duration;
					if (p->start_time < path[index].arrive_time)
						t.start_day = 1;
					else
						t.start_day = 0;
					path[p->ter_num] = t;
				}
			}
			p = p->next;
		}
	}

	if (cost[end_pos] == INT_MAX)	return -2;

	cout << "��  " << start << "  ��  " << end << "  ����ʡǮ·��Ϊ��" << endl;
	stack<string>line;
	line.push(end);
	string tem = end;
	while (tem != start)
	{
		tem = Citylist[path[CityPos(tem)].station_pos].name;
		line.push(tem);
	}
	while (!line.empty())
	{
		tem = line.top(); line.pop();
		if (tem == end)
			cout << "  " << tem << endl;
		else
			cout << "  " << tem << "  ->";
	}

	stack<Station>ss;
	Time total;
	ss.push(path[end_pos]);
	total =total + path[end_pos].duration;
	if (path[end_pos].station_pos == start_pos)	total = total + (path[end_pos].start_time - start_time);
	int pos = path[end_pos].station_pos;
	int latter_pos = end_pos;
	Station st, stt;
	while(pos!=start_pos)
	{
		total = total + path[pos].duration;
		total = total + (path[latter_pos].start_time - path[pos].arrive_time);
		latter_pos = pos;
		if (path[pos].station_pos == start_pos)	total = total + (path[pos].start_time - start_time) ;
		ss.push(path[pos]);
		pos = path[pos].station_pos;
	}
	cout << "�ܼ�Ϊ �� " << cost[end_pos] << endl;
	cout << "��ʱ��Ϊ �� " << total.hour << "ʱ" << total.minutes <<"��"<< endl;
	cout << "������� " << ss.size() << " �˳�,����Ϊ������·��Ϣ�� " << endl;
	cout << endl << "\t\t";
	cout << "�г���\t\t\t" << "���\t\t" << "�յ�\t\t" << "����ʱ��\t\t"
		<< "����ʱ��\t" << ";��ʱ��" << "      Ʊ��\t" << endl;
	int i = 1;
	while(!ss.empty())
	{
		cout << "�� " << i++ << " �ࣺ" << '\t';
		st = ss.top(); ss.pop();
		if (ss.size())
			stt = ss.top();
		else
			stt.station_pos = end_pos;
		cout << st.number << '\t';
		if (st.number.size() < 8)	cout << '\t' << '\t';
		else if (st.number.size() < 16)	cout << '\t';
		cout << Citylist[st.station_pos].name << '\t';
		if (Citylist[st.station_pos].name.size() < 8)	cout << '\t';
		cout << Citylist[stt.station_pos].name << '\t';
		if (Citylist[stt.station_pos].name.size() < 8)	cout << '\t';
		if (st.start_day)
			cout << "���� ";
		else
			cout << "���� ";
		if (st.start_time.hour < 10)	cout << "0";
		cout << st.start_time.hour << "��";
		if (st.start_time.minutes < 10)	cout << "0";
		cout << st.start_time.minutes << "\t\t" ;
		if (st.arrive_time < st.start_time)
			cout << "���� ";
		if (st.arrive_time.hour < 10)	cout << "0";
		cout << st.arrive_time.hour << "��";
		if (st.arrive_time.minutes < 10)	cout << "0";
		cout << st.arrive_time.minutes;		
		if (st.arrive_time < st.start_time)
			cout << "     ";
		else
			cout << "\t       "<<" ";
		if (st.duration.hour < 10)	cout << "0";
		cout <<st.duration.hour << "ʱ";
		if (st.duration.minutes < 10)	cout << "0";
		cout << st.duration.minutes << "��" << "      " << st.price << endl;
	}
	return 0;
}

int TravelMap::Least_Time_Road(string & start, string & end, Time & start_time)const
{
	int start_pos = CityPos(start);
	int end_pos = CityPos(end);
	if (start_pos == -1 || end_pos == -1)	return -1;	//-1������в���ʧ��
	int size = Citylist.size();
	bool * done = new bool[size];
	vector<Time>cost(size);
	vector<Station>path(size);

	for (int i = 0; i < size; ++i)
	{
		done[i] = false;
		cost[i].hour = INT_MAX;
		cost[i].minutes = INT_MAX;
	}
	done[start_pos] = true;
	cost[start_pos].hour = 0;
	cost[start_pos].minutes = 0;

	Road * p = Citylist[start_pos].adj;
	while (p)				//����������ڽӵ����ɶ���ĳ�ʼ������
	{
		Station t;						//p�����Ϊ��վt
		t.station_pos = start_pos;		//t��λ�þ������λ��
		t.number = p->number;			//t�ĳ��κž���p�ĳ��κ�
		t.price = p->price;				
		if (p->start_time < start_time)			//�������ʱ��С�ڳ���ʱ�䣬��ô����Ҫ�Ӻ�һ��
			t.start_day = 1;
		else
			t.start_day = 0;
		t.arrive_time = p->arrive_time;
		t.duration = p->duration;
		t.start_time = p->start_time;
		
		cost[p->ter_num] = (p->start_time - start_time) + p->duration ;  
		//��Ϊû�ж��������ԣ����������Ǳ���ģ�����ʱ��-����ʱ��+������ʻʱ�䣬���ڸýڵ��Ȩ��
		//��Ϊ��ʱ����ļ����й����ⶨ�壬���Բ��ÿ��Ƕ����һ��
		path[p->ter_num] = t;

		p = p->next;
	}

	for (int i = 1; i < size; ++i)
	{
		Time min = { INT_MAX,INT_MAX };
		int index = -1;
		for (int j = 0; j < size; ++j)
			if (!done[j] && cost[j] < min)
			{
				min = cost[j];
				index = j;
			}
		if (index == -1)	break;
		done[index] = true;

		Road * p = Citylist[index].adj;
		while (p)
		{
			if (!done[p->ter_num])
			{
				Time new_cost = cost[index] ;
				new_cost = new_cost + p->duration + (p->start_time - path[index].arrive_time);
				//��Ϊ��ʱ������й��ر�Ķ��壬���Բ��ؿ����Ƿ��һ��
				if (new_cost < cost[p->ter_num])
				{
					cost[p->ter_num] = new_cost;
					Station t;
					t.number = p->number;
					t.price = p->price;
					t.arrive_time = p->arrive_time;
					t.start_time = p->start_time;
					t.station_pos = index;
					t.duration = p->duration;
					if (p->start_time < path[index].arrive_time)
						t.start_day = 1;
					else
						t.start_day = 0;
					path[p->ter_num] = t;
				}
			}
			p = p->next;
		}
	}

	if (cost[end_pos].hour == INT_MAX)	return -2;	//	-2��ʾ���㲻��ͨ

	cout << "��  " << start << "  ��  " << end << "  ����ʡʱ·��Ϊ��" << endl;
	stack<string>line;
	line.push(end);
	string tem = end;
	while (tem != start)
	{
		tem = Citylist[path[CityPos(tem)].station_pos].name;
		line.push(tem);
	}
	while (!line.empty())
	{
		tem = line.top(); line.pop();
		if (tem == end)
			cout << "  " << tem << endl;
		else
			cout << "  " << tem << "  ->";
	}

	stack<Station>ss;
	double total = 0;
	ss.push(path[end_pos]);
	total = total + path[end_pos].price;
	int pos = path[end_pos].station_pos;
	Station st, stt;
	while (pos != start_pos)
	{
		total = total + path[pos].price;
		ss.push(path[pos]);
		pos = path[pos].station_pos;
	}
	cout << "��ʱ��Ϊ �� " << cost[end_pos].hour<<"ʱ"<<cost[end_pos].minutes<<"��" << endl;
	cout << "�ܼ�Ϊ �� " << total << endl;
	cout << "������� " << ss.size() << " �˳�,����Ϊ������·��Ϣ�� " << endl;
	cout << endl << "\t\t";
	cout << "�г���\t\t\t" << "���\t\t" << "�յ�\t\t" << "����ʱ��\t\t"
		<< "����ʱ��\t" << ";��ʱ��" << "      Ʊ��\t" << endl;
	int i = 1;
	while (!ss.empty())
	{
		cout << "�� " << i++ << " �ࣺ" << '\t';
		st = ss.top(); ss.pop();
		if (ss.size())
			stt = ss.top();
		else
			stt.station_pos = end_pos;
		cout << st.number << '\t';
		if (st.number.size() < 8)	cout << '\t' << '\t';
		else if (st.number.size() < 16)	cout << '\t';
		cout << Citylist[st.station_pos].name << '\t';
		if (Citylist[st.station_pos].name.size() < 8)	cout << '\t';
		cout << Citylist[stt.station_pos].name << '\t';
		if (Citylist[stt.station_pos].name.size() < 8)	cout << '\t';
		if (st.start_day)
			cout << "���� ";
		else
			cout << "���� ";
		if (st.start_time.hour < 10)	cout << "0";
		cout << st.start_time.hour << "��";
		if (st.start_time.minutes < 10)	cout << "0";
		cout << st.start_time.minutes << "\t\t";
		if (st.arrive_time < st.start_time)
			cout << "���� ";
		if (st.arrive_time.hour < 10)	cout << "0";
		cout << st.arrive_time.hour << "��";
		if (st.arrive_time.minutes < 10)	cout << "0";
		cout << st.arrive_time.minutes;
		if (st.arrive_time < st.start_time)
			cout << "     ";
		else
			cout << "\t       " << " ";
		if (st.duration.hour < 10)	cout << "0";
		cout << st.duration.hour << "ʱ";
		if (st.duration.minutes < 10)	cout << "0";
		cout << st.duration.minutes << "��" << "      " << st.price << endl;
	}
	return 0;
}
