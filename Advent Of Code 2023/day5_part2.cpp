/*
--- Part Two ---
Everyone will starve if you only plant such a small number of seeds. Re-reading the almanac, it looks like the seeds: line actually describes ranges of seed numbers.

The values on the initial seeds: line come in pairs. Within each pair, the first value is the start of the range and the second value is the length of the range. So, in the first line of the example above:

seeds: 79 14 55 13
This line describes two ranges of seed numbers to be planted in the garden. The first range starts with seed number 79 and contains 14 values: 79, 80, ..., 91, 92. The second range starts with seed number 55 and contains 13 values: 55, 56, ..., 66, 67.

Now, rather than considering four seed numbers, you need to consider a total of 27 seed numbers.

In the above example, the lowest location number can be obtained from seed number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77, temperature 45, humidity 46, and location 46. So, the lowest location number is 46.

Consider all of the initial seed numbers listed in the ranges on the first line of the almanac. What is the lowest location number that corresponds to any of the initial seed numbers?

Your puzzle answer was 20283860.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
/*
originally i used the same logic for both parts.
seeds: 2019933646 2719986 2982244904 337763798 445440 255553492 1676917594 196488200 3863266382 36104375 1385433279 178385087 2169075746 171590090 572674563 5944769 835041333 194256900 664827176 42427020

 ./day5.exe
inputs/day5.txt opened successfully!
read range: 2719986
read range: 337763798
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
Unfortunately the numbers were too large
I realised I don't need to store all of them in memory. I can just store the ranges and then check if the mappping is in the range.
Then I break down the mappings if needed else leave them unchanged.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <ctype.h>
#include <deque>
#include <tuple>
#include <queue>

#define lli long long int

using namespace std;   

void readInput(deque<string> &lines, string file_name) {
/*
    Reads the input file and stores each line in a vector of strings.
    Sends an error message to stderr if the file cannot be opened.
    Sends a success message to stdout if the file is opened successfully. 
    Let m be the number of lines. Time complexity is O(m)
*/
    ifstream file(file_name);
    if (!file){
        cerr << "Unable to open file " << file_name << endl;
    }
    else {
        cout << file_name << " opened successfully!" << endl;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
            // cout << "line: " << line << endl;
    }
    file.close();
    }
}

tuple<lli, lli, lli> parse_line(string &line){
    /*
        Returns a tuple of destination, source, range
        Let n be the number of characters in the line
        O(n) time complexity for this function
    */
    lli destination = -1, source = -1, range = -1, temp = 0;
    for (lli i = 0; i < line.length(); ++i){
        if (line[i] == ' '){
            // reached an empty space. 
            if (destination == -1){
                destination = temp;
                temp = 0;
            }
            else if (source == -1){
                source = temp;
                temp = 0;
            }
        }
        else {
            // not an empty space. add the number to temp
            temp = temp * 10 + (line[i] - '0');
        }
    }
    range = temp;
    return make_tuple(destination, source, range);
}

void get_seed_ranges(deque<string> &lines, unordered_map<lli, lli> &seeds){
    /*
        Fills the seeds vector with the seed numbers from the input file.
        input format is
        seeds: 79 14 55 13
        seed ranges are in pairs
        first number is the start and second number is the range
        O(n) time complexity where n is the number of characters in line
    */
    string line = lines.front();
    lines.pop_front();  // remove the line from the deque. Future functions don't need this line. Pop from deque is O(1)
    lines.pop_front(); // remove the empty line. O(1)
    lli seed = 0;
    lli range = 0;
    bool read_seed = true;
    for (lli i = 7; i < line.length(); ++i){ // start at 6 to skip "seeds: "
        if (isdigit(line[i])){
            if (read_seed){
                // haven't read the value for seed start yet. 
                seed = seed * 10 + (line[i] - '0');
            }
            else {
                // have finished reading the value for seed. now reading the value for range
                range = range * 10 + (line[i] - '0');
            }
        }
        else{
            // reached an empty space or newline
            if (read_seed){
                // were reading seed before this. set read_seed to false.
                read_seed = false;
            }
            else {
                // were reading range before this. set read_seed to true and insert the seed range into the seeds set
                read_seed = true;
                seeds.insert(make_pair(seed, seed + range - 1));    // O(1) to insert into unordered_map
                seed = 0;
                range = 0;
            }
        }
    }
    seeds.insert(make_pair(seed, seed + range - 1)); // insert the last seed range. O(1)
    /*
    for (auto i = seeds.begin(); i != seeds.end(); ++i){
        cout << "Seeds " << i->first << ":" << i->second << endl;
    }
    */
}

void get_mappings(deque<string> &lines, unordered_map<lli, lli> &keys ,unordered_map<lli, lli> &mappings){
    /*
        Fills the map with the soil numbers from the input file.
        input format is
        seed-to-soil map:
        50 98 2
        52 50 48
        etc
        each line is a range of seed numbers and their corresponding soil numbers
        the first number is the destination soil numbers
        the second number is the source seed numbers
        the third number is the length of the range

        pop_front O(1)
        insert O(1)
        erase O(1)
        parse_line O(n) where n is the number of characters in a line
        get<0/1/2> O(1)
        for loop O(m) where m is the number of lines in the input file
        total time complexity is O(mn)
    */
    string line = lines.front();       
    cout << line << endl;
    lines.pop_front();  // remove the line from the deque. don't need this line. this line just says "something-to-something map:"
    line = lines.front();   // get the next line
    lli destination, source, range, temp = 0;

    while (line != ""){
        vector<unordered_map<lli, lli>::iterator> keys_to_remove;
        unordered_map<lli, lli> new_keys;  // Temporary map to store new keys

        tuple<lli, lli, lli> parsed_line = parse_line(line); // get the destination, source and range from the line
        destination = get<0>(parsed_line);
        source = get<1>(parsed_line);
        range = get<2>(parsed_line);

        for(auto it = keys.begin(); it != keys.end();++it){
            // iterate through the keys
            if (it->first > source + range - 1 || it->second < source){
                // the key is not in the range. move on to the next key
            }
            else if (it->first >= source && it->second <= source + range - 1){
                // the key is in the range. insert the mapping into the map
                mappings.insert(make_pair(destination + it->first - source, destination + it->second - source)); 
                keys_to_remove.push_back(it);
            }
            else if(it->first >= source && it->second > source + range - 1){
                // parts of the key are in the range. the start of the key is in the range but the end is not
                new_keys[source + range] = it->second;
                mappings.insert(make_pair(destination + it->first - source, destination + range - 1));
                keys_to_remove.push_back(it);
            }
            else if (it->first < source && it->second >= source && it->second <= source + range - 1){
                // parts of the key are in the range. the end of the key is in the range but the start is not
                mappings.insert(make_pair(destination, destination + it->second - source));
                new_keys[it->first] = source - 1;
                keys_to_remove.push_back(it);
            }
            else if (it->first < source && it->second > source + range - 1){
                // parts of the key are in the range. the start and end of the key are not in the range
                mappings.insert(make_pair(destination, destination + range - 1));
                new_keys[it->first] = source - 1;
                new_keys[source + range] = it->second;
                keys_to_remove.push_back(it);
            }

        }

        // Remove the keys that were inserted into the mappings
        for (auto it : keys_to_remove) {
            keys.erase(it);
        }

        // Insert new keys into the keys map
        keys.insert(new_keys.begin(), new_keys.end());

        
        lines.pop_front();  // line is processed. remove it from the deque
        line = lines.front();   // get the next line
    }

    // line is empty. all lines are processed.
    lines.pop_front();  // remove the empty line
    
    // remaining items in keys were all not in range. add to mappings as is
    for(auto it = keys.begin(); it != keys.end();it++){
        mappings.insert(make_pair(it->first, it->second));
    }
    keys.clear();
}

void test_part2(deque<string> lines){
    string line = lines.front();
    lines.pop_front();
    lli answer = 0;
    for (lli j=0; j < line.length(); ++j){
        if (line[j] == ' '){
            // the number before this was the answer for part 1. reset answer.
            answer = 0;
        }
        else{
            answer = answer * 10 + (line[j] - '0');
        }
    }
    for (auto i = lines.begin(); i != lines.end(); ++i){
        cout << *i << endl;
    }
    unordered_map<lli, lli> seeds;
    unordered_map<lli, lli> mappings;
    get_seed_ranges(lines, seeds);    // get the seeds. O(n) where n is the number of characters in the line
    for (int j = 0; j < 7; j++){
        get_mappings(lines, seeds, mappings); // get the mappings. O(mn) where m is the number of lines in the input file and n is the number of characters in a line
        seeds = mappings;   // copy the mappings to seeds. O(h)
        mappings.clear();   // clear the mappings. O(h)
    }
    lli location = -1;
    for (auto i = seeds.begin(); i != seeds.end(); ++i){
        //cout << "Location: " << i->first << endl;
        if (location == -1){
            location = i->first;
        }
        else{
            location = min(location, i->first);
        }
    }

    cout << "Expected answer: " << answer << endl;
    cout << "Actual answer: " << location << endl;
    cout << "Difference: " << answer - location << endl;

}

void solve_part2(deque<string> lines){
    /*
    Let n be the number of characters in a line and m be the number of lines.
    get_seed_ranges O(n)
    get_mappings O(mn)
    called 6x
    iterating over seeds O(h) where h is the number of disjoint ranges for locations
    total time complexity is O(6mn + h + n) = O((6m+1)n+h) = O(mn + h)
    reading all lines into a deque is O(m)
    Total time complexity is O(m + mn + h) = O(mn + h)
    */
    string line = lines.front();
    /*
    for (auto i = lines.begin(); i != lines.end(); ++i){
        cout << *i << endl;
    }
    */
    unordered_map<lli, lli> seeds;
    unordered_map<lli, lli> mappings;
    get_seed_ranges(lines, seeds);    // get the seeds. O(n) where n is the number of characters in the line
    for (int j = 0; j < 7; j++){
        get_mappings(lines, seeds, mappings); // get the mappings. O(mn) where m is the number of lines in the input file and n is the number of characters in a line
        seeds = mappings;   // copy the mappings to seeds. O(h)
        mappings.clear();   // clear the mappings. O(h)
    }
    lli location = -1;
    for (auto i = seeds.begin(); i != seeds.end(); ++i){
        //cout << "Location: " << i->first << endl;
        if (location == -1){
            location = i->first;
        }
        else{
            location = min(location, i->first);
        }
    }
    // debug statements for future when I fix this ugly code
    cout << "Expected answer: 20283860" << endl;
    cout << "Actual answer: " << location << endl;
    cout << "Difference: " << 20283860 - location << endl;  
}

int main() {
    deque<string> lines;
    deque<string> test_lines;

    //readInput(test_lines, "inputs/sample_day5.txt");
    //test_part2(test_lines);
    readInput(lines, "inputs/day5.txt");
    solve_part2(lines);

    return 0;
}