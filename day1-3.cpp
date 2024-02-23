#include<stdio.h>
int main(){
	int a[100][4];
	int i,j,n,total=0,index,temp;
	float avg_wt,avg_tat;
	printf("enter number of processes:");
	scanf("%d",&n);
	printf("enter burst time:\n");
	for(i=0;i<n;i++){
		printf("P%d:",i+1);
		scanf("%d",&a[i][1]);
		a[i][0]=i+1;
	}
	for(i=0;i<n;i++){
		index=i;
		for(j=i+1;j<n;j++){
			if(a[j][1]<a[index][1])
			index=j;
			temp=a[i][1];
			a[i][1]=a[index][1];
			a[index][1]=temp;
			
			temp=a[i][0];
			a[i][0]=a[index][0];
			a[index][0]=temp;
		}
		a[0][2]=0;
		for(i=1;i<n;i++){
			a[i][2]=0;
			for(j=0;j<i;j++)
			a[i][2]+=a[j][1];
			total+=a[i][2];
		}
		avg_wt=total/n;
		total=0;
		printf("P    BT    WT   TAT\n");
		for(i=0;i<n;i++){
			a[i][3]=a[i][1]+a[i][2];
			total+=a[i][3];
			printf("P%d    %d     %d     %d\n",a[i][0],a[i][1],a[i][2],a[i][3]);
			}
	
		avg_tat=total/n;
		printf("avearge waiting time=%f",avg_wt);
		printf("\naverage turn around time=%f",avg_tat);
	}
}
