// #include <caca.h>
// #include <caca_conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


struct books{ 
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} bk;

struct student{
    int id;
    char studentName[50];
    char courseName[50];
    int studentRollNo;
    char bookName[50];
    char date[12];
} std;

FILE *fp;

void addBook();
void bookList();
void removeBook();
void issueBook();
void issueBookList();

int main() {
    int choice;
    do {
        system("clear");
        printf("<== Library Management System ==>\n");
        printf("1.Add Books\n");
        printf("2.Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("0.EXIT\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                exit(0);
            case 1:
                addBook();
                break;
            case 2:
                bookList();
                break;
            case 3:
                removeBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                issueBookList();
                break;
            default:
                printf("Invalid choice...!\n\n");
        }
        printf("Press any key to continue...\n");
        // getch();
        fflush(stdin);
        getchar();
        // getchar_unlocked();
    } while(1);
    return 0;
}

void addBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(bk.date, myDate);

    fp = fopen("book_data.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &bk.id);

    printf("Enter book name: ");
    fflush(stdin);
    // fgets(bk.bookName, 50, stdin);
    scanf("%s", bk.bookName);

    printf("Enter author name (use 'unknown' if not known): ");
    fflush(stdin);
    // fgets(bk.authorName, 50, stdin);
    scanf("%s", bk.authorName);

    printf("Book Added Successfully...\n");

    fwrite(&bk, sizeof(bk), 1, fp);
    fclose(fp);
}

void bookList() {
    system("clear");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("book_data.txt", "rb");
    while(fread(&bk, sizeof(bk), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %s\n\n", bk.id, bk.bookName, bk.authorName, bk.date);
    }
    fclose(fp);
}

void removeBook() {
    int id;
    int f=0;
    system("clear");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("book_data.txt", "rb");
    ft = fopen("book_data.txt", "wb");

    while(fread(&bk, sizeof(bk), 1, fp) == 1) {
        if(id == bk.id) 
            f=1;
        else 
            fwrite(&bk, sizeof(bk), 1, ft);
    }
    
    if(f == 1) 
        printf("\n\nDelete Successful.");
    else 
        printf("\n\nRecord not found !");

    fclose(fp);
    fclose(ft);

    remove("book_data.txt");
    rename("temp.txt", "book_data.txt");
}

void issueBook() {

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(std.date, myDate);

    int f=0;

    system("clear");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &std.id);

    fp = fopen("book_data.txt", "rb");

    while(fread(&bk, sizeof(bk), 1, fp) == 1) {
        if(bk.id == std.id) {
            strcpy(std.bookName, bk.bookName);
            f=1;
            break;
        }
    }
    
    if(f == 0) {
        printf("No book found with yhis id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter student name: ");
    fflush(stdin);
    scanf("%s", std.studentName);

    printf("Enter student course: ");
    fflush(stdin);
    scanf("%s", std.courseName);

    printf("Enter student roll no: ");
    fflush(stdin);
    scanf("%d", &std.studentRollNo);

    printf("Book Issued Successfully.\n\n");

    fwrite(&std, sizeof(std), 1, fp);
    fclose(fp);
}

void issueBookList() {
    system("clear");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "Std.id", "Name", "Course", "Rollno", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&std, sizeof(std), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", std.id, std.studentName, std.courseName, std.studentRollNo, std.bookName, std.date);
    }
    fclose(fp);
}