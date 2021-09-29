// Program to implement "Linked List" to perform various tasks.

#include<iostream>
// #include<stdlib.h>
#include<cstring>

using namespace std;
struct node
{
    char foodname[30];
    int quantity;
    float price;
    int data;
    struct node*next;
};

// Global struct pointers which are used throughout
// the program to create  linked list and maintain it.

 node* headc = NULL,*newnode,*tailc = NULL;
 node *heada = NULL,*taila = NULL;
 node *head_s;

// This function prints the options available for admin to choose

void adminmenu()
{
    cout<<"\n\t\t\t\t\t\t\t1. View total sales\n";
    cout<<"\t\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout<<"\t\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout<<"\t\t\t\t\t\t\t4. Display order menu\n";
    cout<<"\t\t\t\t\t\t\t5. Back to main menu\n\n";
    cout<<"\t\t\t\t\t\t\t6. Enter your choice--->";

}

// This function prints the option for customers to choose

void customermenu()
{
    cout<<"\n\t\t\t\t\t\t\t1. Place your order\n";
    cout<<"\t\t\t\t\t\t\t2. View your ordered items\n";
    cout<<"\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout<<"\t\t\t\t\t\t\t4. Display your Bill\n";
    cout<<"\t\t\t\t\t\t\t5. Back to main menu\n\n";
    cout<<"\t\t\t\t\t\t\t6. Enter your choice--->";
}

// This function creates a node for admin's linked list

 node*createadmin( node* head, int data, char foodname[30], float price)
 {
     newnode = new node;
     newnode ->data = data;
     newnode -> price = price;
     newnode -> quantity = 0;
     strcpy(newnode -> foodname , foodname);
     newnode -> next = NULL;

     node*temp = head;

     if(temp = NULL)
     {
         heada = taila = newnode;
     }
     else{
         while(temp->next!= NULL)
         {
          temp = temp->next;
         }
         temp->next = newnode;
         taila = newnode;
              }
    return heada;   

 }

 // This function creates a node for customer's linked list

 node * createcustomer(node* head, int data, int quantity)
{
    newnode = new node;
    node *temp1 = heada;
    int flag = 0;
    while(temp1!= NULL)
    {
        if(temp1 -> data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1 -> next;
    }
    if(flag == 1)
    {
        newnode -> data = data;
        newnode -> price = quantity * (temp1-> price);
        newnode -> quantity = quantity;
        strcpy(newnode -> foodname, temp1 -> foodname);
        newnode-> next = NULL;
        node * temp = head;
        if(temp == NULL)
        headc = tailc = newnode;
        else{
            while(temp->next!= NULL)
            temp = temp->next;
            temp->next = newnode;
            tailc = newnode;
        }
    }
    else
    {
        cout<<"\n\t\t\t\t\t\tThis item is not present int the menu\n";

    }
    return headc;
}

// This function displays the respective entire linked list whose head pointer is passed to it

void displayList(node*head)
{
    node *temp1 = head;
    if(temp1 == head)
    {
        cout<<"\n\t\t\t\t\t\t\t\t List is empty!!\n\n";

    }
    else{
        cout<<"\n";
        while(temp1!= NULL)
        {
            if(temp1-> quantity == 0)
            cout<<"\t\t\t\t\t\t\t\t\t\n"<<temp1->data<<temp1->foodname<<temp1->price;
            else
            {
                cout<<"\t\t\t\t\t\t\t\t\n"<<temp1->data<<temp1->foodname<<temp1-> quantity<<temp1->price;
            }
            temp1 = temp1-> next;

        }
        cout<<"\n";
    }
}
 // This function maintains the total value of sales done by 
 // maintaining another Linked List which keeps a track of 
 // Total sales made to each customer  represented by each node


 node * totalsales ( int data, int quantity)
 {
     newnode = new node;
     int flag = 0;
     node* temp1 = heada;
     while ( temp1->data!= data)
     {
         temp1 = temp1->next;
     }
     newnode->data = data;
     newnode -> price = quantity*(temp1->price);
     newnode->quantity = quantity;
     strcpy(newnode->foodname, temp1->foodname);
     newnode-> next = NULL;
     node*temp = head_s;
     if(temp == NULL)
     head_s = newnode;
     else
     {
         while(temp->next!=NULL)
         {
             if(temp->data == data)
             {
                 flag = 1;
                 break;
             }
             temp = temp->next;
         }
         if(flag == 1)
         {
             temp -> quantity+= newnode->quantity;
             temp->price+= newnode->price;
         }
         else
         {
             temp->next = newnode;
         }
     }
     return head_s;
 }

 // This function performs task of calculating total sales for each customer

 void calculatetotsales()
 {
     node*temp = headc;
     while(temp!= NULL)
     {
         head_s = totalsales(temp->data,temp->quantity);
         temp = temp->next;
     }
 }

 //This function performs the task of deleting the data from
 // Linked list whose respective head pointer is passed
 // Here, data to be deleted is passed as a parameter

node* del(int data, node*head,node*tail)
{
    if(head == NULL)
    {
        cout<<"\n\t\t\t\t\t\t\t\tList is empty\n";
    }
    else
    {
        node*temp;
        if(data== head->data)
        {
            temp = head;
            head = head-> next;
            delete temp;
        }
        else if(data== tail->data)
        {
            temp = tail;
            tail->next = NULL;
            delete temp;

        }
        else
        {
            temp = head;
            node*temp1 = temp;
            while(data!= temp->data)
            {
                temp1 = temp;
                temp = temp->next;
            }
            temp1->next = temp->next;
            delete temp;
        }
    }
    return head;
} 

// This function performs the task of deleting foo ditem from admin's Linked list.

int deleteadmin()
{
    cout<<"\n\t\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num;
    node*temp = heada;
    while(temp!= NULL)
    {
        if(temp->data == num)
        {
            heada = del(num, heada, taila);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// This function performs the task of deleting food item from 
// customer's Linked list i.e customer's ordered food item

int deletecustomer()
{
    
}