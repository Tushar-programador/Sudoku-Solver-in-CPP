#include <iostream>
#include <ctime>
using namespace std;
#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if it is safe to place a number in the given cell
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check if 'num' is not in the current row
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num)
        {
            return false;
        }
    }

    // Check if 'num' is not in the current column
    for (int x = 0; x < N; x++)
    {
        if (grid[x][col] == num)
        {
            return false;
        }
    }

    // Check if 'num' is not in the current 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N], int &recursionCount)
{
    int row, col;
    bool isEmpty = false;

    // Find an empty cell
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
        {
            break;
        }
    }

    // No empty cell means the puzzle is solved
    if (!isEmpty)
    {
        return true;
    }

    // Try placing digits 1-9 in the empty cell
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            recursionCount++;

            if (solveSudoku(grid, recursionCount))
            {
                return true;
            }

        
            grid[row][col] = 0;
        }
    }

    return false; 
}

// Function to generate a random Sudoku puzzle 
void generatePuzzle(int grid[N][N], int filledCells)
{
    
    srand(time(0));
    for (int i = 0; i < filledCells; i++)
    {
        int row = rand() % N;
        int col = rand() % N;
        int num = rand() % 9 + 1;
        if (grid[row][col] == 0 && isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
        }
    }
}

int main()
{
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    int recursionCount = 0;

   
    cout << "Initial Sudoku Puzzle:" << endl;
    printGrid(grid);

    // Solve the puzzle
    if (solveSudoku(grid, recursionCount))
    {
        cout << "\nSolved Sudoku Puzzle:" << endl;
        printGrid(grid);
        cout << "\nTotal Recursion Calls: " << recursionCount << endl;
    }
    else
    {
        cout << "No solution exists" << endl;
    }


    cout << "\nGenerated Sudoku Puzzle:" << endl;
    int newGrid[N][N] = {0}; // Clear the grid
    generatePuzzle(newGrid, 30);
    printGrid(newGrid);

    return 0;
}
