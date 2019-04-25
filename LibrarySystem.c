#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
typedef struct book
{
    int id;
    char name[100];
    int lent;
    int left;
}book;
typedef struct user
{
    int id;
    char name[30];
    int quan;
    int bkName[50];
}user;
void Register(int *,int *,book [],user []);
void Lend(int *,int *,book [],user []);
void Return(int *,int *,book [],user []);
void List(int *,int *,book [],user []);
void Add(int *,int *,book [],user []);
void Inquire(int *,int *,book [],user []);
void Search(int *,int *,book [],user []);
int main()
{
    int choice=0, bk_q=0, bow_q=0, i, j;
    FILE *bkDatPtr, *bowDatPtr;
    book booksdat[10000];
    user borrowerdat[1000];
    char info[150], *p, *hold;
    void (*option[7])(int *,int *,book [],user [])={Register, Lend, Return, List, Add, Inquire, Search};
    bkDatPtr=fopen("books.dat", "r+");
    bowDatPtr=fopen("borrower.dat", "r+");
    if (bowDatPtr==NULL)
        bowDatPtr=fopen("borrower.dat", "w+");
    while ((fgets(info,150,bkDatPtr)!=NULL)&&(strcmp(info,"\n")!=0))
    {
        for (p=info;*p!=' ';p++);
        *p='\0';
        (booksdat[bk_q]).id=atoi(info);
        for (;*p!='\n';p++);
        *p='\0';
        for (;*p!=' ';p--);
        *p='\0';
        (booksdat[bk_q]).left=atoi(p+1);
        for (;*p!=' ';p--);
        *p='\0';
        (booksdat[bk_q]).lent=atoi(p+1);
        for (p=info;*p!='\0';p++);
        strcpy((booksdat[bk_q]).name,p+1);
        bk_q++;
    }
    while (fgets(info,100,bowDatPtr)!=NULL)
    {
        for (p=info;*p!=' ';p++);
        *p='\0';
        (borrowerdat[bow_q]).id=atoi(info);
        for (;*p!='\n';p++);
        *p='\0';
        for (;*p!=' ';p--);
        *p='\0';
        (borrowerdat[bow_q]).quan=atoi(p+1);
        for (p=info;*p!='\0';p++);
        strcpy((borrowerdat[bow_q]).name,p+1);
        for (i=0;i<(borrowerdat[bow_q]).quan;i++)
        {
            fgets(info,100,bowDatPtr);
            for (p=info;*p!='\n';p++);
            *p='\0';
            for(j=0;(strcmp(booksdat[j].name,info)!=0)&&(j<bk_q);j++);
            borrowerdat[bow_q].bkName[i]=j;
        }
        fgets(info,10,bowDatPtr);
        bow_q++;
    }
    while (((printf("\nWelcome to uduck 3000 Library System\n1. Register new books\n2. Lend out books\n3. Return back books\n4. List all the books "
	                "in the library\n5. Add new borrower\n6. Inquire borrower state\n7. Search\n8. Quit\n"))&&(scanf("%d", &choice)||1))&&choice!=8)
    {
    	while (getchar() != '\n');
        if (choice<1||choice>7)
        {
            printf("No such option\n");
            continue;
        }
        (option[choice-1])(&bk_q,&bow_q,booksdat,borrowerdat);
        choice = 0;
    }
    fclose(bkDatPtr);
    fclose(bowDatPtr);
    bkDatPtr=fopen("books.dat", "w");
    bowDatPtr=fopen("borrower.dat", "w");
    for (i=0;i<bk_q;i++)
        fprintf(bkDatPtr, "%d %s %d %d\n", booksdat[i].id, booksdat[i].name, booksdat[i].lent, booksdat[i].left);
    for (i=0;i<bow_q;i++)
    {
        fprintf(bowDatPtr, "%d %s %d\n", borrowerdat[i].id, borrowerdat[i].name, borrowerdat[i].quan);
        for (j=0;j<borrowerdat[i].quan;j++)
            fprintf(bowDatPtr, "%s\n", booksdat[borrowerdat[i].bkName[j]].name);
        fprintf(bowDatPtr, "\n");
    }
    fclose(bkDatPtr);
    fclose(bowDatPtr);
    return 0;
}
void Register(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    char name[100], *p, hold[50];
    int quan, i;
    printf("Please enter the new book's name (Press \"Enter\" for return): ");
    fgets(name,100,stdin);
    if (strcmp(name,"\n")==0) return;
    for (p=name;*p!='\n';p++);
    *p='\0';
    printf("Please enter book amount (Press \"Enter\" for return): ");
    while (1)
    {
        fgets(hold,50,stdin);
        if (strcmp(hold,"\n")==0) return;
        for (p=hold;((isdigit(*p))!=0)&&(*p!='\n');p++);
        if (*p=='\n')
            break;
        printf("Book amount should be a digit!!\nPlease enter book amount again (Press \"Enter\" for return): ");
    }
    quan=atoi(hold);
    for(i=0;(strcmp(booksdat[i].name,name)!=0)&&(i<*bk_q);i++);
    if (i!=*bk_q)
        booksdat[i].left=booksdat[i].left+quan;
    else
    {
        booksdat[i].id=*bk_q+1;
        strcpy(booksdat[i].name,name);
        booksdat[i].lent=0;
        booksdat[i].left=quan;
        *bk_q=*bk_q+1;
    }
    printf("There are %d \"%s\" in the library now!!\n\nPress \"Enter\" for return to main menu.\n", booksdat[i].left, booksdat[i].name);
    while (strcmp(fgets(name,10,stdin),"\n")!=0);
}
void Lend(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    char hold[50], s[10];
    int bow, bk, x;
    printf("Borrower id (Press \"Enter\" for return): ");
    while (1)
    {
        fgets(hold,50,stdin);
        if (strcmp(hold,"\n")==0) return;
        for (bow=0; ((sprintf(s,"%d\n",borrowerdat[bow].id)>=0)&& (strcmp(hold,s)!=0))&&(bow<*bow_q);bow++);
        if (bow==*bow_q)
            printf("Sorry, no borrower belongs to this id.\nPlease enter borrower id again (Press \"Enter\" for return): ");
        else
            break;       
    }
    printf("Please enter the book id you want to borrow (Press \"Enter\" for return): ");
    while (1)
    {
        fgets(hold,50,stdin);
        if (strcmp(hold,"\n")==0) return;
        for (bk=0; ((sprintf(s,"%d\n",booksdat[bk].id)>=0)&& (strcmp(hold,s)!=0))&&(bk<*bk_q);bk++);
        if (bk==*bk_q)
            printf("There is no book with this id!!\nPlease enter again (Press \"Enter\" for return): ");
        else
            break;
    }
    if (booksdat[bk].left==0)
        printf("Sorry, the book you want to borrow is insufficient.\n");
    else
    {
        booksdat[bk].left=booksdat[bk].left-1;
        booksdat[bk].lent=booksdat[bk].lent+1;
        x=borrowerdat[bow].quan;
        borrowerdat[bow].quan=borrowerdat[bow].quan+1;
        (borrowerdat[bow]).bkName[x]=bk;
        printf("%s borrows \"%s\" successfully!!\n", borrowerdat[bow].name, booksdat[bk].name);
    }
    printf("\nPress \"Enter\" for return to main menu.\n");
    while (strcmp(fgets(s,10,stdin),"\n")!=0);
}
void Return(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    char id[30], name[100], *p, s[5];
    int i, j, bow, bk;
    printf("Borrower id (Press \"Enter\" for return): ");
    while (1)
    {
        fgets(id,30,stdin);
        if (strcmp(id,"\n")==0) return;
        for (i=0;(i<*bow_q)&&(sprintf(s,"%d\n", borrowerdat[i].id)>=0)&&(strcmp(s,id)!=0);i++);
        if (i==*bow_q)
            printf("Sorry, no borrower belongs to this id.\nPlease enter borrower id again (Press \"Enter\" for return): ");
        else
        {
            bow=i;
            printf("Please enter the book's name (Press \"Enter\" for return): ");
            fgets(name,100,stdin);
            if (strcmp(name,"\n")==0) return;
            for (p=name;*p!='\n';p++);
            *p='\0';
            for (i=0;(strcmp(name,booksdat[borrowerdat[bow].bkName[i]].name)!=0)&&(i<borrowerdat[bow].quan);i++);
            if (i==borrowerdat[bow].quan)
            {
                printf("%s has not borrowed \"%s\"!!\n", borrowerdat[bow].name, name);
                break;
            }
            for (i=0;(strcmp(name,booksdat[i].name)!=0)&&(i<*bk_q);i++);
            if (i==*bk_q)
            {
                printf("\"%s\" does not belong to this library!!\n", name);
                break;
            }
            else
            {
                bk=i;
                booksdat[bk].left=booksdat[bk].left+1;
                booksdat[bk].lent=booksdat[bk].lent-1;
                borrowerdat[bow].quan=borrowerdat[bow].quan-1;
                for (i=0;(i<=borrowerdat[bow].quan)&&(borrowerdat[bow].bkName[i]!=bk);i++);
                for (j=i;j<borrowerdat[bow].quan;j++)
                    borrowerdat[bow].bkName[j]=borrowerdat[bow].bkName[j+1];
                printf("%s has returned \"%s\" to the library!!\n", borrowerdat[bow].name, booksdat[bk].name);
                break;
            }
        }
    }
    printf("\nPress \"Enter\" for return to main menu.\n");
    while (strcmp(fgets(s,10,stdin),"\n")!=0);
}
void List(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    int num=25, i=0, start=0;
    char s[5];
    printf("Rows per page: ");
    scanf("%d", &num);
    while (1)
    {
        printf("\n%-5s%-50s%10s%10s\n", "Id", "Name", "Lend Out", "Remaining");
        for (;(i<start+num)&&(i<*bk_q);i++)
            printf("%-5d%-50s%10d%10d\n", booksdat[i].id, booksdat[i].name, booksdat[i].lent, booksdat[i].left);
        printf("\n\"1\" to view previous page, \"2\" to view next page\nPress \"Enter\" for return\n");
        getchar();
        if (scanf("%[^\n]", s)==0)
            break;
        else if (atoi(s)==1)
            i=start-num;
        else if (atoi(s)==2)
            i=start+num;
        else
        	i=start;
        if (i<0||i>=*bk_q)
        	i=start;
        start=i;
    }
}
void Add(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    int i;
    char name[30], *p, s[10];
    printf("Please enter the new borrower's name (Press \"Enter\" for return): ");
    while (1)
    {
        fgets(name,30,stdin);
        if (strcmp(name,"\n")==0) return;
        for (p=name;*p!='\n';p++);
        *p='\0';
        for (i=0;(strcmp(borrowerdat[i].name,name)!=0)&&(i<*bow_q);i++);
        if (i==*bow_q)
            break;
        else
            printf("Sorry, %s has been registered.\nPlease type again (Press \"Enter\" for return): ", borrowerdat[i].name);
    }
    strcpy(borrowerdat[*bow_q].name,name);
    borrowerdat[*bow_q].quan=0;
    borrowerdat[*bow_q].id=*bow_q+1;
    printf("Welcome %s!!\nYour id is %d\n", name, borrowerdat[*bow_q].id);
    *bow_q=*bow_q+1;
    printf("\nPress \"Enter\" for return to main menu.\n");
    while (strcmp(fgets(s,10,stdin),"\n")!=0);
}
void Inquire(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    int i, j;
    char naid[30], s[5], *p;
    printf("Please enter the user borrower name or id (Press \"Enter\" for return):");
    while (1)
    {
        fgets(naid,30,stdin);
        if (strcmp(naid,"\n")==0) break;
        for (i=0;(i<*bow_q)&&(sprintf(s,"%d\n", borrowerdat[i].id)>=0)&&(strcmp(s,naid)!=0)&&(sprintf(s,"%s\n", borrowerdat[i].name)>=0)&&(strcmp(s,naid)!=0);i++);
        if (i==*bow_q)
        {
            for (p=naid;*p!='\n';p++);
            *p='\0';
            printf("Sorry, no one names %s or owns this id in this system.\nPlease type again (Press \"Enter\" for return): ", naid);
        }
        else
        {
            printf("%d %s borrows %d books\n", borrowerdat[i].id, borrowerdat[i].name, borrowerdat[i].quan);
            for (j=0;j<borrowerdat[i].quan;j++)
                printf("%s\n", booksdat[borrowerdat[i].bkName[j]].name);
            printf("\nPress \"Enter\" for return.\n");
            while (strcmp(fgets(s,10,stdin),"\n")!=0);
            break;
        }
    }
}
void Search(int *bk_q ,int *bow_q ,book booksdat[],user borrowerdat[])
{
    char s[50], s1[5], *p;
    int i, x=0, count, start, match[10000];
    printf("Please enter the search keyword (Press \"Enter\" for return): ");
    fgets(s,50,stdin);
    if (strcmp(s,"\n")==0) return;
    for (p=s;*p!='\n';p++);
    *p='\0';
    for (i=0;i<*bk_q;i++)
    {
        if (strstr(booksdat[i].name,s)!=NULL)
        {
            match[x]=i;
            x++;
        }
    }
    if (x!=0)
    {
        i=0;
        start=0;
        printf("There are %d book(s) match \"%s\"\n", x, s); 
        while (1)
        {  
            printf("\n%-5s%-50s%10s%10s\n", "Id", "Name", "Lend Out", "Remaining");
            for (;(i<x)&&(i<start+10);i++)
                printf("%-5d%-50s%10d%10d\n", booksdat[match[i]].id, booksdat[match[i]].name, booksdat[match[i]].lent, booksdat[match[i]].left);
            printf("\n\"1\" to view previous page, \"2\" to view next page\nPress \"Enter\" for return\n");
            if (scanf("%[^\n]", s1)==0)
                break;
            else if (atoi(s1)==1)
                i=start-10;
            else if (atoi(s1)==2)
                i=start+10;
            else
            	i=start;
            if (i<0||i>=x)
        		i=start;
            start=i;
            getchar();
        }
    }
    else
    {
        printf("No book matches the pattern \"%s\"\n\nPress \"Enter\" for return.\n", s);
        getchar();
        while (strcmp(fgets(s,10,stdin),"\n")!=0);
    }
}
