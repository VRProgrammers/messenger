/*
 * Elliptic Curve Cryptography class header file
 *
 * This header file implements ECC class, which is designed to work with Elliptic Curve Cryptography
 * Key functions :
 *    encode
 *    decode
 */
#include <iostream>
#include "ec_utils.h"

using namespace std;

class ECC {
	public:
		int a=4;	// elliptic curve coefficient
		int b=20;	// elliptic curve coefficient
		static const int p=329;	// prime number to provide finite field

		int points[p*p][2];  // points satisfying the curve


		int PrivKey=11;  // Private Key of Receiver

		int PubKey[2]={0,0};	// Public key of Receiver
		int k=11;	// Random Number required for Encoding
		int Pbase[2]={0,0};	// Base point

		int *temp;
		int message[2];

		int P[2]; // kG, k*Pbase - first part of cyper text
		int R[2]; // Pm+kPb, k*PubKey + message - second part of cyper text

		ECC(){
			generate();
			Pbase[0]=points[5][0]; //Deciding the base point here
			Pbase[1]=points[5][1];
			temp=genKey(PrivKey,Pbase); // generate public key, which is multiplication
			PubKey[0]=*temp;
			PubKey[1]=*(temp+1);
			printf("\nThe Public Key is (%d,%d)\n",PubKey[0],PubKey[1]);

			message[0]=65;
			message[1]=122;
			printf("The message point is (%d,%d)\n",message[0],message[1]);
		}

		void encode(){
			temp=ec::sclr_mult(k,Pbase,a,p);
			P[0]=*temp;
			P[1]=*(temp+1);

			int Q[2]; // k*PubKey, interim result when calculating second part of cyper text
			temp=ec::sclr_mult(k,PubKey,a,p);
			Q[0]=*temp;
			Q[1]=*(temp+1);

			temp=ec::add(message,Q,a,p);
			R[0]=*temp;
			R[1]=*(temp+1);

			printf("The encrypted point is [(%d,%d),(%d,%d)]\n",P[0],P[1],R[0],R[1]);
		}

		void decode(){
			temp=ec::sclr_mult(PrivKey,P,a,p);
			int O[2];  // nBkG
			O[0]=*temp;
			O[1]=p-*(temp+1);

			temp=ec::add(R,O,a,p);
			O[0] = *temp;
			O[1] = *(temp+1);
			printf("The message point is (%d,%d)\n",O[0],O[1]);
		}

		void generate()   // computes all integer points on curve in range
		{
			int rhs,lhs,i=0;
			for(int x=0;x<p;x++)
			{
				rhs=((x*x*x)+(a*x)+b)%p;
				for(int y=0;y<p;y++)
				{
					lhs=(y*y)%p;
					if (lhs==rhs)
					{
						points[i][0]=x;
						points[i][1]=y;
						i+=1;
					}
				}
			}
			printf("\nNumber of points found on the curve is %d \n",i);
			for(int k=0;k<i;k++)
			{
				printf("%d(%d,%d)\n",(k),points[k][0],points[k][1]);
			}
		}

		int * genKey(int X,int P[2])   // generate public key, which is multiplication
		{
			int *temp;
			int *Q = (int*) malloc(2*sizeof(int));
			temp=ec::sclr_mult(X,P,a,p);
			Q[0]=*temp;
			Q[1]=*(temp+1);
			return Q;
		}

};
