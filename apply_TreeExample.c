#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* childnodelist;
    int amountofchildnode;
    void (*branchTree)(struct node*, int*, int);
    void (*printTree)(struct node*, int);
}Tree;

int iscorrectlyroot(int numcheck, int* prohibitedtype, int amount);
Tree* newTree(int data);
void branchTree(Tree* myself, int* data, int amount);
void printTree(Tree* myself, int amount);
void reallyprintTree(Tree* myself, int* printedTable, int level);


int main(){
    int typeoffood, prohibitedtypeoffood, i = 0, j;

    scanf("%d", &typeoffood);
    scanf("%d", &prohibitedtypeoffood);
    fflush(stdin);

    int prohibitedtypeoffoodlists[prohibitedtypeoffood], foodlist[typeoffood];
    char input;
    Tree* rootTreelist[typeoffood];

    while(i < prohibitedtypeoffood){
        scanf("%c", &input);
        if(input >= '0' && input <= '9'){
            prohibitedtypeoffoodlists[i] = input - '0';
            i++;
        }
    }

    for(i = 0; i < typeoffood; i++){
        j = i + 1;
        foodlist[i] = j;
        if(iscorrectlyroot(foodlist[i], &(prohibitedtypeoffoodlists[0]), prohibitedtypeoffood)){
            rootTreelist[i] = newTree(j);
        }
        else{
            rootTreelist[i] = NULL;
        }
    }

    for(i = 0; i < typeoffood; i++){
        if(rootTreelist[i] != NULL){
            rootTreelist[i]->branchTree(rootTreelist[i], &(foodlist[0]), typeoffood - 1);
        }
    }
    for(i = 0; i < typeoffood; i++){
        if(rootTreelist[i] != NULL){
            rootTreelist[i]->printTree(rootTreelist[i], typeoffood);
        }
    }

    return 0;
}

Tree* newTree(int data){
    Tree* new = (Tree*)malloc(sizeof(Tree));
    new->amountofchildnode = 0;
    new->childnodelist = NULL;
    new->data = data;
    new->branchTree = branchTree;
    new->printTree = printTree;
    return new;
}

int iscorrectlyroot(int numcheck, int* prohibitedtype, int amount){
    int i;

    for(i = 0; i < amount; i++, prohibitedtype++){
        if(numcheck == *prohibitedtype){
            return 0;
        }
    }
    return 1;
}

void branchTree(Tree* myself, int* data, int amount){
    int newdata[amount], i = 0;
    Tree* tempchild;

    if(myself != NULL){
        while(i < amount){
            if(myself->data != *data){
                newdata[i] = *data;
                i++;
            }
            data++;
        }
        myself->childnodelist = (Tree*)malloc(sizeof(Tree) * amount);
        for(i = 0; i < amount; i++){
            tempchild = myself->childnodelist + i;
            tempchild->data = newdata[i];
            tempchild->amountofchildnode = 0;
            tempchild->childnodelist = NULL;
            tempchild->branchTree = branchTree;
            tempchild->printTree = printTree;
        }
        myself->amountofchildnode = amount;

        for(i = 0; i < amount; i++){
            myself->branchTree(myself->childnodelist + i, &(newdata[0]), amount - 1);
        }
    }
}

void printTree(Tree* myself, int amount){
    int printedTable[amount];

    reallyprintTree(myself, &(printedTable[0]), 0);
}

void reallyprintTree(Tree* myself, int* printedTable, int level){
    int i;
    
    *(printedTable + level) = myself->data;
    if(myself->amountofchildnode > 0){
        for(i = 0; i < myself->amountofchildnode; i++){
            reallyprintTree(myself->childnodelist + i, printedTable, level + 1);
        }
    }
    else{
        for(i = 0; i <= level; i++){
            printf("%d ", *(printedTable + i));
        }
        printf("\n");
    }

}

  
