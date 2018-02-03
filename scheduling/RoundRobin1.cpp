#include <iostream>
#include <iomanip>
#include <queue>
#include <unistd.h>
using namespace std;

class process
{
public:
	int at,bt,ct,tat,wt,pid,rt;
	bool visited;
	void calculateTAT()
	{
		tat=ct-at;
	}
	void calculateWT()
	{
		wt=tat-bt;
	}
};

float averageWT(process obj[], int n)
{
	float sum=0.0;
	for (int i = 0; i < n; ++i)
	{
		sum=sum+obj[i].wt;
	}
	return sum/n;
}

void printrt(process obj[], int n)
{
	cout<<"PID"<<setw(19)<<"AT"<<setw(19)<<"BT"<<setw(19)<<"RT"<<setw(20)<<"CT"<<setw(20)<<"TAT"<<setw(20)<<"WT"<<endl;
	for (int i = 0; i < n; ++i)
	{
		cout<<obj[i].pid<<setw(20)<<obj[i].at<<setw(20)<<obj[i].bt<<setw(20)<<obj[i].rt<<setw(20)<<obj[i].ct<<setw(20)<<obj[i].tat<<setw(20)<<obj[i].wt<<endl<<endl;
	}
	cout<<"Average Waiting Time: "<<averageWT(obj,n)<<endl;
}


void RoundRobin(process obj[], int n, int tq)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if (obj[i].at>obj[j].at)
			{
				int temp=obj[i].at;
				obj[i].at=obj[j].at;
				obj[j].at=temp;

				temp=obj[i].bt;
				obj[i].bt=obj[j].bt;
				obj[j].bt=temp;	

				temp=obj[i].pid;
				obj[i].pid=obj[j].pid;
				obj[j].pid=temp;

				temp=obj[i].rt;
				obj[i].rt=obj[j].rt;
				obj[j].rt=temp;
			}	
			else if (obj[i].at==obj[j].at and obj[i].pid>obj[j].pid)
			{
				int temp=obj[i].at;
				obj[i].at=obj[j].at;
				obj[j].at=temp;

				temp=obj[i].bt;
				obj[i].bt=obj[j].bt;
				obj[j].bt=temp;	

				temp=obj[i].pid;
				obj[i].pid=obj[j].pid;
				obj[j].pid=temp;

				temp=obj[i].rt;
				obj[i].rt=obj[j].rt;
				obj[j].rt=temp;
			}
		}
	}
	queue<process> ready;
	obj[0].visited=true;
	ready.push(obj[0]);
	int time=obj[0].at;
	printrt(obj,n);
	while(!ready.empty())
	{
		
		if (ready.front().rt<=tq)
		{
			time+=ready.front().rt;
			cout<<"P"<<ready.front().pid<<"(0)"<<setw(20)<<"Time Elapsed: "<<time<<endl;
			for (int i = 0; i < n; ++i)
			{
				if(obj[i].at<=time and obj[i].bt==obj[i].rt and !obj[i].visited)
				{
					obj[i].visited=true;
					ready.push(obj[i]);
					cout<<obj[i].pid<<" is pushed"<<endl;
				}
				else if(obj[i].at>time)
					break;
			}
			obj[ready.front().pid].ct=time;
			obj[ready.front().pid].rt=0;
			
			cout<<ready.front().pid<<" is popped"<<endl;
			ready.pop();
			
		}
		else
		{
			process temp;
			time+=tq;
			//cout<<"before: "<<ready.front().rt;
			ready.front().rt=ready.front().rt-tq;
			//cout<<"\nafter: "<<ready.front().rt<<endl;
			temp=ready.front();
			cout<<"P"<<ready.front().pid<<"("<<temp.rt<<")"<<setw(20)<<"Time Elapsed: "<<time<<endl;
			
			ready.pop();
			
			int count=0;
			for (int i = 0; i < n; ++i)
			{
				if(obj[i].at<=time and obj[i].bt==obj[i].rt and !obj[i].visited)
				{
					obj[i].visited=true;
					ready.push(obj[i]);
					count++;
					cout<<obj[i].pid<<" is pushed"<<endl;
				}
				else if(obj[i].at>time)
					break;
			}
			if(1)
			{
				ready.push(temp);
				cout<<temp.pid<<" is popped"<<endl;
				cout<<temp.pid<<" is pushed"<<endl;
			}
			//printrt(obj,n);
		}
		sleep(1);
	}
	for (int i = 0; i < n; ++i)
	{
		obj[i].calculateTAT();
		obj[i].calculateWT();
	}
}



using namespace std;

int  main(int argc, char const *argv[])
{
	int n,tq;
	cout<<"Enter number of processes: ";
	cin>>n;
	cout<<"Enter Time Quantum: ";
	cin>>tq;
	process obj[n];
	for(int i=0;i<n;i++)
	{
	cout<<"enter the at and bt";
	obj[i].pid=i;
	cin>>obj[i].at>>obj[i].bt;
	obj[i].rt=obj[i].bt;
	obj[i].visited=false;
	}
	RoundRobin(obj,n,tq);
	printrt(obj,n);
	return 0;
}