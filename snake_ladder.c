#include<stdio.h>

//Basic Definition of each cell of the board.

typedef struct n
{
    int data;
    struct n* rand;
    struct n* next;
}node;

int h1_ladder[26] = {0};
int h1_snake[26] = {0};

node* h2_ladder[26];
node* h2_snake[26];

node* createNewNode(node*,int);
node* buildBoard();


//Building the board,i.e,building the links

node* buildBoard()
{
        int k = 0, l = 0;
        node* head = NULL;
        int i = 25;
        while(i >= 1)
        {
            head = createNewNode(head,i);
            h2_ladder[i] = head;
            h2_snake[i] = head;
            i--;
        }
        h2_snake[0] = NULL;
        h2_ladder[0] = NULL;

        h1_ladder[1] = 13;
        h1_ladder[4] = 14;
        h1_ladder[7] = 24;
        h1_ladder[8] = 12;
        h1_ladder[12] = 22;

        h1_snake[23] = 1;
        h1_snake[11] = 3;
        h1_snake[20] = 2;
        h1_snake[16] = 5;
        h1_snake[19] = 10;

        i = 1;
        node* source;
        node* dest;
        while(h2_ladder[i])
        {
            source = h2_ladder[i];
            dest = h2_ladder[h1_ladder[i]];
            if(dest)
                source->rand = dest;
            i++;
        }
        i = 1;
        while(h2_snake[i])
        {
            source = h2_snake[i];
            dest = h2_snake[h1_snake[i]];
            if(dest)
                source->rand = dest;
            i++;
        }
        return head;

}

// function to add new nodes to the list
node* createNewNode(node* head,int data)
{
    node* temp = (node*)malloc(sizeof(node));
    if(head == NULL)
    {
        head = temp;
        temp->data = data;
        temp->rand = NULL;
        temp->next = NULL;
        return head;
    }
    temp->data = data;
    temp->next = head;
    temp->rand = NULL;
    head = temp;
    return head;
}

//function to generate pseudo random values
int generateRandoms()
{
    int lower = 2,upper = 6;
    int num = (rand() + lower) % (upper + 1);
    return num;
}


//the actual function to play the game.
void play(node* head)
{
    int activePlayer = 0;
    int n[2] = {0};
    do
    {
                int r,k;
                printf("press 1 to roll:\n");
                scanf("%d",&r);
                if(r == 1)
                {
                    k = generateRandoms();
                    printf("Player %d rolled: %d\n",activePlayer+1,k);
                    n[activePlayer] = n[activePlayer] + k;
                    if (n[activePlayer] > 25)
                    {
                       n[activePlayer] = n[activePlayer] - k;
                        printf("Player %d present location: %d\n\n",activePlayer+1,h2_ladder[n[activePlayer]]->data);
                        n[activePlayer] = h2_ladder[n[activePlayer]]->data;
                        continue;
                    }
                    node* p1 = h2_ladder[n[activePlayer]]->rand;
                    node* p2 = h2_snake[n[activePlayer]]->rand;
                    if(p1)
                    {
                        printf("Player %d present location: %d\n\n",activePlayer+1,p1->data);
                        n[activePlayer] = p1->data;
                    }
                    else if(p2)
                    {
                        printf("Player %d present location: %d\n\n",activePlayer+1,p2->data);
                        n[activePlayer] = p2->data;
                    }
                    else
                    {
                        printf("Player %d present location: %d\n\n",activePlayer+1,h2_ladder[n[activePlayer]]->data);
                        n[activePlayer] = h2_ladder[n[activePlayer]]->data;
                    }
                }
                else
                    printf("You can roll only with button r");
                if(n[activePlayer] == 25)
                {
                    printf("Player %d Won",activePlayer+1);
                    break;
                }
                activePlayer = (activePlayer == 0) ? 1 : 0;


            }while(1);
}




int main()
{
    printf("Building board--->\n");
    node* head = buildBoard();
    node* curr = head;
    while(curr)
    {
        printf("%d-->",curr->data);
        curr = curr->next;
    }
    printf("\n\n\n");
    play(head);
}
