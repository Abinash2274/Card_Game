#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Card
{
    int face;
    int suit;
};

struct Hand
{
    struct Card cards[5];
};

struct Deck
{
    struct Card dealtCards[52];
    int numCardsDealt;
};

struct Hand hand1,hand2;
struct Deck deck;

static const char *faceStrings[] = {"Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King","Ace"};
static const char *suitStrings[] = {"Red","Blue","Green","Yellow"};
static const char *rankStrings[] = {"High Card","SIngle Pair","Two Pair","Three of a kind","Straight","Flush","Full House","Four of a Kind","Straight Flush"};

void generateHands();
struct Card dealCard();
void analyzeHands();

int main(){
    deck.numCardsDealt=0;
    srand(time(NULL));
    generateHands();
    printHands();
    analyzeHands();
    return 0;
}

void generateHands(){
    int i;
    for (i=0;i<5;i++){
        hand1.cards[i] = dealCard();
        hand2.cards[i] = dealCard();
    }
}

struct Card dealCard()
{
    int i;
    int isUnique;
    struct Card cardToDeal;
    while(1){
        cardToDeal.face = rand()%13;
        cardToDeal.suit = rand()%4;
        isUnique = 1;
        for (i=0; i<deck.numCardsDealt; i++){
            if(deck.dealtCards[i].face == cardToDeal.face && deck.dealtCards[i].suit == cardToDeal.suit)
                isUnique = 0;
        }
        if(isUnique){
            deck.numCardsDealt++;
            deck.dealtCards[deck.numCardsDealt] = cardToDeal;
            return cardToDeal;
        }
    }
};

void printHands(){
    int i;
    printf("Player one has:\n");
    for (i=0; i<5; i++)
        printf("%s of %s\n", faceStrings[hand1.cards[i].face], suitStrings[hand1.cards[i].suit]);
    printf("\nPlayer two has:\n");
    for(i=0; i<5; i++)
        printf("%s of %s\n", faceStrings[hand2.cards[i].face], suitStrings[hand2.cards[i].suit]);
}
    
void analyzeHands(){
    int i,j;
    int hand1FaceCounts[13];
    int hand1SuitCounts[4];
    int hand2FaceCounts[13];
    int hand2SuitCounts[4];
    
    memset(hand1FaceCounts,0,sizeof(hand1FaceCounts));
    memset(hand1SuitCounts,0,sizeof(hand1SuitCounts));
    memset(hand2FaceCounts,0,sizeof(hand2FaceCounts));
    memset(hand2SuitCounts,0,sizeof(hand2SuitCounts));

    for(i=0;i<5;i++){
        hand1FaceCounts[hand1.cards[i].face]++;
        hand1SuitCounts[hand1.cards[i].face]++;
        hand2FaceCounts[hand2.cards[i].face]++;
        hand2SuitCounts[hand2.cards[i].face]++;
    }

    int h1Rank=0, h1Consec=0, h1Straight=0, h1Flush=0, h1Four=0, h1Three=0, h1Pairs=0;
    int h2Rank=0, h2Consec=0, h2Straight=0, h2Flush=0, h2Four=0, h2Three=0, h2Pairs=0;

    for (i=0; i<5; i++){
        if(hand1SuitCounts[i]==5)
           h1Flush=1;
        if(hand2SuitCounts[i]==5)
           h2Flush=1;
    }

    i=0;
    while (hand1FaceCounts[i]==0)
        i++;
    for (; i<3 && hand1FaceCounts[i]; i++)
        h1Consec++;
    if (h1Consec==5)
        h1Straight = 1;
    for(i=0; i<14; i++){
        if(hand1FaceCounts[i]==4)
           h1Four=1;
        if(hand1FaceCounts[i]==3)
           h1Three=1;
        if(hand1FaceCounts[i]==2)
           h1Pairs++;
    }

    for(i=0; i<14; i++){
        if(hand2FaceCounts[i]==4)
           h2Four=1;
        if(hand2FaceCounts[i]==3)
           h2Three=1;
        if(hand2FaceCounts[i]==2)
           h2Pairs++;
    }

    if (h1Straight && h1Flush)
        h1Rank=8;
    else if (h1Four)
        h1Rank=7;
    else if (h1Three && h1Pairs == 1)
        h1Rank=6;
    else if (h1Flush)
        h1Rank=5;
    else if (h1Straight)
        h1Rank=4;
    else if (h1Three)
        h1Rank=3;
    else if (h1Pairs == 2)
        h1Rank=2;
    else if (h1Pairs == 1)
        h1Rank=0;
    else
        h1Rank=0;
    
    
    if (h2Straight && h2Flush)
        h2Rank=8;
    else if (h2Four)
        h2Rank=7;
    else if (h2Three && h2Pairs == 1)
        h2Rank=6;
    else if (h2Flush)
        h2Rank=5;
    else if (h2Straight)
        h2Rank=4;
    else if (h1Three)
        h2Rank=3;
    else if (h2Pairs == 2)
        h2Rank=2;
    else 
        h2Rank=0;
    
    printf("\nPlayer one (1) has a %s. \n",rankStrings[h1Rank]);
    printf("Player two (2) has a %s. \n",rankStrings[h2Rank]);

    if(h1Rank>h2Rank)
       printf("Player 1 Wins!!!\n");
    else if(h2Rank>h1Rank)
       printf("Player 2 Wins!!!\n");
    else
       printf("Two Players..Its a tie!!!\n");
}