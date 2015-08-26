
#include <string.h>
#include <stdio.h>
#include <Python/Python.h>
#include <ctime>
#include <cstdlib>
#define BOARD 9
#define INF 100
#define PLAYER_2 2
#define PLAYER_1 1
int TicTacToeAI(char * stateBoard, int player);
int minNode(char * board);
int maxNode(char * board);
bool is_winner(char * board, char player);
bool is_full(char * board);

bool is_winner(char * board, char player)
{
	if (board[0] == player&&board[1] == player&&board[2] == player)return true;
	if (board[3] == player&&board[4] == player&&board[5] == player)return true;
	if (board[6] == player&&board[7] == player&&board[8] == player)return true;
	if (board[0] == player&&board[3] == player&&board[6] == player)return true;
	if (board[1] == player&&board[4] == player&&board[7] == player)return true;
	if (board[2] == player&&board[5] == player&&board[8] == player)return true;
	if (board[0] == player&&board[4] == player&&board[8] == player)return true;
	if (board[2] == player&&board[4] == player&&board[6] == player)return true;
	return false;
}
bool is_full(char * board)
{
	for (int i = 0; i < BOARD; i++)
		if (board[i]==0)
			return false;
	return true;
}
int minNode(char * board)		//player2
{
	if (is_winner(board, PLAYER_2))
		return -1;
	else if (is_full(board))
		return 0;
	char evaluation = INF;		//µ±Ç°½áµã¹ÀÖµ
	char temp;
	for (int i = 0; i < BOARD; i++)
	{
		if (board[i] == 0)
		{
			board[i] = PLAYER_1;
			temp = maxNode(board);
			if (temp < evaluation)
				evaluation = temp;	//×îÐ¡¹ÀÖµ
			board[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
		}
	}
	return evaluation;
}
int maxNode(char * board)		//player1
{
	if (is_winner(board, PLAYER_1))
		return 1;
	else if (is_full(board))
		return 0;
	char evaluation = -INF;		//µ±Ç°½áµã¹ÀÖµ
	char temp;
	for (int i = 0; i < BOARD; i++)
	{
		if (board[i] == 0)
		{
			board[i] = PLAYER_2;
			temp = minNode(board);
			if (temp > evaluation)
				evaluation = temp;	//×îÐ¡¹ÀÖµ
			board[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
		}
	}
	return evaluation;
}
int TicTacToeAI(char * stateBoard, int player)		//play1:max player2:min
{
	//Minmax
	char pos[BOARD];
	int cnt=0;

	if (player == PLAYER_1)
	{
		char evaluation = -INF;		//µ±Ç°½áµã¹ÀÖµ
		char temp;
		for (int i = 0; i < BOARD; i++)
		{
			if (stateBoard[i] == 0)
			{
				stateBoard[i] = PLAYER_1;
				temp = maxNode(stateBoard);
				if (temp >= evaluation)
				{
					pos[cnt++] = i;			//Î¨Ò»µÄÂä×Ó·½·¨
					evaluation = temp;	//×îÐ¡¹ÀÖµ
				}
				stateBoard[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
			}
		}
	}
	else if (player == PLAYER_2)
	{
		char evaluation = INF;		//µ±Ç°½áµã¹ÀÖµ
		char temp;
		for (int i = 0; i < BOARD; i++)
		{
			if (stateBoard[i] == 0)
			{
				stateBoard[i] = PLAYER_2;
				temp = minNode(stateBoard);
				if (temp <= evaluation)
				{
					pos[cnt++] = i;			//Î¨Ò»µÄÂä×Ó·½·¨
					evaluation = temp;	//×îÐ¡¹ÀÖµ
				}
				stateBoard[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
			}
		}
	}
	srand((unsigned)time(NULL));
	int random=rand()%cnt;
	return pos[random];
}
//Python 包装C++函数
static PyObject *
TicTacToeAI_TicTacToeAI(PyObject * self,PyObject * args)
{
	char * c_stateBoard;
	int player;
	int pos;
	if(!PyArg_ParseTuple(args,"si",&c_stateBoard,&player))
		return NULL;
	for(int i=0;i<BOARD;i++)
		c_stateBoard[i]-='0';
	pos=TicTacToeAI(c_stateBoard,player);
	//free(c_stateBoard);
	return (PyObject*)Py_BuildValue("i",pos);
}
static PyMethodDef TicTacToeAIMethods[]={
	{"TicTacToeAI",TicTacToeAI_TicTacToeAI,METH_VARARGS,NULL},
	{NULL,NULL,0,NULL}
};
extern "C"
void initTicTacToeAI()
{
	Py_InitModule("TicTacToeAI",TicTacToeAIMethods);
}