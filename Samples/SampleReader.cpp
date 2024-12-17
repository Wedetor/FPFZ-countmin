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

using namespace std;

map<pair<string, string>, int> realValuesIP;
map<pair<string, string>, int> filterValuesIP;
vector<long> errorVectorLimitless; 
vector<long> realVectorLimitless;
vector<long> errorVectorLimit; 
vector<long> realVectorLimit;

int main(){
    short spaceCounter;
    string stringFirstIP;
    string stringSecondIP;
    string frequency;

    string input;

    ifstream realFrequencyFile("CTU-60-1_Real_Frequency.txt");

    while (getline(realFrequencyFile, input)) {

        spaceCounter = 0;
        stringFirstIP.clear();
        stringSecondIP.clear();
        frequency.clear();

        for(int i = 0; i < input.size(); i++){
            if(spaceCounter == 0 && input[i] >= 'A'){
                break;
            }
            if(input[i] == ' '){
                spaceCounter++;
                continue;
            }
            if(spaceCounter == 0 && input[i] >= '0' && input[i] <= '9'){
                stringFirstIP.push_back(input[i]);
            }
            if(spaceCounter == 2 && input[i] >= '0' && input[i] <= '9'){
                stringSecondIP.push_back(input[i]);
            }
            if(spaceCounter == 4 && input[i] >= '0' && input[i] <= '9'){
                frequency.push_back(input[i]);
            }
        }
        
        if(spaceCounter > 0){
            pair<string, string> pairIP = pair<string, string>(stringFirstIP, stringSecondIP);

            realValuesIP[pairIP] = stoi(frequency, nullptr, 10);

        }

    }

    realFrequencyFile.close();

    ifstream filterFrequencyFile("CTU-60-1_OLS_FREQUENCY_D_100.txt");

    while (getline(filterFrequencyFile, input)) {

        spaceCounter = 0;
        stringFirstIP.clear();
        stringSecondIP.clear();
        frequency.clear();

        for(int i = 0; i < input.size(); i++){
            if(spaceCounter == 0 && input[i] >= 'A'){
                break;
            }
            if(input[i] == ' '){
                spaceCounter++;
                continue;
            }
            if(spaceCounter == 0 && input[i] >= '0' && input[i] <= '9'){
                stringFirstIP.push_back(input[i]);
            }
            if(spaceCounter == 2 && input[i] >= '0' && input[i] <= '9'){
                stringSecondIP.push_back(input[i]);
            }
            if(spaceCounter == 4 && input[i] >= '0' && input[i] <= '9'){
                frequency.push_back(input[i]);
            }
        }

        if(spaceCounter > 0){
            pair<string, string> pairIP = pair<string, string>(stringFirstIP, stringSecondIP);

            filterValuesIP[pairIP] = stoi(frequency, nullptr, 10);
        }
        
    }

    filterFrequencyFile.close();

    ofstream sampleFrequencyFile("CTU-60_OLS_100_SampleRead.txt");

    for (auto it = realValuesIP.begin(); it != realValuesIP.end(); ++it){
        auto compare = filterValuesIP.find(it->first);
        if(compare != filterValuesIP.end()){
            sampleFrequencyFile << it->first.first << " -> " << it->first.second << " difference " << compare->second - it->second << endl;
            cout << it->first.first << " -> " << it->first.second << " difference " << compare->second - it->second << endl;
            errorVectorLimit.push_back(compare->second - it->second);
            realVectorLimit.push_back(it->second);
            errorVectorLimitless.push_back(compare->second - it->second);
            realVectorLimitless.push_back(it->second);
        } else {
            cout << it->first.first << " -> " << it->first.second << " not found " << 0 - it->second << endl;
            sampleFrequencyFile << it->first.first << " -> " << it->first.second << " not found " << 0 - it->second << endl;
            errorVectorLimit.push_back(0 - it->second);
            realVectorLimit.push_back(it->second);
        }
    }

    float error = 0;

    for(int i = 0; i < errorVectorLimitless.size(); i++){
        error += abs(errorVectorLimitless[i]);
    }

    error = error / errorVectorLimitless.size();

    cout << "Error absoluto medio sin considerar el límite: " << error << endl;
    sampleFrequencyFile << "Error absoluto medio sin considerar el límite: " << error << endl;

    error = 0;

    for(int i = 0; i < errorVectorLimit.size(); i++){
        error += abs(errorVectorLimit[i]);
    }

    error = error / errorVectorLimit.size();

    cout << "Error absoluto medio considerando el límite: " << error << endl;
    sampleFrequencyFile << "Error absoluto medio considerando el límite: " << error << endl;

    error = 0;
    float relative = 0;

    for(int i = 0; i < errorVectorLimitless.size(); i++){
        relative = (float)(abs(errorVectorLimitless[i]))/realVectorLimitless[i];
        error += relative;
    }

    error *= 100;

    cout << "Error relativo medio sin considerar el límite: " << error << "%" << endl;
    sampleFrequencyFile << "Error relativo medio sin considerar el límite: " << error << "%" << endl;

    error = 0;

    for(int i = 0; i < errorVectorLimit.size(); i++){
        relative = (float)(abs(errorVectorLimit[i]))/realVectorLimit[i];
        error += relative;
    }

    error *= 100;

    cout << "Error relativo medio considerando el límite: " << error << "%" << endl;
    sampleFrequencyFile << "Error relativo medio considerando el límite: " << error << "%" << endl;

    sampleFrequencyFile.close();

    cout << "Done! :)" << endl;    

    return 0;
}