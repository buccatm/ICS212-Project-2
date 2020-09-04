/**********************************************************************************************************************
//
//  NAME:                                 MARCOS BUCCAT JR.
//
//  HOMEWORK:                             PROJECT 2
//
//  CLASS:                                ICS 212
//
//  INSTRUCTOR:                           RAVI NARAYAN
//
//  DATE:                                 APRIL 10, 2020
//
//  FILE:                                 llist.cpp
//
//  DESCRIPTION:
//    This file contains the database definiton. It will also print 
//    values when in debugmode.
//
**********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "record.h"
#include "llist.h"

#ifdef DEBUG
#define STATUS "\n\tDEBUG MODE ENABLE\n"
#define DEBUGING 1
#endif

using namespace std;

/***********************************************************************************************************************
//  
//  FUNCTION NAME:                         llist
//
//  DESCRIPTION:                           This is the default constructor. Which will be creating the list. If there 
//                                         are data within a file, that file is read and the list is set up base on the 
//                                         number of records in the file. If the file is empty, the list is empty by default.
//
//  PARAMETER:                             this(record *) : This is the pointer that points to the first
//                                                          record of the list.
//
//  RETURN VALUE:                          NONE
//
***********************************************************************************************************************/

llist::llist()
{
    strcpy(this -> filename, "default.txt");
    this -> start = NULL;
    #if DEBUGING
        cout << STATUS << "\nCreating Default Contruct\n" << endl;
        cout << "file to read: " << filename << "\n" << endl;
    #endif
    readfile();
    #if DEBUGING
        cout << "Exiting Default Constructor" << endl;
        cout << "\n================ EXIT FUNCTION ===================" << endl;
    #endif
}

/**********************************************************************************************************************
//
//  FUNCTION NAME:                         llist
//
//  DESCRIPTION:                           This Function is an overloaded version of the constructor. It is still doing the
//                                         same as the default constructor but, it will read the file that is passed in.
//
//  PARAMETER:                             filename (char[]) : The name of the file to read
//                                         this(record *)    : This is the pointer that points to the first
//                                                             record of the list.
//
//  RETURN VALUE:                          NONE
//
**********************************************************************************************************************/

llist::llist(char filename[])
{
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "\tConstructing List\n" << endl;
    #endif
    strcpy(this -> filename, filename);
    this -> start = NULL;
    readfile();
    #if DEBUGING
        cout << "\n\tCreating the list with data from file:" << filename << endl;
        cout << "\tEXITING CONSTRUCTOR" << endl;
        cout << "\n================ EXIT FUNCTION ===================" << endl;
    #endif
}

/*****************************************************************************************
//  
//  FUNCTION NAME:                llist
//
//  DESCRIPTION:                  This is the copy Constructor. This will copy all of the 
//                                records in the original list. The order of the list will
//                                be the same as the original list at the moment the program
//                                started. The contents will be writen to a file called
//                                "Copy_Data.txt". In Debug all of its data will be printed 
//                                at the start of the program.
//
//  PARAMETERS:                   other (llist&) : The list, to be copying.
//                                this(record *) : This is the pointer that points to the first
//                                                 record of the list. This pointer is not visible.
//
//  Return value:                 NONE
//
********************************************************************************************/

llist::llist(llist& other)
{
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "Copy Constructor" << endl;
    #endif
    record * temp;
    record * position;
    record * prev;
    start = NULL;
    temp = NULL;
    prev = NULL;
    position = other.start;
    strcpy(filename, "Copy_Data.txt");
    while (position != NULL)
    {
        #if DEBUGING
            cout << "Position at orginal LIST: " << position << endl;
            cout << "Start: " << start << endl;
            cout << "PREVIOUS POS: " << prev << endl;
        #endif
        if (start != NULL)
        {
            temp = new record;
            temp -> accountno = position -> accountno;
            strcpy(temp -> name, position -> name);
            strcpy(temp -> address, position -> address);
            temp -> next = NULL;
            prev -> next = temp;
            prev = temp;
        }
        #if DEBUGING
            cout << "Temp: " << temp << "\n" << endl;
        #endif
        if (start == NULL)
        {
            start = new record;
            start -> accountno = position -> accountno;
            strcpy(start -> name, position -> name);
            strcpy(start -> address, position -> address);
            start -> next = NULL;
            prev = start;
        }
        position = position -> next;
    }
    #if DEBUGING
        cout << "Exit Copy Constructor" << endl;
        cout << "\n================ EXIT FUNCTION ===================" << endl;
    #endif
}


/***********************************************************************************************************************
//  
//  FUNCTION NAME:                   ~llist
//
//  DESCRIPTION:                     This is the deconstructor. This will deconstruct the constructor by first writing
//                                   whatever records are left in the list to a file then cleaning up the heap space.
//
//  PARAMETER:                       this(record *) : This is the pointer that points to the first
//                                                    record of the list.
//
//  RETURN VALUE:                    NONE
//
************************************************************************************************************************/

llist::~llist()
{
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "\tDestroying the list\n" << endl;
    #endif
    writefile();
    cleanup();
    #if DEBUGING
        cout << "\tEXITING DECONSTRUCTOR" << endl;
        cout << "\n================ EXIT FUNCTION ===================" << endl;   
    #endif
}

/************************************************************************************************************************
//
//  FUNCTION NAME:                  addRecord
//
//  DESCRIPTION:                    This function will add a record to the list in the heapspace. If the list already has
//                                  some records in the list, the added list will be added at the end of the list.
//
//  PARAMETER:                      accountno (int)  : The accountno passed in from the user. This will be the accountno
//                                                     of the record to add.
//                                  name (char[])    : The name passed in from the user. This will be the name
//                                                     of the record to add.
//                                  address (char[]) : The address passed in from the user. This will be the address
//                                                     of the record to add.
//                                  this(record *)   : This is the pointer that points to the first
//                                                     record of the list.
//
//  RETURN VALUE:  result:          -1: failure
//                                   0: success
//
***************************************************************************************************************************/

int llist::addRecord(int accountno, char name[], char address[])
{
    struct record * temp;
    struct record * index;
    int result;
    result = -1;
    index = start;
    if (accountno > 0)
    {
        temp = new record;
        temp -> accountno = accountno;
        strcpy(temp -> name, name);
        strcpy(temp -> address, address);
        temp -> next = NULL;
        #if DEBUGING
            cout << "\n================ DEBUG MODE ===================" << endl;
            cout << "START :" << start << endl;
            cout << "\nCreating RECORD to add\n" << endl;
            cout << "TEMP: " << temp << endl;
            cout << "Accountno: " << temp -> accountno << endl;
            cout << "Name: " << temp -> name << endl;
            cout << "Address: " << temp -> address << endl;
            cout << "NEXT: " << temp -> next << "\n" << endl;
        #endif
        if (start != NULL)
        {
            #if DEBUGING
                cout << "Current Start: " << index << "\n" <<endl;
            #endif
            while (index -> next != NULL)
            {
                #if DEBUGING
                    cout << "Traversing to the end" << endl;
                    cout << "Current index: " << index << "\n" <<endl;
                    cout << "Next index: " << index -> next << "\n" <<endl;
                #endif
                index = index -> next;
            }
            temp -> next = index -> next;
            index -> next = temp;
            result = 0;
        }
        if (start == NULL)
        {
            this -> start = temp;
            index = start;
            result = 0;
            #if DEBUGING
                cout << "Adding record to empty list\n" << endl;
            #endif
        }
    }
    #if DEBUGING
        cout << "NEW START: " << start << endl;
        cout << "Exiting AddRecord" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return result;
}

/*********************************************************************************************************
//  
//  FUNCTION NAME:                          printRecord
//
//  DESCRIPTION:                            This function will print all the records that matches
//                                          the accountno inputed by the user. It will aslo count
//                                          the amount of records that matches this accountno.
//
//  PARAMETER:                              accountno (int) : The accountno to look for in the list
//                                          this(record *)  : This is the pointer that points to the first
//                                                           record of the list.
//
//  RETURN VALUE:  result:                  -1: fail to find record or empty list
//                                           0: record was found
//
**********************************************************************************************************/

int llist::printRecord(int accountno)
{
    struct record * index;
    int result;
    int records_found;

    result = -1;
    records_found = 0;
    index = start;
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "Entered Print Record" << endl;
        cout << "\nPrint all record With this Accountno: " << accountno << "\n" << endl;
        cout << "Starting index: " << index << endl;
    #endif
    if (start == NULL)
    {
        cout << "LIST is empty" << endl;
    }
    if (accountno > 0 && start != NULL)
    {
        while (index != NULL)
        {
            if (accountno == index -> accountno)
            {
                #if DEBUGING
                    cout << "Record found at: " <<  index << "\n" << endl;
                #endif
                cout << "ACCOUNT#: " << index -> accountno << endl;
                cout << "NAME: " << index -> name << endl;
                cout << "ADDRESS: " << index -> address << "\n" <<endl;
                records_found++;
            }
            index = index -> next;
            #if DEBUGING
                cout << "Current index: " << index << "\n" << endl;
            #endif
        }
    }
    cout << "Number of Records: " << records_found << ", with Accountno: " << accountno << endl;
    if (records_found > 0)
    {
        result = 0;
    }
    if (records_found == 0)
    {
        cout << "No Such Record Found In List" << endl;
    }
    #if DEBUGING
        cout << "Exiting PrintRecord" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return result;
}

/**************************************************************************************************************
//  
//  FUNCTION NAME:                     modifyRecord
//
//  DESCRIPTION:                       This function will modify all of the record with the matching accountno.
//                                     Note that All the matching record will have the same modified address.
//
//  PARAMETERS:                        accountno (int)  : The record accountno to look for to modify.
//                                     address (char[]) : The char array that contains the new address
//                                     this(record *)   : This is the pointer that points to the first
//                                                        record of the list.
//
//  RETURN VALUE:  result:             -1: no record found or list is empty
//                                      0: success
//
****************************************************************************************************************/

int llist::modifyRecord(int accountno, char address[])
{
    struct record * index;
    int result;
    int records_found;
    index = start;
    result = 0;
    records_found = 0;
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "Entered Modify Record" << endl;
        cout << "\nModify all record With this Accountno: " << accountno << "\n" << endl;
        cout << "Starting index: " << index << endl;
    #endif
    cout << "\nNew address to Input:\n" << address << "\n" <<endl;
    if (start == NULL)
    {
        cout << "LIST is empty" << endl;
    }
    if (start != NULL && accountno > 0)
    {
        while (index != NULL)
        {
            if (accountno == index -> accountno)
            {
                #if DEBUGING
                    cout << "Record Found\n" << endl;
                    cout << "Modify Addres at Record: " << index << "\n" << endl;
                    cout << "ACCOUNT#: " << index -> accountno << endl;
                    cout << "NAME: " << index -> name << endl;
                    cout << "OLD ADDRESS: " << index -> address << endl;
                    cout << "\nNEW ADDRESS: " << index -> address << endl;
                    cout << "NEXT: " << index -> next << "\n" <<endl;
                #endif
                strcpy(index -> address, address);
                records_found++;
            }
            index = index -> next;
            #if DEBUGING
                cout << "Current index: " << index << "\n" << endl;
            #endif
        }
    }
    cout << "Number of Records modified: " << records_found << "\n" << endl;
    if (records_found == 0)
    {
        cout << "No Such Record Found In The List" << endl;
        result = -1;
    }
    #if DEBUGING
        cout << "Exiting ModifyRecord" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return result;
}

/********************************************************************************************************
//  
//  FUNCTION NAME:                       deleteRecord
//
//  DESCRIPTION:                         This function will delete all the records in the list that matches
//                                       the inputed accountno.
//
//  PARAMETER:                           accountno (int) : The accountno of the records to delete from list.
//                                       this(record *) : This is the pointer that points to the first
//                                                        record of the list.
//
//  RETURN VALUE:  result                -1 : Record not found or list is empty
//                                        0 : success
//
***********************************************************************************************************/

int llist::deleteRecord(int accountno)
{
    struct record * index;
    struct record * remove;
    struct record * next_index;
    int result;
    int records_removed;
    result = -1;
    records_removed = 0;
    index = start;
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "Entered Delete Record" << endl;
        cout << "\nDelete all record With this Accountno: " << accountno << "\n" << endl;
        cout << "Starting index: " << index << "\n" << endl;
    #endif
    if (index == NULL)
    {
        cout << "List is empty!" << endl;
    }
    if (accountno > 0 && index != NULL)
    {
        do
        {
            if (accountno == index -> accountno)
            {
                remove = index;
                #if DEBUGING
                    cout << "Record Found at the Start of List\n" << endl;
                    cout << "Curent Start: " << start << endl;
                    cout << "NEXT: " << index -> next << endl;
                    cout << "Remove: " << remove << endl;
                #endif
                index = index -> next;
                this -> start = index;
                delete remove;
                records_removed++;
                remove = NULL;
                #if DEBUGING
                    cout << "\nNew Start: " << start << endl;
                    cout << "Remove: " << remove << "\n" <<endl;
                #endif
            }
            if (index != NULL)
            {
                if (accountno != index -> accountno)
                {
                    next_index = index -> next;
                    #if DEBUGING
                        cout << "\nCurrent index: " << start << endl;
                        cout << "NEXT: " << next_index << "\n" << endl;
                    #endif
                    if (next_index != NULL)
                    {
                        if (accountno == next_index -> accountno)
                        {
                            remove = next_index;
                            next_index = remove -> next;
                            index -> next = remove -> next;
                            #if DEBUGING
                                cout << "Record Found!\n" << endl;
                                cout << "NEW NEXT: " << next_index << endl;
                                cout << "Remove: " << remove << endl;
                            #endif
                            delete remove;
                            remove = NULL;
                            records_removed++;
                        }
                     }
                     if (next_index != NULL)
                     {
                         if (accountno != next_index -> accountno)
                         {
                             index = index -> next;
                             #if DEBUGING
                                 cout << "\nCurrent index: " << index << endl;
                             #endif
                         }
                     }
                     if (next_index == NULL)
                     {
                         index = NULL;
                         #if DEBUGING
                             cout << "\nEnd of list\n" << endl;
                         #endif
                     }
                }
            }
            remove = NULL;
        }
        while (index != NULL);
    }
    cout << "Number of Records Removed: " << records_removed << endl;
    if (records_removed == 0)
    {
        cout << "No Such File Found In the List\n" << endl;
    }
    if (records_removed > 0)
    {
        result = 0;
    }
    #if DEBUGING
        cout << "Exiting DeleteRecord" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return result;
}

/****************************************************************************************************************
//  
//  FUNCTION NAME:                                cleanup
//
//  DESCRIPTION:                                  This function will be cleaning up the heap space, by deleteing
//                                                all of the records in the list.
//
//  PARAMETER:                                    this(record *) : This is the pointer that points to the first
//                                                                 record of the list.
//
//  RETURN VALUE:                                 NONE
//
****************************************************************************************************************/

void llist::cleanup()
{
    struct record * index;
    struct record * remove;
    int counter;
    index = start;
    remove = start;
    counter = 0;
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "CLEAN UP" << endl;
        cout << "Starting Address: " << index << "\n" <<endl;
    #endif
    if (start != NULL)
    {
        while (index -> next != NULL)
        {
            #if DEBUGING
                cout << "Cleaning up the heap space" << endl;
                cout << "Current Index: " << remove << endl;
                cout << "NEXT: " << index -> next << endl;
                cout << "REMOVE: " << remove << "\n" <<endl;
            #endif
            index = index -> next;
            delete remove;
            counter++;
            this ->start = index;
            remove = start;
        }
        if (index -> next == NULL)
        {
            #if DEBUGING
                cout << "Current Index: " << remove << endl;
                cout << "NEXT: " << index -> next << endl;
                cout << "REMOVE: " << remove << "\n" << endl;
            #endif

            index = index -> next;
            delete remove;
            counter++;
            remove = index;
            this -> start = index;
        }
    }
    #if DEBUGING
        cout << "Amount Of Records Removed: " << counter << endl;
        cout << "START: " << start << endl;
        cout << "Exiting DeleteRecord" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
}

/***********************************************************************************************************
//
//  FUNCTION NAME:                            readfile
//
//  DESCRIPTION:                              This function will be reading data from a record. The data 
//                                            in this file will be read and inputed into the list.
//                                            The '$' charactor will determine the number of records in this list.
//
//  PARAMETER:                                this(record *) : This is the pointer that points to the first
//                                                             record of the list.
//
//  RETURN VALUE:   result                    -1 : There was nothing read from file, or file doesnot exit
//                                             0 : Successfully added contents from file to the list
//
*************************************************************************************************************/

int llist::readfile()
{
    ifstream read;
    int result;
    int index;
    int size;
    int counter;
    int account;
    int skip;
    int power;
    int base;
    int total;
    int line;
    char input;
    int accountno[13];
    char name[25];
    char address[80];
    result = -1;
    counter = 0;
    total = 0;
    base = 1;
    power = 0;
    size = 0;
    account = 0;
    skip = 0;
    line = 1;
    index = 0;
    read.open(filename);
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "Reading File" << endl;
        cout << "Starting Address: " << start << "\n" <<endl;
    #endif
    if (!(read.is_open()))
    {
        #if DEBUGING
            cout << "File does Not Exist!" << endl;
        #endif
    }
    if (read.is_open())
    {
        #if DEBUGING
            cout << "The file exits!" << endl;
        #endif
        while (read.get(input))
        {
            if (line == 1 && input != '$')
            {
                if (input != '\n')
                {
                    accountno[index] = static_cast<int>(input);
                    if (accountno[index] == 48)
                    {
                        accountno[index] = 0;
                    }
                    if (accountno[index] == 49)
                    {
                        accountno[index] = 1;
                    }
                    if (accountno[index] == 50)
                    {
                        accountno[index] = 2;
                    }
                    if (accountno[index] == 51)
                    {
                        accountno[index] = 3;
                    }
                    if (accountno[index] == 52)
                    {
                        accountno[index] = 4;
                    }
                    if (accountno[index] == 53)
                    {
                        accountno[index] = 5;
                    }
                    if (accountno[index] == 54)
                    {
                        accountno[index] = 6;
                    }
                    if (accountno[index] == 55)
                    {
                        accountno[index] = 7;
                    }
                    if (accountno[index] == 56)
                    {
                        accountno[index] = 8;
                    }
                    if (accountno[index] == 57)
                    {
                        accountno[index] = 9;
                    }
                    if (index < 12)
                    {
                        index++;
                    }
                }
                if (input == '\n')
                {
                    for (size = index - 1; size >= 0; size--)
                    {
                        if (power > 0)
                        {
                            base *= 10;
                        }
                        total += base * accountno[size];
                        power++;
                    }
                    power = 0;
                    index = 0;
                    base = 1;
                    account = total;
                    total = 0;
                    line = 4;
                }
            }
            if (line == 2)
            {
                if (input != '\n')
                {
                    name[index] = input;
                    if (index < 23)
                    {
                        index++;
                    }
                }
                if (input == '\n')
                {
                    name[index] = '\0';
                    line = 6;
                    index = 0;
                }
            }
            if (line == 3)
            {
                if (input != '$')
                {
                    address[index] = input;
                    if (index < 78)
                    {
                        index++;
                    }
                }
                if (input == '$')
                {
                    address[index] = '\0';
                    counter++;
                    #if DEBUGING
                        cout << "RECORD# " << counter << endl;
                    #endif
                    line = 5;
                    index = 0;
                    addRecord(account, name, address);
                }
            }
            if (line == 4)
            {
                line = 2;
            }
            if (line == 5)
            {
                skip++;
            }
            if (skip == 2)
            {
                line = 1;
                skip = 0;
            }
            if (line == 6)
            {
                line = 3;
            }
        }
        result = 0;
        read.close();
    }
    #if DEBUGING
        cout << "Counter: " << counter << endl;
        cout << "START: " << start << endl;
        if (counter == 0)
        {
            cout << "File is Empty" << endl;
        }
        cout << "Exiting ReadFile" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return result;
}

/*********************************************************************************************************
//  
//  FUNCTION NAME:                             writefile
//
//  DESCRIPTION:                               This function will write the records in the list to a file.
//
//  PARAMETER:                                 this(record *) : This is the pointer that points to the first
//                                                              record of the list.
//
//  RETURN VALUE:  result:                     -1 : file does not exist 
//                                             0  : success
//
**********************************************************************************************************/

int llist::writefile()
{
    int result;
    int recs;
    ofstream write;
    struct record * index;
    recs = 0;
    result = -1;
    index = start;
    write.open(filename);
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "Writing data to file: " << filename << "\n" << endl;
        cout << "Starting Address: " << start << "\n" <<endl;
    #endif
    if (write.is_open())
    {
        if (start != NULL)
        {
            while (index != NULL)
            {
                write << index -> accountno << endl;
                write << index -> name << endl;
                write << index -> address << "$" << endl;
                recs++;
                index = index -> next;
                #if DEBUGING
                    cout << "Traversing list" << endl;
                    cout << "Current index: " << index << "\n" <<endl;
                #endif
            }
            result = 0;
        }
        write.close();
    }
    #if DEBUGING
        cout << "Number of Recs Writen to file: " << recs << endl;
        if (recs == 0)
        {
            cout << "The list is empty" << endl;
        }
        cout << "Exiting Write Function" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
        #endif
    return result;
}

/******************************************************************************
//  
//  FUNCTION NAME:                 operator<<
//
//  DESCRIPTION:                   This function overloaded the operator <<. This is
//                                 is an overloaded funtion that will print the
//                                 all of the record in the list
//
//  PARAMETER:                     out (ostream&) : The output stream, or the object for
//                                                  output stream.
//                                 list(llist)    : This is the class that contains the 
//                                                  encapsulized member variables and 
//                                                  member functions.
//
//  RETURN VALUE:                  The output stream, printing the list.
//
*******************************************************************************/

ostream& operator<<(ostream& out, llist & list)
{
    cout << endl;
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "PRinting All function, overloaded operator" << endl;
        cout << "starting Address:" << list.start << "\n" << endl;
    #endif
    struct record * temp;
    int counter;
    counter = 0;
    temp = list.start;
    if (temp == NULL)
    {
        cout << "LIST is Empty" << endl;
    }
    while (list.start != NULL)
    {
        #if DEBUGING
            cout << "Current Address: " << list.start << endl;
            out << "ADDRESS: " << list.start << endl;
        #endif
        out << "ACCOUNTNO: " << list.start -> accountno << endl;
        out << "NAME: " <<list.start -> name << endl;
        out << "ADDRESS: " << list.start -> address << endl;

        #if DEBUGING
            out << "NEXT:" << list.start -> next << endl;
        #endif
        out << "\n" << endl;
        counter++;
        list.start = list.start -> next;
    }
    list.start = temp;
    cout << "Number of Records: " << counter << "\n" <<endl;
    #if DEBUGING
        cout << "Exiting ostream" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return out;
}

/**************************************************************************************************
//  
//  FUNCTION NAME:                reverse
//
//  DESCRIPTION:                  This function will take the list and put the list in reverse
//                                order. This function will be done recursively.
//
//  PARAMETER:                    starting (record*)  : The starting address of the list
//                                this(record *)      : This is the pointer that points to the first
//                                                      record of the list. This is not visible
// 
// RETURN VALUE:  starting:       the new starting addrress of the list.
//
**************************************************************************************************/

record * llist::reverse(record * starting)
{
    record * current;
    record * next;
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "RECURSIVE REVERESE FUNCTION:" << endl;
        cout << "Starting Address: " << starting << "\n" << endl;
    if (starting == NULL)
    {
        cout << "List is empty" << endl;
    }
    #endif

    if (starting != NULL)
    {
        current = starting -> next;
        #if DEBUGING
            cout << "Current pointer: " << current << endl;
        #endif

        if (current != NULL)
        {
            next = current -> next;
            #if DEBUGING
                cout << "NEXT: " << next << endl;
            #endif
            if (next != NULL)
            {
                #if DEBUGING
                    cout << "Recursive call" << "\n" << endl;
                #endif
                current = reverse(current);
                #if DEBUGING
                    cout << "RETURN VAL AFTER RECURSIVE CALL: " << current << endl;
                #endif
            }
        
            if (next == NULL)
            {
                start -> next = NULL;
                this -> start = current;
                #if DEBUGING
                    cout << "AT the end of list" << endl;
                #endif
            }
        
            current -> next = starting;
        }
        if (starting -> next == NULL)
        {
            starting = start;
        }
    }
    #if DEBUGING
        cout << "RETURNING: " << starting << "\n" <<endl;
        cout << "Exiting Recursive Reverse(record *)" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
    return starting;
}

/**************************************************************************************************
//
//  FUNCTION NAME:                  reverse
//
//  DESCRIPTION:                    This Function calls the reverse(record*) function to recursively
//                                  put the list in reverse order.
//
//  PARAMETER:                      this(record *) : This is the pointer that points to the first
//                                                   record of the list. This is not visible.
//
//  RETURN VALUE:                   NONE
//
**************************************************************************************************/

void llist::reverse()
{
    if (start == NULL)
    {
        cout << "List is empty!" << endl;
    }
    start = reverse(start);
    #if DEBUGING
        cout << "\n================ DEBUG MODE ===================" << endl;
        cout << "REVERSE FUNCTION WITHOUT PARAMATER" << endl;
        cout << "NEW START: " << start << endl;
        cout << "Exit reverse()" << endl;
        cout << "\n================ EXIT FUNCTION ===================\n" << endl;
    #endif
}
