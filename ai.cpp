#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

const int HASH_TABLE_LIMIT = 35000;
const int PRIME_31 = 31;

struct review {
    string word = "";
    double size = 0;
    double rating = 0;
    double average = 0;
};

int hashIndex(const string &word) {
    int wordSize = word.size();
    unsigned hash = 0;
    
    for (int i = 0; i < wordSize; i++) {
        hash = (PRIME_31 * hash + int(word[i]));
    }
    
    return hash % HASH_TABLE_LIMIT;
}

int main() {
    review hashTable[HASH_TABLE_LIMIT];
    string fullReview;
    ifstream file;
    file.open("text.txt");

    if (!(file.is_open())) 
        throw runtime_error("Error in opening file");


    while (getline(file, fullReview)) {
        stringstream iss(fullReview);
        double rating;
        string word;

        iss >> rating;

        while (iss >> word) {
            int hash = hashIndex(word);
            while (true) {
                if (hashTable[hash].word == "") {
                    hashTable[hash].word = word;
                    hashTable[hash].size++;
                    hashTable[hash].rating += rating;
                    hashTable[hash].average = hashTable[hash].rating/hashTable[hash].size;
                    break;
                }
                else if (hashTable[hash].word == word) {
                    hashTable[hash].size++;
                    hashTable[hash].rating += rating;
                    hashTable[hash].average = hashTable[hash].rating/hashTable[hash].size;
                    break;
                }
                else {
                    hash = (hash + 1) % HASH_TABLE_LIMIT;
                }
            }            
        }
    }

    string userInput;
    cout << "Enter your review" << endl;
    getline(cin, userInput);
    stringstream userSS(userInput);
    string word;
    double totalAvg = 0;
    int count = 0;
    while (userSS >> word) {
        count++;
        int hash = hashIndex(word);
        while (true) {
            if (hashTable[hash].word == "") {
                hashTable[hash].word = word;
                hashTable[hash].size++;
                break;
            }
            else if (hashTable[hash].word == word) {
                totalAvg += hashTable[hash].average;
                break;
            }
            else {
                hash = (hash + 1) % HASH_TABLE_LIMIT;
            }
        }
    }

    totalAvg = totalAvg/count;
    totalAvg = totalAvg * 100000;
    totalAvg = fmod(totalAvg, 100000);
    totalAvg /= 20000;
    cout << totalAvg << endl;





    file.close();
    return 0;
}