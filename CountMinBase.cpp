#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include "smhasher_copy/MurmurHash3.cpp"

using namespace std;

struct BaseCountMin {

    vector<int> seeds;
    float columns;
    float epsilon;
    float hashAmmount;
    float gamma;

    void fillRandomSeed(){
        int it = 0;
        int possibleRand;
        bool validRand = false;

        srand(time(NULL));

        while(it < seeds.size()){
            validRand = true;
            possibleRand = rand();
            for (int j = 0; j < seeds.size(); j++){
                if( seeds[j] == possibleRand ){
                    validRand = false;
                    break;
                }
            }
            if(validRand) {
                seeds[it] = possibleRand;
                it++;
            }
        }

    }

    void hashFunction(int &elementToHash, unsigned int seedToUse, unsigned int &value){
        MurmurHash3_x86_32(&elementToHash, sizeof(elementToHash), seedToUse, &value);
    }

    BaseCountMin(bool construct){
        if(!construct){
            return;
        }

        cout << "Epsilon (value between 0.01 and 1): ";
        cin >> epsilon;
        cout << "Gamma (value between 0 and 1): ";
        cin >> gamma;

        columns = ceil((float)2 / epsilon);
        hashAmmount = ceil((log2( (float)1 / gamma) ));

        seeds.resize(hashAmmount);
        fillRandomSeed();
    }

    void insertElement (vector< vector<int> > &sketch, int elementToInsert){
        unsigned int indexToSum;
            
        for(int i = 0; i < sketch.size(); i++){
            unsigned int seedToUse = seeds[i];

            hashFunction(elementToInsert, seedToUse, indexToSum);
            
            sketch[i][(indexToSum % (int)columns)]++;

        }
    }

    int queryElement (vector< vector<int> > &sketch, int elementToSearch){
        unsigned int indexToSearch;
        int minCounter = INT_MAX;

        for(int i = 0; i < sketch.size(); i++){
            unsigned int seedToUse = seeds[i];

            hashFunction(elementToSearch, seedToUse, indexToSearch);
            if(sketch[i][indexToSearch % (int)columns] < minCounter)
                minCounter = sketch[i][indexToSearch % (int)columns];
            
        }

        return minCounter;
    }

    int getSketchColumns(){
        return columns;
    }

    int getSketchRows(){
        return hashAmmount;
    }

};