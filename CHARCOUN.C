#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
struct node
{
	int count;
	char data;
	struct node *link;
};
struct list
{
	int count;
	char data;
	struct list *link;
	struct list *left;
	struct list *right;
};
struct str
{
	char c;
	struct str *link;
};
struct arr
{
	struct list *add;
	struct arr *link;
};
struct code
{
	char cd[20];
};
void newlist(struct list**,struct list**,struct list**,char,int);
void min(struct arr**,struct list**,struct list**,int*);
void array(struct arr**,struct list**);
void add(struct node**,char);
void hufftree();
void print_code(struct list*,char*,int,struct code*);
void print(char*,char,struct code*);
void intermediate_file(struct code*);
void compressed_file();
void inorder(struct list**);
void preorder(struct list**);
struct list *l=NULL;
struct arr *ar=NULL;
struct list *rht=NULL;
struct list *lft=NULL;
struct list *min1=NULL;
struct list *min2=NULL;
struct str *string=NULL;
struct code codeword[256];
int sum;
void main()
{
FILE *ft;
struct node *p,*r;
char ch;
int i=0,c,len=-1;
char code[50];
clrscr();
p=NULL;

ft=fopen("ADDNODES.c","r");
if(ft==NULL)
{
	printf("cannot open the file");
	fclose(ft);
	exit(1);
}
while(1)
{
	ch=fgetc(ft);
	if(ch!=EOF)
	add(&p,ch);
	else
	break;
}
fclose(ft);
r=p;
while(r!=NULL)
{
	newlist(&l,&rht,&lft,r->data,r->count);
	r=r->link;
}

hufftree();
while(l->link!=NULL)
l=l->link;

print_code(l,code,len,codeword);
intermediate_file(codeword);
compressed_file();
inorder(&l);
preorder(&l);
getch();
}
void add(struct node **q,char c)
{
	struct node *r,*s,*t;
	int k=0;
	s=*q;
	if(*q==NULL)
	{
		r=(struct node*)malloc(sizeof(struct node));
		r->data=c;
		r->count=1;
		r->link=NULL;
		*q=r;
		return;

	}
		while(s!=NULL)
		{
			t=s;
			if(s->data==c)
			{
				(s->count)++;
				k++;
			}

			s=s->link;
		 }

		 if(k==0)
		 {
			r=(struct node*)malloc(sizeof(struct node));
			r->data=c;
			r->link=NULL;
			r->count=1;
			t->link=r;
		 }

}
void newlist(struct list **l,struct list **lft,struct list **rht,char c,int num)
{
	struct list *r,*temp;
	temp=*l;
	if(*l==NULL)
	{
		r=(struct list*)malloc(sizeof(struct list));
		r->link=NULL;
		r->count=num;
		r->left=*lft;
		r->right=*rht;
		r->data=c;
		*l=r;
		array(&ar,&r);
		return;
	}
	while(temp->link!=NULL)
		temp=temp->link;

		r=(struct list*)malloc(sizeof(struct list));
		temp->link=r;
		r->link=NULL;
		r->count=num;
		r->left=*lft;
		r->right=*rht;
		r->data=c;
		array(&ar,&r);
}

void array(struct arr **a,struct list **l)
{
	struct arr *temp,*r;
	r=*a;
	temp=(struct arr*)malloc(sizeof(struct arr));
	if(*a==NULL)
	{
		temp->link=NULL;
		temp->add=*l;
		*a=temp;
		return;

	}
	while(r->link!=NULL)
		r=r->link;

		temp->link=NULL;
		r->link=temp;
		temp->add=*l;
}
void min(struct arr **ar,struct list **min1,struct list **min2,int *sum)
{
	struct arr *i,*j,*save;
	struct list *temp;
	i=j=*ar;
	while(i!=NULL)
	{
		j=i->link;
		while(j!=NULL)
		{
			if((i->add->count)>(j->add->count))
			{
				temp=i->add;
				i->add=j->add;
				j->add=temp;
			}
			j=j->link;
		}
		i=i->link;
	}
	i=*ar;
	*min1=i->add;
	i=i->link;
	*min2=i->add;
	*sum=((*min1)->count)+((*min2)->count);
	save=*ar;
	*ar=(*ar)->link;
	free(save);
	save=*ar;
	*ar=(*ar)->link;
	free(save);
}
void hufftree()
{
	min(&ar,&min1,&min2,&sum);
	if(ar==NULL)
	{
		newlist(&l,&min1,&min2,'\0',sum);
		return;

	}
	newlist(&l,&min1,&min2,'\0',sum);
	hufftree();
}
void print_code(struct list *l,char *code,int len,struct code *codeword)
{
	if(l)
	{
		if((l->left==NULL)&&(l->right==NULL))
		{
			code[++len]='\0';
			print(code,l->data,codeword);
		}
		if(l->left!=NULL)
		{
			code[++len]='0';
			print_code(l->left,code,len,codeword);
			len--;
		}
		if(l->right!=NULL)
		{
			code[++len]='1';
			print_code(l->right,code,len,codeword);
		}
	}
}
void print(char *code,char ch,struct code *codeword)
{
	strcpy(codeword[ch].cd,code);
	printf("%c %s",ch,codeword[ch].cd);
}
void intermediate_file(struct code *codeword)
{
	FILE *temp,*ft;
	char ch;
	ft=fopen("ADDNODES.c","r");
	if(ft==NULL)
	{
		printf("cannot open file");
		fclose(ft);
		exit(1);
	}
	temp=fopen("temp.txt","w");
	if(temp==NULL)
	{
		printf("cannot open the file");
		fclose(temp);
		exit(2);
	}
	while(1)
	{
		ch=fgetc(ft);
		if(ch!=EOF)
		{
			fputs(codeword[ch].cd,temp);
		}

		else
		break;
	}
	fclose(temp);
	fclose(ft);
}
void compressed_file()
{
	FILE *temp,*cfp;
	int i=0;
	char *s,*x="/r",*sub="SUB";
	temp=fopen("temp.txt","r");
	cfp=fopen("file.txt","w");
	if(cfp==NULL)
	{
		printf("cannot open file");
		fclose(cfp);
		exit(2);
	}
	printf("shishir");
	while(fgets(s,8,temp)!=NULL)
	{
		i=bin2dec(s);
		printf("%c %d",i,i);
		switch(i){
		case 13:
			fputs(x,cfp);
			break;
		case 26:
			fputs(sub,cfp);
			break;
		default:
			fputc(i,cfp);
		}
	}

fclose(temp);
fclose(cfp);
//remove("temp.txt");
}
void inorder(struct list **l)
{
	FILE *cfp;
	struct list *r;
	int *stk[50],top=0,i,n=0,b=0;
	char *s="in",in[4],*rv;
	stk[top]=NULL;
	cfp=fopen("file.txt","a");
	if(cfp==NULL)
	{
		printf("cannot open file");
		exit(1);
	}
	fputs(s,cfp);
	r=*l;
	while(1)
	{
		while(r!=NULL)
		{
			top++;
			stk[top]=r;
			r=r->left;
		}
		r=stk[top];
		if(r==NULL)
		break;
		top--;
		if(r->data=='\0')
		{
			    i=0;
			    n=r->count;
			    while(n>0)
			    {
				b=n%10;
				n=n/10;
				in[i]=b+48;
				i++;
			    }
			    in[i]='\0';
			    rv=strrev(in);
			    fputc('~',cfp);
			    fputs(rv,cfp);
			    printf("%d",r->count);
		}
		else
		{
			fputc('~',cfp);
			fputc(r->data,cfp);
			printf("%c",r->data);
		}
		r=r->right;
	}
	fclose(cfp);
}
void preorder(struct list **l)
{
	FILE *cfp;
	struct list *r;
	int *stk[50],top=0,n=0,b=0,i;
	char *s="pre",pr[4],*rv;
	stk[top]=NULL;
	r=*l;
	cfp=fopen("file.txt","a");
	if(cfp==NULL)
	{
		printf("cannot open file");
		exit(1);
	}
	fputs(s,cfp);
	while(r!=NULL)
	{
		if(r->data=='\0')
		{
			n=r->count;
			i=0;
			while(n>0)
			{
				b=n%10;
				n=n/10;
				pr[i]=b+48;
				i++;
			}
			pr[i]='\0';
			rv=strrev(pr);
			fputc('~',cfp);
			fputs(rv,cfp);
		}
		else
		{
			fputc('~',cfp);
			fputc(r->data,cfp);
		}

		if(r->right!=NULL)
		{
			top++;
			stk[top]=r->right;
		}
		if(r->left!=NULL)
		r=r->left;
		else
		{
			r=stk[top];
			top--;
		}

	}
	fclose(cfp);
}
int bin2dec(char *s)
{
	int i=0,j,temp,dec=0;
	i=strlen(s);
	for(j=i-1;j>=0;--j)
	{
		if(s[j]=='0')
		temp=0;
		else
		temp=1;
		dec+=temp*pow(2,i-j-1);
	}
	return(dec);
}















