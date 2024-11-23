#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include "CountMinEGH.cpp"

using namespace std;

int main(){
    vector< map<int, int> > sketchCountMin;
    
    string filterType;
    int n;
    int d;

    string input;

    while(true){
        cout << "Select filter to use:" << endl;
        cout << "\t BASE \n \t EGH \n \t OLS \n \t POL" << endl;
        cin >> filterType;

        if(filterType == "EGH" || filterType == "egh"){
            vector<int> sketchCountMin;

            cout << "Number of elements (n): ";
            cin >> n;
            cout << "Maximal set size for FPFZ (d): ";
            cin >> d;
            cout << endl;

            EGHFilter egh = EGHFilter(n, d);
            sketchCountMin.resize(egh.getSketchSize());
            
            
            while(true){
                cout << "What would you like to do?" << endl;
                cout << "\t PRINT - Will print the filter. \n"
                        "\t INSERT - Insert an element into the Count Min sketch using this filter. \n"
                        "\t QUERY - Ask if an element is inside the Count Min sketch, and if so, its frecency. \n"
                        "\t EXIT - Leave this section and try other filters." << endl;
                cin >> input;
                if(input == "print" || input == "PRINT"){
                    egh.filterPrint();
                    continue;
                }
                if(input == "insert" || input == "INSERT"){
                    int elementToInsert = -1;
                    while(elementToInsert < 1 || elementToInsert > n){
                        cout << "Please, insert value to insert (greater or equal than 1, less of equal than " << n << "):";
                        cin >> elementToInsert;
                    }
                    
                    vector<bool> bitVector = egh.getFilteredValue(elementToInsert);

                    for(int i = 0; i < bitVector.size(); i++){
                        if(bitVector[i]){
                            sketchCountMin[i]++;
                        }
                    }
                    continue;
                }
                if(input == "query" || input == "QUERY"){
                    int elementToSearch;
                    cout << "Please, insert value to query: ";
                    cin >> elementToSearch;

                    if(elementToSearch < 1 || elementToSearch > n){
                        cout << "Element out of bounds";
                        continue;
                    } else {
                        vector<bool> bitVector = egh.getFilteredValue(elementToSearch);
                        int minCounter = 999;
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
                if(input == "exit" || input == "EXIT"){
                    break;
                }
            }
        }

        break;
    }

    

    return 0;
}