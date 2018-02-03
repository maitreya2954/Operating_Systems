#include <iostream>
#ifndef SCHEDULE_H
#define SCHEDULE_H

class dinchakDash
{
public:
	int at,bt,ct,tat,wt,pid;
	
	void calculateTAT()
	{
		tat=ct-at;
	}
	void calculateWT()
	{
		wt=tat-bt;
	}
	
}obj[15];

void fcfs(int n);

void sort(int m, int n, int ct);

void sjf(int n);

void print();

void resetValues(int n);

#endif