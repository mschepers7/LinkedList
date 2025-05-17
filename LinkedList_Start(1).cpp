
#include <iostream>
using namespace std;


class ListNode 
{
  private: 
  double value; 
  ListNode *next; // Pointer to next node in list
  friend class LinkedList; // Make LinkedList a friend of ListNode
  public:
  ListNode(double v, ListNode *p) // Constructor
  {
    value = v; 
    next = p; // Assign next to p
  }

};

//This class should FOLLOW AFTER the ListNode class in this file.
class LinkedList
{
public:
    void add(double x);
    bool isMember(double x);
    LinkedList( ) { head = NULL;}    
    void print();
    void rPrint(){ rPrint(head);}
    ~LinkedList();
    void remove(double x);
    void reverse( );
    int search(double x);
    void insert(double x, int pos);
    void removeByPos(int pos);
    void sort();        
private:
    ListNode * head;
    static void rPrint(ListNode *pList); 
    static ListNode * insert(ListNode *item, ListNode *sortedList); 
                                   // Insert item into a sorted list  
};


void LinkedList::sort()
{
  ListNode *sortedList = NULL;

  // Repeatedly remove items from list 
  // And insert them into sorted list  
  while (head != NULL)
  {
	
  ListNode *item = head; 
  head = head->next; 

    sortedList = insert(item, sortedList);
  }  
  head = sortedList;  
}


ListNode *LinkedList::insert(ListNode *item , ListNode *sortedList)
{
  // If sortedList is empty or first member of the  sorted list
  // is greater or equal to item then item becomes the first
  // member of the augmented list

  if (sortedList == NULL || sortedList->value >= item->value)
   {
	  
     
      item->next = sortedList; // Place sortedList after item
      return item;            // Return the new head of the list
   }
   ListNode *current = sortedList;
  while (current->next != NULL && current->next->value < item->value)
  {
      current = current->next; // Move to the next node
  }

  item->next = current->next;
  current->next = item;
  return sortedList;  
}


void LinkedList::removeByPos(int pos)
{
  // pos is number of nodes to skip   
  ListNode *p = head;
  if (p == NULL) return;
  while (pos > 0 && p)
  {
     // Skip
     p = p->next;
     pos--;
  }

  // p now points to the nod that should be deleted
  if (p == head)
     {
        head = head->next;
        delete p;
        return;
     }
  else
    {
      if (p == NULL) return; // Nothing to do: pos was too big

      // Need to delete p: Use trailer pointer to come up 
      // behind p and then delete it      
      ListNode *trailer = head;
      while (trailer->next != p)
         trailer = trailer->next;
      trailer->next = p->next;
      delete p;
    }
}


void LinkedList::insert(double x, int pos)
{
    // Cases where the new value goes at the beginning
    // or when the list is empty are handled separately
    if (pos == 0 || head == NULL) 
    {
     head = new ListNode(x, head);

        return;
    }

    // Figure out how many nodes to skip before splicing
    // in a new node
    ListNode *p = head;                  // p is used to walk down the list
    int numberToSkip = 1;  
    while (numberToSkip <= pos)
    {
       if (p->next == NULL || numberToSkip == pos)
       {              
		   //STEP FIVE: Set p->next to a new ListNode with x as the value
		   //and p->next as the node to pass into the constructor.
        p->next = new ListNode(x, p->next);
           return;
       }
       // Not at end and have not skipped enough
       // So skip another one
       p = p->next;
       numberToSkip++;
    }
}


int LinkedList::search(double x)
{
  int position = 0;
  ListNode *p = head;   // Used to search through nodes
  while (p)
  {
    if (p->value == x) return position;
    p = p->next;
    position ++;
  }
  return -1;            // Not found
}


void LinkedList::reverse()
{
  ListNode *rev = NULL; // Holds list being reversed
  ListNode *p = head;   // Traverses nodes of original list
  ListNode *mover;      // Used to move noded from original list to the new list

  while (p)
  {
    // Move node at p to the beginning of the new list rev being constructed
	
    mover = p; 
    p = p->next; 
    mover->next = rev; 
    rev = mover;

  }
  //STEP 6b: assign head to rev
  head = rev;
}


LinkedList::~LinkedList( )
{
   ListNode *p = head;
   ListNode *q;  // Next pointer
   while (p != NULL)
   {
      q = p->next;
      delete p;
      p = q;
   }
}


void LinkedList::remove(double x)
{
    ListNode *garbage;             // Use to delete nodes
    if (head == NULL) return;

    // Is x in the head?
    if (head->value == x)
    {
		

    garbage = head;
    head = head->next; 

        return;
    }

    // x not in the head, find it
    ListNode *p = head;
    while (p->next != NULL && p->next->value != x)
    {
       p = p->next;
    }

    // p->next == NULL or p->next->value is x
    if (p->next == NULL) return;    // Did not find it
    else
      {
       
    garbage = p->next;
    p->next = garbage->next;
    delete garbage;
      }
}


void LinkedList::rPrint(ListNode *pList)
{
  if (pList == NULL) return;
  else
   {
      cout << pList->value << "  ";
      rPrint(pList->next);
   }
}


void LinkedList::print()
{
    ListNode *p = head;             // Use to walk down list
    while (p != NULL)
    {
        cout << p->value << " ";
        p = p->next;
    }
}


void LinkedList::add(double x)
{
    head = new ListNode(x, head);
}


bool LinkedList::isMember(double x)
{
    ListNode *p = head;              // Use p to walk through list
    while (p != NULL)
    {
        if (p->value == x) return true;
        else
            p = p->next;        
    }
    // List is exhausted without finding x
    return false;    
}

int main( )
{
    // Explain program to user
    cout << "This program allows you to construct a list by specifying list members and positions.";        
    cout << "\nYou can then sort the list.";
    // Create empty list
    LinkedList list1;   
    
    // Construct a list using  insert by position        
    for (int k  = 1; k <= 5; k++)
    {
       cout << "\nEnter a number followed by a position: ";
       int x, pos;
       cin >> x >> pos;
       list1.insert(x, pos);
       cout << "\nCurrent list membership is: ";
       list1.rPrint();         
   }
   // Demonstrate the list sort.
   list1.sort();
   cout << "\nHere is the sorted list: \n";  
   list1.rPrint();      

   //Other functions tested
   cout << "\nHere is the reverse list: \n";  
   list1.reverse();
   list1.rPrint(); 

   cout << "\nEnter a value to remove from the list: ";
   double r;
   cin >> r;
   list1.remove(r);

   cout << "\nHere is the shortened list: \n";  
   list1.rPrint();      

   return 0;    
}
