#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char writername[30];
	char bookname[30];
	int price;
	int statu;
} Book;
int menu()
{
	int choice,i;
	do
	{
		printf("---------------MENU---------------\n");
	printf("To list availible books:1\n");
	printf("To list all book which belongs to author you choosed:2\n");
	printf("To list rented books:3\n");
	printf("To record a book:4\n");
	printf("To delete a book:5\n");
	printf("To see total number of books:6\n");
	printf("To update price of a book:7\n");
	printf("To rent a book:8\n");
	printf("To exit:0\n");
	i=scanf("%d",&choice);
	}while(i==0);
	return choice;
}
void sortcheaptoexp(char*fname)
{
	FILE *fp;
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		return;
	}
	Book *book;
	int i,j,k;
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Book);
	fseek(fp,0,SEEK_SET);
	book=(Book*)malloc(k*sizeof(Book));
		if(book==NULL)
	{
		printf("memory couldnt seperated!\n");
		fclose(fp);
		return;
	}
	fread(book,sizeof(Book),k,fp);
	for(i=0;i<k;i++)
	{
		for(j=i+1;j<k;j++)
		{
			if(book[i].price>book[j].price)
			{
				Book temp=book[i];
				book[i]=book[j];
				book[j]=temp;
			}
		}
	}
	fseek(fp,0,SEEK_SET);
	fwrite(book,sizeof(Book),k,fp);
	free(book);
	fclose(fp);
	
}
void sortexptocheap(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		return;
	}
	Book *book;
	int i,j,k;
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Book);
	fseek(fp,0,SEEK_SET);
	book=(Book*)malloc(k*sizeof(Book));
	if(book==NULL)
	{
		printf("memory allocation error\n");
		fclose(fp);
		return;
	}
	fread(book,sizeof(Book),k,fp);
	for(i=0;i<k;i++)
	{
		for(j=i;j<k;j++)
		{
			if(book[i].price<book[j].price)
			{
				Book temp= book[i];
				book[i]=book[j];
				book[j]=temp;
			}
		}
	}
	fseek(fp,0,SEEK_SET);
	fwrite(book,sizeof(Book),k,fp);
	free(book);
	fclose(fp);
}
void sortalphabetically(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"rb+");
	if(fp==NULL)
	{
		return;
	}
	Book *book,b;
	int i,j,k;
	long size;
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	k=size/sizeof(Book);
	fseek(fp,0,SEEK_SET);
	book=(Book*)malloc(k*sizeof(Book));
	if(book==NULL)
	{
		printf("memory couldnt seperated!\n");
		fclose(fp);
		return;
	}
	fread(book,sizeof(Book),k,fp); 
	
	for (int i = 0; i <k; i++) {
        book[i].bookname[strcspn(book[i].bookname, "\n")] = '\0';
    }
    
	for(i=0;i<k;i++)
	{
		for(j=i+1;j<k;j++)
		{

				if(strcmp(book[i].bookname,book[j].bookname)>0)
				{
					 Book temp = book[i];
                book[i] = book[j];
                book[j] = temp;
					break;				
				}

			
		}
	} 
	fseek(fp, 0, SEEK_SET);
	fwrite(book,sizeof(Book),k,fp);
	free(book);
	fclose(fp);
	
}
void recordbook(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"ab");
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;
	}
	Book book;
	printf("Enter the writer name:\n");
	getchar();
	fgets(book.writername,30,stdin);
	book.writername[strcspn(book.writername, "\n")] = 0;
	printf("Enter the book name:\n");
	fgets(book.bookname,30,stdin);
	book.bookname[strcspn(book.bookname, "\n")] = 0;
	printf("Enter the price:\n");
	scanf("%d",&book.price);
	printf("Enter the statu(availible 1 else 0):\n");
	scanf("%d",&book.statu);
	fwrite(&book,sizeof(Book),1,fp);
	fclose(fp);
}
void listavailiblebooks(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"rb");
	int d;
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;
	}
	printf("\n\nTo list the books alphabetically:1\n\nTo list the books according to price(cheap to expensive):2\n\n\To list the books according to price(expensive to cheap):3\n\n");
	scanf("%d",&d);
	if(d==1)
	sortalphabetically(fname);
	else if(d==2)
	sortcheaptoexp(fname);
	else if(d==3)
	sortexptocheap(fname);
	else 
	{
		printf("invalid choice!!");
		
	}
	Book book;	
	printf("\n\n----------------------------------\n\n");
	while(fread(&book,sizeof(Book),1,fp)==1)	
	{
		if(book.statu==1)
		printf("\n\n%s\n%s\n%d\n\n\n",book.bookname,book.writername,book.price);
	}
	printf("\n\n----------------------------------\n\n");
	fclose(fp);
}
void listrentedbooks(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;
	}
	int d;
	printf("\n\nTo list the books alphabetically:1\n\nTo the books list according to price(cheap to expensive):2\n\n\To list the books according to price(expensive to cheap):3\n\n");
	scanf("%d",&d);
	if(d==1)
	sortalphabetically(fname);
	else if(d==2)
	sortcheaptoexp(fname);
	else if(d==3)
	sortexptocheap(fname);
	Book book;
	printf("\n\n----------------------------------\n\n");
	while(fread(&book,sizeof(Book),1,fp)==1)
	{
		if(book.statu==0)
		printf("\n\n%s\n%s\n%d$\n\n\n",book.bookname,book.writername,book.price);
	}
	printf("\n\n----------------------------------\n\n");
	fclose(fp);
}
void listauthorbooks(char *fname)
{
	FILE *fp;
	int d;
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;		
	}
	printf("\n\nTo list the books alphabetically:1\n\nTo list the books according to price(cheap to expensive):2\n\n\To list the books according to price(expensive to cheap):3\n\n");
	scanf("%d",&d);
	if(d==1)
	sortalphabetically(fname);
	else if(d==2)
	sortcheaptoexp(fname);
	else if(d==3)
	sortexptocheap(fname);
	Book book;
	char str[30];
	printf("Enter the author name:\n");
	getchar();
	fgets(str,30,stdin);
	str[strcspn(str, "\n")] = 0;
	printf("\n\n----------------------------------\n\n");
	while(fread(&book,sizeof(Book),1,fp)==1)
	{
		if(strcmp(book.writername,str)==0)
		{
			printf("\n\n%s\n%s\n%d$\n\n\n",book.writername,book.bookname,book.price);
		}
		
	}	
	printf("\n\n----------------------------------\n\n");
	fclose(fp);
	
}
void deletebook(char *fname)
{
	FILE *fp;
	Book *book;
	int k,i;
	char deletedbook[30];
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;
	}
	printf("Enter the book name you want to delete:\n");
	getchar();
	fgets(deletedbook,30,stdin);
	deletedbook[strcspn(deletedbook,"\n")]=0;
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Book);
	if(k==0)
	{
		printf("There is no car in the file!\n");
		fclose(fp);
		return;
	}
	fseek(fp,0,SEEK_SET);
	book=(Book*)malloc(k*sizeof(Book));
	if(book==NULL)
	{
		printf("Not enough memory!\n");
		fclose(fp);
		return;
	}
	fread(book,sizeof(Book),k,fp);
	fclose(fp);
	fp=fopen(fname,"wb");
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;
	}
	for(i=0;i<k;i++)
	{
		if(strcmp(book[i].bookname,deletedbook)!=0)
		{
			fwrite(&book[i],sizeof(Book),1,fp);
		}
		
	}
	printf("The book is deleted\n");
	fclose(fp);
}
void numberofbooks(char *fname)
{
	FILE *fp;
	int k;
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		printf("file opening error!");
		return;
	}
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Book);
	printf("Total number of books:%d\n",k);
	fclose(fp);
	
}
void updateprice(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"r+b");
	Book book;
	char str[30];
	int k,newprice,i;
	if(fp==NULL)
	{
		printf("file opening error!\n");
		return;
	}
	
	printf("Enter the name of the book:\n");
	getchar();
	fgets(str,30,stdin);
	str[strcspn(str,"\n")]=0;
	
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Book);
	fseek(fp,0,SEEK_SET);  
	
	for(i=0;i<k;i++)
	{
		fread(&book,sizeof(Book),1,fp);
		if(strcmp(str,book.bookname)==0)
		{
		printf("Enter new name price of the book:\n");
		scanf("%d",&newprice);
		book.price=newprice;
		fseek(fp,-sizeof(Book),SEEK_CUR);
		fwrite(&book,sizeof(Book),1,fp);
		printf("The price of book is updated\n");
		break;
		}
	}
	fclose(fp);
	
}
void rentbook(char *fname)
{
	FILE *fp;
	char name[30];
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
	printf("file opening error!\n");		
	return;
	}
	Book book;
	
	printf("Enter the name of the book:\n");
	getchar();
	fgets(name,30,stdin);
	name[strcspn(name,"\n")]=0;
	
	while(fread(&book,sizeof(Book),1,fp)==1)
	{
		if(strcmp(name,book.bookname)==0)
		{
			book.statu=0;
			fseek(fp,-sizeof(Book),SEEK_CUR);
			fwrite(&book,sizeof(Book),1,fp);
			printf("The book is rented\n");
			break;
		}
	}
	fclose(fp);
}

int main()
{
	int choice;
	char *fname="book.bin";
	
	do 
	{
	choice=menu();
	switch(choice)
	{
		case 1:
			listavailiblebooks(fname);
		    break;
		case 2:
			listauthorbooks(fname);
			break;
		case 3:
			listrentedbooks(fname);
			break;
	    case 4:
	    	recordbook(fname);
	    	break;
	    case 5:
	    	deletebook(fname);
	    	break;
	    case 6:
	    	numberofbooks(fname);
	    	break;
	    case 7:
	    	updateprice(fname);
	    	break;
	    case 8:
	    	rentbook(fname);
	    	break;		 
	    case 0:
	    	exit(0);
	    default:
	    	printf("invalid choice!");
			
	}
} while(choice!=0);

}
