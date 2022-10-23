//calculator.h
#ifndef CALCULATOR_H
#include<string>
using namespace std;

struct element//ֱ�Ӷ�ȡ��ÿ��Ԫ��ͳһ����Ϊһ���ṹ�壬�������ֺͲ�����
{
	bool type;		//false ��ʾ��Ԫ��Ϊ���֣�true ��ʾ��Ԫ��Ϊ����
	double real, img;	//������ʵ�����鲿
	int op;			//�� 0 ��ʼ������������ֱ�Ϊ�� �����š������š��ӡ������ˡ������˷�
};

class calculator
{
	static const int MAX_NUM = 1000;		//�������1000���������������
	static const int priority[7];			//����������ȼ�

private:
	element all_element[MAX_NUM];			//�±�[0,element_num)

	int element_num;						//һ���ж��ٸ�Ԫ��
	int p_o_e_num;							//������ʽ�ж��ٸ�Ԫ��
	int stack_num;							//ջ�����ж���Ԫ��

	int middel_order_expression[MAX_NUM];	//������ʽ����
	int preorder_expression[MAX_NUM];		//������ʽ����
	int stack[MAX_NUM];						//����ת������Ҫ��һ��ջ,��1��ʼ�ţ��������Ҳ��Ҫһ��ջ

	void get_m_o_e();						//�õ�������ʽ
	void get_p_o_e();						//�õ�������ʽ

public:
	element ans;							    //�ü���ʽ�Ĵ�
	
	calculator();					            //Ĭ�Ϲ��캯��
	bool get(string);				        //����һ��������ʽ������Ϊ������ʽ��������ʽ���﷨�����򷵻�false
	void print(int i);				            //��ӡ������ʽ(0 Ϊ��������Ϊǰ��)
	void calculate();				        //��ʼ����
	void print_ans(element ans);	    //��ӡ��
	void clear();					            //����ϴ�����
	
	void distance();                        //����������֮��ľ���
	void solve();                             //���һԪ���η���

	bool Better(element, element);   //�ж�����������Ԫ�ص����ȼ�
};

#endif // !CALCULATOR_H
