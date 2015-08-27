
#include <string.h>
#include <stdio.h>
#include <Python/Python.h>
#include <ctime>
#include <cstdlib>
#define BOARD 9
#define INF 100
#define PLAYER_2 2
#define PLAYER_1 1
#define DEBUG 0
int TicTacToeAI(char * stateBoard, int player);
int minNode(char * board);
int maxNode(char * board);
bool is_winner(char * board, char player);
bool is_full(char * board);
void printBoard(char * board)
{
	for (int i = 0; i < BOARD; i++)
	{
		if (board[i] == 0)
			printf("-");
		else if (board[i] == 1)
			printf("X");
		else if (board[i] == 2)
			printf("O");
		if ((i+1) % 3  == 0)
			printf("\n");
	}
	printf("evalueation:");
}
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

	char evaluation = -INF;
	if (is_winner(board, PLAYER_2))
		evaluation = -1;
	else if (is_full(board))
		evaluation = 0;
	else
	{
		//µ±Ç°½áµã¹ÀÖµ
		char temp;
		for (int i = 0; i < BOARD; i++)
		{
			if (board[i] == 0)
			{
				board[i] = PLAYER_1;
				temp = maxNode(board);
				if (temp > evaluation)
					evaluation = temp;	//×îÐ¡¹ÀÖµ
				board[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
			}
		}
	}
#if DEBUG
	printBoard(board);
	printf("%d\n", evaluation);
#endif
	return evaluation;
}
int maxNode(char * board)		//player1
{
	char evaluation = INF;
	if (is_winner(board, PLAYER_1))
		evaluation=1;
	else if (is_full(board))
		evaluation=0;
	else
	{
			//µ±Ç°½áµã¹ÀÖµ
		char temp;
		for (int i = 0; i < BOARD; i++)
		{
			if (board[i] == 0)
			{
				board[i] = PLAYER_2;
				temp = minNode(board);
				if (temp < evaluation)
					evaluation = temp;	//×îÐ¡¹ÀÖµ
				board[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
			}
		}
	}
#if DEBUG
	printBoard(board);
	printf("%d\n", evaluation);
#endif
	return evaluation;
}
int TicTacToeAI(char * stateBoard, int player)		//play1:max player2:min
{
	//Minmax
	char probablyWin[BOARD];
	char probablyWinEvaluation[BOARD];
	char win[BOARD];
	int index;
	int probablyWin_cnt = 0;
	int win_cnt = 0;
	char evaluation;
	if (player == PLAYER_1)
	{
		evaluation = -INF;		//µ±Ç°½áµã¹ÀÖµ
		char temp;
		for (int i = 0; i < BOARD; i++)
		{
			if (stateBoard[i] == 0)
			{
				stateBoard[i] = PLAYER_1;
				temp = maxNode(stateBoard);
				if (temp >= evaluation)
				{
					index = i;			//Î¨Ò»µÄÂä×Ó·½·¨
					probablyWin[probablyWin_cnt] = i;
					probablyWinEvaluation[probablyWin_cnt++] = temp;
					evaluation = temp;	//×îÐ¡¹ÀÖµ
				}
				stateBoard[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
			}
		}
#if DEBUG
		printBoard(stateBoard);
		printf("%d\n", evaluation);
#endif
	}
	else if (player == PLAYER_2)
	{
		evaluation = INF;		//µ±Ç°½áµã¹ÀÖµ
		char temp;
		for (int i = 0; i < BOARD; i++)
		{
			if (stateBoard[i] == 0)
			{
				stateBoard[i] = PLAYER_2;
				temp = minNode(stateBoard);
				if (temp <= evaluation)
				{
					index = i;		//Î¨Ò»µÄÂä×Ó·½·¨
					probablyWin[probablyWin_cnt] = i;
					probablyWinEvaluation[probablyWin_cnt++] = temp;
					evaluation = temp;	//×îÐ¡¹ÀÖµ
				}
				stateBoard[i] = 0;		//»Ö¸´µ±Ç°×´Ì¬
			}
		}
#if DEBUG
		printBoard(stateBoard);
		printf("%d\n", evaluation);
#endif
	}
	for (int i = 0; i < probablyWin_cnt;i++)		//find the places which hava a max evaluation
	if (probablyWinEvaluation[i] == evaluation)
			win[win_cnt++] = probablyWin[i];
	srand((unsigned)time(NULL));
	int random=rand()%win_cnt;
	return win[random];		//randomly choose one place where have a probability to win
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
	free(c_stateBoard);
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