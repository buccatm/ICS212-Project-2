/***************************************************************************************************
//
//  NAME:                  MARCOS BUCCAT JR.
//
//  HOMEWORK:              PROJECT 2
//
//  CLASS:                 ICS 212
//
//  INSTRUCTOR:            RAVI NARAYAN
//
//  DATE:                  APRIL 10, 2020
//
//  FILE:                  record.h
//
//  DESCRIPTION:
//    This file contains the record file that contains the address
//    account number, name and the address.
//
***************************************************************************************************/

#ifndef RECORD
#define RECORD

struct record
{
    int                 accountno;
    char                name[25];
    char                address[80];
    struct record *     next;
};
#endif
