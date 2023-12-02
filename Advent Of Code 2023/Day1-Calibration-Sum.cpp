/*
--- Day 1: Trebuchet?! ---
Something is wrong with global snow production, and you've been selected to take a look. The Elves have even given you a map; on it, they've used stars to mark the top fifty locations that are likely to be having problems.

You've been doing this long enough to know that to restore snow operations, you need to check all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

You try to ask why they can't just use a weather machine ("not powerful enough") and where they're even sending you ("the sky") and why your map looks mostly blank ("you sure ask a lot of questions") and hang on did you just say the sky ("of course, where do you think snow comes from") when you realize that the Elves are already loading you into a trebuchet ("please hold still, we need to strap you in").

As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.

The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.

Consider your entire calibration document. What is the sum of all of the calibration values?
*/

/*
--- Part Two ---
Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last digit on each line. For example:

0

What is the sum of all of the calibration values?
*/

/*
THESE FUNCTIONS WERE MADE FOR PART 1 BUT NOW THEY ARE NOT NEEDED AFTER I IMPLEMENTED PART 2

int get_first_digit(string line) {
    int val;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            val = line[i] - '0';
            return val;
        }
    }
    return -1;  // Could not find a digit
}

int get_last_digit(string line) {
    int val;
    for (int i = line.length()-1; i >= 0; i--) {
        if (isdigit(line[i])) {
            val = line[i] - '0';
            return val;
        }
    }
    return -1;  // Could not find a digit
}
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<ctype.h>


using namespace std;


map<string, int> digits = {
    {"zero",  0},
    {"one" , 1},
    {"two" , 2},
    {"three" , 3},
    {"four" , 4},
    {"five" , 5},
    {"six" , 6},
    {"seven" , 7},
    {"eight" , 8},
    {"nine" , 9}
};


int get_digit_from_string(string word) {
    if (digits.find(word) != digits.end()) {
                return digits.at(word);
    }
    return -1;  // Could not find a digit
}

int get_first_digit_from_string(string line){
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
        try {
            int val1, val2, val3;
            val1 = get_digit_from_string(line.substr(i, 3));
            if (val1 != -1){return val1;}
            val2 = get_digit_from_string(line.substr(i, 4));
            if (val2 != -1){return val2;}
            val3 = get_digit_from_string(line.substr(i, 5));
            if (val3 != -1){return val3;}             
        }
        catch (...) {}
    }
    return -1;  // Could not find a digit
}

int get_last_digit_from_string(string line){
    for (int i = line.length() - 1; i >= 0; i--) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
        try {
            int val1, val2, val3;
            val1 = get_digit_from_string(line.substr(i-2, 3));
            if (val1 != -1){return val1;}
            val2 = get_digit_from_string(line.substr(i-3, 4));
            if (val2 != -1){return val2;}
            val3 = get_digit_from_string(line.substr(i-4, 5));
            if (val3 != -1){return val3;}             
        }
        catch (...) {}
    }
    return -1;  // Could not find a digit
}

int main() {
    ifstream input("inputs/day1.txt");
    string line;
    int sum = 0;
    while (getline(input, line)) {
        // Process each line here
        int first = get_first_digit_from_string(line);
        int last = get_last_digit_from_string(line);
        // cout << first << " " << last << endl;
        sum += first * 10 + last;
    }
    cout << sum << endl;
    return 0;
}