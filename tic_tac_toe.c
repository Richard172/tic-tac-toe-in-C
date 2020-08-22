#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char grid(int digit)
{
	if (digit == 0)
	{
		return '-';
	}
	else if (digit == -1)
	{
		return 'X';
	}
	else if (digit == 1)
	{
		return 'O';
	}
}

int valid(int game[3][3], int x, int y)
{
	if (x < 0 || y < 0 || x > 2 || y > 2)
	{
		return 0;
	}
	if (game[x][y] == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void print_game(int game[3][3])
{
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", grid(game[0][0]), grid(game[0][1]), grid(game[0][2]));
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", grid(game[1][0]), grid(game[1][1]), grid(game[1][2]));
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", grid(game[2][0]), grid(game[2][1]), grid(game[2][2]));
	printf("+---+---+---+\n");
}

void game_rule()
{
	printf("\nHere's the rule for tic tac toe:\n\n");
	printf("The game board is a 3 by 3 matrix grid.\n");
	printf("The first player plays X, and the second player plays O.\n");
	printf("Whoever gets 3 of his/her marks in a row(horizontally, vertically, diagonally) wins.\n");
	printf("When the game board is full with no players winning, the game ends with a draw for both player.\n\n");
}

int draw(int game[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game[i][j] == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int winning(int game[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		int vo = 1, vx = 1, ho = 1, hx = 1, dlo = 1, dlx = 1, dro = 1, drx = 1;
		for (int j = 0; j < 3; j++)
		{
			if (game[i][j] != -1)
			{
				hx = 0;
			}
			if (game[i][j] != 1)
			{
				ho = 0;
			}
			if (game[j][i] != -1)
			{
				vx = 0;
			}
			if (game[j][i] != 1)
			{
				vo = 0;
			}
			if (game[j][j] != -1)
			{
				dlx = 0;
			}
			if (game[j][j] != 1)
			{
				dlo = 0;
			}
			if (game[j][2 - j] != -1)
			{
				drx = 0;
			}
			if (game[j][2 - j] != 1)
			{
				dro = 0;
			}
		}
		if (vx == 1 || hx == 1 || dlx == 1 || drx == 1)
		{
			return -1;
		}
		if (vo == 1 || ho == 1 || dlo == 1 || dro == 1)
		{
			return 1;
		}
	}
	return 0;
}

int minimax(int game[3][3], int player, int* x, int* y)
{
	int win = winning(game);
	if (win != 0)
	{
		return win * player;
	}
	
	int row = -1;
	int column = -1;
	int score = -2;
	int new_score;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game[i][j] == 0)
			{
				game[i][j] = player;
				new_score = -minimax(game, -player, x, y);
				game[i][j] = 0;
				if (new_score > score)
				{
					score = new_score;
					row = i;
					column = j;
				}
			}
		}
	}
	
	*x = row;
	*y = column;
	
	if (row == -1 || column == -1)
	{
		return 0;
	}
	return score;
}

void computer(int game[3][3], int player)
{
	int x, y;
	minimax(game, player, &x, &y);
	
	game[x][y] = player;
	printf("\nComputer's turn:\n\n");
	print_game(game);
}

void player_turn(int game[3][3], int player)
{
	int row = -1, column = -1;
	int validness = valid(game, row, column);
	
	while (validness == 0)
	{
		printf("Print the row number: (1-3)\n");
		scanf("%d", &row);
		printf("Prinf the column number: (1-3)\n");
		scanf("%d", &column);
		
		
		validness = valid(game, row - 1, column - 1);
		if (validness == 0)
		{
			printf("Invalid input!! Please try again\n");
		}
	}
	game[row - 1][column - 1] = player;
	print_game(game);
}

void condition(int game[3][3], int player)
{
	if (winning(game) == 0)
	{
		printf("Draw!!\n\n");
	}
	if (player == -1 && winning(game) == -1)
	{
		printf("Player wins!\n\n");
	}
	if (player == -1 && winning(game) == 1)
	{
		printf("Computer wins!\n\n");
	}
	if (player == 1 && winning(game) == -1)
	{
		printf("Computer wins!\n\n");
	}
	if (player == 1 && winning(game) == 1)
	{
		printf("Player wins!\n\n");
	}
}

int main()
{
	
	
	float query = -1.0;
	
	while (query != 0.0)
	{
		
		srand(time(0));
		int coin = rand() % 2;
		int player;
		int col, row;
		int initial = 0;
		
		(coin == 1) ? (player = -1) : (player = 1);
		
		int game[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
		};
		
		printf("Please choose one of the following digits:\n\n");
		printf("(0). Halt the program.\n");
		printf("(1). see the rule of the game.\n");
		printf("(2). Play tic tac toe (first player is randomly generated).\n");
		printf("(3). Play tic tac toe (You choose who goes first and second).\n");
		
		scanf("%f", &query);
		
		if (query == 0.0)
		{
			printf("Exiting the game...\n");
		}
		else if (query == 1.0)
		{
			game_rule();
		}
		else if (query == 2.0)
		{
			
			if (player == -1)
			{	
				printf("Player goes first, computer goes second.\n\n");
				player_turn(game, player);
			}
			else
			{
				printf("Computer goes first, player goes second.\n\n");
			}
			while (draw(game) == 0 && winning(game) == 0)
			{
				computer(game, -player);
				if (winning(game) != 0)
				{
					break;
				}
				player_turn(game, player);
			}
			
			condition(game, player);
		}
		else if (query == 3.0)
		{
			
			while (initial < 1 || initial > 2)
			{
				printf("Do you want to go (1)st or (2)nd?\n");
				scanf("%d", &initial);
				
				if (initial < 1 || initial > 2)
				{
					printf("Invalid input, please try again (1 - 2)\n\n");
				}
			}
			
			(initial == 1) ? (player = -1) : (player = 1);
		
			if (player == -1)
			{
				printf("Player goes first, computer goes second.\n\n");
				player_turn(game, player);
			}
			else
			{
				printf("Computer goes first, player goes second.\n\n");
			}
			while (draw(game) == 0 && winning(game) == 0)
			{
				computer(game, -player);
				if (winning(game) != 0)
				{
					break;
				}
				player_turn(game, player);
			}
			
			condition(game, player);
		}
		
		else
		{
			printf("Please input a valid integer.\n\n");
		}
	}
}