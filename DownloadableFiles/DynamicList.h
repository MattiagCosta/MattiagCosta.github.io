#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <stdlib.h>

typedef unsigned long long validIndex;

typedef struct{
	void** list;
	validIndex elements, capacity;
	validIndex capacityIncrement;
} DynamicList;

int SetUpDynamicList(DynamicList* list, validIndex capacityIncreament);
void EmptyDynamicList(DynamicList* list);
void ResetDynamiclist(DynamicList* list);
void AddElementToDynamicList(DynamicList* list, void* garbage);
void* GetElementFromDynamicList(DynamicList* list, validIndex atIndex);
validIndex SearchElementInDynamiclist(DynamicList* list, void* garbage);
void RemoveElementFromDynamicList(DynamicList* list, validIndex atIndex);

#endif // DYNAMICLIST_H