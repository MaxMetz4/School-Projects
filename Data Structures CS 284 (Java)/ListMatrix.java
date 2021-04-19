package special_assignment;

import java.util.ArrayList;

/**
 *  Name: Maxwell Metzner
 *  Pledge: I pledge my honor that I have abided by the Stevens Honor system.
 *  Section: CS 284-B
 */

public class ListMatrix extends ListCollection<Integer> {
  private int rows;
  private int columns;

  /**
   * Initializes a `ListMatrix` with the specified number of rows and columns. By
   * default, ALL elements are set to 0.
   * 
   * @param rows
   * @param columns
   */
  public ListMatrix(int rows, int columns) {
	  setNodeCount(columns);
	  this.rows = rows;
	  this.columns = columns;
	  
	  SingleLL<Integer> temp = new SingleLL<Integer>();
	  for (int i = 0; i<columns; i++) {
		  for (int j = 0; j<rows; j++) {
			  temp.append(0);//prepares a linked list representing a column
		  }
		  collection.add(temp);//inserts the column
		  temp = new SingleLL<Integer>();//resets the linked list to empty to start over for next column
	  }
  }

  /**
   * @return the number of rows
   */
  public int numRows() {
    return this.rows;
  }

  /**
   * 
   * @return the number of columns
   */
  public int numColumns() {
    return this.columns;
  }

  /**
   * Adds the `ListMatrix` to `ListMatrix other`, storing the result in the caller
   * (this)
   * 
   * @throws IllegalArgumentException if dimensions do not properly coincide
   * @param other
   * @complexity Your big-o and supporting explanation here: The first loop to check for errors has negligible time complexity, 
   * so it can be ignored for big O notation. The method then goes through 2 matrices, looping through the rows has time 
   * complexity n and then it does this for n columns. it also does this for both matrices so the time complexity would be near 2n^2
   * or O(n^2)
   */
  public void add(ListMatrix other) {
	  if (this.rows != other.rows || this.columns != other.columns) {
		  throw new IllegalArgumentException();
	  }
	  for (int c = 0; c<this.columns; c++) {
		  for (int r = 0; r<this.rows; r++) {
			  this.setElem(c,r,this.getElem(c, r) + other.getElem(c, r));
			  //adds int found in the same row & column for both matrices (added to the matrix this)
		  }		  
	  }
  }

  /**
   * Returns the transpose of the matrix
   * 
   * @param matrix
   * @return matrix transpose
   */
  public static ListMatrix transpose(ListMatrix matrix) {
	  ListMatrix newMatrix = new ListMatrix(matrix.columns, matrix.rows);
	  for (int c = 0; c<matrix.columns; c++) {
		  for (int r = 0; r<matrix.rows; r++) {
			  newMatrix.setElem(r,c,matrix.getElem(c, r)	);
			  //This rotates the elements of the matrix 90 degrees clockwise (if that makes sense), so columns 
			  // of transposition are backwards but rows are accurate
		  }		  
	  }
	  
	  newMatrix.rows = matrix.columns;
	  newMatrix.columns = matrix.rows;
	  
	  ListMatrix temp = new ListMatrix(0,0);
	  for (int i=newMatrix.columns-1; i!=-1; i--) {//reflects newMatrix horizontally to fix the column order
		  temp.addList(newMatrix.getList(i));
	  }
	  temp.rows=newMatrix.rows;
	  temp.columns=newMatrix.columns;//updates the row and column count to be accurate
	  return temp;
  }

  /**
   * Multiplies the `ListMatrix` with `ListMatrix other`, returning the result as
   * a new `ListMatrix.
   * 
   * @throws IllegalArgumentException if dimensions do not properly coincide
   * @param other
   * @return
   */
  public ListMatrix multiply(ListMatrix other) {
	  if (this.columns != other.rows) {
		  throw new IllegalArgumentException();
	  }
	  ListMatrix newMatrix = new ListMatrix(0,0);
	  SingleLL<Integer> tempRow = new SingleLL<Integer>();
	  for (int c = 0; c < this.rows;c++) {
		  for (int r = 0; r<other.columns; r++) {  //Loop basically completes a row of completed multiplication
			  tempRow.append(this.multiplyHelper(r).multiplyPart(other, c));
		  }
		  newMatrix.addList(tempRow); //documents the row of completed multiplication then resets tempRow
		  tempRow = new SingleLL<Integer>();
	  }
	  return newMatrix;
  }
  
  public ListMatrix multiplyHelper(int row) {//this retrieves a row of the given matrix since getting a matrix row is awkward
	  ListMatrix newMatrix = new ListMatrix(this.columns,1);
	  for (int i = 0; i<this.columns; i++) {
		  newMatrix.setElem(0,i,this.getElem(i, row));
	  }
	  return newMatrix;
  }
  
  public Integer multiplyPart(ListMatrix other, int column) {
	  //accepts a single row and specific column of matrix. Row can be given through multiplyHelper
	  ArrayList<Integer> multiplicand = new ArrayList<Integer>();
	  ArrayList<Integer> multiplier = new ArrayList<Integer>();
	  Integer sum = 0;
	  if (this.rows>this.columns) {//Checks if this is row, else its a column of a matrix
		  for (int i=0; i< this.rows; i++) {
			  multiplicand.add(this.getElem(0, i));
		  }
	  } else {
		  for (int i=0; i< this.columns; i++) {
			  multiplicand.add(this.getElem(i, 0));
		  }
	  }
	  if (other.rows > other.columns) {//Checks if this is row, else its a column of a matrix
		  for (int i=0; i< other.rows; i++) {
			  multiplier.add(other.getElem(column,i));
		  }
	  } else {
		  for (int i=0; i< other.columns; i++) {
			  multiplier.add(other.getElem(i, 0));
		  }
	  }
	  for (int i=0; i<multiplicand.size();i++) {
		  sum = sum + (multiplicand.get(i)* multiplier.get(i));//performs the matrix multiplication of the row and column elements
	  }
	  return sum;
  }

//  public static void main(String args[]) {															// Highlight and "CTRL + / " to uncomment
//	  System.out.println("   		                [1][3]");
//	  System.out.println("[[1, 2], [3, 4]]  = 	[2][4]");
//	  System.out.println();
//	  
//	  ListMatrix myMatrix = new ListMatrix(2, 2); // tests ListMatrix constructor
//	  ListMatrix myMatrix2 = new ListMatrix(2, 2);
//	  System.out.println("Empty Matrix: " + myMatrix);//format of output shown below
//
//	  myMatrix.setElem(0, 0, 2);//top left = 2
//	  myMatrix.setElem(0, 1, 4);//bottom left = 4
//	  myMatrix.setElem(1, 0, 6);//top right = 6
//	  myMatrix.setElem(1, 1, 8);//bottom right = 8
//	  
//	  myMatrix2.setElem(0, 0, 1);
//	  myMatrix2.setElem(0, 1, 3);
//	  myMatrix2.setElem(1, 0, 5);
//	  myMatrix2.setElem(1, 1, 7);
//	  
//	  System.out.println("myMatrix: " + myMatrix);
//	  System.out.println("myMatrix2: " + myMatrix2);
//	  
//	  myMatrix.add(myMatrix2);
//	  System.out.println("Matrices added: " + myMatrix);//tests add()
//	  
//	  myMatrix = new ListMatrix(2, 3);
//	  myMatrix.setElem(0, 0, 2);//top left = 2
//	  myMatrix.setElem(0, 1, 4);//bottom left = 4
//	  myMatrix.setElem(1, 0, 6);//top middle = 6
//	  myMatrix.setElem(1, 1, 8);//bottom middle = 8
//	  myMatrix.setElem(2, 0, 10);//top right = 10
//	  myMatrix.setElem(2, 1, 12);//bottom right = 12
//	  
//	  System.out.println("Matrix: " + myMatrix);
//	  System.out.println("Matrix Transposed: " + transpose(myMatrix));//tests transpose (2x3 -> 3x2)
//	  
//	  System.out.println("Multiply: "+myMatrix.multiply(transpose(myMatrix)));//tests multiply
//	  
//	  //		          (  4   2)
//	  // (2 6 10)    (  8   6)     (176 140)
//	  // (4 8 12) X ( 12 10) = (224 176)  :)
//  }
}
