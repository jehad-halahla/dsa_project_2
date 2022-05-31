#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**************************************************************************************************
    MADE BY: JEHAD KHALED HALAHLA
         ID: 1201467
        SEC: 1
 INSTRUCTOR:DR.AHMAD ABU SNENA
THIS PROJECT WAS INDIVISUAL EFFORT
**ONLY BASIC FUNCTIONS PROVIDED BY INSTRUCTOR WERE COPIED, EXCEPT FOR THE DELETE NODE FUNCTION**

                      ********** FINISHED ON 6:24 PM 28/5/2022


                  THANK YOU VERY MUCH FOR TAKING THE TIME TO EXAMINE THIS CODE!!


                             ****@ ALL RIGHTS RESERVED*****
**************************************************************************************************/
struct AVLnode;
typedef struct AVLnode *AVL_T;//only names to indicate usage
typedef struct linkedListNode//a list to store topics in each tree node
{
    char topic[50];
    struct linkedListNode *next;//next pointer
} linkedListNode;

typedef struct data// a struct to simplify dealing with tree nodes
{
    char courseName [50];
    int creditHours;
    char courseCode [50];
    char departmentName [50];
    linkedListNode *head;// a head pointer for the topics list
} data;

struct AVLnode
{
    data *information;
    //double Data;
    AVL_T Left;
    AVL_T Right;
    int Height;
};
//information creation
data* createDataBlock(char courseName[50],int creditHours,char courseCode[50],char departmentName[50],char topics[500],data* newData);
//linked list methods, no need to explain further
linkedListNode* makeEmpty(linkedListNode* head);
void deleteList(linkedListNode* head);
void push(linkedListNode** headPtr,linkedListNode* newNode);
void deleteNode( linkedListNode* L,char topic[50]);
linkedListNode* findPrevious(char topics[50], linkedListNode* L);
void printList(linkedListNode* head);
//height calculations
int getHeight(AVL_T t);//get height of tree
int MAX(int x, int y);//get the max of two integers
//modification methods
AVL_T insert(AVL_T t, char key[50], data* newData);//insert a node to a tree, with rebalancing
void updateTreeNode(AVL_T node,AVL_T root,int edit);
AVL_T insertUsingCourseName(AVL_T t,char key [50],data* newData);//insert for the name tree, to get a lexicographic order
AVL_T createNameOrderedTree(AVL_T destination,AVL_T source);//tree creation, recursively adds nodes from one tree to another
AVL_T deleteTreeNode(AVL_T root, char key[50]);//deletion,rebalancing included
AVL_T insertIfStartsWithX(AVL_T destination, AVL_T source,char x);//letter tree if it starts
AVL_T insertIfinDepartment(AVL_T destination, AVL_T source,char department[50]);//insert in department
AVL_T deleteInCommon(AVL_T destination,  AVL_T source);//deletes joint elements from destination tree

//rotation methods,taken from dr.ahmad abu snena code,i can explain each one of them with ease
AVL_T singleRotateLeft(AVL_T x);
AVL_T singleRotateRight(AVL_T y);
AVL_T doubleRotateLeft(AVL_T K3);
AVL_T doubleRotateRight(AVL_T K3);
AVL_T minValueNode(AVL_T node);

//print functions, only to get output
void printPreOrder(AVL_T t);
void printInOrder(AVL_T t);
void printPostOrder(AVL_T t);
void printInOrderDepartmentRestricted(AVL_T t,char department [50]);//only print nodes that belong to a given department
void printMenu();//gives a generic menu
void printListOnFile(FILE* outputFile,linkedListNode* head);//prints linked list of topics on the out file
//reading file & printing on file
void printOnFile(FILE *outputFile, AVL_T t);//print data of tree nodes on the file
AVL_T readFile(AVL_T root);//reads input file
//inserting new course from user
AVL_T insertFromUser(AVL_T t);//inserts a tree node from user input-formatted-
//find course using course code!
AVL_T findNode(AVL_T t,char code[50]);//returns a node with the given code
int main()
{
    AVL_T root = NULL;//main tree that contains courses
    int choice;
    do
    {
        printMenu();
        printf("\nplease choose an option\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
        {
            root = readFile(root);
            break;
        }
        case 2:
        {
            root = insertFromUser(root);
            printInOrder(root);//to check if it inserts correctly
            break;
        }
        case 3:
        {
            char code[50];
            printf("please enter course code:\n");
            scanf("%s",code);
            struct AVLnode *node = root;//it will recursively iterate anyways so it doesn't matter
            if(root ==NULL)//tree isn't initialized
            {
                printf("empty tree!!\n");
            }

            else
            {
                node = findNode(root,code);
                if(node == NULL)
                {
                    printf("course with code %s not found!\n",code);
                }
                else
                {
                    printf("\ncourse %s info:\ncourse name: %s\ncredit hours: %d\ncourse department: %s\ntopics: ",node->information->courseCode,node->information->courseName,node->information->creditHours,node->information->departmentName);
                    printList(node->information->head);
                    //a function for node update
                    int n;
                    do
                    {
                        printf("\ndo you want to edit this course's info? 1 if yes, 0 if no..\n");
                        scanf("%d",&n);
                        if(n != 1)
                        {
                            printf("please enter a valid option\n");
                        }
                        else
                        {
                            int edit;
                            printf("choose what you want to edit:\n1. course name\n2. course department\n3. credit hours\n4. topics\n5. course code-i hope i get a bonus for this :)-\n");
                            scanf("%d",&edit);
                            updateTreeNode(node,root,edit);
                        }
                    }
                    while(n != 0);
                }
            }
            break;
        }
        case 4:
        {
            AVL_T rootNameOrdered = NULL;
            rootNameOrdered = createNameOrderedTree(rootNameOrdered,root);
            printf("IN-ORDER TREE(lexicographic order by course name):\n");
            printInOrder(rootNameOrdered);
            break;
        }
        case 5:
        {
            char code[50];
            printf("please enter course code:\n");
            scanf("%s",code);
            struct AVLnode *node = root;
            if(root ==NULL)
            {
                printf("empty tree!!\n");
            }

            else
            {
                node = findNode(root,code);
                if(node == NULL)
                {
                    printf("course with code %s not found!\n",code);
                }
                else
                {
                    printf("\ncourse %s topics: ",node->information->courseCode);
                    printList(node->information->head);
                }
            }

            break;
        }
        case 6:
        {
            int c;
            printf("0 if you want to sort lexicographically by code, any other number if by name\n");
            scanf("%d",&c);
            if(c == 0 )
            {
                char department[50];
                printf("enter department..>\n");
                getchar();
                fgets(department,50,stdin);
                sscanf(department,"%[^\n]",department);
                printInOrderDepartmentRestricted(root,department);
            }
            else
            {
                AVL_T rootNameOrdered = NULL;
                rootNameOrdered = createNameOrderedTree(rootNameOrdered,root);
                char department[50];
                printf("enter department..>\n");
                getchar();//to empty the buffer, used alot in this program
                fgets(department,50,stdin);//safer than gets
                sscanf(department,"%[^\n]",department);// a smart way to remove trailing \n from fgets
                printInOrderDepartmentRestricted(rootNameOrdered,department);
            }
            break;
        }
        case 7:
        {
            char code[50];
            printf("please enter course code you want to delete:\n");
            scanf("%s",code);
            root = deleteTreeNode(root,code);// a simple straightforward delete by code
            break;
        }
        case 8:
        {
            AVL_T treeSpecificLetter = NULL;
            char x;
            printf("please enter the letter you want to delete nodes based on\n");
            getchar();//again to empty stdin from \n
            scanf("%c",&x);
            treeSpecificLetter = insertIfStartsWithX(treeSpecificLetter,root,x);
            //printInOrder(treeSpecificLetter);
            root = deleteInCommon(root,treeSpecificLetter);
            break;
        }
        case 9:
        {

            char department[50];
            printf("please enter the department you want to delete nodes based on\n");
            getchar();
            fgets(department,50,stdin);
            sscanf(department,"%[^\n]",department);
            AVL_T treeOfSpecDepartment = NULL;
            treeOfSpecDepartment = insertIfinDepartment(treeOfSpecDepartment,root,department);
            printInOrder(treeOfSpecDepartment);
            root = deleteInCommon(root,treeOfSpecDepartment);

            break;
        }
        case 10:
        {
            FILE *outputFile = fopen("offered_courses.txt","w");
            printOnFile(outputFile,root);
            fclose(outputFile);


            break;
        }
        case 0:
        {
            //do nothing
            break;
        }
        default:
            printf("please enter a valid option\n");
        }
    }
    while(choice != 0);
    printf("\n\n**********************************THANK YOU VERY MUCH FOR USING THIS CODE %c**********************************\n\n",1);

    return 0;
}

void printMenu()
{
    printf("1. Read the file courses.txt file and create the tree.\n"
           "2. Insert a new course from the user with all its associated data.\n"
           "3. Find a course and support updating of its information.\n"
           "4. List courses in lexicographic order with their associated information(credit hours, IDs, and topics).\n"
           "5. List all topics associated with a given course.\n"
           "6. List all courses in lexicographic order that belong to the same department.\n"
           "7. Delete a course.\n"
           "8. Delete all courses that start with a specific letter.\n"
           "9. Delete all courses belong to a given department.\n"
           "10. Save all words in file offered_courses.txt.\n"
           "0. exit code\n");
}
int getHeight (AVL_T t)
{
    if(t==NULL)
        return -1;
    else
        return t->Height;
}
int MAX(int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}
AVL_T singleRotateLeft(AVL_T x)
{
    AVL_T y;
    y = x->Right;
    x->Right = y->Left;
    y->Left = x;

    x->Height = 1 + MAX(getHeight(x->Left), getHeight(x->Right));
    y->Height = 1 + MAX(getHeight(x), getHeight(y->Right));

    return y;
}
AVL_T singleRotateRight(AVL_T y)
{
    AVL_T x;
    x = y->Left;
    y->Left = x->Right;
    x->Right = y;
    y->Height = 1 + MAX(getHeight(y->Right), getHeight(y->Left));
    x->Height = 1 + MAX(getHeight(y), getHeight(x->Left));
    return x;
}
AVL_T doubleRotateLeft(AVL_T K3)
{
    K3->Left = singleRotateLeft(K3->Left);
    return singleRotateRight(K3);
}
AVL_T doubleRotateRight(AVL_T K3)
{
    K3->Right  = singleRotateRight(K3->Right);
    return singleRotateLeft(K3);
}
AVL_T insert(AVL_T t, char key[50],data* newData)
{
    if(t==NULL)
    {
        t=malloc(sizeof(struct AVLnode));
        //t->Data=key;
        t->information = newData;
        t->Height=0;
        t->Left= t->Right=NULL;
    }
    else if(strcmp(key, t->information->courseCode)<0)
    {
        t->Left=insert(t->Left,key,newData);
        if(getHeight(t->Left) - getHeight(t->Right) >= 2)
        {
            if(strcmp(key, t->Left->information->courseCode)<0)
                t=singleRotateRight(t);
            else
                t=doubleRotateLeft(t);
        }
    }
    else if(strcmp(key, t->information->courseCode)>0)
    {
        t->Right = insert(t->Right,key,newData);
        if(getHeight(t->Right) - getHeight(t->Left) >= 2)
        {
            if(strcmp(key, t->Right->information->courseCode)>0)
                t=singleRotateLeft(t);
            else
                t=doubleRotateRight(t);
        }
    }
    t->Height = 1 + MAX(getHeight(t->Right), getHeight(t->Left));
    return t;
}
void printInOrder(AVL_T t)
{
    if(t!= NULL)
    {
        printInOrder(t->Left);
        printf("\n%s || %d || %s || %s\nTopics:\n",t->information->courseName,t->information->creditHours,t->information->courseCode,t->information->departmentName);
        printList(t->information->head);
        printInOrder(t->Right);
    }
}
void printPreOrder(AVL_T t)
{
    if(t!= NULL)
    {
        printf("\n%s || %d || %s || %s ||\nTopics:\n",t->information->courseName,t->information->creditHours,t->information->courseCode,t->information->departmentName);
        printList(t->information->head);
        printPreOrder(t->Left);
        printPreOrder(t->Right);
    }
}
void printPostOrder(AVL_T t)
{
    if(t!=NULL)
    {
        printPostOrder(t->Left);
        printPostOrder(t->Right);
        printf("\n%s || %d || %s || %s ||\nTopics:\n",t->information->courseName,t->information->creditHours,t->information->courseCode,t->information->departmentName);
        printList(t->information->head);
    }
}

//linked lists
linkedListNode* makeEmpty(linkedListNode* head)
{
    //if there exists a list in memory location, replace it
    if(head != NULL)
        deleteList(head);
    head =(linkedListNode*)malloc(sizeof(linkedListNode));//returns null if it can't allocate
    if(head == NULL)
        printf("no memory space available");
    head->next= NULL;
    return head;
}
void deleteList(linkedListNode* head)
{
    linkedListNode *ptr,*temp;
    //since head doesn't have actual data we start iterating from its next
    ptr = head->next;
    head->next = NULL;
    //iteration loop
    while(ptr != NULL)
    {
        temp = ptr->next;//so we don't lose the link
        free(ptr);//frees the allocated memory for the node
        ptr = temp;
    }
}
void push(linkedListNode** headPtr,linkedListNode* newNode)
{
    linkedListNode* ptr;
    ptr = *headPtr;
    //loop gets the last node
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    //adding the new node at the end and making its next NULL
    ptr->next = newNode;
    ptr->next->next = NULL;
}
void deleteNode( linkedListNode* L,char topic[50])
{
    linkedListNode* P, *temp;
    P = findPrevious(topic, L);
    if( P->next !=NULL )
    {
        temp = P->next;
        P->next = temp->next; //bypass delete cell
        //empties the linked list to save memory
        free(temp);
    }
}
linkedListNode* findPrevious(char topic[50], linkedListNode* L)
{
    linkedListNode* ptr;
    ptr = L;
    while(ptr->next != NULL && strcmp(ptr->next->topic,topic)!=0)
        ptr = ptr->next;
    return ptr;
}
void printList(linkedListNode* head)
{
    linkedListNode* ptr;
    for(ptr=head->next ; ptr->next!= NULL; ptr = ptr->next )
    {
        printf("%s, ",ptr->topic);
    }

    printf("%s.\n\n",ptr->topic);
}
//data
void printListOnFile(FILE* outputFile,linkedListNode* head)
{
    linkedListNode* ptr;
    for(ptr=head->next ; ptr->next!= NULL; ptr = ptr->next )
    {
        fprintf(outputFile,"%s, ",ptr->topic);
    }

    fprintf(outputFile,"%s.\n\n",ptr->topic);
}
data* createDataBlock(char courseName [50],int creditHours,char courseCode[50],char departmentName [50],char topics [500],data* newData)
{
    newData =(data*)malloc(sizeof(data));//memory allocation
    //copies data
    strcpy(newData->courseName,courseName);
    newData->creditHours = creditHours;
    strcpy(newData->courseCode,courseCode);
    strcpy(newData->departmentName,departmentName);
    newData->head =NULL;
    newData->head = makeEmpty(newData->head);
    char *token = strtok(topics, ",");//insert into linked list
    while(token!=NULL)
    {
        char *tok = token ;
        if(token[0]==' ')//removing space from file format
        {
            tok = token+1;
        }

        //printf( "%s\n", tok ); //printing each token
        linkedListNode *newNode = NULL;
        newNode =(linkedListNode*)malloc(sizeof(linkedListNode));
        strcpy(newNode->topic,tok);
        push(&(newData->head),newNode);//push topic into topic linked list for specific tree

        token = strtok(NULL, ",");

    }
    return newData;
}

AVL_T readFile(AVL_T root)
{
    FILE *filePtr = fopen("courses.txt","r");
    char line [800];
    char courseName [50];
    int creditHours;
    char courseCode [50];
    char departmentName [50];
    char topics [500];
    if(!filePtr)
    {
        printf("file doesn't exist\n");
    }
    else
    {
        while(fgets(line,800,filePtr))//gets line with an excess \n
        {
            //cut according to file format
            sscanf(line, "%[^:]:%d#%[^#]#%[^/]/%[^\n]", courseName, &creditHours, courseCode,departmentName,topics);
            data *newData = createDataBlock(courseName,creditHours,courseCode,departmentName,topics,newData);
            root = insert(root,newData->courseCode,newData);
        }

    }
    return root;
}
AVL_T insertFromUser(AVL_T t)
{
    char line[800];
    char courseName [50];
    int creditHours;
    char courseCode [50];
    char departmentName [50];
    char topics [500];
    data * newData = NULL;
    printf("please enter course info in the following format:\n");
    printf("Course name:Credit Hours#Course Code#Course Department/topic1,topic2,topic3....topicN\n");
    getchar();//empties buffer
    fgets(line,800,stdin);
    sscanf(line, "%[^:]:%d#%[^#]#%[^/]/%[^\n]", courseName, &creditHours, courseCode,departmentName,topics);
    newData = createDataBlock(courseName,creditHours,courseCode,departmentName,topics,newData);
    if(findNode(t,courseCode) == NULL)
    {
        t= insert(t,newData->courseCode,newData);
    }
    else
    {
        while(findNode(t,courseCode) != NULL)
        {
            printf("this course code already exists!,please try again\n");
            gets(courseCode);
        }
        strcpy(newData->courseCode,courseCode);
        t= insert(t,newData->courseCode,newData);
    }

    return t;

}
AVL_T findNode(AVL_T t,char code[50])
{
    if(t!=NULL)
    {
        if(strcmp(t->information->courseCode,code)==0)
        {
            return t;
        }
        else if(strcmp(t->information->courseCode,code)>0)
            return findNode(t->Left,code);
        else
            return findNode(t->Right,code);
    }
}

void updateTreeNode(AVL_T node,AVL_T root,int edit)
{
    switch(edit)
    {
    case 1:
    {
        char courseName [50];
        printf("please enter the desired name:\n");
        getchar();
        fgets(courseName,50,stdin);
        sscanf(courseName,"%[^\n]",courseName);//get rid of the trailling \n
        strcpy(node->information->courseName,courseName);
        break;
    }
    case 2:
    {
        char courseDepartment[50];
        printf("please enter the desired course department:\n");
        getchar();
        fgets(courseDepartment,50,stdin);
        sscanf(courseDepartment,"%[^\n]",courseDepartment);//get rid of the trailling \n
        strcpy(node->information->departmentName,courseDepartment);
        break;
    }
    case 3:
    {
        int credit;
        printf("please enter desired credit hours:\n");
        scanf("%d",&credit);
        node->information->creditHours = credit;//update credit
        break;
    }
    case 4:
    {
        int add;//user may want to either delete a topic or insert one
        printf("0 if you want to add a topic, any other number if you want to delete a topic..>\n");
        scanf("%d",&add);
        char topic[50];
        if(add == 0)
        {

            printf("please enter the topic you want to add:\n");
            getchar();
            fgets(topic,50,stdin);
            sscanf(topic,"%[^\n]",topic);
            linkedListNode *newNode =(linkedListNode*)malloc(sizeof(linkedListNode));
            strcpy(newNode->topic,topic);
            push(&(node->information->head),newNode);
        }
        else
        {
            printf("please enter the topic you want to remove:\n");
            getchar();
            fgets(topic,50,stdin);
            sscanf(topic,"%[^\n]",topic);
            deleteNode(node->information->head,topic);
        }
        break;
    }
    case 5:
    {
        printf("please enter the desired new code:\n");
        char code [50];
        getchar();
        fgets(code,50,stdin);
        sscanf(code,"%[^\n]",code);
        struct AVLnode *foundNode = NULL;
        foundNode = findNode(root,node->information->courseCode);
        if(foundNode!= NULL)
        {
            struct data* newBlock = foundNode->information;
            if(findNode(root,code) == NULL)
            {
                strcpy(newBlock->courseCode,code);
                //deletes the node to re-insert it
                root = deleteTreeNode(root,newBlock->courseCode);
                //inserting it again after updating code to get rearranged
                root = insert(root,newBlock->courseCode,newBlock);
                printf("node course code updated and re-inserted !\n");
                break;
            }
            else
            {
                printf("\ncourse with this code already exists, please try updating again\n");
            }

        }
        else
        {
            printf("error occured!\n");
        }
        break;
    }
    default:
        printf("please enter a valid option\n");
        break;
    }

}
AVL_T insertUsingCourseName(AVL_T t,char key [50],data* newData)
{
    if(t==NULL)
    {
        t=malloc(sizeof(struct AVLnode));
        //t->Data=key;
        t->information = newData;
        t->Height=0;
        t->Left= t->Right=NULL;
    }
    else if(strcmp(key, t->information->courseName)<0)
    {
        t->Left=insertUsingCourseName(t->Left,key,newData);
        if(getHeight(t->Left) - getHeight(t->Right) >= 2)
        {
            if(strcmp(key, t->Left->information->courseName)<0)
                t=singleRotateRight(t);
            else
                t=doubleRotateLeft(t);
        }
    }
    else if(strcmp(key, t->information->courseName)>0)
    {
        t->Right = insertUsingCourseName(t->Right,key,newData);
        if(getHeight(t->Right) - getHeight(t->Left) >= 2)
        {
            if(strcmp(key, t->Right->information->courseName)>0)
                t=singleRotateLeft(t);
            else
                t=doubleRotateRight(t);
        }
    }
    t->Height = 1 + MAX(getHeight(t->Right), getHeight(t->Left));
    return t;
}

int countTreeElements(AVL_T t)
{
    if(t != NULL)
    {
        return 1+ countTreeElements(t->Left) + countTreeElements(t->Right);//may be needed
    }
}
AVL_T createNameOrderedTree(AVL_T destination,AVL_T source)
{
    if(source!=NULL)
    {
        //makes a tree that is name ordered
        destination = createNameOrderedTree( destination, source->Left);
        destination = insertUsingCourseName(destination,source->information->courseName,source->information);
        destination = createNameOrderedTree(destination, source->Right);

    }
    return destination;
}
void printInOrderDepartmentRestricted(AVL_T t,char department [50])
{
    if(t != NULL)
    {
        printInOrderDepartmentRestricted(t->Left,department);
        if(strcmp(t->information->departmentName,department)==0)
            printf("\n%s || %d || %s || %s\nTopics:\n",t->information->courseName,t->information->creditHours,t->information->courseCode,t->information->departmentName);
        printList(t->information->head);
        printInOrderDepartmentRestricted(t->Right,department);


    }
}

AVL_T deleteTreeNode(AVL_T root, char key[50])
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(key, root->information->courseCode)<0)
        root->Left = deleteTreeNode(root->Left, key);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(key, root->information->courseCode)>0)
        root->Right = deleteTreeNode(root->Right, key);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->Left == NULL) || (root->Right == NULL) )
        {
            AVL_T temp = root->Left ? root->Left : root->Right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVL_T temp = minValueNode(root->Right);
            // Copy the inorder successor's data to this node
            root->information = temp->information;

            // Delete the inorder successor
            root->Right = deleteTreeNode(root->Right, temp->information->courseCode);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->Height = 1 + MAX(getHeight(root->Left),getHeight(root->Right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->Left) >= 0)
        return singleRotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->Left) < 0)
    {
        root->Left =  singleRotateLeft(root->Left);
        return singleRotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->Right) <= 0)
        return singleRotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->Right) > 0)
    {
        root->Right = singleRotateRight(root->Right);
        return singleRotateLeft(root);
    }

    return root;
}

AVL_T minValueNode(AVL_T node)
{
    AVL_T current = node;

    /* loop down to find the leftmost leaf */
    while (current->Left != NULL)
        current = current->Left;
    return current;
}


int getBalance(AVL_T t)
{
    if (t == NULL)
        return 0;
    return getHeight(t->Left) - getHeight(t->Right);
}
AVL_T insertIfStartsWithX(AVL_T destination, AVL_T source,char x)
{
    if(source != NULL)
    {
        //a simple recursive function, inserts the node from source into destination if first letter matches the courseCode
        destination = insertIfStartsWithX(destination,source->Left,x);
        if((source->information->courseCode)[0] == x)
            destination = insert(destination,source->information->courseCode,source->information);
        destination = insertIfStartsWithX(destination, source->Right,x);

    }
    return destination;

}

AVL_T deleteInCommon(AVL_T destination,  AVL_T source)// i am very proud of this function
{
    if(source !=NULL)
    {
        //deletes nodes in source, from destination
        destination = deleteInCommon(destination,source->Left);
        destination = deleteTreeNode(destination,source->information->courseCode);
        destination = deleteInCommon(destination, source->Right);
    }
    return destination;
}

AVL_T insertIfinDepartment(AVL_T destination, AVL_T source,char department[50])
{
    if(source != NULL)
    {
        destination = insertIfinDepartment(destination,source->Left,department);
        if(strcmp(source->information->departmentName,department)==0)//if it is in the required department, add it to dest tree
            destination = insert(destination,source->information->courseCode,source->information);
        destination = insertIfinDepartment(destination,source->Right,department);

    }
    return destination;
}
void printOnFile(FILE *outputFile, AVL_T t)
{
    if(t != NULL)
    {

        printOnFile(outputFile,t->Left);
        fprintf(outputFile,"\n%s || %d || %s || %s\nTopics:\n",t->information->courseName,t->information->creditHours,t->information->courseCode,t->information->departmentName);
        printListOnFile(outputFile,t->information->head);
        printOnFile(outputFile,t->Right);
    }

}

