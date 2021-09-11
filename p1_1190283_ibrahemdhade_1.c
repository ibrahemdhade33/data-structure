#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#define maxchar 1000000
char blank[maxchar];
//define of the node
struct  Node {
     double coff;
     long int pow;
    struct Node *next;
    struct Node *pre;
}Node;
//define array of nodes
struct Node **arr;

//define head and tail for insertion
struct Node *tail,*head;
//function that remove all spaces from the string read from the file
char *removespaces1(char text[]) {
    for (int j = 0; j <100 ; ++j) {
        blank[j]='\0';
    }
    int c = 0, d = 0;
    while (text[c] != '\0') {
        if (!(text[c] == ' ') ) {
            blank[d] = text[c];
            d++;
        }
        c++;
    }
    return blank;
}
//using of merg sort to sort the data for multypication and addition and subtraction
struct Node *split(struct Node *head)
{
    struct Node *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}

struct Node *merge(struct Node *first, struct Node *second)
{

    if (!first)
        return second;


    if (!second)
        return first;


    if (first->pow > second->pow)
    {
        first->next = merge(first->next,second);
        first->next->pre = first;
        first->pre = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->pre= second;
        second->pre = NULL;
        return second;
    }
}


struct Node *mergeSort(struct Node *head)
{
    if (!head || !head->next)
        return head;
    struct Node *second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head,second);
}






FILE *out;
int pos = 0;

void show(struct Node* node,int flage) {
    if (flage == 0) {
        LOOP:
        while (node != NULL) {
            if (node->coff == 0.0) {
                node = node->next;
                goto LOOP;
            }

            if ((node->coff == 1 || node->coff == -1) && node->pow == 1) {
                if (node->coff == 1)
                    printf("x ");
                if (node->coff == -1)
                    printf("-x ");
            } else if (node->pow == 0)
                printf("%.3f ", node->coff);
            else if (node->coff == 1.0 || node->coff == -1) {
                if (node->coff == 1)
                    printf("x^%d ", node->pow);
                if (node->coff == -1)
                    printf("-x^%d ", node->pow);
            } else if (node->pow == 1)
                printf("%.3f x ", node->coff);

            else
                printf("%.3f x^%d ", node->coff, node->pow);
            if (node->next != NULL && node->next->coff > 0)
                printf("+ ");

            node = node->next;
        }

    } else {
        LOOP1 :
        while (node != NULL) {
            if (node->coff == 0) {
                node = node->next;
                goto LOOP1;
                if ((node->coff == 1 || node->coff == -1) && node->pow == 1) {
                    if (node->coff == 1)
                        fprintf(out, "x ");
                    if (node->coff == -1)
                        fprintf(out, "-x ");
                } else if (node->pow == 0)
                    fprintf(out, "%.3f ", node->coff);
                else if (node->coff == 1.0 || node->coff == -1) {
                    if (node->coff == 1)
                        fprintf(out, "x^%d ", node->pow);
                    if (node->coff == -1)
                        fprintf(out, "-x^%d ", node->pow);
                } else if (node->pow == 1)
                    fprintf(out, "%.3f x ", node->coff);
                else
                    fprintf(out, "%.3f x^%d ", node->coff, node->pow);
                if (node->next != NULL && node->next->coff > 0)
                    fprintf(out, "+ ");
                node = node->next;
            }
            fprintf(out, "\n");
        }
    }
}
//this function is to read from file and fill the linked list
void readfile() {
    char *ptr;
    int length = 0;
    FILE *fp;
    char str[maxchar];
    char *filename = "equations.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    arr = malloc(maxchar * sizeof(struct Node));

    while (fgets(str, maxchar, fp) != NULL) {
        //get the first line and remove all spaces from it
        strcpy(str, removespaces1(str));
        int i = 0, j = 0, k = 0;
        double coff1;
        int pow1;
        char sign = '\0';
        //read the line char by char to get coff and power
        while (str[i] != '\n' && str[i] != '\0') {
            char coff[1000000] = "", pow[10] = "";
            //read if ther a sign
            if (str[i] == '-' || str[i] == '+') {
                sign = str[i];
                i++;
            }
            //read numbers
            while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
                k++;
                coff[j] = str[i];
                j++;
                i++;
            }
            j = 0;
            //get the coff
            if (k == 0)
                coff1 = 1;
            else
                coff1 = atof(coff);
            k = 0;
            if (sign == '-')
                coff1 = coff1 * -1;
            //get the pow
            if (str[i] == 'x' || str[i] == 'X') {
                i++;
                if (str[i] == '^') {
                    i++;
                    while (str[i] != '+' && str[i] != '-') {
                        pow[j] = str[i];
                        j++;
                        i++;
                    }
                    j = 0;
                    pow1 = atoi(pow);
                } else
                    pow1 = 1;
            } else {
                pow1 = 0;
            }
            //store data in linked list
            struct Node *newnode;
            newnode = (struct Node *) malloc(sizeof(struct Node));
            newnode->coff = coff1;
            newnode->pow = pow1;
            if (length == 0) {
                arr[pos] = tail=head = newnode;
                newnode->next = NULL;
                newnode->pre = NULL;
                length++;
            } else {
                newnode->next = NULL;
                newnode->pre = tail;
                tail->next = newnode;
                tail = newnode;
                length++;
            }
        }
        int m = 0;
        struct Node *temp = arr[pos];
        show(temp, 0);
        printf("\n");
        pos++;
        length = 0;
    }
    fclose(fp);
}
//this function is to remove duplicate for in the power for polynomyals come from the multyplycation and addition and subtraction
//for subtraction and addition i creat an array that contain all the array in the array of linked list then i have passed it to this function and in will find the result debend on the flage
struct Node *removeDuplicates(struct Node *start) {
    struct Node *ptr1, *ptr2;
    ptr1 = start;
    while (ptr1 != NULL) {
        if(ptr1->next!=NULL)
        ptr2 = ptr1->next;
        else
            break;
        while (ptr2->pow == ptr1->pow) {
            ptr1->coff = ptr1->coff + ptr2->coff;
                ptr2->pre->next = ptr2->next;
                if (ptr2->next != NULL)
                    ptr2->next->pre = ptr2->pre;
                struct Node *temp = ptr2;
                ptr2 = ptr2->next;
                free(temp);
                if (ptr2 == NULL)
                    break;

        }
        ptr1 = ptr1->next;
    }
    return start;
}
//this function is to multibly the array of linked list
struct Node *multiply() {
    struct Node **arr1;
    arr1 = malloc(maxchar * sizeof(struct Node));
    if (pos == 1)
        return arr[0];
    int k = 0;
    struct Node *ptr1;
    struct Node *ptr2;
    struct Node *head, *tail;
    int pos1 = pos;
    //printf("%d",pos1);
    int i = 0, j = 0;
    LOOP:   for (i = 0, j = 0; i < pos1; i = i + 2, j++) {
        if (pos1 % 2 != 0) {
            if (k == 0) {
                arr1[j] = arr[i];
                i++;
                j++;
            } else {
                i++;
                j++;
            }
        }
        if (k == 0) {
            ptr1 = arr[i];
            ptr2 = arr[i + 1];
        } else {
            ptr1 = arr1[i];
            ptr2 = arr1[i + 1];
        }
        int len = 0;
        while (ptr1 != NULL) {
            while (ptr2 != NULL) {
                struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
                newnode->coff = ptr1->coff * ptr2->coff;
                newnode->pow = ptr1->pow + ptr2->pow;
                if (len == 0) {
                    head = tail = newnode;
                    len++;
                } else {
                    newnode->next = NULL;
                    newnode->pre = tail;
                    tail->next = newnode;
                    tail = newnode;
                    len++;
                }
                ptr2 = ptr2->next;
            }
            if (k == 0) {
                ptr2 = arr[i+1];
            } else
                ptr2 = arr1[i+1];
            ptr1 = ptr1->next;

        }
        arr1[j] = removeDuplicates(mergeSort(head));
        len = 0;
    }
    if(pos1%2==0)
    pos1 = pos1/2;
    else
        pos1 = (pos1/2)+1;
    k++;
    if( pos1!=1 && pos1!=0){

        goto LOOP;

    }
    return removeDuplicates((mergeSort(head)));
}
//this function is to make a list from all list in the array
//flage 1 for make on list for subtraction and flage 0 for addition
struct Node *joinlists(int flag) {
    struct Node *result;
    result = NULL;
    struct Node *tail = NULL;
    int len = 0;
    for (int k = 0; k < pos; ++k) {
        struct Node *temp;
        temp = arr[k];
        while (temp != NULL) {
            struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
            if (flag == 1 && k >= 1)
                newnode->coff = -1 * temp->coff;
            else
                newnode->coff = temp->coff;
            if (len == 0) {
                newnode->pow = temp->pow;
                newnode->next = NULL;
                newnode->pre = NULL;
                result = tail = newnode;
                temp = temp->next;
                len++;
            } else {
                newnode->pow = temp->pow;
                temp = temp->next;
                newnode->next = NULL;
                newnode->pre = tail;
                tail->next = newnode;
                tail = newnode;
            }
        }
    }
    return result;
}
float value(struct Node *node, float x) {
    float sum = 0.0;
    while (node != NULL) {
        sum += powf(x, node->pow) * node->coff;
        node = node->next;
    }
    return sum;
}
//the main function and creat the menu
int main() {
    struct Node *ptrmul = NULL;
    struct Node *ptradd = NULL;
    struct Node *ptrsub = NULL;
    float x;
    out = fopen("results.txt.", "a+");
    int todo;
    printf("please chose from the menu :\n\n "
           "1- read file of equations\n"
           "2- multiply equations \n"
           "3- add equations \n"
           "4- subtract equations\n "
           "5- save the result of all operation you do to file \n"
           "6- enter a value to substitute for x \n"
           "7- exit from the program \n");
    scanf("%d", &todo);
    while (todo) {
        switch (todo) {
            case 1:
                printf("the equations from the file is : \n\n");
                readfile();
                printf("the file has been stored to the linked list successfully ");
                break;
            case 2:
                if (arr == NULL) {
                    printf("please read the file");
                    break;
                }
                printf("\n\nthe multiplication of the equations is : \n\n");
                ptrmul = multiply();
                show(ptrmul, 0);
                printf("\n");
                break;

            case 3:
                if (arr == NULL) {
                    printf("please read the file");
                    break;
                }
                printf("\nthe addition of the equations is : \n\n");
                ptradd = removeDuplicates(mergeSort(joinlists(0)));

                show(ptradd, 0);
                printf("\n");
                break;
            case 4:
                if (arr == NULL) {
                    printf("please read the file");
                    break;
                }
                printf("\nthe subtraction  of the equations is : \n\n");
                ptrsub = removeDuplicates(mergeSort(joinlists(1)));
                show(ptrsub, 0);
                printf("\n");
                break;
            case 5:
                if (arr == NULL) {
                    printf("please read the file");
                    break;
                }
                printf("all results off operations has been added to file out.txt");
                fprintf(out, "\nthe multiplication of the equations is : \n");
                show(ptrmul, 1);
                fprintf(out, "\nthe addition of the equations is : \n");
                show(ptradd, 1);
                fprintf(out, "\nthe subtraction of the equations is : \n");
                show(ptrsub, 1);
                fclose(out);
                break;
            case 6:
                scanf("%f", &x);
                printf("\nthe result of substitute x in the multiplication equ is : \n");
                float mull = value(ptrmul, x);
                printf("%f", mull);
                printf("\nthe result of substitute x in the addition equ is : \n");
                float add = value(ptradd, x);
                printf("%f", add);
                printf("\nthe result of substitute x in the subtraction equ is : \n");
                float sub = value(ptrsub, x);
                printf("%f", sub);
                break;
            case 7:
                printf("thanks for using our program 3> 3> 3> ");
                exit(1);

            default:
                printf("out of range please chose again or exit the program ");
                break;
        }
        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("\nplease chose from the menu :\n\n "
               "1- read file of equations\n"
               "2- multiply equations \n"
               "3- add equations \n"
               "4- subtract equations\n "
               "5- save the result of all operation you do to file \n"
               "6- enter a value to substitute for x \n"
               "7- exit from the program \n");
        scanf("%d", &todo);
    }
    return 0;
}
