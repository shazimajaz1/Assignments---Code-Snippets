//This class is used to construct a list through
//object oriented programming. Each list consist 
//of nodes of Student type of data. Each Node has
//a next field of Type Node which points to the 
//Next Node in the List
//Modified By: Shazim Ajaz
//Date: 03/22/2018
//The basic structure was created by the class professor. I have 
//implemented the behavior. 

public class LinkedList {
   // This is a privat class inside the LinkedList
   //Providing access to only the LinkedList itself.
   //It have two fields, one of which is data which
   //holds the data for each node and the other one is
   //Next, which points to the next Node in the LinkedList
   private class Node {
      private Student Data = null;
      private Node Next = null;
      public Node() { 
          Data = null; 
          Next = null; 
      }
      public Node(Student element) { 
          Data = element; 
      }
      public Node(Student o, Node n) { 
          Data = o; 
          Next = n; 
      }      
      public void setNext(Node n) { 
         Next = n; 
      }
      public Node getNext() {  
         return Next; 
      }
      public Student getElement() {  
         return Data; 
      }
      public void setElement(Student element) { 
         Data = element; 
      }
   }

   // Internal data for LinkedList
   private Node head = null;
   private Node current = null;
   private int size = 0;
   
   // LinkedList constructor
   public LinkedList() {
      head = null;
      current = head;
   }
   
   // Move the current position forward one position
   public void forward() {
      //There are two conditions that are needed to be checked
      //First one is to make sure that the list is not empty.
      //Second to ensure that the list has more than one elements
      //Both can be possible if size is greater than one.
      if(size > 1 && current != null) {
         Node temp = current.getNext();
         if(temp != null) 
         current = current.getNext();   
      }
      //After the Above code executes, the current will point to
      //the next Node in the LinkedList instance.
   }
   
   // Move the current position backward one position
   public void backward() {
      //These steps are being followed to move the current position backward.
      //Secure the value of current in the Temporary variable.
      if(head != current) {
         Node temp = new Node();
         temp = head;
         //Setting the value of current to start
         //Using a loop, we move in the list until before the Node we were before
         while(temp.getNext() != current && temp.getNext() != null) {
            temp = temp.getNext();
         }
         current = temp;
         //The Ending Result: When the Above code will execute, the current will
         //be moved backward. 
      }
   }   
 
   // Get current object's data element
   public Student currentData() {
      if(size == 0) {
         return null;
      }
      return current.getElement();
   }
   public Node getCurrent() {
      return current;
   }
  
   // Add object to the first of the list
   public void addFirst(Student o) {
      
      if(!(repeated(o))) {
         //In order to add the object to the first of the list, we must secure the head
         //in a temporary variables, so that the list is not lost.
         Node temp;
         if(size > 0) {
            //Adding the New Element to The List
            temp = new Node(o, head);
            head = temp;
            current = head;
         } else {
            head = new Node(o, null);
            current = head;
         }
         //After the above code executes,the head will point the new elements and the
         //next new element will point towards the rest of the list
         size++;
      }
   }
	
   
   // resetCurrent at the first position
   public void resetCurrent() {
      current = head;
      //After the above code executes, both head and current will point towards the
      //start of the List.   
   }
   
   // Add object to the last of the list
   public void addLast(Student o) {
      if(!(repeated(o))) {
         //In Order to add the object to the last of the list, these steps are being folowed.
         if(size > 0) {
            Node temp = head;
            while(temp.getNext() != null)
               temp = temp.getNext();
            //Creating a new Node
            Node last = new Node(o, null);
            temp.setNext(last);
            
            //Increasing size by 1
            size++;
         } else
            addFirst(o);
         
      }
   }
	
   // Add an object o before the current position
   public void insertBefore(Student o) {
      //Checking to See if the Same Student Already Exists in the List
      if(head == null) {
         return;
      }
      if(!(repeated(o))) {      
         if(head == current) {
            addFirst(o);
         } else {
            //Adding the Node
            Node prev;
            backward();
            prev = current;
            forward();
            
            //Create a New Node
            Node add = new Node(o, null);
            prev.setNext(add);
            add.setNext(current);
            size++;
         }
      }
   }
   
   // Add an object o after the current position
   public void insertAfter(Student o) {
      //Checking to See if the Same Student Already Exists in the List
      //Secure the value of the Current.next in a temporary variable
      if(!(repeated(o))) {
         if(size == 0) {
            addFirst(o);
         } else if(current != null) {
            Node temp = new Node();
            temp = current.getNext();
            current.setNext(new Node(o, temp));
            size++;
         }
      }
   }
   
   // Get first object
   public Student getFirst() {
      if(size == 0) {
         return null;
      }
      return head.getElement();  
   }
	
   // Get last object
   public Student getLast() {
         if(size > 0) {
         //A new temporary object shall be created to secure the value of current
         Node temp = new Node();
         temp = current;
         while(temp.getNext() != null) {
            temp   = temp.getNext();
         }
         backward();
         
         return temp.getElement();
      } else
         return null;
   }
	
   // Remove the first object
   public Student removeFirst(){
      //If the list if empty
      if(size == 0) {
         return null;
      }
      else { 
         //To remove the first first element, using leap frog techniqute
         Node temp = new Node();
         temp = head;
         head = head.getNext();
         size--;
         return temp.getElement();
      }
   }
	
   // Remove the last object
   public Student removeLast() {
      if(size == 0) {
         return null;
      }else if(size == 1) {
         Node a = new Node();
         a = head;
         head = null;
         size--;
         return a.getElement();
      } else {
         Node t = current;
         while(t.getNext() != null) {
            t = t.getNext();
         }
         current = t;
         backward();
         current.setNext(null);
         size--;
         return t.getElement();
      }   
   }
	
   // Remove object o from the list
   public void remove(Student o) {
      if(size != 0) {
         //Making sure that the temporary node is pointing at the position before the node
         Node prev = null;
         Node temp = head;
         //Scanning through the list until the desired element is reached:
         while(temp.getNext() != null && temp.getElement() != o) {
            prev = temp; //Saving the address for the previous element.
            temp = temp.getNext(); //Traversing the temp
         }
         //After the execution of the above code: prev will point to the location one before
         if(temp.getElement() == o) {
            //Set if current = temporary otherwise keep it as it is
            current = current == temp ? prev:current;
            
            //To make sure that previous does not point to null i.e the list is the first element in the list
            if(prev != null) {
            
               //using the Leap Frog Technique to remove the desired  element
               prev.setNext(temp.getNext()); 
               size--;
            } else if(prev == null) { //if it is the first element
               //using Leapfrog technique to make the head jump over one element
               head = head.getNext();
               size--;
            } else { //If it is the last element
               removeLast();
            }
         } 
      }       
   }
   
   // Returns the number of elements on the list
   public int size() {
      return size;
   }
	
   // Is the list emptied?
   public boolean isEmpty() {
      return size == 0;
   }

   // Display a content of a list
   public String toString() {
      String r = "( HEAD -> ";
      // Node l = head.getNext();
      Node l = head;
      while (l != null) {
         r = r + l.getElement() + " -> " ;
         l = l.getNext();
      }
      return  r + " )";
   }
   
   //This Method is for internal use only and checks to see if 
   //the same Node is repeated inside a list.
   private boolean repeated(Student o) {
      Node t = new Node();
      t = head;
      if(size > 0) {
         while(t != null) {
            if(t.getElement() == o && (t.getElement() != null)) {
               return true;
            } 
            t = t.getNext();
         }
      }
      return false;

   }
   //This Methods Checks to see if the list is not tryin got add itself as a node
   private boolean iteself(Student o) {
      Node t = new Node();
      t = head;
      return false; 
   }
}