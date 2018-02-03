#include <iostream>
#ifndef SCHEDULE_H
#define SCHEDULE_H


class process
{
public:
	int at,bt,ct,tat,wt,pid,rt;
	int priority;
	bool visited, completed;
	
	void calculateTAT()
	{
		tat=ct-at;
	}
	void calculateWT()
	{
		wt=tat-bt;
	}
	int findRR(int c)
	{
		return (((c-at)+bt)/bt);
	}
	
};

void fcfs(process obj[],int n);

void sort(process obj[], int m, int n, int ct);

void sjf(process obj[],int n);

void srt(process obj[], int n);

void priority_np(process obj[], int n);

void priority_p(process obj[], int n);

void print(process obj[], int n);

void printrt(process obj[], int n);

void printpriority(process obj[], int n);

void RoundRobin(process obj[], int n);

void refresh(process obj1[], process obj2[], int n);

void priority_pre(process obj[], int n);

#endif