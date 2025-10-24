#include<stdio.h>
int main()
{
	FILE *Sourcefile,*Destinationfile;
	char c;
	Sourcefile=fopen("C:/Users/hi/OneDrive/Desktop/OS/os1.txt","r");
	if(Sourcefile==NULL)
	{
		printf("Error opening source file");
	}
	Destinationfile=fopen("C:/Users/hi/OneDrive/Desktop/OS/os12.txt","w");
	if(Destinationfile==NULL)
	{
		printf("Error opening destination file");
		fclose(Sourcefile);
	}
	while((c=fgetc(Sourcefile))!=EOF)
	{
		fputc(c,Destinationfile);
	}
	fclose(Sourcefile);
	fclose(Destinationfile);
	printf("File Copied successfully from source to destination");
}
