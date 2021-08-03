/*
 * Elliptic Curve Cryptography class header file
 *   this header file implements ECC class, which is designed to work with Elliptic Curve Cryptography
 *
 *
 * Functionality:
 *    int * encodeMessage(int message) -- encodes user message. Returns pointer to array of 4 ellements
 *    int decodeMessage(int cyperText[4]) -- decodes cyperText and returns int - message
 *
 */
#include <cstdio>
#include <iostream>
#include <time.h>
#include "ec_utils.h"

using namespace std;

#define MAX_Y 329

// The first coordinate is concidered to be the value, the second one is ignored
class ECC {
	public:
		int a = 4;	              // elliptic curve coefficient
		int b = 20;	              // elliptic curve coefficient
		static const int p = 329;	  // prime number to provide finite field

		int points[p*p][2];       // points satisfying the curve


		int PrivKey = 19;           // Private Key of Receiver

		int PubKey[2] = {0,0};	  // Public key of Receiver
		int k = 19;	              // Random Number required for Encoding
		int Pbase[2] = {0,0};	  // Base point

		int *temp;

		int P[2];       // kG, k*Pbase - first part of cyper text
		int R[2];       // Pm+kPb, k*PubKey + message - second part of cyper text

		ECC(){
			generate();

            // Deciding the base point
			Pbase[0] = points[7][0];
			Pbase[1] = points[7][1];

			temp=genKey(PrivKey,Pbase);     // generate public key, which is multiplication
			PubKey[0] = *temp;
			PubKey[1] = *(temp+1);
		}

		int * encodeMessage(int userMessage) {
			temp = ec::sclr_mult(k,Pbase,a,p);
			P[0] = *temp;
			P[1] = *(temp+1);

            int message[2];
            message[0] = userMessage;
            message[1] = 122;
            // message[1] = 1 + rand() % MAX_Y;

			int Q[2];          // k*PubKey, interim result when calculating second part of cyper text
			temp = ec::sclr_mult(k,PubKey,a,p);
			Q[0] = *temp;
			Q[1] = *(temp+1);

			temp = ec::add(message,Q,a,p);
			R[0] = *temp;
			R[1] = *(temp+1);

            int *encoded = (int*) malloc(4*sizeof(int)); 

            *encoded     = P[0];
            *(encoded+1) = P[1];
            *(encoded+2) = R[0];
            *(encoded+3) = R[1];

            return encoded;
		}

		int decodeMessage(int cyperText[4]) {
			int O[2];           // nBkG

            int P[2] = {cyperText[0], cyperText[1]};
			temp = ec::sclr_mult(PrivKey,P,a,p);
			O[0] = *temp;
			O[1] = p - *(temp+1);

            int R[2] = {cyperText[2], cyperText[3]};
			temp = ec::add(R,O,a,p);
			O[0] = *temp;
			O[1] = *(temp+1);

            return O[0];
		}

		void generate() {   // computes all integer points on curve in range
            srand(time(0));
			int rhs,lhs,i=0;
			for(int x = 0; x < p; x++)
			{
				rhs=((x*x*x)+(a*x)+b)%p;
				for(int y = 0; y < p; y++)
				{
					lhs = (y*y)%p;
					if (lhs==rhs)
					{
						points[i][0]=x;
						points[i][1]=y;
						i+=1;
					}
				}
			}
		}

		int * genKey(int X,int P[2]){   // generate public key, which is multiplication
			int *temp;
			int *Q = (int*) malloc(2*sizeof(int));
			temp=ec::sclr_mult(X,P,a,p);
			Q[0]=*temp;
			Q[1]=*(temp+1);
			return Q;
		}

};
