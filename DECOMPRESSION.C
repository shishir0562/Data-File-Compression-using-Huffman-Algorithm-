#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
void fetch(struct list**);
void dec2bin(int,char*);
struct htree* recons_huff(struct str*,struct str*,int);
void disp(struct list*);
void pre_list(struct arr**,struct list**);
void in_list(struct arr**,struct list**);
void del(struct list**);
void getcode(struct htree*,char*,struct code*,int);
void print_code(char,char*,struct code*);
void temp_file(struct list*);
void de_compress(struct code*);
struct str* modify(struct arr*,int);
int count(struct arr*);

struct list
{
	char data;
	struct list *right;
	struct list *left;
};
struct arr
{
	char data[8];
	struct arr *link;
};
struct htree
{
	char data[8];
	struct htree *right;
	struct htree *left;
};
struct str
{
	char s[8];
};
struct code
{
	char c[100];
};
struct list *save=NULL;
struct arr *pr=NULL;
struct arr *in=NULL;
struct htree *h=NULL;
void main()
{
	struct list *l;
	struct arr *r;
	struct str *instr,*prestr;
	int c,i=-1,j=0;
	struct code codeword[256];
	char coding[150];
	clrscr();
	l=NULL;
	fetch(&l);
	disp(l);
	pre_list(&pr,&l);
	del(&save);
	in_list(&in,&save);
	c=count(in);
	del(&save);
	instr=modify(in,c);   //conversion into arrays  //changing
	prestr=modify(pr,c);
	h=recons_huff(instr,prestr,c);
	printf("\n");
	getcode(h,coding,codeword,i);
	/*disp(l);
	printf("\n");
	temp_file(l);
	//for(j=96;j<116;j++)
	//printf("%c %s\n",104,codeword[104].c);
	de_compress(codeword);*/
	getch();

}
void de_compress(struct code *codeword)
{
	FILE *temp,*dcmp;
	char *head,ch;
	int top=0,i,flag=-1;
	temp=fopen("temp2.txt","r");
	if(temp==NULL)
	{
		printf("cannot open the file");
		exit(0);
	}

	dcmp=fopen("original.txt","w");
	if(dcmp==NULL)
	{
		printf("cannot open the file");
		exit(1);
	}
	while((ch=fgetc(temp))!=EOF)
	{
		i=0;
		*(head+top)=ch;
		*(head+top+1)='\0';
		printf("%s",head);
		while(i<256)
		{
			if(strcmp(codeword[i].c,head)==0)
			{
				fputc(i,dcmp);
				top=0;
				flag=1;
				break;
			}
			else
				flag=0;
			i++;
		}
		if(flag==0)
			top++;
			printf(" ");
	}
	fclose(dcmp);
	fclose(temp);
}
void fetch(struct list **l)
{

	FILE *ft;
	struct list *temp,*r;
	char ch;
	ft=fopen("FILE.txt","r");
	if(ft==NULL)
	{
		printf("cannot open file");
		fclose(ft);
		exit(1);
	}
	while(ch!=EOF)
	{
		ch=fgetc(ft);
		temp=(struct list*)malloc(sizeof(struct list));
		if(*l==NULL)
		{

			temp->data=ch;
			temp->left=temp->right=NULL;
			*l=temp;
			r=temp;
		}
		else
		{
			temp->data=ch;
			temp->right=NULL;
			r->right=temp;
			temp->left=r;
			r=temp;
		}
	}
	r->left->right=NULL;
	free(r);

}
void temp_file(struct list *l)
{
	FILE *temp;
	struct list *r;
	char *s;
	temp=fopen("temp2.txt","w");
	r=l;
	while(r!=NULL)
	{
		if((r->data=='S')&&(r->right->data=='U')&&(r->right->right->data=='B'))
		{
			r=r->right->right->right;
			dec2bin(26,s);
			fputs(s,temp);
		}
		else
		if((r->data=='/')&&(r->right->data=='r'))
		{
			r=r->right->right;
			dec2bin(13,s);
			fputs(s,temp);

		}
		else
		{
			dec2bin(r->data,s);
			printf("%d %s\n",r->data,s);
			fputs(s,temp);
			r=r->right;
		}

	}
	fclose(temp);
}
void pre_list(struct arr **p,struct list **l)
{
	struct list *r;
	struct arr *temp,*q;
	char s[]="pre";
	int i,j=0;
	r=*l;
	i=2;
	while(r->right!=NULL)
		r=r->right;
	while(1)
	{
		if(r->data==s[i]&&r->left->data==s[i-1]&&r->left->left->data==s[i-2])
		{
			save=r->left->left;
			break;
		}
		else
			r=r->left;
	}
	r=r->right;
	while(r->right!=NULL)
	{
		temp=(struct arr*)malloc(sizeof(struct arr));
		if(*p==NULL)
		{
			j=0;
			while(r->right->data!='~')
			{
				temp->data[j]=r->right->data;
				r=r->right;
				j++;
			}
			temp->data[j]='\0';
			temp->link=NULL;
			*p=temp;
			q=temp;
		}
		else
		{
			r=r->right;
			j=0;
			do{
				temp->data[j]=r->right->data;
				j++;
				r=r->right;
			}while(r->right!=NULL&&r->right->data!='~');
			temp->data[j]='\0';
			q->link=temp;
			q=temp;
			temp->link=NULL;
		}
	}
}
void in_list(struct arr **in,struct list **save)
{
	struct arr *temp,*q;
	struct list *r;
	char s[]="in";
	int i=1,j=0;
	r=*save;
	while(1)
	{
		if(r->data==s[i]&&r->left->data==s[i-1])
		{
			*save=r->left;
			break;
		}
		else
			r=r->left;
	}
	r=r->right;
	while(r->right!=NULL)
	{
		temp=(struct arr*)malloc(sizeof(struct arr));
		if(*in==NULL)
		{
			j=0;
			while(r->right->data!='~')
			{
				temp->data[j]=r->right->data;
				j++;
				r=r->right;
			}
			temp->data[j]='\0';
			temp->link=NULL;
			*in=temp;
			q=temp;

		}
		else
		{
			r=r->right;
			j=0;
			do
			{
				temp->data[j]=r->right->data;
				j++;
				r=r->right;
			}while(r->right!=NULL&&r->right->data!='~');
			temp->data[j]='\0';
			temp->link=NULL;
			q->link=temp;
			q=temp;

		}
	}
}
struct htree* recons_huff(struct str *in,struct str *pre,int length)
{
	int i=0;
	if(length==0)
		return NULL;
	else
	{
		struct htree *node=(struct htree*)malloc(sizeof(struct htree));
		strcpy(node->data,pre->s);
		while(strcmp((in+i)->s,pre->s)!=0)
			i++;

		node->left=recons_huff(in,(pre+1),i);


		node->right=recons_huff((in+i+1),(pre+i+1),length-i-1);
		return(node);
	}
}
void getcode(struct htree *root,char *coding,struct code *codeword,int len)
{
	if(root)
	{
		if((root->left==NULL)&&(root->right==NULL))
		{
			coding[++len]='\0';
			print_code(root->data[0],coding,codeword);
		}
		if(root->left!=NULL)
		{
			coding[++len]='0';
			getcode(root->left,coding,codeword,len);
			len--;
		}
		if(root->right!=NULL)
		{
			coding[++len]='1';
			getcode(root->right,coding,codeword,len);
		}
	}
}
void print_code(char ch,char *coding,struct code *codeword)
{
	strcpy(codeword[ch].c,coding);
	printf("\n%c %s %d",ch,codeword[ch].c,ch);
}
struct str* modify(struct arr *a,int count)
{
	struct str *string;
	struct arr *r;
	int i=0;
	r=a;
	string=(struct str*)malloc(count*sizeof(struct str));
	//printf("\n");
	while(r!=NULL)
	{
		strcpy(string[i].s,r->data);
		//printf("%s ",string[i].s);
		i++;
		r=r->link;
	}
	return string;
}
int count(struct arr *p)
{
	struct arr *r;
	int i=0;
	r=p;
	while(r!=NULL)
	{
		i++;
		r=r->link;
	}
	return i;
}
void del(struct list **s)
{
	struct list *r,*temp;
	r=*s;
	*s=(*s)->left;
	while(r!=NULL)
	{
		temp=r;
		r=r->right;
		free(temp);
	}
	(*s)->right=NULL;

}
void disp(struct list *l)
{
	struct list *r;
	r=l;
	while(r!=NULL)
	{
		printf("%c",r->data);
		r=r->right;
	}
}
void dec2bin(int ch,char *s)
{
	int i=6,temp;
	//if(ch<0)
		//ch+=256;
	while(ch!=0)
	{
	temp=ch%2;
	if(temp==1)
		s[i]='1';
	else
	s[i]='0';
	ch=ch/2;
	i--;
	}
	for(temp=0;temp<=i;temp++)
		s[temp]='0';
		s[7]='\0';
}



