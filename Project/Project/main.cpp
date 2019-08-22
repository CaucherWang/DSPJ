#include "TravelMap.h"

void Menu(TravelMap & Train_Map,TravelMap & Plane_Map);
void Main_Function(TravelMap & Train_Map, TravelMap & Plane_Map);
void AddCity(TravelMap & Train_Map, TravelMap & Plane_Map);
void DestroyCity(TravelMap & Train_Map, TravelMap & Plane_Map);
void Display_city(TravelMap & Train_Map, TravelMap & Plane_Map);

int main()
{
	TravelMap Train_Map(0), 
		Plane_Map(1);
	system("color 8B");
	Menu(Train_Map,Plane_Map);
	cout << "Welcome!" << endl;
}

//�˵�����
void Menu(TravelMap & Train_Map, TravelMap & Plane_Map)		
{
	while (1)
	{
		cout << "\n\n\n\n";
		cout << "                     *****************************************\n";
		cout << "                     **          1=����һ������             **\n";
		cout << "                     **          2=����һ���             **\n";
		cout << "                     **          3=����һ��ɻ�             **\n";
		cout << "                     **          4=ɾ��һ������             **\n";
		cout << "                     **          5=ɾ��һ���             **\n";
		cout << "                     **          6=ɾ��һ��ɻ�             **\n";
		cout << "                     **          7=��ʾ���г���             **\n";
		cout << "                     **          8=��ʾ���л�             **\n";
		cout << "                     **          9=��ʾ���зɻ�             **\n";
		cout << "                     **          10=��ѯ���·��            **\n";
		cout << "                     **          0=�˳�                     **\n";
		cout << "                     *****************************************\n";
		cout << "                                   ���ѡ��";
		int choice;
		cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 0:return;
		case 1:AddCity(Train_Map,Plane_Map); break;
		case 2:Train_Map.AddRoad(); break;
		case 3:Plane_Map.AddRoad(); break;
		case 4:DestroyCity(Train_Map,Plane_Map); break;
		case 5:Train_Map.DestroyRoad(); break;
		case 6:Plane_Map.DestroyRoad(); break;
		case 7:Display_city(Train_Map,Plane_Map); break;
		case 8:Train_Map.Display_road(); break;
		case 9:Plane_Map.Display_road(); break;
		case 10:Main_Function(Train_Map,Plane_Map); break;
		default:cout << "�����������������룺"; break;
		}
	}
}

void Main_Function(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	cout << endl << endl << endl << endl << endl;
	cout << "����������أ�";
	string start;
	cin >> start; cin.get();
	cout << "������Ŀ�ĵأ�";
	string end;
	cin >> end; cin.get();
	cout << "��ѡ����з�ʽ��" << endl
		<< "0=��" << endl
		<< "1=�ɻ�" << endl
		<< "���ѡ���ǣ�";
	bool travel_method;
	cin >> travel_method; cin.get();
	cout << "���������ʱ�䣨��ʽ��8:45)��";
	Time start_t; int t;
	cin >> t; cin.get(); start_t.hour = t;
	cin >> t; cin.get(); start_t.minutes = t;
	cout << "��ѡ����в��ԣ�" << endl
		<< "0=��ʡǮ" << endl
		<< "1=��ʡʱ��" << endl
		<< "���ѡ���ǣ�";
	bool strategy; 
	int tag;
	cin >> strategy; cin.get();
	if (travel_method)
	{
		if (strategy)
		{
			tag = Plane_Map.Least_Time_Road(start, end, start_t);
			if(tag==-1)	cout<< "�޴˳��У���ѯʧ��." << endl;
			else if (tag == -2)	cout << "�����м�û�п���·." << endl;
		}
		else
		{
			tag = Plane_Map.Lowest_Price_Road(start, end, start_t);
			if (tag == -1)	cout << "�޴˳��У���ѯʧ��." << endl;
			else if (tag == -2)	cout << "�����м�û�п���·." << endl;
		}
	} 
	else
	{
		if (strategy)
		{
			tag = Train_Map.Least_Time_Road(start, end, start_t);
			if (tag == -1)	cout << "�޴˳��У���ѯʧ��." << endl;
			else if (tag == -2)	cout << "�����м�û�п���·." << endl;
		}
		else
		{
			tag = Train_Map.Lowest_Price_Road(start, end, start_t);
			if (tag == -1)	cout << "�޴˳��У���ѯʧ��." << endl;
			else if (tag == -2)	cout << "�����м�û�п���·." << endl;
		}
	}

	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=������ѯ�����·       **\n";
	cout << "                     **          0=�����ϼ��˵�           **\n";
	cout << "                     ***************************************\n";
	cout << "                                   ���ѡ��";
	int choice;
	cin >> choice;
	if (choice)	Main_Function(Train_Map,Plane_Map);
	else
		system("CLS");
}

void AddCity(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	cout << endl << endl << endl << endl << endl;
	cout << "����Ҫ��ӳ��е������ǣ�";
	string name;
	cin >> name;
	bool t1, t2;
	t1=Train_Map.AddCity(name);
	t2=Plane_Map.AddCity(name);
	if (t1&&t2)
		cout << "��� " << name << " �ɹ�!" << endl;
	else if (t1 && !t2)
		cout << "��·ͼ����Ӵ˳��гɹ�������ͼ�����д˳��У����ʧ�ܡ�" << endl;
	else if (!t1&&t2)
		cout << "����ͼ����Ӵ˳��гɹ�����·ͼ�����д˳��У����ʧ�ܡ�" << endl;
	else
		cout << "�ó����ѳ�������·ͼ�뺽��ͼ�У��޷��ظ���ӡ�" << endl;
	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=�������ӳ���             **\n";
	cout << "                     **          0=�����ϼ��˵�             **\n";
	cout << "                     ***************************************\n";
	cout << "                                   ���ѡ��";
	int choice;
	cin >> choice;
	if (choice)	AddCity(Train_Map,Plane_Map);
	else
		system("CLS");
}

void DestroyCity(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	cout << endl << endl << endl << endl << endl;
	cout << "����Ҫɾ�����е������ǣ�";
	string name;
	cin >> name;
	cin.get();
	bool t1 = Train_Map.DestroyCity(name);
	bool t2 = Plane_Map.DestroyCity(name);
	if (t1&&t2)
		cout << "ɾ�� " << name << " �ɹ���" << endl;
	else if (t1 && !t2)
		cout << "ɾ����·�ɹ����ó���û�л�����" << endl;
	else if (t2 && !t1)
		cout << "ɾ�����߳ɹ����ó���û�л�վ��" << endl;
	else
		cout << "�ó���û�л�վ�ͷɻ�����ɾ��ʧ�ܡ�" << endl;

	cout << "\n\n\n\n";
	cout << "                     ***************************************\n";
	cout << "                     **          1=����ɾ������             **\n";
	cout << "                     **          0=�����ϼ��˵�             **\n";
	cout << "                     ***************************************\n";
	cout << "                                   ���ѡ��";
	int choice;
	cin >> choice;
	if (choice)	DestroyCity(Train_Map,Plane_Map);
	else
		system("CLS");
}

void Display_city(TravelMap & Train_Map, TravelMap & Plane_Map)
{
	Train_Map.Display_city();
	Plane_Map.Display_city();
}
