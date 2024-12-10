/*
 * 	-----------------------SUDOKU SOLVER-----------------------
 * 
 * 					   Coder: Grant Knowlton
 * 							02/03/2023
 * 
 * ------------------------------------------------------------
 * 	This application requests input from the user in the form
 * 	of 9x9 integer arrays (Sudoku boards).  The user can input
 *  as many 9x9 sudoku squares as they wish, as long as the
 *  list ends with a board of all zeros.
 * 	
 * 	Example board:
 * 	1 2 3 4 5 6 7 8 9
 *  4 5 6 7 8 9 1 2 3
 *  7 8 9 1 2 3 4 5 6
 *  2 3 1 5 6 4 8 9 7
 *  5 6 4 8 9 7 2 3 1
 *  8 9 7 2 3 1 0 6 4
 *  3 1 2 6 4 5 9 7 8
 *  6 4 5 9 7 8 3 1 2
 *  9 7 8 3 1 2 6 4 5
 * 	
 * 	The program will then determine which case problem it must
 *  solve (1 missing number, 2 missing numbers, or 3 missing
 *  numbers), and calculate the correct number to go in each
 *  missing position.  After calculations, it will return the 
 *  correct values and their location in the format of:
 *  (row, column, value)
 * 
 * 	Once the program has calculated all the missing values in
 * 	each board, it will terminate the program after printing
 *  the string "END".
 * 
 */

// import java scanner class :D
import java.util.Scanner;

public class SudokuSolver
{
	// The correct sum for each row
	public final static int correctSum = 45;
	
	// A number representing the side length of the sudoku board
	public final static int boardDimension = 9;
	
    public static void main(String[] args)
    {
        // Create scanner :3
    	Scanner scnr = new Scanner(System.in);
    	
    	// The variable to store the current working board
    	int currentBoard[][] = new int[boardDimension][boardDimension];
    	
    	// Arrays for position of each zero
		int posZeros[][] = new int[3][2];
    	
    	// The number of zeros in current board 0_0
    	int numZeros = 0;
    	
    	// The correct value for each location
    	int correctValues[] = new int[3];
    	
    	// A boolean variable for storing if the current board is the final board
    	boolean isEndingBoard = false;
    	
    	// Reads the first board into currentBoard, count number of zeros, 
    	// store location of each zero.  Declares generic i and j iterators.
    	for(int i = 0; i < boardDimension; i++)
    	{
    		for(int j = 0; j < boardDimension; j++)
    		{
    			// Stores the row number and column number into the first row of the posZeros array.
				// Then it increments numZeros so that the next found zero can be stored in the next
				// row.
    			if((currentBoard[i][j] = scnr.nextInt()) == 0 && numZeros < 3)
    			{
    				
    				posZeros[numZeros][0] = i;
    				posZeros[numZeros][1] = j;
    				numZeros++;
    			}
    			// This runs if a fourth zero is found.  It will set i to boardDimension so that
    			// when we break from the for(int j) loop the i loop will end as well.
    			else if(currentBoard[i][j] == 0)
	    		{
    				numZeros++;
	    			i = boardDimension;
	    			break;
	    		}
    		}
    	}
    	// Indent for the eventual output values
    	System.out.println();
    	
    	// Tests if the first board is either invalid or the ending board
    	if(numZeros > 3)
    	{
    		System.out.print("END");
    		isEndingBoard = true;
    		
    	}
    	
    	// Run while board is not the ending board
    	while(!isEndingBoard)
    	{
    		// Case 1: The number of 0s in the board is 1
    		if(numZeros == 1)
    		{
    			// Calls the calculateValueForOneMissing function, which finds a missing value if it is solvable
    			// using the function.  Since this is the case for one zero, it will only run the function once.
    			// This section will run the function with the current board and the row/column number of the only
    			// zero, then stores the found solution in the array for correct values at the first address.
    			correctValues[0] = calculateValueForOneMissing(currentBoard, posZeros[0][0], posZeros[0][1]);
    		}
    		// Case 2: The number of 0s in the board is 2
    		else if(numZeros == 2)
    		{
    			// Essentially the same as the case for one zero, but it will run the function twice for both sets
    			// of row/column values, and stores the second found value at the second address in the correct values
    			// array.
    			correctValues[0] = calculateValueForOneMissing(currentBoard, posZeros[0][0], posZeros[0][1]);
    			correctValues[1] = calculateValueForOneMissing(currentBoard, posZeros[1][0], posZeros[1][1]);
    		}
    		// Case 3: The number of 0s in the board is 3
    		else
    		{
    			// The expression in the if statement will assign the first correct value to the output of the 
    			// calculateValueForOneMissing function. If the function returns 0 (Meaning the current location is
    			// unsolvable with the function), then this if statement will run.  If the function returns an actual
    			// solved value it will run the expressions under else.
    			if((correctValues[0] = calculateValueForOneMissing(currentBoard, posZeros[0][0], posZeros[0][1])) == 0)
    			{
    				// In the case of the first selected value is unsolvable with the function, the easy workaround for
    				// this situation is to solve the next set of column/row values, add that to the current board array
    				// at the right location, then solve for the other two values as normal.  The first values returning
    				// zero means that the first value is at the corner of the L shape (Described in a comment above the
    				// calculateValueForOneMissing definition), so by solving for the second value and storing it in the
    				// array at the right location, we are left with a simple 2 missing value problem that can be easily
    				// solved.
    				correctValues[1] = calculateValueForOneMissing(currentBoard, posZeros[1][0], posZeros[1][1]);
    				currentBoard[posZeros[1][0]][posZeros[1][1]] = correctValues[1];
    				correctValues[2] = calculateValueForOneMissing(currentBoard, posZeros[2][0], posZeros[2][1]);
    				correctValues[0] = calculateValueForOneMissing(currentBoard, posZeros[0][0], posZeros[0][1]);
    			}
    			else
    			{
    				// This is in the case that the first value in the zero row/column array was solvable, and
    				// by storing it's value back into the currentBoard array, we prevent having the issue with
    				// the corner zero being unsolvable with the function.
    				currentBoard[posZeros[0][0]][posZeros[0][1]] = correctValues[0];
    				correctValues[1] = calculateValueForOneMissing(currentBoard, posZeros[1][0], posZeros[1][1]);
    				correctValues[2] = calculateValueForOneMissing(currentBoard, posZeros[2][0], posZeros[2][1]);
    			}
    		}
    		
    		// Prints the solutions for the current board, using printOneSolution
    		// to ease the format of printing.  Declares generic i iterator.
    		for(int i = 0; i < numZeros; i++)
    		{
    			printOneSolution(posZeros[i][0], posZeros[i][1], correctValues[i]);
    			if(numZeros > 1 && i < numZeros - 1)
    			{
    				System.out.print(" ");
    			}
    		}
    		System.out.println();
    		
    		// Resets number of zeros for the next board.
    		numZeros = 0;
    		
    		// Reads the first board into currentBoard, count number of zeros, 
        	// store location of each zero.  Declares generic i and j iterators.
    		for(int i = 0; i < boardDimension; i++)
    	    {
    	    	for(int j = 0; j < boardDimension; j++)
    	    	{
    	    		// Stores the row number and column number into the first row of the posZeros array.
    				// Then it increments numZeros so that the next found zero can be stored in the next
    				// row.
    	    		if((currentBoard[i][j] = scnr.nextInt()) == 0 && numZeros < 3)
    	    		{
    	    			posZeros[numZeros][0] = i;
    	    			posZeros[numZeros][1] = j;
    	    			numZeros++;
    	    		}
    	    		// This runs if a fourth zero is found.  It will set i to boardDimension so that
        			// when we break from the for(int j) loop the i loop will end as well.
    	    		else if(currentBoard[i][j] == 0)
    	    		{
    	    			numZeros++;
    	    			i = boardDimension;
    	    			break;
    	    		}
    	    	}
    	    }
    		
    		// If it is unsolvable or the ending board of all zeros, it will print END then set the
    		// boolean isEndingBoard to true.
    		if(numZeros > 3)
    		{
    			System.out.print("END");
    			isEndingBoard = true;
    		}
    		scnr.close();
    	}
    }
    
    // Calculates a missing value at a location, returning the value if it is solvable
    // or returning 0 if the current value is not currently solvable
    // For example: if the zero is at the corner of the L shape      0
    // then it will return 0								    ---> 0 0
    public static int calculateValueForOneMissing(int board[][], int zeroRow, int zeroColumn)
    {
    	// Initialize values for the sum of all numbers in the row and column the zero is in
    	int columnSum = 0;
    	int rowSum = 0;
    	
    	// Initialize values for the number of zeros in the row and column the zero is in
    	int columnZeros = 0;
    	int rowZeros = 0;
    	
    	// Iterate through all the values in the row the zero is located, then add the each value
    	// to the rowSum and increment the number of zeros in the row by one for each zero.  Declares
    	// generic i iterator.
    	for(int i = 0; i < boardDimension; i++)
    	{
    		rowSum += board[zeroRow][i];
    		if(board[zeroRow][i] == 0)
    		{
    			rowZeros++;
    		}
    	}
    	
    	// Iterate through all the values in the column the zero is located, then add the each value
    	// to the columnSum and increment the number of zeros in the column by one for each zero.
    	// Declares generic i iterator.
    	for(int i = 0; i < boardDimension; i++)
    	{
    		 columnSum += board[i][zeroColumn];
    		 if(board[i][zeroColumn] == 0)
     		 {
     			columnZeros++;
     		 }
    	}
    	
    	// This will cause the function to return zero if there are two zeros in both the row and
    	// column the zero is in, implying that the value is currently not able to be solved with
    	// this function.
    	if(columnZeros == 2 && rowZeros == 2)
    	{
    		return 0;
    	}
    	
    	// If the value is solvable, then the function will either return (correct column sum - current column sum) if
    	// the number of zeros in the column is less than the number in the row, or it will return (correct row sum -
    	// current row sum) if the number of zeros in the column is greater than the number of zeros in the row.
    	// Basically the set of numbers with less zeros will be the only one capable of solving for the missing value.
    	// If there are an equal number of zeros then it will default to (correct column sum - current column sum) because
    	// it does not matter which set of numbers is used to calculate for the missing value.
    	return rowZeros > columnZeros ? correctSum - columnSum : correctSum - rowSum;
    }
    
    // Prints the solution input in the format (row,column,value)
    public static void printOneSolution(int row, int col, int val)
    {
    	System.out.printf("(%d,%d,%d)", row, col, val);
    }
}