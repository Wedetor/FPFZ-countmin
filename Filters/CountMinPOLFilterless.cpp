#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <climits>

using namespace std;

class POLFilterless {

    private:
        unsigned long long n;
        unsigned int d;
        unsigned int t;
        unsigned int root;
        unsigned int vectorSize;

        // ======= v Root factory v ======================


        // nthRoot taken from GeeksForGeeks
        long double nthRoot(unsigned long A, unsigned long N)
        {
            // initially guessing a random number between
            // 0 and 9
            long double xPre = rand() % 10;
        
            //  smaller eps, denotes more accuracy
            long double eps = 1e-4;
        
            // initializing difference between two
            // roots by INT_MAX
            long double delX = INT_MAX;
        
            //  xK denotes current value of x
            long double xK;
        
            //  loop until we reach desired accuracy
            while (delX > eps)
            {
                //  calculating current value from previous
                // value by newton's method
                xK = ((N - 1.0) * xPre +
                    (long double)A/pow(xPre, N-1)) / (long double)N;
                delX = abs(xK - xPre);
                xPre = xK;
            }
        
            return xK;
        }

        // ======= ^ Root factory ^ ======================

        // ======= v Coefficient factory v ====================

        vector<unsigned int> coefficientCalculator(unsigned int element){

            vector<unsigned int> coefficientsValues;
            unsigned int y = element;
            for (int i = 0; i <= (t-1)*d; i++){
                coefficientsValues.push_back(y % root);
                y = ceil((y - (y % root))/root);
            }
            return coefficientsValues;

        }

    // ======= ^ Coefficient factory ^ ===================

    // ======= v Filter factory v ========================

    // ======= ^ Filter factory ^ ========================
    public:
        POLFilterless(unsigned int numberOfElements, unsigned int maximalSetSize, unsigned int tValue){

            n = numberOfElements;
            d = maximalSetSize;
            t = tValue;

            if(numberOfElements == 0){
                return;
            }

            while((t-1)*d + 1 >= ceil(nthRoot(n, t))){
                cout << "Please, insert a new value for t: ";
                cin >> t;
            }

            root = nthRoot(n, t);

            if((double)root != nthRoot(n, t))
                root++;

            vectorSize = ((t-1)*d + 1)*root;
        }

        unsigned int getSketchSize(){
            return vectorSize;
        }

        vector<bool> getFilteredValue(unsigned int i){
            vector<unsigned int> coefficientsToUse = coefficientCalculator(i);

            vector<bool> bitVector;
            bitVector.resize(vectorSize);

            unsigned int offset = 0;
            for(unsigned int j = 0; j <= (t-1)*d; j++){
                unsigned long long int result = 0;
                for(unsigned int k = 0; k < coefficientsToUse.size(); k++){
                    result += coefficientsToUse[k]*pow(j, k);
                }
                result = result % root;
                bitVector[result + offset] = 1;
                offset += root;
            }

            return bitVector;
        }

};