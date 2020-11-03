// Implements Game of Fifteen (generalized to d x d)

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 9
#define COLOR "\033[32m"

// Board
int board[DIM_MAX][DIM_MAX];

// Dimensions
int d;

// Saved locations of the blank tile
int blank_row;
int blank_col;

// Prototypes
void clear(void);

void greet(void);

void init(void);

void draw(void);

bool move(int tile);

bool won(void);

void swap(int *a, int *b);

void print_grid_row(int d);

void print_tile(int tile);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // Ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
               DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // Open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // Greet user with instructions
    greet();

    // Initialize the board
    init();

    // Accept moves until game is won
    while (true)
    {
        // Clear the screen
        clear();

        // Draw the current state of the board
        draw();

        // Log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // Check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // Prompt for move
        int tile = get_int("Tile to move: ");

        // Quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // Log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // Move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // Sleep thread for animation's sake
        usleep(50000);
    }

    // Close log
    fclose(file);

    // Success
    return 0;
}

// Clears screen using ANSI escape sequences
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

// Greets player
void greet(void)
{
    clear();
    printf("WELCOME TO THE GAME OF FIFTEEN\n");
    usleep(2000000);
}

// Initializes the game's board with tiles numbered 1 through d*d - 1
// (i.e., fills 2D array with values but does not actually print them)
void init(void)
{
    blank_col = d - 1;
    blank_row = d - 1;

    int current_tile = d * d - 1;
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (current_tile < 1)
            {
                break;
            }
            else if (current_tile == 2)
            {
                // Do we have to swap the order of the 2 and the 1?
                // That is to say, is d even?

                if (d % 2 == 0)
                {
                    // Swap the order of 2 and 1
                    board[row][col] = 1;
                    board[row][col + 1] = 2;

                    // Skip ahead so that it will enter the first if statement on next loop
                    current_tile = 1;
                }
            }

            board[row][col] = current_tile;

            current_tile--;
        }
    }
}

// Prints the board in its current state
void draw(void)
{
    // For each tile, print 2 characters and then separate columns with 2 spaces
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            int current_tile = board[row][col];

            if (current_tile == 0)
            {
                printf(" _  ");
            }
            else
            {
                // Does this need a leading space? (Is it 1 digit or 2 digits?)
                if (current_tile / 10 == 0)
                {
                    printf(" ");
                }

                // Print the number with the trailing column-separating spaces
                printf("%d  ", current_tile);
            }
        }

        printf("\n");
    }
}

// If tile borders empty space, moves tile and returns true, else returns false
bool move(int tile)
{
    // Find the tile's row and col
    int tile_row = -1, tile_col = -1;

    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col] == tile)
            {
                tile_row = row;
                tile_col = col;
                break;
            }
        }
    }

    if (tile_row == -1 || tile_col == -1)
    {
        return 0; // Could not find tile in board, return false
    }

    printf("\ntile_row, tile_col: %d, %d; blank_row, blank_col: %d, %d\n", tile_row, tile_col, blank_row, blank_col);


    // Does this tile border empty space? Swap and return true if so
    if ((abs(tile_row - blank_row) == 1 && tile_col == blank_col) ||
        (abs(tile_col - blank_col) == 1 && tile_row == blank_row))
    {
        board[blank_row][blank_col] = tile;
        board[tile_row][tile_col] = 0;

        // Update blank row and col
        blank_row = tile_row;
        blank_col = tile_col;

        return 1;
    }

    return 0;
}

// Returns true if game is won (i.e., board is in winning configuration), else false
bool won(void)
{
    // Is the blank in the bottom right corner?
    if (blank_row != d - 1 || blank_col != d - 1)
    {
        return 0;
    }

    // Is the board in increasing order?
    int current_expected_tile_value = 1;

    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (row != blank_row || col != blank_col)
            {
                // This is not the blank tile's location
                if (board[row][col] != current_expected_tile_value)
                {
                    return 0;
                }

                current_expected_tile_value++;
            }
        }
    }

    return 1;
}
