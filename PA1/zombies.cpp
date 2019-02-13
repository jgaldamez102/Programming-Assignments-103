
/********************************************************
 * CS 103 Zombie-pocalypse PA
 * Name: Joses Galdamez
 * USC email: jgaldame@usc.edu
 * Comments (you want us to know): This program takes in 
 *     inputs for population size and zombie size and uses 
 *     simulation and random functions to determine how long
 *     it takes for a population to become 100% infected.
 ********************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
    // Array with enough entries for the maximum population size possible.
    bool pop[MAXPOP]= {false};
    double night[MAXPOP];
    int N, k, M, seed;
    int nights=0, up=0;
    double avg=0;
    int min=100000, max=0;
    cout<< "Enter the following: N k M seed: " << endl;
    cin >> N >> k >> M >> seed;

    if ( k > N ){
        cout << "Invalid inputs, shutting down now! "<< endl;
        exit(0);
    }
    
    //Switching k amount of pop variables to "zombies"
    for (int i =0; i< k ; i++){
        pop[i]=true;
    }
    
    int realk=k;
    srand(seed);
    
    //For loop for M simulations
    for (int m=0; m<M; m++){
        k=realk;
        
        //While loop that runs until everyone is a zombie.
        while (k < N ){
            int temp=0;
            //Randomly choosing a new zombie
            for (int i=0;i<k;i++){
                pop[rand()%N]=true;
            }
            
            for (int j=0;j<N;j++){
                
                if (pop[j]==true){
                    temp++;
                    
                }
                k=temp;
                
            }
            nights ++;
            
        }
        
        //Resets the pop array to original bool variables.
        for (int r=realk;r<N;r++){
            pop[r]=false;
        }
        
        night[up]=nights;
        up++;
        
        //Finds max.
        if (nights >max){
            max=nights;
        }
        //Finds min.
        if (nights < min){
            min=nights;
        }
        nights=0;
        
    }
    //Finds Average.
    for (int i=0;i<M;i++){
        avg=avg + night[i];
    }
    avg=avg/M;
    
    
    cout<< "Average Nights: " << avg << endl
    << "Max Nights: " << max << endl
    << "Min Nights: " << min << endl;
    return 0;
}