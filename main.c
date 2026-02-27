#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct Book
{
    int code;
    char name[100];
    char author[100];
    int pages;
    int price;
    int copies;
};

struct Book library[MAX];
int count = 0;

// Function Declarations
void login();
void loadFromFile();
void saveToFile();
void addBook();
void displayBooks();
void searchBook();
void updateBook();
void deleteBook();
void issueBook();
void returnBook();

int main()
{
    int choice;

    login();           // Admin login
    loadFromFile();    // Load existing data

    while (1)
    {
        printf("\n====================================\n");
        printf("   ADVANCED LIBRARY MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("6. Issue Book\n");
        printf("7. Return Book\n");
        printf("8. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchBook(); break;
        case 4: updateBook(); break;
        case 5: deleteBook(); break;
        case 6: issueBook(); break;
        case 7: returnBook(); break;
        case 8:
            saveToFile();
            printf("Data Saved Successfully!\n");
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

// ================= LOGIN =================
void login()
{
    char username[50], password[50];

    printf("Admin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") != 0 || strcmp(password, "1234") != 0)
    {
        printf("Invalid Login! Exiting...\n");
        exit(0);
    }

    printf("Login Successful!\n");
}

// ================= LOAD FROM FILE =================
void loadFromFile()
{
    FILE *fp = fopen("library.txt", "r");

    if (fp == NULL)
        return;

    while (fscanf(fp, "%d %s %s %d %d %d",
                  &library[count].code,
                  library[count].name,
                  library[count].author,
                  &library[count].pages,
                  &library[count].price,
                  &library[count].copies) != EOF)
    {
        count++;
    }

    fclose(fp);
}

// ================= SAVE TO FILE =================
void saveToFile()
{
    FILE *fp = fopen("library.txt", "w");
int i;
    for ( i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %s %d %d %d\n",
                library[i].code,
                library[i].name,
                library[i].author,
                library[i].pages,
                library[i].price,
                library[i].copies);
    }

    fclose(fp);
}

// ================= ADD BOOK =================
void addBook()
{
    if (count >= MAX)
    {
        printf("Library Full!\n");
        return;
    }

    printf("Enter Code: ");
    scanf("%d", &library[count].code);

    printf("Enter Name: ");
    scanf("%s", library[count].name);

    printf("Enter Author: ");
    scanf("%s", library[count].author);

    printf("Enter Pages: ");
    scanf("%d", &library[count].pages);

    printf("Enter Price: ");
    scanf("%d", &library[count].price);

    printf("Enter Copies: ");
    scanf("%d", &library[count].copies);

    count++;

    printf("Book Added Successfully!\n");
}

// ================= DISPLAY BOOKS =================
void displayBooks()
{
    if (count == 0)
    {
        printf("No Books Available!\n");
        return;
    }
int i;
    for ( i = 0; i < count; i++)
    {
        printf("\n----------------------------\n");
        printf("Code: %d\n", library[i].code);
        printf("Name: %s\n", library[i].name);
        printf("Author: %s\n", library[i].author);
        printf("Pages: %d\n", library[i].pages);
        printf("Price: %d\n", library[i].price);
        printf("Copies: %d\n", library[i].copies);
    }
}

// ================= SEARCH BOOK =================
void searchBook()
{
    int code, found = 0;

    printf("Enter Code to Search: ");
    scanf("%d", &code);
int i;
    for ( i = 0; i < count; i++)
    {
        if (library[i].code == code)
        {
            printf("Book Found: %s by %s\n",
                   library[i].name,
                   library[i].author);
            printf("Copies Available: %d\n", library[i].copies);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book Not Found!\n");
}

// ================= UPDATE BOOK =================
void updateBook()
{
    int code;

    printf("Enter Code to Update: ");
    scanf("%d", &code);
int i;
    for ( i = 0; i < count; i++)
    {
        if (library[i].code == code)
        {
            printf("Enter New Price: ");
            scanf("%d", &library[i].price);

            printf("Enter New Copies: ");
            scanf("%d", &library[i].copies);

            printf("Book Updated Successfully!\n");
            return;
        }
    }

    printf("Book Not Found!\n");
}

// ================= DELETE BOOK =================
void deleteBook()
{
    int code;

    printf("Enter Code to Delete: ");
    scanf("%d", &code);
int i,j;
    for ( i = 0; i < count; i++)
    {
        if (library[i].code == code)
        {
            for ( j = i; j < count - 1; j++)
            {
                library[j] = library[j + 1];
            }
            count--;

            printf("Book Deleted Successfully!\n");
            return;
        }
    }

    printf("Book Not Found!\n");
}

// ================= ISSUE BOOK =================
void issueBook()
{
    int code;

    printf("Enter Code to Issue: ");
    scanf("%d", &code);
int i;
    for (int i = 0; i < count; i++)
    {
        if (library[i].code == code)
        {
            if (library[i].copies > 0)
            {
                library[i].copies--;
                printf("Book Issued Successfully!\n");
            }
            else
            {
                printf("No Copies Available!\n");
            }
            return;
        }
    }

    printf("Book Not Found!\n");
}

// ================= RETURN BOOK =================
void returnBook()
{
   int i;
    int code;

    printf("Enter Code to Return: ");
    scanf("%d", &code);

    for (i = 0; i < count; i++)
    {
        if (library[i].code == code)
        {
            library[i].copies++;
            printf("Book Returned Successfully!\n");
            return;
        }
    }

    printf("Book Not Found!\n");
}