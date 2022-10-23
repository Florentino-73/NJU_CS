#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"
#include<fstream>
#include<conio.h>

#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3
#define Max_step 500

//ά���ı������̣�-1�����λ��0��������ӣ�1���������
int chess_board[ROWS][COLS]; 

//��¼ÿһ����Ľṹ�����ڸ��̣������ķ����������ӣ��Ǹ÷��ĵڼ���
struct step_msg
{
	int color;
	int row;
	int col;
	int num; //��Ӧĳһ���ĵڼ���
};

step_msg all_step[Max_step]; //ÿ��������в������ɵĵĽṹ������

int step_num = 0; //ÿ�����ܲ���
int black_num = 0; //�ڷ�����
int white_num = 0; //�׷�����

Reversi::Reversi()
{
	client_socket = ClientSocket();
	oppositeColor = ownColor = -1;
}

Reversi::~Reversi() {}
void Reversi::setOwnColor(int color)
{
	if (color != 0 && color != 1)
		return;
	ownColor = color;
	oppositeColor = 1 - color;
}

/*
 send id and password to server by socket ͨ���ӿڽ�id�����봫�͸�������
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char* id, const char* pass) //��Ȩ
{
	client_socket.connectServer();
	std::cout << "Authorize " << id << std::endl;
	char msgBuf[BUFSIZE];
	memset(msgBuf, 0, BUFSIZE);
	msgBuf[0] = 'A';
	memcpy(&msgBuf[1], id, 9);
	memcpy(&msgBuf[10], pass, 6);
	int rtn = client_socket.sendMsg(msgBuf);
	if (rtn != 0) printf("Authorized Failed!\n");
}

//�û�id���룬����������Ҫ�ж�Ӧ���˺����룺��Ӧ�ļ� players-0.txt
void Reversi::gameStart()
{
	char id[12] = { 0 }, passwd[10] = { 0 };
	strcpy(id, ID);
	strcpy(passwd, PASSWORD);
	authorize(id, passwd);

	printf("Game Start!\n");

	for (int round = 0; round < ROUNDS; round++)
	{
		roundStart(round);
		oneRound(round);
		roundOver(round);
	}
	gameOver();
	client_socket.close();
}

void Replay(int round);

void Reversi::gameOver()
{
	printf("Game Over!\n");
	cout << "�Ƿ���и��̣�1.YES;    2.NO" << endl;
	cout << "������ָ�";
	int choice;
	cin >> choice;
	while(choice == 1)
	{
		cout << "��ѡ���̵�����(0,1,2)��";
		int round;
		cin >> round;
		Replay(round);
		cout << "�Ƿ�������и��̣�1.YES;    2.NO" << endl;
		cout << "������ָ�";
		cin >> choice;
	}
	cout << "���̽�����" << endl;
		
}

//��һ����Ϣ������һ������������Ϣ��1.�Լ��Ĳ����в���   2.����������һ�� 
void Reversi::roundStart(int round)
{
	printf("Round %d Ready Start!\n", round);

	// first time receive msg from server
	int rtn = client_socket.recvMsg();
	if (rtn != 0) return;
	if (strlen(client_socket.getRecvMsg()) < 2)
		printf("Authorize Failed!\n"); //��Ȩʧ��
	else
		printf("Round start received msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[1]) 
	{
	// this client : black chessman 
	case 'B': //black
		ownColor = 0;
		oppositeColor = 1;
		rtn = client_socket.sendMsg("BB");
		printf("Send BB -> rtn: %d\n", rtn);
		if (rtn != 0) return;
		break;
	
	case 'W': //white
		ownColor = 1;
		oppositeColor = 0;
		rtn = client_socket.sendMsg("BW");
		printf("Send BW -> rtn: %d\n", rtn);
		if (rtn != 0) return;
		break;
	
	default:
		printf("Authorized Failed!\n");
		break;
	}
}

void Reversi::oneRound(int round)
{
	//ÿ�ֿ�ʼǰ��ʼ��
	int STEP = 1;
	step_num = 1; //ÿ�����ܲ���
	black_num = 0; //�ڷ�����
	white_num = 0; //�׷�����
	
	//���������ÿ�
	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
			chess_board[i][j]=-1;
	
	//��ԪĬ��Ϊ����
	chess_board[9][9] = 1; 
	white_num++;

	switch (ownColor)
	{
	case 0: //black
		while (STEP < Max_step) 
		{
			pair<int, int> chess = step(ownColor);  // take action, send message
			
			// lazi only excute after server's message confirm  in observe function
			//�۲캯��ȷ���˷�������Ϣ֮������
			generateOneStepMessage(chess.first, chess.second);

			if (observe() >= 1) break;     // receive RET Code

			if (observe() >= 1) break;    // see white move
			
			STEP++;
		}
		printf("One Round End\n");
		break;
	
	case 1: //white
		while (STEP < Max_step) 
		{
			if (observe() >= 1) break;    // see black move

			pair<int, int> chess = step(ownColor);  // take action, send message
			
			// lazi only excute after server's message confirm  in observe function
			//�۲캯��ȷ���˷�������Ϣ֮������
			generateOneStepMessage(chess.first, chess.second);

			if (observe() >= 1) break;     // receive RET Code

			STEP++;
		}
		printf("One Round End\n");
		break;

	default:
		break;
	}
	saveChessBoard(round);  //�Ը�����ֽ��и���
}

void Reversi::roundOver(int round)
{
	printf("Round %d Over!\n", round);
	// reset initializer
	//���ó�ʼֵ
	ownColor = oppositeColor = -1;
}

int Reversi::observe()
{
	int rtn = 0;
	int recvrtn = client_socket.recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[0]) 
	{
	case 'R':
	{
		switch (client_socket.getRecvMsg()[1])
		{
		case 'Y':   // valid step
			switch (client_socket.getRecvMsg()[2])
			{
			case 'P':   // update chessboard
			{
				int desRow = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int color = (client_socket.getRecvMsg()[7] - '0');
				
				//��������Ϣ�͸�����
				handleMessage(desRow, desCol, color);

				printf("a valid step of : (%d %d)\n", desRow, desCol);
				break;
			}
			case 'N':   // R0N: enemy wrong step
			{
				printf("a true judgement of no step\n");
				break;
			}
			}
			break;
		
		case 'W':
			// invalid step
			switch (client_socket.getRecvMsg()[2]) 
			{
			case 'P': 
			{
				int desRow = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int color = (client_socket.getRecvMsg()[7] - '0');
				printf("Invalid step , server random a true step of : (%d %d)\n", desRow, desCol);
				
				//��������Ϣ�͸�����
				handleMessage(desRow, desCol, color);
				break;
			}
			case 'N': 
			{
				printf("a wrong judgement of no step\n");
				break;
			}
			default:
				break;
			}
			break;
		
		case '1':
			printf("Error -1: Msg format error!\n");
			rtn = -1;
			break;
		
		case '2':
			printf("Error -2: Corrdinate error!\n");
			rtn = -2;
			break;
		
		case '4':
			printf("Error -4: Invalid step!\n");
			rtn = -4;
			break;
		
		default:
			printf("Error -5: Other error!\n");
			rtn = -5;
			break;
		}
		break;
	}
	
	case 'E':
	{
		switch (client_socket.getRecvMsg()[1])
		{
		case '0':
			// game over
			rtn = 2;
			break;
		case '1':
			// round over
			rtn = 1;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return rtn;
}

void Reversi::generateOneStepMessage(int row, int col)
{
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));

	//put row and col in the message
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row / 10;
	msg[3] = '0' + row % 10;
	msg[4] = '0' + col / 10;
	msg[5] = '0' + col % 10;
	msg[6] = '\0';

	//��ӡAI���ɵ�ĳ�����λ��
	printf("generate one step at possition (%2d,%2d) : %s\n", row, col, msg);

	client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/

//�ж�����
bool huosi(int* row, int* col, int my_color); //����
bool chongsi(int* row, int *col, int my_color); //����
bool huosan(int* row, int* col, int my_color); //����
bool huoer(int* row, int* col, int my_color); //���
											  
//Generate a valid step ����һ���Ϸ�����
pair<int, int> Reversi::step(int my_color)
{
	/*����˼·�Ǳ��������ϵ�ÿһ����λ�����ݸ�λ���ĸ�������ܻ��γɵ���������
	�����壬���ģ����ģ�������������������߶����ĸ������и��֣��ҵ���ֵ���Ŀ�λ����
	������ж����ֵ��λ����ѡ�񣬲��������ʽ�Թ�ܶԷ���·�����ˣ�
	*/

	//int attack_point[ROWS][COLS]; //��¼ÿ��λ�õĽ�����ֵ
	//int guard_point[ROWS][COLS]; //��¼ÿ��λ�õķ��ط�ֵ

	//���õ�һ��
	/*ִ�����µ�һ��*/
	if (step_num == 1&&my_color==0)
		return make_pair(8, 9);
	/*ִ�����µ�һ��*/
	if (step_num == 2 && my_color == 1)
	{
		if (chess_board[8][9] == -1)
			return make_pair(8, 9);
		if (chess_board[10][9] == -1)
			return make_pair(10, 9);
		if (chess_board[9][8] == -1)
			return make_pair(9, 8);
		if (chess_board[9][10] == -1)
			return make_pair(9, 10);
	}
	
	int row, col; //��������
	
	if (huosi(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //�ҷ��γ�����
	else if (chongsi(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //�ҷ��γ�����
	else if(huosi(&row, &col, my_color) == true)
		return make_pair(row, col); //��ס�Է����ģ���ȻΪʱ����
	else if (chongsi(&row, &col, my_color) == true)
		return make_pair(row, col); //��ס�Է�����
	else if (huosan(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //�ҷ��γɻ���
	else if (huosan(&row, &col, my_color) == true)
		return make_pair(row, col); //��ס�Է�����
	else if (huoer(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //�ҷ��γɻ���
	else if (huoer(&row, &col, my_color) == true)
		return make_pair(row, col); //��ס�Է����
	else
	{
		int i = 1, j = 1;
		do
		{
			i = rand() % 18;
			j = rand() % 18;
		} while (chess_board[i][j] != -1);

		cout << "�������" << i << " " << j << endl;
		row = i;
		col = j;
		return make_pair(row, col);
	}
}

bool huosi(int* row, int* col, int my_color)
{
	//���������߿ո�
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		for (int j = 1; j < 15; j++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color)
				if (chess_board[i][j - 1] == -1 )
				{
					*row = i;
					*col = j - 1;
					return true;
				}
				else if(chess_board[i][j + 4] == -1)
				{
					*row = i;
					*col = j + 4;
					return true;
				}
		}
	}
	/*����*/
	for (int j = 0; j < 19; j++)
	{
		for (int i = 1; i < 15; i++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == 1 - my_color)
				if (chess_board[i - 1][j] ==-1 )
				{
					*row = i - 1;
					*col = j;
					return true;
				}
			else if(chess_board[i + 4][j] != my_color)
				{
					*row = i + 4;
					*col = j;
					return true;
				}
		}
	}
	/*��б*/
	for (int i = 1; i < 15; i++)
	{
		for (int j = 1; j < 15; j++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == 1 - my_color)
				if (chess_board[i - 1][j - 1] ==-1 )
				{
					*row = i - 1;
					*col = j - 1;
					return true;
				}
				else if (chess_board[i + 4][j + 4] == -1)
				{
					*row = i + 4;
					*col = j + 4;
					return true;
				}
		}
	}
	/*��б*/
	for (int i = 17; i >= 4; i--)
	{
		for (int j = 1; j <= 16; j++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i - 1][j + 1] == 1 - my_color && chess_board[i - 2][j + 2] == 1 - my_color && chess_board[i - 3][j + 3] == 1 - my_color)
				if (chess_board[i + 1][j - 1] ==-1 )
				{
					*row = i + 1;
					*col = j - 1;
					return true;
				}
				else if (chess_board[i - 4][j + 4] == -1)
				{
					*row = i - 4;
					*col = j + 4;
					return true;
				}
		}
	}

	//������һ������һ������������һ����������
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		for (int j = 1; j < 14; j++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == -1 && chess_board[i][j + 4] == 1 - my_color)
			{
				*row = i;
				*col = j + 3;
				return true;//�ĳɹ���
			}
			else if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == -1 && chess_board[i][j + 3] == 1 - my_color && chess_board[i][j + 4] == 1 - my_color)
			{
				*row = i;
				*col = j + 2;
				return true;//�ĳɹ���			
			}
			else if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == -1 && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color && chess_board[i][j + 4] == 1 - my_color)
			{
				*row = i;
				*col = j + 1;
				return true;//�ĳɹ���
			}
		}
	}
		/*����*/
		for (int j = 0; j < 19; j++)
		{
			for (int i = 1; i < 14; i++)
			{
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == -1 && chess_board[i + 4][j] == 1 - my_color)
				{
					*row = i + 3;
					*col = j;
					return true;//�ĳɹ���
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == -1 && chess_board[i + 3][j] == 1 - my_color && chess_board[i + 4][j] == 1 - my_color)
				{
					*row = i + 2;
					*col = j;
					return true;//�ĳɹ���
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == -1 && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == 1 - my_color && chess_board[i + 4][j] == 1 - my_color)
				{
					*row = i + 1;
					*col = j;
					return true;//�ĳɹ���
				}
			}
		}
		/*��б*/
		for (int i = 1; i < 14; i++)
		{
			for (int j = 5; j < 18; j++)
			{
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j - 1] == -1 && chess_board[i + 2][j - 2] == 1 - my_color && chess_board[i + 3][j - 3] == 1 - my_color && chess_board[i + 4][j - 4] == 1 - my_color)
				{
					*row = i + 1;
					*col = j - 1;
					return true;//�ĳɹ���
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == -1 && chess_board[i + 3][j - 3] == 1 - my_color && chess_board[i + 4][j - 4] == 1 - my_color)
				{
					*row = i + 2;
					*col = j - 2;
					return true;//�ĳɹ���
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == 1 - my_color && chess_board[i + 3][j - 3] == -1 && chess_board[i + 4][j - 4] == 1 - my_color)
				{
					*row = i + 3;
					*col = j - 3;
					return true;//�ĳɹ���
				}
			}
		}
		/*��б*/
		for (int i = 1; i < 14; i++)
		{
			for (int j = 1; j < 14; j++)
			{
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == -1 && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == 1 - my_color && chess_board[i + 4][j + 4] == 1 - my_color)
				{
					*row = i + 1;
					*col = j + 1;
					return true;//�ĳɹ���
				}
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == -1 && chess_board[i + 3][j + 3] == 1 - my_color && chess_board[i + 4][j + 4] == 1 - my_color)
				{
					*row = i + 2;
					*col = j + 2;
					return true;//�ĳɹ���
				}
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == -1 && chess_board[i + 4][j + 4] == 1 - my_color)
				{
					*row = i + 3;
					*col = j + 3;
					return true;//�ĳɹ���
				}
			}
		}
	return false;
}

bool chongsi(int* row, int* col,int my_color)
{
	//����---���ݡ�б����������з���
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		//�жϵ�ǰ���Ƿ���������ĸ����ӣ��Ҹ������ĸ����ӵ��������Ҳ����һ������
		for (int j = 0; j < 19; j++)
		{
			if (j <= 15 && chess_board[i][j] == 1 - my_color)
			{
				//�ж��Ƿ���j��ʼ���������ĸ�
				if (chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color)
				{
					//�жϸ������������Ƿ��а��ӻ��������Ѿ�����߽�
					if (j + 3 == 18 && chess_board[i][j - 1] == -1)
					{
						*row = i;
						*col = j - 1;
						return true;//�ĳɹ���
					}
					else if (j == 0 && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 4;
						return true;//�ĳɹ���
					}
					else if (j < 15 && chess_board[i][j - 1] == my_color && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 4;
						return true;//�ĳɹ���
					}
					else if (j > 0 && chess_board[i][j + 4] == my_color && chess_board[i][j - 1] == -1)
					{
						*row = i;
						*col = j - 1;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		//�жϵ�ǰ���Ƿ���������ĸ����ӣ��Ҹ������ĸ����ӵ��������Ҳ����һ������
		for (int j = 0; j < 19; j++)
		{
			if (j <= 15 && chess_board[j][i] == 1 - my_color)
			{
				//�ж��Ƿ���j��ʼ���������ĸ�
				if (chess_board[j + 1][i] == 1 - my_color && chess_board[j + 2][i] == 1 - my_color && chess_board[j + 3][i] == 1 - my_color)
				{
					if (j == 0 && chess_board[j + 4][i] == -1)
					{
						*row = j + 4;
						*col = i;
						return true;//�ĳɹ���
					}
					else if (j + 3 == 18 && chess_board[j - 1][i] == -1)
					{
						*row = j - 1;
						*col = i;
						return true;//�ĳɹ���
					}
					else if (j > 0 && chess_board[j + 4][i] == my_color && chess_board[j - 1][i] == -1)
					{
						*row = j - 1;
						*col = i;
						return true;//�ĳɹ���
					}
					else if (j < 15 && chess_board[j - 1][i] == my_color && chess_board[j + 4][i] == -1)
					{
						*row = j + 4;
						*col = i;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 0; i < 16; i++)
	{
		for (int j = 3; j < 19; j++)
		{
			if (!((i == 0 && j == 3) || (i == 15 && j == 18)))
			{
				if (chess_board[i][j] == 1 - my_color)
				{
					if (chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == 1 - my_color && chess_board[i + 3][j - 3] == 1 - my_color)
					{
						if (i == 0 && chess_board[i + 4][j - 4] == -1)
						{
							*row = i + 4;
							*col = j - 4;
							return true;//�ĳɹ���
						}
						else if (i == 15 && chess_board[i - 1][j + 1] == -1)
						{
							*row = i - 1;
							*col = j + 1;
							return true;//�ĳɹ���
						}
						else if (j == 3 && chess_board[i - 1][j + 1] == -1)
						{
							*row = i - 1;
							*col = j + 1;
							return true;//�ĳɹ���
						}
						else if (j == 18 && chess_board[i + 4][j - 4] == -1)
						{
							*row = i + 4;
							*col = j - 4;
							return true;//�ĳɹ���
						}
						else if (i < 15 && chess_board[i - 1][j + 1] == my_color && chess_board[i + 4][j - 4] == -1)
						{
							*row = i + 4;
							*col = j - 4;
							return true;//�ĳɹ���
						}
						else if (i > 0 && chess_board[i + 4][j - 4] == my_color && chess_board[i - 1][j + 1] == -1)
						{
							*row = i - 1;
							*col = j + 1;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (!(i == 0 && j == 15) || (i == 15 && j == 0))
			{
				if (chess_board[i][j] == 1 - my_color)
				{
					if (chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == 1 - my_color)
					{
						if (i == 0 && chess_board[i + 4][j + 4] == -1)
						{
							*row = i + 4;
							*col = j + 4;
							return true;//�ĳɹ���
						}
						else if (i == 15 && chess_board[i - 1][j - 1] == -1)
						{
							*row = i - 1;
							*col = j - 1;
							return true;//�ĳɹ���
						}
						else if (j == 15 && chess_board[i - 1][j - 1] == -1)
						{
							*row = i - 1;
							*col = j - 1;
							return true;//�ĳɹ���
						}
						else if (j == 0 && chess_board[i + 4][j + 4] == -1)
						{
							*row = i + 4;
							*col = j + 4;
							return true;//�ĳɹ���
						}
						else if (j < 15 && chess_board[i - 1][j - 1] == my_color && chess_board[i + 4][j + 4] == -1)
						{
							*row = i + 4;
							*col = j + 4;
							return true;//�ĳɹ���
						}
						else if (i > 0 && chess_board[i + 4][j + 4] == my_color && chess_board[i - 1][j - 1] == -1)
						{
							*row = i - 1;
							*col = j - 1;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	return false;
}

bool huosan(int* row, int* col, int my_color)
{
	//�������߶��пո� XXX
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		for (int j = 1; j < 16; j++)
		{
			if (chess_board[i][j] == 1-my_color)
			{
				if (chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == 1 - my_color)
				{
					if (chess_board[i][j - 1] == -1 && chess_board[i][j + 3] == -1)
					{
						if (j == 1 || j != 15)
						{
							//��Ȼ���ұ�
							*row = i;
							*col = j + 3;
							return true;//�ĳɹ���
						}
						if (j == 15)
						{
							//��Ȼ�����
							*row = i;
							*col = j - 1;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	/*����*/
	for (int j = 0; j < 19; j++)
	{
		for (int i = 1; i < 16; i++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == 1 - my_color)
				{
					if (chess_board[i - 1][j] == -1 && chess_board[i + 3][j] == -1)
					{
						if (i == 1 || i != 15)
						{
							*row = i + 3;
							*col = j;
							return true;//�ĳɹ���
						}
						else if (i == 15)
						{
							*row = i - 1;
							*col = j;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 1; i < 16; i++)
	{
		for (int j = 3; j < 18; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == 1 - my_color)
				{
					if (chess_board[i - 1][j + 1] == -1 && chess_board[i + 3][j - 3] == -1)
					{
						if (i == 15)
						{
							//��Ȼ���ϱ�
							*row = i - 1;
							*col = j + 1;
							return true;//�ĳɹ���
						}
						else
						{
							//���±�
							*row = i + 3;
							*col = j - 3;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 1; i < 16; i++)
	{
		for (int j = 1; j < 16; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == 1 - my_color)
				{
					if (chess_board[i + 3][j + 3] == -1 && chess_board[i - 1][j - 1] == -1)
					{
						if (i == 1)
						{
							//���±�
							*row = i + 3;
							*col = j + 3;
							return true;//�ĳɹ���
						}
						else
						{
							//���ϱ�
							*row = i - 1;
							*col = j - 1;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	//�м��һ���������пո� XX_X
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		for (int j = 1; j < 15; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == -1 && chess_board[i][j + 3] == 1 - my_color)
				{
					if (chess_board[i][j - 1] == -1 && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 2;
						return true;//�ĳɹ���
					}
				}
				else if (chess_board[i][j + 1] == -1 && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color)
				{
					if (chess_board[i][j - 1] == -1 && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 1;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	/*����*/
	for (int j = 0; j < 19; j++)
	{
		for (int i = 1; i < 15; i++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == -1 && chess_board[i + 3][j] == 1 - my_color)
				{
					if (chess_board[i - 1][j] == -1 && chess_board[i + 4][j] == -1)
					{
						*row = i + 2;
						*col = j;
						return true;//�ĳɹ���
					}
				}
				else if (chess_board[i + 1][j] == -1 && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == 1 - my_color)
				{
					if (chess_board[i - 1][j] == -1 && chess_board[i + 4][j] == -1)
					{
						*row = i + 1;
						*col = j;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 1; i < 15; i++)
	{
		for (int j = 4; j < 18; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j - 1] == -1 && chess_board[i + 2][j - 2] == 1 - my_color && chess_board[i + 3][j - 3] == 1 - my_color)
				{
					if (chess_board[i - 1][j + 1] == -1 && chess_board[i + 4][j - 4] == -1)
					{
						*row = i + 1;
						*col = j - 1;
						return true;//�ĳɹ���
					}
				}
				else if (chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == -1 && chess_board[i + 3][j - 3] == 1 - my_color)
				{
					if (chess_board[i - 1][j + 1] == -1 && chess_board[i + 4][j - 4] == -1)
					{
						*row = i + 2;
						*col = j - 2;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 1; i < 15; i++)
	{
		for (int j = 1; j < 15; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j + 1] == -1 && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == 1 - my_color)
				{
					if (chess_board[i - 1][j - 1] == -1 && chess_board[i + 4][j + 4] == -1)
					{
						*row = i + 1;
						*col = j + 1;
						return true;//�ĳɹ���
					}
				}
				else if (chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == -1 && chess_board[i + 3][j + 3] == 1 - my_color)
				{
					if (chess_board[i - 1][j - 1] == -1 && chess_board[i + 4][j + 4] == -1)
					{
						*row = i + 2;
						*col = j + 2;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	return false;
}

bool huoer(int* row, int* col, int my_color)
{
	//���߶��пո� XX
	/*����*/
	for (int i = 0; i < 19; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == 1 - my_color)
			{
				if (chess_board[i][j - 1] == -1 && chess_board[i][j + 2] == -1)
				{
					if (j == 1 || j != 16)
					{
						//��Ȼ���ұ�
						*row = i;
						*col = j + 2;
						return true;//�ĳɹ���
					}
					if (j == 16)
					{
						//��Ȼ�����
						*row = i;
						*col = j - 1;
						return true;//�ĳɹ���
					}
				}
			}
		}
	}
	/*����*/
	for (int j = 0; j < 19; j++)
	{
		for (int i = 1; i <= 16; i++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == 1 - my_color)
			{
				if (chess_board[i - 1][j] == -1 && chess_board[i + 2][j] == -1)
				{
					if (i == 1 || i != 16)
					{
						*row = i + 2;
						*col = j;
						return true; //�ĳɹ���
					}
					else if (i == 16)
					{
						*row = i - 1;
						*col = j;
						return true; //�ĳɹ���
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 1; i <= 16; i++)
	{
		for (int j = 2; j <= 18; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j - 1] == 1 - my_color)
				{
					if (chess_board[i - 1][j + 1] == -1 && chess_board[i + 2][j - 2] == -1)
					{
						if (i == 16)
						{
							//��Ȼ���ϱ�
							*row = i - 1;
							*col = j + 1;
							return true;//�ĳɹ���
						}
						else
						{
							//���±�
							*row = i + 2;
							*col = j - 2;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	/*��б*/
	for (int i = 1; i <= 16; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j + 1] == 1 - my_color)
				{
					if (chess_board[i + 2][j + 2] == -1 && chess_board[i - 1][j - 1] == -1)
					{
						if (i == 1)
						{
							//���±�
							*row = i + 2;
							*col = j + 2;
							return true;//�ĳɹ���
						}
						else
						{
							//���ϱ�
							*row = i - 1;
							*col = j - 1;
							return true;//�ĳɹ���
						}
					}
				}
			}
		}
	}
	
	//�м��һ���������пո� X_X
	/*����*/
	for (int i = 0; i < 19; i++)
		for (int j = 1; j <= 15; j++)
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i][j + 1] ==-1 && chess_board[i][j + 2] == 1 - my_color)
				{
					if (chess_board[i][j - 1] == -1&&chess_board[i][j + 3] == -1)
					{
						*row = i;
						*col = j + 1;
						return true;//�ĳɹ���
					}
				}
			}
	/*����*/
	for (int j = 0; j < 19; j++)
		for (int i = 1; i <= 15; i++)
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j] == -1 && chess_board[i + 2][j] == 1 - my_color)
				{
					if (chess_board[i - 1][j] == -1&& chess_board[i + 3][j] == -1)
					{
						*row = i + 1;
						*col = j;
						return true;//�ĳɹ���
					}
				}
			}
	/*��б*/
	for (int i = 1; i <= 15; i++)
		for (int j = 3; j < 18; j++)
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j - 1] == -1 && chess_board[i + 2][j - 2] == 1 - my_color)
				{
					if (chess_board[i - 1][j + 1] == -1&&chess_board[i + 3][j - 3] == -1)
					{
						*row = i + 1;
						*col = j - 1;
						return true;//�ĳɹ���
					}
				}
			}
	/*��б*/
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
			if (chess_board[i][j] == 1 - my_color)
			{
				if (chess_board[i + 1][j + 1] == -1 && chess_board[i + 2][j + 2] == 1 - my_color)
				{
					if (chess_board[i - 1][j - 1] == -1 && chess_board[i + 3][j + 3] == -1)
					{
						*row = i + 1;
						*col = j + 1;
						return true;//�ĳɹ���
					}
				}
			}
	return false;
}

//��ӡͼ�λ�����
void DisplayBoard()
{
	/*************************************************
   *
   *���Ʊ����Ҫ���ַ�:�� �� ���� �� �ȩ� �� ���������
   *�����ֵ0��ʾ���壬1��ʾ���壬-1��ʾ��λ��û����
   *
   */
	for (int i = 0; i < 19; i++)
	{
		//��0��
		if (i == 0)
		{
			//��0��
			if (chess_board[i][0] == 1)
				printf("��");
			if (chess_board[i][0] == 0)
				printf("��");
			if (chess_board[i][0] == -1)
				printf("�� ");

			//��1-17��
			for (int j = 1; j <= 17; j++)
			{
				if (chess_board[i][j] == 1)
					printf("��");
				if (chess_board[i][j] == 0)
					printf("��");
				if (chess_board[i][j] == -1)
					printf("�� ");
			}

			//��18��
			if (chess_board[i][18] == 1)
				printf("��");
			if (chess_board[i][18] == 0)
				printf("��");
			if (chess_board[i][18] == -1)
				printf("�� ");

			printf("\n");
		}

		//��1-17��
		if (i <= 17 && i >= 1)
		{
			//��0��
			if (chess_board[i][0] == 1)
				printf("��");
			if (chess_board[i][0] == 0)
				printf("��");
			if (chess_board[i][0] == -1)
				printf("�� ");

			//��1-17��
			for (int j = 1; j <= 17; j++)
			{
				if (chess_board[i][j] == 1)
					printf("��");
				if (chess_board[i][j] == 0)
					printf("��");
				if (chess_board[i][j] == -1)
					printf("�� ");
			}

			//��18��
			if (chess_board[i][18] == 1)
				printf("��");
			if (chess_board[i][18] == 0)
				printf("��");
			if (chess_board[i][18] == -1)
				printf("�� ");

			printf("\n");
		}

		//��18��
		if (i == 18)
		{
			//��0��
			if (chess_board[i][0] == 1)
				printf("��");
			if (chess_board[i][0] == 0)
				printf("��");
			if (chess_board[i][0] == -1)
				printf("�� ");

			//��1-17��
			for (int j = 1; j <= 17; j++)
			{
				if (chess_board[i][j] == 1)
					printf("��");
				if (chess_board[i][j] == 0)
					printf("��");
				if (chess_board[i][j] == -1)
					printf("�� ");
			}

			//��18��
			if (chess_board[i][18] == 1)
				printf("��");
			if (chess_board[i][18] == 0)
				printf("��");
			if (chess_board[i][18] == -1)
				printf("�� ");

			printf("\n");
		}
	}
}

//ÿ�ֽ����󱣴���������Ϣ��д�븴���ļ�
void Reversi::saveChessBoard(int round)
{
	//������Ϣд���ļ�����ʽΪ����+��ɫ(0,1)+��+��
	string round_s;
	if (round == 0)	round_s = "round_0";
	if (round == 1)	round_s = "round_1";
	if (round == 2)	round_s = "round_2";
	string address = "D:\\NJU" + round_s + ".txt";
	ofstream out_file(address, ios::out);
	out_file << 0 << " " << 1 << " " << 9 << " " <<9<< endl;
	for (int i = 1; i < step_num; i++)
	{
		out_file << i << " " << all_step[i].color << " " << all_step[i].row << " " << all_step[i].col << endl;
	}

	//��ӡ�����������
	DisplayBoard();
	
	//��ӡ������Ϣ
	cout << "��0������0���ڵ�9�е�9��" << endl;
	for (int i = 1; i < step_num; i++)
	{
		cout << "��" << i << "����";
		if (all_step[i].color == 0)
			cout << "��" << all_step[i].num;
		else if (all_step[i].color == 1)
			cout << "��" << all_step[i].num;
		cout << "�����ڵ�" << all_step[i].row << "��" << all_step[i].col << "��";
		cout << endl;
	}
	if (all_step[step_num - 1].color == 0)
		cout << "�ڷ���ʤ��" << endl;
	else
		cout << "�׷���ʤ��" << endl;
}

//��ȡ�����ļ���Ϣ����ͨ�����¼�ʵ�ָ���
void Replay(int round)
{
	string round_s;
	if (round == 0)	round_s = "round_0";
	if (round == 1)	round_s = "round_1";
	if (round == 2)	round_s = "round_2";
	string address = "D:\\NJU" + round_s+".txt";
	ifstream in_file(address, ios::in);
	if (in_file.is_open() == 0)
		cout << "���ļ�����" << endl;

	cout << "��ʼ���̵�" << round << "�֣�ʹ�ü����������ҿ���ǰ��ҳ��Esc���˳�����" << endl;

	//���̳�ʼ��
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			chess_board[i][j] = -1;

	//��ԪĬ��Ϊ����
	chess_board[9][9] = 1;
	int step=0;
	while (in_file.peek() != EOF)
	{
		int a;
		in_file >> a;
		in_file >> all_step[step].color;
		in_file >> all_step[step].row;
		in_file >> all_step[step].col;
		step++;
	}
	 
	//��ӡ��ʼʱ������
	cout << "��0������0���ڵ�9�е�9��" << endl;
	DisplayBoard();

	//ͨ���������Ҽ����Ʒ�ҳ
	int i = 0;
	int ch;
	while (i>=0 &&i <= step-1&&(ch=_getch())!=0x1B)
	{
		switch (ch)
		{
		case 0xE0:
			switch (ch = _getch())
			{
			case 72:  //��
				i--;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "��" << i << "����";
				if (all_step[i].color == 0)
					cout << "��" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "��" << all_step[i].num;
				cout << "�����ڵ�" << all_step[i].row << "��" << all_step[i].col << "��";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			case 80:  //��
				i++;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "��" << i << "����";
				if (all_step[i].color == 0)
					cout << "��" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "��" << all_step[i].num;
				cout << "�����ڵ�" << all_step[i].row << "��" << all_step[i].col << "��";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			case 75:  //��
				i--;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "��" << i << "����";
				if (all_step[i].color == 0)
					cout << "��" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "��" << all_step[i].num;
				cout << "�����ڵ�" << all_step[i].row << "��" << all_step[i].col << "��";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			case 77:  //�� 
				i++;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "��" << i << "����";
				if (all_step[i].color == 0)
					cout << "��" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "��" << all_step[i].num;
				cout << "�����ڵ�" << all_step[i].row << "��" << all_step[i].col << "��";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			default:
				break;
			}
			break;
		
		default:
			break;
		}
		if (i <= 0)
			cout << "�Ѿ��ǵ�һ���ˣ�" << endl;
		if (i >= step-1)
			cout << "�Ѿ������һ���ˣ�" << endl;
	}

}

//�������������Ϣ��ʵ�ֽ���
void Reversi::handleMessage(int row, int col, int color)
{
	//��������������ĳһ�������Ϣд�뱾������
	chess_board[row][col] = color;
	
	//����һ�������Ϣд�븴����Ϣ�ṹ������
	all_step[step_num].color = color;
	all_step[step_num].row = row;
	all_step[step_num].col = col;
	if (color == 0)
	{
		all_step[step_num].num = black_num;
		black_num++;
	}
	else if (color == 1)
	{
		all_step[step_num].num = white_num;
		white_num++;
	}
	step_num++;   //����ܲ���+1
}

//�������*��,��*:.��(������)/$:*.���* ��