/*********************************************************************************************************
//  
//  NAME:                                  MARCOS BUCCAT JR.
//
//  HOMEWORK:                              PROJECT 2
//
//  CLASS:                                 ICS 212
//
//  INSTRUCTOR:                            RAVI NARAYAN
//
//  DATE:                                  APRIL 13, 2020
//
//  FILE:                                  llist.h
//
//  DESCRIPTION:
//   This File contains the class llist. It contains
//   the methods prototype and member variables. It also
//   contains the contructor and decornstructor.
//
**************************************************************************************************************/

#ifndef LLIST
#define LLIST
#include "record.h"
class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record *);
    void        cleanup();

public:
    llist();
    llist(char[]);
    llist(llist&);
    ~llist();
    int addRecord(int, char[], char[]);
    int printRecord(int);
    friend std::ostream& operator<<(std::ostream&, llist&);
    int modifyRecord(int, char[]);
    int deleteRecord(int);
    void reverse();
};
#endif
