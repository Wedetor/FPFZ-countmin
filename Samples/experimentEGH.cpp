#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include <time.h>
#include "../Filters/CountMinEGH.cpp"

using namespace std;

EGHFilter egh = EGHFilter(0, 0);

vector<int> sketchCountMin;
vector<bool> bitVector;
map<pair<string, string>, int> dictionaryOfIPs;
vector<pair<string, string>> indexOfIPs;
int n = 39; // We know the value
int d = 4; // Change according to experiment.

int main(){
    short spaceCounter;
    string stringFirstIP;
    string stringSecondIP;
    int numberOfPair = 1;
    clock_t t;
    clock_t totalTime;

    string input;

    ifstream test("CTU-IoT-Malware-Capture-60-1_all.txt");

    t = clock();
    egh = EGHFilter(n, d);
    sketchCountMin.resize(egh.getSketchSize());
    t = clock() - t;
    totalTime += t;

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
        
        it = dictionaryOfIPs.find(compare);
        if(it != dictionaryOfIPs.end()){
            t = clock();
            bitVector = egh.getFilteredValue(it->second);
            
            for(int i = 0; i < bitVector.size(); i++){
                if(bitVector[i]){
                    sketchCountMin[i]++;
                }
            }
            t = clock() - t;
            totalTime += t;

            continue;
        } else {
            dictionaryOfIPs[compare] = numberOfPair;

            t = clock();
            bitVector = egh.getFilteredValue(numberOfPair);
            
            for(int i = 0; i < bitVector.size(); i++){
                if(bitVector[i]){
                    sketchCountMin[i]++;
                }
            }
            t = clock() - t;
            totalTime += t;

            numberOfPair++;
            indexOfIPs.push_back(compare);

            continue;

        }

        
    }

    test.close();

    ofstream EGHFrequencyFile("CTU_60-1_EGH_FREQUENCY_D_10.txt");

    t = clock();
    for(int i = 1; i <= n; i++){
        bitVector = egh.getFilteredValue(i);
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
            cout << indexOfIPs[i-1].first << " -> " << indexOfIPs[i-1].second <<" was found " << minCounter << " times. \n";
            EGHFrequencyFile << indexOfIPs[i-1].first << " -> " << indexOfIPs[i-1].second << " frequency " << minCounter << endl;
        }
    }
    t = clock() - t;
    totalTime += t;

    cout << "it took " << ((float)totalTime)/CLOCKS_PER_SEC << " to finish." << endl;
    EGHFrequencyFile << "it took " << ((float)totalTime)/CLOCKS_PER_SEC << " to finish." << endl;

    EGHFrequencyFile.close();

    cout << "Done! :)" << endl;    

    return 0;
}