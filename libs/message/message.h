#ifndef _MESSAGE_H
#define _MESSAGE_H 1

#include "../array/array.h"

#define MAX_LEN_WORKER_NAME 100

typedef struct MasterToWorkerActualInfo {
    SizeData index_row;
    SizeData index_column;

    Array row_array;
    Array column_array;
} MasterToWorkerActualInfo;

typedef struct MasterToWorkerMsgInfo {
    long mType;
    MasterToWorkerActualInfo info;
} MasterToWorkerMsgInfo;


typedef struct WorkerToMasterActualInfo {
    char worker_name[MAX_LEN_WORKER_NAME];
    SizeData index_row;
    SizeData index_column;
    int32_t value;
} WorkerToMasterActualInfo;

typedef struct WorkerToMasterMsgInfo {
    long mType;
    WorkerToMasterActualInfo info;
} WorkerToMasterMsgInfo;

#endif // _MESSAGE_H