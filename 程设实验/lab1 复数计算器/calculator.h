//calculator.h
#ifndef CALCULATOR_H
#include<string>
using namespace std;

struct element//直接读取的每个元素统一定义为一个结构体，包括数字和操作符
{
	bool type;		//false 表示该元素为数字，true 表示该元素为操作
	double real, img;	//复数的实部和虚部
	int op;			//从 0 开始定义操作符，分别为： 左括号、右括号、加、减、乘、除、乘方
};

class calculator
{
	static const int MAX_NUM = 1000;		//假设最多1000个操作数或操作符
	static const int priority[7];			//各运算符优先级

private:
	element all_element[MAX_NUM];			//下标[0,element_num)

	int element_num;						//一共有多少个元素
	int p_o_e_num;							//先序表达式有多少个元素
	int stack_num;							//栈里面有多少元素

	int middel_order_expression[MAX_NUM];	//中序表达式数组
	int preorder_expression[MAX_NUM];		//先序表达式数组
	int stack[MAX_NUM];						//中序转先序需要用一个栈,从1开始放；计算过程也需要一个栈

	void get_m_o_e();						//得到中序表达式
	void get_p_o_e();						//得到先序表达式

public:
	element ans;							    //该计算式的答案
	
	calculator();					            //默认构造函数
	bool get(string);				        //接受一个计算表达式并保存为中序表达式，如果表达式有语法错误，则返回false
	void print(int i);				            //打印计算表达式(0 为中序，其它为前序)
	void calculate();				        //开始计算
	void print_ans(element ans);	    //打印答案
	void clear();					            //清除上次运算
	
	void distance();                        //求两个复数之间的距离
	void solve();                             //求解一元二次方程

	bool Better(element, element);   //判断两个操作符元素的优先级
};

#endif // !CALCULATOR_H
