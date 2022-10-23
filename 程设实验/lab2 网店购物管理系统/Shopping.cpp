#include<iostream>
#include<cstring>
#include<fstream>
#include"Shopping.h"
using namespace std;
 
//显示主界面
void Shopping::show()
{
	cout <<"====================================================================================================" << endl;
	cout << "                               ";
	cout<<"\033[34;1m欢迎使用\033[0m"<<"\033[35;1mNJU_SHOPPING\033[0m"<<"\033[36;1m购物系统,\033[0m"<<"\033[33;1m请输入对应操作\033[0m" << endl;
	cout << "====================================================================================================" << endl;
	cout << "\033[33;1m1.用户登录     2.用户注册     3.管理员登录     4.退出系统\033[0m" << endl;
	int n;
	cout << "输入操作：" << endl;
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
			admin_operate(); //直接登入管理员界面便于debug
			break;
		case 9:
			user_operate(0, &all_users[0]);
			break;
		default:
			cout << "\033[31;1m错误的操作指令！\033[0m" << endl;
			break;
		}
		cout << "===========================================================" << endl;
		cout << "\033[33;1m1.用户登录     2.用户注册     3.管理员登录     4.退出系统\033[0m" << endl;
		cout << "输入操作：" << endl;
		cin >> n;
	}
	cout << "\033[33;1m欢迎下次使用！\033[0m" << endl;
}
 
//用户登录界面 附加功能：密码错误提示及次数上限
void Shopping::users_enter()
{
	read_all_the_users(); //读取用户列表
 
	int cnt = 0;
	while (cnt < 3)
	{
		string name, passwd;
		cout << "输入用户名：";
		cin >> name;
		cout << "输入密码：";
		cin >> passwd;
 
		int i;
		for (i = 0; i < user_num; i++)
		{
			if (name == all_users[i].name && passwd == all_users[i].password)
			{
				cout << "*******" << endl;
				cout << "登录成功！" << endl;
				cout << "*******" << endl;
				user_operate(i,&all_users[i]); //传入用户在用户列表中的下标和结构体指针
				break;
			}
		}
		if (i < user_num)
			break;
		else if(i==user_num)
		{
			cnt++;
			cout << "用户名或密码错误，请再次输入用户名与密码，";
			cout << "你还有" << 3 - cnt << "次机会" << endl;
		}
	}
 
	if (cnt == 3)
		cout << "错误次数已达上限，系统关闭！" << endl;
}
 
//用户注册界面 附加功能：已存在的用户名或过短的密码都不符合要求，需要重新输入
void Shopping::users_register()
{
	read_all_the_users(); //读取用户列表
 
	string name, passwd;
	cout << "输入用户名：";
	cin >> name;
	while (true)
	{
		int i;
		for (i = 0; i < user_num; i++)
		{
			if (all_users[i].name == name)
			{
				cout << "用户名已存在，请重新输入！" << endl;
				break;
			}
		}
		if (i == user_num) //合法的用户名
			break;
		else if (i < user_num)
		{
			cout << "输入用户名：";
			cin >> name;
		}
	}
	
	cout << "输入密码：";
	cin >> passwd;
	while (passwd.size() <= 3)
	{
			cout << "密码长度太短，请重新输入！" << endl;
			cout << "输入密码：";
			cin >> passwd;
	}
 
	//新建一个用户
	user_num++;
	all_users[user_num-1].name = name;
	all_users[user_num-1].password = passwd;
	all_users[user_num-1].shopping_car_num = 0;
	write_shopping_car(&all_users[user_num - 1]); //创建购物车文件
 
 
	write_all_the_users(); //写入用户列表
 
	//注册成功并登录
	cout << "***************" << endl;
	cout << "注册成功！登录成功！" << endl;
	cout << "***************" << endl;
	user_operate(user_num-1, &all_users[user_num-1]);//传入用户在用户列表中的下标和结构体指针
 
}
 
//管理员登录界面 附加功能：密码错误提示及次数上限
void Shopping::administrator_enter()
{
	
	int cnt = 0;
	while (cnt < 3)
	{
		cout << "输入管理员ID：";
		string id, passwd;
		cin >> id;
		cout << "输入管理员密码：";
		cin >> passwd;
		if (id == admin_ID && passwd == admin_passwd)
		{
			cout << "*******" << endl;
			cout << "登录成功！" << endl;
			cout << "*******" << endl;
			admin_operate();
			break;
		}
		else
		{
			cnt++;
			cout << "ID或密码错误，请再次输入管理员ID与密码，";
			cout << "你还有" << 3 - cnt << "次机会" << endl;
		}
	}
	if (cnt == 3)
		cout << "错误次数已达上限，系统关闭！" << endl;
}
 
 
//文件相关操作
//读取库存文件
void Shopping::read_all_the_items()
{
	item_num = 0;//先将库存货物种类置为0
 
	ifstream in_file(all_items_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "打开文件错误！" << endl;
	string a, b, c, d, e;
	in_file >> a >> b >> c >> d >> e;//读入文件表头
 
	while (in_file.peek()!=EOF)//读入库存数据
	{
			in_file >> all_items[item_num].ID_1;
			in_file >> all_items[item_num].ID_2;
			in_file >> all_items[item_num].name; 
			in_file >> all_items[item_num].brand;
			in_file >> all_items[item_num].price; 
			in_file >> all_items[item_num].amount;
			if(all_items[item_num].ID_1=='F') //用于规避文件结尾的空白行
				item_num++;
	}
}
 
//写入库存文件
void Shopping::write_all_the_items()
{
	//更新的商品信息写入库存文件
	ofstream out_file(all_items_address, ios::out);
	out_file << "ID" << "	" << "名称" << "	" << "品牌" << "	" << "价格" << "	" << "数量" << endl;
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
 
//读取售货清单
void Shopping::read_the_sales_list()
{
	sale_item_num = 0;//先将售货清单数量置为0
 
	ifstream in_file(sales_list_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "打开文件错误！" << endl;
	string a, b, c, d, e,f;
	in_file >> a >> b >> c >> d >> e>>f; //读入文件表头
 
	while (in_file.peek() != EOF) 
	{
			in_file >> all_sales[sale_item_num].ID_1; 
			in_file >> all_sales[sale_item_num].ID_2;
			in_file >> all_sales[sale_item_num].name;
			in_file >> all_sales[sale_item_num].brand;
			in_file >> all_sales[sale_item_num].price;
			in_file >> all_sales[sale_item_num].amount;
			in_file >> all_sales[sale_item_num].my_user;
			if (all_sales[sale_item_num].ID_1 == 'F') //用于规避文件结尾的空白行
				sale_item_num++;
	}
}
 
//写入售货清单
void Shopping::write_the_sales_list()
{
	//更新的售货清单写入文件
	ofstream out_file(sales_list_address, ios::out);
	out_file << "ID" << "	" << "名称" << "	" << "品牌" << "	" << "价格" << "	" << "数量" <<"	"<<"用户名"<< endl;
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
 
//读取用户列表
void Shopping::read_all_the_users()
{
	user_num = 0;//先将用户数量置为0
 
	ifstream in_file(all_users_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "打开文件错误！" << endl;
	string a, b;
	in_file >> a >> b ; //读入文件表头
 
	while (in_file.peek() != EOF) 
	{
		in_file >> all_users[user_num].name;
		in_file >> all_users[user_num].password;
		if (all_users[user_num].name[0]>='a'&& all_users[user_num].name[0]<='z') //用于规避文件结尾的空白行
			user_num++;
	}
}
 
//写入用户列表
void Shopping::write_all_the_users()
{
	//更新的用户列表写入库存文件
	ofstream out_file(all_users_address, ios::out);
	out_file << "用户名\t"<< "密码\t\t" <<endl;
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
 
//读取收货地址
void Shopping::read_shopping_address()
{
	read_all_the_users(); //先读取用户列表
 
	ifstream in_file(users_shopping_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "打开文件错误！" << endl;
	string a, b;
	in_file >> a >> b; //读入文件表头
 
	while (in_file.peek() != EOF) 
	{
		string name,address;
		in_file >> name >> address;
		for (int i = 0; i < user_num; i++)
			if (name == all_users[i].name) //找到该用户
				all_users[i].address = address; //修改该用户地址
	}
}
 
//写入收货地址
void Shopping::write_shopping_address()
{
	read_all_the_users(); //先读取用户列表
 
	//更新的收货地址写入文件
	ofstream out_file(users_shopping_address, ios::out);
	out_file << "用户名\t" << "收货地址\t\t" << endl;
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
 
//读取用户购物车
void Shopping::read_shopping_car(user* this_user)
{
	this_user->shopping_car_num = 0;//先将购物车商品种类置为0
	string shopping_car_address = "D:\\" + this_user->name + ".txt";//设置购物车文件地址
 
	ifstream in_file(shopping_car_address, ios::in);
	if (in_file.is_open() == 0)
		cout << "打开文件错误！" << endl;
	string a, b, c, d, e;
	in_file >> a >> b >> c >> d >> e; //读入文件表头
 
	while (!in_file.eof()) //读入库存数据
	{
		in_file >> this_user->shopping_car[this_user->shopping_car_num].ID_1;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].ID_2;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].name;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].brand;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].price;
		in_file >> this_user->shopping_car[this_user->shopping_car_num].amount;
		if (this_user->shopping_car[this_user->shopping_car_num].ID_1 == 'F') //用于规避文件结尾的空白行
			this_user->shopping_car_num++;
	}
}
 
//写入用户购物车
void Shopping::write_shopping_car(user* this_user)
{
	//更新的用户购物车写入库存文件
	string shopping_car_address = "D:\\" + this_user->name + ".txt";//设置购物车文件地址
	
	ofstream out_file(shopping_car_address, ios::out);
	if (this_user->shopping_car_num != 0)
	{
		out_file << "ID" << "	" << "名称" << "	" << "品牌" << "	" << "价格" << "	" << "数量"  << endl;
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
 
 
//管理员相关操作
//管理员操作界面
void Shopping::admin_operate()
{
	cout << "=========================================================================================" << endl;
	cout << "\033[33;1m0.注销登录     1.查询商品     2.增加商品     3.删除商品     4.修改产品数量     5.查询售货清单\033[0m" << endl;
	cout << "输入操作：";
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
			cout << "\033[31;1m错误的操作指令！\033[0m" << endl;
			break;
		}
		cout << "=========================================================================================" << endl;
		cout << "\033[33;1m0.注销登录     1.查询商品     2.增加商品     3.删除商品     4.修改产品数量     5.售货清单\033[0m" << endl;
		cout << "输入操作：" << endl;
		cin >> n;
	}
	cout << "退出登录！" << endl;
}
 
//管理员查看商品，先读入库存文件，再进行输出
void Shopping::show_items() 
{
	read_all_the_items(); //读入库存文件
	
	//输出库存商品数据，数量为0的商品也要输出
	if (item_num == 0)
		cout << "当前库存为空！" << endl;
 
	else 
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "名称" << "		" << "品牌" << "		" << "价格" << "		" << "数量" << endl;
		for (int i = 0; i < item_num; i++)
		{
			//输出库存商品信息，通过控制位宽和制表符实现整齐的顺序
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
 
//管理员添加商品，先读入库存文件，再添加商品，最后写入库存文件
void Shopping::add_item()
{
	read_all_the_items();
	
	cout << "请输入要进货的商品ID：";
	string s;
	cin >> s;
 
	//获取新增商品的ID，存入number变量
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
			cout << "新增该商品的数量为：";
			cin >> n;
			all_items[i].amount += n;
			cout << "新增成功！该商品现在的数量为" << all_items[i].amount << endl;
			break;
		}
	}
	if (i == item_num&&item_num<Max_num) //没有找到对应的ID，新建一种商品
	{
		item_num++; //商品种类数+1
 
		all_items[item_num-1].ID_1 = all_items[item_num - 2].ID_1; //开头序号相同
		all_items[item_num-1].ID_2 = all_items[item_num - 2].ID_2+1; //序号编码+1
 
		cout << "库存中没有找到对应ID，将自动新建一种商品，请输入该商品的名称：";
		cin >> all_items[item_num-1].name;
		cout << "请输入该商品的品牌：";
		cin >> all_items[item_num-1].brand;
		cout << "请输入该商品的价格：";
		cin >> all_items[item_num-1].price;
		cout << "请输入该商品的数量：";
		cin >> all_items[item_num-1].amount;
		cout << "添加成功！" << endl;
	}
	
	//更新的商品信息写入库存文件
	write_all_the_items();
}
 
//管理员删除商品，先读入库存文件，再删除商品，最后写入库存文件
void Shopping::delete_item()
{
	read_all_the_items();
 
	cout << "请输入要删除的商品ID：";
	string s;
	cin >> s;
 
	//获取删除商品的ID，存入number变量
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
			cout << "删除成功！" << endl;
			break;
		}
	}
	if (i == item_num) //没有找到对应的ID
		cout << "没有找到对应的商品！" << endl;
 
	//更新的商品信息写入库存文件
	write_all_the_items();
}
 
//管理员修改商品，先读入库存文件，再修改商品信息，最后写入库存文件
void Shopping::change_item()
{
	read_all_the_items();
 
	cout << "请输入要修改的商品ID：";
	string s;
	cin >> s;
 
	//获取修改商品的ID，存入number变量
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
			cout << "请输入要修改的商品信息：1.名称	2.品牌	 3.价格	  4.数量" << endl;
			cout << "请输入操作：";
			int n;
			cin >> n;
			string str;
			switch (n)
			{
			case 1:
				cout << "请输入修改后的名称：";
				cin >> str;
				all_items[i].name = str;
				cout << "修改成功！" << endl;
				break;
			case 2:
				cout << "请输入修改后的品牌：";
				cin >> str;
				all_items[i].brand = str;
				cout << "修改成功！" << endl;
				break;
			case 3:
				cout << "请输入修改后的价格：";
				float x;
				cin >> x;
				all_items[i].price = x;
				if (x < 0)
					cout << "修改失败！价格不能为负！" << endl;
				else
					cout << "修改成功！" << endl;
				break;
			case 4:
				cout << "请输入修改后的数量：";
				int amt;
				cin >> amt;
				all_items[i].amount = amt;
				cout << "修改成功！" << endl;
				break;
			default:
				cout << "错误的操作数！" << endl;
				break;
			}
			break;
		}
	}
	if (i == item_num) //没有找到对应的ID
		cout << "没有找到对应的商品！" << endl;
 
	//更新的商品信息写入库存文件
	write_all_the_items();
}
 
//管理员查询售出清单，先读文件，再合并同类项，最后按照ID升序输出
void Shopping::show_sales_list()
{
	read_the_sales_list(); //读取售货清单
 
	//根据ID冒泡排序
	for(int i=0; i<sale_item_num-1; i++)
		for (int j = 0; j < sale_item_num - i - 1; j++)
		{
			//若前者ID大于后者，结构体内容交换
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
 
	//合并同类项，对于相同的商品将已售数量累加到第一条记录中，其余置为-1
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
		cout << "当前售货清单为空！" << endl;
 
	else
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "名称" << "		" << "品牌" << "		" << "价格" << "		" << "已售数量" << endl;
		for (int i = 0; i < sale_item_num; i++)
		{
			//输出库存商品信息，通过控制位宽和制表符实现整齐的顺序
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
 
 
//用户相关操作
//用户操作界面
void Shopping::user_operate(int index, user* this_user) 
{
	cout << "=========================================================================================" << endl;
	cout << "\033[33;1m1.注销登录     2.查看商品     3.商品搜索     4.添加商品至购物车\033[0m" << endl;
	cout << "\033[33;1m5.删除购物车商品     6.查看购物车     7.结账     8.修改密码	9.管理收货地址\033[0m" << endl;
	cout << "输入操作：";
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
			cout << "\033[31;1m错误的操作指令！\033[0m" << endl;
			break;
		}
		cout << "=========================================================================================" << endl;
		cout << "\033[33;1m1.注销登录     2.查看商品     3.商品搜索     4.添加商品至购物车\033[0m" << endl;
		cout << "\033[33;1m5.删除购物车商品     6.查看购物车     7.结账     8.修改密码	9.管理收货地址\033[0m" << endl;
		cout << "输入操作：" << endl;
		cin >> n;
	}
	cout << "退出登录！" << endl;
}
 
//用户查看商品，读入库存文件，再按要求输出
void Shopping::visit_items()
{
	read_all_the_items(); //读入库存文件
 
	//输出库存商品数据，数量为0的商品不需要输出
	if (item_num == 0)
		cout << "当前库存为空！" << endl;
 
	else
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "名称" << "		" << "品牌" << "		" << "价格" << "		" << "数量" << endl;
		for (int i = 0; i < item_num; i++)
		{
			//输出库存商品信息，通过控制位宽和制表符实现整齐的顺序
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
 
//用户搜索商品 扩展功能：可选择名称+品牌的搜索方式
void Shopping::search_item()
{
	read_all_the_items(); //读取库存
 
	string choice; //选择搜索方式
	cout << "请选择商品搜索方式：1.名称搜索     2.名称+品牌搜索" << endl;
	cout << "请输入商品搜索方式：";
	cin >> choice;
 
	//第一种搜索方式
	if (choice == "1")
	{
		int flag = 0; //表示搜索是否成功
		cout << "请输入商品名称：";
		string name;
		cin >> name;
 
		for (int i = 0; i < item_num; i++)
		{
			if (all_items[i].amount > 0&&all_items[i].name == name) //搜索成功
			{
				if (flag == 0) //如果是搜索到的第一个商品，输出表头
				{
					cout << "********************************************************************************" << endl;
					cout << "ID" << "		" << "名称" << "		" << "品牌" << "		" << "价格" << "		" << "数量" << endl;
					flag = 1;
				}
 
				//输出搜索结果
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
		
		if (flag == 1) //搜索成功，输出表尾
			cout << "********************************************************************************" << endl;
		else //搜索失败，输出提示语
			cout << "未找到该商品，试试换一个词搜索吧！" << endl;
	}
 
	//第二种搜索方式
	else if(choice=="2")
	{
		int flag = 0; //表示搜索是否成功
		cout << "请输入商品名称：";
		string name;
		cin >> name;
		cout << "请输入商品品牌：";
		string brand;
		cin >> brand;
 
		for (int i = 0; i < item_num; i++)
		{
			if (all_items[i].amount > 0&&all_items[i].name == name&& all_items[i].brand == brand) //搜索成功
			{
				if (flag == 0) //如果是搜索到的第一个商品，输出表头
				{
					cout << "********************************************************************************" << endl;
					cout << "ID" << "		" << "名称" << "		" << "品牌" << "		" << "价格" << "		" << "数量" << endl;
					flag = 1;
				}
				
				//输出搜索结果
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
		
		if (flag == 1) //搜索成功，输出表尾
			cout << "********************************************************************************" << endl;
		else //搜索不成功，输出提示语
			cout << "未找到该商品，试试换一个词搜索吧！" << endl;
	}
	
	else
		cout << "\033[31;1m错误的操作指令！\033[0m" << endl;
}
 
//用户添加商品至购物车
void Shopping::add_shopping_car(int index, user* this_user)
{
	read_all_the_items(); //读取库存
	read_shopping_car(this_user); //读取该用户购物车
 
	cout << "输入添加至购物车的商品ID：";
	string id;
	cin >> id;
	//获取新增商品的ID编号，存入number变量
	int number;
	if (id[3] == '0')
		number = id[4] - '0';
	else
		number = (id[4] - '0') + (id[3] - '0') * 10;
 
	cout << "输入添加至购物车的商品数量：";
	int amount;
	cin >> amount;
 
	int i;
	for (i = 0; i < this_user->shopping_car_num; i++)
	{
		if (this_user->shopping_car[i].ID_2 == number)
		{
			int index = 0; //用来记录该商品在购物车中的下标
			for(int j=0;j<item_num;j++)
				if (all_items[j].ID_2 = number)
					index = j;
			
			if (amount > all_items[index].amount)//添加数量超过库存，添加失败
			{
				cout << "添加失败！添加数量超过商品库存，请修改！" << endl;
				break;
			}
			
			else //添加成功 
			{
				this_user->shopping_car[i].amount += amount;
				cout << "***************" << endl;
				cout << "加入购物车成功！" << endl;
				cout << "***************" << endl;
				write_shopping_car(this_user);
				break;
			}	
		}
	}
 
	if (i == this_user->shopping_car_num) //购物车中未找到对应ID
	{
		int j;
		for(j=0;j<item_num;j++)
			if (all_items[j].ID_2 == number) //在库存中找到了对应ID
			{
				if (number > all_items[i].amount) //添加数量超过库存，添加失败
				{
					cout << "添加失败！添加数量超过商品库存，请修改！" << endl;
					break;
				}
				else //添加成功，购物车种类加一
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
					cout << "加入购物车成功！" << endl;
					cout << "***************" << endl;
					break;
				}
			}
		
		if(j==item_num)
		{
			cout << "店铺中没找到该ID对应的商品，请检查是否输入正确！" << endl;
		}
	}
 
	//展示购物车
	cout << "购物车中现在有：" << endl;
	visit_shopping_car(index, this_user);
}
 
//用户删除购物车商品
void Shopping::delete_shopping_car(int index, user* this_user)
{
	read_shopping_car(this_user); //读取该用户购物车
 
	cout << "输入待删除的商品ID：";
	string id;
	cin >> id;
	//获取待删除商品的ID编号，存入number变量
	int number;
	if (id[3] == '0')
		number = id[4] - '0';
	else
		number = (id[4] - '0') + (id[3] - '0') * 10;
 
	cout << "输入待删除商品的数量：";
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
			cout << "删除成功！" << endl;
			cout << "**********" << endl;
			break;
		}
	}
	if(i== this_user->shopping_car_num)
		cout<<"购物车中没有该ID对应的商品，请检查是否输入错误！"<<endl;
	
	//展示购物车
	cout << "购物车中现在有：" << endl;
	visit_shopping_car(index, this_user);
 
}
 
//用户查看购物车，先读取对应的购物车文件再输出
void Shopping::visit_shopping_car(int index, user* this_user)
{
	read_shopping_car(this_user); //读入库存文件
 
	//输出库存商品数据，数量为0的商品也要输出
	if (this_user->shopping_car_num == 0)
		cout << "当前购物车为空！去别处逛逛吧！" << endl;
 
	else
	{
		cout << "********************************************************************************" << endl;
		cout << "ID" << "		" << "名称" << "		" << "品牌" << "		" << "价格" << "		" << "数量" << endl;
		for (int i = 0; i < this_user->shopping_car_num; i++)
		{
			//输出库存商品信息，通过控制位宽和制表符实现整齐的顺序
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
 
//用户结账，需要修改用户购物车、库存和售货清单
void Shopping::check_out(int index, user* this_user)
{
	//读取库存，购物车，收货地址和售货清单
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
			cout << "当前收货地址为空，请设置一个收货地址：";
			cin >> address;
			this_user->address = address;
			write_shopping_address();
			cout << "设置成功！" << endl;
		}
		cout << "当前收货地址为：" << this_user->address << endl;
 
		float money = 0; //待付金额=sum(单价*数量)
		for (int i = 0; i < this_user->shopping_car_num; i++)
			money += this_user->shopping_car[i].price * this_user->shopping_car[i].amount;
 
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
		cout << "\033[31;1m一共需要付款\033[0m" << money << "\033[31;1m元！\033[0m";
		cout << "\033[31;1m确认付款请按1，取消付款请按0，请输入操作：\033[0m";
		int choice;
		cin >> choice;
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
 
		if (choice == 0)
			cout << "已取消付款！" << endl;
 
		else if (choice == 1)
		{
			//修改库存
			for (int i = 0; i < this_user->shopping_car_num; i++)
			{
				int num = this_user->shopping_car[i].ID_2;
				for (int j = 0; j < item_num; j++)
					if (all_items[j].ID_2 == num)
						all_items[j].amount -= this_user->shopping_car[i].amount;
			}
			write_all_the_items();
 
			//修改售货清单
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
 
			//清空用户购物车
			for (int i = 0; i < this_user->shopping_car_num; i++)
				this_user->shopping_car[i].amount = 0;
			write_shopping_car(this_user);
 
			//输出提示语
			cout << "**********" << endl;
			cout << "付款成功！" << endl;
			cout << "**********" << endl;
		}
	}
	
}
 
//拓展功能：用户修改密码
void Shopping::change_password(int index, user* this_user)
{
	cout << "请输入原密码：";
	string old_pass;
	cin >> old_pass;
	
	if (old_pass == this_user->password)
	{
		string new_pass;
		cout << "请输入新密码：";
		cin >> new_pass;
		//设置新密码长度大于三位
		while (new_pass.size() <= 3)
		{
				cout << "密码长度太短，请重新输入！" << endl;
				cout << "输入密码：";
				cin >> new_pass;
		}
		this_user->password = new_pass;
		write_all_the_users();
		cout << "**********" << endl;
		cout << "修改成功！" << endl;
		cout << "**********" << endl;
	}
 
	else
		cout << "密码输入错误，修改失败！" << endl;
}
 
//拓展功能：管理收货地址
void Shopping::change_address(int index, user* this_user)
{
	read_shopping_address(); //读取收货地址
 
	if (this_user->address != "none") //当前地址不为空
	{
		string address;
		cout << "当前的收货地址为：" << this_user->address << endl;
		cout << "修改后的收货地址为：";
		cin >> address;
		this_user->address = address;
		cout << "**********" << endl;
		cout << "修改成功！" << endl;
		cout << "**********" << endl;
	}
	else
	{
		cout << "当前地址为空，请输入你的收货地址：";
		string address;
		cin >> address;
		this_user->address = address;
		cout << "**********" << endl;
		cout << "修改成功！" << endl;
		cout << "**********" << endl;
	}
	write_shopping_address(); //写入文件中
}
 
//完结撒花?