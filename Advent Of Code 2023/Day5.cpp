/*
--- Day 5: If You Give A Seed A Fertilizer ---
You take the boat and find the gardener right where you were told he would be: managing a giant "garden" that looks more to you like a farm.

"A water source? Island Island is the water source!" You point out that Snow Island isn't receiving any water.

"Oh, we had to stop the water because we ran out of sand to filter it with! Can't make snow with dirty water. Don't worry, I'm sure we'll get more sand soon; we only turned off the water a few days... weeks... oh no." His face sinks into a look of horrified realization.

"I've been so busy making sure everyone here has food that I completely forgot to check why we stopped getting more sand! There's a ferry leaving soon that is headed over in that direction - it's much faster than your boat. Could you please go check it out?"

You barely have time to agree to this request when he brings up another. "While you wait for the ferry, maybe you can help us with our food production problem. The latest Island Island Almanac just arrived and we're having trouble making sense of it."

The almanac (your puzzle input) lists all of the seeds that need to be planted. It also lists what type of soil to use with each kind of seed, what type of fertilizer to use with each kind of soil, what type of water to use with each kind of fertilizer, and so on. Every type of seed, soil, fertilizer and so on is identified with a number, but numbers are reused by each category - that is, soil 123 and fertilizer 123 aren't necessarily related to each other.

For example:

seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4
The almanac starts by listing which seeds need to be planted: seeds 79, 14, 55, and 13.

The rest of the almanac contains a list of maps which describe how to convert numbers from a source category into numbers in a destination category. That is, the section that starts with seed-to-soil map: describes how to convert a seed number (the source) to a soil number (the destination). This lets the gardener and his team know which soil to use with which seeds, which water to use with which fertilizer, and so on.

Rather than list every source number and its corresponding destination number one by one, the maps describe entire ranges of numbers that can be converted. Each line within a map contains three numbers: the destination range start, the source range start, and the range length.

Consider again the example seed-to-soil map:

50 98 2
52 50 48
The first line has a destination range start of 50, a source range start of 98, and a range length of 2. This line means that the source range starts at 98 and contains two values: 98 and 99. The destination range is the same length, but it starts at 50, so its two values are 50 and 51. With this information, you know that seed number 98 corresponds to soil number 50 and that seed number 99 corresponds to soil number 51.

The second line means that the source range starts at 50 and contains 48 values: 50, 51, ..., 96, 97. This corresponds to a destination range starting at 52 and also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53 corresponds to soil number 55.

Any source numbers that aren't mapped correspond to the same destination number. So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers looks like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51
With this map, you can look up the soil number required for each initial seed number:

Seed number 79 corresponds to soil number 81.
Seed number 14 corresponds to soil number 14.
Seed number 55 corresponds to soil number 57.
Seed number 13 corresponds to soil number 13.
The gardener and his team want to get started as soon as possible, so they'd like to know the closest location that needs a seed. Using these maps, find the lowest location number that corresponds to any of the initial seeds. To do this, you'll need to convert each seed number through other categories until you can find its corresponding location number. In this example, the corresponding types are:

Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.
So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial seed numbers?

Your puzzle answer was 313045984.

The first half of this puzzle is complete! It provides one gold star: *
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

void get_seeds(deque<string> &lines, unordered_set<lli> &seeds){
    /*
        Fills the seeds vector with the seed numbers from the input file.
        input format is
        seeds: 79 14 55 13
        each seed is separated by a " "
    */
    string line = lines.front();
    lines.pop_front();  // remove the line from the deque. Future functions don't need this line. 
    lines.pop_front(); // remove the empty line
    lli seed = 0;
    for (lli i = 7; i < line.length(); ++i){ // start at 6 to skip "seeds: "
        if (line[i] == ' ' && seed != 0){
            seeds.insert(seed);
            seed = 0;
        }
        else {
            seed = seed * 10 + (line[i] - '0');
        }
    }
    // insert the last seed
    seeds.insert(seed);
    cout << "seeds:";
    for (auto i = seeds.begin(); i != seeds.end(); ++i){
        cout << *i << " ";
    }
    cout << endl;
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

void get_mapping(deque<string> &lines, unordered_set<lli> &seeds, unordered_set<lli> &map){
    /*
        Fills the soil map with the soil numbers from the input file.
        input format is
        seed-to-soil map:
        50 98 2
        52 50 48
        each line is a range of seed numbers and their corresponding soil numbers
        the first number is the destination soil numbers
        the second number is the source seed numbers
        the third number is the length of the range

        pop_front O(1)
        insert O(1)
        erase O(1)
        prase_line O(n) where n is the number of characters in a line
        get<0/1/2> O(1)
        for loop O(m) where m is the number of lines in the input file
        let h be the number of seeds
        total time complexity is O(mnh)
    */
    lines.pop_front();  // remove the line from the deque. don't need this line. 
    lli destination, source, range, temp = 0;
    string line = lines.front();   

    while (line != ""){
        // reset the numbers at the start of every loop
        tuple<lli, lli, lli> parsed_line = parse_line(line);
        destination = get<0>(parsed_line);
        source = get<1>(parsed_line);
        range = get<2>(parsed_line);
        lines.pop_front();  // remove the line from the deque. don't need this line since we processed it just now

        // check all the seeds to see if any of them are in this given range. If they are then we want to add them to the soil map and remove them from the seeds set
        for(auto i = seeds.begin(); i != seeds.end();){ // erasing the current element invalidates the iterator. so we need to increment it only if we are not erasing
            if ( (*i) >= source && (*i) < source + range){
                lli moved_to = destination + (*i) - source; 
                map.insert(moved_to); // destination;
                cout << "moving " << *i << " to " << moved_to << endl; // debugging statement
                i = seeds.erase(i); // erase returns an iterator to the next element
            }
            else {
                ++i;
            }
        }
        // all seeds in this line have been checked and added. repeat this until we reach an empty line and then add remaining seeds with their own soil number

        line = lines.front();   // get the next line
    }
    for (auto j = seeds.begin(); j != seeds.end();){
        map.insert(*j);
        cout << "moving " << *j << " to " << *j << endl;    // debugging statement
        j = seeds.erase(j);
    }
    cout << endl;
    // reached "" line. remove it
    lines.pop_front();    
}

void get_locations(deque<string> &lines, unordered_set<lli> &humidity, priority_queue<lli, vector<lli>, greater<lli>> &locations){
    /*
    Fills the priority queue with locations from the input file, based on the humidity to locations map.
    Input format is
    humidity-to-location map:
    60 56 37
    56 93 4
    similar to get_mappings function, only difference is inserting llio a priority queue instead of a set
    */
    lines.pop_front();  // remove the line from the deque. don't need this line. 
    lli destination, source, range, temp = 0;
    string line = lines.front();  

    while (!lines.empty()){
        // reset the numbers at the start of every loop
        tuple<lli, lli, lli> parsed_line = parse_line(line);
        destination = get<0>(parsed_line);
        source = get<1>(parsed_line);
        range = get<2>(parsed_line);
        lines.pop_front();  // remove the line from the deque. don't need this line since we processed it just now

        // check all the humidity to see if any of them are in this given range. If they are then we want to add them to the locations pq and remove them from the humidity set
        for(auto i = humidity.begin(); i != humidity.end();){ // erasing the current element invalidates the iterator. so we need to increment it only if we are not erasing
            if ( (*i) >= source && (*i) < source + range){
                lli moved_to = destination + (*i) - source; 
                locations.push(moved_to); // destination;
                cout << "moving " << *i << " to " << moved_to << endl;  // debugging statement
                i = humidity.erase(i); // erase returns an iterator to the next element
            }
            else {
                ++i;
            }
        }
        // all humidities in this line have been checked and added. repeat this until we reach an empty line and then add remaining humidity with their own location number
        if (lines.empty()){
            break;
        }
        line = lines.front();   // get the next line
    }
    for (auto j = humidity.begin(); j != humidity.end();){
        locations.push(*j);
        cout << "moving " << *j << " to " << *j << endl;    // debugging statement
        j = humidity.erase(j);
    }
    cout << endl;
    // reached "" line. remove it
    lines.pop_front();  
}

void test_part1(deque<string> lines){
    string line = lines.front();
    lines.pop_front();
    int answer = 0;
    for (lli j=0; j < line.length(); ++j){
        if (line[j] == ' '){
            // the number after this is the answer for part 2. stop reading the line.
            break;
        }
        else{
        answer = answer * 10 + (line[j] - '0');
        }
    }
    for (auto i = lines.begin(); i != lines.end(); ++i){
        cout << *i << endl;
    }
    unordered_set<lli> seeds;
    unordered_set<lli> mappings;
    priority_queue<lli, vector<lli>, greater<lli>> locations;
    get_seeds(lines, seeds);    // get the seeds. O(n) where n is the number of characters in the line
    /*
    seed to soil map
    soil to fertilizer map
    fertilizer to water map
    water to light map
    light to temperature map
    temperature to humidity map
    humidity to location map
    last map should be called using a different function since I want a priority queue to be able to access the answer in constant time.
    I call get_mappings() 6 times, so I should loop it.
    */
    for (lli i = 0; i < 6; ++i){
        cout << "mapping " << i+1 << endl;
        get_mapping(lines, seeds, mappings);    // get the mappings. O(mnh) where m is the number of lines in the input file and h is the number of seeds
        seeds = mappings;   // copy the mappings to seeds. O(h)
        mappings.clear();   // clear the mappings. O(h)
    }
    get_locations(lines, seeds, locations); // get the locations. O(mnh)
    // 7 O(mnh) calls. total time complexity is O(mnh)
    lli location = locations.top();

    cout << "Expected answer: " << answer << endl;
    cout << "Calculated answer: " << location << endl;
    cout << "Difference: " << answer - location << endl;
}

void solve_part1(deque<string> lines){
    unordered_set<lli> seeds;
    unordered_set<lli> mappings;
    priority_queue<lli, vector<lli>, greater<lli>> locations;
    get_seeds(lines, seeds);    // get the seeds. O(n) where n is the number of characters in the line
    /*
    seed to soil map
    soil to fertilizer map
    fertilizer to water map
    water to light map
    light to temperature map
    temperature to humidity map
    humidity to location map
    last map should be called using a different function since I want a priority queue to be able to access the answer in constant time.
    I call get_mappings() 6 times, so I should loop it.
    */
    for (lli i = 0; i < 6; ++i){
        cout << "mapping " << i+1 << endl;
        get_mapping(lines, seeds, mappings);    // get the mappings. O(mnh) where m is the number of lines in the input file and h is the number of seeds
        seeds = mappings;   // copy the mappings to seeds. O(h)
        mappings.clear();   // clear the mappings. O(h)
    }
    get_locations(lines, seeds, locations); // get the locations. O(mnh)
    // 7 O(mnh) calls. total time complexity is O(mnh)
    lli location = locations.top();

    cout << "Expected answer: 313045984" << endl;   // for debugging in case I fix this ugly code
    cout << "Calculated answer: " << location << endl;
    cout << "Difference: " << 313045984 - location << endl; // for debugging in case I fix this ugly code
}

int main() {
    deque<string> lines;
    deque<string> test_lines;

    //readInput(test_lines, "inputs/sample_day5.txt");
    //test_part1(test_lines);
    readInput(lines, "inputs/day5.txt");
    solve_part1(lines);

    return 0;
}
