/*
 * Elliptic Curve Utilities header file
 *
 * This header file implements functions to work with elliptic curves
 *    sclr_mult  -- multiply point of the elliptic curve by an integer
 *    add        -- add two points
 *    inverse
 */
#include <stdlib.h>

namespace ec {
    int * sclr_mult(int k,int point[2], int a, int p);
    int * add(int A[2],int B[2], int a, int p);
    int inverse(int num, int p);

    int * sclr_mult(int k,int P[2], int a, int p)	// ?? using LSB first algorithm ??
    {
        int *temp,i;
        int *Q = (int*) malloc(2*sizeof(int));
        Q[0]=0;
        Q[1]=0;
        for(i=31;i>=0;i--)
        {
            if((k>>i)&1)
                break;
        }
        int P_temp [2];
        P_temp[0] = P[0];
        P_temp[1] = P[1];
        for(int j=0;j<=i;j++)
        {
            if((k>>j)&1)
            {
                temp=add(Q,P,a,p);
                Q[0]=*temp;
                Q[1]=*(temp+1);
            }
            temp=add(P,P,a,p);
            P_temp[0]=*temp;
            P_temp[1]=*(temp+1);
        }
        return Q;
    }

    int * add(int A[2],int B[2], int a, int p)
    {
        int *C = (int*) malloc(2*sizeof(int));
        int x=0;
        if (A[0]==0 || A[1]==0)
        {
            return B;
        }
        if (B[0]==0 || B[1]==0)
        {
            return A;
        }
        if (A[1]==(p-B[1]))
        {
            return C;
        }
        if ((A[0]==B[0]) && (A[1]==B[1]))
        {
            x=((3*(A[0]*A[0]))+a)*inverse(2*A[1], p);
            C[0]=((x*x)-(2*A[0]))%p;
            C[1]=((x*(A[0]-C[0]))-A[1])%p;
        }
        else
        {
            x=(B[1]-A[1])*inverse(B[0]-A[0], p);
            C[0]=((x*x)-(A[0]+B[0]))%p;
            C[1]=((x*(A[0]-C[0]))-A[1])%p;
        }
        if (C[0]<0)
            C[0]=p+C[0];
        if (C[1]<0)
            C[1]=p+C[1];
        return C;
    }
    int inverse(int num, int p)
    {
        int i=1;
        if (num<0){
            num=p+num;
        }
        for (i=1;i<p;i++)
        {
            if(((num*i)%p)==1)
                break;
        }
        return i;
    }
}
