#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE*fptr1,*fptr2;
	char filename[100],c;
	printf("enter the file name to open for reading\n");
	scanf("%s",filename);
	fptr1=fopen(filename,"r");
	if(fptr1==NULL){
		printf("cannot open file%s\n",filename);
		exit(0);
	}
	printf("enter the file name to open for writing\n");
	scanf("%s",filename);
	fptr2=fopen(filename,"w");
	if(fptr2==NULL){
		printf("cannot open file %s\n",filename);
		exit(0);
	}
	c=fgetc(fptr1);
	while(c!=EOF){
		fputc(c,fptr2);
		c=fgetc(fptr1);
	}
	printf("\n contents copied to %s",filename);
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}
