#include<stdio.h>
int main(){
	int bt[20],p[20],wt[20],tat[20],i,j,n,total=0,pos,temp;
	float avg_wt,avg_tat;
	printf("enter number of processes:");
	scanf("%d\n",&n);
	printf("\n enter burst time:");
	for(i=0;i<n;i++){
		printf("P%d\n:",i+1);
		scanf("%d",&bt[i]);
		p[i]=i+1;
	}
	for(i=0;i<n;i++){
		pos=i;
		for(j=i+1;j<n;j++){
			if(bt[j]<bt[pos])
			pos=j;
		}
		temp=bt[i];
		bt[i]=bt[pos];
		bt[pos]=temp;
		
		
		temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
	}
	wt[0]=0;
	for(i=1;i<n;i++){
		wt[i]=0;
		for(j=0;j<i;j++)
		wt[i]+=bt[j];
		total+=wt[i];
	}
	avg_wt=total/n;
	total=0;
	printf("process   bursttime   waiting timeturn aroundtime\n");
	for(i=0;i<n;i++){
		tat[i]=bt[i]+wt[i];
		total+=tat[i];
		printf("p%d          %d           %d       %d\n",p[i],bt[i],wt[i],tat[i]);
	}
	avg_tat=total/n;
	printf("average waiting time=%f\n",avg_wt);
	printf("average turnaround time=%f",avg_tat);
}
