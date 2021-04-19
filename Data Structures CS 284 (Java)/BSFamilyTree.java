package special_assignment;

//Name: Maxwell Metzner
//Pledge: I pledge my honor that I have abided by the Stevens Honor System.

import java.util.ArrayList;

/**
 * BSFamilyTree creates a tree for specific families. 
 */
public class BSFamilyTree {
	private FamilyTreeNode root;

    /**
     * Constructor: constructs an empty BSFamilyTree
     */
    public BSFamilyTree() {
        root = null;
    }

    /**
     * takes in the last name and returns true if there
     * is a FamilyTreeNode with the given last name.
     */
	public boolean doesFamilyExist(String lastName) {
    	if (root == null) {
    		return false;
    	}
        FamilyTreeNode current = root;
        while (true) {
            int alphabetical = root.getLastName().compareToIgnoreCase(lastName);//Alphabetical checks if the name comes before or after so the binary tree can be traversed
            if (alphabetical != 0) {
            	alphabetical = alphabetical / Math.abs(alphabetical);//so outcome is simply -1, 0, or 1
            }
            if (alphabetical == 1) {
            	if (current.getLeft() == null) {
            		return false;
            	}
            	if (current.getLeft().getLastName() == lastName) {
                 	return true;
             	} else {
             		if (current.getLeft() == null && current.getRight() == null) {
             			return false;
             		}
             		current = current.getLeft();
             	}
            } else 
            if (alphabetical == -1) {
            	if (current.getRight() == null) {
            		return false;
            	}
              	if (current.getRight().getLastName() == lastName) {
                 	return true;
             	} else {
             		if (current.getLeft() == null && current.getRight() == null) {
             			return false;
             		}
             		current = current.getRight();
             	}
            } else 
            if (alphabetical == 0) {
            	if (current.getLastName() == lastName) {
                  	return true;
              	} else {
              		return false;
              	}
            }
        }
	}

    /**
     * Takes in a last name and creates a new instance of
     * FamilyTreeNode and adds it to the BSFamilyTree.
     */
    public void addFamilyTreeNode(String lastName) {
        FamilyTreeNode newNode = new FamilyTreeNode(lastName);
        if (root == null) {
        	root = newNode;
        	return;
        }
        FamilyTreeNode current = root;
        while (true) {
        	int alphabetical = current.getLastName().compareToIgnoreCase(lastName);//Alphabetical checks if the name comes before or after so the binary tree can be traversed
        	if (alphabetical != 0) {
            	alphabetical = alphabetical / Math.abs(alphabetical);//so outcome is simply -1, 0, or 1
            }
             if (alphabetical == 1) {
            	 if (current.getLeft() == null) {
                  	current.setLeft(newNode);
                  	return;
              	} else {
              		current = current.getLeft();
              	}
             } else
             if (alphabetical == -1) {
            	 if (current.getRight() == null) {
                  	current.setRight(newNode);
                  	return;
              	} else {
              		current = current.getRight();
              	}
             } else 
             if (alphabetical == 0) {
            	 throw new IllegalArgumentException("FamilyTreeNode already in BSFamilyTree");
             }
        }
    }

    /**
     * Takes a last name and then finds that specific
     * family tree and then returns that FamilyTreeNode
     * If last name is not in tree, throws an exception.
     */
    public FamilyTreeNode getFamilyTreeNode(String lastName) {
        FamilyTreeNode current = root;
        while (true) {
        	if (current == null) {
        		throw new IllegalArgumentException("Desired FamilyTreeNode not in BSFamilyTree");
        	}
        	int alphabetical = current.getLastName().compareToIgnoreCase(lastName);//Alphabetical checks if the name comes before or after so the binary tree can be traversed
        	if (alphabetical != 0) {
            	alphabetical = alphabetical / Math.abs(alphabetical);//so outcome is simply -1, 0, or 1
            }
        	if (alphabetical == 0) {
        		return current;
        	} else if (alphabetical == 1) {
        		if (current.getLeft().getLastName() == null) {
                	throw new IllegalArgumentException("Desired FamilyTreeNode not in BSFamilyTree");
            	} else {
            		current = current.getLeft();
            	}
        	} else if (current.getRight().getLastName() == null) {
         		throw new IllegalArgumentException("Desired FamilyTreeNode not in BSFamilyTree");
        	} else {
        		current = current.getRight();
        	}
        }
        }

    /**
     * Returns true if the input phone number exists in the BSFamilyTree
     * false otherwise.
     */
    public boolean doesNumberExist(String phoneNumber) {
    	ArrayList<String> numbers = new ArrayList<String>();
    	if (root == null) {
    		return false;
    	}
    	numberCollector(root, numbers);
    	if (numbers.contains(phoneNumber)) {
    		return true;
    	}
    	return false;
    	
    }
    
    private void numberCollector(FamilyTreeNode current, ArrayList<String> numList) {//Helper function for doesNumberExist that creates an arraylist (numlist) storing all phone numbers in the specified family
    	for (Person a : current.getMembers()) {
    		numList.add(a.getPhoneNumber());
    	}
    	if (current.getLeft() == null && current.getRight() == null) {
    		return;
    	}
    	if (current.getLeft() != null) {//These last 2 if cases traverse the binary tree, adding any numbers that are found
    		numberCollector(current.getLeft(), numList);
    	}
    	if (current.getRight() != null) {
    		numberCollector(current.getRight(), numList);
    	}
    }
    
    /**
     * Returns the string representation of the BSFamilyTree
     */
    public String toString() {
        return twoString(root,1);
    }
    
    public String twoString(FamilyTreeNode current, int indent) { //twoString is a helper function of toString created to keep track of indentations and recursively traverse the binary tree
    	if (current == null) {
    		return "null";
    	} else {
    		System.out.println(current.toString());
    	}	
    	if (current.getLeft() == null && current.getRight() == null) {//If it is a leaf, print out the 2 null children
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		System.out.println("null");
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		System.out.println("null");
    	}
    	if (current.getLeft() != null && current.getRight() == null) {//If there is a left branch but no right branch
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		twoString(current.getLeft(), indent + 1);//Prioritize left branch first in all if statements since it is a PREORDER TREE
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		System.out.println("null");
    	}
    	if (current.getRight() != null && current.getLeft() == null) {//If there is a right branch and no left branch
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		System.out.println("null");
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		twoString(current.getRight(), indent + 1);
    	}
    	if (current.getLeft() != null && current.getRight() != null) {//If there are two branches
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		twoString(current.getLeft(), indent + 1);
    		for (int i = 0; i < indent; i++) {
    			System.out.print("  ");
    		}
    		twoString(current.getRight(), indent + 1);
    	}
    	return null;
    }
    
    /*
    public static void main(String args[]) {
		BSFamilyTree newTree = new BSFamilyTree();
		newTree.addFamilyTreeNode("Wumbo");
		newTree.root.addFamilyMember("Wumbo", "Spongebob", "1234567890");
		newTree.root.addFamilyMember("Wumbo", "Patrick", "2345678901");
		if (newTree.doesNumberExist("2345678901") == true) {
			//System.out.println("Test 1 Success");
		}
		if (newTree.doesNumberExist("079ME") == false) {
			//System.out.println("Test 2 Success");
		}
		newTree.addFamilyTreeNode("Smith");
		newTree.getFamilyTreeNode("Smith").addFamilyMember("Smith", "Morty", "3456789012");
		newTree.getFamilyTreeNode("Smith").addFamilyMember("Smith", "Beth", "4567890123");
		//newTree.toString();
		newTree.addFamilyTreeNode("West");
		newTree.getFamilyTreeNode("West").addFamilyMember("West", "Kanye", "5678901234");
		newTree.getFamilyTreeNode("West").addFamilyMember("West", "North", "6789012345");
		newTree.toString();
    }
    */
}
