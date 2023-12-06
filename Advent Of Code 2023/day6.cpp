/*
--- Day 6: Wait For It ---
The ferry quickly brings you across Island Island. After asking around, you discover that there is indeed normally a large pile of sand somewhere near here, but you don't see anything besides lots of water and the small island where the ferry has docked.

As you try to figure out what to do next, you notice a poster on a wall near the ferry dock. "Boat races! Open to the public! Grand prize is an all-expenses-paid trip to Desert Island!" That must be where the sand comes from! Best of all, the boat races are starting in just a few minutes.

You manage to sign up as a competitor in the boat races just in time. The organizer explains that it's not really a traditional race - instead, you will get a fixed amount of time during which your boat has to travel as far as it can, and you win if your boat goes the farthest.

As part of signing up, you get a sheet of paper (your puzzle input) that lists the time allowed for each race and also the best distance ever recorded in that race. To guarantee you win the grand prize, you need to make sure you go farther in each race than the current record holder.

The organizer brings you over to the area where the boat races are held. The boats are much smaller than you expected - they're actually toy boats, each with a big button on top. Holding down the button charges the boat, and releasing the button allows the boat to move. Boats move faster if their button was held longer, but time spent holding the button counts against the total race time. You can only hold the button at the start of the race, and boats don't move until the button is released.

For example:

Time:      7  15   30
Distance:  9  40  200
This document describes three races:

The first race lasts 7 milliseconds. The record distance in this race is 9 millimeters.
The second race lasts 15 milliseconds. The record distance in this race is 40 millimeters.
The third race lasts 30 milliseconds. The record distance in this race is 200 millimeters.
Your toy boat has a starting speed of zero millimeters per millisecond. For each whole millisecond you spend at the beginning of the race holding down the button, the boat's speed increases by one millimeter per millisecond.

So, because the first race lasts 7 milliseconds, you only have a few options:

Don't hold the button at all (that is, hold it for 0 milliseconds) at the start of the race. The boat won't move; it will have traveled 0 millimeters by the end of the race.
Hold the button for 1 millisecond at the start of the race. Then, the boat will travel at a speed of 1 millimeter per millisecond for 6 milliseconds, reaching a total distance traveled of 6 millimeters.
Hold the button for 2 milliseconds, giving the boat a speed of 2 millimeters per millisecond. It will then get 5 milliseconds to move, reaching a total distance of 10 millimeters.
Hold the button for 3 milliseconds. After its remaining 4 milliseconds of travel time, the boat will have gone 12 millimeters.
Hold the button for 4 milliseconds. After its remaining 3 milliseconds of travel time, the boat will have gone 12 millimeters.
Hold the button for 5 milliseconds, causing the boat to travel a total of 10 millimeters.
Hold the button for 6 milliseconds, causing the boat to travel a total of 6 millimeters.
Hold the button for 7 milliseconds. That's the entire duration of the race. You never let go of the button. The boat can't move until you let you of the button. Please make sure you let go of the button so the boat gets to move. 0 millimeters.
Since the current record for this race is 9 millimeters, there are actually 4 different ways you could win: you could hold the button for 2, 3, 4, or 5 milliseconds at the start of the race.

In the second race, you could hold the button for at least 4 milliseconds and at most 11 milliseconds and beat the record, a total of 8 different ways to win.

In the third race, you could hold the button for at least 11 milliseconds and no more than 19 milliseconds and still beat the record, a total of 9 ways you could win.

To see how much margin of error you have, determine the number of ways you can beat the record in each race; in this example, if you multiply these values together, you get 288 (4 * 8 * 9).

Determine the number of ways you could beat the record in each race. What do you get if you multiply these numbers together?
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
#include <cmath>

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

void fill_vector(string line, vector<lli> &vec){
    lli number = 0;
    bool encountered_colon = 0;
    for (int i = 0; i < line.length(); ++i){
        if (line[i] == ':'){
            encountered_colon = 1;
        }
        if (isdigit(line[i])){
            number = number * 10 + (line[i] - '0');
        }
        else {
            // line[i] is " "
            if (encountered_colon && number != 0){
                vec.push_back(number);
                number = 0;
            }
        }
    }
    vec.push_back(number);  // add last number
}

void fill_vector_part_2(string line, vector<lli> &vec){
    // same function, just ignores spaces
    lli number = 0;
    bool encountered_colon = 0;
    for (int i = 0; i < line.length(); ++i){
        if (line[i] == ':'){
            encountered_colon = 1;
        }
        if (isdigit(line[i])){
            number = number * 10 + (line[i] - '0');
        }
        else {
            // line[i] is " " but we are not adding numbers now, just ignoring spaces
        }
    }
    vec.push_back(number);  // add number
}

lli get_ways_to_win(lli time_limit, lli distance){
    /*
    For part 1
    lim = 7
    t = 0 s = 0
    t = 1 s = 1* (lim - 1)
    t = 2 s = 2 * (lim - 2)


    s = hold * (lim - hold)

    s < hold(lim-hold)

    - hold^2 + lim * hold - s > 0

    hold = (- lim +- root(lim^2 - 4 * s))/(-2)  roots

    we are interested in counting the whole numbers that satisfy the inequality

    first case has roots (7+root(13))/2 and (7-root(13))/2, or approximately 1.70 and 5.30
    we are counting the whole numbers in between
    so 2, 3, 4, 5 = 4 ways of winning
    */
    int root_1 = int(ceil((-time_limit + sqrt(time_limit * time_limit - 4 * distance))/(-2)));   // smaller number, take ceil
    int root_2 = int(floor((-time_limit - sqrt(time_limit * time_limit - 4 * distance))/(-2)));  // larger number, take floor
    return root_2 - root_1 + 1;
}

void test_part1(deque<string> lines){
    lli answer = 0; // Answer to part 1
    string line = lines.front();
    lines.pop_front();
    vector<lli> time_limits;
    vector<lli> distances;
    answer = stoi(line);
    line = lines.front();
    lines.pop_front();
    fill_vector(line, time_limits); // fill time_limits
    line = lines.front();
    lines.pop_front();
    fill_vector(line, distances); // fill distances
    lli ways_to_beat = 0;
    for(int i = 0; i < time_limits.size(); ++i){
        cout << "Race " << i+1 << ": " << time_limits[i] << " " << distances[i] << endl;
        int temp = get_ways_to_win(time_limits[i], distances[i]);
        if (temp) { // non zero value, we have ways to win
        cout << "Calculated ways to win for race " << i+1 << ": " << temp << endl;
            if (!ways_to_beat){ ways_to_beat = temp;}
            else { ways_to_beat *= temp;}
        }
        // else we had no ways to win. If we multiply with zero we will lose our previous ways to win
    }
    cout << "Answer: " << answer << endl;
    cout << "calculated: " << ways_to_beat << endl;
}

void solve_part1(deque<string> lines){
    string line;
    vector<lli> time_limits;
    vector<lli> distances;
    line = lines.front();
    lines.pop_front();
    fill_vector(line, time_limits); // fill time_limits
    line = lines.front();
    lines.pop_front();
    fill_vector(line, distances); // fill distances
    lli ways_to_beat = 0;
    for(int i = 0; i < time_limits.size(); ++i){
        cout << "Race " << i+1 << ": " << time_limits[i] << " " << distances[i] << endl;
        int temp = get_ways_to_win(time_limits[i], distances[i]);
        if (temp) { // non zero value, we have ways to win
        cout << "Calculated ways to win for race " << i+1 << ": " << temp << endl;
            if (!ways_to_beat){ ways_to_beat = temp;}
            else { ways_to_beat *= temp;}
        }
        // else we had no ways to win. If we multiply with zero we will lose our previous ways to win
    }
    cout << "Answer: " << 1159152 << endl; // for debugging later
    cout << "calculated: " << ways_to_beat << endl;
}

void test_part2(deque<string> lines){
    lli answer = 71503; // Answer to part 2
    lines.pop_front(); // had answer to part 1, don't care about it
    string line = lines.front();
    lines.pop_front();
    vector<lli> time_limits;
    vector<lli> distances;
    fill_vector_part_2(line, time_limits); // fill time_limits
    line = lines.front();
    lines.pop_front();
    fill_vector_part_2(line, distances); // fill distances
    cout << "Race " << 1 << ": " << time_limits[0] << " " << distances[0] << endl;
    lli ways_to_beat = get_ways_to_win(time_limits[0], distances[0]);;
    cout << "Calculated ways to win for race " << 1 << ": " << ways_to_beat << endl;
    cout << "Answer: " << answer << endl;
}

void solve_part2(deque<string> lines){
    string line;// = lines.front();
    vector<lli> time_limits;
    vector<lli> distances;
    line = lines.front();
    lines.pop_front();
    fill_vector_part_2(line, time_limits); // fill time_limits
    line = lines.front();
    lines.pop_front();
    fill_vector_part_2(line, distances); // fill distances
    cout << "Race " << 1 << ": " << time_limits[0] << " " << distances[0] << endl;
    lli ways_to_beat = get_ways_to_win(time_limits[0], distances[0]);;
    cout << "Calculated ways to win for race " << 1 << ": " << ways_to_beat << endl;
    //cout << "Answer: " << 1159152 << endl; // for debugging later
}

int main() {

    deque<string> lines;
    deque<string> test_lines;

    readInput(test_lines, "inputs/sample_day6.txt");
    readInput(lines, "inputs/day6.txt");

    //test_part1(test_lines);
    //solve_part1(lines);

    test_part2(test_lines);
    solve_part2(lines);

    return 0;
}