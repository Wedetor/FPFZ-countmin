#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std;

class OLSFilterless {

    private:
        // n = Number of elements.
        // d = Maximal set size for FPFZ.
        // s = sqrt(n). Value used to create OLS

        unsigned int n;
        unsigned int d;
        unsigned int s;

        // ======= v OLS factory v ==========================

        // ======= ^ OLS factory ^ ===========================

    // ======= v Filter factory v ========================

    // ======= ^ Filter factory ^ ========================
    public:
        OLSFilterless(unsigned int numberOfElements, unsigned int maximalSetSize){
            this->n = numberOfElements;
            this->d = maximalSetSize;
            this->s = ceil(sqrt(n));

            if(s%2 == 0)
                s++;
        }

        unsigned long getSketchSize(){
            return (d+1)*s;
        }

        vector<bool> getFilteredValue(unsigned int elementToFilter){
            vector<bool> bitVector;
            bitVector.resize((d+1) * s);

            for(unsigned int currentSquareIndex = 0; currentSquareIndex <= d; currentSquareIndex++){

                switch(currentSquareIndex){
                    case 0:
                        bitVector[(elementToFilter-1) % s] = 1;
                        break;

                    case 1:
                        bitVector[((elementToFilter-1) / s) + currentSquareIndex*s] = 1;
                        break;

                    default:
                        if(currentSquareIndex < 1 + ((s-1) * s)){
                            bitVector[(((elementToFilter - 1 + (((elementToFilter - 1)/s) + (currentSquareIndex-2)/s))) % s) + currentSquareIndex*s] = 1;
                        } else {
                            bitVector[((s - (elementToFilter % s)) + ((((elementToFilter - 1)/s) + ((currentSquareIndex - (3 + ((s-1) * s) )/s)))) % s) + currentSquareIndex*s] = 1;
                        }
                        break;
                }
            }

            return bitVector;
        }
    
};

