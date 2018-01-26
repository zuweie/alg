#ifndef _ENTITY_H_
#define _ENTITY_H_

// 对所有数据的一种抽象。
typedef union _UValue {
        int ivalue;
        long lvalue;
        short svalue;
        char  cvalue;
        float fvalue;
        double dvalue;
        unsigned int uivalue;
        unsigned long ulvalue;
        unsigned short usvalue;
        unsigned char  ucvalue;
        char* pcvalue;
        void* pvalue;
} Uvalue;

typedef struct _Entity {
    Uvalue _data; 
    int (*compare) (const void* thiz, const void* other);
    int (*cleanup) (struct _Entity* e);

} Entity;

#endif

