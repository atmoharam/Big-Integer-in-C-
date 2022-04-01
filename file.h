//
// Created by mido_ on 5/10/2021.
//

#ifndef DS_ASS_PROB_1_BIGDECIMALINT_H
#define DS_ASS_PROB_1_BIGDECIMALINT_H
#include "cstring"
using namespace std;
#include <iostream>
#include "cmath"
#include "algorithm"
#include "vector"

class BigDecimalInt {
public:
    vector<int> numberOfDigits;
    bool negative = false;
    string numbers;

public:
    BigDecimalInt(string number) {
        //check if the input is empty
        if (number == "" || allZeros(number)) {
            numbers = "0";
            numberOfDigits.push_back(0);
        } else {
            bool sign = false;
            int countZeros = 0;
            //check if 1st char is a sign or not
            if (number[0] == '-' || number[0] == '+') {
                sign = true;
                if (number[0] == '-') { negative = true; }
            }
            //count how many zeros in left
            for (int i = sign; i < number.size(); ++i) {
                if (number[i] == '0') { countZeros++; }
                else { break;; }
            }
            //remove sign and zeros
            for (int i = countZeros + sign; i < number.size(); i++) {
                numbers = numbers + number[i];
            }
            //add the digits
            for (char temp : numbers) {
                numberOfDigits.push_back(temp - '0');
            }
        }
    }
    bool allZeros(string s)
    {
        for (int i = 0; i < s.size(); ++i) {
            if(s[i]!='0'){return false;}
        }
        return true;
    }

    BigDecimalInt operator+(BigDecimalInt obj) {

        //if minus , or negative part
        if (negative && !obj.negative) {
            BigDecimalInt dummy(numbers);
            return obj -dummy ;
        }

        // other is negative - subtract its value
        if (obj.negative) {
            BigDecimalInt dummy(obj.numbers);
            return  *this - dummy;
        }
        vector<int> small, big;
        //set the bigger of them in
        if (numberOfDigits.size() >= obj.numberOfDigits.size()) {
            big = numberOfDigits;
            small = obj.numberOfDigits;
        } else {
            big = obj.numberOfDigits;
            small = numberOfDigits;
        }
        int lengthDiff = big.size() - small.size();
        string sum = "";
        bool carry = false;

        for (int i = small.size() - 1; i >= 0; i--) {
            int digit = small[i] + big[i + lengthDiff] + carry;
            carry = digit / 10;
            digit = digit % 10;
            char val = digit + '0';
            sum = (val) + sum;
        }
        for (int i = lengthDiff - 1; i >= 0; i--) {
            if (big[i] + carry == 10) {
                sum = '0' + sum;
                carry = true;
            } else {
                char val = ((carry + big[i]) + '0');
                sum = val + sum;
                carry = false;
            }
        }
        if (carry) {
            sum = "1" + sum;
        }
        BigDecimalInt obj2(sum);
        return obj2;

    }


    BigDecimalInt operator-(BigDecimalInt obj) {
        if (obj.negative) {
            BigDecimalInt duumy (obj.numbers);
            return   duumy+ *this;

        }

        if (this->compare(obj) < 0) {
            BigDecimalInt result = obj - *this;
            if (result.numbers[0]== '-'){
                string sub="";
                for(int i = 1  ; i< numbers.size() ;i++)
                {
                    sub=numbers[i]+sub;
                }
                result.numbers=sub;

            } else {
                result.numbers='-'+result.numbers;
            }
            result.negative = !result.negative;
            return result;

        }
        int lengthDeff = numbers.size() - obj.numbers.size();
        string result = "";
        bool carry = false;
        for (int i = obj.numbers.size() - 1; i >= 0; i--) {
            int biggerDigit = numberOfDigits[i + lengthDeff] - carry;
            int smallDigit = obj.numberOfDigits[i];
            carry = false;

            if (biggerDigit < smallDigit) {
                biggerDigit += 10;
                carry = true;
            }
            char temp = (biggerDigit - smallDigit + '0');
            result = temp + result;
        }

        for (int i = lengthDeff - 1; i >= 0; i--) {
            if (carry > numberOfDigits[i]) {
                char temp = numberOfDigits[i] + 10 - carry + '0';
                result = temp + result;
                carry = true;
            } else {
                char temp = numberOfDigits[i] - carry + '0';
                result = temp + result;
                carry = 0;
            }

        }
        BigDecimalInt dummy(result);
        return dummy;


    }

    int compare(BigDecimalInt other) {


        // Current is negative, other is positive
        if (negative && !other.negative)
            return -1;

            // Current is positive, other is negative
        else if (!negative && other.negative){
            return 1;
        }

            // Both are negative
        else if (negative){
            // Current is negative and has more digits - therefore it is smaller
            if (numberOfDigits.size() > other.numberOfDigits.size())
                return -1;
                // Current is negative and has less digits - Therefore it is bigger
            else if (numberOfDigits.size() < other.numberOfDigits.size())
                return 1;

                // Both have same number of digits - need to iterate them
            else
                for (int index = 0; index < numberOfDigits.size(); index++) {

                    // Current has bigger negative digit - therefore it is smaller
                    if (numberOfDigits[index] > other.numberOfDigits[index])

                        return -1;

                        // Current has smaller negative digit - therefore it is smaller
                    else if (numberOfDigits[index] < other.numberOfDigits[index])
                        return 1;
                }

            // If we have reached here, the numbers are completely identical
            return 0;
        }

        // If we have reached here, both numbers are positive

        // Current is positive and has more digits - Therefore it is bigger
        if (numberOfDigits.size() > other.numberOfDigits.size()) {
            return 1;
        }

            // Current is positive and has less digits - Therefore it is smaller
        else if (numberOfDigits.size() < other.numberOfDigits.size())
            return -1;

            // Both have same number of digits - need to iterate them
        else
            for (int index = 0; index < numberOfDigits.size(); index++) {

                // Current has bigger positive digit - therefore it is bigger
                if (numberOfDigits[index]> other.numberOfDigits[index])
                    return 1;

                    // Current has smaller positive digit - therefore it is smaller
                else if (numberOfDigits[index]< other.numberOfDigits[index])
                    return -1;
            }

        // If we have reached here, the numbers are completely identical
        return 0;
    }


#endif //DS_ASS_PROB_1_BIGDECIMALINT_H
};
