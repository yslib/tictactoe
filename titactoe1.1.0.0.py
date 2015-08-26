# coding:utf-8
import sys
from TicTacToeAI import TicTacToeAI as t_ai             #C++写的AI
'tic tac toe'

#global variables
style=['X','O']
player_1='O'     # X OR O
player_2='X'     # O OR X
steps=0
board=[0 for i in range(10)]
#functions
def draw_board():
    count=0
    sys.stdout.write(' '*5)
    for i in range(1,10):
        if board[i]==1:
            sys.stdout.write(player_1)
            sys.stdout.write(' '*5)
        elif board[i]==2:
            sys.stdout.write(player_2)
            sys.stdout.write(' '*5)
        elif board[i]==0:
            sys.stdout.write(str(i))
            sys.stdout.write(' '*5)
        if (count+1)%3==0:
            print ' '
            print ' '
            sys.stdout.write(' '*5)
        count+=1

def is_winner(player):
    if board[1]==player and board[2]==player and board[3]==player:
        return True
    if board[4]==player and board[5]==player and board[6]==player:
        return True
    if board[7]==player and board[8]==player and board[9]==player:
        return True
    if board[1]==player and board[4]==player and board[7]==player:
        return True
    if board[2]==player and board[5]==player and board[8]==player:
        return True
    if board[3]==player and board[6]==player and board[9]==player:
        return True
    if board[1]==player and board[5]==player and board[9]==player:
        return True
    if board[3]==player and board[5]==player and board[7]==player:
        return True
    return False

def is_full_board():
    if steps==9:
        return True
    return False
def go(player,position):

    if board[int(position)]!=0:
        return False
    board[int(position)]=player
    return True
def choose_player_style():
     while True:
        global player_1
        global player_2
        global style
        player_1=raw_input()
        player_1.upper()
        if player_1=='X':
            player_2='O'
        elif player_1=='O':
            player_2='X'
        else:
            print "you input the wrong choice,please enter again('X' or 'O'):"
            continue
        style[0]=player_1
        style[1]=player_2
        break
def get_player_step():
    while True:
        step=raw_input()

        if isinstance(step,str) and int(step)<=9 and int(step)>=1:
            return step
        print 'Wrong place .try again'
if __name__=="__main__":
    print "welcome to TIC TAC TOE!"
    pos=''
    while True:
        steps=0
        board=[0 for i in range(10)]
        again=False
        over_full=False
        over_win=False
        print "choose X or O that you like:"
        choose_player_style()
        draw_board()
        while True:
            player=(steps)%2+1          #which player
            print "waiting player",style[player-1],"go"
            while True:
                if(player==1):
                    str_state=""
                    for i in range(1,10):
                        str_state+=str(board[i])
                    pos=t_ai(str_state,player)+1
                else:
                    pos=get_player_step()
                if not go(player,pos):
                    print "this place have already been hold，try again"
                    continue
                break
            steps+=1
            draw_board()
            if is_winner(player):
                over_win=True
            if is_full_board():
                over_full=True
            if over_win or over_full:
                break
        while True:
            if over_win==True:
                print "congratulations.player ",style[player-1]," win!"
            else:
                print "ooh,the board is full"
            print "Try again?(y or n)"
            ans=raw_input().lower()
            if ans=='y':
                again=True
                break
            elif ans=='n':
                again=False
                break
            else:
                print "uuh?"
        if again==False:
            break
