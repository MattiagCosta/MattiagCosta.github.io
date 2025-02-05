#include "Dynamiclist.h"

int SetUpDynamicList(DynamicList* list, validIndex capacityIncreament){
	list->list = (void**)malloc(capacityIncreament * sizeof(void*));
	list->capacity = capacityIncreament;
	list->elements = 0;
	list->capacityIncrement = capacityIncreament;
	if(list->list==NULL){ return 1; }
	return 0;
}

void EmptyDynamicList(DynamicList* list){
	for(int i = 0; i<list->elements; i++){ free(list->list[i]); }
	list->elements = 0;
	list->capacity = list->capacityIncrement;
	list->list = (void**)realloc(list->list, list->capacity*sizeof(void*));
}

void ResetDynamiclist(DynamicList* list){
	EmptyDynamicList(list);
	free(list);
	list->list = NULL;
	list->elements = 0;
	list->capacity = 0;
}

void AddElementToDynamicList(DynamicList* list, void* garbage){
	if(list->elements>=list->capacity){
		list->capacity+=list->capacityIncrement;
		list->list = (void**)realloc(list->list, list->capacity*sizeof(void*));
	}
	list->list[list->elements] = garbage;
	list->elements++;
}

void* GetElementFromDynamicList(DynamicList* list, validIndex atIndex){
	if(atIndex>=list->elements){ return NULL; }
	void* element = list->list[atIndex];
	list->elements--;
	for(int i = atIndex; i<list->elements; i++){
		list->list[i] = list->list[i+1];
	}
	if(list->elements<list->capacity-list->capacityIncrement){
		list->capacity-=list->capacityIncrement;
		list->list = (void**)realloc(list->list, list->capacity*sizeof(void*));
	}
	return element;
}

validIndex SearchElementInDynamiclist(DynamicList* list, void* element){
	for(int i = 0; i<list->elements; i++){
		if(list->list[i]==element){ return i; }
	}
	return -1;
}

void RemoveElementFromDynamicList(DynamicList* list, validIndex atIndex){
	if(atIndex<list->elements){
		free(list->list[atIndex]);
		list->elements--;
		for(int i = atIndex; i<list->elements; i++){
			list->list[i] = list->list[i+1];
		}
		if(list->elements<list->capacity-list->capacityIncrement){
			list->capacity-=list->capacityIncrement;
			list->list = (void**)realloc(list->list, list->capacity*sizeof(void*));
		}
	}
}