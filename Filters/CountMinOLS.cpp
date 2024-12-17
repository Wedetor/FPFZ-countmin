#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>

using namespace std;

class OLSFilter {

    private: 

        // n = Number of elements.
        // d = Maximal set size for FPFZ.
        // s = sqrt(n). Value used to create OLS

        unsigned int n;
        unsigned int d;
        unsigned int s;

        vector<vector<vector<unsigned int>>> squares;
        map<unsigned int, vector<bool>> filter;

        // ======= v OLS factory v ==========================

        void fillSquares(vector<vector<vector<unsigned int>>> &squares){
            unsigned int offset;
            unsigned int increment = 1;
            unsigned int startingPoint = 0;
            bool reverseFlag = false;

            for(int i = 0; i <= d; i++){
                vector<vector<unsigned int>> square;
                square.resize(s);
                offset = 0;

                for(unsigned int j = 0; j < s; j++){
                    square[j].resize(s);
                }

                switch(i){
                    case 0:
                        for(unsigned int j = 0; j < s; j++){
                            for(unsigned int k = 0; k < s; k++){
                                square[j][k] = k;
                            }
                        }
                        break;
                    case 1:
                        for(unsigned int j = 0; j < s; j++){
                            for(unsigned int k = 0; k < s; k++){
                                square[j][k] = j;
                            }
                        }
                        break;
                    default:
                        if(!reverseFlag) {
                            for(unsigned int j = 0; j < s; j++){
                                for(unsigned int k = 0; k < s; k++){
                                    square[j][k] = (k + offset + startingPoint) % s;
                                }
                                offset = offset + increment;
                            }

                            increment++;

                            if(increment % s == 0){
                                startingPoint++;
                                if(startingPoint % s == 0){
                                    reverseFlag = true;
                                    startingPoint = 0;
                                    offset = 0;
                                    increment = 1;
                                    continue;
                                }
                                increment++;
                            }
                        } else {
                            for(unsigned int j = 0; j < s; j++){
                                for(unsigned int k = 0; k < s; k++){
                                    square[j][s-1-k] = (k + offset + startingPoint) % s;
                                }
                                offset = offset + increment;
                            }

                            increment++;

                            if(increment % s == 0){
                                startingPoint++;
                                if(startingPoint % s == 0){
                                    reverseFlag = true;
                                }
                                increment++;
                            }
                        }

                        

                }

                squares.push_back(square);
            }
        }

        // ======= ^ OLS factory ^ ===========================

        // ======= v Filter factory v ========================

        void filterBuild(map<unsigned int, vector<bool>> &filter){
            for(int i = 1; i <= n; i++){
                vector<bool> bitVector;
                bitVector.resize((d+1) * s);
                

                for(int currentSquareIndex = 0; currentSquareIndex < squares.size(); currentSquareIndex++){

                    bitVector[(squares[currentSquareIndex][(i-1) / s][(i-1) % s]) + (currentSquareIndex * s)] = 1;

                }

                filter.insert(pair<int, vector<bool>>(i, bitVector));
            }
        }

    public:

        void filterPrint(){
            map<unsigned int, vector<bool>>::iterator it;

            cout << "============OLS===============" << endl;
            for(it = filter.begin(); it != filter.end(); it++){
                cout << it->first << " ";
                if(it->first < 10)
                    cout << " ";

                for(int i = 0; i < (it->second).size(); i++){
                    cout << (it->second)[i] << " ";
                }

                cout << endl;
            }

            cout << "===============================" << endl;
        }

        // ======= ^ Filter factory ^ ========================

        OLSFilter(unsigned int numberOfElements, unsigned int maximalSetSize){
            n = numberOfElements;
            d = maximalSetSize;
            s = ceil(sqrt(n));

            fillSquares(this->squares);

            filterBuild(this->filter);
        }

        unsigned int getSketchSize(){
            return (d+1)*s;
        }

        vector<bool> getFilteredValue(unsigned int i){
            return filter[i];
        }

        void printSquares(){
            for(unsigned int i = 0; i < squares.size(); i++){
                for(unsigned int j = 0; j < squares[0].size(); j++){
                    for(unsigned int k = 0; k < squares[0].size(); k++){
                        cout << squares[i][j][k] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
};

