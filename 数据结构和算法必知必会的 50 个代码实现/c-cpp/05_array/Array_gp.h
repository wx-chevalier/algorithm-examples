#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct Array
{
    // pָ��Ŀռ��С
    size_t size;
    // pָ���Ѿ�ʹ�õĿռ��С
    size_t len;
    // �������͵Ĵ�С
    size_t typeSize;
    // ֵ���ƺ���
    void(*dup)(void *ptr, void *key);
    // ֵ�ͷź���
    void(*free)(void *ptr);
    // ֵ�ȽϺ���
    int(*match)(void *ptr, void *key);
    // ������ݵ�ָ��
    void   *p;
}Array;

#define arraySetDupMethod(a, m) ((a)->dup = (m))
#define arraySetFreeMethod(a, m) ((a)->free = (m))
#define arraySetMatchMethod(a, m) ((a)->match = (m))

#define arrayGetDupMethod(a) ((a)->dup)
#define arrayGetFree(a) ((a)->free)
#define arrayGetMatchMethod(a) ((a)->match)

Array* arrayCreate();
void arrayInit(Array *array, int size, int typeSize);

int arrayInsert(Array *array, size_t pos, void *const value);
size_t arraySearchValue(Array *array, void* const value);
void* arrayIndex(Array *array, size_t index);
int arrayModify(Array *array, size_t pos, void *const value);

size_t arrayLen(Array *array);
size_t arraySize(Array *array);

void arrayEmpty(Array *array);
void arrayDelValue(Array *array, void *value);
void arrayDelIndex(Array *array, size_t pos);

#endif // !__ARRAY_H__