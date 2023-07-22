#include <stdio.h>

void init_board (void);
void draw_board (void);
int numb_players (void);
int play_again (void);
int square_valid (int);
int game_done (void);
int find_sos (int, int, char);
void two_player (void);
int find_square (void);
void player_move(int);
void comp_play(void);
void comp_move(void);
void winner (void);
void how_big(void);
int comp_find_os (void);
int comp_find_ss (void);

char board[50][50];
int Player1, Player2, Computer, players, n;

int main ()
{
	while(1)
	{
		how_big();
		init_board();
		if(numb_players()==1)
		{
			players=1;
			comp_play();
		}
		else
		{
			players=2;
			two_player();
		}
                if(game_done())
                {
                        printf("Game done!\n");
			winner();
			
			if (!play_again())
                	{
                        	break;
                	}

                }
	} 	
	return 0;
}

void init_board()
{
	for (int row = 0; row < n; row++)
	{
		for (int col=0; col<n; col++)
		{
			board[row][col]=' ';
		}
	}
	Player1 = 0;
	Player2 = 0;
	Computer = 0;
	
	return;
}

void draw_board()
{
	int row, col;
	printf("\n");
	for (int row=0; row<n; row++)
	{
		printf(" *"); 
		for (col=0; col<n; col++)
		{
			printf(" %c *",board[row][col]);
		}
		printf(" \n");
		if (row != n)
		{
			printf(" ");
			for(int ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("*");
			}
			printf(" \n");
		}
	}
	printf("\n");		
	if(players == 1)
	{
		printf("Player has %d points, while I have %d points.\n", Player1, Computer);
	}
	else if (players == 2)
	{
		printf("Player 1 has %d points, while Player 2 has %d points.\n", Player1, Player2);
	}
	return;
}

int numb_players()
{
	char answer;
	
	printf("How many players are playing? (1 or 2)\n");
	do 
	{
		answer = getchar();
	} while((answer !='1') && (answer !='2'));
	
	if(answer == '1')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void how_big()
{

        printf("The board is nxn, how big do you want n to be (1-50)\n");
        do
        {
                scanf("%d", &n);
        } while((n==0) && (n>50));
	
	return;
}

int play_again()
{
  char response;

  printf("Do you want to play again? (y/n) \n");
  do
  {
    response = getchar();

  }while ((response != 'y') && (response != 'Y') &&
       (response != 'n') && (response != 'N'));

  if ((response == 'y') || (response == 'Y'))
  {
     return 1;
  }
  else
  {
    return 0;
  }
}

int game_done()
{
	int row, col;
	
	for (row=0; row<n; row++)
	{
		for(col=0; col<n; col++)
		{
			if (board[row][col] == ' ')
			{
				return 0;
			}
		}
	}
	
	return 1;
}

int square_valid (int square)
{
   int row, col;
   
   if(square>0 && square<((n*n)+1))
   {	
	row = (square-1)/n;
	col = (square-1)%n;

	if (board[row][col]==' ')
	{
		return 1;
	}
	else 
	{
		return 0;
	} 
  }
  else
  {
	return 0;	
  }
}

void two_player()
{
	do
	{
		player_move(1);
		if(game_done())
		{ 
			return;
		}
		player_move(2);
	}while (!game_done());

	return;	
}

void player_move(int player)
{
  int square;
  int row, col;
  char symbol;

  do
  {
	draw_board();
        printf("\nPlayer %d enter a square: \n",player);

	do
	{
		scanf("%d", &square);
	}while (!square_valid(square));

	row = (square-1)/n;
	col = (square-1)%n;
	
	printf("What symbol do you want to enter in square %d? (S or O) \n", square);
	do
	{
		symbol = getchar();
	}while ((symbol != 'S') && (symbol != 's') && (symbol != 'O') && (symbol != 'o') && (symbol != '0'));

	if((symbol == 'S') || (symbol == 's'))
	{
		symbol = 'S';
	}
	else 
	{
		symbol = 'O';	
	}

	board[row][col] = symbol;
   }while(find_sos (square, player, symbol)); 
   
   return;
}

int find_sos (int square, int player, char symbol)
{
	int row,col,sos;
	
	row = (square-1)/n;
	col = (square-1)%n;
	sos = 0;
	
  if(symbol == 'S')
  {
	if ((board[row][col-2] == 'S') && (board[row][col-1] == 'O'))
	{
		sos++;
	}
	if ((board[row][col+1]== 'O') && (board[row][col+2] == 'S'))
	{
		sos++;
	}	
	if((board[row+1][col] == 'O') && (board[row+2][col] == 'S'))
	{
		sos++;
	}
	if((board[row-1][col] == 'O') && (board[row-2][col] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col+1] == 'O') && (board[row+2][col+2] == 'S'))
	{
		sos++;
	}
	if((board[row-1][col-1] == 'O') && (board[row-2][col-2] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col-1] == 'O') && (board[row+2][col-2] == 'S'))
	{
		sos++;
	}
	if((board[row-1][col+1] == 'O') && (board[row-2][col+2] == 'S'))
	{
		sos++;
	}
  }
  else if(symbol == 'O')
  {
	if((board[row+1][col] == 'S') && (board[row-1][col] == 'S'))
	{
		sos++;
	}
	if((board[row][col+1] == 'S') && (board[row][col-1] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col+1] == 'S') && (board[row-1][col-1] == 'S'))
	{
		sos++;
	}
	if((board[row+1][col-1] == 'S') && (board[row-1][col+1] == 'S'))
	{
		sos++;
	}
  }



        if (player == 1)
        {
                Player1= Player1+sos;
        }
        else if (player == 2)
        {
                 Player2= Player2+sos;
        }
        else if (player == 3)
        {
                 Computer= Computer+sos;
        }
	


	if (sos>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void winner()
{
	if ((Player1 > Player2) && (Player1 > Computer))
	{
		printf("Player 1 won!\n");
	}
	else if (Player2> Player1)
	{
		printf("Player 2 won!\n");
	}
	else if (Computer > Player1)
	{ 
		printf("I won!\n");
	}
	else
	{
		printf("Game is a draw\n");
	}
}

void comp_play()
{
	do
	{
		player_move(1);
		if (!game_done())
		{
			comp_move();
		}
	}while(!game_done());

	return;
}

int find_square()
{
	int row, col, square;
	
	for (square=1; square<((n*n)+1); square++)
	{
		row = (square-1)/n;
		col = (square-1)%n;
		if (board[row][col] == ' ')
		{
			return square;
		}
	}
	return 0;
}

void comp_move()
{
	
  int square;
  int row, col;
  char symbol;

  do
  {
        draw_board();
	if(comp_find_os())
	{
		square = comp_find_os();
		symbol = 'S';
	}
	else if(comp_find_ss())
	{
		square = comp_find_ss();
		symbol = 'O';
	}
	else
	{
		square = find_square();
		symbol = 'S';
	}
	row = (square-1)/n;
	col = (square-1)%n;
        
   	board[row][col] = symbol;
	printf("I am putting a %c in %d square\n", symbol, square);
   }while(find_sos (square, 3, symbol));

   return;
}

int comp_find_os ()
{
	int square;

	for (int ii=0; ii<n; ii++)
	{
		for(int jj=0; jj<n; jj++)
		{
		   square = ((ii*n) +jj)+1;
		   if(square_valid(square))
		   {
			if((board[ii][jj+1]=='O') && (board[ii][jj+2] == 'S'))
			{
				return square;
			}
                       if((board[ii][jj-1]=='O') && (board[ii][jj-2] == 'S'))
                        {
                                return square;
                        }
			if ((board[ii+1][jj] == 'O') && (board[ii+2][jj] =='S'))
			{
				return square;
			}
                        if ((board[ii-1][jj] == 'O') && (board[ii-2][jj] =='S'))
                        {
                                return square;
                        }
			if((board[ii+1][jj+1] == 'O') && (board[ii+2][jj+2] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii-1][jj-1] == 'O') && (board[ii-2][jj-2] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii+1][jj-1] == 'O') && (board[ii+2][jj-2] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii-1][jj+1] == 'O') && (board[ii-2][jj+2] == 'S'))
                        {
                                return square;
                        }
		  }
		}
	}
	return 0;
}

int comp_find_ss()
{
	int square;

        for (int ii=0; ii<n; ii++)
        {
                for(int jj=0; jj<n; jj++)
                {  
                   square = ((ii*n) +jj)+1;

                   if(square_valid(square))
                   {

		        if((board[ii][jj+1]=='S') && (board[ii][jj-1] == 'S'))
                        {
                                return square;
                        }
                        if ((board[ii+1][jj] == 'S') && (board[ii-1][jj] =='S'))
                        {
                                return square;
                        }
                        if((board[ii+1][jj+1] == 'S') && (board[ii-1][jj-1] == 'S'))
                        {
                                return square;
                        }
                        if((board[ii+1][jj-1] == 'S') && (board[ii-1][jj+1] == 'S'))
                        {
                                return square;
                        }
                  }
		}
        }
	return 0;
}
