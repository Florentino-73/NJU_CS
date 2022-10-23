//calculator.cpp
#include<cmath>
#include<string>
#include<cstring>
#include<iostream>
#include<iomanip>
#include"calculator.h"
using namespace std;

//操作符的优先级，依次为：左括号、右括号、加、减、乘、除、乘方
const int calculator::priority[7] = { 666,666,0,0,1,1,2 }; 

calculator::calculator()
{
	clear();
}

bool calculator::get(string t)
{
	int cnt = 0;	//括号数
	int length = t.size();
	//依次处理字符
	for (int i = 0; i < length; i++)
	{
		//处理完一个元素后，i 指向元素末尾
		//把一个复数拆成一个实数加一个纯虚数
		
		//负数（当负号前面不是一个数字时，既判定为负数）
		if ((i==0&&t[i]=='-')||(t[i] == '-' && i>0 && (t[i - 1] < '0' || t[i - 1] > '9')))
		{
			i++;
			//处理实数
			if (t[i] >= '0' && t[i] <= '9')
			{
				all_element[element_num].type = false;
				double tsum = 0;
				int p1 = 10;	         //整数部分的权
				double p2 = 0.1;   //小数部分的权
				do
				{
					tsum = tsum * p1 + t[i] - '0';
					i++;
				} while (t[i] >= '0' && t[i] <= '9');
				if (t[i] == '.')
				{
					i++;
					do
					{
						tsum+= (t[i] - '0') * p2;
						p2 *= 0.1;
						i++;
					} while (t[i] >= '0' && t[i] <= '9');
				}
				all_element[element_num].real = -tsum;
				i--;
			}

			//处理虚数
			else
			{
				all_element[element_num].type = false;
				i++;
				double tsum = 0;
				int p1 = 10;	      //整数部分的权
				double p2 = 0.1;//小数部分的权
				do
				{
					tsum = tsum * p1 + t[i] - '0';
					i++;
				} while (t[i] >= '0' && t[i] <= '9');
				if (t[i] == '.')
				{
					i++;
					do
					{
						tsum = tsum + (t[i] - '0') * p2;
						p2 *= 0.1;
						i++;
					} while (t[i] >= '0' && t[i] <= '9');
				}
				all_element[element_num].img = tsum;
				i--;
			}
		}

		else
		{
			//处理实数
			if (t[i] >= '0' && t[i] <= '9')
			{
				all_element[element_num].type = false;
				double tsum = 0;
				int p1 = 10;	//整数部分的权
				double p2 = 0.1;//小数部分的权
				do
				{
					tsum = tsum * p1 + t[i] - '0';
					i++;
				} while (t[i] >= '0' && t[i] <= '9');
				if (t[i] == '.')
				{
					i++;
					do
					{
						tsum = tsum + (t[i] - '0') * p2;
						p2 *= 0.1;
						i++;
					} while (t[i] >= '0' && t[i] <= '9');
				}
				all_element[element_num].real = tsum;
				i--;
			}

			//处理虚数
			else if (t[i] == 'i')
			{
				all_element[element_num].type = false;
				i++;
				double tsum = 0;
				int p1 = 10;	//整数部分的权
				double p2 = 0.1;//小数部分的权
				do
				{
					tsum = tsum * p1 + t[i] - '0';
					i++;
				} while (t[i] >= '0' && t[i] <= '9');
				if (t[i] == '.')
				{
					i++;
					do
					{
						tsum = tsum + (t[i] - '0') * p2;
						p2 *= 0.1;
						i++;
					} while (t[i] >= '0' && t[i] <= '9');
				}
				all_element[element_num].img = tsum;
				i--;
			}

			//处理其他操作
			else
			{
				all_element[element_num].type = true;
				int op_type;
				switch (t[i])
				{
				case '(':
					op_type = 0;
					cnt++;
					break;
				case '（':
					op_type = 0;
					cnt++;
					break;
				case ')':
					op_type = 1;
					cnt++;
					break;
				case '）':
					op_type = 1;
					cnt++;
					break;
				case '+':
					op_type = 2;
					break;
				case '-':
					op_type = 3;
					break;
				case '*':
					op_type = 4;
					break;
				case '/':
					op_type = 5;
					break;
				case '^':
					op_type = 6;
					break;
				default:
					return false;
					break;
				}
				all_element[element_num].op = op_type;
			}
		}

		//显然，现在的元素数量要加一个了
		element_num++;
	}
	p_o_e_num = element_num - cnt;//先序表达式的个数等于总个数减去括号数
	
	//得到中序表达式
	get_m_o_e();
	//得到先序表达式
	get_p_o_e();
	return true;
}

void calculator::print(int choice)
{
	int* p = (choice == 0 ? middel_order_expression : preorder_expression);
	int t = (choice == 0 ? element_num : p_o_e_num);
	for (int i = 0; i < t; i++)
	{
		//如果是操作
		if (all_element[p[i]].type)
		{
			char op_type;
			switch (all_element[p[i]].op)
			{
			case 0:
				op_type = '(';
				break;
			case 1:
				op_type = ')';
				break;
			case 2:
				op_type = '+';
				break;
			case 3:
				op_type = '-';
				break;
			case 4:
				op_type = '*';
				break;
			case 5:
				op_type = '/';
				break;
			case 6:
				op_type = '^';
				break;
			default:
				cout << "error：不合法的操作符！" << endl;
				return;
				break;
			}
			cout << op_type;
		}
		//如果是数字
		else
		{
			//cout 默认输出double的六位小数
			//默认实部或者虚部是0，则不输出实部或虚部
			if (all_element[p[i]].real != 0)
			{
				cout << setprecision(6) << all_element[p[i]].real;
				if (all_element[p[i]].img != 0)
				{
					cout << setprecision(6) << all_element[p[i]].img << "+i";
				}
			}
			else
			{
				if (all_element[p[i]].img != 0)
				{
					cout << setprecision(6) << all_element[p[i]].img << "i";
				}
				else
				{
					cout << '0' ;
				}
			}
		}
	}
	cout << endl;
}

void calculator::calculate()
{
	//calculator::print(0);
	//计算会改变前序表达式和所有元素，所以在计算完再查看元素或表达式就会得到错误结果
	for (int i = p_o_e_num - 1; i >= 0; i--)
	{
		if (all_element[preorder_expression[i]].type)
		{
			all_element[preorder_expression[i]].type = false;	//这个操作的结果存在这
			//下面的式子写的长了一点
			switch (all_element[preorder_expression[i]].op)
			{
			case 2:				// +
				all_element[preorder_expression[i]].real = all_element[stack[stack_num]].real + all_element[stack[stack_num - 1]].real;
				all_element[preorder_expression[i]].img = all_element[stack[stack_num]].img + all_element[stack[stack_num - 1]].img;
				stack_num -= 2;
				break;
			
			case 3:				// -
				all_element[preorder_expression[i]].real = all_element[stack[stack_num]].real - all_element[stack[stack_num - 1]].real;
				all_element[preorder_expression[i]].img = all_element[stack[stack_num]].img - all_element[stack[stack_num - 1]].img;
				stack_num -= 2;
				break;
			
			case 4:				// *
				all_element[preorder_expression[i]].real = all_element[stack[stack_num]].real * all_element[stack[stack_num - 1]].real - all_element[stack[stack_num]].img * all_element[stack[stack_num - 1]].img;
				all_element[preorder_expression[i]].img = all_element[stack[stack_num]].img * all_element[stack[stack_num - 1]].real + all_element[stack[stack_num]].real * all_element[stack[stack_num - 1]].img;
				stack_num -= 2;
				break;
			
			case 5:				// /
				double ttt;  //分母有理化
				ttt = all_element[stack[stack_num - 1]].real * all_element[stack[stack_num - 1]].real + all_element[stack[stack_num - 1]].img * all_element[stack[stack_num - 1]].img;

				all_element[preorder_expression[i]].real = (all_element[stack[stack_num]].real * all_element[stack[stack_num - 1]].real + all_element[stack[stack_num]].img * all_element[stack[stack_num - 1]].img) / ttt;
				all_element[preorder_expression[i]].img = (all_element[stack[stack_num]].img * all_element[stack[stack_num - 1]].real - all_element[stack[stack_num]].real * all_element[stack[stack_num - 1]].img) / ttt;

				stack_num -= 2;
				break;
			
			case 6:             //^
				int n;
				n=int (all_element[stack[stack_num - 1]].real);  //指数;
				
				if (n == 0)
				{
					all_element[preorder_expression[i]].real = 0;
					all_element[preorder_expression[i]].img = 0;
				}
				if (n > 0)
				{
					all_element[preorder_expression[i]].real = all_element[stack[stack_num]].real;
					all_element[preorder_expression[i]].img = all_element[stack[stack_num]].img;
					for (int j = 1; j < n; j++)
					{
						double real_s;
						double img_s;
						
						real_s = all_element[preorder_expression[i]].real * all_element[stack[stack_num]].real - all_element[preorder_expression[i]].img * all_element[stack[stack_num]].img;
						img_s= all_element[preorder_expression[i]].img * all_element[stack[stack_num]].real + all_element[preorder_expression[i]].real * all_element[stack[stack_num]].img;
						
						all_element[preorder_expression[i]].real = real_s;
						all_element[preorder_expression[i]].img = img_s;
					}
				}
				if (n < 0)   //先乘方再取倒数
				{
					all_element[preorder_expression[i]].real = all_element[stack[stack_num]].real;
					all_element[preorder_expression[i]].img = all_element[stack[stack_num]].img;
					for (int j = 1; j < -n; j++)
					{
						double real_s;
						double img_s;

						real_s = all_element[preorder_expression[i]].real * all_element[stack[stack_num]].real - all_element[preorder_expression[i]].img * all_element[stack[stack_num]].img;
						img_s = all_element[preorder_expression[i]].img * all_element[stack[stack_num]].real + all_element[preorder_expression[i]].real * all_element[stack[stack_num]].img;

						all_element[preorder_expression[i]].real = real_s;
						all_element[preorder_expression[i]].img = img_s;
					}
					double ttt;  //分母有理化
					ttt = all_element[preorder_expression[i]].real * all_element[preorder_expression[i]].real + all_element[preorder_expression[i]].img * all_element[preorder_expression[i]].img;
					all_element[preorder_expression[i]].real = all_element[preorder_expression[i]].real / ttt;
					all_element[preorder_expression[i]].img = -all_element[preorder_expression[i]].img / ttt;
				}
				stack_num -= 2;
				break;
			
			default:
				cout << "error" << endl;
				return;
				break;
			}
		}
		stack[++stack_num] = preorder_expression[i];
	}

	ans = all_element[preorder_expression[0]];
}

void calculator::print_ans(element ans)
{
	if (ans.real != 0)
	{
		cout <<fixed<< setprecision(6) << ans.real;
		if (ans.img != 0)
		{
			if (ans.img > 0)
			{
				cout <<"+"<<fixed<< setprecision(6) << ans.img << "i";
			}
			else
			{
				cout <<"-"<<fixed<< setprecision(6) << -ans.img << "i";
			}
		}
	}
	else
	{
		if (ans.img != 0)
		{
			if (ans.img > 0)
			{
				cout <<"+"<< fixed << setprecision(6) << ans.img << "i";
			}
			else
			{
				cout  <<"+"<< fixed << setprecision(6) << -ans.img << "i";
			}
		}
		else
		{
			cout << '0';
		}
	}
	cout << endl;
}

void calculator::clear()
{
	element_num = 0;
	p_o_e_num = 0;
	stack_num = 0;
	ans.type = 0;
	ans.real = 0;
	ans.img = 0;
	memset(all_element, 0, sizeof(all_element));
	memset(middel_order_expression, 0, sizeof(middel_order_expression));
	memset(preorder_expression, 0, sizeof(preorder_expression));
	memset(stack, 0, sizeof(stack));
}

void calculator::get_m_o_e()
{
	//现在的all_element 就是中序表达式
	for (int i = 0; i < element_num; i++)
	{
		middel_order_expression[i] = i;
	}
}

void calculator::get_p_o_e()
{
	/*
	中序表达式转前序表达式步骤
	1、反转输入字符串，如“2*3/(2-1)+3*(4-1)” 反转后为“ )1-4(*3+)1-2(/3*2”，
	2、从字符串中取出下一个字符　　
		2.1.如果是操作数，则直接输出　　
		2.2.如果是“)”，压入栈中　　
		2.3.如果是运算符但不是“(”，“)”,则不断循环进行以下处理　　　　
			2.3.1.如果栈为空，则此运算符进栈，结束此步骤　　　　
			2.3.2.如果栈顶是“)”,则此运算符进栈，结束此步骤　　　　
			2.3.2.如果此运算符与栈顶优先级相同或者更高，此运算符进栈，结束此步骤　　　　
			2.3.4.否则，运算符连续出栈，直到满足上述三个条件之一，然后此运算符进栈　　
		2.4、如果是“(”，则运算符连续出栈，直到遇见“)”为止,将“)”出栈且丢弃之
	3、如果还有更多的字符串，则转到第2步
	4、不在有未处理的字符串了，输出栈中剩余元素
	5、再次反转字符串得到最终结果
	*/
	int t = 0;	//放先序表达式的位置
	for (int i = element_num - 1; i >= 0; i--)
	{
		if (all_element[i].type == false)
		{
			preorder_expression[t] = i;
			t++;
		}
		else if (all_element[i].op == 1)	// ）
		{
			stack[++stack_num] = i;
		}
		else if (all_element[i].op != 0 && all_element[i].op != 1)
		{
			while (1)
			{
				if (stack_num == 0)
				{
					stack[++stack_num] = i;
					break;
				}
				else if (all_element[stack[stack_num]].op == 1)
				{
					stack[++stack_num] = i;
					break;
				}
				else if (Better(all_element[i], all_element[stack[stack_num]]))
				{
					stack[++stack_num] = i;
					break;
				}
				else
				{
					preorder_expression[t] = stack[stack_num];
					--stack_num;
					t++;
				}
			}
		}
		else
		{
			while (stack_num && all_element[stack[stack_num]].op != 1)
			{
				preorder_expression[t] = stack[stack_num];
				--stack_num;
				t++;
			}
			--stack_num;
		}
	}
	while (stack_num > 0)
	{
		preorder_expression[t] = stack[stack_num];
		--stack_num;
		t++;
	}
	int temp;
	for (int i = 0; i <= (p_o_e_num - 1) / 2; i++)
	{
		temp = preorder_expression[i];
		preorder_expression[i] = preorder_expression[p_o_e_num - 1 - i];
		preorder_expression[p_o_e_num - 1 - i] = temp;
	}
}

bool calculator::Better(element a, element b)
{
	return priority[a.op] >= priority[b.op];
}

void calculator::distance() 
{
	element x, y, dis;
	cout << "请分别输入第一个复数的实部和虚部：";
	cin >> x.real >> x.img;
	cout << "第一个复数为：";
	print_ans(x);
	
	cout << "请分别输入第二个复数的实部和虚部：";
	cin >> y.real >> y.img;
	cout << "第二个复数为：";
	print_ans(y);
	
	dis.real = sqrt((x.real - y.real) * (x.real - y.real) + (x.img - y.img) * (x.img - y.img));
	dis.img = 0;

	cout << "计算结果为：";
	print_ans(dis);
}

void calculator::solve()
{
	float a, b, c, x1, x2, delta, real, img;
	cout << "请输入一元二次方程各项系数a,b,c： ";
	cin >> a >> b >> c;
	delta = b * b - 4 * a * c;

	if (delta > 0)
	{
		x1 = (-b + sqrt(delta)) / (2 * a);
		x2 = (-b - sqrt(delta)) / (2 * a);
		cout << "方程有两个不相同的实根：" << endl;
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}

	else if (delta == 0) 
	{
		cout << "方程有两个相同的实根" << endl;
		x1 = (-b /(2 * a));
		cout << "x1 = x2 = " << x1 << endl;
	}

	else 
	{
		real = -b / (2 * a);
		img = sqrt(-delta) / (2 * a);
		cout << "方程有两个不同的虚根：" << endl;
		cout << "x1 = " << real << "+" << img << "i" << endl;
		cout << "x2 = " << real << "-" << img << "i" << endl;
	}

}