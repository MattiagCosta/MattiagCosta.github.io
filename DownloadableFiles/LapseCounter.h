#ifndef LAPSESCOUNTER_H
#define LAPSESCOUNTER_H

#include <windows.h>

typedef struct{
	ULONGLONG count, timer;
} LapseData;

typedef struct{
	FILETIME lft, ft; // 100-nanonesconds intervals; 10000 100-nanoseconds intervals = 1 millisecond
	ULARGE_INTEGER lt, t;
	// what user need
	ULONGLONG lapse;
	LapseData thisLapseData, previousLapseData;
} LapseCounter;

#define LAPSE_ISTANT 0
#define LAPSE_MICROSECOD 10
#define LAPSE_MILLISECOND 10000
#define LAPSE_SECOND 10000000
#define LAPSE_MINUTE 600000000

void StartLapseCounter(LapseCounter* lapseCounter, ULONGLONG lapse);
int CallLapseCounter(LapseCounter* lapseCounter);

#endif // LAPSESCOUNTER_H