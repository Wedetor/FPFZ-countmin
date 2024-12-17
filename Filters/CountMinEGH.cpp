#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <set>

using namespace std;

class EGHFilter {

    // n = Number of elements.
    // d = Maximal set size for FPFZ.
    //
    // primeIndex = We might end up with a set
    // with more primes than neccesary. This tells us
    // the index of the last prime to use.
    // 
    // m = Sum of the k primes chosen.

    private :
        unsigned int n;
        unsigned int d;
        set<int64_t> primes;
        unsigned int primeIndex;
        unsigned int m = 0;
        map<unsigned int, vector<bool>> filter;

        string strMultiply(string nums1, string nums2) {
            unsigned int n = nums1.size();
            unsigned int m = nums2.size();
            string ans(n + m, '0');
            for(int i = n - 1; i >= 0; i--) {
                for(int j = m - 1; j >= 0; j--) {
                    unsigned int p = (nums1[i] - '0') * (nums2[j] - '0') + (ans[i + j + 1] - '0');
                    ans[i+j+1] = p % 10 + '0';
                    ans[i+j] += p / 10;
            }
            }
            for(unsigned int i = 0; i < m + n; i++) {
                if(ans[i] !='0') return ans.substr(i);
            }
            return "0";
        }

        string strPower(string base, unsigned int power) {
            if(power == 0)
                return "1";

            if(power == 1)
                return base;
            
            string powAns = strMultiply(base, base);
            
            for(unsigned int i = 3; i < power; i++){
                powAns = strMultiply(powAns, base);
            }

            return powAns;
        }

        // ======== v Prime factory v ===============================

        set<int64_t> primeCalculator(long long maxPrime){
            vector<bool> is_prime(maxPrime + 1, true);
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

        set<int64_t> primesMultiplied(string numberToCompare, unsigned int &primeIndex){
            set<int64_t> possibleAnswer;
            long long possibleMax = 10;
            unsigned int index;
            string currentProduct;
            bool complete = false;

            while(!complete){
                possibleAnswer = primeCalculator(possibleMax);
                index = 0;
                currentProduct = "1";
                for(auto prime: possibleAnswer){
                    currentProduct = strMultiply(currentProduct, to_string(prime));
                    index++;
                    if(currentProduct.size() >= numberToCompare.size() && currentProduct.compare(numberToCompare) >= 0){
                        complete = true;
                        break;
                    }
                }

                if(complete){
                    primeIndex = index;
                    return possibleAnswer;
                }

                possibleMax *= 2;
            }

            cout << "Something went wrong" << endl;
            return possibleAnswer;
        }

        unsigned int primesSum(set<int64_t> primes, unsigned int primeIndex){
            unsigned long long sum = 0;

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

        void filterBuild(map<unsigned int, vector<bool>> &filter){
            for(int i = 1; i <= n; i++){
                vector<bool> bitVector;
                bitVector.resize(m);
                unsigned int currentSumIndex = 0;
                unsigned int topSumIndex = 0;
                unsigned int offset;

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

                filter.insert(pair<unsigned int, vector<bool>>(i, bitVector));
            }
        }

        // ======== ^ Filter factory ^ ==============================

    public:

        void print(){
            map<unsigned int, vector<bool>>::iterator it;

            cout << "============EGH===============" << endl;
            for(it = this->filter.begin(); it != this->filter.end(); it++){
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

        EGHFilter(unsigned int numberOfElements, unsigned int maximalSetSize){
            n = numberOfElements;
            d = maximalSetSize;

            primes = primesMultiplied(strPower(to_string(n), d), this->primeIndex);
            m = primesSum(this->primes, this->primeIndex);

            filterBuild(this->filter);
        }

        map<unsigned int, vector<bool>> getFilter(){
            return filter;
        }

        int getSketchSize(){
            return m;
        }

        vector<bool> getFilteredValue(unsigned int i){
            return filter[i];
        }

};