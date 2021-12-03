#include<iostream>
#include<cstring>
using namespace std;

struct node
{
    char foodname[30];
    int quantity;
    float price;
    int data;
    struct node *next;
};

/* 
Global struct pointers which are used throughout
the program to create  linked list and maintain it.
*/
node *headc = NULL, *newnode, *tailc = NULL;
node *heada = NULL, *taila = NULL;
node *head_s;

// This function prints the options available for admin to choose
void adminmenu()
{
    cout << "\n\t\t\t1. View total sales\n";
    cout << "\t\t\t2. Add new items in the order menu\n";
    cout << "\t\t\t3. Delete items from the order menu\n";
    cout << "\t\t\t4. Display order menu\n";
    cout << "\t\t\t5. Back to main menu\n\n";
    cout << "\t\t\t6. Enter your choice--->";
}

// This function prints the option for customers to choose
void customermenu()
{
    cout << "\n\t\t\t1. Place your order\n";
    cout << "\t\t\t2. View your ordered items\n";
    cout << "\t\t\t3. Delete an item from order\n";
    cout << "\t\t\t4. Display your Bill\n";
    cout << "\t\t\t5. Back to main menu\n\n";
    cout << "\t\t\t6. Enter your choice--->";
}

// This function creates a node for food's list
node *createadmin(node *head, int data, char foodname[30], float price)
{    
    newnode = new node;
    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    strcpy(newnode->foodname, foodname);
    newnode->next = NULL;
    node *temp = head;
    if (temp!= NULL)
    {        
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
        taila = newnode;    
    }
    else
    {    
        heada = taila = newnode;
    }     
    return heada;
}

// This function creates a node for customer's order list
node *createcustomer(node *head, int data, int quantity)
{
    newnode = new node;
    node *temp1 = heada;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }
    if (flag == 1)
    {
        newnode->data = data;
        newnode->price = quantity * (temp1->price);
        newnode->quantity = quantity;
        strcpy(newnode->foodname, temp1->foodname);
        newnode->next = NULL;
        node *temp = head;
        if (temp == NULL)
            headc = tailc = newnode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newnode;
            tailc = newnode;
        }
    }
    else
    {
        cout << "\n\t\t\tThis item is not present in the menu\n";
    }
    return headc;
}

// This function displays the respective entire linked list whose head pointer is passed to it.
void displayList(node *head)
{
    node *temp1 = head;
    if (temp1 == NULL)
    {
        cout << "\n\t\t\t List is empty!!\n\n";
    }
    else
    {
        cout << "\n";
        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
               { cout << "\t\t\t\n"
                     << "Serial no."<<"\t" << "Item name" <<"\t\t"<< "Price";
                cout << "\t\t\t\n"
                     << temp1->data<<"\t\t" << temp1->foodname <<"\t"<< temp1->price;
               }
            else
            {
                cout << "\t\t\t\n"
                     << "Serial no."<<"\t" << "Item name" <<"\t\t"<< "Quantity\tPrice";
                cout << "\t\t\t\n"
                     << temp1->data <<"\t\t" << temp1->foodname <<"\t" << temp1->quantity <<"\t\t" << temp1->price;
            }
            temp1 = temp1->next;
        }
        cout << "\n";
    }
}


/* This function maintains the total value of sales done by
 maintaining another Linked List which keeps a track of
 Total sales made to each customer  represented by each node
*/
node *totalsales(int data, int quantity)
{
    newnode = new node;
    int flag = 0;
    node *temp1 = heada;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }
    newnode->data = data;
    newnode->price = quantity * (temp1->price);
    newnode->quantity = quantity;
    strcpy(newnode->foodname, temp1->foodname);
    newnode->next = NULL;
    node *temp = head_s;
    if (temp == NULL)
        head_s = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if (flag == 1)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
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
    node *temp = headc;
    while (temp != NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

/*This function performs the task of deleting the data from
 Linked list whose respective head pointer is passed
 Here, data to be deleted is passed as a parameter
*/
node *del(int data, node *head, node *tail)
{
    if (head == NULL)
    {
        cout << "\n\t\t\tList is empty\n";
    }
    else
    {
        node *temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            delete temp;
        }        
        else
        {
            temp = head;
            node *temp1 = temp;
            while (data != temp->data)
            {
                temp1 = temp;
                temp = temp->next;
            }
            temp1->next = temp->next;
            if(temp == tail)
            tail = temp1;
            delete temp;
        }
    }
    return head;
}

// This function performs the task of deleting food item from admin's Linked list.
int deleteadmin()
{
    cout << "\n\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;
    node *temp = heada;
    while (temp != NULL)
    {
        if (temp->data == num)
        {
            heada = del(num, heada, taila);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/* This function performs the task of deleting food item from
 customer's Linked list i.e customer's ordered food item*/
int deletecustomer()
{
    cout << "\n\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;
    node *temp = headc;
    while (temp != NULL)
    {
        
        if (temp->data==num)
        {
            headc = del(num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// This function displays the total bill of food items ordered by customer
void displaybill()
{
    displayList(headc);
    node *temp = headc;
    float total_price = 0;
    while (temp != NULL)
    {
        total_price += (temp->quantity) * (temp->price);
        temp = temp->next;
    }
    cout << "\t\t\tTotal price: " << total_price;
}

// This function performs the task of deleting entire Linked List.
node *deleteList(node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        node *n, *temp = head;
        while (temp != NULL)
        {
            n = temp->next;
            delete temp;
            temp = n;
        }
        head = NULL;
    }
    return head;
}

// This function opens up the admin section and provides its interface and functionalities
void admin()
{
    cout << "\n\t\t\t-----------------------------------------------------\n";
    cout << "\t\t\t\t\t   ADMIN SECTION\n";
    cout << "\t\t\t-----------------------------------------------------\n";
    while (1)
    {
        adminmenu(); // prints admin functionality list

        int opt;
        cin >> opt;
        if (opt == 5)
            break;
        switch (opt) // switch-case block which executes according to the option selected by user
        {
        case 1:
            displayList(head_s);
            break;
        case 2:
           { cout << "\n\t\t\tEnter serial no.of the food item: ";
            int num, flag = 0;
            char name[50];
            float price;
            cin >> num;
            node *temp = heada;
            while (temp != NULL)
            {
                if (temp->data == num)
                {
                    cout << "\n\t\t\tFood item with given serial number already exists!!\n\n";
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if (flag == 1)
            {
                break;
            }
            cout << "\t\t\tEnter food item name: ";
            cin.ignore();
            cin.getline(name,50);
            cout << "\t\t\tEnter price: ";
            cin >> price;
            heada = createadmin(heada, num, name, price);
            cout << "\n\t\t\tNew food item added to the linked list!!\n\n";
            break;
           }
        case 3:
            if (deleteadmin())
            {
                cout << "\n\t\t\tUpdated list of food items menu \n";
                displayList(heada);
            }
            else
            {
                cout << "\n\t\t\tFood item with given serial number doesn't exist!\n\n";
            }
            break;
        case 4:
            cout << "\n\t\t\t Order menu \n";
            displayList(heada);
            break;
        default:
            cout << "\n\t\t\tWrong Input!! Please choose valid option\n";
            break;
        }
    }
}

// This function opens up the customer section and provides its interface and functionalities
void customer()
{
    int flag = 0, j = 1;
    char ch;
    cout << "\n\t\t\t-----------------------------------------------------\n";
    cout << "\t\t\t\t\t CUSTOMER SECTION\n";
    cout << "\t\t\t-----------------------------------------------------\n";
    while (1)
    {
        customermenu();
        int opt;
        cin >> opt;
        if (opt == 5)
            break;
        // Switch case block which executes according to the option selected by user
        switch (opt)
        {
        case 1:
            displayList(heada);
            cout << "\n\t\t\tEnter number corresponding to the item you want to order: ";
            int n;
            cin >> n;
            cout << "\t\t\t Enter quantity: ";
            int quantity;
            cin >> quantity;
            headc = createcustomer(headc, n, quantity);
            break;
        case 2:
            cout << "\n\t\t\t List of ordered items \n";
            displayList(headc);
            break;
        case 3:
            if (deletecustomer())
            {
                cout << "\n\t\t\t Updated list of your ordered food items\n";
            displayList(headc);
            }
            else
                cout << "\n\t\t\tFood item with given serial number doesn't exist!!\n";
            break;
        case 4:
            calculatetotsales();
            cout << "\n\t\t\t Final Bill\n";
            displaybill();
            headc = deleteList(headc);
            cout << "\n\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;
        default:
            cout << "\n\t\t\t Wrong input!!! Please choose valid option\n";
            break;
        }
        if (flag == 1)
            break;
    }
}

// This function prints the welcome interface and opens the main menu where user can select the option where you want to go.
void mainmenu()
{
    cout << "\n***************************************************************************************\n";
    cout << "\n\t\t\tWELCOME TO OUR RESTAURANT :)\n";
    cout << "\n***************************************************************************************\n\n\n";
    cout << "\t\t\t\t\t1. ADMIN SECTION---->\n";
    cout << "\t\t\t\t\t2. CUSTOMER SECTION---->\n";
    cout << "\t\t\t\t\t3. EXIT--->\n\n";
    cout << "\t\t\t\t\tEnter Your Choice---->";
}

int main() // From here the actual program execution begins
{
    // Here I have initialized admin's Linked List i.e. Food Menu with 5 items
    char item[5][30] = {"Hot and Sour Soup","Manchow Soup","Manchurian Noodles","Fried Rice","Makkka Noodles"};
    heada = createadmin(heada, 1, item[0], 100.0);
    heada = createadmin(heada, 2, item[1], 200.0);
    heada = createadmin(heada, 3, item[2], 150.0);
    heada = createadmin(heada, 4, item[3], 100.0);
    heada = createadmin(heada, 5, item[4], 80.0);    
    while(1)
    {
        mainmenu();
        int choice;
        cin>>choice;
        if (choice == 3)
        {
            cout << "\n\n\t\t\t**********Thank You!!***************\n";
            break;
        }

        //switch case block which executes according to the option selected by user
        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 3:
            break;
        default:
            cout << "\n\t\t\t\t\t\t\t\t\t Wrong Input !! Please choose valid option\n";
            break;
        }
    }
}