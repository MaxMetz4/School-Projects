package special_assignment;

/**
 *  Name: Maxwell Metzner
 *  Pledge: I pledge my honor that I have abided by the Stevens Honor system.
 *  Section: CS 284-B
 */

import java.util.ArrayList;
import java.util.List;

public class ListCollection<E> {
  private int nodeCount;
  protected List<SingleLL<E>> collection;

  /**
   * Base constructor, initializes an empty ListCollection.
   */
  public ListCollection() {
	  List <SingleLL<E>> collection = new ArrayList<SingleLL<E>>();
	  this.collection = collection;
  }

  /**
   * Initializes a ListCollection with `numLists` lists.
   * 
   * @param numLists
   */
  public ListCollection(int numLists) {
	  List <SingleLL<E>> collection = new ArrayList<SingleLL<E>>();
	  if (numLists < 0) {
		  throw new IllegalArgumentException("The number of lists must be >= 0");
	  }
	  for (int i = 0; i < numLists; i++) {
			collection.add(null); //adds an empty space for a list for numList amount of times
		}
	  this.collection = collection;

	  
  }

  /**
   * @return The size of the `ListCollection`
   */
  public int size() {
	  return collection.size();
  }

  /**
   * Sets the nodeCount
   * 
   * @param nodeCount
   */
  public void setNodeCount(int nodeCount) {
	  this.nodeCount = nodeCount;
  }

  /**
   * @return the nodeCount
   */
  public int getNodeCount() {
	  return this.nodeCount;
  }

  /**
   * Adds the specified `SingleLL` to the end of the `ListCollection`
   * 
   * @param list
   */
  public void addList(SingleLL<E> list) {
	  collection.add(list);
	  nodeCount++;
  }

  /**
   * Adds the specified `List` to the `ListCollection`
   * 
   * @param list
   * @complexity Your big-o and supporting explanation here: The method iterates through all of the items in list 
   *  and .append uses .insert which has to travel 1,2,3 ... n(n+1)/2 times to add to the very end of the linked list. This results
   *  in O(n^2)
   * 
   */
  public void addList(List<E> list) {
	  SingleLL<E>current = new SingleLL<E>();
	  for (E x : list) { //for all the stuff in list, append it into a linked list
          current.append(x);
      }
	  collection.add(current);
	  nodeCount++;
  }

  /**
   * Returns the list at the specified index
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @return the list
   */
  public SingleLL<E> getList(int listIndex) {
	  if (listIndex > collection.size() || listIndex < 0) {
		  throw new IllegalArgumentException();
	  }
	  return collection.get(listIndex);
  }

  /**
   * Adds an element to the `elemIndex` position of the list at `listIndex`
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @param elemIndex
   * @param elem
   * @complexity Your big-o and supporting explanation here: First the .get() method iterates through all of the SingleLL's
   * that are present (n time complexity), then once it finds the correct SingleLL it iterates through the linked list until it finds the 
   * right node to add to (elemIndex), also with time complexity n. This makes the time complexity n+n=2n or O(n).
   */
  public void addElem(int listIndex, int elemIndex, E elem) {
	  SingleLL<E>desiredList = new SingleLL<E>();
	  if (listIndex > collection.size() || listIndex < 0 || elemIndex < 0) {
		  throw new IllegalArgumentException("Index does not exist in collection");
	  }
	  desiredList = collection.get(listIndex);
	  desiredList.insert(elemIndex, elem);
  }

  /**
   * Sets the element at the `elemIndex` position of the list at `listIndex`
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @param elemIndex
   * @param elem
   */
  public void setElem(int listIndex, int elemIndex, E elem) {
	  SingleLL<E>desiredList = new SingleLL<E>();
	  if (listIndex > collection.size() || listIndex < 0) {
		  throw new IllegalArgumentException("Index does not exist in collection");
	  }
	  desiredList = collection.get(listIndex);
	  if (elemIndex > desiredList.size() || elemIndex < 0) {
		  throw new IllegalArgumentException("Index does not exist in SingleLL");
	  }
	  desiredList.set(elemIndex, elem);
	  //do I have to overwrite with desiredList still?
  }

  /**
   * Returns the element at the `elemIndex` position of the list at `listIndex`
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @param elemIndex
   * @return
   */
  public E getElem(int listIndex, int elemIndex) {
	  SingleLL<E>desiredList = new SingleLL<E>();
	  if (listIndex > collection.size()) {
		  throw new IllegalArgumentException("Index does not exist in collection");
	  }
	  desiredList = collection.get(listIndex);
	  return desiredList.get(elemIndex);
  }

  /**
   * Returns the `ListCollection` in string form, following STRICTLY the rule of
   * "[LIST1, LIST2, LIST3, ... ]" Example: [[0, 1, 2], [3, 4, 5] [6, 7, 8]]
   */
  
  public String toString() {
	  StringBuilder sb = new StringBuilder();
	  int commaLocation = 0;
	    sb.append("[");
	    for (SingleLL<E> x: collection) {
	    	if (x == null) {//shows there is an empty linkedList and avoiding null pointer
	    		sb.append("[]");
	    	} else {
	    		sb.append(x.toString());
	    	}
	    	if (commaLocation != nodeCount-1) {//makes sure there is no comma at the end of the list of lists
	    		sb.append(", ");
	    	}
	    	commaLocation++;
	    }
	    sb.append("]");
	    return sb.toString();
	  }
  
//  public static void main(String args[]) { 																				// Highlight and "CTRL + / " to uncomment
//	  ListCollection<String> myCollection = new ListCollection<String>();
//	  ListCollection<String> myCollection2 = new ListCollection<String>(3); 
//	  SingleLL<String> linkedList1 = new SingleLL<String>();
//	  List<String> linkedList2 = new ArrayList<String>();
//	  
//	  linkedList1.append("hello");
//	  linkedList1.append("world");
//	  myCollection.addList(linkedList1);// tests addList for linked lists
//	  linkedList2.add("world");
//	  myCollection.addList(linkedList2);// tests addList for lists
//	  
//	  System.out.println("ListCollection Constructor: " + myCollection);  //tests toString & ListCollection constructor
//	  System.out.println("Alternate ListCollection Constructor: " + myCollection2); //tests ListCollection(int numLists) constructor
//	  System.out.println("Size: " + myCollection2.size()); //tests size()
//	  
//	  myCollection2.setNodeCount(5); // tests setNodeCount
//	  System.out.println("Get/Set Node Count: " + myCollection2.getNodeCount()); // tests getNodeCount
//	  
//	  myCollection2.setNodeCount(3); //resets to correct value
//	  System.out.println("Get list: " + myCollection.getList(1));// tests getList
//	  
//	  myCollection.addElem(0, 2, "hi");
//	  System.out.println("Add elem: " + myCollection);// tests addElem
//	  
//	  myCollection.setElem(0, 2, "okay");
//	  System.out.println("Set elem: " + myCollection);// tests setElem
//	  System.out.println("Get elem: " + myCollection.getElem(0, 2)); //tests getElem
//  }
}
