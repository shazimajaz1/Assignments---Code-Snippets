// ****************************************************************
// MagicSquare.java
// Edited By Shazim Ajaz
// Date Created: Feb, 21, 2018
// CSC 20-LAB
// ****************************************************************
import java.util.Scanner;
public class MagicSquare { 

    int[][] square;

    public MagicSquare(int size)
    {
      //Declaring an array with the given size from test file.
      square = new int[size] [size];       
    }
//--------------------------------------
//return the sum of the values in the given row
//--------------------------------------
 
    private int sumMagicRow(int row)
    {
      int sum = 0;
      for(int i = 0; i < square.length; i ++) {
         //Add the next value to the previous value with each iteration.
         sum += square[row][i];
      }
      return sum;
    }
//--------------------------------------
//return the sum of the values in the given column
//--------------------------------------
 
    private int sumMagicCol(int col)
    {
      int sum = 0;
      for(int i = 0; i < square.length; i++) {
         //Add the next value to te previous value with each iteration.
         sum += square[i][col];
      }
      return sum;
    }
//--------------------------------------
//return the sum of the values in the main diagonal
//--------------------------------------
 
    private int sumMagicDiagMain()
    {
      int sum = 0;
      int count = 0;
      for(int i = 0; i < square.length; i++) {
         sum += square[i][count]; //Going from top to Bottom
         count++;
      }
      return sum;
    }
//--------------------------------------
//return the sum of the values in the other ("reverse") diagonal
//--------------------------------------
 
    private int sumMagicDiagRev()
    {
      int sum = 0;
      int count = 0;
      for(int i = square.length - 1; i >= 0; i--) {
        sum += square[i][count]; //Going from bottom to top.
        count++; 
      }
      return sum;
    }
 
//--------------------------------------
//return true if the square is magic (all rows, cols, and diags
// have same sum), false otherwise
//-------------------------------------- 
    public boolean isMagicSquare()
    {
       
       int[] rowSum = new int[square.length];
       int[] colSum = new int[square.length];
       int diagRev = sumMagicDiagRev();
       int diagMain = sumMagicDiagMain();
       //Storing the Value of Row sums and Colum sums in Arrays.
       for(int row = 0; row < square.length; row++) {
          rowSum[row] = sumMagicRow(row);
          colSum[row] = sumMagicCol(row);
       }
       //Printing Out the Result for row Sum
       for(int k = 0; k < square.length; k++) {
         System.out.println("Sum of row " + k + " is " + rowSum[k]); 
       }
       System.out.println();
       //Printing Out the Resutl for col Sum
       for(int m = 0; m < square.length; m++) {
         System.out.println("Sum of column " + m + " is " + colSum[m]);
       }
       System.out.println();
       //Printing out result for  Diagnols
       System.out.println("The sum of the main Diagonal is: " + diagMain);
       System.out.println("The sum of the other Diagonal is: " + diagRev);
       //Comparing Value of Each member with the other.
       for(int j = 0; j < square.length - 1; j++) {
         //Comapring rows with rows and columns and diagnols.
         if(rowSum[j] != rowSum[j + 1] || diagRev != rowSum[j] || diagMain != rowSum[j]) {
            System.out.println("It is not a magic square");
            return false;
         }
         //Comparing rows colums with rows and cols.
         else if(colSum[j] != rowSum[j + 1] || diagRev != colSum[j] || diagMain != colSum[j] ) {
            System.out.println("It is not a magic square");
            return false;
         }
       }
       if(diagRev != diagMain) //Comparing Two Diagnolas.
         return false;
       System.out.println();         
       System.out.println("It is a magic Square");
       return true;
    }
//--------------------------------------
//This method prints the Square on the Screen
//--------------------------------------
    public void printSquare(int count)
    {
      //Loop for each row.
      for(int i = 0; i < square.length; i++) {
         //Loop for each cloumn member of the row.
         for(int j = 0; j < square.length; j++) {
            System.out.printf("%3d ",square[i][j]);
         }
         System.out.println(); //Printing space everytimes a row ends.
      }
    }

//--------------------------------------
//read info into the square from the input stream associated with
//the Scanner parameter
//--------------------------------------
    public void readSquare(Scanner scan)
    {
        String line;
        for (int row = 0; row < square.length; row++) {
           for (int col = 0; col < square.length; col++) {
              square[row][col] = scan.nextInt();
           }
        }
    }
}