package exercises;

import java.util.Scanner;

//Class doubllylinkedlist

public class DoubleLinkedList {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		//creating object of linkedlist
		LinkedList list = new LinkedList();
		System.out.println("Doubly linked list Test\n");
		char ch;
		//perform list operations
		do {
			System.out.println("1. Insert at beginning");
			System.out.println("2. Insert at end");
			System.out.println("3. Insert at indexition");
			System.out.println("4. Delete at indexition");
			System.out.println("5. Check empty");
			System.out.println("6. get size");
			int choice = scan.nextInt();
			switch(choice) {
			case 1:
				System.out.println("Enter integer element to insert");
				list.insertAthead(scan.nextInt());
				break;
			case 2:
				System.out.println("Enter integer element to insert");
				list.insertAttail(scan.nextInt());
				break;
			case 3:
				System.out.println("Enter integer element to insert");
				int num = scan.nextInt();
				System.out.println("Enter indexition");
				int index = scan.nextInt();
				if (index < 1 || index > list.getSize()) {
					System.out.println("Invalid indexition\n");
				} else {
					list.insertAtindex(num, index);
				}
				break;
			case 4:
				System.out.println("Enter indexition");
				int p = scan.nextInt();
				if (p<1 || p > list.getSize())
					System.out.println("Invalid indexition\n");
				else
					list.deleteAtindex(p);
				break;
			case 5:
				System.out.println("empty Status = " + list.isEmpty());
				break;
			case 6:
				System.out.println("Size = " + list.getSize() + "\n");
				break;
			default:
				System.out.println("Wrong entry \n");
				break;
			}
			//display list
			list.display();
			System.out.println("Do you want to continue?");
			ch = scan.next().charAt(0);
		} while (ch == 'Y');
	}
}
