//
// Created by Ki Ageng Satria Pamungkas on 5/2/18.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void add(vector<int> &v,vector<int> &w){
    uint64_t carry = 0;
    uint64_t sum;
    while(w.size()<v.size()){
        w.push_back(0);
    }
    for (uint64_t i = 0; i <w.size() ; ++i) {
        sum = v[i]+w[i] + carry;
        v[i] = sum % 10;
        carry =  sum /10;
    }
    while(carry != 0){
        if(w.size() == v.size()) {
            v.push_back(carry % 10);
        } else {
            sum = v[w.size()] + carry;
            v[w.size()] = sum % 10;
        }
        carry = carry/10;
    }
}
vector<int> multiply(vector<int> v, uint64_t x){
    uint64_t carry = 0;
    uint64_t prod = 0;
    for (uint64_t i = 0; i < v.size() ; ++i) {
        prod = ( v[i] * x ) + carry;
        v[i] = prod % 10;
        carry =  prod / 10;
    }
    while(carry != 0){
        v.push_back(carry % 10);
        carry = carry / 10;
    }
    return v;
}
int main() {
    string s1, s2;
    vector <int> firstNumber;
    vector <int> result;
    cin >> s1 >> s2;
    for (int i = 0; i < s1.size(); ++i) {
        firstNumber.insert(firstNumber.begin(), s1[i] - '0');
    }
    reverse(s2.begin(), s2.end());
    for (int i = 0; i < s2.size(); ++i) {
        uint64_t multiplier = s2[i] - '0';
        vector <int> multiplyResult = multiply(firstNumber, multiplier);
        for (int j = 1; j <= i; ++j) {
            multiplyResult.insert(multiplyResult.begin(), 0);
        }
        add(multiplyResult, result);
        result = multiplyResult;
    }
    reverse(result.begin(), result.end());
    cout << "Hasil : " ;
    for (int j = 0; j < result.size(); ++j) {
        cout << result[j];
    }
    cout << endl;
    cout << result.size() << " digit(s)" <<endl;
}