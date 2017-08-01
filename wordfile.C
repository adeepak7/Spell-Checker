#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int i;
	char ch;
	char s[32];
	FILE *fp,*fh;
	fh = fopen("abc1.txt","r");
	if(fh == NULL)
	{
		printf("\nFile Not Found");
		return 0;
	}
	//printf("\nYES");
	while(!feof(fh))
	{
		char *s=(char *)malloc(sizeof(char)*32);
	
		for(i=0;(ch=fgetc(fh))!=32 && !feof(fh);i++)
		{
			s[i]=ch;
		}
		s[i]='\0';
		printf("%s\n",s);
	}
	return 0;
}
