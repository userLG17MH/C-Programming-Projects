#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 3

// Function to check for a winner [ Winner Winner Chicken Dinner ]

char checkWinner(char grid[SIZE][SIZE]) 

{
    // Check rows and columns
    
    for (int i = 0; i < SIZE; i++) 
	{
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ')
            return grid[i][0]; 
            
			// Row winner
            
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ')
            return grid[0][i]; 
            
			// Column winner
    }

    // Checking diagonals
    
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ')
        return grid[0][0];
        
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ')
        return grid[0][2];

    // No winner -_-,
    
    return ' ';
}
    // Function to check for a draw [-_-]
    
    int isDraw(char grid[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
	{
        for (int j = 0; j < SIZE; j++) 
		{
            if (grid[i][j] == ' ')
                return 0;
                
				// Found an empty cell, not a draw :)
        }
    }
    return 1;
    
	// No empty cells, It's a draw :)
}

int main() 
{
    // Initializing / Making a 3x3 grid
    
    char grid[SIZE][SIZE] = 
    {
        {' ', ' ', ' '}, 
        {' ', ' ', ' '}, 
        {' ', ' ', ' '}
    };
	
    int row, col, player = 1;
    char mark, winner;

    while (1) 
    {
        // Displaying the grid
        
        printf("\n");
        printf(" %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
        printf("---|---|---\n");
        printf(" %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
        printf("---|---|---\n");
        printf(" %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);

        // Determining the current player's mark
        
        mark = (player == 1) ? 'X' : 'O';

        // Input row and column Designing
        
        printf("Player %d (%c), enter your position as row and column (e.g., 0 1): ", player, mark);
        
		if (scanf("%d %d", &row, &col) != 2) 
        {
            printf("Invalid input! Please enter two integers separated by a space.\n");
            while (getchar() != '\n');
            
			// Clearing the input buffer
			
            continue;
        }

        // Validating input
        
        if (row < 0 || row > 2 || col < 0 || col > 2) 
        {
            printf("Invalid position! Rows and columns must be between 0 and 2. Please try again.\n");
            continue;
        }

        if (grid[row][col] != ' ') 
        {
            printf("Position Already Taken! Please Try Again.\n");
            continue;
        }

        // Placing the mark
        
        grid[row][col] = mark;

        // Checking for a winner
        
        winner = checkWinner(grid);
        
        if (winner != ' ') 
		{
            printf("\nPlayer %d (%c) WINs!\n", (winner == 'X' ? 1 : 2), winner);
            break;
        }

        //  Draw Checking (If Happens)
        
        if (isDraw(grid)) 
		{
            printf("\n !! MATCH DRAW !! \n");
            break;
        }

        // Switching player
        
        player = (player == 1) ? 2 : 1;
    }

    // Final grid display For Winner
    
        printf("\nFinal Grid:\n");
		printf(" %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
		printf("---|---|---\n");
		printf(" %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
		printf("---|---|---\n");
		printf(" %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);

    return 0;
}
