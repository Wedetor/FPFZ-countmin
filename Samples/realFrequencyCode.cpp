#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include "../Filters/CountMinEGH.cpp"

using namespace std;

/*EGHFilter egh = EGHFilter(0, 0);

vector<int> sketchCountMin;
vector<bool> bitVector;*/
map<pair<string, string>, int> realFrequency;

int main(){
    short spaceCounter;
    string stringFirstIP;
    string stringSecondIP;

    string input;

    ifstream test("chicago2016_withdata.txt");

    while (getline(test, input)) {
        spaceCounter = 0;
        stringFirstIP.clear();
        stringSecondIP.clear();

        for(int i = 0; i < input.size(); i++){
            if(input[i] == ' '){
                spaceCounter++;
                continue;
            }
            if(spaceCounter == 6){
                stringFirstIP.push_back(input[i]);
            }
            if(spaceCounter == 7){
                stringSecondIP.push_back(input[i]);
            }
            if(spaceCounter == 8){
                break;
            }
        }
        pair<string, string> compare = pair<string, string>(stringFirstIP, stringSecondIP);

        map<pair<string, string>, int>::iterator it;
        
        it = realFrequency.find(compare);
        if(it != realFrequency.end()){
            it->second++;
            continue;
        }

        realFrequency[compare] = 1;
    }

    test.close();

    cout << "Map done, making real Frequency" << endl;

    ofstream realFrequencyFile("chicago2016_Real_Frequency_Direction.txt");

    realFrequencyFile << "Size of realFrequency Map: " << (float)sizeof(realFrequency) / (float)1024 << " KB." << endl;

    for(auto map : realFrequency){
        realFrequencyFile << map.first.first << " -> " << map.first.second << " frequency " << map.second << endl;
    }

    realFrequencyFile.close();

    cout << "Done! :)" << endl;

    





    /*while(true){
        cout << "Number of elements (n): ";
        cin >> n;
        cout << "Maximal set size for FPFZ (d): ";
        cin >> d;

        egh = EGHFilter(n, d);
        sketchCountMin.resize(egh.getSketchSize());

        egh.filterPrint();

        int elementToInsert = -1;

        cout << "Please, insert value to insert (greater or equal than 1, less of equal than " << n << "):";
        cin >> elementToInsert;

        bitVector = egh.getFilteredValue(elementToInsert);
        break;


        for(int i = 0; i < bitVector.size(); i++){
            if(bitVector[i]){
                sketchCountMin[i]++;
            }
        }

            
        

        int elementToSearch;
        cout << "Please, insert value to query: ";
        cin >> elementToSearch;

        if(elementToSearch < 1 || elementToSearch > n){
            cout << "Element out of bounds";
            continue;
        } else {
            bitVector = egh.getFilteredValue(elementToSearch);
            break;
        }

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

                
    }*/
    

    

    return 0;
}