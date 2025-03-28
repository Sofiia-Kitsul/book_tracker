#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

// a little description:
//this code uses a hash table.
//it stores the books and its authors
//it is good to use when you want to keep track of all the books you ever read


//struct
typedef struct node
{
    char *book;
    char *author;
    struct node *next;
}
node;

//table itself
#define TABLE_SIZE 26
node *table[TABLE_SIZE];


//functions:
//1
int intro ();
//2
int control (char *newName, char *newAuthor);
//3
int hash(char *charakter);
//4
int addToTable(char *newName, char *newAuthor, int index);
//5
bool check(char *newName, char *newAuthor, int index);
//6
int loop();
//7
int freeMemory();


//main function
int main()
{
    //do as a greeting
    printf("Store the books in a hash table!\n");

    //intro function call
    intro();

    //bye
    printf("Thanks for using this book tracker!\n");
    return 0;
}

//control
int control (char *newName, char *newAuthor)
{
    
    int index = hash(newName); //gets an index for the bucket in a hash table
    addToTable(newName, newAuthor, index); //adds the book and its author to the hash table
    int continueJ = loop(); //checks whether the user wants to continue entering new books
    if (continueJ == 0) 
    {
        freeMemory();
        return 0;
    } //if user said no, then this if statement frees the memory and returns to main function
    return 0;
}

//memory free
int freeMemory()
{
    for (int i = 0; i < 26; i++)
    {
        //if the bucket at that particular index is not NULL then do teh following
        if(table[i] != NULL)
        {
            node *freeH = table[i];
            //the while loop that frees all the nodes in the hash table at the particular index
            while(freeH != NULL)
            {
                node *temp = freeH->next;
                free(freeH->book);
                free(freeH->author);
                free(freeH);
                freeH = temp;
            }
            //free the bucket itself
            table[i] = NULL;
        }
    }
    return 0;
}

//loop function loops so that user can keep entering new books
int loop()
{
    char *yesString = "Yes";
    char *noString = "No";
    char moreBooks[100]= "";
    while( strcmp(moreBooks, yesString) != 0 && strcmp(moreBooks, noString) != 0 )
    {
        printf("Do you want to add more books? (Acceptable answers: Yes/yes or No/no). ");
        fgets(moreBooks, sizeof(moreBooks), stdin);
        moreBooks[strcspn(moreBooks, "\n")] = '\0';
        if (moreBooks[0] != '\0')
        {
            moreBooks[0] = toupper(moreBooks[0]);
        }

        if (strcmp(moreBooks, yesString) == 0 || strcmp(moreBooks, noString) == 0 )
        {
            if (strcmp(moreBooks, yesString) == 0)
            {
                intro();
            }
            else
            {
                break;
            }
        }
    }
    return 0;
}

//intro fucntion asks to eneter the book name and author and then calls control function
int intro()
{
    //intro
    char newName[100];
    printf("Enter a book name : ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';

    newName[0] = toupper(newName[0]);

    char newAuthor[100];
    printf("Enter the author's name : ");
    fgets(newAuthor, sizeof(newAuthor), stdin);
    newAuthor[strcspn(newAuthor, "\n")] = '\0';
    newAuthor[0] = toupper(newAuthor[0]);
    printf("Processing...\n");

    //function where everything will be
    control(newName, newAuthor);
    return 0;
}


//function to add new books to hash table
int addToTable(char *newName, char *newAuthor, int index)
{
    //check if it is already there
    bool checkTheBook = check(newName, newAuthor, index);
    if (checkTheBook == true)
    {
        printf("Added!\n");
        return 0;
    }

    //allocate memory for new node
    node *newBook = malloc(sizeof(node));
    if (newBook == NULL) {
        printf("Memory allocation failed for new node.\n");
        return 1;
    }

    //put the book name in the new node
    newBook->book = malloc(strlen(newName) + 1);
    newBook->author = malloc(strlen(newAuthor) + 1);
    if (newBook->book == NULL || newBook->author == NULL)
    {
        printf("Memory allocation failed for book/author.\n");
        if (newBook->book != NULL)
        {
            free(newBook->book);
        }
        if (newBook->author != NULL)
        {
            free(newBook->author);
        }
        free(newBook);
        return 1;
    }

    strcpy(newBook->book, newName);
    strcpy(newBook->author, newAuthor);

    //if there is nothing starting at that letter in the table yet.
    if(table[index] == NULL)
    {
        table[index] = newBook;
        newBook->next = NULL;
        printf("Added!\n");
        return 0;
    }
    else
    {
        newBook->next = table[index];
        table[index] = newBook;
        printf("Added!\n");
        return 0;
    }
}

//check function checks whether the book is already in the hash table
bool check(char *newName, char *newAuthor, int index)
{
    if(table[index] == NULL)
    {
        return false;
    }
    else if (((strcmp(table[index]->book, newName)) == 0) && ((strcmp(table[index]->author, newAuthor) == 0)))
    {
        return true;
    }
    else
    {

        node *check = table[index]->next;
        while(check != NULL )
        {
            if (((strcmp(check->book, newName)) == 0) && ((strcmp(check->author, newAuthor) == 0)))
            {
                return true;
            }
            else
            {
                check = check->next;
            }
        }
    }
    return false;
}

//hash function-gives the number.
//it is a very simple hash fucntion!
int hash(char *book)
{
    //if books name is not composed from letters
    if (!isalpha(book[0]))
    {
        return 0;
    }
    return ((toupper(book[0])-'A'));
}
