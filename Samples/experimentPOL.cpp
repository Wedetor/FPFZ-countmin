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
#include "../Filters/CountMinPOLFilterless.cpp"

using namespace std;

POLFilterless pol = POLFilterless(0, 0, 0);

vector<unsigned int> sketchCountMin;
vector<bool> bitVector;
map<pair<string, string>, unsigned int> dictionaryOfIPs;
vector<pair<string, string>> indexOfIPs;
unsigned int n = 2313441;
unsigned int n_RealValue = 39; // We know the value
unsigned int d = 30; // Change according to experiment.
unsigned int t = 50;
bool timeLimitExceded = false;

int main(){
    indexOfIPs.resize(n);
    short spaceCounter;
    string stringFirstIP;
    string stringSecondIP;
    unsigned int numberOfPair = 1;
    clock_t t;
    clock_t totalTime;

    string input;

    ifstream test("CTU-IoT-Malware-Capture-60-1_all.txt");

    t = clock();
    pol = POLFilterless(n, d, t);
    sketchCountMin.resize(pol.getSketchSize());
    t = clock() - t;
    totalTime = t;

    while (getline(test, input)) {

        if(((float)totalTime)/CLOCKS_PER_SEC > (float)10){
            timeLimitExceded = true;
            break;
        }

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
        map<pair<string, string>, unsigned int>::iterator it;
        
        it = dictionaryOfIPs.find(compare);

        if(it != dictionaryOfIPs.end()){
            t = clock();
            bitVector = pol.getFilteredValue(it->second);
            
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
            bitVector = pol.getFilteredValue(numberOfPair);
            
            for(int i = 0; i < bitVector.size(); i++){
                if(bitVector[i]){
                    sketchCountMin[i]++;
                }
            }
            t = clock() - t;
            totalTime += t;

            indexOfIPs[numberOfPair-1] = compare;
            numberOfPair++;
            

            continue;

        }

        
    }

    test.close();

    ofstream POLFrequencyFile("CTU-60-1_POL_FREQUENCY_D_test.txt");

    t = clock();
    for(unsigned int i = 1; i <= n_RealValue; i++){
        bitVector = pol.getFilteredValue(i);

        unsigned int minCounter = UINT32_MAX;

        for(unsigned int j = 0; j < bitVector.size(); j++){
            if(bitVector[j]){
                if(sketchCountMin[j] < minCounter){
                    minCounter = sketchCountMin[j];
                }
            }
        }

        cout << indexOfIPs[i-1].first << " -> " << indexOfIPs[i-1].second <<" was found " << minCounter << " times. \n";
        POLFrequencyFile << indexOfIPs[i-1].first << " -> " << indexOfIPs[i-1].second << " frequency " << minCounter << endl;

    }
    t = clock() - t;
    totalTime += t;

    cout << "Time Limit Exceded = " << timeLimitExceded << endl;
    POLFrequencyFile << "Time Limit Exceded = " << timeLimitExceded << endl;
    cout << "it took " << ((float)totalTime)/CLOCKS_PER_SEC << " to finish." << endl;
    POLFrequencyFile << "it took " << ((float)totalTime)/CLOCKS_PER_SEC << " to finish." << endl;
    cout << "The size of the filter is: " << (float)sizeof(pol) / (float)1024 << " KB" << endl;
    POLFrequencyFile << "The size of the filter is: " << (float)sizeof(pol) / (float)1024 << " KB" << endl;
    cout << "The size of the sketch is: " << sizeof(sketchCountMin) / (float)1024 << " KB" << endl;
    POLFrequencyFile << "The size of the sketch is: " << sizeof(sketchCountMin) / (float)1024 << " KB" << endl;

    POLFrequencyFile.close();

    cout << "Done! :)" << endl;    

    return 0;
}