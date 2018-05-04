//
// Created by Ki Ageng Satria Pamungkas on 5/4/18.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
void cutVectorIntoTwo(vector<int> input, vector<int> &v, vector<int> &w) {
    int n = input.size() / 2;
    int m = input.size() - n;
    v = input;
    w = input;
    v.resize(n);
    reverse(w.begin(), w.end());
    w.resize(m);
    reverse(w.begin(), w.end());
}
vector<int> add(vector<int> v, vector<int> w){
    int64_t carry = 0;
    int64_t sum;
    if(v.size() > w.size()) {
        while(w.size() < v.size()){
            w.push_back(0);
        }
        for (int64_t i = 0; i < w.size() ; ++i) {
            sum = v[i] + w[i] + carry;
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
            carry = carry / 10;
        }
        return v;
    } else {
        while(v.size() < w.size()){
            v.push_back(0);
        }
        for (int64_t i = 0; i < v.size() ; ++i) {
            sum = w[i] + v[i] + carry;
            w[i] = sum % 10;
            carry =  sum /10;
        }
        while(carry != 0){
            if(w.size() == v.size()) {
                w.push_back(carry % 10);
            } else {
                sum = w[v.size()] + carry;
                w[v.size()] = sum % 10;
            }
            carry = carry / 10;
        }
        return w;
    }
}
vector<int> decrease(vector<int> v, vector<int> w) {
    int64_t sum;
    while(w.size() < v.size()){
        w.push_back(0);
    }
    while(v.size() < w.size()){
        v.push_back(0);
    }
    for (int64_t i = 0; i < w.size() ; ++i) {
        if (v[i] < w[i]) {
            v[i] = v[i] + 10;
            v[i] = v[i] - w[i];
            v[i + 1] =  v[i + 1] - 1;
        } else {
            v[i] = v[i] - w[i];
        }
    }
    return v;
}
vector<int> multiply(vector<int> v, int64_t x){
    int64_t carry = 0;
    int64_t prod = 0;
    for (int64_t i = 0; i < v.size() ; ++i) {
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
vector<int> karatsuba(vector<int> numOne, vector<int> numTwo) {
    if ((numOne.size() == 1) or (numTwo.size() == 1)) {
        return numOne.size() > numTwo.size() ? multiply(numOne, numTwo[0]) : multiply(numTwo, numOne[0]);
    } else {
        int n = numOne.size() > numTwo.size()? numOne.size()  / 2 : numTwo.size() / 2;
        vector <int> numOneFirstHalf, numOneSecondHalf, numTwoFirstHalf, numTwoSecondHalf, x1, x2, x3, middle, damnedNumber;
        cutVectorIntoTwo(numOne, numOneSecondHalf, numOneFirstHalf);
        cutVectorIntoTwo(numTwo, numTwoSecondHalf, numTwoFirstHalf);
        x1 = karatsuba(numOneFirstHalf, numTwoFirstHalf);
        x2 = karatsuba(add(numOneFirstHalf, numOneSecondHalf), add(numTwoFirstHalf, numTwoSecondHalf));
        x3 = karatsuba(numOneSecondHalf, numTwoSecondHalf);
        damnedNumber = add(x3, x1);
        middle = decrease(x2, damnedNumber);
        for (int j = 0; j < n * 2; ++j) {
            x1.insert(x1.begin(), 0);
        }
        for (int j = 0; j < n; ++j) {
            middle.insert(middle.begin(), 0);
        }
        return add(add(x1, middle), x3);
    }
}
int main() {
    string s1, s2;
    vector <int> firstNumber, secondNumber, result;
    cin >> s1 >> s2;
    for (int i = 0; i < s1.size(); ++i) {
        firstNumber.insert(firstNumber.begin(), s1[i] - '0');
    }
    for (int i = 0; i < s2.size(); ++i) {
        secondNumber.insert(secondNumber.begin(), s2[i] - '0');
    }
    result = karatsuba(firstNumber, secondNumber);
    reverse(result.begin(), result.end());
    cout << "Hasil : " ;
    for (int j = 0; j < result.size(); ++j) {
        cout << result[j];
    }
    cout << endl;
}