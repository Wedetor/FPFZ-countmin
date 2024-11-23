#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>

using namespace std;

struct OLSFilter {

    // n = Number of elements.
    // d = Maximal set size for FPFZ.
    // s = sqrt(n). Value used to create OLS

    int n;
    int d;
    int s;

    vector<vector<vector<int>>> squares;
    map<int, vector<bool>> filter;

    // ======= v OLS factory v ==========================

    void fillSquares(vector<vector<vector<int>>> &squares, int s, int d){
        int offset;
        int increment = 1;
        int startingPoint = 0;

        for(int i = 0; i <= d; i++){
            vector<vector<int>> square;
            square.resize(s);
            offset = 0;

            for(int j = 0; j < s; j++){
                square[j].resize(s);
            }

            switch(i){
                case 0:
                    for(int j = 0; j < s; j++){
                        for(int k = 0; k < s; k++){
                            square[j][k] = k;
                        }
                    }
                    break;
                case 1:
                    for(int j = 0; j < s; j++){
                        for(int k = 0; k < s; k++){
                            square[j][k] = j;
                        }
                    }
                    break;
                default:
                    for(int j = 0; j < s; j++){
                        for(int k = 0; k < s; k++){
                            square[j][k] = (k + offset + startingPoint) % s;
                        }
                        offset = offset + increment;
                    }

                    increment++;

                    if(increment % s == 0){
                        startingPoint++;
                        increment++;
                    }
            }

            squares.push_back(square);
        }
    }

    void printSquares(){
        for(int i = 0; i < this->squares.size(); i++){
            for(int j = 0; j < this->squares[0].size(); j++){
                for(int k = 0; k < this->squares[0].size(); k++){
                    cout << squares[i][j][k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    // ======= ^ OLS factory ^ ===========================

    // ======= v Filter factory v ========================

    void filterBuild(map<int, vector<bool>> &filter, vector<vector<vector<int>>> squares, int n, int d, int s){
        for(int i = 1; i <= n; i++){
            vector<bool> bitVector;
            bitVector.resize((d+1) * s);
            

            for(int currentSquareIndex = 0; currentSquareIndex < squares.size(); currentSquareIndex++){

                bitVector[(squares[currentSquareIndex][(i-1) / s][(i-1) % s]) + (currentSquareIndex * s)] = 1;

            }

            filter.insert(pair<int, vector<bool>>(i, bitVector));
        }
    }

    void filterPrint(){
        map<int, vector<bool>>::iterator it;

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

    OLSFilter(int numberOfElements, int maximalSetSize){
        this->n = numberOfElements;
        this->d = maximalSetSize;
        this->s = ceil(sqrt(n));

        fillSquares(this->squares, this->s, this->d);

        filterBuild(this->filter, this->squares, this->n, this->d, this->s);
    }

    int getSketchSize(){
        return (d+1)*s;
    }

    vector<bool> getFilteredValue(int i){
        return this->filter[i];
    }
    
};

