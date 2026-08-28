#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>


void listContacts(AddressBook *addressBook) 
{
    int sortCriteria;
    do
    {
        //based on 1)name or 2)phone or 3)email
        printf("\nList of Contacts by: \n");
        printf("1. Name \n");
        printf("2. Phone number \n");
        printf("3. Email \n");
        printf("4. Exit \n");
        // Sort contacts based on the chosen criteria
        printf("Which one you wants to sort : ");
        scanf("%d",&sortCriteria);

        switch(sortCriteria)
        {
            case 1:  //Based on Contacts names
            sorted_by_name(addressBook);
            break;
            case 2:  //Based on the Contacts phone Numbers
            sorted_by_phone(addressBook);
            break;
            case 3:  //Based on Contacts email Id
            sorted_by_email(addressBook);
            break;
            case 4:  //Exit
            printf("Exiting...\n");
            return;
            default: 
            printf("Invalid\n");
        }
    } while (1);
}

void display(AddressBook *addressBook)
{
    printf("%-8s%-25s%-15s%s\n","SI No.","Name","Phone","Email");
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        printf("%-8d%-25s%-15s%s\n",i+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
    }
}

void swap(AddressBook *addressBook, int j)
{
    Contact temp = addressBook -> contacts[j];
    addressBook -> contacts[j] = addressBook -> contacts[j+1];
    addressBook -> contacts[j+1] = temp;
}

void sorted_by_name(AddressBook *addressBook)
{
    int i, j;
    for(i = 0; i < addressBook -> contactCount - 1; i++)
    {
        for(j = 0; j < addressBook -> contactCount - i - 1; j++)
        {
            if(strcasecmp(addressBook -> contacts[j].name, addressBook -> contacts[j+1].name) > 0)
            {
                swap(addressBook, j);
            }
        }
    }
    display(addressBook);
}
void sorted_by_phone(AddressBook *addressBook)
{
    int i, j;
    for(i = 0; i < addressBook -> contactCount - 1; i++)
    {
        for(j = 0; j < addressBook -> contactCount - i - 1; j++)
        {
            if(strcasecmp(addressBook -> contacts[j].phone, addressBook -> contacts[j+1].phone) > 0)
            {
                swap(addressBook, j);
            }
        }
    }
    display(addressBook);
}
void sorted_by_email(AddressBook *addressBook)
{
    int i, j;
    for(i = 0; i < addressBook -> contactCount - 1; i++)
    {
        for(j = 0; j < addressBook -> contactCount - i - 1; j++)
        {
            if(strcasecmp(addressBook -> contacts[j].email, addressBook -> contacts[j+1].email) > 0)
            {
                swap(addressBook, j);
            }
        }
    }
    display(addressBook);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook -> contactCount >= 100)
    {
        printf("Address Book is full\n");
        return;
    }
    //Name
    while(1)
    {
        printf("Enter Name : ");
        scanf(" %[^\n]",addressBook -> contacts[addressBook -> contactCount].name);
        if(!valid_name(addressBook -> contacts[addressBook -> contactCount].name))
        {
            printf("Re Enter the name again\n");
            continue;
        }
        //Check for name is duplicate or not
        if(duplicate_name(addressBook, addressBook -> contacts[addressBook -> contactCount].name, -1))
        {
            printf("Name is already taken, please enter the unique name\n");
            continue;
        }
        break; //Valid and Unique name
    }
    //Phone
    while(1)
    {
        printf("Enter Phone Number : ");
        scanf(" %s",addressBook -> contacts[addressBook -> contactCount].phone);
        if(!valid_phone(addressBook -> contacts[addressBook -> contactCount].phone))
        {
            printf("Re enter phone Number\n");
            continue;
        }
        //Check for Phone number is duplicate or not
        if(duplicate_phone(addressBook, addressBook -> contacts[addressBook -> contactCount].phone, -1))
        {
            printf("Phone number is already taken, please enter the unique number\n");
            continue;
        }
        break; //Valid and Unique phone number
    }
    //Email
    while(1)
    {
        printf("Enter Email : ");
        scanf(" %s",addressBook -> contacts[addressBook -> contactCount].email);
        if(!valid_email(addressBook -> contacts[addressBook -> contactCount].email))
        {
            printf("Re enter the email\n");
            continue;
        }
        //Check for Email is duplicate or not
        if(duplicate_email(addressBook, addressBook -> contacts[addressBook -> contactCount].email, -1))
        {
            printf("Email is already taken, please enter the unique number\n");
            continue;
        }
        break;
    }
    addressBook -> contactCount++;
}
//Valid name or not
int valid_name(char *name)
{
    for(int i=0; name[i] != 0; i++)
    {
        if((!isalnum(name[i])) && (name[i] != ' '))
        {
            return 0;
        }
    }
    return 1;
}
//Name is duplicate or not
int duplicate_name(AddressBook *addressBook, char *name, int index)
{
    int i;
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(i != index && strcasecmp(addressBook -> contacts[i].name, name) == 0)
        {
            return 1;//Duplicate
        }
    }
    return 0;//Not duplicate
}
//Valid phone number or not
int valid_phone(char *phone)
{
    if(strlen(phone) != 10)
    {
        return 0;
    }
    if(phone[0] < '6' || phone[0] > '9')
    {
        return 0;
    }
    for(int i=0; phone[i] != 0; i++)
    {
        if(!isdigit(phone[i]))
        {
            return 0;
        }
    }
    return 1;
}
//Phone number is duplicate or not
int duplicate_phone(AddressBook *addressBook, char *phone, int index)
{
    int i;
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(i != index && strcasecmp(addressBook -> contacts[i].phone, phone) == 0)
        {
            return 1;// Duplicate 
        }
    }
    return 0;//Not duplicate
}
//Valid Email or not
int valid_email(char *email)
{
    int i,at_count = 0,at_index, com_count=0;
    int len = strlen(email);
    for(i=0 ; email[i] != 0; i++)
    {
        if(!isalnum(email[0]) || email[i] == ' ' || isupper(email[i]) != 0)
        {
            return 0;
        }
        if(email[i] == '@')
        {
            at_count++;
            at_index=i;
        }
        if(i >= 3 && strncmp(&email[i - 3], ".com", 4) == 0)
        {
            com_count++;
        }
    }
    if(at_count != 1 || com_count != 1|| (len - 4) - at_index < 2)
    {
        return 0;
    }
    if(strcmp(&email[len -4], ".com") != 0)
    {
        return 0;
    }
    return 1;
}
//Email is duplicate or not
int duplicate_email(AddressBook *addressBook, char *email, int index)
{
    int i;
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(i != index && strcasecmp(addressBook -> contacts[i].email, email) == 0)
        {
            return 1;//Duplicate
        }
    }
    return 0;// Not Duplicate
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char search[50];
    do
    {
        printf("\nSearch by :\n");
        printf("1. Name\n");
        printf("2. Phone number\n");
        printf("3. Email\n");
        printf("4. Exit\n");

        printf("Enter your choice : ");
        scanf("%d",&choice);

        if(choice == 4)
        {
            printf("Exiting...\n");
            return;
        }
        if(choice >= 1 && choice <= 3)
        { 
            printf("Enter what you wants to search : ");
            scanf("%s", search);
        }
        switch(choice)
        {
            case 1: //Search by Name
                search_by_name(addressBook, search);
                break;
            case 2:  //Search by Phone Number
                search_by_phone(addressBook, search);
                break;
            case 3:  //Search by Email
                search_by_email(addressBook, search);
                break;
            default:// If choice is > 3
                printf("Invalid input\n");
        }
    } while (1);  
}

void search_by_name(AddressBook *addressBook, char *search)
{
    int i,flag;
    flag = 0;
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcasestr(addressBook -> contacts[i].name,search) != NULL)
        {
            if(flag == 0)
            {
                printf("%-8s%-25s%-15s%s\n","SI No.","Name","Phone","Email");
                flag = 1;
            }
            printf("%-8d%-25s%-15s%s\n",i+1, addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
        }
    }
    if(flag == 0)
    {
        printf("Contact is not found\n");
    }
}

void search_by_phone(AddressBook *addressBook, char *search)
{
    int i,flag;
    flag = 0;
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcasestr(addressBook -> contacts[i].phone,search) != NULL)
        {
            if(flag == 0)
            {
                printf("%-8s%-25s%-15s%s\n","SI No.","Name","Phone","Email");
                flag = 1;
            }
            printf("%-8d%-25s%-15s%s\n",i+1, addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
        }
    }
    if(flag == 0)
    {
        printf("Contact is not found\n");
    }
}

void search_by_email(AddressBook *addressBook, char *search)
{
    int i,flag;
    flag = 0;
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcasestr(addressBook -> contacts[i].email, search) != NULL)
        {
            if(flag == 0)
            {
                printf("%-8s%-25s%-15s%s\n","SI No.","Name","Phone","Email");
                flag = 1;
            }
            printf("%-8d%-25s%-15s%s\n",i+1, addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
        }
    }
    if(flag == 0)
    {
        printf("Contact is not found\n");
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice, index;
    char search[40];
    do
    {
        printf("\nEdit the Contacts by :\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        if(choice == 4)
        {
            printf("Exiting...\n");
            return;
        }
        //Search for editing contact
        if(choice >= 1 && choice <= 3)
        {
            printf("Which one you wants to edit : ");
            scanf(" %[^\n]",search);
        }
        switch(choice)
        {
            case 1://By name
                search_by_name(addressBook, search);
                printf("Select the index number of contact which one you want to edit : ");
                index_value(addressBook, &index);
                edit_choice(addressBook, index);
                break;
            case 2://By phone number
                search_by_phone(addressBook, search);
                printf("Select the index number of contact which one you want to edit : ");
                index_value(addressBook, &index);
                edit_choice(addressBook, index);
            break;
            case 3://By Email
                search_by_email(addressBook, search);
                printf("Select the index number of contact which one you want to edit : ");
                index_value(addressBook, &index);
                edit_choice(addressBook, index);
                break;
            default:
                printf("Invalid Input\n");
        }
    } while (1); 
}

void index_value(AddressBook *addressBook, int *index)
{
    while(1)
    {
        scanf("%d",index);
        (*index)--;
        if(*index >= 0 && *index < addressBook -> contactCount)
        {
            break;
        }
        else
        {
            printf("Re enter the index number : ");
        }
    }
}

void edit_choice(AddressBook *addressBook, int index)
{
    int choice;
    do
    {
        printf("\nWhich one you wants to edit :\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter the choice : ");
        scanf("%d", &choice);

        if(choice == 4)
        {
            printf("Exiting...\n");
            return;
        }
        switch(choice)
        {
            case 1:
            printf("Enter New Name : ");
            while(1)
            {
                scanf(" %[^\n]",addressBook -> contacts[index].name);
                if(!valid_name(addressBook -> contacts[index].name))
                {
                    printf("Re Enter the name again\n");
                    continue;
                }
                //Check for name is duplicate or not
                if(duplicate_name(addressBook, addressBook -> contacts[index].name, index))
                {
                    printf("Name is already taken, please enter the unique name\n");
                    continue;
                }
                printf("Contact is editted successfully..\n");
                break; //Valid and Unique name
            }
            break;
            case 2:
            printf("Enter New Phone number : ");
            while(1)
            {
                scanf("%s",addressBook -> contacts[index].phone);
                if(!valid_phone(addressBook -> contacts[index].phone))
                {
                    printf("Re Enter the phone number again\n");
                    continue;
                }
                //Check for phone number is duplicate or not
                if(duplicate_phone(addressBook, addressBook -> contacts[index].phone, index))
                {
                    printf("Phone number is already taken, please enter the unique phone number\n");
                    continue;
                }
                printf("Contact is editted successfully..\n");
                break; //Valid and Unique 
            }
            break;
            case 3:
            printf("Enter New email : ");
            while(1)
            {
                scanf(" %s",addressBook -> contacts[index].email);
                if(!valid_email(addressBook -> contacts[index].email))
                {
                    printf("Re Enter the email again\n");
                    continue;
                }
                //Check for email is duplicate or not
                if(duplicate_email(addressBook, addressBook -> contacts[index].email, index))
                {
                    printf("Email is already taken, please enter the unique email\n");
                    continue;
                }
                printf("Contact is editted successfully..\n");
                break; //Valid and Unique
            }
            break;
            default:
            printf("Invalid choice\n");  
        }
    } while (1);
    
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice, index;
    char search[40];
    do
    {
        printf("\nDelete the Contact by :\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        if(choice == 4)
        {
            printf("Exiting...\n");
            return;
        }
        //Search for deleting contact
        if(choice >= 1 && choice <= 3)
        {
            printf("Which one you wants to delete : ");
            scanf(" %[^\n]",search);
        }
        switch(choice)
        {
            case 1://By name
                search_by_name(addressBook, search);
                printf("Select the index number of contact which one you want to delete : ");
                index_value(addressBook, &index);
                delete_contact(addressBook, index);
                break;
            case 2://By phone number
                search_by_phone(addressBook, search);
                printf("Select the index number of contact which one you want to delete : ");
                index_value(addressBook, &index);
                delete_contact(addressBook, index);
                break;
            case 3://By Email
                search_by_email(addressBook, search);
                printf("Select the index number of contact which one you want to delete : ");
                index_value(addressBook, &index);
                delete_contact(addressBook, index);
                break;
            default:
                printf("Invalid Input\n");
        }
    } while (1); 
}

void delete_contact(AddressBook *addressBook, int index)
{
    for(int i = index; i < addressBook -> contactCount - 1; i++)
    {
        addressBook -> contacts[i] = addressBook -> contacts[i+1];
    }
    addressBook -> contactCount--;
    printf("Contact deleted Successfully...\n");
}