/**********************************************************************************************************************
//  
//  NAME:                                  MARCOS BUCCAT JR.
//
//  HOMEWORK:                              PROJECT 2
//
//  CLASS:                                 ICS 212
//
//  INSTRUCTOR:                            RAVI NARAYAN
//
//  DATE:                                  April 12, 2020
//
//  FILE:                                  user-interface.cpp
//
//  DESCRIPTION:
//    This file contains the user interface protoype and
//    definitions. It also contains all other functions
//    to create the user interfacei. This file also 
//    contains the main to execute the project program.
//    The program will be run in debug mode if "project_debug" is executed.
//    The program will run Without debug if "project" is executed.
//
*********************************************************************************************************************/

#include <iostream>
#include "record.h"
#include "llist.h"

#ifdef DEBUG
#define STATUS "\n\tDEBUG MODE ENABLE-INTERFACE\n"
#define DEBUGING 1
#endif

using namespace std;

void user_interface();
void get_input(char[], int, int*);
void check_input(char[], int*, int*, int*, int);
int convert(int arr[], int);
void extract(int[], char[], int);
void getAddress(char[], int);

/********************************************************************************************************************
//
//  FUNCTION NAME:                        main
//  
//  DESCRIPTION:                          This program will run the user-interface. When the user-interface runs
//                                        it will ask the user for inputs. Those inputs will call the database
//                                        methods to modify, add, delete or print the records.
//
//  PARAMETER:                            argc (int)     : The number of arguments passed.
//                                        argu (char*[]) : The actual arguments passed.
//
//  RETURN VALUE:                         0 : Success
//
*********************************************************************************************************************/

int main(int argc, char * argu[])
{
    user_interface();
    return 0;
}

/******************************************************************************************************************************
//  
//  FUNCTION NAME:                       check_input
//
//  DESCRIPTION:                         This function will take in a char array and looks at its elements. The 
//                                       function will count each number, alphabets and special charactors found
//                                       in this array. For read name input mode, exception is made such that
//                                       space, ''' and '.' are not counted. For Normal input mode every charactor
//                                       in the array is counted.
//
//  PARAMETER:                           array (char[]) : The array that stores the char elements to be read.
//                                       number (int*)  : The address to store the number of numbers found in array.
//                                       letter (int*)  : The address to store the number of letters found in array.
//                                       speical (int*) : The address to store the number of special charactors found in array.
//                                       mode (int)     : The mode that will determind if functions is reading for
//                                                        getting names, or normal inputs.
//
//  RETURN VALUE:                        NONE
//
***********************************************************************************************************************************/

void check_input(char array[], int * number, int * letter, int * special, int mode)
{
    int index;
    int nums;
    int letts;
    int sps;
    nums = 0;
    letts = 0;
    sps = 0;
    #if DEBUGING
        cout << "\n========================== DEBUG MODE ============================" << endl;
        cout << "check input function\nPASSING:" << endl;
        cout << "ARRAY: " << array << endl;
        cout << "number ADDRESS: " << number << ", val = " << *number << endl;
        cout << "letter ADDRESS: " << letter << ", val = " << *letter << endl;
        cout << "special ADDRESS: " << special << ", val = "<< *special << endl;
        if (mode == 1)
        {
            cout << "Checking for Getting name input" << endl;
        }
        if (mode == 0)
        {
            cout << "Checking for Getting input" << endl;
        }
    #endif
    for (index = 0; array[index] != '\0'; index++)
    {
        if (array[index] >= '0' && array[index] <= '9')
        {
            nums++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", nums + 1 = " << nums << endl;
            #endif
        }
        if (array[index] >= 'a' && array[index] <= 'z')
        {
            letts++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", letter + 1 = " << letts << endl;
            #endif
        }
        if (array[index] >= 'A' && array[index] <= 'Z')
        {
            letts++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", letter + 1 = " << letts << endl;
            #endif
        }
        if (array[index] >= '!' && array[index] <= '/')
        {
            sps++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index])  << ", special + 1 = " << sps << endl;
            #endif
        }
        if (array[index] >= ':' && array[index] <= '@')
        {
            sps++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", special + 1 = " << sps << endl;
            #endif
        }
        if (array[index] >= '[' && array[index] <= '`')
        {
            sps++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", special + 1 = " << sps << endl;
            #endif
        }
        if (array[index] >= '{' && array[index] <= '}')
        {
            sps++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", special + 1 = " << sps << endl;
            #endif
        }
        if (array[index] == ' ' && mode == 0)
        {
            sps++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", special + 1 = " << sps << endl;
            #endif
        }
        if (array[index] == '~')
        {
            sps++;
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(array[index]) << ", special + 1 = " << sps << endl;
            #endif
        }
        if (mode == 1 && ((array[index] == 39) || (array[index] == '.')))
        {
            sps--;
        }
    }
    if (sps < 0)
    {
        sps = 0;
    }
    *number = nums;
    *letter = letts;
    *special = sps;
     #if DEBUGING
         cout << "Number of Special Chars: " << *special << endl;
         cout << "Number of Numbers: " << *number << endl;
         cout << "Number of letters: " << *letter << endl;
         cout << "\nEND OF CHECK INPUT" << endl;
         cout << "======================== EXIT FUNCTION =============================\n" << endl;
     #endif
}

/*********************************************************************************************************************************
//  
//  FUNCTION NAME:                                  getAddress
//
//  DESCRIPTION:                                    This function will get the address from the user. It Will instruct the user
//                                                  to input a address. The '$' charactor, will enter the inputed address.
//                                                  The Max charactor is 79, so this function will input up to 79 charactors only or
//                                                  if the '$' was detected before reaching the size 79.
//
//  PARAMETER:                                      address (char[]) : The char array to store the input address.
//                                                  size    (int)    : The maximum charactors to input.
//
//  RETRUN VALUE:                                   NONE
//
**********************************************************************************************************************************/

void getAddress(char address[], int size)
{
    char temp[1000];
    int index;
    int max;
    max = 0;
    #if DEBUGING
        cout << "\n========================== DEBUG MODE ============================" << endl;
        cout << "get address function\nPASSING:" << endl;
        cout << "Max Size of address passed: " << size << endl;
    #endif
    cout << "Enter an Address" << endl;
    cout << "Input \'$\' to enter input" << endl;
    cin.getline(temp, 998, '$');
    for (index = 0; temp[index] != '\0'; index++)
    {
        max++;
    }
    #if DEBUGING
        cout << "Size of inputed ADDRESS: " << max << endl;
    #endif
    if (size < max)
    {
        #if DEBUGING
            cout << "Input SIZE, INVALID" << endl;
        #endif
        for (index = 0; index < 78; index++)
        {
            address[index] = temp[index];
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(address[index]) << endl;
            #endif
        }
        address[78] = '\0';
    }
    if (max < size)
    {
        #if DEBUGING
            cout << "Input SIZE, VALID" << endl;
        #endif
        for (index = 0; temp[index] != '\0'; index++)
        {
            address[index] = temp[index];
            #if DEBUGING
                cout << "index[" << index << "]: ";
                cout << static_cast<char>(address[index]) << endl;
            #endif
        }
        address[index] = '\0';
    }
    cin.ignore(1000, '\n');
    #if DEBUGING
        cout << "END OF GET ADDRESS" << endl;
        cout << "======================== EXIT FUNCTION ===========================\n" << endl;
    #endif
}

/*****************************************************************************************************************
//
//  FUNCTION NAME:                                 user_interface
//
//  DESCRIPTION:                                   This function will the interface. It will display the instructions
//                                                 and the option for the user to interact with. The options inputed from
//                                                 user will call the functions from the database or the llilst header file.
//
//  PARAMETER:                                     NONE
//
//  RETURN VALUE:                                  NONE
//
********************************************************************************************************************/

void user_interface()
{
    int run;
    llist list;
    llist list_two(list);
    int option;
    int nums;
    int letts;
    int symb;
    int index;
    int size;
    int accountno;
    int valid;
    char input[1000] = {" "};
    char name[25] = {" "};
    char address[80]= {" "};
    int temp[1000];

    #if DEBUGING
        cout << "\n========================== DEBUG MODE ============================" << endl;
        cout << "User-interface function" << endl;
        cout << "\nDATA OF COPY CONSTRUCTOR" << endl;
        cout << list_two << endl;
    #endif
    char tittle[] = "\n\tThe Bank Interface\n";
    char welcome[] = "\nWelcome to the Bank Menue\n";
    char instruct[] = "\nEnter the Following for options\n";
    char option_one[] = "\tEnter \'1\' to add a record\n";
    char option_two[] = "\tEnter \'2\' to print a record\n";
    char option_three[] = "\tEnter \'3\' to print all records\n";
    char option_four[] = "\tEnter \'4\' to modify a record\n";
    char option_five[] = "\tEnter \'5\' to remove a record\n";
    char option_six[] = "\tEnter \'6\' Reverse list order\n";
    char option_sev[] = "\tEnter \'7\' to exit the program\n";
    char invalid_input[] = "Error Input is Invlaid\n";
    run = 1;
    cout << tittle;
    cout<< welcome;
    cout << instruct;
    cout << endl;
    cout << option_one;
    cout << option_two;
    cout << option_three;
    cout << option_four;
    cout << option_five;
    cout << option_six;
    cout << option_sev << endl;
    while (run == 1)
    {
        option = 0;
        size = 0;
        nums = 0;
        valid = 0;
        letts = 0;
        symb = 0;
        index = 0;
        accountno = 0;
        cout << "Enter Input: ";
        get_input(input, 998, &size);
        check_input(input, &nums, & letts, &symb, 0);
        if (nums > 0 && letts == 0 && symb == 0)
        {
            extract(temp, input, size);
            option = convert(temp, size);
            #if DEBUGING
                cout << "input: " << option << "\n" << endl;
            #endif
        }
        if (option == 1)
        {
            cout << "\n\tAdd a Record To List\n" << endl;
            while (valid == 0)
            {
                cout << "Enter Account Number: ";
                get_input(input, 100, &size);
                check_input(input, &nums, &letts, &symb, 0);
                if (nums > 0 && letts == 0 && symb == 0)
                {
                    extract(temp, input, size);
                    accountno = convert(temp, size);
                }
                if (accountno != 0)
                {
                    valid = 1;
                }
                if (valid == 0)
                {
                    cout << "Try again!" << endl;
                }
            }
            valid = 0;
            while (valid == 0)
            {
                cout << "\nName must not have Numbers or Special Charactors,";
                cout << "names with \''\' or \'.\' will be allowed\n" << endl;
                cout << "Enter name: ";
                get_input(input, 998, &size);
                check_input(input, &nums, &letts, &symb, 1);
                if (nums == 0 && letts > 0 && symb == 0)
                {
                    if (size > 24)
                    {
                        #if DEBUGING
                            cout << "Input SIZE, INVALID" << endl;
                            cout << "Extracting ONLY the 24 charactors" << endl;
                        #endif
                        for (index = 0; index < 23; index++)
                        {
                            name[index] = input[index];
                            #if DEBUGING
                                cout << "index[" << index << "]: ";
                                cout << static_cast<char>(name[index]) << endl;
                            #endif
                        }
                        name[24] = '\0';
                    }
                    if (size < 24)
                    {
                        #if DEBUGING
                            cout << "Input SIZE, VALID" << endl;
                            cout << "Extracting the charactors" << endl;
                        #endif
                        for (index = 0; input[index] != '\0'; index++)
                        {
                            name[index]= input[index];
                            #if DEBUGING
                                cout << "index[" << index << "]: ";
                                cout << static_cast<char>(name[index]) << endl;
                            #endif
                        }
                        name[index] = '\0';
                    }
                    valid = 1;
                }
                if (valid == 0)
                {
                    cout << "Try again!" << endl;
                }
            }
            getAddress(address, 78);
            list.addRecord(accountno, name, address);
        }
        if (option == 2)
        {
            cout << "\n\tPRINT A RECORD" << endl;
            while (valid == 0)
            {
                cout << "Enter Account Number: ";
                get_input(input, 100, &size);
                check_input(input, &nums, &letts, &symb, 0);
                if (nums > 0 && letts == 0 && symb == 0)
                {
                    extract(temp, input, size);
                    accountno = convert(temp, size);
                    cout << "input: " << option << "\n" << endl;
                }
                if (accountno != 0)
                {
                    valid = 1;
                }
                if (valid == 0)
                {
                    cout << "Try again!" << endl;
                }
            }
            list.printRecord(accountno);
        }
        if (option == 3)
        {
            cout << "\n\tPRINT ALL RECORD\n" << endl;
            cout << list;
        }
        if (option == 4)
        {
            cout << "\n\tMODIFY Records" << endl;
            while (valid == 0)
            {
                cout << "Enter Account Number: ";
                get_input(input, 100, &size);
                check_input(input, &nums, &letts, &symb, 0);
                if (nums > 0 && letts == 0 && symb == 0)
                {
                    extract(temp, input, size);
                    accountno = convert(temp, size);
                    cout << "input: " << option << "\n" << endl;
                }
                if (accountno != 0)
                {
                    valid = 1;
                }
                if (valid == 0)
                {
                    cout << "Try again!" << endl;
                }
            }
            getAddress(address, 78);
            list.modifyRecord(accountno, address);
            list_two.modifyRecord(accountno, address);
        }
        if (option == 5)
        {
            cout << "\n\tREMOVE Records" << endl;
            while (valid == 0)
            {
                cout << "Enter Account Number: ";
                get_input(input, 100, &size);
                check_input(input, &nums, &letts, &symb, 0);
                if (nums > 0 && letts == 0 && symb == 0)
                {
                    extract(temp, input, size);
                    accountno = convert(temp, size);
                }
                if (accountno != 0)
                {
                    valid = 1;
                }
                if (valid == 0)
                {
                    cout << "Try again!" << endl;
                }
            }
            list.deleteRecord(accountno);
        }
        if (option == 6)
        {
            cout << "Reverse list" << endl;
            list.reverse();
        }
        if (option == 7)
        {
            cout << "\n\tEXITING PROGRAM\n" << endl;
            run = 0;
        }
        if (option != 7 || option > 7)
        {
            if (option <= 0 || option > 7)
            {
                cout << invalid_input << endl;
            }
            cout << instruct;
            cout << option_one;
            cout << option_two;
            cout << option_three;
            cout << option_four;
            cout << option_five;
            cout << option_six;
            cout << option_sev << endl;
        }
    }
    #if DEBUGING
        cout << "END OF INTERFACE" << endl;
        cout << "======================== EXIT FUNCTION ===========================\n" << endl;
    #endif
}

/*************************************************************************************************************
//  
//  FUNCTION NAME:                          extract
//
//  DESCRIPTION:                            This function will extract the char elements from the char array and
//                                          convert those values into numbers from 0 - 9 by converting
//                                          its Ascii Value to what it represent. Example Ascii 48 is '0'. 
//                                          These converted values will be stored into a temp array. These elements 
//                                          extracted must have been checked that they're ascii value is between 
//                                          48 - 57.
//
//  PARAMETER:                              temp (int[])   : The temporary holder for the extracted and converted chars.
//                                          input (char[]) : The char array to be reading and extracting from.
//                                          size (int)     : The number of char values to extract from input.
//
//  RETURN VALUE:                           NONE
//
*************************************************************************************************************/

void extract(int temp[], char input[], int size)
{
    int index;
    #if DEBUGING
        cout << "\n========================== DEBUG MODE ============================" << endl;
        cout << "extract function" << endl;
        cout << "EXTRACT ARRAY "  << input << endl;
        cout << "Store " << temp << endl;
        cout << "Size of Array To Extract: " << size << endl;
    #endif
    for (index = 0; index < size; index++)
    {
        temp[index] = static_cast<int>(input[index]);
        if (temp[index] == 48)
        {
            temp[index] = 0;
        }
        if (temp[index] == 49)
        {
            temp[index] = 1;
        }
        if (temp[index] == 50)
        {
            temp[index] = 2;
        }
        if (temp[index] == 51)
        {
            temp[index] = 3;
        }
        if (temp[index] == 52)
        {
            temp[index] = 4;
        }
        if (temp[index] == 53)
        {
            temp[index] = 5;
        }
        if (temp[index] == 54)
        {
            temp[index] = 6;
        }
        if (temp[index] == 55)
        {
            temp[index] = 7;
        }
        if (temp[index] == 56)
        {
            temp[index] = 8;
        }
        if (temp[index] == 57)
        {
            temp[index] = 9;
        }
        #if DEBUGING
            cout << "INDEX[" << index << "]: " << temp[index] << endl;
        #endif
    }
    #if DEBUGING
        cout << "END OF EXTRACT" << endl;
        cout << "======================== EXIT FUNCTION ===========================\n" << endl;
    #endif
}

/*****************************************************************************************************
//  
//  FUNCTION NAME:                           convert
//
//  DESCRIPTION:                             This Function will convert an int array into an int.
//                                           Example if int array was {1, 2, 3}. The function will
//                                           return the int value 123.
//
//  PARAMETER:                               arr (int[]) : The integer array to be converting to int
//                                           sinze (int) : The number of elements in the array.
//
//  RETURN VALUE:                            total (int) : The converted value of the int array.
//
******************************************************************************************************/

int convert(int arr[], int size)
{
    int max;
    int power;
    int base;
    int total;
    #if DEBUGING
        cout << "\n========================== DEBUG MODE ============================" << endl;
        cout << "Convert function" << endl;
        cout << "ARRAY to Convert "  << arr << endl;
        cout << "Size of Array To Convert: " << size << endl;
    #endif
    max = size;
    power = 0;
    base = 1;
    total = 0;
    #if DEBUGING
        cout << "power: " << power << endl;
        cout << "Total: " << total << endl;
    #endif
    for (max = size; max != 0; max--)
    {
        if (power > 0)
        {
            base *= 10;
        }
        #if DEBUGING
            cout << "power: " << power << endl;
            cout << "Base^[" << power << "] = " << base << endl;
            cout << "total" << " = " << base << " * " << arr[max - 1] << " + " << total << endl;
        #endif
        total += base * arr[max - 1];
        power++;
    }
    #if DEBUGING
        cout << "Value: " << total << "\n" << endl;
        cout << "END OF CONVERT" << endl;
        cout << "======================== EXIT FUNCTION =============================\n" << endl;
    #endif
    return total;
}

/***************************************************************************************************
//  
//  FUNCTION NAME:                      get_input
//
//  DESCRIPTION:                        This function will get the input from the user.
//                                      These inputs are for getting the name, option and accountno.
//
//  PARAMETER:                          input (char[])  : The array to store the input.
//                                      max (int)       : The maximum size of input.
//                                      size_arr (int*) : The address to store the number charactors
//                                                        inputed into the input array.
//
//  RETURN VALUE:                       NONE
//
****************************************************************************************************/

void get_input(char input[], int max, int * size_arr)
{
    int index;
    int size;
    #if DEBUGING
        cout << "\n========================== DEBUG MODE ============================" << endl;
        cout << "get_input function" << endl;
        cout << "Last input in ARRAY: "  << input << endl;
        cout << "Size of Array To Convert: " << size_arr << " = " << *size_arr << endl;
    #endif

    size = 0;
    cin.getline(input, max, '\n');

    for (index = 0; input[index] != '\0'; index++)
    {
        #if DEBUGING
            cout << "index[" << index << "]: " << input[index] << endl;
        #endif
        size++;
    }
    *size_arr = size;
    #if DEBUGING
        cout << "Size of Input: " << size << "\n" << endl;
        cout << "END OF GET INPUT" << endl;
        cout << "====================== EXIT FUNCTION =============================\n" << endl;
    #endif
}
