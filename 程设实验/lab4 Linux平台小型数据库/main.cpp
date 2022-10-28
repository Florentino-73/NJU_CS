#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*һЩ����ָ��
* TABLE LIST
* CREATE TABLE Student FROM student.txt
* CREATE TABLE CS_Student FROM CS.txt
* CREATE TABLE Student (ѧ��,����,רҵ) TO student.txt
* CREATE TBALE Lecture (�γ̱��,�γ�����,�ο���ʦ) TO lecture.txt
* DROP TABLE Lecture
*
* INSERT INTO Student VALUES (170000001,���Ĳ�,�������ѧ�뼼��)
* INSERT INTO Student VALUES (170000002,������,����ϵ)
* INSERT INTO Student (ѧ��,����) VALUES (170000003,�ݾ���)
* INSERT INTO Student (ѧ��,����,רҵ) VALUES (170000004,�����,΢����)
* 
* DELETE FROM Student WHERE ���� = ���Ĳ�
* DELETE * FROM Student
* 
* UPDATE Student SET ѧ�� = 170000000, רҵ = �������ѧ�뼼��
* UPDATE Student SET ѧ�� = 170000000, רҵ = �����ѧ WHERE ���� = ���Ĳ�
* 
* SELECT ѧ��,���� FROM Student
* SELECT * FROM Student
* SELECT רҵ FROM Student
* SELECT DISTINCT רҵ FROM Student
* SELECT * FROM Student ORDER BY ѧ�� DESC
* SELECT רҵ FROM Student WHERE ���� = ���Ĳ�
* SELECT * FROM Student WHERE ���� = ���Ĳ�
* SELECT * FROM Student WHERE רҵ = �������ѧ�뼼�� TO CS.txt
*
* SELECT * FROM Student WHERE ѧ�� > 170000000
* SELECT MAX(ѧ��) FROM Student
* SELECT * FROM Student WHERE ѧ�� < (SELECT MAX(ѧ��) FROM Student)
*/

/*
* ���������ݽṹ����������~
*/
struct SQL //���ݿ�ṹ�壬�����������ļ����ͱ���Ӧ���
{
    string table_name;
    string file_name;
    int index;
};
SQL my_sql[100]; //ά��һ�����ݿ�״̬����
int my_sql_num = 0; //��ǰ���ݿ�״̬����

struct TABLE //���ṹ�壬�����������ļ��������е�����������������
{
    string table_name;
    string file_name;
    string column[50];
    int col_num = 0; 
    int row_num = 0;
};
TABLE all_table[100]; //ά��һ��ȫ��������
int table_num = 0; //��ǰ���ݿ�������

string table_data[100][100]; //ά��һ�����ݶ�ά���飬������ʱ�洢���µı������
int row = 0, col = 0; //��ǰ�������������

//��ȡ���ݿ��ļ�
void read_my_sql();

//д�����ݿ��ļ�
void write_my_sql();

//��ȡ���б��������
void read_all_table();

//��ȡ��ͷ
void read_table(int index, string filename);

//д���ͷ
void write_table(int index, string filename);

//��ȡ�������
void read_table_data(int index, string filename);

//д��������
void write_table_data(int index, string filename);

//����ָ������
void Create_table(char ins[]);

//����ָ��ɾ�����
void Drop_table(char ins[]);

//�鿴���б��
void Table_list();

//�����в�������
void Insert_table_data(char ins[]);

//ɾ���������
void Delete_table_data(char ins[]);

//�޸ı������
void Updata_table_data(char ins[]);

//ѡ�������ݲ�չʾ
void Selete_table_data(char ins[]);

//��ӡ�������
void printf_table(int index);

//��ӡ���б���б�
void printf_table_list();

//�ж��Ƿ�Ϊ���У���m�Ƿ�Ϊ��ĸ��
bool is_not_endl(char m);

/*
* ������������~
*/
int main()
{
    cout << "\033[33m-----\033[32mWelcome \033[35mto \033[36mmySQL!\033[33m-----\033[0m" << endl;
    while (true)
    {
        cout << "(mysql)==>";
        char ins[100]; //��������ָ��
        cin.getline(ins, 100);

        //Quit �˳����ݿ�
        if (ins[0] == 'q'&& ins[1] == 'u'&& ins[2] == 'i'&& ins[3] == 't')
        {
            cout << "\033[33m-----\033[32mQuit \033[36mmySQL!\033[33m-----\033[0m" << endl;
            break;
        }

        //CREATE TABLE      ���������
        else if (ins[0] == 'C' && ins[1] == 'R' && ins[2] == 'E' && ins[3] == 'A' && ins[4] == 'T' && ins[5] == 'E')
        {
            Create_table(ins);
        }

        //DROP TABLE        ɾ�������    
        else if (ins[0] == 'D' && ins[1] == 'R' && ins[2] == 'O' && ins[3] == 'P')
        {
            Drop_table(ins);
        }

        //TABLE LIST        �鿴���б��
        else if ((ins[0]=='0')||(ins[0] == 'T' && ins[1] == 'A' && ins[2] == 'B' && ins[3] == 'L' && ins[4] == 'E'))
        {
            Table_list();
        }

        //INSERT INTO       ��������
        else if (ins[0] == 'I' && ins[1] == 'N' && ins[2] == 'S' && ins[3] == 'E' && ins[4] == 'R' && ins[5] == 'T')
        {
            Insert_table_data(ins);
        }

        //DELETE        ɾ������
        else if (ins[0] == 'D' && ins[1] == 'E' && ins[2] == 'L' && ins[3] == 'E' && ins[4] == 'T' && ins[5] == 'E')
        {
            Delete_table_data(ins);
        }

        //UPDATE        ��������
        else if (ins[0] == 'U' && ins[1] == 'P' && ins[2] == 'D' && ins[3] == 'A' && ins[4] == 'T' && ins[5] == 'E')
        {
            Updata_table_data(ins);
        }

        //SELECT        ѡ������
        else if (ins[0] == 'S' && ins[1] == 'E' && ins[2] == 'L' && ins[3] == 'E' && ins[4] == 'C' && ins[5] == 'T')
        {
            Selete_table_data(ins);
        }

        //ERROR     ָ�����
        else
        {
            cout << "Error instruction!" << endl;
        }
    }

    return 0;
}

/*
* �����Ǻ����Ķ���~
*/

//��ȡ���ݿ�״̬�ļ�
void read_my_sql()
{
    my_sql_num = 0; //������״̬ǰ�Ƚ�ԭ״̬����
    const string my_sql_filename = "my_sql.txt"; //�������ݿ�״̬�ļ���

    //���ļ������ļ������ڣ��򴴽��ļ�
    ifstream in_file(my_sql_filename, ios::_Noreplace);

    while (in_file.peek() != EOF)
    {
        in_file >> my_sql[my_sql_num].table_name;
        in_file >> my_sql[my_sql_num].file_name;
        in_file >> my_sql[my_sql_num].index;
        if (is_not_endl(my_sql[my_sql_num].table_name[0]) == 1)
            my_sql_num++;
    }

    in_file.close();
}

//д�����ݿ�״̬�ļ�
void write_my_sql()
{
    const string my_sql_filename = "my_sql.txt"; //�������ݿ�״̬�ļ���
    ofstream out_file(my_sql_filename, ios::out);
    for (int i = 0; i < my_sql_num; i++)
    {
        //���� �ļ��� �±�
        out_file << my_sql[i].table_name << " ";
        out_file << my_sql[i].file_name << " ";
        out_file << my_sql[i].index << endl;
    }
    out_file.close();
}

//��ȡ���б��������
void read_all_table()
{
    table_num = 0; //���������

    for (int i = 0; i < my_sql_num; i++)
    {
        //ÿ��һ�����ݿ���Ϣ����õ�һ�ű�
        int ind = my_sql[i].index;
        all_table[ind].table_name = my_sql[i].table_name;
        all_table[ind].file_name = my_sql[i].file_name;
        read_table(ind, my_sql[i].file_name);
        if (is_not_endl(all_table[ind].file_name[0]) == 1)
            table_num++;
    }
}

//��ȡ��ͷ
void read_table(int index, string filename)
{
    all_table[index].col_num = 0; //�����ͷǰ�Ƚ������������

   //���ļ������ļ������ڣ��򴴽��ļ�
    ifstream in_file(filename, ios::_Noreplace);
    string s;
    getline(in_file, s);
    int i = 0;

    //������ͷ
    while(i<s.size())
    {
        int k = 0;
        string str;
        if (s[i + k] == ' ') //��ܺ����м�������ո�
            i++;
        while (i+k!=s.size() && s[i + k] != ' ')
        {
            str += s[i + k];
            k++;
        }

        int c = all_table[index].col_num;
        all_table[index].column[c] = str;
        all_table[index].col_num++;
        i = i + k + 1;
    }
    
    in_file.close();
}

//д���ͷ
void write_table(int index, string filename)
{
    ofstream out_file(filename, ios::out);
    for (int i = 0; i < all_table[index].col_num; i++)
        out_file << all_table[index].column[i] << " ";
    out_file << endl;
    out_file.close();
}

//��ȡ�������
void read_table_data(int index, string filename)
{
    all_table[index].row_num = 0; //�����ͷǰ�Ƚ������������

     //���ļ������ļ������ڣ��򴴽��ļ�
    ifstream in_file(filename, ios::_Noreplace);

    //�ȶ���ͷ
    string s;
    getline(in_file, s);

    //ʣ�µ��Ǳ������
    while(in_file.peek()!=EOF)
    {
        for (int j = 0; j < all_table[index].col_num; j++)
            in_file >> table_data[all_table[index].row_num][j]; //�ö�ά������ܱ����Ϣ
        if(table_data[all_table[index].row_num][0]>="0" && table_data[all_table[index].row_num][0]<="9")
            all_table[index].row_num++;
    }    
    in_file.close();
}

//д��������
void write_table_data(int index, string filename)
{
    ofstream out_file(filename, ios::out);
    //д���ͷ
    for (int i = 0; i < all_table[index].col_num; i++)
    {
        out_file << all_table[index].column[i] << " ";
    }
    out_file << endl;
    
    //д������
    for (int i = 0; i < all_table[index].row_num; i++)
    {
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            out_file << table_data[i][j]<<" ";
        }
        out_file << endl;
    }
    out_file.close();
}

//����ָ�����񣬻�ȡ�������ļ�������������
void Create_table(char ins[])
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();

    //����ָ���ȡ��������¼���ܱ��������
    string tablename;
    int i = 13; //�ƶ���ָ����name�ĵ�һλ
    while (ins[i] != ' ')
    {
        tablename += ins[i];
        i++;
    }
    all_table[table_num].table_name = tablename;

    i += 1;
    //��һ�ഴ�����
    if (ins[i] == '(') 
    {
        //��������Ƿ��ظ�
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //������Ѵ���
                cout << "TABLE " << tablename << " Already Exists !" << endl;
                return;
            }
        }
        //����ָ���ȡÿһ�е�����������¼���ܱ��������
        i += 1; //�ƶ���ָ����column[i]�ĵ�һλ
        int k = 0;
        string col_name[50];
        col = 0;
        while (true)
        {
            col_name[col] += ins[i + k];
            k++;
            if (ins[i + k] == ',' || ins[i + k] == '��')
            {
                //��ÿ�е����ָ�����Ӧ����column�����У���Ӧ����+1
                int c = all_table[table_num].col_num;
                all_table[table_num].column[c] = col_name[col];
                all_table[table_num].col_num++; col++;
                //�ƶ�����һ�������ĵ�һλ
                i = i + k + 1;
                k = 0;
            }
            else if (ins[i + k] == ')' || ins[i + k] == '��')
            {
                //��ÿ�е����ָ�����Ӧ����column�����У���Ӧ����+1
                int c = all_table[table_num].col_num;
                all_table[table_num].column[c] = col_name[col];
                all_table[table_num].col_num++; col++;
                i = i + k + 1;
                break;
            }
        }

        //����ָ���ȡ�ļ�������¼���ܱ��������
        i += 4; //�ƶ���ָ����file�ĵ�һλ
        string filename;
        while (ins[i] != '\0')
        {
            filename += ins[i];
            i++;
        }
        all_table[table_num].file_name = filename;

        //��������ļ���д���ͷ
        write_table(table_num, filename);

        //�޸����ݿ�״̬
        my_sql[my_sql_num].table_name = tablename;
        my_sql[my_sql_num].file_name = filename;
        my_sql[my_sql_num].index = table_num;
        my_sql_num++;
        write_my_sql(); //�������ݿ�״̬�ļ�

        table_num++; //��󣬱��������һ

        //չʾ���´����ı�ͷ
        cout << "--------------------" << endl;
        cout << "ID ";
        for (int i = 0; i < all_table[table_num - 1].col_num; i++)
        {
            cout << all_table[table_num - 1].column[i] << " ";
        }
        cout << endl;
        cout << "--------------------" << endl;
    }
    
    //�ڶ��ഴ����䣨�൱�ڴ�ӡ���б��
    else if (ins[i] == 'F') 
    {
        int index;
        string filename;
        bool flag = 1;
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                printf_table(index);
                flag = 0;
                break;
            }
            else if (my_sql[j].table_name == "None")
            {
                //�������ϱ������
                my_sql[j].table_name = tablename;
                write_my_sql();
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                printf_table(index);
                flag = 0;
                break;
            }
        }
        if (flag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }
    }

    else
    {
        cout << "Error instruction!" << endl;
    }
}

//����ָ��ɾ�����
void Drop_table(char ins[])
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();

    //����ָ���ȡ��ɾ������
    string tablename;
    int i = 11;
    while (ins[i] != '\0')
    {
        tablename += ins[i];
        i++;
    }

    bool flag = 1;
    for (int j = 0; j < my_sql_num;j++)
    {
        if (my_sql[j].table_name == tablename)
        {
            //�ҵ���ɾ�ı�����������Ǩ��
            for (int k = j; k < my_sql_num-1; k++)
            {
                my_sql[k].table_name = my_sql[k+1].table_name;
                my_sql[k].file_name = my_sql[k+1].file_name;
            }
            table_num--;
            my_sql_num--;
            flag = 0;
            cout << "DROP TABLE SUCCESS !" << endl;
            break;
        }
    }

    if (flag == 1) //û�ҵ�
    {
        cout << "Not found TABLE " << tablename << " !" << endl;
        return;
    }

    write_my_sql(); //�������ݿ�״̬�ļ�
    read_all_table(); //�޸ĵ�ǰ����б�
}

//�鿴���б��
void Table_list()
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();
    //���ζ�ȡÿ�ű�������
    for (int i = 0; i < table_num; i++)
    {
        read_table_data(i, all_table[i].file_name);
    }
    //��ӡ���б����Ϣ
    cout << "   Total table number:" << table_num << endl;
    for (int i = 0; i < table_num; i++)
    {
        cout << "      " << all_table[i].table_name << ":";
        cout << "��" << all_table[i].col_num << "��" << all_table[i].row_num << "��";
        if (all_table[i].col_num == 0)
            cout << "[ ]" << endl;
        else
        {
            cout << "[" << all_table[i].column[0];
            for (int j = 1; j < all_table[i].col_num; j++)
                cout << "��" << all_table[i].column[j];
            cout << "]" << endl;
        }
    }
}

//�����в�������
void Insert_table_data(char ins[])
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();

    //����ָ���ȡ����
    string tablename;
    int i = 12; //�ƶ���ָ����name�ĵ�һλ
    while (ins[i] != ' ')
    {
        tablename += ins[i];
        i++;
    }
    all_table[table_num].table_name = tablename;

    //���ݱ����򿪶�Ӧ�ļ�����ȡ�������
    int index;
    string filename;
    bool flag = 1;
    for (int j = 0; j < my_sql_num; j++)
    {
        if (my_sql[j].table_name == tablename)
        {
            //�ҵ��˶�Ӧ�ı��
            index = my_sql[j].index;
            filename = my_sql[j].file_name;
            read_table_data(index, filename);
            flag = 0;
            break;
        }
    }
    if (flag == 1) //û�ҵ�
    {
        cout << "Not found TABLE " << tablename << " !" << endl;
        return;
    }

    i += 1; 
    //��һ��������
    if (ins[i] == 'V') 
    {
        i += 8; //i�ƶ���value[i]�ĵ�һλ
        int k = 0;
        string col_value[50];
        int num = 0;
        col = 0, row = all_table[index].row_num;
        while (true)
        {
            col_value[num] += ins[i + k];
            k++;
            if (ins[i + k] == ',' || ins[i + k] == '��')
            {
                //��ÿ�е�ֵ������Ӧ����ֵ�����У���Ӧ����+1
                table_data[row][col] = col_value[num];
                num++; col++;
                //�ƶ�����һ��ֵ
                i = i + k + 1;
                k = 0;
            }
            else if (ins[i + k] == ')' || ins[i + k] == '��')
            {
                //��ÿ�е�ֵ������Ӧ����ֵ�����У���Ӧ����+1
                table_data[row][col] = col_value[num];
                num++; col++;
                i = i + k + 1;
                break;
            }
        }
        cout << "INSERT SUCCESS !" << endl;
        all_table[index].row_num++;
        printf_table(index);

        //�޸ı���ļ�
        write_table_data(index, filename);
    }
    
    //�ڶ���������
    else if (ins[i] == '(') 
    {
        //��ȡ���������ƺ���ӵ�ֵ
        i += 1; //i�ƶ���column[i]�ĵ�һλ
        int k = 0;
        string cols[50]; //�ݴ�column[i]��ֵ
        int num = 0; //����ֵ�ĸ���
        while (true)
        {
            cols[num] += ins[i + k];
            k++;
            if (ins[i + k] == ',' || ins[i + k] == '��')
            {
                num++;
                //�ƶ�����һ��ֵ
                i = i + k + 1;
                k = 0;
            }
            else if (ins[i + k] == ')' || ins[i + k] == '��')
            {
                num++;
                i = i + k + 1;
                break;
            }
        }

        i += 9; //i�ƶ���value[i]�ĵ�һλ
        k = 0;
        string value[50]; //�ݴ�value[i]��ֵ
        num = 0; //����ֵ�ĸ���
        while (true)
        {
            string col_value;
            value[num] += ins[i + k];
            k++;
            if (ins[i + k] == ',' || ins[i + k] == '��')
            {
                num++;
                //�ƶ�����һ��ֵ
                i = i + k + 1;
                k = 0;
            }
            else if (ins[i + k] == ')' || ins[i + k] == '��')
            {
                num++;
                i = i + k + 1;
                break;
            }
        }

        col = 0, row = all_table[index].row_num;
        for (int m = 0; m < all_table[index].col_num; m++)
        {
            bool tag = 1; //��ʾ�Ƿ�Ϊȱʡ
            for (int n = 0; n < num; n++)
            {
                if (all_table[index].column[m] == cols[n])
                {
                    table_data[row][m] = value[n];
                    tag = 0;
                    break;
                }
            }
            if (tag == 1)
                table_data[row][m] = "��"; //ȱʡֵĬ��Ϊ��
        }

        cout << "INSERT SUCCESS !" << endl;
        all_table[index].row_num++;
        printf_table(index);

        //�޸ı���ļ�
        write_table_data(index, filename);
    }

    else
    {
        cout << "Error instruction!" << endl;
    }
}

//ɾ���������
void Delete_table_data(char ins[])
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();

    //��һ��ɾ�����
    if (ins[7] == 'F')
    {
        //����ָ���ȡ����
        string tablename;
        int i = 12; //�ƶ���ָ����name�ĵ�һλ
        while (ins[i] != ' ')
        {
            tablename += ins[i];
            i++;
        }
        all_table[table_num].table_name = tablename;

        //��ȡ������� 
        int index;
        string filename;
        bool flag = 1; 
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                flag = 0;
                break;
            }
        }

        if (flag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }

        i += 7; //i�ƶ�����ɾ����column��һλ
        string column;
        while (ins[i] != ' ')
        {
            column += ins[i];
            i++;
        }

        i += 3; //i�ƶ�����ɾ����value��һλ
        string value;
        while (ins[i] != '\0')
        {
            value += ins[i];
            i++;
        }

        col = all_table[index].col_num, row = all_table[index].row_num;

        //���ҵ�ɾ�����е��±�
        int column_index = -1;
        for (int k = 0; k < col; k++)
        {
            if (all_table[index].column[k] == column)
            {
                column_index = k;
                break;
            }
        }
        if (column_index == -1)
        {
            cout << "Error instruction!" << endl;
            return;
        }

        bool tag = 1;
        //�������������������ļ�¼
        for (int k = 0; k < row; k++)
        {
            if (table_data[k][column_index] == value)
            {
                tag = 0;
                //�ҵ���ɾ�У���������Ǩ��
                for (int m = k; m < row - 1; m++)
                {
                    for (int n = 0; n < col; n++)
                    {
                        table_data[m][n] = table_data[m + 1][n];
                    }
                }
                break;
            }
        }
        if (tag == 1)
        {
            cout << "Error instruction!" << endl;
            return;
        }

        else
        {
            all_table[index].row_num--;

            cout << "DELETE SUCCESS !" << endl;
            printf_table(index);

            //�޸ı���ļ�
            write_table_data(index, filename);
        }
    }

    //�ڶ���ɾ�����
    else if (ins[7] == '*' && ins[9]=='F')
    {
        //����ָ���ȡ����
        string tablename;
        int i = 14; //�ƶ���ָ����name�ĵ�һλ
        while (ins[i] != '\0')
        {
            tablename += ins[i];
            i++;
        }
        all_table[table_num].table_name = tablename;

        //��ȡ������� 
        int index;
        string filename;
        bool flag = 1;
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                flag = 0;
                break;
            }
        }
        if (flag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }

        all_table[index].row_num = 0; //ɾ��������
        cout << "DELETE SUCCESS !" << endl;
        printf_table(index);

        //�޸ı���ļ�
        write_table_data(index, filename);
    }

    else
    {
        cout << "Error instruction!" << endl;
    }
}

//�޸ı������
void Updata_table_data(char ins[])
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();

    //����ָ���ȡ����
    string tablename;
    int i = 7; //�ƶ���ָ����name�ĵ�һλ
    while (ins[i] != ' ')
    {
        tablename += ins[i];
        i++;
    }
    all_table[table_num].table_name = tablename;

    //���ݱ����򿪶�Ӧ�ļ�����ȡ�������
    int index;
    string filename;
    bool flag = 1;
    for (int j = 0; j < my_sql_num; j++)
    {
        if (my_sql[j].table_name == tablename)
        {
            //�ҵ��˶�Ӧ�ı��
            index = my_sql[j].index;
            filename = my_sql[j].file_name;
            read_table_data(index, filename);
            flag = 0;
            break;
        }
    }
    if (flag == 1) //û�ҵ�
    {
        cout << "Not found TABLE " << tablename << " !" << endl;
        return;
    }

    i += 5; //�ƶ���column i��һλ
    int k = 0;
    int tag = 0;
    string s[50];
    string column[50], value[50];
    int num = 0;
    while (true)
    {
        while (ins[i + k] != ','&& ins[i + k] != '\0'&&ins[i + k] != 'W')
        {
            s[num] += ins[i + k];
            k++;
        }

        if (ins[i + k] == ',')
        {
            num++;
            i = i + k + 2;
            k = 0;
        }

        else if (ins[i + k] == '\0')
        {
            tag = 1; //��һ��������
            num++;
            break;
        }

        else if (ins[i + k] == 'W')
        {
            tag = 2; //�ڶ���������
            num++;
            //���һ�����һ���ո�ɾȥ֮
            string temp = s[num - 1].substr(0, s[num - 1].size() - 1);
            s[num - 1] = temp;
            i = i + k + 6; //i �ƶ���column��λ
            break;
        }
    }

    //����ٴν���
    for (int j = 0; j < num; j++)
    {
        int cur = 0;
        while (s[j][cur] != ' ')
            cur++;
        column[j] = s[j].substr(0, cur);
        cur += 3;
        value[j] = s[j].substr(cur, s[j].size());
    }

    if (tag == 1)
    {
        //�Ա��ÿһ�н��б���������column[]�����ж��Ƿ���Ҫ����
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            for (int n = 0; n < num; n++)
            {
                if (all_table[index].column[j] == column[n]) 
                {
                    //������һ��ÿһ�е�ֵ
                    for (int m = 0; m < all_table[index].row_num; m++)
                    {
                        //m�Ǳ���ĳһ�У�j�Ǳ���ĳһ�У�n�Ƕ�ӦҪ�޸ĵ�ֵ
                        table_data[m][j] = value[n];
                    }
                    break;
                }
            }
        }
        cout << "UPDATE SUCCESS !" << endl;
        printf_table(index);

        //�޸ı���ļ�
        write_table_data(index, filename);
    }

    else if (tag == 2)
    {
        //��¼�������� column = value
        string clmn, val;
        while (ins[i] != ' ')
        {
            clmn += ins[i];
            i++;
        }
        i += 3;
        while (ins[i] != '\0')
        {
            val += ins[i];
            i++;
        }
        
        //�ҵ���Ӧ���е��±�
        int column_index = -1;
        for (k = 0; k < all_table[index].col_num; k++)
        {
            if (all_table[index].column[k] == clmn)
            {
                column_index = k;
                break;
            }
        }
        if (column_index == -1)
        {
            cout << "Error instruction!" << endl;
            return;
        }

        //�Ա��ÿһ�н��б���������column[]�����ж��Ƿ���Ҫ����
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            for (int n = 0; n < num; n++)
            {
                if (all_table[index].column[j] == column[n])
                {
                    //ֻ������һ�����������������е�ֵ
                    for (int m = 0; m < all_table[index].row_num; m++)
                    {
                        //�ж��Ƿ���������
                        if (table_data[m][column_index] == val)
                        {
                            //m�Ǳ���ĳһ�У�j�Ǳ���ĳһ�У�n�Ƕ�ӦҪ�޸ĵ�ֵ
                            table_data[m][j] = value[n];
                        }
                    }
                    break;
                }
            }
        }
        cout << "UPDATE SUCCESS !" << endl;
        printf_table(index);

        //�޸ı���ļ�
        write_table_data(index, filename);
    }

    else
    {
        cout << "Error instruction!" << endl;
    }
}

//ѡ�������ݲ�չʾ
void Selete_table_data(char ins[])
{
    //�ȶ�ȡ���ݿ�״̬�ļ������б���б�
    read_my_sql();
    read_all_table();

    if (ins[7] == '*')
    {
        //����ָ���ȡ����
        string tablename;
        int i = 14; //�ƶ���ָ����name�ĵ�һλ
        while (ins[i] != '\0' && ins[i] != ' ')
        {
            tablename += ins[i];
            i++;
        }

        //���ݱ����򿪶�Ӧ�ļ�����ȡ�������
        int index;
        string filename;
        bool flag = 1;
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                flag = 0;
                break;
            }
        }
        if (flag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }

        //��TABLE name��ѡ��������չʾ����չʾ����TABLE
        if (ins[i] == '\0')
        {
            printf_table(index);
        }

        //�Է��صĲ�ѯ�����ĳЩ�н�������չʾ
        else if (ins[i] == ' ' && ins[i + 1] == 'O')
        {
            i += 10; //�ƶ��� column i ��һλ
            string column[50];
            int num = 0;
            int k = 0;
            while (true)
            {
                while (ins[i + k] != ',' && ins[i + k] != ' ')
                {
                    column[num] += ins[i + k];
                    k++;
                }

                if (ins[i + k] == ',')
                {
                    num++;
                    i = i + k + 1;
                    k = 0;
                }

                else if (ins[i + k] == ' ')
                {
                    num++;
                    i = i + k + 1; //i �ƶ���ASC|DESC��λ
                    break;
                }
            }

            //�ҵ���Ӧ���е��±�
            int column_index = -1;
            for (k = 0; k < all_table[index].col_num; k++)
            {
                //֧�ְ�ĳһ�е�ֵ����
                if (all_table[index].column[k] == column[0])
                {
                    column_index = k;
                    break;
                }
            }
            if (column_index == -1)
            {
                cout << "Error instruction!" << endl;
                return;
            }

            if (ins[i] == 'A') //����
            {
                for (int m = 0; m < all_table[index].row_num - 1; m++)
                {
                    for (int n = 0; n < all_table[index].row_num - m - 1; n++)
                    {
                        if (table_data[n][column_index] > table_data[n + 1][column_index])
                        {
                            //��������Ԫ��
                            for (int tt = 0; tt < all_table[index].col_num; tt++)
                            {
                                string temp = table_data[n][tt];
                                table_data[n][tt] = table_data[n + 1][tt];
                                table_data[n + 1][tt] = temp;
                            }
                        }
                    }
                }
            }

            else if (ins[i] == 'D') //����
            {
                for (int m = 0; m < all_table[index].row_num - 1; m++)
                {
                    for (int n = 0; n < all_table[index].row_num - m - 1; n++)
                    {
                        if (table_data[n][column_index] < table_data[n + 1][column_index])
                        {
                            //��������Ԫ��
                            for (int tt = 0; tt < all_table[index].col_num; tt++)
                            {
                                string temp = table_data[n][tt];
                                table_data[n][tt] = table_data[n + 1][tt];
                                table_data[n + 1][tt] = temp;
                            }
                        }
                    }
                }
            }

            else
            {
                cout << "Error instruction!" << endl;
                return;
            }

            //��ӡ
            //��ӡ��ͷ
            cout << "----------------------------------------" << endl;
            cout << "ID ";
            for (int j = 0; j < all_table[index].col_num; j++)
            {
                cout << all_table[index].column[j] << " ";
            }
            cout << endl;
            cout << "----------------------------------------" << endl;

            //��ӡ����
            for (int m = 0; m < all_table[index].row_num; m++)
            {
                cout << m + 1 << " ";
                for (int n = 0; n < all_table[index].col_num; n++)
                {
                    cout << table_data[m][n] << " ";
                }
                cout << endl;
                cout << "----------------------------------------" << endl;
            }
        }

        else if (ins[i] == ' ' && ins[i + 1] == 'W')
        {
            i += 7; //i �ƶ���column��һλ
            //��¼�������� column = value
            string clmn, val;
            while (ins[i] != ' ')
            {
                clmn += ins[i];
                i++;
            }
            i += 1;
            
            // column = value
            if (ins[i] == '=')
            {
                i += 2;
                while (ins[i] != '\0' && ins[i] != ' ')
                {
                    val += ins[i];
                    i++;
                }

                //�ҵ���Ӧ���е��±�
                int column_index = -1;
                for (int k = 0; k < all_table[index].col_num; k++)
                {
                    if (all_table[index].column[k] == clmn)
                    {
                        column_index = k;
                        break;
                    }
                }
                if (column_index == -1)
                {
                    cout << "Error instruction!" << endl;
                    return;
                }

                if (ins[i] == '\0')
                {
                    //��ӡ
                    //��ӡ��ͷ
                    cout << "----------------------------------------" << endl;
                    cout << "ID ";
                    for (int j = 0; j < all_table[index].col_num; j++)
                    {
                        cout << all_table[index].column[j] << " ";
                    }
                    cout << endl;
                    cout << "----------------------------------------" << endl;

                    //��ӡ����
                    for (int m = 0; m < all_table[index].row_num; m++)
                    {
                        if (table_data[m][column_index] == val)
                        {
                            cout << m + 1 << " ";
                            for (int n = 0; n < all_table[index].col_num; n++)
                            {
                                cout << table_data[m][n] << " ";
                            }
                            cout << endl;
                            cout << "----------------------------------------" << endl;
                        }
                    }
                }

                else
                {
                    i += 4; //�ƶ����±���ļ�����һλ
                    string new_filename;
                    while (ins[i] != '\0')
                    {
                        new_filename += ins[i];
                        i++;
                    }

                    //��ӡ
                    //��ӡ��ͷ
                    cout << "----------------------------------------" << endl;
                    cout << "ID ";
                    for (int j = 0; j < all_table[index].col_num; j++)
                    {
                        cout << all_table[index].column[j] << " ";
                    }
                    cout << endl;
                    cout << "----------------------------------------" << endl;

                    //��ӡ����
                    for (int m = 0; m < all_table[index].row_num; m++)
                    {
                        if (table_data[m][column_index] == val)
                        {
                            cout << m + 1 << " ";
                            for (int n = 0; n < all_table[index].col_num; n++)
                            {
                                cout << table_data[m][n] << " ";
                            }
                            cout << endl;
                            cout << "----------------------------------------" << endl;
                        }
                    }

                    //�����±�д���ļ�
                    ofstream out_file(new_filename, ios::out);
                    //д���ͷ
                    for (int j = 0; j < all_table[index].col_num; j++)
                    {
                        out_file << all_table[index].column[j] << " ";
                    }
                    out_file << endl;

                    //д������
                    for (int m = 0; m < all_table[index].row_num; m++)
                    {
                        if (table_data[m][column_index] == val)
                        {
                            for (int n = 0; n < all_table[index].col_num; n++)
                            {
                                out_file << table_data[m][n] << " ";
                            }
                            out_file << endl;
                        }
                    }
                    out_file.close();

                    //�޸����ݿ�״̬
                    my_sql[my_sql_num].table_name = "None";
                    my_sql[my_sql_num].file_name = new_filename;
                    my_sql[my_sql_num].index = table_num;
                    my_sql_num++;
                    write_my_sql(); //�������ݿ�״̬�ļ�

                }
            }
            
            // column > value
            else if (ins[i] == '>')
            {
                i += 2;
                while (ins[i] != '\0')
                {
                    val += ins[i];
                    i++;
                }

                //�ҵ���Ӧ���е��±�
                int column_index = -1;
                for (int k = 0; k < all_table[index].col_num; k++)
                {
                    if (all_table[index].column[k] == clmn)
                    {
                        column_index = k;
                        break;
                    }
                }
                if (column_index == -1)
                {
                    cout << "Error instruction!" << endl;
                    return;
                }

                //��ӡ
                //��ӡ��ͷ
                cout << "----------------------------------------" << endl;
                cout << "ID ";
                for (int j = 0; j < all_table[index].col_num; j++)
                {
                    cout << all_table[index].column[j] << " ";
                }
                cout << endl;
                cout << "----------------------------------------" << endl;

                //��ӡ����
                for (int m = 0; m < all_table[index].row_num; m++)
                {
                    if (table_data[m][column_index] > val)
                    {
                        cout << m + 1 << " ";
                        for (int n = 0; n < all_table[index].col_num; n++)
                        {
                            cout << table_data[m][n] << " ";
                        }
                        cout << endl;
                        cout << "----------------------------------------" << endl;
                    }
                }
            }
           
            // column < value ������value=max(ѧ��)
            else if (ins[i] == '<')
            {
                i += 2;

                //�ҵ���Ӧ���е��±�
                int column_index = -1;
                for (int k = 0; k < all_table[index].col_num; k++)
                {
                    if (all_table[index].column[k] == clmn)
                    {
                        column_index = k;
                        break;
                    }
                }
                if (column_index == -1)
                {
                    cout << "Error instruction!" << endl;
                    return;
                }

                //��ѧ�����ֵ
                string max = table_data[0][column_index];
                for (int j = 0; j < all_table[index].row_num; j++)
                {
                    if (table_data[j][column_index] > max)
                    {
                        max = table_data[j][column_index];
                    }
                }

                //��ӡ
                //��ӡ��ͷ
                cout << "----------------------------------------" << endl;
                cout << "ID ";
                for (int j = 0; j < all_table[index].col_num; j++)
                {
                    cout << all_table[index].column[j] << " ";
                }
                cout << endl;
                cout << "----------------------------------------" << endl;

                //��ӡ����
                for (int m = 0; m < all_table[index].row_num; m++)
                {
                    if (table_data[m][column_index] < max)
                    {
                        cout << m + 1 << " ";
                        for (int n = 0; n < all_table[index].col_num; n++)
                        {
                            cout << table_data[m][n] << " ";
                        }
                        cout << endl;
                        cout << "----------------------------------------" << endl;
                    }
                }
            }

            else
            {
                cout << "Error instruction!" << endl;
                return;
            }
        }

        else
        {
            cout << "Error instruction!" << endl;
        }
    }

    else if (ins[7] == 'D')
    {
        string column[50];
        int num = 0;
        int i = 16; //�ƶ��� column i ��һλ
        int k = 0;
        while (true)
        {
            while (ins[i + k] != ',' && ins[i + k] != ' ')
            {
                column[num] += ins[i + k];
                k++;
            }

            if (ins[i + k] == ',')
            {
                num++;
                i = i + k + 1;
                k = 0;
            }

            else if (ins[i + k] == ' ')
            {
                num++;
                i = i + k + 6; //i �ƶ���name��λ
                break;
            }
        }

        //��������
        string tablename;
        while (ins[i] != '\0' && ins[i] != ' ')
        {
            tablename += ins[i];
            i++;
        }

        //���ݱ����򿪶�Ӧ�ļ�����ȡ�������
        int index;
        string filename;
        bool tag = 1;
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                tag = 0;
                break;
            }
        }
        if (tag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }

        bool flag[50]; //��ÿһ�������
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            flag[j] = 0;
        }
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            for (k = 0; k < num; k++)
            {
                if (all_table[index].column[j] == column[k])
                {
                    flag[j] = 1;
                    break;
                }
            }
        }

        //��ӡ��ͷ
        cout << "----------------------------------------" << endl;
        cout << "ID ";
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            if (flag[j] == 1)
                cout << all_table[index].column[j] << " ";
        }
        cout << endl;
        cout << "----------------------------------------" << endl;

        //��ӡ����
        for (int m = 0; m < all_table[index].row_num; m++)
        {
            bool print = 1; //�ж�Ҫ��Ҫ��ӡ 
            for (int n = 0; n < all_table[index].col_num; n++)
            {
                if (flag[n] == 1)
                {
                    for (int a = 0; a < m; a++)
                    {
                        if (table_data[a][n] == table_data[m][n])
                        {
                            print = 0;
                            break;
                        }
                    }
                }
            }

            if (print == 1)
            {
                cout << m + 1 << " ";
                for (int n = 0; n < all_table[index].col_num; n++)
                {
                    if (flag[n] == 1)
                        cout << table_data[m][n] << " ";
                }
                cout << endl;
                cout << "----------------------------------------" << endl;
            }
        }

    }

    else if (ins[7] == 'M')
    {
        int i = 11; 
        string column;
        while (ins[i] != ')')
        {
            column += ins[i];
            i++;
        }

        //����ָ���ȡ����
        i += 7;
        string tablename;
        while (ins[i] != '\0')
        {
            tablename += ins[i];
            i++;
        }

        //���ݱ����򿪶�Ӧ�ļ�����ȡ�������
        int index;
        string filename;
        bool flag = 1;
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                flag = 0;
                break;
            }
        }
        if (flag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }


        //�ҵ���Ӧ���е��±�
        int column_index = -1;
        for (int k = 0; k < all_table[index].col_num; k++)
        {
            if (all_table[index].column[k] == column)
            {
                column_index = k;
                break;
            }
        }
        if (column_index == -1)
        {
            cout << "Error instruction!" << endl;
            return;
        }

        //�����ֵ
        int maxline = 0;
        string max = table_data[0][column_index];
        for (int j = 0; j < all_table[index].row_num; j++)
        {
            if (table_data[j][column_index] > max)
            {
                max = table_data[j][column_index];
                maxline = j;
            }
        }

        //��ӡ
        //��ӡ��ͷ
        cout << "----------------------------------------" << endl;
        cout << "ID ";
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            cout << all_table[index].column[j] << " ";
        }
        cout << endl;
        cout << "----------------------------------------" << endl;

        //��ӡ����
        cout << maxline + 1 << " ";
        for (int n = 0; n < all_table[index].col_num; n++)
        {
            cout << table_data[maxline][n] << " ";
        }
        cout << endl;
        cout << "----------------------------------------" << endl;

    }

    else
    {
        string column[50];
        int num = 0;
        int i = 7; //�ƶ��� column i ��һλ
        int k = 0;
        while (true)
        {
            while (ins[i + k] != ',' && ins[i + k] != ' ')
            {
                column[num] += ins[i + k];
                k++;
            }

            if (ins[i + k] == ',')
            {
                num++;
                i = i + k + 1;
                k = 0;
            }

            else if (ins[i + k] == ' ')
            {
                num++;
                i = i + k + 6; //i �ƶ���name��λ
                break;
            }
        }

        //��������
        string tablename;
        while (ins[i] != '\0' && ins[i] != ' ')
        {
            tablename += ins[i];
            i++;
        }
        all_table[table_num].table_name = tablename;

        //���ݱ����򿪶�Ӧ�ļ�����ȡ�������
        int index;
        string filename;
        bool tag = 1;
        for (int j = 0; j < my_sql_num; j++)
        {
            if (my_sql[j].table_name == tablename)
            {
                //�ҵ��˶�Ӧ�ı��
                index = my_sql[j].index;
                filename = my_sql[j].file_name;
                read_table_data(index, filename);
                tag = 0;
                break;
            }
        }
        if (tag == 1) //û�ҵ�
        {
            cout << "Not found TABLE " << tablename << " !" << endl;
            return;
        }

        bool flag[50]; //��ÿһ�������
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            flag[j] = 0;
        }
        for (int j = 0; j < all_table[index].col_num; j++)
        {
            for (k = 0; k < num; k++)
            {
                if (all_table[index].column[j] == column[k])
                {
                    flag[j] = 1;
                    break;
                }
            }
        }

        //��TABLE name��ѡ��������չʾ
        if (ins[i] == '\0')
        {
            //��ӡ��ͷ
            cout << "----------------------------------------" << endl;
            cout << "ID ";
            for (int j = 0; j < all_table[index].col_num; j++)
            {
                if(flag[j]==1)
                    cout << all_table[index].column[j] << " ";
            }
            cout << endl;
            cout << "----------------------------------------" << endl;
            
            //��ӡ����
            for (int m = 0; m < all_table[index].row_num; m++)
            {
                cout << m + 1 << " ";
                for (int n = 0; n < all_table[index].col_num; n++)
                {
                    if (flag[n] == 1)
                        cout << table_data[m][n] << " ";
                }
                cout << endl;
                cout << "----------------------------------------" << endl;
            }
        }

        //��TABLE name��ѡ��������չʾ
        else if (ins[i] == ' ' && ins[i + 1] == 'W')
        {
            i += 7; //�ƶ���column��λ
            //��¼�������� column = value
            string clmn, val;
            while (ins[i] != ' ')
            {
                clmn += ins[i];
                i++;
            }
            i += 3;
            while (ins[i] != '\0')
            {
                val += ins[i];
                i++;
            }

            //�ҵ���Ӧ���е��±�
            int column_index = -1;
            for (k = 0; k < all_table[index].col_num; k++)
            {
                if (all_table[index].column[k] == clmn)
                {
                    column_index = k;
                    break;
                }
            }
            if (column_index == -1)
            {
                cout << "Error instruction!" << endl;
                return;
            }

            //��ӡ��ͷ
            cout << "----------------------------------------" << endl;
            cout << "ID ";
            for (int j = 0; j < all_table[index].col_num; j++)
            {
                if (flag[j] == 1)
                    cout << all_table[index].column[j] << " ";
            }
            cout << endl;
            cout << "----------------------------------------" << endl;
            
            //��ӡ����
            for (int m = 0; m < all_table[index].row_num; m++)
            {
                if(table_data[m][column_index]==val)
                {
                    cout << m + 1 << " ";
                    for (int n = 0; n < all_table[index].col_num; n++)
                    {
                        if (flag[n] == 1)
                            cout << table_data[m][n] << " ";
                    }
                    cout << endl;
                    cout << "----------------------------------------" << endl;
                }
            }
        }

        else
        {
            cout << "Error instruction!" << endl;
        }
    }
}

//��ӡ���
void printf_table(int index)
{
    cout << "----------------------------------------" << endl;
    cout << "ID ";
    for (int i = 0; i < all_table[index].col_num; i++)
    {
        cout << all_table[index].column[i] << " ";
    }
    cout << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < all_table[index].row_num; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < all_table[index].col_num; j++)
            cout << table_data[i][j] << " ";
        cout << endl;
        cout << "----------------------------------------" << endl;
    }
}

//��ӡ���б���б�
void printf_table_list()
{
    for (int i = 0; i < table_num; i++)
        cout << all_table[i].table_name << " " << all_table[i].file_name << endl;
}

//�ж��Ƿ�Ϊ���У���m�Ƿ�Ϊ��ĸ��
bool is_not_endl(char m)
{
    if (((m >= 'a') && (m <= 'z')) || ((m >= 'A') && (m <= 'Z')))
        return true;
    return false;
}