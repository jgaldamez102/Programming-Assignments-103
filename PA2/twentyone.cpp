/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Joses Galdamez
 * USC email:jgaldame@usc.edu
 * Comments (you want us to know):This program recreates Blackjack, in which
 * you, the player, and the dealer, each get dealt two cards to begin with and
 * utilzes a while loop to understand different commands the player wants to
 * take in (hit, play again, sit). in the end, the program will determine who
 * wins the game based on the values given from the cards they have.
 ******************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;


const char suit[4] = {'H','S','D','C'};
const char* type[13] =
{"2","3","4","5","6","7",
    "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/* Permutes the deck of cards, effectively shuffling it.
 */
void shuffle(int cards[])
{
    for (int i=0;i<NUM_CARDS;i++){
        cards[i]=i;
    }
    for (int i=51;i>0;i--){
        int j=rand()%(i+1);
        int temp=cards[j];
        
        cards[j]=cards[i];
        cards[i]=temp;
    }
}

/* Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 */
void printCard(int id){
    cout << type[id%13] << "-" << suit[id/13];
}

/* Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id){
    return value[id%13];
}


/* Prints out each card in the hand separated by a space and
 * then prints a newline at the end.
 */
void printHand(int hand[], int numCards)
{
    for (int i=0;i<numCards;i++){
        printCard(hand[i]);
        cout << " ";
    }
    cout << endl;
}


/* Returns the total score of the provided hand.
 * ACES will be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    int total=0;
    bool ace=false;
    for (int i=0;i<numCards;i++){
        if (cardValue(hand[i]) ==11){
            ace=true;
        }
        total+=cardValue(hand[i]);
    }
    if (ace ==true && total>21){
        total-=10;
    }
    
    return total;
}

/* Simply displays the dealer's and the player's
 * total cards, using printCard() and printHand().
 */
void beginning(int dhand[],int phand[] ,int pposition){
    cout<<"Dealer: ? ";
    printCard(dhand[1]);
    cout<<endl << "Player: ";
    printHand(phand,pposition);
    
}
/* Displays command options, used primarily to
 * only display when needed to (player having 21)
 */
void enter(){
    cout << "Type 'h' to hit and 's' to stay: "<<endl;
}

/*Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);
    
    int cards[52];
    int dhand[9];
    int phand[9];
    //---------------------------------------
    // Do not change this code -- End
    //---------------------------------------
    
    
    shuffle(cards);
    
    //Declare counter variables, as well as string input.
    int cposition=0, dposition=0, pposition=0;
    string option;
    
    //Hands out the first two cards to each player.
    for (int i=0;i<4;i++){
        if (i%2==0){
            phand[pposition]=cards[i];
            pposition++;
            cposition++;
        }
        else if (i%2 ==1) {
            dhand[dposition]=cards[i];
            dposition++;
            cposition++;
        }
    }
    //Displays beginning cards and their values.
    beginning(dhand,phand,pposition);
    if (getBestScore(phand,pposition)==21){
        option="s";
    }
    else{
        enter();
        
        cin>>option;
    }
    //while loop that loops through every possible option.
    while (option == "h" || option == "s" || option == "y"){
        
        //if option 'h' is used.
        if(option =="h"){
            phand[pposition]=cards[cposition];
            cposition++;
            pposition++;
            cout <<"Player: ";
            printHand(phand,pposition);
            
            //If player busts.
            if(getBestScore(phand,pposition)>21){
                
                cout <<"Player busts" <<endl << "Lose "
                << getBestScore(phand,pposition)
                << " " << getBestScore(dhand,dposition)<<endl;
                cout<< endl << "Play again? [y/n]"<<endl;
                cin>>option;
            }
            //If player automatically has 21.
            else if(getBestScore(phand,pposition)==21){
                option="s";
            }
            else{
                getBestScore(phand,pposition);
                cout << "Type 'h' to hit and 's' to stay: " <<endl;
                cin>>option;
            }
        }
        
        //if option 's' is used
        else if (option == "s"){
            //adds cards to dealer until it hits 17.
            while (getBestScore(dhand,dposition) <17){
                dhand[dposition]=cards[cposition];
                cposition++;
                dposition++;
            }
            
            //If player automatically has 21.
            if (getBestScore(phand,pposition)==21){
                cout<< "Dealer: ";
                printHand(dhand,dposition);
                cout <<"Win "<<getBestScore(phand, pposition) << " "
                <<getBestScore(dhand,dposition) <<endl
                <<endl << "Play again? [y/n]" <<endl;
                cin>>option;
            }
            
            //If dealer busts
            else if(getBestScore(dhand,dposition)>21){
                cout <<"Dealer busts" <<endl << "Win "
                <<getBestScore(phand,pposition)
                <<" " << getBestScore(dhand,dposition)
                <<endl << "Play again? [y/n]" << endl;
                cin >>option;
            }
            
            //If neither busts.
            else if (getBestScore(dhand, dposition)>16
                     &&getBestScore(dhand,dposition)<22){
                if (getBestScore(phand,pposition)<
                    getBestScore(dhand,dposition)
                    ){
                    cout <<"Dealer: ";
                    printHand(dhand,dposition);
                    cout << endl <<"Lose "
                    <<getBestScore(phand,pposition) <<" "
                    <<getBestScore(dhand,dposition) << endl
                    << "Play again? [y/n]" <<endl;
                    cin>>option;
                }
                else if (getBestScore(dhand,dposition)
                         < getBestScore(phand,pposition)){
                    cout<< "Dealer: ";
                    printHand(dhand,dposition);
                    cout <<"Win "<<getBestScore(phand, pposition) << " "
                    <<getBestScore(dhand,dposition) <<endl
                    <<endl << "Play again? [y/n]" <<endl;
                    cin>>option;
                }
                else if (getBestScore(dhand,dposition)
                         == getBestScore(phand,dposition)){
                    cout << "Dealer: ";
                    printHand(dhand,dposition);
                    cout << endl << "Tie "
                    <<getBestScore(phand, pposition) << " "
                    <<getBestScore(dhand,dposition) << endl
                    << "Play again? [y/n]" <<endl;
                    cin>>option;
                }
                
            }
        }
        
        //if option 'y' is used
        else if (option == "y"){
            //Reinitialize all variables/arrays
            shuffle(cards);
            cposition=0,pposition=0,dposition=0;
            for (int j=0; j<9;j++){
                phand[j]=0;
                dhand[j]=0;
            }
            for (int i=0;i<4;i++){
                if (i%2==0){
                    phand[pposition]=cards[i];
                    pposition++;
                    cposition++;
                }
                else if (i%2 ==1) {
                    dhand[dposition]=cards[i];
                    dposition++;
                    cposition++;
                }
            }
            //Calls beginning function again.
            beginning(dhand,phand,pposition);
            enter();
            cin >>option;
            
            
        }
        //if anything else is pressed.
        else{
            break;
        }
    }
    
    return 0;
}

