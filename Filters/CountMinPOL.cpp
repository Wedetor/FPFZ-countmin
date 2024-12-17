#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <climits>

using namespace std;

class POLFilter {

    private:

        unsigned int n;
        unsigned int d;
        unsigned int t;
        unsigned int root;
        unsigned int vectorSize;
        map<unsigned int, vector<unsigned int>> coefficients;
        map<unsigned int, vector<bool>> filter;

        // ======= v Root factory v ======================


        // nthRoot taken from GeeksForGeeks
        double nthRoot(unsigned int A, unsigned int N)
        {
            // initially guessing a random number between
            // 0 and 9
            double xPre = rand() % 10;
        
            //  smaller eps, denotes more accuracy
            double eps = 1e-4;
        
            // initializing difference between two
            // roots by INT_MAX
            double delX = INT_MAX;
        
            //  xK denotes current value of x
            double xK;
        
            //  loop until we reach desired accuracy
            while (delX > eps)
            {
                //  calculating current value from previous
                // value by newton's method
                xK = ((N - 1.0) * xPre +
                    (double)A/pow(xPre, N-1)) / (double)N;
                delX = abs(xK - xPre);
                xPre = xK;
            }
        
            return xK;
        }

        // ======= ^ Root factory ^ ======================

        // ======= v Coefficient factory v ====================

        void coefficientCalculator(map<unsigned int, vector<unsigned int>> &coefficient){
            for(unsigned int i = 1; i <= n; i++){
                vector<unsigned int> coefficientsValues;
                int y = i;
                for (int j = 0; j <= (t-1)*d; j++){
                    coefficientsValues.push_back(y % root);
                    y = ceil((y - (y % root))/root);
                }
                coefficient.insert(pair<unsigned int, vector<unsigned int>>(i, coefficientsValues));
            }
        }

        // ======= ^ Coefficient factory ^ ===================

        // ======= v Filter factory v ========================

        void filterBuild(map<unsigned int, vector<bool>> &filter){
            map<unsigned int, vector<unsigned int>>::iterator itCoefficient;
            
            for(unsigned int i = 1; i <= n; i++){
                vector<bool> bitVector;
                bitVector.resize(vectorSize);

                itCoefficient = coefficients.find(i);
                vector<unsigned int> coefficientsToUse =  itCoefficient -> second;

                unsigned int offset = 0;
                for(unsigned int j = 0; j <= (t-1)*d; j++){
                    long long result = 0;
                    for(unsigned int k = 0; k < coefficientsToUse.size(); k++){
                        result += coefficientsToUse[k]*pow(j, k);
                    }
                    result = result % root;
                    bitVector[result + offset] = 1;
                    offset += root;
                }

                filter.insert(pair<unsigned int, vector<bool>>(i, bitVector));
            }
        }

    public:

        void filterPrint(){
            map<unsigned int, vector<bool>>::iterator it;

            cout << "============POL===============" << endl;
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

        POLFilter(unsigned int numberOfElements, unsigned int maximalSetSize){

            n = numberOfElements;
            d = maximalSetSize;

            if(numberOfElements == 0){
                return;
            }

            cout << "Set a value for t (3 is recommended): ";
            cin >> t;

            while((t-1)*d + 1 >= ceil(nthRoot(n, t))){
                cout << "Please, insert a new value for t: ";
                cin >> t;
            }

            root = nthRoot(n, t);

            if((double)root != nthRoot(n, t))
                root++;

            vectorSize = ((t-1)*d + 1)*root;
            
            coefficientCalculator(coefficients);

            filterBuild(filter);
        }

        unsigned int getSketchSize(){
            return vectorSize;
        }

        vector<bool> getFilteredValue(int i){
            return this->filter[i];
        }

};