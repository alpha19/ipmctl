/*
* Copyright (c) 2018, Intel Corporation.
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _DATA_SET_H_
#define _DATA_SET_H_

#include <Uefi.h>
#include <Debug.h>
#include <Types.h>

/*
* Types of values supported in DataSets.
*/
typedef enum {
  KEY_W_STR,
  KEY_UINT64,
  KEY_INT64,
  KEY_UINT32,
  KEY_INT32,
  KEY_UINT16,
  KEY_INT16,
  KEY_UINT8,
  KEY_INT8,
  KEY_BOOL
} KEY_TYPE;

/*
* Information describing a key/value pair in a DataSet.
*/
typedef struct _KEY_VAL_INFO {
  KEY_TYPE Type;      //type of value associated with a particular key
  CHAR16 *Key;        //the name associated with a particular value
  UINT32 ValueSize;   //the binary size of the value
}KEY_VAL_INFO;

#define DATA_SET_CONTEXT  VOID

/*
* Utilized with DataSet recursing APIs.  Executed for each DataSet found while traversing 
* a DataSet tree.
*/
typedef VOID * (*DataSetCallBack)(DATA_SET_CONTEXT *, CHAR16*, VOID*, VOID*);
/*
* Utilized with DataSet recursing APIs.  Executed when all children DataSets have been traversed.
*/
typedef VOID * (*DataSetAllChildrenDoneCallBack)(DATA_SET_CONTEXT *, CHAR16*, VOID*);
/*
* Create a new data set structure
*/
DATA_SET_CONTEXT *CreateDataSet(DATA_SET_CONTEXT *DataSetCtx, CHAR16 *Name, VOID *UserData);
/*
* Get the next child dataset in the data set.
*/
DATA_SET_CONTEXT *GetNextChildDataSet(DATA_SET_CONTEXT *DataSetCtx, DATA_SET_CONTEXT *CurrentChildDataSetCtx);
/*
* Does the data set contain children data sets?
*/
BOOLEAN IsLeaf(DATA_SET_CONTEXT *DataSetCtx);
/*
* Free a data set structure
*/
VOID FreeDataSet(DATA_SET_CONTEXT *DataSetCtx);
/*
* Retrieve a data set by specifying a path in the form of /sensorlist/dimm[0]/sensor[1]
*/
DATA_SET_CONTEXT *GetDataSet(DATA_SET_CONTEXT *Root, CHAR16 *NamePath, ...);
/*
* Get the name of a data set
*/
CHAR16 * GetDataSetName(DATA_SET_CONTEXT *DataSetCtx);
/*
* set the user's data to the corresponding data set (UserData must be allocated by AllocatePool)
*/
VOID SetDataSetName(DATA_SET_CONTEXT *DataSetCtx, CHAR16 *Name);
/*
* Return the user's data from the corresponding data set
*/
VOID * GetDataSetUserData(DATA_SET_CONTEXT *DataSetCtx);
/*
* set the user's data to the corresponding data set (UserData must be allocated by AllocatePool)
*/
VOID SetDataSetUserData(DATA_SET_CONTEXT *DataSetCtx, VOID *UserData);
/*
* Recurses through data set tree, invoking the callback at each node (data set) in the tree
*/
VOID RecurseDataSet(DATA_SET_CONTEXT *DataSetCtx, DataSetCallBack CallBackRoutine, DataSetAllChildrenDoneCallBack ChildrenDoneCallBackRoutine, VOID *, BOOLEAN Sparse);
/*
* Callback routine for squash operation
*/
DATA_SET_CONTEXT *SquashDataSet(DATA_SET_CONTEXT *DataSetCtx);
/*
* Get the next key in the data set. KeyInfo == NULL retrieves the first key in the data set.
*/
KEY_VAL_INFO * GetNextKey(DATA_SET_CONTEXT *DataSetCtx, KEY_VAL_INFO *KeyInfo);
/*
* Get the number of key/val pairs in a data set.
*/
UINT32 GetKeyCount(DATA_SET_CONTEXT *DataSetCtx);
/*
* Set a unicode string value
*/
EFI_STATUS SetKeyValueWideStr(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, const CHAR16 *Val);
/*
* Set an unsigned 64 bit value into the data set.
*/
EFI_STATUS SetKeyValueUint64(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT64 Val);
/*
* Retrieve an unsigned 64 bit value from the data set.
*/
EFI_STATUS SetKeyValueInt64(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT64 Val);
/*
* Set an unsigned 32 bit value into the data set.
*/
EFI_STATUS SetKeyValueUint32(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT32 Val);
/*
* Set an signed 32 bit value into the data set.
*/
EFI_STATUS SetKeyValueInt32(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT32 Val);
/*
* Set an unsigned 16 bit value into the data set.
*/
EFI_STATUS SetKeyValueUint16(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT16 Val);
/*
* Set an signed 16 bit value into the data set.
*/
EFI_STATUS SetKeyValueInt16(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT16 Val);
/*
* Set a boolean into the data set.
*/
EFI_STATUS SetKeyValueBool(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, BOOLEAN Val);
/*
* Set an unsigned 8 bit value into the data set.
*/
EFI_STATUS SetKeyValueUint8(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT8 Val);
/*
* Set a signed 8 bit value into the data set.
*/
EFI_STATUS SetKeyValueInt8(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key,  INT8 Val);
/*
* Retrieve a unicode string from the data set.
*/
EFI_STATUS GetKeyValueWideStr(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, CHAR16 **Val, CHAR16 *DefaultVal);
/*
* Retrieve an unsigned 64 bit value from the data set.
*/
EFI_STATUS GetKeyValueUint64(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT64 *Val, UINT64 *DefaultVal);
/*
* Retrieve an signed 64 bit value into the data set.
*/
EFI_STATUS GetKeyValueInt64(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT64 *Val, INT64 *DefaultVal);
/*
* Retrieve an unsigned 32 bit value from the data set.
*/
EFI_STATUS GetKeyValueUint32(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT32 *Val, UINT32 *DefaultVal);
/*
* Retrieve a signed 32 bit value from the data set.
*/
EFI_STATUS GetKeyValueInt32(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT32 *Val, INT32 *DefaultVal);
/*
* Retrieve an unsigned 16 bit value from the data set.
*/
EFI_STATUS GetKeyValueUint16(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT16 *Val, UINT16 *DefaultVal);
/*
* Retrieve a signed 16 bit value from the data set.
*/
EFI_STATUS GetKeyValueInt16(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT16 *Val, INT16 *DefaultVal);
/*
* Retrieve a boolean value from the data set.
*/
EFI_STATUS GetKeyValueBool(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, BOOLEAN *Val, BOOLEAN *DefaultVal);
/*
* Set an unsigned 8 bit value into the data set.
*/
EFI_STATUS GetKeyValueUint8(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, UINT8 *Val, UINT8 *DefaultVal);
/*
* Retrieve a signed 8 bit value from the data set.
*/
EFI_STATUS GetKeyValueInt8(DATA_SET_CONTEXT *DataSetCtx, const CHAR16 *Key, INT8 *Val, INT8 *DefaultVal);
#endif /** _DATA_SET_H_**/