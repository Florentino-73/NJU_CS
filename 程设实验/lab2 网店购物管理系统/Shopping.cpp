#include<iostream>
#include<cstring>
#include<fstream>
#include"Shopping.h"
using namespace std;
 
//��ʾ������
void Shopping::show()
{
	cout <<"====================================================================================================" << endl;
	cout << "                               ";
	cout<<"\033[34;1m��ӭʹ��\033[0m"<<"\033[35;1mNJU_SHOPPING\033[0m"<<"\033[36;1m����ϵͳ,\033[0m"<<"\033[33;1m�������Ӧ����\033[0m" << endl;
	cout << "====================================================================================================" << endl;
	cout << "\033[33;1m1.�û���¼     2.�û�ע��     3.����Ա��¼     4.�˳�ϵͳ\033[0m" << endl;
	int n;
	cout << "���������" << endl;
	cin >> n;
	while (n != 4)
	{
		switch (n)
		{
		case 1:
			users_enter();
			break;
		case 2:
			users_register();
			break;
		case 3:
			administrator_enter();
			break;
		case 8:
			admin_operate(); //ֱ�ӵ������Ա�������debug
			break;
		case 9:
			user_operate(0, &all_users[0]);
			break;
		default:
			cout << "\033[31;1m����Ĳ���ָ�\033[0m" << endl;
			break;
		}
		cout << "===========================================================" << endl;
		cout << "\033[33;1m1.�û���¼     2.�û�ע��     3.����Ա��¼     4.�˳�ϵͳ\033[0m" << endl;
		cout << "���������" << endl;
		cin >> n;
	}
	cout << "\033[33;1m��ӭ�´�ʹ�ã�\033[0m" << endl;
}
 
//�û���¼���� ���ӹ��ܣ����������ʾ����������
void Shopping::users_enter()
{
	read_all_the_users(); //��ȡ�û��б�
 
	int cnt = 0;
	while (cnt < 3)
	{
		string name, passwd;
		cout << "�����û�����";
		cin >> name;
		cout << "�������룺";
		cin >> passwd;
 
		int i;
		for (i = 0; i < user_num; i++)
		{
			if (name == all_users[i].name && passwd == all_users[i].password)
			{
				cout << "*******" << endl;
				cout << "��¼�ɹ���" << endl;
				cout << "*******" << endl;
				user_operate(i,&all_users[i]); //�����û����û��б��е��±�ͽṹ��ָ��
				break;
			}
		}
		if (i < user_num)
			break;
		else if(i==user_num)
		{
			cnt++;
			cout << "�û���������������ٴ������û��������룬";
			cout << "�㻹��" << 3 - cnt << "�λ���" << endl;
		}
	}
 
	if (cnt == 3)
		cout << "��������Ѵ����ޣ�ϵͳ�رգ�" << endl;
}
 
//�û�ע����� ���ӹ��ܣ��Ѵ��ڵ��û�������̵����붼������Ҫ����Ҫ��������
void Shopping::users_register()
{
	read_all_the_users(); //��ȡ�û��б�
 
	string name, passwd;
	cout << "�����û�����";
	cin >> name;
	while (true)
	{
		int i;
		for (i = 0; i < user_num; i++)
		{
			if (all_users[i].name == name)
			{
				cout << "�û����Ѵ��ڣ����������룡" << endl;
				break;
			}
		}
		if (i == user_num) //�Ϸ����û���
			break;
		else if (i < user_num)
		{
			cout << "�����û�����";
			cin >> name;
		}
	}
	
	cout << "�������룺";
	cin >> passwd;
	while (passwd.size() <= 3)
	{
			cout << "���볤��̫�̣����������룡" << endl;
			cout << "�������룺";
			cin >> passwd;
	}
 
	//�½�һ���û�
	user_num++;
	all_users[user_num-1].name = name;
	all_users[user_num-1].password = passwd;
	all_users[user_num-1].shopping_car_num = 0;
	write_shopping_car(&all_users[user_num - 1]); //�������ﳵ�ļ�
 
 
	write_all_the_users(); //д���û��б�
 
	//ע��ɹ�����¼
	cout << "***************" << endl;
	cout << "ע��ɹ�����¼�ɹ���" << endl;
	cout << "***************" << endl;
	user_operate(user_num-1, &all_users[user_num-1]);//�����û����û��б��е��±�ͽṹ��ָ��
 
}
 
//����Ա��¼���� ���ӹ��ܣ����������ʾ����������
void Shopping::administrator_enter()
{
	
	int cnt = 0;
	while (cnt < 3)
	{
		cout << "�������ԱID��";
		string id, passwd;
		cin >> id;
		cout << "�������Ա���룺";
		cin >> passwd;
		if (id == admin_ID && passwd == admin_passwd)
		{
			cout << "*******" << endl;
			cout << "��¼�ɹ���" << endl;
			cout << "*******" << endl;
			admin_operate();
			break;
		}
		else
		{
			cnt++;
			cout << "ID������������ٴ��������ԱID�����룬";
			cout << "�㻹��" << 3 - cnt << "�λ���" << endl;
		}
	}
	if (cnt == 3)
		cout << "��������Ѵ����ޣ�ϵͳ�رգ�" << endl;
}
 
 
//�ļ���ز���
//��ȡ����ļ�
void Shopping::read_all_the_items()
{
	item_num = 0;//�Ƚ�������������Ϊ0
 
	ifstream in_file(all_items_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "���ļ�����" << endl;
	string a, b, c, d, e;
	in_file >> a >> b >> c >> d >> e;//�����ļ���ͷ
 
	while (in_file.peek()!=EOF)//����������
	{
			in_file >> all_items[item_num].ID_1;
			in_file >> all_items[item_num].ID_2;
			in_file >> all_items[item_num].name; 
			in_file >> all_items[item_num].brand;
			in_file >> all_items[item_num].price; 
			in_file >> all_items[item_num].amount;
			if(all_items[item_num].ID_1=='F') //���ڹ���ļ���β�Ŀհ���
				item_num++;
	}
}
 
//д�����ļ�
void Shopping::write_all_the_items()
{
	//���µ���Ʒ��Ϣд�����ļ�
	ofstream out_file(all_items_address, ios::out);
	out_file << "ID" << "	" << "����" << "	" << "Ʒ��" << "	" << "�۸�" << "	" << "����" << endl;
	for (int i = 0; i < item_num; i++)
	{
		out_file << all_items[i].ID_1 << "00";
		if (all_items[i].ID_2 < 10)
			out_file << "0";
		out_file << all_items[i].ID_2 << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_items[i].name << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_items[i].brand << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_items[i].price << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_items[i].amount << "\t";
		out_file << endl;
	}
}
 
//��ȡ�ۻ��嵥
void Shopping::read_the_sales_list()
{
	sale_item_num = 0;//�Ƚ��ۻ��嵥������Ϊ0
 
	ifstream in_file(sales_list_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "���ļ�����" << endl;
	string a, b, c, d, e,f;
	in_file >> a >> b >> c >> d >> e>>f; //�����ļ���ͷ
 
	while (in_file.peek() != EOF) 
	{
			in_file >> all_sales[sale_item_num].ID_1; 
			in_file >> all_sales[sale_item_num].ID_2;
			in_file >> all_sales[sale_item_num].name;
			in_file >> all_sales[sale_item_num].brand;
			in_file >> all_sales[sale_item_num].price;
			in_file >> all_sales[sale_item_num].amount;
			in_file >> all_sales[sale_item_num].my_user;
			if (all_sales[sale_item_num].ID_1 == 'F') //���ڹ���ļ���β�Ŀհ���
				sale_item_num++;
	}
}
 
//д���ۻ��嵥
void Shopping::write_the_sales_list()
{
	//���µ��ۻ��嵥д���ļ�
	ofstream out_file(sales_list_address, ios::out);
	out_file << "ID" << "	" << "����" << "	" << "Ʒ��" << "	" << "�۸�" << "	" << "����" <<"	"<<"�û���"<< endl;
	for (int i = 0; i < sale_item_num; i++)
	{
		out_file << all_sales[i].ID_1 << "00";
		if (all_sales[i].ID_2 < 10)
			out_file << "0";
		out_file << all_sales[i].ID_2 << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_sales[i].name << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_sales[i].brand << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_sales[i].price << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_sales[i].amount << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_sales[i].my_user << "\t";
		out_file << endl;
	}
}
 
//��ȡ�û��б�
void Shopping::read_all_the_users()
{
	user_num = 0;//�Ƚ��û�������Ϊ0
 
	ifstream in_file(all_users_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "���ļ�����" << endl;
	string a, b;
	in_file >> a >> b ; //�����ļ���ͷ
 
	while (in_file.peek() != EOF) 
	{
		in_file >> all_users[user_num].name;
		in_file >> all_users[user_num].password;
		if (all_users[user_num].name[0]>='a'&& all_users[user_num].name[0]<='z') //���ڹ���ļ���β�Ŀհ���
			user_num++;
	}
}
 
//д���û��б�
void Shopping::write_all_the_users()
{
	//���µ��û��б�д�����ļ�
	ofstream out_file(all_users_address, ios::out);
	out_file << "�û���\t"<< "����\t\t" <<endl;
	for (int i = 0; i < user_num; i++)
	{
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_users[i].name << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_users[i].password << "\t";
		out_file << endl;
	}
}
 
//��ȡ�ջ���ַ
void Shopping::read_shopping_address()
{
	read_all_the_users(); //�ȶ�ȡ�û��б�
 
	ifstream in_file(users_shopping_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "���ļ�����" << endl;
	string a, b;
	in_file >> a >> b; //�����ļ���ͷ
 
	while (in_file.peek() != EOF) 
	{
		string name,address;
		in_file >> name >> address;
		for (int i = 0; i < user_num; i++)
			if (name == all_users[i].name) //�ҵ����û�
				all_users[i].address = address; //�޸ĸ��û���ַ
	}
}
 
//д���ջ���ַ
void Shopping::write_shopping_address()
{
	read_all_the_users(); //�ȶ�ȡ�û��б�
 
	//���µ��ջ���ַд���ļ�
	ofstream out_file(users_shopping_address, ios::out);
	out_file << "�û���\t" << "�ջ���ַ\t\t" << endl;
	for (int i = 0; i < user_num; i++)
	{
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_users[i].name << "\t";
		out_file.width(10);
		out_file.setf(ios::left);
		out_file << all_users[i].address << "\t";
		out_file << endl;
	}
}
 
//��ȡ�û����ﳵ
void Shopping::read_shopping_car(user* this_user)
{
	this_user->shopping_car_num = 0;//�Ƚ����ﳵ��Ʒ������Ϊ0
	string shopping_car_address = "D:\\" + this_user->name + ".txt";//���ù��ﳵ�ļ���ַ
 
	ifstream in_file(shopping_car_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "���ļ�����" << endl;
	string a, b, c, d, e;
	in_file >> a >> b >> c >> d >> e; //�����ļ���ͷ
 
	while (!in_file.eof()) //����������
	{
		in_file >> this_user->shopping_car[this_user->shopping_car_num].ID_1;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].ID_2;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].name;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].brand;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].price;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].amount;
		if (this_user->shopping_car[this_user->shopping_car_num].ID_1 == 'F') //���ڹ���ļ���β�Ŀհ���
			this_user->shopping_car_num++;
	}
}
 
//д���û����ﳵ
void Shopping::write_shopping_car(user* this_user)
{
	//���µ��û����ﳵд�����ļ�
	string shopping_car_address = "D:\\" + this_user->name + ".txt";//���ù��ﳵ�ļ���ַ
	
	ofstream out_file(shopping_car_address, ios::out);
	if (this_user->shopping_car_num != 0)
	{
		out_file << "ID" << "	" << "����" << "	" << "Ʒ��" << "	" << "�۸�" << "	" << "����"  << endl;
		for (int i = 0; i < this_user->shopping_car_num; i++)
		{
			out_file << this_user->shopping_car[i].ID_1 << "00";
			if (this_user->shopping_car[i].ID_2 < 10)
				out_file << "0";
			out_file << this_user->shopping_car[i].ID_2 << "\t";
			out_file.width(10);
			out_file.setf(ios::left);
			out_file << this_user->shopping_car[i].name << "\t";
			out_file.width(10);
			out_file.setf(ios::left);
			out_file << this_user->shopping_car[i].brand << "\t";
			out_file.width(10);
			out_file.setf(ios::left);
			out_file << this_user->shopping_car[i].price << "\t";
			out_file.width(10);
			out_file.setf(ios::left);
			out_file << this_user->shopping_car[i].amount << "\t";
			out_file << endl;
		}
	}
}
 
 
//����Ա��ز���
//����Ա��������
void Shopping::admin_operate()
{
	cout << "=========================================================================================" << endl;
	cout << "\033[33;1m0.ע����¼     1.��ѯ��Ʒ     2.������Ʒ     3.ɾ����Ʒ     4.�޸Ĳ�Ʒ����     5.��ѯ�ۻ��嵥\033[0m" << endl;
	cout << "���������";
	int n;
	cin >> n;
	while (n != 0)
	{
		switch (n)
		{
		case 1:
			show_items();
			break;
		case 2:
			add_item();
			break;
		case 3:
			delete_item();
			break;
		case 4:
			change_item();
			break;
		case 5:
			show_sales_list();
			break;
		default:
			cout << "\033[31;1m����Ĳ���ָ�\033[0m" << endl;
			break;
		}
		cout << "=========================================================================================" << endl;
		cout << "\033[33;1m0.ע����¼     1.��ѯ��Ʒ     2.������Ʒ     3.ɾ����Ʒ     4.�޸Ĳ�Ʒ����     5.�ۻ��嵥\033[0m" << endl;
		cout << "���������" << endl;
		cin >> n;
	}
	cout << "�˳���¼��" << endl;
}
 
//����Ա�鿴��Ʒ���ȶ������ļ����ٽ������
void Shopping::show_items() 
{
	read_all_the_items(); //�������ļ�
	
	//��������Ʒ���ݣ�����Ϊ0����ƷҲҪ���
	if (item_num == 0)
		cout << "��ǰ���Ϊ�գ�" << endl;
 
	else 
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "����" << "		" << "Ʒ��" << "		" << "�۸�" << "		" << "����" << endl;
		for (int i = 0; i < item_num; i++)
		{
			//��������Ʒ��Ϣ��ͨ������λ����Ʊ��ʵ�������˳��
			if (all_items[i].amount >= 0||all_items[i].amount==-1)
			{
				cout << all_items[i].ID_1 << "00";
				if (all_items[i].ID_2 < 10)
					cout << "0";
				cout<< all_items[i].ID_2 << "\t\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].name<<"\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].brand << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].price << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].amount << "\t";
				cout << endl;
			}
		}
		cout << "********************************************************************************" << endl;
	}
}
 
//����Ա�����Ʒ���ȶ������ļ����������Ʒ�����д�����ļ�
void Shopping::add_item()
{
	read_all_the_items();
	
	cout << "������Ҫ��������ƷID��";
	string s;
	cin >> s;
 
	//��ȡ������Ʒ��ID������number����
	int number;
	if (s[3] == '0')
		number = s[4] - '0';
	else
		number = (s[4] - '0') + (s[3] - '0') * 10;
	
	int i = 0;
	for(i=0;i<item_num;i++)
	{
		if (all_items[i].ID_2 == number)
		{
			int n;
			cout << "��������Ʒ������Ϊ��";
			cin >> n;
			all_items[i].amount += n;
			cout << "�����ɹ�������Ʒ���ڵ�����Ϊ" << all_items[i].amount << endl;
			break;
		}
	}
	if (i == item_num&&item_num<Max_num) //û���ҵ���Ӧ��ID���½�һ����Ʒ
	{
		item_num++; //��Ʒ������+1
 
		all_items[item_num-1].ID_1 = all_items[item_num - 2].ID_1; //��ͷ�����ͬ
		all_items[item_num-1].ID_2 = all_items[item_num - 2].ID_2+1; //��ű���+1
 
		cout << "�����û���ҵ���ӦID�����Զ��½�һ����Ʒ�����������Ʒ�����ƣ�";
		cin >> all_items[item_num-1].name;
		cout << "���������Ʒ��Ʒ�ƣ�";
		cin >> all_items[item_num-1].brand;
		cout << "���������Ʒ�ļ۸�";
		cin >> all_items[item_num-1].price;
		cout << "���������Ʒ��������";
		cin >> all_items[item_num-1].amount;
		cout << "��ӳɹ���" << endl;
	}
	
	//���µ���Ʒ��Ϣд�����ļ�
	write_all_the_items();
}
 
//����Աɾ����Ʒ���ȶ������ļ�����ɾ����Ʒ�����д�����ļ�
void Shopping::delete_item()
{
	read_all_the_items();
 
	cout << "������Ҫɾ������ƷID��";
	string s;
	cin >> s;
 
	//��ȡɾ����Ʒ��ID������number����
	int number;
	if (s[3] == '0')
		number = s[4] - '0';
	else
		number = (s[4] - '0') + (s[3] - '0') * 10;
 
	int i = 0;
	for (i = 0; i < item_num; i++)
	{
		if (all_items[i].ID_2 == number)
		{
			all_items[i].amount = -1;
			cout << "ɾ���ɹ���" << endl;
			break;
		}
	}
	if (i == item_num) //û���ҵ���Ӧ��ID
		cout << "û���ҵ���Ӧ����Ʒ��" << endl;
 
	//���µ���Ʒ��Ϣд�����ļ�
	write_all_the_items();
}
 
//����Ա�޸���Ʒ���ȶ������ļ������޸���Ʒ��Ϣ�����д�����ļ�
void Shopping::change_item()
{
	read_all_the_items();
 
	cout << "������Ҫ�޸ĵ���ƷID��";
	string s;
	cin >> s;
 
	//��ȡ�޸���Ʒ��ID������number����
	int number;
	if (s[3] == '0')
		number = s[4] - '0';
	else
		number = (s[4] - '0') + (s[3] - '0') * 10;
 
	int i = 0;
	for (i = 0; i < item_num; i++)
	{
		if (all_items[i].ID_2 == number)
		{
			cout << "������Ҫ�޸ĵ���Ʒ��Ϣ��1.����	2.Ʒ��	 3.�۸�	  4.����" << endl;
			cout << "�����������";
			int n;
			cin >> n;
			string str;
			switch (n)
			{
			case 1:
				cout << "�������޸ĺ�����ƣ�";
				cin >> str;
				all_items[i].name = str;
				cout << "�޸ĳɹ���" << endl;
				break;
			case 2:
				cout << "�������޸ĺ��Ʒ�ƣ�";
				cin >> str;
				all_items[i].brand = str;
				cout << "�޸ĳɹ���" << endl;
				break;
			case 3:
				cout << "�������޸ĺ�ļ۸�";
				float x;
				cin >> x;
				all_items[i].price = x;
				if (x < 0)
					cout << "�޸�ʧ�ܣ��۸���Ϊ����" << endl;
				else
					cout << "�޸ĳɹ���" << endl;
				break;
			case 4:
				cout << "�������޸ĺ��������";
				int amt;
				cin >> amt;
				all_items[i].amount = amt;
				cout << "�޸ĳɹ���" << endl;
				break;
			default:
				cout << "����Ĳ�������" << endl;
				break;
			}
			break;
		}
	}
	if (i == item_num) //û���ҵ���Ӧ��ID
		cout << "û���ҵ���Ӧ����Ʒ��" << endl;
 
	//���µ���Ʒ��Ϣд�����ļ�
	write_all_the_items();
}
 
//����Ա��ѯ�۳��嵥���ȶ��ļ����ٺϲ�ͬ��������ID�������
void Shopping::show_sales_list()
{
	read_the_sales_list(); //��ȡ�ۻ��嵥
 
	//����IDð������
	for(int i=0; i<sale_item_num-1; i++)
		for (int j = 0; j < sale_item_num - i - 1; j++)
		{
			//��ǰ��ID���ں��ߣ��ṹ�����ݽ���
			if (all_sales[j].ID_2 > all_sales[j + 1].ID_2)
			{
				int temp1 = all_sales[j].ID_2;
				all_sales[j].ID_2 = all_sales[j + 1].ID_2;
				all_sales[j + 1].ID_2 = temp1;
 
				char temp2 = all_sales[j].ID_1;
				all_sales[j].ID_1 = all_sales[j + 1].ID_1;
				all_sales[j + 1].ID_1 = temp2;
 
				string temp3 = all_sales[j].name;
				all_sales[j].name = all_sales[j + 1].name;
				all_sales[j + 1].name = temp3;
				
				string temp4 = all_sales[j].brand;
				all_sales[j].brand = all_sales[j + 1].brand;
				all_sales[j + 1].brand = temp4;
 
				float temp5 = all_sales[j].price;
				all_sales[j].price = all_sales[j + 1].price;
				all_sales[j + 1].price = temp5;
 
				int temp6 = all_sales[j].amount;
				all_sales[j].amount = all_sales[j + 1].amount;
				all_sales[j + 1].amount = temp6;
				
				string temp7 = all_sales[j].my_user;
				all_sales[j].my_user = all_sales[j + 1].my_user;
				all_sales[j + 1].my_user = temp7;
			}
		}
 
	//�ϲ�ͬ���������ͬ����Ʒ�����������ۼӵ���һ����¼�У�������Ϊ-1
	for (int i = 0; i < sale_item_num - 1; i++)
	{
		if (all_sales[i].amount == -1)
			continue;
		for (int j = i + 1; j < sale_item_num ; j++)
		{
			if (all_sales[j].amount == -1)
				continue;
			if (all_sales[i].ID_2 == all_sales[j].ID_2 && all_sales[i].name == all_sales[j].name && all_sales[i].brand == all_sales[j].brand && all_sales[i].price == all_sales[j].price)
			{
				all_sales[i].amount += all_sales[j].amount;
				all_sales[j].amount = -1;
			}
		}
	}
	if (sale_item_num == 0)
		cout << "��ǰ�ۻ��嵥Ϊ�գ�" << endl;
 
	else
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "����" << "		" << "Ʒ��" << "		" << "�۸�" << "		" << "��������" << endl;
		for (int i = 0; i < sale_item_num; i++)
		{
			//��������Ʒ��Ϣ��ͨ������λ����Ʊ��ʵ�������˳��
			if (all_sales[i].amount > 0)
			{
				cout << all_sales[i].ID_1 << "00";
				if (all_sales[i].ID_2 < 10)
					cout << "0";
				cout << all_sales[i].ID_2 << "\t\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_sales[i].name << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_sales[i].brand << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_sales[i].price << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_sales[i].amount << "\t";
				cout << endl;
			}
		}
		cout << "********************************************************************************" << endl;
	}
}
 
 
//�û���ز���
//�û���������
void Shopping::user_operate(int index, user* this_user) 
{
	cout << "=========================================================================================" << endl;
	cout << "\033[33;1m1.ע����¼     2.�鿴��Ʒ     3.��Ʒ����     4.�����Ʒ�����ﳵ\033[0m" << endl;
	cout << "\033[33;1m5.ɾ�����ﳵ��Ʒ     6.�鿴���ﳵ     7.����     8.�޸�����	9.�����ջ���ַ\033[0m" << endl;
	cout << "���������";
	int n;
	cin >> n;
	write_shopping_address();
	while (n != 1)
	{
		switch (n)
		{
		case 2:
			visit_items();
			break;
		case 3:
			search_item();
			break;
		case 4:
			add_shopping_car(index, this_user);
			break;
		case 5:
			delete_shopping_car(index, this_user);
			break;
		case 6:
			visit_shopping_car(index, this_user);
			break;
		case 7:
			check_out(index, this_user);
			break;
		case 8:
			change_password(index, this_user);
			break;
		case 9:
			change_address(index, this_user);
			break;
		default:
			cout << "\033[31;1m����Ĳ���ָ�\033[0m" << endl;
			break;
		}
		cout << "=========================================================================================" << endl;
		cout << "\033[33;1m1.ע����¼     2.�鿴��Ʒ     3.��Ʒ����     4.�����Ʒ�����ﳵ\033[0m" << endl;
		cout << "\033[33;1m5.ɾ�����ﳵ��Ʒ     6.�鿴���ﳵ     7.����     8.�޸�����	9.�����ջ���ַ\033[0m" << endl;
		cout << "���������" << endl;
		cin >> n;
	}
	cout << "�˳���¼��" << endl;
}
 
//�û��鿴��Ʒ���������ļ����ٰ�Ҫ�����
void Shopping::visit_items()
{
	read_all_the_items(); //�������ļ�
 
	//��������Ʒ���ݣ�����Ϊ0����Ʒ����Ҫ���
	if (item_num == 0)
		cout << "��ǰ���Ϊ�գ�" << endl;
 
	else
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "����" << "		" << "Ʒ��" << "		" << "�۸�" << "		" << "����" << endl;
		for (int i = 0; i < item_num; i++)
		{
			//��������Ʒ��Ϣ��ͨ������λ����Ʊ��ʵ�������˳��
			if (all_items[i].amount > 0)
			{
				cout << all_items[i].ID_1 << "00";
				if (all_items[i].ID_2 < 10)
					cout << "0";
				cout << all_items[i].ID_2 << "\t\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].name << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].brand << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].price << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].amount << "\t";
				cout << endl;
			}
		}
		cout << "********************************************************************************" << endl;
	}
}
 
//�û�������Ʒ ��չ���ܣ���ѡ������+Ʒ�Ƶ�������ʽ
void Shopping::search_item()
{
	read_all_the_items(); //��ȡ���
 
	string choice; //ѡ��������ʽ
	cout << "��ѡ����Ʒ������ʽ��1.��������     2.����+Ʒ������" << endl;
	cout << "��������Ʒ������ʽ��";
	cin >> choice;
 
	//��һ��������ʽ
	if (choice == "1")
	{
		int flag = 0; //��ʾ�����Ƿ�ɹ�
		cout << "��������Ʒ���ƣ�";
		string name;
		cin >> name;
 
		for (int i = 0; i < item_num; i++)
		{
			if (all_items[i].amount > 0&&all_items[i].name == name) //�����ɹ�
			{
				if (flag == 0) //������������ĵ�һ����Ʒ�������ͷ
				{
					cout << "********************************************************************************" << endl;
					cout << "ID" << "		" << "����" << "		" << "Ʒ��" << "		" << "�۸�" << "		" << "����" << endl;
					flag = 1;
				}
 
				//����������
				cout << all_items[i].ID_1 << "00";
				if (all_items[i].ID_2 < 10)
					cout << "0";
				cout << all_items[i].ID_2 << "\t\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].name << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].brand << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].price << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].amount << "\t";
				cout << endl;
			}
		}
		
		if (flag == 1) //�����ɹ��������β
			cout << "********************************************************************************" << endl;
		else //����ʧ�ܣ������ʾ��
			cout << "δ�ҵ�����Ʒ�����Ի�һ���������ɣ�" << endl;
	}
 
	//�ڶ���������ʽ
	else if(choice=="2")
	{
		int flag = 0; //��ʾ�����Ƿ�ɹ�
		cout << "��������Ʒ���ƣ�";
		string name;
		cin >> name;
		cout << "��������ƷƷ�ƣ�";
		string brand;
		cin >> brand;
 
		for (int i = 0; i < item_num; i++)
		{
			if (all_items[i].amount > 0&&all_items[i].name == name&& all_items[i].brand == brand) //�����ɹ�
			{
				if (flag == 0) //������������ĵ�һ����Ʒ�������ͷ
				{
					cout << "********************************************************************************" << endl;
					cout << "ID" << "		" << "����" << "		" << "Ʒ��" << "		" << "�۸�" << "		" << "����" << endl;
					flag = 1;
				}
				
				//����������
				cout << all_items[i].ID_1 << "00";
				if (all_items[i].ID_2 < 10)
					cout << "0";
				cout << all_items[i].ID_2 << "\t\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].name << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].brand << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].price << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << all_items[i].amount << "\t";
				cout << endl;
			}
		}
		
		if (flag == 1) //�����ɹ��������β
			cout << "********************************************************************************" << endl;
		else //�������ɹ��������ʾ��
			cout << "δ�ҵ�����Ʒ�����Ի�һ���������ɣ�" << endl;
	}
	
	else
		cout << "\033[31;1m����Ĳ���ָ�\033[0m" << endl;
}
 
//�û������Ʒ�����ﳵ
void Shopping::add_shopping_car(int index, user* this_user)
{
	read_all_the_items(); //��ȡ���
	read_shopping_car(this_user); //��ȡ���û����ﳵ
 
	cout << "������������ﳵ����ƷID��";
	string id;
	cin >> id;
	//��ȡ������Ʒ��ID��ţ�����number����
	int number;
	if (id[3] == '0')
		number = id[4] - '0';
	else
		number = (id[4] - '0') + (id[3] - '0') * 10;
 
	cout << "������������ﳵ����Ʒ������";
	int amount;
	cin >> amount;
 
	int i;
	for (i = 0; i < this_user->shopping_car_num; i++)
	{
		if (this_user->shopping_car[i].ID_2 == number)
		{
			int index = 0; //������¼����Ʒ�ڹ��ﳵ�е��±�
			for(int j=0;j<item_num;j++)
				if (all_items[j].ID_2 = number)
					index = j;
			
			if (amount > all_items[index].amount)//�������������棬���ʧ��
			{
				cout << "���ʧ�ܣ��������������Ʒ��棬���޸ģ�" << endl;
				break;
			}
			
			else //��ӳɹ� 
			{
				this_user->shopping_car[i].amount += amount;
				cout << "***************" << endl;
				cout << "���빺�ﳵ�ɹ���" << endl;
				cout << "***************" << endl;
				write_shopping_car(this_user);
				break;
			}	
		}
	}
 
	if (i == this_user->shopping_car_num) //���ﳵ��δ�ҵ���ӦID
	{
		int j;
		for(j=0;j<item_num;j++)
			if (all_items[j].ID_2 == number) //�ڿ�����ҵ��˶�ӦID
			{
				if (number > all_items[i].amount) //�������������棬���ʧ��
				{
					cout << "���ʧ�ܣ��������������Ʒ��棬���޸ģ�" << endl;
					break;
				}
				else //��ӳɹ������ﳵ�����һ
				{
					this_user->shopping_car_num++;
					this_user->shopping_car[this_user->shopping_car_num - 1].ID_1 = all_items[j].ID_1;
					this_user->shopping_car[this_user->shopping_car_num - 1].ID_2 = number;
					this_user->shopping_car[this_user->shopping_car_num - 1].name = all_items[j].name;
					this_user->shopping_car[this_user->shopping_car_num - 1].brand = all_items[j].brand;
					this_user->shopping_car[this_user->shopping_car_num - 1].price = all_items[j].price;
					this_user->shopping_car[this_user->shopping_car_num - 1].amount = amount;
					write_shopping_car(this_user);
					cout << "***************" << endl;
					cout << "���빺�ﳵ�ɹ���" << endl;
					cout << "***************" << endl;
					break;
				}
			}
		
		if(j==item_num)
		{
			cout << "������û�ҵ���ID��Ӧ����Ʒ�������Ƿ�������ȷ��" << endl;
		}
	}
 
	//չʾ���ﳵ
	cout << "���ﳵ�������У�" << endl;
	visit_shopping_car(index, this_user);
}
 
//�û�ɾ�����ﳵ��Ʒ
void Shopping::delete_shopping_car(int index, user* this_user)
{
	read_shopping_car(this_user); //��ȡ���û����ﳵ
 
	cout << "�����ɾ������ƷID��";
	string id;
	cin >> id;
	//��ȡ��ɾ����Ʒ��ID��ţ�����number����
	int number;
	if (id[3] == '0')
		number = id[4] - '0';
	else
		number = (id[4] - '0') + (id[3] - '0') * 10;
 
	cout << "�����ɾ����Ʒ��������";
	int amount;
	cin >> amount;
 
	int i;
	for (i = 0; i < this_user->shopping_car_num; i++)
	{
		if (this_user->shopping_car[i].ID_2 == number)
		{
			this_user->shopping_car[i].amount -=amount;
			write_shopping_car(this_user);
			cout << "**********" << endl;
			cout << "ɾ���ɹ���" << endl;
			cout << "**********" << endl;
			break;
		}
	}
	if(i== this_user->shopping_car_num)
		cout<<"���ﳵ��û�и�ID��Ӧ����Ʒ�������Ƿ��������"<<endl;
	
	//չʾ���ﳵ
	cout << "���ﳵ�������У�" << endl;
	visit_shopping_car(index, this_user);
 
}
 
//�û��鿴���ﳵ���ȶ�ȡ��Ӧ�Ĺ��ﳵ�ļ������
void Shopping::visit_shopping_car(int index, user* this_user)
{
	read_shopping_car(this_user); //�������ļ�
 
	//��������Ʒ���ݣ�����Ϊ0����ƷҲҪ���
	if (this_user->shopping_car_num == 0)
		cout << "��ǰ���ﳵΪ�գ�ȥ�𴦹��ɣ�" << endl;
 
	else
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "����" << "		" << "Ʒ��" << "		" << "�۸�" << "		" << "����" << endl;
		for (int i = 0; i < this_user->shopping_car_num; i++)
		{
			//��������Ʒ��Ϣ��ͨ������λ����Ʊ��ʵ�������˳��
			if (this_user->shopping_car[i].amount > 0)
			{
				cout << this_user->shopping_car[i].ID_1 << "00";
				if (this_user->shopping_car[i].ID_2 < 10)
					cout << "0";
				cout << this_user->shopping_car[i].ID_2 << "\t\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << this_user->shopping_car[i].name << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << this_user->shopping_car[i].brand << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << this_user->shopping_car[i].price << "\t";
				cout.width(10);
				cout.setf(ios::left);
				cout << this_user->shopping_car[i].amount << "\t";
				cout << endl;
			}
		}
		cout << "********************************************************************************" << endl;
	}
}
 
//�û����ˣ���Ҫ�޸��û����ﳵ�������ۻ��嵥
void Shopping::check_out(int index, user* this_user)
{
	//��ȡ��棬���ﳵ���ջ���ַ���ۻ��嵥
	read_all_the_items();
	read_shopping_car(this_user);
	read_the_sales_list();
	read_shopping_address();
 
	visit_shopping_car(index, this_user);
	
	if (this_user->shopping_car_num > 0)
	{
		if (this_user->address == "none")
		{
			string address;
			cout << "��ǰ�ջ���ַΪ�գ�������һ���ջ���ַ��";
			cin >> address;
			this_user->address = address;
			write_shopping_address();
			cout << "���óɹ���" << endl;
		}
		cout << "��ǰ�ջ���ַΪ��" << this_user->address << endl;
 
		float money = 0; //�������=sum(����*����)
		for (int i = 0; i < this_user->shopping_car_num; i++)
			money += this_user->shopping_car[i].price * this_user->shopping_car[i].amount;
 
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
		cout << "\033[31;1mһ����Ҫ����\033[0m" << money << "\033[31;1mԪ��\033[0m";
		cout << "\033[31;1mȷ�ϸ����밴1��ȡ�������밴0�������������\033[0m";
		int choice;
		cin >> choice;
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
 
		if (choice == 0)
			cout << "��ȡ�����" << endl;
 
		else if (choice == 1)
		{
			//�޸Ŀ��
			for (int i = 0; i < this_user->shopping_car_num; i++)
			{
				int num = this_user->shopping_car[i].ID_2;
				for (int j = 0; j < item_num; j++)
					if (all_items[j].ID_2 == num)
						all_items[j].amount -= this_user->shopping_car[i].amount;
			}
			write_all_the_items();
 
			//�޸��ۻ��嵥
			for (int i = 0; i < this_user->shopping_car_num; i++)
			{
				sale_item_num++;
				all_sales[sale_item_num - 1].ID_1 = this_user->shopping_car[i].ID_1;
				all_sales[sale_item_num - 1].ID_2 = this_user->shopping_car[i].ID_2;
				all_sales[sale_item_num - 1].name = this_user->shopping_car[i].name;
				all_sales[sale_item_num - 1].brand = this_user->shopping_car[i].brand;
				all_sales[sale_item_num - 1].price = this_user->shopping_car[i].price;
				all_sales[sale_item_num - 1].amount = this_user->shopping_car[i].amount;
				all_sales[sale_item_num - 1].my_user = this_user->name;
			}
			write_the_sales_list();
 
			//����û����ﳵ
			for (int i = 0; i < this_user->shopping_car_num; i++)
				this_user->shopping_car[i].amount = 0;
			write_shopping_car(this_user);
 
			//�����ʾ��
			cout << "**********" << endl;
			cout << "����ɹ���" << endl;
			cout << "**********" << endl;
		}
	}
	
}
 
//��չ���ܣ��û��޸�����
void Shopping::change_password(int index, user* this_user)
{
	cout << "������ԭ���룺";
	string old_pass;
	cin >> old_pass;
	
	if (old_pass == this_user->password)
	{
		string new_pass;
		cout << "�����������룺";
		cin >> new_pass;
		//���������볤�ȴ�����λ
		while (new_pass.size() <= 3)
		{
				cout << "���볤��̫�̣����������룡" << endl;
				cout << "�������룺";
				cin >> new_pass;
		}
		this_user->password = new_pass;
		write_all_the_users();
		cout << "**********" << endl;
		cout << "�޸ĳɹ���" << endl;
		cout << "**********" << endl;
	}
 
	else
		cout << "������������޸�ʧ�ܣ�" << endl;
}
 
//��չ���ܣ������ջ���ַ
void Shopping::change_address(int index, user* this_user)
{
	read_shopping_address(); //��ȡ�ջ���ַ
 
	if (this_user->address != "none") //��ǰ��ַ��Ϊ��
	{
		string address;
		cout << "��ǰ���ջ���ַΪ��" << this_user->address << endl;
		cout << "�޸ĺ���ջ���ַΪ��";
		cin >> address;
		this_user->address = address;
		cout << "**********" << endl;
		cout << "�޸ĳɹ���" << endl;
		cout << "**********" << endl;
	}
	else
	{
		cout << "��ǰ��ַΪ�գ�����������ջ���ַ��";
		string address;
		cin >> address;
		this_user->address = address;
		cout << "**********" << endl;
		cout << "�޸ĳɹ���" << endl;
		cout << "**********" << endl;
	}
	write_shopping_address(); //д���ļ���
}
 
//�������?