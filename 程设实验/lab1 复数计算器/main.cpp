//main.cpp
#include<iostream>
#include<cstdlib>
#include<string>
#include"calculator.h"
using namespace std;
int main()
{
	calculator cs;
	string t;
	cout << "���������� by swb" << endl;
	cout << "��������������1����������������2����������������quit��" << endl;
	cout << "--------------------------------------------------" << endl;
	cin >> t;
	
	while (true)                      //��t�������ۣ�����UI��������˵�(��ϸ˵����PART2)
	{
		if (t == "1")
		{
			cout << "��������Ҫ����ı��ʽ��" << endl;
			cin >> t;
			int flag=cs.get(t);
			if (flag)
			{
				cs.calculate();
				cout << "������Ϊ(������λС��)��";
				cs.print_ans(cs.ans);
				cs.clear();
			}
			else
			{
				cout << "���ʽ�����������������룡" << endl;
			}
			cout << endl;
			cout << "��������������1����������������2����������������quit��" << endl;
			cout << "--------------------------------------------------" << endl;
		}
		else if (t == "2")
		{
			cout << "���������������1����һԪ���η��̵ĸ�������2��" << endl;
			cin >> t;
			if (t == "1")
			{
				cs.distance();
				cs.clear();
				cout << endl;
			}
			
			if (t == "2")
			{
				cs.solve();
				cout << endl;
			}

			cout << "��������������1����������������2����������������quit��" << endl;
			cout << "--------------------------------------------------" << endl;
		}
		else if (t == "quit")
			break;
		else
		{
			cout << "�����������������" << endl;
		}
		cin >> t;
	}	
	cout << "�˳����򣬻�ӭ�´�ʹ�ã�" << endl;
	return 0;
}
