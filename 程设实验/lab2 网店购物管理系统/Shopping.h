#pragma once
#include<cstring>
using namespace std;
const int Max_num = 105;
 
//������Ʒ�ṹ�壬��������ID�����ơ�Ʒ�ơ��۸�����
struct item
{
	char ID_1;
	int ID_2;
	string name;
	string brand;
	float price;
	int amount;
};
 
//�û��ṹ�壬�����û����ƣ��û����룬�ջ���ַ���û����ﳵ
struct user
{
	string name;
	string password;
	string address="none";
	item shopping_car[Max_num];//���ﳵ����Ʒ�ṹ������ʵ��
	int shopping_car_num = 0; //���ﳵ����Ʒ����
};
 
//������Ʒ�ṹ�壬��������ID�����ơ�Ʒ�ơ��۸����������������û�
struct sale_item
{
	char ID_1;
	int ID_2;
	string name;
	string brand;
	float price;
	int amount;
	string my_user;
};
 
//�½�һ������ϵͳ����
class Shopping 
{
private:
	const string admin_ID ="nju_shopping"; //����ԱID
	const string admin_passwd = "201830210"; //����Ա����
	const char all_items_address[20] = "D:\\���.txt"; //����ļ���ַ
	const char sales_list_address[20] = "D:\\�����嵥.txt" ; //�ۻ��嵥�ļ���ַ
	const char all_users_address[20] = "D:\\�û�.txt"; //�û��б��ļ���ַ
	const char users_shopping_address[20] = "D:\\�ջ���ַ.txt"; //�û��ջ���ַ�ļ���ַ
 
public:
	item all_items[Max_num]; //���̿�棬����Ʒ�ṹ������ʵ��
	user all_users[Max_num]; //�û��б����û��ṹ������ʵ��
	sale_item all_sales[Max_num]; //�ۻ��嵥����������Ʒ�ṹ������ʵ��
 
	int item_num = 0; //��ǰ�����Ʒ������
	int user_num = 0; //�û��б�����
	int sale_item_num = 0; //�ۻ��嵥����
 
	//�Ѻõ�UI����
	void show();  //��ʾ������
	void users_enter(); //�û���¼����
	void users_register(); //�û�ע�����
	void administrator_enter(); //����Ա��¼����
	void admin_operate(); //����Ա��������
	void user_operate(int index,user* this_user); //�û���������,��Ҫ�Ĳ���Ϊ:���û����û��б��е��±��Լ��ýṹ��
 
	//�ļ���ز���
	void read_all_the_items(); //��ȡ����ļ�
	void write_all_the_items(); //д�����ļ�
	void read_the_sales_list(); //��ȡ�ۻ��嵥
	void write_the_sales_list(); //д���ۻ��嵥
	void read_all_the_users(); //��ȡ�û��б�
	void write_all_the_users(); //д���û��б�
	void read_shopping_address(); //��ȡ�ջ���ַ
	void write_shopping_address(); //д���ջ���ַ
	void read_shopping_car(user* this_user); //��ȡ�û����ﳵ�ļ�
	void write_shopping_car(user* this_user); //д���û����ﳵ�ļ�
 
	//����Ա��ز���
	void show_items(); //��ѯ��Ʒ
	void add_item(); //������Ʒ
	void delete_item(); //ɾ����Ʒ
	void change_item(); //�޸���Ʒ����
	void show_sales_list(); //�ۻ��嵥
 
	//�û���ز���
	void visit_items(); //�鿴��Ʒ
	void search_item(); //��Ʒ����
	void add_shopping_car(int index, user* this_user); //�����Ʒ�����ﳵ
	void delete_shopping_car(int index, user* this_user); //ɾ�����ﳵ��Ʒ
	void visit_shopping_car(int index, user* this_user); //�鿴���ﳵ
	void check_out(int index, user* this_user); //����
	void change_password(int index, user* this_user); //��չ���ܣ��û��޸�����
	void change_address(int index, user* this_user); //��չ���ܣ������ջ���ַ
 
};