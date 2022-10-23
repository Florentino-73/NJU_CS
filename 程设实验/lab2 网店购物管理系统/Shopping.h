#pragma once
#include<cstring>
using namespace std;
const int Max_num = 105;
 
//单个商品结构体，包括两段ID、名称、品牌、价格、数量
struct item
{
	char ID_1;
	int ID_2;
	string name;
	string brand;
	float price;
	int amount;
};
 
//用户结构体，包括用户名称，用户密码，收货地址，用户购物车
struct user
{
	string name;
	string password;
	string address="none";
	item shopping_car[Max_num];//购物车由商品结构体数组实现
	int shopping_car_num = 0; //购物车中商品数量
};
 
//已售商品结构体，包括两段ID、名称、品牌、价格、已售数量、购买用户
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
 
//新建一个购物系统的类
class Shopping 
{
private:
	const string admin_ID ="nju_shopping"; //管理员ID
	const string admin_passwd = "201830210"; //管理员密码
	const char all_items_address[20] = "D:\\库存.txt"; //库存文件地址
	const char sales_list_address[20] = "D:\\已售清单.txt" ; //售货清单文件地址
	const char all_users_address[20] = "D:\\用户.txt"; //用户列表文件地址
	const char users_shopping_address[20] = "D:\\收货地址.txt"; //用户收货地址文件地址
 
public:
	item all_items[Max_num]; //店铺库存，由商品结构体数组实现
	user all_users[Max_num]; //用户列表，由用户结构体数组实现
	sale_item all_sales[Max_num]; //售货清单，由已售商品结构体数组实现
 
	int item_num = 0; //当前库存商品种类数
	int user_num = 0; //用户列表数量
	int sale_item_num = 0; //售货清单数量
 
	//友好的UI界面
	void show();  //显示主界面
	void users_enter(); //用户登录界面
	void users_register(); //用户注册界面
	void administrator_enter(); //管理员登录界面
	void admin_operate(); //管理员操作界面
	void user_operate(int index,user* this_user); //用户操作界面,需要的参数为:该用户在用户列表中的下标以及该结构体
 
	//文件相关操作
	void read_all_the_items(); //读取库存文件
	void write_all_the_items(); //写入库存文件
	void read_the_sales_list(); //读取售货清单
	void write_the_sales_list(); //写入售货清单
	void read_all_the_users(); //读取用户列表
	void write_all_the_users(); //写入用户列表
	void read_shopping_address(); //读取收货地址
	void write_shopping_address(); //写入收货地址
	void read_shopping_car(user* this_user); //读取用户购物车文件
	void write_shopping_car(user* this_user); //写入用户购物车文件
 
	//管理员相关操作
	void show_items(); //查询商品
	void add_item(); //增加商品
	void delete_item(); //删除商品
	void change_item(); //修改商品数量
	void show_sales_list(); //售货清单
 
	//用户相关操作
	void visit_items(); //查看商品
	void search_item(); //商品搜索
	void add_shopping_car(int index, user* this_user); //添加商品至购物车
	void delete_shopping_car(int index, user* this_user); //删除购物车商品
	void visit_shopping_car(int index, user* this_user); //查看购物车
	void check_out(int index, user* this_user); //结账
	void change_password(int index, user* this_user); //拓展功能：用户修改密码
	void change_address(int index, user* this_user); //拓展功能：管理收货地址
 
};