#include<stdio.h>
#include<stdlib.h>
#include"DSFINALP.h"
int main()
{
	int flg=0,opt,r,bopt;
	char str[20];
	BST p;
	char ch;
	NODE *c,*d;
	FILE *fp;
	init(&p);
	while(1)
	{
		printf("\n*****************SPELL CHECKER MENU*******************\n1.VIEW FILE\n2.LOAD DICTIONARY\n3.BINARY TREE MENU\n4.CHECK FILE\n5.EXIT\nOPTION:");
		scanf("%d",&bopt);
		if(bopt<1||bopt>4)
		break;
	switch(bopt)
	{
		case 1:

					printf("\nTest file name: DS Spell checker\nYour data: \n");
					fp=fopen("abc1.txt","r");
					if(fp == NULL)
					{
						printf("\nTest file not found!!!!!");
						return 0;
					}
					while(!feof(fp))
					{
						ch=fgetc(fp);
						printf("%c",ch);
					}
					fclose(fp);
					break;

		case 2:
					createBST(&p);
                        		flg=1;
                                        break;
                                        default:
                                        if(flg==0)
                                        {
                                                printf("\nInvalid Operation!!!Please load The Dictionary");
                                                continue;
                                        }

		switch(bopt)
		{
		case 3:
			while(1)
			{
				opt=menu();
				if(opt>=9)
				{
					break;
				}
				switch(opt)
				{
					case 1:
						printf("\nPreorder:");
						preorder(p.rt);
						break;
					case 2:
						printf("\nInorder:");
						inorder(p.rt);
						break;
					case 3:
						printf("\nPostorder:");
						postorder(p.rt);
						break;
					case 4:
						printf("\nEnter Search Word:");
						scanf("%s",str);
						r=search(&p,str,&c,&d);
						if(r)
						printf("\nFound");
						else
						printf("\nNot Found");
						break;
					case 5:
						printf("\nEnter Data :");
						scanf("%s",str);
						delnode(&p,str);
						break;
					case 6:
						printf("\nMaximum Depth:%d",depth(p.rt));
						break;
					case 7:
						printf("Word Count=%d",count(p.rt));
						break;
					case 8:
						printf("\nEnter string:");
						scanf("%s",str);
						suggesstion(str,&p);
						break;
				}
			}
			break;
		case 4:
			spellchk(&p);
			break;

	}
		}
	}

	return 0;

}
