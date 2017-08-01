#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<fstream.h>
//#incude<bits/stdc++.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

typedef struct node
{
	struct node* left;
	char data[31];
	struct node *right;
}NODE;
typedef struct bst
{
	NODE *rt;
}BST;

void init(BST *p)
{
        p->rt=NULL;
}

void strcpy(char d[], char s[]) {
   int c = 0;

   while (s[c] != '\0') {
      d[c] = s[c];
      c++;
   }
   d[c] = '\0';
}

NODE *createnode(char* d)
{
	NODE *a=(NODE*)malloc(sizeof(NODE));
	strcpy(a->data,d);
	a->left=a->right=NULL;
	return a;
}
int strcmp(char *s1, char *s2)
{
    int i;
    for (i = 0; s1[i] && s2[i]; ++i)
    {
        /* If characters are same or inverting the 6th bit makes them same */
        if (s1[i] == s2[i] || (s1[i] ^ 32) == s2[i])
           continue;
        else
           break;
    }

    /* Compare the last (or first mismatching in case of not same) characters */
    if (s1[i] == s2[i])
        return 0;
    if ((s1[i]|32) < (s2[i]|32)) //Set the 6th bit in both, then compare
        return -1;
    return 1;
}
void preorder(NODE *p)
{
	if(p!=NULL)
	{
		printf("%s ",p->data);
		preorder(p->left);
		preorder(p->right);
	}
	else
	return;
}
int count(NODE *p)
{
	int cnt=1;
	if(p==NULL)
	return 0;
	else
	{
		cnt+=count(p->left);

		//printf("\n%s",p->data);
		cnt+=count(p->right);
		return cnt;
	}
}
void inorder(NODE *p)
{
	if(p!=NULL)
	{
		 inorder(p->left);
		 printf("%s ",p->data);
		 inorder(p->right);
	}
	return ;
}

void postorder(NODE *p)
{
	if(p!=NULL)
	{
		postorder(p->left);
		postorder(p->right);
		printf("%s ",p->data);
	}
	else
	return;
}
void createBST(BST *a)
{
	NODE *p,*q;
	int d;
	FILE *fp=fopen("dictf.txt","r");
	if(fp==NULL)
	{
		printf("\nFile Not Found!!!");
		return ;
	}
	while(!feof(fp))
	{
		char* s =(char*)malloc(31*sizeof(s));
		fscanf(fp,"%s",s);
		p=createnode(s);
		if(a->rt==NULL)
		{
			a->rt=p;
		}
		else
		{
			q=a->rt;
			while(1)
			{
				if(strcmp(s,q->data)<0)
				{
					if(q->left==NULL)
					{
						q->left=p;
						break;
					}
					else
					{
						q=q->left;
					}
				}
				else
				{
					if(q->right==NULL)
					{
						q->right=p;
						break;
					}
					else
					{
						q=q->right;
					}
				}
			}

		}
	}
	fclose(fp);
}

void suggesstion(char * ,BST *);


int search(BST * p,char sv[],NODE **curr,NODE** prnt)
{
	int flg=0;
	NODE *a=p->rt;
	*curr=*prnt=NULL;

	//printf("%s",a->data);
	while(1)
	{
		if(!strcmp(a->data,sv))
		{
			*curr=a;
			flg=1;
			break;
		}
	if(strcmp(sv,a->data)<0)
	{
		if(a->left==NULL)
		{
			*curr=*prnt=NULL;
			break;
		}
		else
		{
			*prnt=a;
			a=a->left;
		}
	}
	else
	{
		if(a->right==NULL)
		{
			*curr=*prnt=NULL;
			break;
		}
		else
		{
			*prnt=a;
			a=a->right;
		}
	}

	}
    return flg;
}

/*
int countclose(char *t, char *d)
{
	int tlength=strlen(t);
	int dlength=strlen(d);
	int count=0,flg=0,i;
	if( dlength == tlength)
	{
	//printf("\n%s %s",t,d);


	//printf("%s %s",t,d);
	printf("\nEntered countclose");
	for(i=0;i<tlength && i<dlength ;i++)
	{
		if(t[i] != d[i])
			count++;
	}
//	printf("\nCount=%d",count);
	}
	return count;
}
*/

int levenshtein(char *s1, char *s2)
{

    unsigned int x, y, s1len, s2len;



     int matrix[20][20];

    s1len = strlen(s1);

    s2len = strlen(s2);



    matrix[0][0] = 0;

    for (x = 1; x <= s2len; x++)

        matrix[x][0] = matrix[x-1][0] + 1;

    for (y = 1; y <= s1len; y++)

        matrix[0][y] = matrix[0][y-1] + 1;

    for (x = 1; x <= s2len; x++)

        for (y = 1; y <= s1len; y++)

            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));



    return(matrix[s2len][s1len]);

}






int searchclose(BST * p,char sv[],NODE **curr,NODE** prnt)
{
        int flg=0,t=0;
        NODE *a=p->rt;
        *curr=*prnt=NULL;
	while(1)
        {
	//if((a->data)[0] == sv[0])
	t=levenshtein(a->data,sv);
	if(t==0 || t==1)
        {

		*curr=a;
                flg=1;
	//	printf("\nb1");
		break;
        }
        if(strcmp(sv,a->data)<0)
        {
                if(a->left==NULL)
                {
                        *curr=*prnt=NULL;
			//printf("\nb2");
                        break;
                }
                else
                {
                        *prnt=a;
                        a=a->left;
                }
        }
        else
        {
                if(a->right==NULL)
                {
                        *curr=*prnt=NULL;
			//printf("\nb3");
                        break;
                }
                else
                {
                        *prnt=a;
                        a=a->right;
                }
        }
	}
	//printf("\nFlag=%d",flg);
	return flg;
}




void delnode(BST *p,char* data)
{
	NODE *a,*b,*c,*d;
	int flg;
	flg=search(p,data,&c,&d);
	if(flg==0)
	{
		printf("\nNode not exists!!!");
		return ;
	}
	if(d==NULL)
	{
		printf("\nInvalid Data!!!");
	}
	//Deleting the leaf node..
	if(c->left==NULL&&c->right==NULL)
	{
		if(d->left==c)
		{
			d->left=NULL;
		}
		else
		{
			d->right=NULL;
		}
	}
	if(c->left!=NULL&&c->right!=NULL)
	{
		if(d->left==c)
		{
			a=c->right;
			while(a!=NULL)
			{
				b=a;
				a=a->left;
			}
			b->left=c->left;
			d->left=c->right;
		}
		else
		{
			a=c->left;
			while(a!=NULL)
			{
				b=a;
				a=a->right;
			}
			b->right=c->right;
			d->right=c->left;
		}
	}
	//NODE to delete only one child..
	if(d->right==c)
	{
		if(c->left==NULL)
		{
			d->right=c->right;
		}
		else
		{
			d->right=c->left;
		}
	}
	if(d->left==c)
	{
		if(c->right==NULL)
		{
			d->left=c->left;
		}
		else
		{
			d->left=c->right;
		}

	}
	free(c);



}

void spellchk(BST *p)
{

	FILE *fh = fopen("abc1.txt","r");
        int flg,i,linecount=1;
	char ch,ch1;
	char s[32];
	NODE *c,*d;
	if(fh == NULL)
        {
                printf("\nFile Not Found");
                return ;
        }
        //printf("\nYES");
        while(!feof(fh))
        {
                char *s=(char *)malloc(sizeof(char)*32);

                for(i=0;(ch=fgetc(fh))!=32 && !feof(fh) ;i++)
                {
                        if(ch!='\n')
			s[i]=ch;
			if(ch == '\n')
			{
				linecount++;
				break;
			}
                }
                s[i]='\0';


		flg=search(p,s,&c,&d);

		if(flg)
		{
			printf("\n%s :Found at line :%d",s,linecount);
		}
		else
		{
			printf("\n*****************************************************");
			printf("\n%s :Not Found at line :%d",s,linecount);
			printf("\nDid you mean this:\n");
			suggesstion(s,p);
			printf("\n*****************************************************\n");
		}
		free(s);
	}


}

int depth(NODE *p)
{
	if(p==NULL)
	return 0;
	else
	{
		int ldepth=depth(p->left);
		int rdepth=depth(p->right);

		if(ldepth>rdepth)
			return (ldepth+1);
		else
			return (rdepth+1);
	}
}

void suggesstion(char *s,BST *p)
{
	int flg;
	NODE *c,*d;
	NODE *tmp1,*tmp2;
	flg=searchclose(p,s,&c,&d);
	printf("\nTop Suggestions:");
	if(flg!= 0)
	{
		//printf("\nCurrent data =%s \nParent data:%s",c->data,d->data);
		if(d==NULL)
		{
			printf("\nNot Found!");
			return ;
		}
		printf("\n%s",d->data);
		if(c!=NULL)
		{
			//tmp1=c->left;
			printf("\n%s",c->data);
		}
		if(c->right!=NULL)
		{
			tmp2=c->right;
			printf("\n%s",tmp2->data);
		}
		if(c->left!=NULL)
		{
			tmp1=c->left;
			printf("\n%s",tmp1->data);
		}
	}
	if(flg==0)
	printf("\nNo Suggesstions!!!!");
	return;
}

int menu()
{
	int opt;
	printf("\n******************BINARY SEARCH TREE MENU:****************\n1.Preorder\n2.Inorder\n3.Postorder\n4.Search word\n5.Delete Value\n6.Find depth\n7.Count Words\n8.Provide suggesstions\n9.Exit\nOption:");
	scanf("%d",&opt);
	//printf("123445");
	return opt;
}


