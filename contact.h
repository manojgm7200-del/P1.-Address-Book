#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int valid_name(char *name);
int duplicate_name(AddressBook *addressBook, char *name, int index);
int valid_phone(char *phone);
int duplicate_phone(AddressBook *addressBook, char *phone, int index);
int valid_email(char *name);
int duplicate_email(AddressBook *addressBook, char *email, int index);

void searchContact(AddressBook *addressBook);
void search_by_name(AddressBook *addressBook, char *search);
void search_by_phone(AddressBook *addressBook, char *search);
void search_by_email(AddressBook *addressBook, char *search);

void editContact(AddressBook *addressBook);
void index_value(AddressBook *addressBook, int *index);
void edit_choice(AddressBook *addressbook, int index);

void deleteContact(AddressBook *addressBook);
void delete_contact(AddressBook *addressBook, int index);

void listContacts(AddressBook *addressBook);
void display(AddressBook *addressBook);
void sorted_by_name(AddressBook *addressBook);
void sorted_by_phone(AddressBook *addressBook);
void sorted_by_email(AddressBook *addressBook);

void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif