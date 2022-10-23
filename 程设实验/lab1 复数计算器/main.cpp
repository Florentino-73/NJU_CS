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
	cout << "复数计算器 by swb" << endl;
	cout << "基础运算请输入1，附加运算请输入2，结束运算请输入quit：" << endl;
	cout << "--------------------------------------------------" << endl;
	cin >> t;
	
	while (true)                      //对t分类讨论，创建UI界面的主菜单(详细说明见PART2)
	{
		if (t == "1")
		{
			cout << "请输入你要计算的表达式：" << endl;
			cin >> t;
			int flag=cs.get(t);
			if (flag)
			{
				cs.calculate();
				cout << "计算结果为(保留六位小数)：";
				cs.print_ans(cs.ans);
				cs.clear();
			}
			else
			{
				cout << "表达式输入有误！请重新输入！" << endl;
			}
			cout << endl;
			cout << "基础运算请输入1，附加运算请输入2，结束运算请输入quit：" << endl;
			cout << "--------------------------------------------------" << endl;
		}
		else if (t == "2")
		{
			cout << "求复数间距离请输入1，求一元二次方程的根请输入2：" << endl;
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

			cout << "基础运算请输入1，附加运算请输入2，结束运算请输入quit：" << endl;
			cout << "--------------------------------------------------" << endl;
		}
		else if (t == "quit")
			break;
		else
		{
			cout << "输入错误！请重新输入" << endl;
		}
		cin >> t;
	}	
	cout << "退出程序，欢迎下次使用！" << endl;
	return 0;
}
