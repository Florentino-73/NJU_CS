#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"
#include<fstream>
#include<conio.h>

#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3
#define Max_step 500

//维护的本地棋盘，-1代表空位，0代表落黑子，1代表落白子
int chess_board[ROWS][COLS]; 

//记录每一步棋的结构体用于复盘，包括哪方在哪里落子，是该方的第几步
struct step_msg
{
	int color;
	int row;
	int col;
	int num; //对应某一方的第几步
};

step_msg all_step[Max_step]; //每轮棋局所有步数构成的的结构体数组

int step_num = 0; //每轮棋总步数
int black_num = 0; //黑方步数
int white_num = 0; //白方步数

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
 send id and password to server by socket 通过接口将id和密码传送给服务器
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char* id, const char* pass) //授权
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

//用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
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
	cout << "是否进行复盘？1.YES;    2.NO" << endl;
	cout << "请输入指令：";
	int choice;
	cin >> choice;
	while(choice == 1)
	{
		cout << "请选择复盘的轮数(0,1,2)：";
		int round;
		cin >> round;
		Replay(round);
		cout << "是否继续进行复盘？1.YES;    2.NO" << endl;
		cout << "请输入指令：";
		cin >> choice;
	}
	cout << "复盘结束！" << endl;
		
}

//发一次消息，走哪一步，等两个消息，1.自己的步数行不行   2.对面走了哪一步 
void Reversi::roundStart(int round)
{
	printf("Round %d Ready Start!\n", round);

	// first time receive msg from server
	int rtn = client_socket.recvMsg();
	if (rtn != 0) return;
	if (strlen(client_socket.getRecvMsg()) < 2)
		printf("Authorize Failed!\n"); //授权失败
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
	//每轮开始前初始化
	int STEP = 1;
	step_num = 1; //每轮棋总步数
	black_num = 0; //黑方步数
	white_num = 0; //白方步数
	
	//本地棋盘置空
	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
			chess_board[i][j]=-1;
	
	//天元默认为白子
	chess_board[9][9] = 1; 
	white_num++;

	switch (ownColor)
	{
	case 0: //black
		while (STEP < Max_step) 
		{
			pair<int, int> chess = step(ownColor);  // take action, send message
			
			// lazi only excute after server's message confirm  in observe function
			//观察函数确认了服务器信息之后落子
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
			//观察函数确认了服务器信息之后落子
			generateOneStepMessage(chess.first, chess.second);

			if (observe() >= 1) break;     // receive RET Code

			STEP++;
		}
		printf("One Round End\n");
		break;

	default:
		break;
	}
	saveChessBoard(round);  //对该轮棋局进行复盘
}

void Reversi::roundOver(int round)
{
	printf("Round %d Over!\n", round);
	// reset initializer
	//重置初始值
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
				
				//将棋盘信息送给本地
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
				
				//将棋盘信息送给本地
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

	//打印AI生成的某步棋的位置
	printf("generate one step at possition (%2d,%2d) : %s\n", row, col, msg);

	client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/

//判断棋形
bool huosi(int* row, int* col, int my_color); //活四
bool chongsi(int* row, int *col, int my_color); //冲四
bool huosan(int* row, int* col, int my_color); //活三
bool huoer(int* row, int* col, int my_color); //活二
											  
//Generate a valid step 生成一步合法的棋
pair<int, int> Reversi::step(int my_color)
{
	/*整体思路是遍历棋盘上的每一个空位，根据该位置四个方向可能会形成的特殊棋形
	（连五，活四，冲四，活三，眠三，活二，眠二）的个数进行赋分，找到分值最大的空位落子
	（如果有多个等值空位可以选择，采用随机方式以规避对方套路机器人）
	*/

	//int attack_point[ROWS][COLS]; //记录每个位置的进攻分值
	//int guard_point[ROWS][COLS]; //记录每个位置的防守分值

	//设置第一步
	/*执黑子下第一步*/
	if (step_num == 1&&my_color==0)
		return make_pair(8, 9);
	/*执白子下第一步*/
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
	
	int row, col; //返回坐标
	
	if (huosi(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //我方形成连五
	else if (chongsi(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //我方形成连五
	else if(huosi(&row, &col, my_color) == true)
		return make_pair(row, col); //堵住对方活四（虽然为时已晚）
	else if (chongsi(&row, &col, my_color) == true)
		return make_pair(row, col); //堵住对方冲四
	else if (huosan(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //我方形成活四
	else if (huosan(&row, &col, my_color) == true)
		return make_pair(row, col); //堵住对方活三
	else if (huoer(&row, &col, 1 - my_color) == true)
		return make_pair(row, col); //我方形成活三
	else if (huoer(&row, &col, my_color) == true)
		return make_pair(row, col); //堵住对方活二
	else
	{
		int i = 1, j = 1;
		do
		{
			i = rand() % 18;
			j = rand() % 18;
		} while (chess_board[i][j] != -1);

		cout << "随机落子" << i << " " << j << endl;
		row = i;
		col = j;
		return make_pair(row, col);
	}
}

bool huosi(int* row, int* col, int my_color)
{
	//四连，两边空格
	/*横向*/
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
	/*纵向*/
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
	/*右斜*/
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
	/*左斜*/
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

	//三连空一个再连一个或者两连空一个再连两个
	/*横向*/
	for (int i = 0; i < 19; i++)
	{
		for (int j = 1; j < 14; j++)
		{
			if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == -1 && chess_board[i][j + 4] == 1 - my_color)
			{
				*row = i;
				*col = j + 3;
				return true;//赌成功了
			}
			else if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == -1 && chess_board[i][j + 3] == 1 - my_color && chess_board[i][j + 4] == 1 - my_color)
			{
				*row = i;
				*col = j + 2;
				return true;//赌成功了			
			}
			else if (chess_board[i][j] == 1 - my_color && chess_board[i][j + 1] == -1 && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color && chess_board[i][j + 4] == 1 - my_color)
			{
				*row = i;
				*col = j + 1;
				return true;//赌成功了
			}
		}
	}
		/*纵向*/
		for (int j = 0; j < 19; j++)
		{
			for (int i = 1; i < 14; i++)
			{
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == -1 && chess_board[i + 4][j] == 1 - my_color)
				{
					*row = i + 3;
					*col = j;
					return true;//赌成功了
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == 1 - my_color && chess_board[i + 2][j] == -1 && chess_board[i + 3][j] == 1 - my_color && chess_board[i + 4][j] == 1 - my_color)
				{
					*row = i + 2;
					*col = j;
					return true;//赌成功了
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j] == -1 && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == 1 - my_color && chess_board[i + 4][j] == 1 - my_color)
				{
					*row = i + 1;
					*col = j;
					return true;//赌成功了
				}
			}
		}
		/*左斜*/
		for (int i = 1; i < 14; i++)
		{
			for (int j = 5; j < 18; j++)
			{
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j - 1] == -1 && chess_board[i + 2][j - 2] == 1 - my_color && chess_board[i + 3][j - 3] == 1 - my_color && chess_board[i + 4][j - 4] == 1 - my_color)
				{
					*row = i + 1;
					*col = j - 1;
					return true;//赌成功了
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == -1 && chess_board[i + 3][j - 3] == 1 - my_color && chess_board[i + 4][j - 4] == 1 - my_color)
				{
					*row = i + 2;
					*col = j - 2;
					return true;//赌成功了
				}
				else if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == 1 - my_color && chess_board[i + 3][j - 3] == -1 && chess_board[i + 4][j - 4] == 1 - my_color)
				{
					*row = i + 3;
					*col = j - 3;
					return true;//赌成功了
				}
			}
		}
		/*右斜*/
		for (int i = 1; i < 14; i++)
		{
			for (int j = 1; j < 14; j++)
			{
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == -1 && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == 1 - my_color && chess_board[i + 4][j + 4] == 1 - my_color)
				{
					*row = i + 1;
					*col = j + 1;
					return true;//赌成功了
				}
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == -1 && chess_board[i + 3][j + 3] == 1 - my_color && chess_board[i + 4][j + 4] == 1 - my_color)
				{
					*row = i + 2;
					*col = j + 2;
					return true;//赌成功了
				}
				if (chess_board[i][j] == 1 - my_color && chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == 1 - my_color && chess_board[i + 3][j + 3] == -1 && chess_board[i + 4][j + 4] == 1 - my_color)
				{
					*row = i + 3;
					*col = j + 3;
					return true;//赌成功了
				}
			}
		}
	return false;
}

bool chongsi(int* row, int* col,int my_color)
{
	//冲四---横纵、斜几个情况进行分析
	/*横向*/
	for (int i = 0; i < 19; i++)
	{
		//判断当前行是否存在连续四个黑子，且该连续四个黑子的左侧或者右侧存在一个白子
		for (int j = 0; j < 19; j++)
		{
			if (j <= 15 && chess_board[i][j] == 1 - my_color)
			{
				//判断是否会从j开始出现连续四个
				if (chess_board[i][j + 1] == 1 - my_color && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color)
				{
					//判断该四连的左右是否有白子或者左右已经到达边界
					if (j + 3 == 18 && chess_board[i][j - 1] == -1)
					{
						*row = i;
						*col = j - 1;
						return true;//赌成功了
					}
					else if (j == 0 && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 4;
						return true;//赌成功了
					}
					else if (j < 15 && chess_board[i][j - 1] == my_color && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 4;
						return true;//赌成功了
					}
					else if (j > 0 && chess_board[i][j + 4] == my_color && chess_board[i][j - 1] == -1)
					{
						*row = i;
						*col = j - 1;
						return true;//赌成功了
					}
				}
			}
		}
	}
	/*纵向*/
	for (int i = 0; i < 19; i++)
	{
		//判断当前行是否存在连续四个黑子，且该连续四个黑子的左侧或者右侧存在一个白子
		for (int j = 0; j < 19; j++)
		{
			if (j <= 15 && chess_board[j][i] == 1 - my_color)
			{
				//判断是否会从j开始出现连续四个
				if (chess_board[j + 1][i] == 1 - my_color && chess_board[j + 2][i] == 1 - my_color && chess_board[j + 3][i] == 1 - my_color)
				{
					if (j == 0 && chess_board[j + 4][i] == -1)
					{
						*row = j + 4;
						*col = i;
						return true;//赌成功了
					}
					else if (j + 3 == 18 && chess_board[j - 1][i] == -1)
					{
						*row = j - 1;
						*col = i;
						return true;//赌成功了
					}
					else if (j > 0 && chess_board[j + 4][i] == my_color && chess_board[j - 1][i] == -1)
					{
						*row = j - 1;
						*col = i;
						return true;//赌成功了
					}
					else if (j < 15 && chess_board[j - 1][i] == my_color && chess_board[j + 4][i] == -1)
					{
						*row = j + 4;
						*col = i;
						return true;//赌成功了
					}
				}
			}
		}
	}
	/*左斜*/
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
							return true;//赌成功了
						}
						else if (i == 15 && chess_board[i - 1][j + 1] == -1)
						{
							*row = i - 1;
							*col = j + 1;
							return true;//赌成功了
						}
						else if (j == 3 && chess_board[i - 1][j + 1] == -1)
						{
							*row = i - 1;
							*col = j + 1;
							return true;//赌成功了
						}
						else if (j == 18 && chess_board[i + 4][j - 4] == -1)
						{
							*row = i + 4;
							*col = j - 4;
							return true;//赌成功了
						}
						else if (i < 15 && chess_board[i - 1][j + 1] == my_color && chess_board[i + 4][j - 4] == -1)
						{
							*row = i + 4;
							*col = j - 4;
							return true;//赌成功了
						}
						else if (i > 0 && chess_board[i + 4][j - 4] == my_color && chess_board[i - 1][j + 1] == -1)
						{
							*row = i - 1;
							*col = j + 1;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	/*右斜*/
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
							return true;//赌成功了
						}
						else if (i == 15 && chess_board[i - 1][j - 1] == -1)
						{
							*row = i - 1;
							*col = j - 1;
							return true;//赌成功了
						}
						else if (j == 15 && chess_board[i - 1][j - 1] == -1)
						{
							*row = i - 1;
							*col = j - 1;
							return true;//赌成功了
						}
						else if (j == 0 && chess_board[i + 4][j + 4] == -1)
						{
							*row = i + 4;
							*col = j + 4;
							return true;//赌成功了
						}
						else if (j < 15 && chess_board[i - 1][j - 1] == my_color && chess_board[i + 4][j + 4] == -1)
						{
							*row = i + 4;
							*col = j + 4;
							return true;//赌成功了
						}
						else if (i > 0 && chess_board[i + 4][j + 4] == my_color && chess_board[i - 1][j - 1] == -1)
						{
							*row = i - 1;
							*col = j - 1;
							return true;//赌成功了
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
	//三连两边都有空格 XXX
	/*横向*/
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
							//必然堵右边
							*row = i;
							*col = j + 3;
							return true;//赌成功了
						}
						if (j == 15)
						{
							//必然堵左边
							*row = i;
							*col = j - 1;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	/*纵向*/
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
							return true;//赌成功了
						}
						else if (i == 15)
						{
							*row = i - 1;
							*col = j;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	/*左斜*/
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
							//必然堵上边
							*row = i - 1;
							*col = j + 1;
							return true;//赌成功了
						}
						else
						{
							//赌下边
							*row = i + 3;
							*col = j - 3;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	/*右斜*/
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
							//赌下边
							*row = i + 3;
							*col = j + 3;
							return true;//赌成功了
						}
						else
						{
							//堵上边
							*row = i - 1;
							*col = j - 1;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	//中间空一个且两边有空格 XX_X
	/*横向*/
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
						return true;//赌成功了
					}
				}
				else if (chess_board[i][j + 1] == -1 && chess_board[i][j + 2] == 1 - my_color && chess_board[i][j + 3] == 1 - my_color)
				{
					if (chess_board[i][j - 1] == -1 && chess_board[i][j + 4] == -1)
					{
						*row = i;
						*col = j + 1;
						return true;//赌成功了
					}
				}
			}
		}
	}
	/*纵向*/
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
						return true;//赌成功了
					}
				}
				else if (chess_board[i + 1][j] == -1 && chess_board[i + 2][j] == 1 - my_color && chess_board[i + 3][j] == 1 - my_color)
				{
					if (chess_board[i - 1][j] == -1 && chess_board[i + 4][j] == -1)
					{
						*row = i + 1;
						*col = j;
						return true;//赌成功了
					}
				}
			}
		}
	}
	/*左斜*/
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
						return true;//赌成功了
					}
				}
				else if (chess_board[i + 1][j - 1] == 1 - my_color && chess_board[i + 2][j - 2] == -1 && chess_board[i + 3][j - 3] == 1 - my_color)
				{
					if (chess_board[i - 1][j + 1] == -1 && chess_board[i + 4][j - 4] == -1)
					{
						*row = i + 2;
						*col = j - 2;
						return true;//赌成功了
					}
				}
			}
		}
	}
	/*右斜*/
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
						return true;//赌成功了
					}
				}
				else if (chess_board[i + 1][j + 1] == 1 - my_color && chess_board[i + 2][j + 2] == -1 && chess_board[i + 3][j + 3] == 1 - my_color)
				{
					if (chess_board[i - 1][j - 1] == -1 && chess_board[i + 4][j + 4] == -1)
					{
						*row = i + 2;
						*col = j + 2;
						return true;//赌成功了
					}
				}
			}
		}
	}
	return false;
}

bool huoer(int* row, int* col, int my_color)
{
	//两边都有空格 XX
	/*横向*/
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
						//必然堵右边
						*row = i;
						*col = j + 2;
						return true;//赌成功了
					}
					if (j == 16)
					{
						//必然堵左边
						*row = i;
						*col = j - 1;
						return true;//赌成功了
					}
				}
			}
		}
	}
	/*纵向*/
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
						return true; //赌成功了
					}
					else if (i == 16)
					{
						*row = i - 1;
						*col = j;
						return true; //赌成功了
					}
				}
			}
		}
	}
	/*左斜*/
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
							//必然堵上边
							*row = i - 1;
							*col = j + 1;
							return true;//赌成功了
						}
						else
						{
							//赌下边
							*row = i + 2;
							*col = j - 2;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	/*右斜*/
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
							//赌下边
							*row = i + 2;
							*col = j + 2;
							return true;//赌成功了
						}
						else
						{
							//堵上边
							*row = i - 1;
							*col = j - 1;
							return true;//赌成功了
						}
					}
				}
			}
		}
	}
	
	//中间空一个且两边有空格 X_X
	/*横向*/
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
						return true;//赌成功了
					}
				}
			}
	/*纵向*/
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
						return true;//赌成功了
					}
				}
			}
	/*左斜*/
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
						return true;//赌成功了
					}
				}
			}
	/*右斜*/
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
						return true;//赌成功了
					}
				}
			}
	return false;
}

//打印图形化棋盘
void DisplayBoard()
{
	/*************************************************
   *
   *绘制表格需要的字符:┌ ┬ ┐├ ┼ ┤└ ┴ ┘│─●○
   *数组的值0表示黑棋，1表示白棋，-1表示该位置没有棋
   *
   */
	for (int i = 0; i < 19; i++)
	{
		//第0行
		if (i == 0)
		{
			//第0列
			if (chess_board[i][0] == 1)
				printf("●");
			if (chess_board[i][0] == 0)
				printf("○");
			if (chess_board[i][0] == -1)
				printf("┌ ");

			//第1-17列
			for (int j = 1; j <= 17; j++)
			{
				if (chess_board[i][j] == 1)
					printf("●");
				if (chess_board[i][j] == 0)
					printf("○");
				if (chess_board[i][j] == -1)
					printf("┬ ");
			}

			//第18列
			if (chess_board[i][18] == 1)
				printf("●");
			if (chess_board[i][18] == 0)
				printf("○");
			if (chess_board[i][18] == -1)
				printf("┐ ");

			printf("\n");
		}

		//第1-17行
		if (i <= 17 && i >= 1)
		{
			//第0列
			if (chess_board[i][0] == 1)
				printf("●");
			if (chess_board[i][0] == 0)
				printf("○");
			if (chess_board[i][0] == -1)
				printf("├ ");

			//第1-17列
			for (int j = 1; j <= 17; j++)
			{
				if (chess_board[i][j] == 1)
					printf("●");
				if (chess_board[i][j] == 0)
					printf("○");
				if (chess_board[i][j] == -1)
					printf("┼ ");
			}

			//第18列
			if (chess_board[i][18] == 1)
				printf("●");
			if (chess_board[i][18] == 0)
				printf("○");
			if (chess_board[i][18] == -1)
				printf("┤ ");

			printf("\n");
		}

		//第18行
		if (i == 18)
		{
			//第0列
			if (chess_board[i][0] == 1)
				printf("●");
			if (chess_board[i][0] == 0)
				printf("○");
			if (chess_board[i][0] == -1)
				printf("└ ");

			//第1-17列
			for (int j = 1; j <= 17; j++)
			{
				if (chess_board[i][j] == 1)
					printf("●");
				if (chess_board[i][j] == 0)
					printf("○");
				if (chess_board[i][j] == -1)
					printf("┴ ");
			}

			//第18列
			if (chess_board[i][18] == 1)
				printf("●");
			if (chess_board[i][18] == 0)
				printf("○");
			if (chess_board[i][18] == -1)
				printf("┘ ");

			printf("\n");
		}
	}
}

//每轮结束后保存该轮棋的信息并写入复盘文件
void Reversi::saveChessBoard(int round)
{
	//复盘信息写入文件，格式为步数+颜色(0,1)+行+列
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

	//打印结束后的棋盘
	DisplayBoard();
	
	//打印复盘信息
	cout << "第0步：白0落在第9行第9列" << endl;
	for (int i = 1; i < step_num; i++)
	{
		cout << "第" << i << "步：";
		if (all_step[i].color == 0)
			cout << "黑" << all_step[i].num;
		else if (all_step[i].color == 1)
			cout << "白" << all_step[i].num;
		cout << "落子在第" << all_step[i].row << "行" << all_step[i].col << "列";
		cout << endl;
	}
	if (all_step[step_num - 1].color == 0)
		cout << "黑方获胜！" << endl;
	else
		cout << "白方获胜！" << endl;
}

//读取复盘文件信息，并通过上下键实现复盘
void Replay(int round)
{
	string round_s;
	if (round == 0)	round_s = "round_0";
	if (round == 1)	round_s = "round_1";
	if (round == 2)	round_s = "round_2";
	string address = "D:\\NJU" + round_s+".txt";
	ifstream in_file(address, ios::in);
	if (in_file.is_open() == 0)
		cout << "打开文件错误！" << endl;

	cout << "开始复盘第" << round << "轮，使用键盘上下左右控制前后翻页，Esc键退出复盘" << endl;

	//棋盘初始化
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			chess_board[i][j] = -1;

	//天元默认为白子
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
	 
	//打印开始时的棋盘
	cout << "第0步：白0落在第9行第9列" << endl;
	DisplayBoard();

	//通过上下左右键控制翻页
	int i = 0;
	int ch;
	while (i>=0 &&i <= step-1&&(ch=_getch())!=0x1B)
	{
		switch (ch)
		{
		case 0xE0:
			switch (ch = _getch())
			{
			case 72:  //上
				i--;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "第" << i << "步：";
				if (all_step[i].color == 0)
					cout << "黑" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "白" << all_step[i].num;
				cout << "落子在第" << all_step[i].row << "行" << all_step[i].col << "列";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			case 80:  //下
				i++;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "第" << i << "步：";
				if (all_step[i].color == 0)
					cout << "黑" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "白" << all_step[i].num;
				cout << "落子在第" << all_step[i].row << "行" << all_step[i].col << "列";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			case 75:  //左
				i--;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "第" << i << "步：";
				if (all_step[i].color == 0)
					cout << "黑" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "白" << all_step[i].num;
				cout << "落子在第" << all_step[i].row << "行" << all_step[i].col << "列";
				cout << endl;

				for (int j = 0; j <= i; j++)
					chess_board[all_step[j].row][all_step[j].col] = all_step[j].color;
				DisplayBoard();
				break;

			case 77:  //右 
				i++;
				for (int i = 0; i < 19; i++)
					for (int j = 0; j < 19; j++)
						chess_board[i][j] = -1;

				cout << "第" << i << "步：";
				if (all_step[i].color == 0)
					cout << "黑" << all_step[i].num;
				else if (all_step[i].color == 1)
					cout << "白" << all_step[i].num;
				cout << "落子在第" << all_step[i].row << "行" << all_step[i].col << "列";
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
			cout << "已经是第一步了！" << endl;
		if (i >= step-1)
			cout << "已经是最后一步了！" << endl;
	}

}

//处理服务器的信息，实现交互
void Reversi::handleMessage(int row, int col, int color)
{
	//将服务器传来的某一步棋的信息写入本地棋盘
	chess_board[row][col] = color;
	
	//将这一步棋的信息写入复盘信息结构体数组
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
	step_num++;   //棋局总步数+1
}

//完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。