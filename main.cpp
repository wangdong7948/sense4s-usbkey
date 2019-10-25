#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>   //dlopen  dlclose  dlsym
#include "kdvtype.h"
#include "sense4.h"

int main()
{
    PSENSE4_CONTEXT pstS4CtxList = NULL;
    DWORD ulCtxListSize = 0;
    DWORD ulResult = 0;
    DWORD ulDeviceNum = 0;
    DWORD nRet = FALSE;
    unsigned char pucSn[8] = {0};
    
    char *error;


    typedef void (*s4enum_t)(SENSE4_CONTEXT*, DWORD*);
    typedef void (*s4open_t)(SENSE4_CONTEXT*);
    typedef void (*s4control_t)(SENSE4_CONTEXT*, DWORD, VOID*, DWORD, VOID*, DWORD, DWORD*);
    typedef void (*s4close_t)(SENSE4_CONTEXT*);
    
    
    //void (*S4Enum)(SENSE4_CONTEXT *, DWORD*);
    //void (*S4Open)(SENSE4_CONTEXT*); 
    //void (*S4Control)(SENSE4_CONTEXT*, DWORD, VOID *, DWORD, VOID *, DWORD, DWORD *);
    //void (*S4Close)(SENSE4_CONTEXT*);

    void *handle = dlopen("./libsenseEIV.so", RTLD_LAZY);
    if(!handle){
        fprintf(stderr, "%s\n", dlerror());
        printf("dlopen ./libsenseEIV.so failed!!\n");
        exit(1);
    }

    s4enum_t S4Enum = (s4enum_t)dlsym(handle, "S4Enum");

    if((error = dlerror())!= NULL){
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    s4open_t S4Open = (s4open_t)dlsym(handle, "S4Open");
    if((error = dlerror())!= NULL){
        fprintf(stderr, "%s\n", error);
        exit(1);
    }


     s4control_t S4Control = (s4control_t)dlsym(handle, "S4Control");
     if((error = dlerror())!= NULL){
         fprintf(stderr, "%s\n", error);
         exit(1);
     }

     s4close_t S4Close = (s4close_t)dlsym(handle, "S4Close");
     if((error = dlerror())!= NULL){
         fprintf(stderr, "%s\n", error);
         exit(1);
     }

    printf("ready to execute S4Enum()\n");
    S4Enum(NULL, &ulCtxListSize);

    pstS4CtxList = (PSENSE4_CONTEXT)malloc(ulCtxListSize);

    S4Enum(pstS4CtxList, &ulCtxListSize);
    printf("ready to execute S4Enum()\n");

    ulDeviceNum = ulCtxListSize/sizeof(SENSE4_CONTEXT);

    int i; 
    for(i = 0; i< ulDeviceNum; i++)
    {
        char szDeviceID[20] = {0};
        memcpy(szDeviceID, (pstS4CtxList+i)->bID, 8);

        S4Open(pstS4CtxList + i);
        printf("ready to execute S4Open()\n");

        S4Control(pstS4CtxList+i, S4_GET_SERIAL_NUMBER, NULL, 0, &pucSn, sizeof(pucSn), NULL);
        printf("ready to execute S4Control()\n");

        S4Close(pstS4CtxList+i);
        printf("ready to execute S4Close()\n");
        
    }
    return 0;
}
