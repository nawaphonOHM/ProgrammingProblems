#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct meme{
    char string[31];
    struct meme* next; 
}meme;

void assignfromlocation(char* word, meme** memeCollection);
void printmemes(meme** memes);

int main(){
    int amount, i, wordLocation;
    meme* memeCollection[26];
    char word[31];

    for(i = 0; i < 26; i++){
        memeCollection[i] = NULL;
    }

    scanf("%d", &amount);

    for(i = 0; i < amount; i++){  
        scanf("%*[ \n\r]%s", &word[0]);
        wordLocation = word[0] % 'a';
        assignfromlocation(&(word[0]), &(memeCollection[wordLocation]));
    }

    for(i = 0; i < 26; i++){
        printmemes(&(memeCollection[i]));
    }

    



    return 0;
}

void assignfromlocation(char* word, meme** memeCollection){
    char tempword[31];
    meme* tempaddress;

    if(*memeCollection != NULL){
        if(strcmp(&((*memeCollection)->string[0]), word) == 0){
            return;
        }
        if(strcmp(&((*memeCollection)->string[0]), word) > 0){
            tempaddress = (*memeCollection)->next;
            (*memeCollection)->next = (struct meme*)malloc(sizeof(meme));
            strcpy(&(tempword[0]), &((*memeCollection)->string[0]));
            strcpy(&((*memeCollection)->string[0]), word);
            strcpy(&(((*memeCollection)->next)->string[0]), &(tempword[0]));
            ((*memeCollection)->next)->next = tempaddress;
            return;
        }
        else{
            assignfromlocation(word, &((*memeCollection)->next));
        }
    }
    else{
        *memeCollection = (struct meme*)malloc(sizeof(meme));
        (*memeCollection)->next = NULL;
        strcpy(&((*memeCollection)->string[0]), word);
        return;
    }
}
void printmemes(meme** memes){
    if(*memes == NULL){
        return;
    }
    printf("%s\n", &((*memes)->string[0]));
    printmemes(&((*memes)->next));
}
