#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <set>
#include "smhasher_copy/MurmurHash3.cpp"

using namespace std;

// ======== v Prime factory v ===============================

set<int64_t> primeCalculator(long long numberToCompare){
    vector<bool> is_prime(numberToCompare + 1, true);
    set<int64_t> primes;
    is_prime[0] = is_prime[1] = false;
    int64_t p, pp, q, x;

    primes.insert(2);
    for (q = 4; q < is_prime.size(); q += 2)
        is_prime[q] = false;
    primes.insert(3);
    for (q = 9; q < is_prime.size(); q += 3)
        is_prime[q] = false;

    for (p = 5; p < is_prime.size(); p += 6) {
        if (is_prime[p]) {
            primes.insert(p);
            for (q = p * p; q < is_prime.size(); q += p)
                is_prime[q] = false;
        }

        pp = p + 2;
        if (is_prime[pp]) {
            primes.insert(pp);
            for (q = pp * pp; q < is_prime.size(); q += pp)
                is_prime[q] = false;
        }
    }

    return primes;
}

set<int64_t> primesMultiplied(long long numberToCompare, int &primeIndex){
    set<int64_t> possibleAnswer;
    set<int64_t> answer;
    int possibleSize = 10;
    int index;
    long long currentProduct;
    bool complete = false;

    while(!complete){
        possibleAnswer = primeCalculator(possibleSize);
        index = 0;
        currentProduct = 1;
        for(auto prime: possibleAnswer){
            currentProduct *= prime;
            index++;
            if(currentProduct >= numberToCompare){
                complete = true;
                break;
            }
        }

        
        if(complete){
            primeIndex = index;
            return possibleAnswer;
        }

        possibleSize *= 2;
    }

    cout << "Something went wrong" << endl;
    return possibleAnswer;
}

int primesSum(set<int64_t> primes, int primeIndex){
    int sum = 0;

    for(auto prime : primes){
        sum += prime;
        primeIndex--;
        if(primeIndex < 0) 
            break;
    }

    return sum;
}

// ======== ^ Prime factory ^ ===============================

// ======== v Filter factory v ==============================

void filterBuild(map<int, vector<bool>> &filter, set<int64_t> primes, int primeIndex, int n, int m){
    for(int i = 1; i <= n; i++){
        vector<bool> bitVector;
        bitVector.resize(m);
        int currentSumIndex = 0;
        int topSumIndex = 0;
        int offset;

        for(auto prime: primes){
            offset = 0;
            currentSumIndex = 0;

            for(auto primeSum: primes){
                if(currentSumIndex == topSumIndex)
                    break;
                offset += primeSum;
                currentSumIndex++;
            }

            bitVector[(i % prime) + offset] = 1;
            topSumIndex++;
        }

        filter.insert(pair<int, vector<bool>>(i, bitVector));
    }
}

void filterPrint(map<int, vector<bool>> filter){
    map<int, vector<bool>>::iterator it;

    cout << "============EGH===============" << endl;
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

// ======== ^ Filter factory ^ ==============================


int main(){
    vector<int> sketchCountMin;

    // n = Number of elements.
    // d = Maximal set size for FPFZ.
    //
    // primeIndex = We might end up with a set
    // with more primes than neccesary. This tells us
    // the index of the last prime to use.
    // 
    // m = Sum of the k primes chosen.
    int n;
    int d;
    int primeIndex;
    int m = 0;

    cout << "Number of elements (n): ";
    cin >> n;
    cout << "Maximal set size for FPFZ (d): ";
    cin >> d;

    set<int64_t> primes = primesMultiplied(pow(n, d), primeIndex);
    m = primesSum(primes, primeIndex);

    sketchCountMin.resize(m);

    map<int, vector<bool>> filter;

    filterBuild(filter, primes, primeIndex, n, m);

    filterPrint(filter);

    return 0;
}