# include <stdio.h>
# include <stdlib.h>
# include <math.h>

unsigned int hasnotARealAnswer (int numberA, 
                                    int numberB, 
                                    int numberC);
unsigned int hasAPerfectSquare (int numberA, 
                                    int numberB, 
                                    int numberC);
typedef struct structA
{
    float numerator;
    float denominator;
    struct structA* next;
}fration;

typedef struct structB
{
    float fistAnswer;
    float secondAnswer;
}realAnswer;

void rationalRootOperation (fration* head, 
                            int inputA, 
                            int inputC);
void findTheAnswer (fration* head, realAnswer* answerones, fration** answer);
fration findAnotherAnswer (fration* input, 
                            int numberA, 
                            int numberB);

void evaluationAnswer (int inputA, 
                        int inputB, 
                        int inputC, 
                        realAnswer* answerones);

int main ()
{
    int inputA, inputB, inputC;
    fration* head;
    head = malloc ( sizeof ( fration ) );
    fration* answer;
    fration anotherAnswer;
    realAnswer answerones;
    answer = NULL;

    scanf ( "%d %d %d", 
            &inputA, 
            &inputB, 
            &inputC );

    if ( hasnotARealAnswer ( inputA, inputB, inputC ) || 
            hasAPerfectSquare ( inputA, inputB, inputC ) ) printf ( "No Solution" );
    else
    {
        rationalRootOperation ( head, inputA, inputC );
        evaluationAnswer ( inputA, inputB, inputC, &answerones );
        findTheAnswer ( head, &answerones, &answer );
        if ( answer->numerator != 0 ) answer->numerator *= -1;
        answer->next = NULL;
        anotherAnswer = findAnotherAnswer ( answer, inputA, inputB );
        anotherAnswer.next = NULL;

        printf ( "%.0f %.0f %.0f %.0f", 
                    answer->denominator, 
                    answer->numerator, 
                    anotherAnswer.denominator, 
                    anotherAnswer.numerator );
    }

    return 0;
}

unsigned int hasnotARealAnswer (int numberA, 
                                    int numberB, 
                                    int numberC)
{
    return (numberB * numberB) - (4 * numberA * numberC) < 0;
}

unsigned int hasAPerfectSquare (int numberA, 
                                    int numberB, 
                                    int numberC)
{
    int test1, test2;

    test1 = (numberB * numberB) - (4 * numberA * numberC);
    test2 = test1;

    test2 = sqrt ( test2 );
    test2 *= test2;

    return test1 != test2;
}

void rationalRootOperation (fration* head, 
                            int inputA,  
                            int inputC)
{
    int tempA, tempB;
    fration* nextnode;
    fration* lastnode;

    nextnode = head;

    if ( inputC != 0 )
    {
        for ( tempA = 1; tempA <= inputA; tempA++ )
        {
            if ( inputA % tempA == 0 )
            {
                for ( tempB = inputC; tempB > 0; tempB-- )
                {
                    if ( inputC % tempB == 0 )
                    {
                        nextnode->numerator = tempB;
                        nextnode->denominator = tempA;
                        nextnode->next = (fration*)malloc ( sizeof ( fration ) );
                        nextnode = nextnode->next;
                    }
                }
                for ( tempB = inputC; tempB < 0; tempB++ )
                {
                    if ( inputC % tempB == 0 )
                    {
                        nextnode->numerator = -tempB;
                        nextnode->denominator = tempA;
                        nextnode->next = (fration*)malloc ( sizeof ( fration ) );
                        nextnode = nextnode->next;
                    }
                }
            }
        }

        for ( tempA = 1; tempA <= inputA; tempA++ )
        {
            if ( inputA % tempA == 0 )
            {
                for ( tempB = 1; tempB <= inputC; tempB++ )
                {
                    if ( inputC % tempB == 0 )
                    {
                        nextnode->numerator = -tempB;
                        nextnode->denominator = tempA;
                        nextnode->next = (fration*)malloc ( sizeof ( fration ) );
                        lastnode = nextnode;
                        nextnode = nextnode->next;
                    }
                }
                for ( tempB = -1; tempB >= inputC; tempB-- )
                {
                    if ( inputC % tempB == 0 )
                    {
                        nextnode->numerator = tempB;
                        nextnode->denominator = tempA;
                        nextnode->next = (fration*)malloc ( sizeof ( fration ) );
                        lastnode = nextnode;
                        nextnode = nextnode->next;
                    }
                }
            }
        }
    }
    else
    {
        nextnode->numerator = 0;
        nextnode->denominator = 1;
        nextnode->next = (fration*)malloc ( sizeof ( fration ) );
        lastnode = nextnode;
        nextnode = nextnode->next;
    }

    lastnode->next = NULL;
    free ( nextnode );
}

void findTheAnswer (fration* head, realAnswer* answerones, fration** answer)
{
    float testAnswer; 

    while ( head != NULL )
    {
        testAnswer = head->numerator / head->denominator;

        if ( testAnswer == answerones->fistAnswer || 
            testAnswer == answerones->secondAnswer)
        {
            if ( *answer != NULL )
            {
                if ( (*answer)->denominator != head->denominator )
                {
                    if ( head->denominator < (*answer)->denominator ) *answer = head;
                }
                else
                {
                    if ( head->numerator > (*answer)->numerator ) *answer = head;
                }
            }
            else *answer = head;
        }

        head = head->next;
    }
}

fration findAnotherAnswer (fration* input, 
                            int numberA, 
                            int numberB)
{
    fration anotherAnswer;
    int temp;
    
    anotherAnswer.denominator = numberA / input->denominator;
    temp = numberB - (anotherAnswer.denominator * input->numerator);
    anotherAnswer.numerator = temp / input->denominator;

    return anotherAnswer;
}

void evaluationAnswer (int inputA, int inputB, int inputC, realAnswer* answerones)
{
    answerones->fistAnswer = (-inputB + sqrt ( (inputB * inputB) - (4 * inputA * inputC) )) / (2 * inputA);
    answerones->secondAnswer = (-inputB - sqrt ( (inputB * inputB) - (4 * inputA * inputC) )) / (2 * inputA);
}
