#include "LapseCounter.h"

void StartLapseCounter(LapseCounter* lapseCounter, ULONGLONG lapse){
	GetSystemTimeAsFileTime(&(lapseCounter->lft));
	lapseCounter->lt.LowPart = lapseCounter->lft.dwLowDateTime;
	lapseCounter->lt.HighPart = lapseCounter->lft.dwHighDateTime;

	lapseCounter->thisLapseData.count = 0;
	lapseCounter->thisLapseData.timer = 0;
	lapseCounter->lapse = lapse;

	lapseCounter->thisLapseData.count = 0;
	lapseCounter->thisLapseData.timer = 0;
}

int CallLapseCounter(LapseCounter* lapseCounter){
	GetSystemTimeAsFileTime(&(lapseCounter->ft));

	lapseCounter->t.LowPart = lapseCounter->ft.dwLowDateTime;
	lapseCounter->t.HighPart = lapseCounter->ft.dwHighDateTime;
	lapseCounter->thisLapseData.timer = lapseCounter->t.QuadPart-lapseCounter->lt.QuadPart;

	lapseCounter->thisLapseData.count++;

	if(lapseCounter->thisLapseData.timer>lapseCounter->lapse){
		lapseCounter->previousLapseData.timer = lapseCounter->thisLapseData.timer;
		lapseCounter->previousLapseData.count = lapseCounter->thisLapseData.count;
		lapseCounter->thisLapseData.count = 0;
		lapseCounter->lt.QuadPart = lapseCounter->t.QuadPart;
		return 1;
	}

	return 0;
}