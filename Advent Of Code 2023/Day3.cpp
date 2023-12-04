/*
--- Day 3: Gear Ratios ---
You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water source, but this is as far as he can bring you. You go inside.

It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.

"Aaah!"

You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.

The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one. If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.

The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

Your puzzle answer was 520135.

--- Part Two ---
The engineer finds the missing part and installs it in the engine! As the engine springs to life, you jump in the closest gondola, finally ready to ascend to the water source.

You don't seem to be going very fast, though. Maybe something is still wrong? Fortunately, the gondola has a phone labeled "help", so you pick it up and the engineer answers.

Before you can explain the situation, she suggests that you look out the window. There stands the engineer, holding a phone in one hand and waving with the other. You're going so slowly that you haven't even left the station. You exit the gondola.

The missing part wasn't the only issue - one of the gears in the engine is wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
In this schematic, there are two gears. The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?

Your puzzle answer was 72514855.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <set>
#include <utility>
#define pii pair<int, int> 


using namespace std;


bool is_symbol(char c){
    return (!isdigit(c) && c != '.');
}


bool valid_index(int row, int column, int num_lines, int num_columns){
    return (row >= 0 && row < num_lines && column >= 0 && column < num_columns);
}


bool symbol_is_adjacent(int row, int column, int num_lines, int num_columns, vector<string> &lines){
    for(int current_row = row-1; current_row <= row+1; current_row++){
        for (int current_column = column-1; current_column <= column+1; current_column++){
            if (valid_index(current_row, current_column, num_lines, num_columns)){
                if (is_symbol(lines[current_row][current_column])){
                    return true;
                }
            }
        }
    }
    return false;
}


int add_part_numbers(int num_lines, std::vector<std::__cxx11::string> &lines)
{
    int sum = 0;
    int number = 0;
    bool adjacent = false;   
    for (int i = 0; i < num_lines; i++){
        int num_columns = lines[i].length();
        for (int j = 0; j < num_columns; j++){
            if (isdigit(lines[i][j])){
                number = number * 10 + (lines[i][j] - '0');       
                adjacent = (adjacent || symbol_is_adjacent(i, j, num_lines, num_columns, lines));
            }
            else{
                if (adjacent){
                    sum += number;
                }
                number = 0;
                adjacent = false;
            }   
        }
    }
    if (adjacent) {
    sum += number;
    }
    return sum;   
}


void test(string file_name){
    ifstream testFile(file_name);
    if (!testFile){
        cerr << "Unable to open file inputs/sample_day3";
        exit(1);
    }

    int num_tests, num_lines, answer;

    string line, dummy;
    vector<string> lines;

    testFile >> num_tests;
    getline(testFile, dummy); // read and discard the rest of the line
    // Consume the newline character after reading num_test

    for (int test = 0; test < num_tests; test++){
        testFile >> num_lines;
        testFile >> answer;
        // Consume the newline character after reading num_lines and answer
        getline(testFile, dummy); // read and discard the rest of the line
        lines.clear();
        for (int line_num = 0; line_num < num_lines; line_num++){
            getline(testFile, line);
            lines.push_back(line);
        }
        int sum = add_part_numbers(num_lines, lines);
        if (sum == answer){
            cout << "Test " << test << " passed" << endl;
            // cout << "Expected: " << answer << endl;
            // cout << "Actual: " << sum << endl;
        }
        else{
            cout << "Test " << test << " failed" << endl;
            cout << "Expected: " << answer << endl;
            cout << "Actual: " << sum << endl;
        }
    }
    testFile.close();
}


void solve_part_1(string file_name){
    ifstream inputFile(file_name);
    if (!inputFile){
        cerr << "Unable to open file with task data: " << file_name << endl;
        exit(1);
    }
    
    int num_lines = 0;
    vector<string> lines;

    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            cout << line << endl;
            lines.push_back(line);
            num_lines++;
        }
        inputFile.close();
    }
   set<char> symbols;
   for (auto it = lines.begin(); it != lines.end(); ++it){  // iterate over all lines
        for (int i = 0; i < (*it).length(); i++){
            if (!isdigit((*it)[i]) && (*it)[i] != '.'){
                symbols.insert((*it)[i]);
            }
        }
    }
    
    cout << "Number of lines: " << num_lines << endl;
    cout << "Number of unique symbols: " << symbols.size() << endl;
    cout << "Unique Symbols: ";
    
    for (auto it = symbols.begin(); it != symbols.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    int sum = add_part_numbers(num_lines, lines);

    cout << "Sum of all part numbers: " << sum << endl;
    cout << "Expected Sum: 520135" << endl;
    cout << "Difference: " << sum - 520135 << endl;
}


vector<pii> get_gear_locs(std::vector<std::__cxx11::string> &lines){
    int gear_ratio_sum = 0;
    vector<pii> gear_locs;
    int num_lines = lines.size();
    int num_columns = lines[0].length();
    for (int row = 0; row < num_lines; row++){
        for (int column = 0; column < num_columns; column++){
            if (lines[row][column] == '*'){
                gear_locs.push_back(make_pair(row, column));
            }
        }
    }

    return gear_locs;
}


pii find_num(int row, int column, vector<string> &line) {
    int start = column;
    int end = column;

    // Find the start position
    while (start >= 0 && isdigit(line[row][start])) {
        start--;
    }
    start++;  // Adjust for the correct start position

    // Find the end position
    while (end < line[row].length() && isdigit(line[row][end])) {
        end++;
    }

    return make_pair(start, end);
}


int coord_to_num(int row, pii coord, vector<string> &line){
    int num = 0;
    for (int i = coord.first; i < coord.second; i++){
        num = num * 10 + (line[row][i] - '0');
    }
    return num;
}


int add_gear_ratios(std::vector<std::__cxx11::string> &lines){
    int gear_ratio_sum = 0;
    int num_lines = lines.size();
    int num_columns = lines[0].length();
    set<pair<int, pii>> num_locs;
    vector<pii> gear_locs = get_gear_locs(lines);
    // i find all numbers next to a gear. If set size is exactly two I add the products of all numbers. Inside my set I store pairs of pairs. These pairs are x,y coords of start and end of a number.
    for (auto gear = gear_locs.begin(); gear != gear_locs.end(); ++gear){
        int row = (*gear).first;
        int column = (*gear).second;
        for (int current_row = row-1; current_row <= row+1; current_row++){
            for (int current_column = column-1; current_column <= column+1; current_column++){
                if (valid_index(current_row, current_column, num_lines, num_columns)){
                    if (isdigit(lines[current_row][current_column])){
                        pii coord = find_num(current_row, current_column, lines);
                        num_locs.insert(make_pair(current_row, coord));
                    }
                }
            }
        }
        if (num_locs.size() == 2){
            int num1 = coord_to_num((*num_locs.begin()).first, (*num_locs.begin()).second, lines);
            int num2 = coord_to_num((*num_locs.rbegin()).first, (*num_locs.rbegin()).second, lines);
            
            gear_ratio_sum += num1 * num2;
            cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
            cout << "Gear Ratio Sum: " << gear_ratio_sum << endl;
        }
        num_locs.clear();
    }
    return gear_ratio_sum;
}   


void solve_part2(string file_name){
    ifstream inputFile(file_name);
    if (!inputFile){
        cerr << "Unable to open file with task data: " << file_name << endl;
        exit(1);
    }
    vector<string> lines;
    int num_lines = 0;
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            //cout << line << endl;
            lines.push_back(line);
            num_lines++;
        }
        inputFile.close();
    }
    int gear_ratios = add_gear_ratios(lines);
    cout << "Sum of all gear ratios: " << gear_ratios << endl;
    // add debugging statements for expected sum value in case I refactor the code later.
    cout << "Expected Sum: 72514855" << endl;
    cout << "Difference: " << gear_ratios - 72514855 << endl;
    // gear_ratios = add_gear_ratios();
}


void test_part2(string file_name){
    ifstream inputFile(file_name);
    if (!inputFile){
        cerr << "Unable to open file with task data: " << file_name << endl;
        exit(1);
    }
    vector<string> lines;
    int num_lines = 0;
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            cout << line << endl;
            lines.push_back(line);
            num_lines++;
        }
        inputFile.close();
    }
    int gear_ratios = add_gear_ratios(lines);
    cout << "Sum of all gear ratios: " << gear_ratios << endl;
    cout << "Expected Sum: 467835" << endl;
    cout << "Difference: " << gear_ratios - 467835 << endl;
    // gear_ratios = add_gear_ratios();
}


int main(){
    // solve_part_1("inputs/day3.txt");
    // test("inputs/sample_day3.txt");
    solve_part2("inputs/day3.txt");
    //test_part2("inputs/d3p2.txt");
    return 0;
}
