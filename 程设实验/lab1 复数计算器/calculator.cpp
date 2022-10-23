//calculator.cpp
#include<cmath>
#include<string>
#include<cstring>
#include<iostream>
#include<iomanip>
#include"calculator.h"
using namespace std;

//�����������ȼ�������Ϊ�������š������š��ӡ������ˡ������˷�
const int calculator::priority[7] = { 666,666,0,0,1,1,2 }; 

calculator::calculator()
{
	clear();
}

bool calculator::get(string t)
{
	int cnt = 0;	//������
	int length = t.size();
	//���δ����ַ�
	for (int i = 0; i < length; i++)
	{
		//������һ��Ԫ�غ�i ָ��Ԫ��ĩβ
		//��һ���������һ��ʵ����һ��������
		
		//������������ǰ�治��һ������ʱ�����ж�Ϊ������
		if ((i==0&&t[i]=='-')||(t[i] == '-' && i>0 && (t[i - 1] < '0' || t[i - 1] > '9')))
		{
			i++;
			//����ʵ��
			if (t[i] >= '0' && t[i] <= '9')
			{
				all_element[element_num].type = false;
				double tsum = 0;
				int p1 = 10;	         //�������ֵ�Ȩ
				double p2 = 0.1;   //С�����ֵ�Ȩ
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

			//��������
			else
			{
				all_element[element_num].type = false;
				i++;
				double tsum = 0;
				int p1 = 10;	      //�������ֵ�Ȩ
				double p2 = 0.1;//С�����ֵ�Ȩ
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
			//����ʵ��
			if (t[i] >= '0' && t[i] <= '9')
			{
				all_element[element_num].type = false;
				double tsum = 0;
				int p1 = 10;	//�������ֵ�Ȩ
				double p2 = 0.1;//С�����ֵ�Ȩ
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

			//��������
			else if (t[i] == 'i')
			{
				all_element[element_num].type = false;
				i++;
				double tsum = 0;
				int p1 = 10;	//�������ֵ�Ȩ
				double p2 = 0.1;//С�����ֵ�Ȩ
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

			//������������
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
				case '��':
					op_type = 0;
					cnt++;
					break;
				case ')':
					op_type = 1;
					cnt++;
					break;
				case '��':
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

		//��Ȼ�����ڵ�Ԫ������Ҫ��һ����
		element_num++;
	}
	p_o_e_num = element_num - cnt;//������ʽ�ĸ��������ܸ�����ȥ������
	
	//�õ�������ʽ
	get_m_o_e();
	//�õ�������ʽ
	get_p_o_e();
	return true;
}

void calculator::print(int choice)
{
	int* p = (choice == 0 ? middel_order_expression : preorder_expression);
	int t = (choice == 0 ? element_num : p_o_e_num);
	for (int i = 0; i < t; i++)
	{
		//����ǲ���
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
				cout << "error�����Ϸ��Ĳ�������" << endl;
				return;
				break;
			}
			cout << op_type;
		}
		//���������
		else
		{
			//cout Ĭ�����double����λС��
			//Ĭ��ʵ�������鲿��0�������ʵ�����鲿
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
	//�����ı�ǰ����ʽ������Ԫ�أ������ڼ������ٲ鿴Ԫ�ػ���ʽ�ͻ�õ�������
	for (int i = p_o_e_num - 1; i >= 0; i--)
	{
		if (all_element[preorder_expression[i]].type)
		{
			all_element[preorder_expression[i]].type = false;	//��������Ľ��������
			//�����ʽ��д�ĳ���һ��
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
				double ttt;  //��ĸ����
				ttt = all_element[stack[stack_num - 1]].real * all_element[stack[stack_num - 1]].real + all_element[stack[stack_num - 1]].img * all_element[stack[stack_num - 1]].img;

				all_element[preorder_expression[i]].real = (all_element[stack[stack_num]].real * all_element[stack[stack_num - 1]].real + all_element[stack[stack_num]].img * all_element[stack[stack_num - 1]].img) / ttt;
				all_element[preorder_expression[i]].img = (all_element[stack[stack_num]].img * all_element[stack[stack_num - 1]].real - all_element[stack[stack_num]].real * all_element[stack[stack_num - 1]].img) / ttt;

				stack_num -= 2;
				break;
			
			case 6:             //^
				int n;
				n=int (all_element[stack[stack_num - 1]].real);  //ָ��;
				
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
				if (n < 0)   //�ȳ˷���ȡ����
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
					double ttt;  //��ĸ����
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
	//���ڵ�all_element ����������ʽ
	for (int i = 0; i < element_num; i++)
	{
		middel_order_expression[i] = i;
	}
}

void calculator::get_p_o_e()
{
	/*
	������ʽתǰ����ʽ����
	1����ת�����ַ������硰2*3/(2-1)+3*(4-1)�� ��ת��Ϊ�� )1-4(*3+)1-2(/3*2����
	2�����ַ�����ȡ����һ���ַ�����
		2.1.����ǲ���������ֱ���������
		2.2.����ǡ�)����ѹ��ջ�С���
		2.3.���������������ǡ�(������)��,�򲻶�ѭ���������´���������
			2.3.1.���ջΪ�գ�����������ջ�������˲��衡������
			2.3.2.���ջ���ǡ�)��,����������ջ�������˲��衡������
			2.3.2.������������ջ�����ȼ���ͬ���߸��ߣ����������ջ�������˲��衡������
			2.3.4.���������������ջ��ֱ������������������֮һ��Ȼ����������ջ����
		2.4������ǡ�(�����������������ջ��ֱ��������)��Ϊֹ,����)����ջ�Ҷ���֮
	3��������и�����ַ�������ת����2��
	4��������δ������ַ����ˣ����ջ��ʣ��Ԫ��
	5���ٴη�ת�ַ����õ����ս��
	*/
	int t = 0;	//��������ʽ��λ��
	for (int i = element_num - 1; i >= 0; i--)
	{
		if (all_element[i].type == false)
		{
			preorder_expression[t] = i;
			t++;
		}
		else if (all_element[i].op == 1)	// ��
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
	cout << "��ֱ������һ��������ʵ�����鲿��";
	cin >> x.real >> x.img;
	cout << "��һ������Ϊ��";
	print_ans(x);
	
	cout << "��ֱ�����ڶ���������ʵ�����鲿��";
	cin >> y.real >> y.img;
	cout << "�ڶ�������Ϊ��";
	print_ans(y);
	
	dis.real = sqrt((x.real - y.real) * (x.real - y.real) + (x.img - y.img) * (x.img - y.img));
	dis.img = 0;

	cout << "������Ϊ��";
	print_ans(dis);
}

void calculator::solve()
{
	float a, b, c, x1, x2, delta, real, img;
	cout << "������һԪ���η��̸���ϵ��a,b,c�� ";
	cin >> a >> b >> c;
	delta = b * b - 4 * a * c;

	if (delta > 0)
	{
		x1 = (-b + sqrt(delta)) / (2 * a);
		x2 = (-b - sqrt(delta)) / (2 * a);
		cout << "��������������ͬ��ʵ����" << endl;
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}

	else if (delta == 0) 
	{
		cout << "������������ͬ��ʵ��" << endl;
		x1 = (-b /(2 * a));
		cout << "x1 = x2 = " << x1 << endl;
	}

	else 
	{
		real = -b / (2 * a);
		img = sqrt(-delta) / (2 * a);
		cout << "������������ͬ�������" << endl;
		cout << "x1 = " << real << "+" << img << "i" << endl;
		cout << "x2 = " << real << "-" << img << "i" << endl;
	}

}