package homeworks;

// Maxwell Metzner
// I pledge my honor that I have abided by the Stevens Honor System.

import java.util.Random;// used in priority (bounded 0-99)
import java.util.ArrayList; // used as stack

public class Treap<E  extends Comparable<E>> {
	class Node<E> {
		//Data Fields
		public E data; // key for the search
		public int priority; // random heap priority
		public Node <E> left;
		public Node <E> right; 
		
		//Constructors
		public Node (E data , int priority) {			
			super();
			if (data == null) {
				  throw new IllegalArgumentException("Data is null");
				}
			this.data = data;
			this.priority = priority;
			this.left = null;
			this.right = null;
			
		}
		//Methods
		
		/**
		 * 	Rotates the Nodes to the right, making sure to return the pivot
		 * so that it can be attached to a predecessor node.
		 * 
		 * @return pivot, the highest node post-rotation
		 */
		Node<E> rotateRight() {
			Node<E> root = this;
			Node<E> pivot = this.left;
			root.left = pivot.right;
			pivot.right = root;
			return pivot;
		}
		
		/**
		 * Rotates the Nodes to the left, making sure to return the pivot
		 * so that it can be attached to a predecessor node.
		 * 
		 * @return pivot, the highest node post-rotation
		 */
		Node<E> rotateLeft() {
			Node<E> root = this;
			Node<E> pivot = this.right;
			root.right = pivot.left;
			pivot.left = root;
			return pivot;
		}
	}
	
	//Data Fields
	private Random priorityGenerator ;
	private Node<E> root ;
	
	//Constructors
	public Treap() {
		this.root = null;
		priorityGenerator = new Random();
	}
	public Treap(long seed) {
		this.root = null;
		priorityGenerator = new Random(seed);
	}
	
	public Node<E> getRoot() { //I made this to make testing easier
		return root;
	}

	//Methods
	
	/**
	 * Used in both add methods, reheap recursively makes sure that after the nodes have been 
	 * added into the heap, the priorities are also in order, changing the ordering of 
	 * the heap using left and right rotations.
	 * 
	 * @param stack, an ArrayList acting like a FIFO stack that keeps track of the successive parent nodes
	 * @param newNode, the node that is being added to the treap
	 */
	private void reheap(ArrayList<Node<E>> stack, Node<E> newNode) {
		if (stack.size() == 0) {//if the stack is empty, there is no travelling, meaning that the node becomes the root
			root = newNode;
		} else {
			if (newNode.priority < stack.get(0).priority) {//our work is done if it is already sorted
				return;
			} else {
				if (stack.get(0).left == newNode) {
					Node<E> temp = stack.get(0);//"pop" functionality
					stack.remove(0);
					temp.rotateRight();
					if (stack.size() > 0) {
						if (stack.get(0).right != temp) {
							stack.get(0).left = newNode;
						} else {
							stack.get(0).right = newNode;
						}
					}
					
				} else {
					Node<E> temp = stack.get(0);//"pop" functionality
					stack.remove(0);
					temp.rotateLeft();
					if (stack.size() > 0) {
						if (stack.get(0).right != temp) {
							stack.get(0).left = newNode;
						} else {
							stack.get(0).right = newNode;
						}
					}
				}
				reheap(stack, newNode);
			}
		}
	}
	
	/**
	 * If there is not a priority provided, a priority is generated from between 0-99
	 * and given to the new node. This new node info is then sent to the other
	 * method add.
	 * 
	 * @param key the informational part of the node
	 * @return true if everything goes well
	 */
	boolean add (E key ) {
		add(key, priorityGenerator.nextInt(100));
		return true;
	}
	
	/**
	 * A node is added to the treap following the rules of a binary tree. After the
	 * node is added, reheap is called to reorganize the binary tree into a treap
	 * incorporating the priority.
	 * 
	 * @param key the informational part of the node
	 * @param priority determines how high on the treap the node is
	 * @return true if everything goes well
	 */
	boolean add (E key , int priority ) {
		Node<E> current = new Node<E>(key,priority);
		if (this.getRoot() == null) {//If three is empty, node is the root
			this.root = current;
			return true;
		}
		boolean done = false;
		Node<E> checker = getRoot();
		ArrayList<Node<E>> stack = new ArrayList<Node<E>>();//Keeps track of path when adding
		while (done == false) {
			if (current.data.compareTo(checker.data) == -1) {//part 1, binary tree part decides if left or right branch
				if (checker.left == null) {
					stack.add(0, checker);
					checker.left = current;
					done = true;
				} else {
					stack.add(0, checker);
					checker = checker.left;
				}
			}
			if (current.data.compareTo(checker.data) == 1) {//part 2
				if (checker.right == null) {
					stack.add(0, checker);
					checker.right = current;
					done = true;
				} else {
					stack.add(0, checker);
					checker = checker.right;
				}
			}
		}
		reheap(stack, current);//makes sure that priorities are in order
		return true;
	}
	
	/**
	 * Deletes a node from the treap. To remove the node without destroying the 
	 * treap, the node that will be deleted is rotated until it is a leaf and can be 
	 * removed.
	 * 
	 * @param key the informational part of the node
	 * @return true if everything goes well
	 */
	boolean delete (E key ) {
		Node<E> current = getRoot();
		Node<E> parent = null;
		boolean done = false;
		while(done == false) {//this loops until the desired key is found
			if (key.compareTo(current.data) == 0) {
				done = true;
			}
			if (key.compareTo(current.data) == -1) {
				parent = current;
				current = current.left;
			}
			if (key.compareTo(current.data) == 1) {
				parent = current;
				current = current.right;
			}
			}
		while (current.left != null || current.right != null) {
			if (current.left != null) {
				current.rotateRight();
			}
			if (current.right != null) {
				current.rotateLeft();
			}
		}
		if (current.left == null && current.right == null) {//this rotates desired node into a leaf
			if (parent.left == current) {
				parent.left = null;
			} else {
				if (parent.right == current) {
					parent.right = null;
				}
			}
		}
		return true;
	}
	
	/**
	 * Determines if the key is in the treap by using the key/data value and 
	 * decending just as you would a heap.
	 * 
	 * @param root the parent of the nodes being viewed
	 * @param key the identifier for the node that is being sought after
	 * @return true if node exists in treap
	 */
	private boolean find (Node <E> parent, E key) {
		if (key.compareTo(parent.data) == -1) {
			if (parent.left == null) {
				return false;
			}
			parent = parent.left;
			return find(parent, key);
		} else {
			if (key.compareTo(parent.data) == 1) {
				if (parent.right == null) {
					return false;
				}
				parent = parent.right;
				return find(parent, key);
			}
		}
		return true;
	}
		
	
	/**
	 * Determines if the key is in the treap.
	 * 
	 * @param key the identifier for the node that is being sought after
	 * @return true if node exists in treap
	 */
	public boolean find (E key) {
		return find(getRoot(), key);
	}
	
	/**
	 * Converts the treap into text, displaying the key and priority of each node in
	 * the treap using a preorder traversal (going left to right in the tree) and different
	 * depths of the nodes are shown with the amount of spaces in front of the node.
	 */
	public String toString() { 
		this.twoString();
		return "";
	}
	
	// HELPER FUNCTIONS (Excluding reheap)
	
	/**
	 * helper of toString, converts the treap into text, displaying the key and priority of each node in
	 * the treap using a preorder traversal (going left to right in the tree) and different
	 * depths of the nodes are shown with the amount of spaces in front of the node.
	 */
	public void twoString() {//not restricted to returning String - need to add "null" branches"
        if(this.getRoot() == null)
            return;
        ArrayList<Node<E>> stack = new ArrayList<Node<E>>();
        stack.add(this.getRoot());
        while(stack.size() != 0){
            Node<E> n = stack.get(0);
            stack.remove(0);
            if (parent(n,getRoot()) != null && parent(n,getRoot()).left == null  && parent(n,getRoot()).right != null) {
           	 for (int i = depth(n, this.getRoot()); i>0; i--) {
               	 System.out.print("   ");
               }
           	 System.out.println("null");
            }
            for (int i = depth(n, this.getRoot()); i>0; i--) {
            	 System.out.print("   ");
            }
            	 System.out.print("(key = " + n.data);
                 System.out.println(", priority = " + n.priority + ")");
                 
                 
                 if (n.left == null && n.right == null) {
                	 for (int i = depth(n, this.getRoot())+1; i>0; i--) {
                    	 System.out.print("   ");
                    }
                	 System.out.println("null");
                	 for (int i = depth(n, this.getRoot())+1; i>0; i--) {
                    	 System.out.print("   ");
                    }
                	 System.out.println("null");
                 }
                 if (parent(n,getRoot()) != null && parent(n,getRoot()).left != null  && parent(n,getRoot()).right == null) {
                   	 for (int i = depth(n, this.getRoot()); i>0; i--) {
                       	 System.out.print("   ");
                       }
                   	 System.out.println("null");
                    }
           
            if(n.right != null){
                stack.add(0,n.right);
            }
            if(n.left != null) {
                stack.add(0,n.left);
            }
        }
    }
	
	/**
	 * Helps the twoString method by finding how many spaces to indent to 
	 * accurately display the treap. Otherwise similar to the find method, except
	 * it returns the height of the node being found.
	 * 
	 * @param desired the node that the depth is being found for
	 * @param root the highest node in the treap, used as a starting point for the node search
	 * @return integer, the depth of the desired node
	 */
	private int depth(Node<E> desired, Node<E> root) { // used to determine how far to indent on toString
		int counter = 0;
		boolean done = false;
		while (done == false) {
			if (desired.data.compareTo(root.data) == 1) {
				root=root.right;
				counter++;
			}
			if (desired.data.compareTo(root.data) == -1) {
				root=root.left;
				counter++;
			}
			if (desired.data.compareTo(root.data) == 0) {
				done = true;
			}
		}
		return counter;
	}
	
	/**
	 * Finds the parent of the node in the treap. Used in twoString to find if the
	 * parent node has another branch that is empty.
	 * 
	 * @param desired the child node
	 * @param root the highest node in the treap.
	 * @return
	 */
	private Node<E> parent(Node<E> desired, Node<E> root) {//easier way to get the parent of a node given the root of tree and desired node
		boolean done = false;
		if (root == null) {
			throw new IllegalArgumentException("Data is null");
		}
		if (desired == null) {
			throw new IllegalArgumentException("Desired is null");
		}
		while (done == false) {
			if (desired.data.compareTo(root.data) == 1) {
				if (root.right.data.compareTo(desired.data) == 0) {
					done = true;
				} else {
					root=root.right;
				}
			}
			if (desired.data.compareTo(root.data) == -1) {
				if (root.left.data.compareTo(desired.data) == 0) {
					done = true;
				} else {
					root=root.left;
				}
			}
			if (desired.data.compareTo(root.data) == 0) {
				return null;
			}
		}
		return root;
	}
	
//	public static void main(String args[]) {
//		Treap<Integer> testTree = new Treap < Integer >();
//		testTree . add (4 ,19);
//		testTree . add (2 ,31);
//		testTree . add (6 ,70);
//		testTree . add (1 ,84);
//		testTree . add (3 ,12);
//		testTree . add (5 ,83);
//		testTree . add (7 ,26);
//		testTree.toString();
//		
//		System.out.println(); 	System.out.println(); 	System.out.println();
//		
//		testTree.delete(7);
//		testTree.toString();
//
//	}
}