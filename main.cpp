#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include "Filters/CountMinEGH.cpp"
#include "Filters/CountMinOLS.cpp"
#include "Filters/CountMinPOL.cpp"
#include "CountMinBase.cpp"

using namespace std;

EGHFilter egh = EGHFilter(0, 0);
OLSFilter ols = OLSFilter(0, 0);
POLFilter pol = POLFilter(0, 0);
BaseCountMin base = BaseCountMin(false);

vector< vector<int> > baseSketchCountMin;
vector<int> sketchCountMin;
vector<bool> bitVector;

int main(){
    string filterType;
    short filterTypeSwitch;
    int n;
    int d;

    string input;

    while(true){
        cout << "Select filter to use:" << endl;
        cout << "\t BASE \n \t EGH \n \t OLS \n \t POL" << endl;
        cout << "Or enter EXIT to terminate program." << endl;
        cin >> filterType;

        if(filterType == "EXIT" || filterType == "exit"){
            break;
        }

        if(filterType == "BASE" || filterType == "base"){

            n = INT_MAX;

            base = BaseCountMin(true);
            baseSketchCountMin.resize(base.getSketchRows());
            for(int i = 0; i < baseSketchCountMin.size(); i++){
                baseSketchCountMin[i].resize(base.getSketchColumns());
            }
            filterTypeSwitch = 0;

        }

        if(filterType == "EGH" || filterType == "egh"){

            cout << "Number of elements (n): ";
            cin >> n;
            cout << "Maximal set size for FPFZ (d): ";
            cin >> d;
            cout << endl;

            egh = EGHFilter(n, d);
            sketchCountMin.resize(egh.getSketchSize());
            filterTypeSwitch = 1;       

        }

        if(filterType == "OLS" || filterType == "ols"){

            cout << "Number of elements (n): ";
            cin >> n;
            cout << "Maximal set size for FPFZ (d): ";
            cin >> d;
            cout << endl;

            ols = OLSFilter(n, d);
            sketchCountMin.resize(ols.getSketchSize());
            filterTypeSwitch = 2;       

        }

        if(filterType == "POL" || filterType == "pol"){
            
            cout << "Number of elements (n): ";
            cin >> n;
            cout << "Maximal set size for FPFZ (d): ";
            cin >> d;
            cout << endl;

            pol = POLFilter(n, d);
            sketchCountMin.resize(pol.getSketchSize());
            filterTypeSwitch = 3;
        }

        while(filterTypeSwitch > -1 && filterTypeSwitch < 4){
            
            cin >> input;
            if(input == "print" || input == "PRINT"){
                switch (filterTypeSwitch) {
                    case 0:
                        for(int i = 0; i < baseSketchCountMin.size(); i++){
                            for(int j = 0; j < baseSketchCountMin[i].size(); j++){
                                cout << baseSketchCountMin[i][j] << " ";
                            }
                            cout << endl;
                        }
                        break;

                    case 1:
                        egh.filterPrint();
                        break;

                    case 2:
                        ols.printSquares();
                        ols.filterPrint();
                        break;

                    case 3:
                        pol.filterPrint();
                        break;

                    default:
                        break;
                }
                
                continue;
            }
            if(input == "insert" || input == "INSERT"){
                int elementToInsert = -1;
                while(elementToInsert < 1 || elementToInsert > n){
                    cout << "Please, insert value to insert (greater or equal than 1, less of equal than " << n << "):";
                    cin >> elementToInsert;
                }
                
                switch (filterTypeSwitch) {
                    case 0:
                        base.insertElement(baseSketchCountMin, elementToInsert);
                        break;

                    case 1:
                        bitVector = egh.getFilteredValue(elementToInsert);
                        break;

                    case 2:
                        bitVector = ols.getFilteredValue(elementToInsert);
                        break;

                    case 3:
                        bitVector = pol.getFilteredValue(elementToInsert);
                        break;
                    
                    default:
                        break;
                }

                if(filterTypeSwitch == 0){
                    continue;
                } else {
                    for(int i = 0; i < bitVector.size(); i++){
                        if(bitVector[i]){
                            sketchCountMin[i]++;
                        }
                    }

                    continue;
                }
                
            }
            if(input == "query" || input == "QUERY"){
                int elementToSearch;
                cout << "Please, insert value to query: ";
                cin >> elementToSearch;

                if(elementToSearch < 1 || elementToSearch > n){
                    cout << "Element out of bounds";
                    continue;
                } else {

                    switch (filterTypeSwitch) {
                        case 0:
                            cout << elementToSearch << " was found " << base.queryElement(baseSketchCountMin, elementToSearch) << " times. \n";
                            break;

                        case 1:
                            bitVector = egh.getFilteredValue(elementToSearch);
                            break;

                        case 2:
                            bitVector = ols.getFilteredValue(elementToSearch);
                            break;
                        
                        case 3:
                            bitVector = pol.getFilteredValue(elementToSearch);
                            break;

                        default:
                            break;
                    }

                    if(filterTypeSwitch == 0){
                        continue;
                    } else {

                        unsigned int minCounter = UINT32_MAX;
                        bool notFound = false;

                        for(int i = 0; i < bitVector.size(); i++){
                            if(bitVector[i]){
                                if(sketchCountMin[i] == 0){
                                    cout << "Element not in sketch." << endl;
                                    notFound = true;
                                    break;
                                } else {
                                    if(sketchCountMin[i] < minCounter){
                                        minCounter = sketchCountMin[i];
                                    }
                                }
                            }
                        }

                        if(!notFound){
                            cout << elementToSearch << " was found " << minCounter << " times. \n";
                        }

                        continue;

                    }       
                }
            }
            if(input == "exit" || input == "EXIT"){
                break;
            }

            cout << "What would you like to do?" << endl;
            cout << "\t PRINT - Print the filter currently in use. \n"
                    "\t INSERT - Insert an element into the Count Min sketch using this filter. \n"
                    "\t QUERY - Ask if an element is inside the Count Min sketch, and if so, its frecency. \n"
                    "\t EXIT - Leave this section and try other filters." << endl;

        }

    }

    return 0;
}