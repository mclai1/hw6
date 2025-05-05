#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0,0,0,0,0};
        std::string x = k;
        for (int i=4; i>=0; --i){
            if (x.length() == 0){
                break;
            }
            int a[6] = {0,0,0,0,0,0};
            // If the string is longer than 6, take the last 6 chars
            if (x.length() >= 6){
                std::string temp = x.substr(x.length()-6, 6);
                for (int j=0; j<6; ++j){
                    a[j] = letterDigitToNumber(temp[j]);
                }
                x = x.substr(0, x.length()-6);
            }
            // If the string is shorter than 6, fill the extra spaces with 0
            else{
                for (int j=5; j>=0; --j){
                    if (x.length() == 0){
                        a[j] = 0;
                    }
                    else{
                        a[j] = letterDigitToNumber(x[x.length()-1]);
                        x = x.substr(0, x.length()-1);
                    }
                }
            }
            // Convert the 6 chars to a value
            w[i] = a[0]*pow(36,5) + a[1]*pow(36,4) + a[2]*pow(36,3) + a[3]*pow(36,2) + a[4]*36 + a[5];
        }
        // Hash the values together
        return (w[0]*rValues[0] + w[1]*rValues[1] + w[2]*rValues[2] + w[3]*rValues[3] + w[4]*rValues[4]);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Convert letters
        if (std::isalpha(letter)){
            return std::tolower(letter) - 'a';
        }
        // Convert digits
        else if (std::isdigit(letter)){
            return letter - '0' + 26;
        }
        // Not a a-z or 0-9
        else{
            return -1;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
