/*
--- Day 7: Camel Cards ---
Your all-expenses-paid trip turns out to be a one-way, five-minute ride in an airship. (At least it's a cool airship!) It drops you off at the edge of a vast desert and descends back to Island Island.

"Did you bring the parts?"

You turn around to see an Elf completely covered in white clothing, wearing goggles, and riding a large camel.

"Did you bring the parts?" she asks again, louder this time. You aren't sure what parts she's looking for; you're here to figure out why the sand stopped.

"The parts! For the sand, yes! Come with me; I will show you." She beckons you onto the camel.

After riding a bit across the sands of Desert Island, you can see what look like very large rocks covering half of the horizon. The Elf explains that the rocks are all along the part of Desert Island that is directly above Island Island, making it hard to even get there. Normally, they use big machines to move the rocks and filter the sand, but the machines have broken down because Desert Island recently stopped receiving the parts they need to fix the machines.

You've already assumed it'll be your job to figure out why the parts stopped when she asks if you can help. You agree automatically.

Because the journey will take a few days, she offers to teach you the game of Camel Cards. Camel Cards is sort of similar to poker except it's designed to be easier to play while riding a camel.

In Camel Cards, you get a list of hands, and your goal is to order them based on the strength of each hand. A hand consists of five cards labeled one of A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2. The relative strength of each card follows this order, where A is the highest and 2 is the lowest.

Every hand is exactly one type. From strongest to weakest, they are:

Five of a kind, where all five cards have the same label: AAAAA
Four of a kind, where four cards have the same label and one card has a different label: AA8AA
Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
High card, where all cards' labels are distinct: 23456
Hands are primarily ordered based on type; for example, every full house is stronger than any three of a kind.

If two hands have the same type, a second ordering rule takes effect. Start by comparing the first card in each hand. If these cards are different, the hand with the stronger first card is considered stronger. If the first card in each hand have the same label, however, then move on to considering the second card in each hand. If they differ, the hand with the higher second card wins; otherwise, continue with the third card in each hand, then the fourth, then the fifth.

So, 33332 and 2AAAA are both four of a kind hands, but 33332 is stronger because its first card is stronger. Similarly, 77888 and 77788 are both a full house, but 77888 is stronger because its third card is stronger (and both hands have the same first and second card).

To play Camel Cards, you are given a list of hands and their corresponding bid (your puzzle input). For example:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
This example shows five hands; each hand is followed by its bid amount. Each hand wins an amount equal to its bid multiplied by its rank, where the weakest hand gets rank 1, the second-weakest hand gets rank 2, and so on up to the strongest hand. Because there are five hands in this example, the strongest hand will have rank 5 and its bid will be multiplied by 5.

So, the first step is to put the hands in order of strength:

32T3K is the only one pair and the other hands are all a stronger type, so it gets rank 1.
KK677 and KTJJT are both two pair. Their first cards both have the same label, but the second card of KK677 is stronger (K vs T), so KTJJT gets rank 2 and KK677 gets rank 3.
T55J5 and QQQJA are both three of a kind. QQQJA has a stronger first card, so it gets rank 5 and T55J5 gets rank 4.
Now, you can determine the total winnings of this set of hands by adding up the result of multiplying each hand's bid with its rank (765 * 1 + 220 * 2 + 28 * 3 + 684 * 4 + 483 * 5). So the total winnings in this example are 6440.

Find the rank of every hand in your set. What are the total winnings?

Your puzzle answer was 255048101.

--- Part Two ---
To make things a little more interesting, the Elf introduces one additional rule. Now, J cards are jokers - wildcards that can act like whatever card would make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even than 2. The other cards stay in the same order: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J.

J cards can pretend to be whatever card is best for the purpose of determining hand type; for example, QJJQ2 is now considered four of a kind. However, for the purpose of breaking ties between two hands of the same type, J is always treated as J, not the card it's pretending to be: JKKK2 is weaker than QQQQ2 because J is weaker than Q.

Now, the above example goes very differently:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
32T3K is still the only one pair; it doesn't contain any jokers, so its strength doesn't increase.
KK677 is now the only two pair, making it the second-weakest hand.
T55J5, KTJJT, and QQQJA are now all four of a kind! T55J5 gets rank 3, QQQJA gets rank 4, and KTJJT gets rank 5.
With the new joker rule, the total winnings in this example are 5905.

Using the new joker rule, find the rank of every hand in your set. What are the new total winnings?

Your puzzle answer was 253718286.

Both parts of this puzzle are complete! They provide two gold stars: **
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <cstring>
#include <unordered_set>
#include <ctype.h>
#include <deque>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;

#define lli long long int
#define hand pair<string, int>
// Custom comparator
struct Compare {
	unordered_map<char, int> weights = {{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, 
										{'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, 
										{'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}};

	bool operator()(const hand &a, const hand &b) {
		if (a.second != b.second) {
			return a.second < b.second;
		} 
		for (int i = 0; i < 5; ++i) {
			if (a.first[i] != b.first[i]) {
				return weights[a.first[i]] < weights[b.first[i]];
			}
		}
		return false; // Added a default return statement to avoid compilation warning
	}
};

struct Compare2 {
	unordered_map<char, int> weights = {{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 1}, {'T', 10}, 
										{'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, 
										{'5', 5}, {'4', 4}, {'3', 3}, {'2', 2} };

	bool operator()(const hand &a, const hand &b) {
		if (a.second != b.second) {
			return a.second < b.second;
		} 
		for (int i = 0; i < 5; ++i) {
			if (a.first[i] != b.first[i]) {
				return weights[a.first[i]] < weights[b.first[i]];
			}
		}
		return false; // Added a default return statement to avoid compilation warning
	}
};

bool readInput(deque<string> &lines, string file_name) {
/*
    Reads the input file and stores each line in a vector of strings.
    Sends an error message to stderr if the file cannot be opened.
    Sends a success message to stdout if the file is opened successfully. 
    Let m be the number of lines. Time complexity is O(m)
*/
    ifstream file(file_name);
    if (!file){
        cerr << "Unable to open file " << file_name << endl;
        return 0;
    }
    cout << file_name << " opened successfully!" << endl;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
            // cout << "line: " << line << endl;
    }
    return 1;
}

int get_type(string line){
	unordered_map<char, int> freq;
	int max_freq = 0;
	for (int i = 0; i < 5; i++) {
		char c = line[i];
		freq[c]++;
		max_freq = max(max_freq, freq[c]);
	}
	if (max_freq > 3){
		return max_freq + 1;
	}
	if (max_freq == 1){
		return 0;
	}
	if (max_freq == 3){
		// 3 of a kind or full house
		for (auto it = freq.begin(); it != freq.end(); it++){
			if (it->second == 2){
				return 4; // full house
			}
		}
		return 3; // 3 of a kind
	}
	// 2 pair or 1 pair
	bool encountered_2 = false;
	for (auto it = freq.begin(); it != freq.end(); it++){
		if (it->second == 2 && encountered_2){
			return 2; // 2 pair
		}
		else if (it->second == 2){
			encountered_2 = true;
		}
	}
	return 1; // 1 pair
	
}

int get_type2(string line){
	unordered_map<char, int> freq;
	int max_freq = 0;
	int joker_count = 0;
	for (int i = 0; i < 5; i++) {
		char c = line[i];
		freq[c]++;
		if (c == 'J'){
			joker_count++;
		}
		if (c != 'J'){	// not counting jokers in max_freq
			max_freq = max(max_freq, freq[c]);
		}
	}
	if (!joker_count){
		if (max_freq > 3){
			return max_freq + 1;
		}
		if (max_freq == 1){
			return 0;
		}
		if (max_freq == 3){
			// 3 of a kind or full house
			for (auto it = freq.begin(); it != freq.end(); it++){
				if (it->second == 2 && !joker_count){
					return 4; // full house
				}
			}

			return 3; // 3 of a kind
		}
		// 2 pair or 1 pair
		bool encountered_2 = false;
		for (auto it = freq.begin(); it != freq.end(); it++){
			if (it->second == 2 && encountered_2){
				return 2; // 2 pair
			}
			else if (it->second == 2){
				encountered_2 = true;
			}
		}
		return 1; // 1 pair
	}
	// else we have jokers
	if (max_freq == 4 || (max_freq == 3 && joker_count == 2) || (max_freq == 2 && joker_count == 3) || (max_freq == 1 && joker_count == 4) || joker_count == 5){
		return 6;	// Now we have 5 of a kind with jokers.
	}
	if ((max_freq == 3 && joker_count == 1) || (max_freq == 2 && joker_count == 2) || (max_freq == 1 && joker_count == 3)){
		return 5;	// Now we have 4 of a kind with jokers.
	}
	// full house condition with joker:2 pairs with 1 joker
	if (max_freq == 2){
		bool encountered_2 = false;
		for (auto it = freq.begin(); it != freq.end(); it++){
			if (it->second == 2 && encountered_2){
				return 4; // full house
			}
			else if (it->second == 2){
				encountered_2 = true;
			}
		}
		// 3 of a kind with joker
		return 3;	// only one pair.
	}
	// max freq = 1. joker count = 1, 2
	if (joker_count == 1){
		return 1;	// 1 pair
	}
	return 3;	// 3 of a kind as we have 2 jokers
}

string get_hand(string line){
	return line.substr(0, 5);
}

int get_bid(string line){
	return stoi(line.substr(6));
}

int get_total_winnings(deque<string> &input){
	int rank = input.size();
	int total_winnings = 0;
	unordered_map<string, int> bids;
	priority_queue<hand, vector<hand>, Compare> pq;
	for (string line : input) {
		string cards = get_hand(line);
		pq.push(make_pair(cards, get_type(line)));
		bids[cards] = get_bid(line);
	}
	while (!pq.empty()) {
		hand curr = pq.top();
		//cout << "Rank " << rank << ": " << curr.first << " " << curr.second << endl; // Debugging
		pq.pop();
		total_winnings += rank * bids[curr.first];
		rank--;
	}
	return total_winnings;
}

int get_joker_winnings(deque<string> &input){
	int rank = input.size();
	int total_winnings = 0;
	unordered_map<string, int> bids;
	priority_queue<hand, vector<hand>, Compare2> pq;
	for (string line : input) {
		string cards = get_hand(line);
		pq.push(make_pair(cards, get_type2(line)));
		bids[cards] = get_bid(line);
	}
	while (!pq.empty()) {
		hand curr = pq.top();
		//cout << "Rank " << rank << ": " << curr.first << " " << curr.second << endl; // Debugging
		pq.pop();
		total_winnings += rank * bids[curr.first];
		rank--;
	}
	return total_winnings;
}

void test(int part, deque<string> &input) {
	if (part == 1) {
		cout << "Expected answer: 6440" << endl;

		int answer = get_total_winnings(input);
		cout << "Calculated answer: " << answer << endl;
		cout << "Difference: " << 6440 - answer << endl;
	} else {
		// part 2
		cout << "Expected answer: 5905" << endl;
		int answer = get_joker_winnings(input);
		cout << "Calculated answer: " << answer << endl;
		cout << "Difference: " << 5905 - answer << endl;
	}
}

void solve(int part, deque<string> &input) {
	if (part == 1) {
		cout << "Expected answer: 255048101" << endl;

		int answer = get_total_winnings(input);
		cout << "Calculated answer: " << answer << endl;
		cout << "Difference: " << 255048101 - answer << endl;
	} else {
		// part 2
		cout << "Expected answer: 253718286" << endl;
		int answer = get_joker_winnings(input);
		cout << "Calculated answer: " << answer << endl;
		cout << "Difference: " << 253718286 - answer << endl;
	}
}

int main(int argc, char** argv){
    deque<string> input;

    if (argc != 4) {
        cerr << "Invalid number of arguments. Please provide 3 arguments: part number (1 or 2), mode (t or s), and file path." << endl;
        return -1;
    }

    if (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0) {
        cerr << "Invalid part number. Please enter 1 or 2." << endl;
        return -1;
    }

    if (strcmp(argv[2], "t") != 0 && strcmp(argv[2], "s") != 0) {
        cerr << "Invalid mode. Please enter t for test or s for solve." << endl;
        return -1;
    }

    if (strcmp(argv[1], "1") == 0) {
        cout << "Part 1" << endl;
    } else {
        cout << "Part 2" << endl;
    }

    try{
        if (readInput(input, argv[3])){
            if (strcmp(argv[2], "t") == 0) {
				test(stoi(argv[1]), input);
			} else {
				solve(stoi(argv[1]), input);
			}
			
			return 0;
        } 
		else {
            throw runtime_error("Error reading input");
        }
    } 
	catch (const exception& e) {
        cerr << "Error reading input: " << e.what() << endl;
        return -1;
    }
}