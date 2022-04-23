#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// void strlwr(char *str){
//   for(int i = 0; i < strlen(str);i++){
//     str[i] = tolower((int) str[i]);
//   }
// }

// void strupr(char *str){
//   for(int i = 0; i < strlen(str);i++){
//     str[i] = toupper((int) str[i]);
//   }
// }

typedef struct{
    char meno[64];
    char priezvisko[64];
} MENA_AUTOROV;

struct NameNode{
    MENA_AUTOROV data;
    struct NameNode* next;
};

typedef struct{
    int id;
    char nazov[128];
    char typ[3];
    int cas;
    struct NameNode *mena;
    int datum;
} PRISPEVOK;



struct Node{
    PRISPEVOK data;
    struct Node* next;
};

void printNode(struct Node* head){
    if(head != NULL){
        struct NameNode* tmp = head -> data.mena;
        int nameCount = 1;
        printf("ID cislo: %d\n", head->data.id);
        printf("Nazov prispevku: %s\n", head->data.nazov);
        printf("Mena autorov:\n");
        while(tmp != NULL){
            printf("    %d: %s %s\n", nameCount, tmp -> data.meno, tmp -> data.priezvisko);
            nameCount++;
            tmp = tmp -> next;
        }
        printf("Typ prezentovania %s\n", head->data.typ);
        printf("Cas prezentovania: %d\n", head->data.cas);
        printf("Datum: %d\n", head->data.datum);
        printf("\n");

    }
}

void printAll(struct Node* head){

    while (head != NULL) {
        printNode(head);
        head = head->next;
    }
}

void printNodePointers(struct Node* head){
    int counter = 0;
    printf("\n");
    while(head != NULL){
        printf("NODE %d POINTER: %p\n", counter, head );
        head = head -> next;
        counter++;
    }
    printf("\n");

}


void freeNode(struct Node* target){
    struct NameNode* meno_target = NULL;
    struct NameNode* meno_tmp = target ->data.mena;
    while(meno_tmp != NULL){
        meno_target = meno_tmp;
        meno_tmp = meno_tmp -> next;
        free(meno_target);
    }

    free(target);
    return;
}


void freeListsMemory(struct Node** head){
    struct Node* target;
    while((*head) != NULL){
     
        target = (*head);
        (*head) = (*head) -> next;
        freeNode(target);
    }
    return;
}


void switchNodes(struct Node** head, int c1, int c2){
    struct Node *headCopy1, *headCopy2, *old1, *old2, *tmp;
    int maxPosition = (c1 > c2) ? c1 : c2;


    printNodePointers(*head);

    printf("BreakPoint 1\n");
    
    if(c1 == c2){
        return;
    }
    int i = 0;
    tmp = *head;
    old1 = NULL;
    old2 = NULL;

    while(tmp != NULL && (i <= maxPosition)){
        if(i == c1 -1){
            old1 = tmp;
        }
        if(i == c1){
            headCopy1 = tmp;
        }

        if( i == c2 - 1){
            old2 = tmp;
        }
        if(i == c2){
            headCopy2 = tmp;
        }

        tmp = tmp-> next;
        i++;
    }
    // printf("BreakPoint 2\n");


    if(headCopy1 != NULL && headCopy2 != NULL){
        if(old1 != NULL){
            old1 -> next = headCopy2;
        }
        // printf("BreakPoint 3\n");

        if(old2 != NULL){
            old2 -> next = headCopy1;
        }
        // printf("BreakPoint 4\n");

        tmp = headCopy1 -> next;
        // printf("BreakPoint 5\n");
        // printf("HEADCP2: %p\n", headCopy2);
        headCopy1 -> next = headCopy2 -> next;
        // printf("BreakPoint 6\n");

        headCopy2 -> next = tmp;

        // printf("BreakPoint 7\n");


        if(old1 == NULL){
            *head = headCopy2;
        }
        else if(old2 == NULL){
            *head = headCopy1;
        }
    }

    printNodePointers(*head);

}

  



// void switchNodes(struct Node** head, int c1, int c2){
//     struct Node *headCopy1, *headCopy2, *old1, *old2, *tmp;
//     int maxPosition = (c1 > c2) ? c1 : c2;
//     int totalNodes = 6;

//     printNodePointers(*head);

//     printf("BreakPoint 1\n");
    
//     if(c1 == c2){
//         return 1;
//     }
//     int i = 0;
//     tmp = *head;
//     old1 = NULL;
//     old2 = NULL;

//     while(tmp != NULL && (i <= maxPosition)){
//         if(i == c1 -1){
//             old1 = tmp;
//         }
//         if(i == c1){
//             headCopy1 = tmp;
//         }

//         if( i == c2 - 1){
//             old2 = tmp;
//         }
//         if(i == c2){
//             headCopy2 = tmp;
//         }

//         tmp = tmp-> next;
//         i++;
//     }
//     printf("BreakPoint 2\n");


//     if(headCopy1 != NULL && headCopy2 != NULL){
//         if(old1 != NULL){
//             old1 -> next = headCopy2;
//         }
//         printf("BreakPoint 3\n");

//         if(old2 != NULL){
//             old2 -> next = headCopy1;
//         }
//         printf("BreakPoint 4\n");

//         tmp = headCopy1 -> next;
//         printf("BreakPoint 5\n");
//         printf("HEADCP2: %p\n", headCopy2);
//         headCopy1 -> next = headCopy2 -> next;
//         printf("BreakPoint 6\n");

//         headCopy2 -> next = tmp;

//         printf("BreakPoint 7\n");


//         if(old1 == NULL){
//             *head = headCopy2;
//         }
//         else if(old2 == NULL){
//             *head = headCopy1;
//         }
//     }

//     printNodePointers(*head);


// }





void insertNodeAtIndex(int index, struct Node** head, struct Node* nodeToInsert){
    printf("\n\n");
    struct Node* newNode = nodeToInsert;

    printf("START: %p\n", (*head));

    printNodePointers(*head);

    if((*head) == NULL){
        (*head) = newNode;
        printf("MASTERHEAD POINTER: %p\n", (*head));
    }
    else{
        struct Node* headCopy = (*head);
        printf("NEWNODE POINTER: %p\n", newNode);

        if(index == 1){
            printf("Moving to first\n");
            newNode -> next = headCopy;
            printf("HEADCOPY POINTER: %p\n", headCopy);
            printf("NEWNODE POINTER: %p\n", newNode);
            printf("NEWNODE NEXT POINTER: %p\n", newNode -> next);
            (*head) = newNode;
            printf("HEAD POINTER: %p\n", (*head));
            printNodePointers(*head);
            return;
        }
        for(int i = 0; i < index-2 && headCopy -> next != NULL; i++){
            headCopy = headCopy -> next;
        }
        
        if(headCopy -> next != NULL){
            newNode -> next = headCopy -> next;
            headCopy -> next = newNode;
        }
        else{
            headCopy -> next = newNode;
        }
        printf("HEAD NEXT POINTER: %p\n", (*head) -> next);
        printf("NEWNODE NEXT POINTER: %p\n", newNode -> next);
        printf("HEADCOPY: %p\n", headCopy);

    }

    printNodePointers(*head);
    printNode(*head);
 
}

void help(){
    system("clear");
    printf("***********************\n");
    printf("    ZPrPr2 Projekt 2\n\n");
    printf(" Funkcie\n");
    printf("  v - vypis udajov zo suboru, alebo z poli\n");
    printf("  o - vypis prispevkov s rovnakym datumom\n");
    printf("  n - zisti pocet zaznamov v subore, vytvori polia pre polozky\n");
    printf("  s - vypis prezentovani podla datumu\n");
    printf("  h - histogram typov prezentovania\n");
    printf("  z - vymazanie zaznamu podla nazvu\n");
    printf("  p - pridanie zaznamu\n");
    printf("\n");
    printf("  k - ukoncenie\n\n");
    printf("  l - pomocne menu\n");
    printf("\n***********************\n");
}

void a(struct Node** head){
    if(*head == NULL){
        printf("Zaznamy neboli nacitane\n");
        return;
    }
    char newType[32];
    int id = 0;

    while(scanf("%d %s", &id, newType) != 2 || id % 15 != 0 || ((strcmp(newType, "UP") && strcmp(newType, "UD") && strcmp(newType, "PP") && strcmp(newType, "PD")))){
        printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
    }

    struct Node* headCopy = *head;
    while(headCopy != NULL){

        if(headCopy -> data.id == id){
            printf("Prispevok s nazvom %s sa bude prezentovat %s [%s]\n", headCopy -> data.nazov, newType, headCopy -> data.typ);
            strcpy(headCopy -> data.typ, newType);
        }

        headCopy = headCopy -> next;
    }

}

void v( struct Node* head ){
    if(head != NULL){
        printAll(head);
    }
    else{
        printf("Prazdny zoznam zaznamov!\n");
    }
    
    return;

}

void h(struct Node* head){
    int counter = 0;
    char typEntry[32];
    fgets(typEntry, 32, stdin);
    strupr(typEntry);
    char *remNewLine = strrchr(typEntry, '\n');
    if(remNewLine){
        *remNewLine = '\0';
    }
    while(head != NULL){
        if(!strcmp(head -> data.typ, typEntry)){
            counter++;
            printf("%d.\n", counter);
            printNode(head);
        }
        head = head -> next;
    }

    if(!counter){
        printf("Pre typ %s nie su ziadne zaznamy\n", typEntry);
    }
}

void z(struct Node** head){
    char name[128];
    fgets(name, 128, stdin);
    strlwr(name);

    char *newLineRemove = strrchr(name, '\n');
    if(newLineRemove){
        *newLineRemove = '\0';
    }

    struct Node* headCopy = (*head);
    struct Node* tmp = NULL;




    while(headCopy != NULL){
        struct NameNode* tmp_meno = headCopy -> data.mena;
        int nodeMatchFound = 0;
        while(tmp_meno != NULL){

            char nodeNameString[256];
            nodeNameString[0] = '\0';

            strcat(nodeNameString, tmp_meno -> data.meno);
            strcat(nodeNameString, " ");
            strcat(nodeNameString, tmp_meno -> data.priezvisko);
 
            strlwr(nodeNameString);
            if(!strcmp(name, nodeNameString)){
                printf("Prispevok s nazvom %s bol vymazany.\n", headCopy -> data.nazov);
                nodeMatchFound = 1;   
                break;         
            }
            
            nodeNameString[0] = '\0';
            tmp_meno = tmp_meno -> next;
        }
        if(nodeMatchFound){
            // printf("TMP: %p\n", tmp);
            // printf("NODEMATCH: %p\n", headCopy);
            if(tmp == NULL){
                *head = headCopy->next;
                // free(headCopy);
                freeNode(headCopy);
                headCopy = *head;
                
            }
            else{
                tmp->next = headCopy->next;
             
                freeNode(headCopy);
                headCopy = tmp->next;
            }
            continue;
      
        }

        // printf("Moving to next node\n");
        tmp = headCopy;
        headCopy = headCopy -> next;
        
    }
    // printf("Printing main tree\n");
    // printNodePointers(*head);
    return;

}

void p( struct Node ** head){
    int n = 0;
    printf("N: ");
    scanf("%d", &n);

    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    struct NameNode* nameRecord = (struct NameNode*) malloc(sizeof(struct NameNode));
    nameRecord -> next = NULL;

    newNode -> next = NULL;
    newNode -> data.mena = nameRecord;

    
    char menaAutorov[256];
    char nazov[64];
    char typ[3];
    int id = 0;
    int cas = 0;
    int datum = 0;
  
    printf("ID: ");
    scanf("%d", &id);

    while(getchar() != '\n');
    printf("Nazov: ");
    fgets(nazov, 64, stdin);

    char *remNewLine = strrchr(nazov,'\n');
    if(remNewLine){
        *remNewLine = '\0';
    }
  
    printf("Mena: ");
    fgets(menaAutorov, 256, stdin);

    remNewLine = strrchr(menaAutorov,'\n');
    if(remNewLine){
        *remNewLine = '\0';
    }
  
    printf("Typ: ");
    fgets(typ, 3, stdin);

    remNewLine = strrchr(typ,'\n');
    if(remNewLine){
        *remNewLine = '\0';
    }
  
    printf("Cas: ");
    scanf("%d", &cas);
  

    printf("Datum: ");
    scanf("%d", &datum);
  


    printf("\n\nData:\n");
    printf("ID: %d\n", id);
    printf("Nazov: %s\n", nazov);
    printf("Mena: %s\n", menaAutorov);
    printf("Typ: %s\n", typ);
    printf("Cas: %d\n", cas);
    printf("Datum: %d\n\n", datum);

    printf("Data input success\n");

    newNode -> data.id = id;
    newNode -> data.cas = cas;
    newNode -> data.datum = datum;
    strcpy(newNode -> data.typ, typ);
    strcpy(newNode -> data.nazov, nazov);
    
    char *segment;
    int nameCheck = 0;
    segment = strtok(menaAutorov, "#");
    while(segment != NULL){
        int specialCheck = 0;
        if(nameCheck){
            nameRecord -> next = (struct NameNode*) malloc(sizeof(struct NameNode));
            nameRecord = nameRecord -> next;
            nameRecord -> next = NULL;
        }
        int positionIndex = 0;
        for(int i = 0; i < (int)strlen(segment); i++){
            if(segment[i] == ' '){
                if(!specialCheck){
                    nameRecord->data.meno[positionIndex] = '\0';
                }
                specialCheck = 1;
                positionIndex = 0;
                continue;
            }
            if(!specialCheck){
                nameRecord->data.meno[positionIndex] = segment[i];
                positionIndex++;
    
            }
            if(specialCheck == 1){
                nameRecord -> data.priezvisko[positionIndex] = segment[i];
                positionIndex++;
        
            }
        }

        nameRecord -> data.priezvisko[positionIndex] = '\0';
        nameCheck++;
        segment = strtok(NULL, "#");
    }

    printf("Node data paste success\n");

    if(n > 0){
        insertNodeAtIndex(n,head, newNode);
    }
}

void n( struct Node** head ){   
  
    FILE *fr;

    if((fr = fopen("OrganizacnePodujatia2.txt", "r")) == NULL){
        printf("Zaznamy neboli nacitane\n");
        return;
    }

    int rowCount = 0;

    if((*head) != NULL){
        freeListsMemory(head);
    }
   
    fseek(fr, 0, SEEK_SET);

    char row[256];
  

    (*head) = (struct Node*) malloc(sizeof(struct Node));

    struct Node* newRecord = (*head);


    struct NameNode* nameRecord = NULL;

    nameRecord = (struct NameNode*) malloc(sizeof(struct NameNode));
    nameRecord -> next = NULL;
    newRecord -> data.mena = nameRecord;

    (*head) -> next = NULL;

    int recordsCount = 1;

    while(feof(fr) == 0){
        
        fgets(row,256,fr);

        char *rem_newline = strrchr(row, '\n');
        if(rem_newline){
            *rem_newline = '\0';
        }
        
        if(rowCount == 1){
            newRecord -> data.id = atoi(row);
        }
        else if(rowCount == 2){
            strcpy(newRecord -> data.nazov, row);
        }
        else if(rowCount == 3){
            int namesCount = 0;

            char *segment;
            segment = strtok(row, "#");

    
            int nameCheck = 0;
            while(segment != NULL){
                
                int specialCheck = 0;
                if(nameCheck){
                    nameRecord -> next = (struct NameNode *) malloc(sizeof(struct NameNode));
                    nameRecord = nameRecord -> next;
                    nameRecord -> next = NULL;
                }

                int positionIndex = 0;
                for(int i = 0; i < (int)strlen(segment); i++){
                    if(segment[i] == ' '){
                        if(!specialCheck){
                            nameRecord->data.meno[positionIndex] = '\0';
                        }
                        specialCheck = 1;
                        positionIndex = 0;
                        continue;
                    }
                    if(!specialCheck){
                        nameRecord->data.meno[positionIndex] = segment[i];
                        positionIndex++;
           
                    }
                    if(specialCheck == 1){
                        nameRecord -> data.priezvisko[positionIndex] = segment[i];
                        positionIndex++;
              
                    }
                }

                nameRecord -> data.priezvisko[positionIndex] = '\0';

             
         
                nameCheck++;
                segment = strtok(NULL, "#");
            }
        
            namesCount++;

        }
        else if(rowCount == 4){
            strcpy(newRecord -> data.typ, row);
        }
        else if(rowCount == 5){
            newRecord -> data.cas = atoi(row);
        }
        else if(rowCount == 6){
            newRecord -> data.datum = atoi(row);
        }
        else if(rowCount == 7 ){
            rowCount = 1;
            newRecord -> next = (struct Node *) malloc(sizeof(struct Node));
            newRecord = newRecord -> next;
            newRecord -> next = NULL;
            nameRecord = (struct NameNode*) malloc(sizeof(struct NameNode));
            nameRecord -> next = NULL;
            newRecord -> data.mena = nameRecord;
            recordsCount++;
            continue;
        }

        rowCount++;

    }

    if(fclose(fr) == EOF){
      printf("Nezatvoreny subor!");
    }
  
    printf("Nacitalo sa %d zaznamov\n", recordsCount);
}

void r( struct Node** head){
    if((*head) != NULL){
        int nodePos1, nodePos2;
        
        while(scanf("%d %d", &nodePos1, &nodePos2) != 2){
            printf("Neplatny vstup!\n");
            while(getchar() != '\n');
        }
        printf("POS1: %d  |  POS2: %d\n", nodePos1, nodePos2);
        // switchNodes(head, 15, 15);
        // switchNodes(head,3,2);
        // switchNodes(head,2,6);
        // switchNodes(head,1,6);

    }
}

int main(){

    //! VARIABLES
    char opt = ' ';

    //! POINTERS

    //! LINKED LISTS
    struct Node* head = NULL;

    //! POLIA

    //? Menu
    while(scanf("%c", &opt) < 1){
        printf("Neplatny vstup!\n");
        while(getchar() != '\n');
    }

    while(1){

        switch (opt){
            case 'v':
                v(head);
                break;
            case 'n':
                n(&head);
                break;
            case 'h':
                h(head);
                break;
            case 'a':
                a(&head);
                break;
            case 'k':
                freeListsMemory(&head);
                return 0;
            case 'r':
                r(&head);
                break;
            case 'z':
                z(&head);
                break;
            case 'p':
                p(&head);
                break;
            default:
                printf("Neplatny vstup!\n");
                break;
        }

        while(scanf(" %c", &opt) < 1){
            printf("Neplatny vstup!\n");
            while(getchar() != '\n');
        }
  
        while(getchar() != '\n');
    }
    return 0;
}