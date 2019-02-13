/*******************************************************************************
 * CS 103 It's All A Blur PA
 * Name: Joses Galdamez
 * USC email:jgaldame@usc.edu
 * Comments (you want us to know):This programs manipulates different images 
 * with different filters using gaussian equations.  
 ******************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

//================================function prototypes here======================

void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);

void convolve(unsigned char out[][SIZE][3], unsigned char in[][SIZE][3] ,
              int N, double kernel[][11]);

void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);

void gaussian(double k[][11], int N, double sigma);

void gaussian_filter(unsigned char output [][SIZE][3], 
                     unsigned char input[][SIZE][3], int N, double sigma);

void unsharp(unsigned char output[][SIZE][3], unsigned char input[][SIZE][3],
             int N, double sigma, double alpha);

//============================Do not change code in main()======================

#ifndef AUTOTEST

int main(int argc, char* argv[])
{
    //First check argc
    if(argc < 3)
    {
        //we need at least ./filter <input file> <filter name> to continue
      cout << "usage: ./filter <input file> <filter name> <filter parameters>";
      cout << " <output file name>" << endl;
        return -1;
    }
    //then check to see if we can open the input file
    unsigned char input[SIZE][SIZE][RGB];
    unsigned char output[SIZE][SIZE][RGB];
    char* outfile;
    int N;
    double sigma, alpha;
    //double kernel[11][11];
    
    // read file contents into input array
    int status = readRGBBMP(argv[1], input);
    if(status != 0)
    {
        cout << "unable to open " << argv[1] << " for input." << endl;
        return -1;
    }
    //Input file is good, now look at next argument
    if( strcmp("sobel", argv[2]) == 0)
    {
        sobel(output, input);
        outfile = argv[3];
    }
    else if( strcmp("blur", argv[2]) == 0)
    {
        if(argc < 6)
        {
            cout << "not enough arguments for blur." << endl;
            return -1;
        }
        N = atoi(argv[3]);
        sigma = atof(argv[4]);
        outfile = argv[5];
        gaussian_filter(output, input, N, sigma);
    }
    else if( strcmp("unsharp", argv[2]) == 0)
    {
        if(argc < 7)
        {
            cout << "not enough arguments for unsharp." << endl;
            return -1;
        }
        N = atoi(argv[3]);
        sigma = atof(argv[4]);
        alpha = atof(argv[5]);
        outfile = argv[6];
        unsharp(output, input, N, sigma, alpha);
        
    }
    else if( strcmp("dummy", argv[2]) == 0)
    {
        //do dummy
        dummy(output, input);
        outfile = argv[3];
    }
    else
    {
        cout << "unknown filter type." << endl;
        return -1;
    }
    
    if(writeRGBBMP(outfile, output) != 0)
    {
        cout << "error writing file " << argv[3] << endl;
    }
    
}

#endif

//=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
    double k[11][11];
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            k[i][j] = 0;
        }
    }
    k[1][1] = 1;
    convolve(out, in, 3, k);
}


/*Convolves an input image with an NxN kernel to produce the output kernel*/
void convolve(unsigned char out[][SIZE][3], unsigned char in[][SIZE][3] ,
              int N, double kernel[][11]){
    
    int padded[SIZE+10][SIZE+10][RGB];// Use for input image with appropriate
    int temp[SIZE][SIZE][RGB];       
    // Use for the unclamped output pixel
    // values then copy from temp to out,
    // applying clamping
    
    //first set all of padded to 0 (black)
    for (int i=0; i< SIZE+10; i ++){
        for (int j=0; j<SIZE+10;j++){
            for (int k=0; k<RGB; k++){
                padded[i][j][k] = 0;
            }
        }
    }
    
    
    //Copies input into padding to appropriate locations
    for (int i=0; i< SIZE ; i ++){
        for (int j=0; j<SIZE; j ++){
            for (int k = 0; k < RGB ; k ++ ){
                padded[i + (N/2)][j+ (N/2)][k] = in[i][j][k];
            }
        }
    }
    
    //initializes temp pixels to 0
    for (int i=0; i< SIZE; i ++){
        for (int j=0; j<SIZE;j++){
            for (int k=0; k<RGB; k++){
                temp[i][j][k] = 0;
            }
        }
    }
    
    
    
    /* Perfoms convolve and place the results in in the temp array*/
    for(int y= 0 ;y<SIZE;y++)
        for(int x= 0 ;x<SIZE;x++)
            for(int k=0;k<3;k++)
                for(int i= -N/2; i<= (N/2) ; i++)
                    for(int j=-N/2 ; j<= (N/2) ; j++)
                        temp[y][x][k] += 
                        (int)(padded[y+i + (N/2)][x+j + (N/2)][k]*
                              kernel[(N/2) + i][(N/2) + j]);
    
    
    /* Clamping for loops*/ 
    for (int i=0;i <SIZE; i++){
        for (int j=0;j <SIZE; j++){
            for (int k =0; k<3; k++){
                 /*Clamping*/
                if (temp[i][j][k] <0){
                    temp[i][j][k] = 0;
                }
                else if (temp[i][j][k] > 255){
                    temp[i][j][k] = 255;
                }
                out [i][j][k]=(unsigned char)temp[i][j][k];
            }
        }
    }
    
    
    
}

/*Sobel Function*/ 
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
    double k[11][11];
    double s_h1[3][3] = { {-1, 0, 1},
                          {-2, 0, 2},
                          {-1, 0, 1} };
    double s_h2[3][3] = { {1, 0, -1},
                          {2, 0, -2},
                          {1, 0, -1} };
    //hold intemediate images
    unsigned char h1_soble[SIZE][SIZE][RGB]; 
    unsigned char h2_soble[SIZE][SIZE][RGB];
    
    for (int i = 0; i < 11; i++){
        for(int j=0; j < 11; j++){
            k[i][j] = 0;
        }
    }
    
    
    /* Copies in 1st 3x3 horizontal sobel kernel */
    for (int i=0; i <3; i++){
        for (int j=0; j<3; j++){
            k[i][j] = s_h1[i][j];
        }
    }
    
    /* Calls convolve to apply horizontal sobel kernel with h1_soble*/
    convolve(h1_soble, in, 3, k);
    
    /* Copies in 2nd 3x3 horizontal sobel kernel */
    for (int i=0; i <3; i++){
        for (int j=0; j<3; j++){
            k[i][j] = s_h2[i][j];
        }
    }
    
    
    /* Calls convolve to apply horizontal sobel kernel with h2_soble*/
    convolve(h2_soble, in, 3, k);
    
    int temp=0;
    /*Adds the two results (applying clamping) to produce the final output*/
    for (int i=0;i <SIZE; i++){
        for (int j=0;j <SIZE; j++){
            for (int x =0; x<RGB; x++){
                temp= (int)(h1_soble[i][j][x] + h2_soble[i][j][x]);
                 /*Clamping*/
                if (temp <0){
                    temp = 0;
                }
                else if (temp > 255){
                    temp = 255;
                }
                out [i][j][x] = (unsigned char)(temp);
            }
        }
    } 
}


/*Gaussian Function*/
void gaussian(double k[][11], int N, double sigma){
    double sum=0;
    for (int i=0;i < N; i++){
        for (int j=0; j <N ; j++){
            //long Gaussian equation
            k[i][j] = exp(-((pow((i-(N/2)),2)/(2*pow(sigma,2)))
                            +(pow((j-(N/2)),2)/(2*pow(sigma,2)))));
            sum += k[i][j];
        }
    }
    
    for (int i=0; i< N; i++){
        for (int j=0;j <N; j++){
            k[i][j] /= sum;
        }
    }
    /*displays numbers from functions*/ 
    /*for (int i=0;i <N; i++){
        for( int j=0; j<N; j++){
            cout << k[i][j] << " ";
        }
    }*/
    
}
/*Gaussian filter Function*/
void gaussian_filter(unsigned char output [][SIZE][3], 
                     unsigned char input[][SIZE][3], int N, double sigma){
    double k[11][11];
    for (int i=0; i<N ; i++){
        for (int j=0; j<N; j++){
            k[i][j] = 0;
        }
    }
    gaussian(k,N,sigma);
    convolve(output, input, N, k);
    
    
}
/*Unsharp Function*/ 
void unsharp(unsigned char output[][SIZE][3], 
         unsigned char input[][SIZE][3], int N,double sigma, double alpha){
    unsigned char b[SIZE][SIZE][3];
    gaussian_filter(b, input,  N,  sigma);
    int d[SIZE][SIZE][3];
    
    
    double temp = 0;
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE; j ++){
            for (int k=0;k<3; k++){
                d[i][j][k] = (int)input[i][j][k] - (int)b[i][j][k];
                
            }
        }
    }
    
    
    
    for (int i=0;i<SIZE; i++){
        for (int j=0;j<SIZE; j++){
            for (int k=0; k<3;k++){
                temp = (int)input[i][j][k] + (alpha* d[i][j][k]);
                /*Clamping*/
                if (temp < 0){
                    temp=0;
                }
                else if (temp > 255){
                    temp=255;
                }
                output[i][j][k] = (unsigned char)temp;
            }
        }
    }
    
    
}


