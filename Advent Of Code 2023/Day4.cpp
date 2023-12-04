/*
--- Day 4: Scratchcards ---
The gondola takes you up. Strangely, though, the ground doesn't seem to be coming with you; you're not climbing a mountain. As the circle of Snow Island recedes below you, an entire new landmass suddenly appears above you! The gondola carries you to the surface of the new island and lurches into the station.

As you exit the gondola, the first thing you notice is that the air here is much warmer than it was on Snow Island. It's also quite humid. Is this where the water source is?

The next thing you notice is an Elf sitting on the floor across the station in what seems to be a pile of colorful square cards.

"Oh! Hello!" The Elf excitedly runs over to you. "How may I be of service?" You ask about water sources.

"I'm not sure; I just operate the gondola lift. That does sound like something we'd have, though - this is Island Island, after all! I bet the gardener would know. He's on a different island, though - er, the small kind surrounded by water, not the floating kind. We really need to come up with a better naming scheme. Tell you what: if you can help me with something quick, I'll let you borrow my boat and you can go visit the gardener. I got all these scratchcards as a gift, but I can't figure out what I've won."

The Elf leads you over to the pile of colorful cards. There, you discover dozens of scratchcards, all with their opaque covering already scratched off. Picking one up, it looks like each card has two lists of numbers separated by a vertical bar (|): a list of winning numbers and then a list of numbers you have. You organize the information into a table (your puzzle input).

As far as the Elf has been able to figure out, you have to figure out which of the numbers you have appear in the list of winning numbers. The first match makes the card worth one point and each match after the first doubles the point value of that card.

For example:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
In the above example, card 1 has five winning numbers (41, 48, 83, 86, and 17) and eight numbers you have (83, 86, 6, 31, 17, 9, 48, and 53). Of the numbers you have, four of them (48, 83, 17, and 86) are winning numbers! That means card 1 is worth 8 points (1 for the first match, then doubled three times for each of the three matches after the first).

Card 2 has two winning numbers (32 and 61), so it is worth 2 points.
Card 3 has two winning numbers (1 and 21), so it is worth 2 points.
Card 4 has one winning number (84), so it is worth 1 point.
Card 5 has no winning numbers, so it is worth no points.
Card 6 has no winning numbers, so it is worth no points.
So, in this example, the Elf's pile of scratchcards is worth 13 points.

Take a seat in the large pile of colorful cards. How many points are they worth in total?

Your puzzle answer was 23235.

--- Part Two ---
Just as you're about to report your findings to the Elf, one of you realizes that the rules have actually been printed on the back of every card this whole time.

There's no such thing as "points". Instead, scratchcards only cause you to win more scratchcards equal to the number of winning numbers you have.

Specifically, you win copies of the scratchcards below the winning card equal to the number of matches. So, if card 10 were to have 5 matching numbers, you would win one copy each of cards 11, 12, 13, 14, and 15.

Copies of scratchcards are scored like normal scratchcards and have the same card number as the card they copied. So, if you win a copy of card 10 and it has 5 matching numbers, it would then win a copy of the same cards that the original card 10 won: cards 11, 12, 13, 14, and 15. This process repeats until none of the copies cause you to win any more cards. (Cards will never make you copy a card past the end of the table.)

This time, the above example goes differently:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
Card 1 has four matching numbers, so you win one copy each of the next four cards: cards 2, 3, 4, and 5.
Your original card 2 has two matching numbers, so you win one copy each of cards 3 and 4.
Your copy of card 2 also wins one copy each of cards 3 and 4.
Your four instances of card 3 (one original and three copies) have two matching numbers, so you win four copies each of cards 4 and 5.
Your eight instances of card 4 (one original and seven copies) have one matching number, so you win eight copies of card 5.
Your fourteen instances of card 5 (one original and thirteen copies) have no matching numbers and win no more cards.
Your one instance of card 6 (one original) has no matching numbers and wins no more cards.
Once all of the originals and copies have been processed, you end up with 1 instance of card 1, 2 instances of card 2, 4 instances of card 3, 8 instances of card 4, 14 instances of card 5, and 1 instance of card 6. In total, this example pile of scratchcards causes you to ultimately have 30 scratchcards!

Process all of the original and copied scratchcards until no more scratchcards are won. Including the original set of scratchcards, how many total scratchcards do you end up with?

Your puzzle answer was 5920640.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <deque>

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

pair<vector<int>, unordered_set<int>> parse_line(string line){
/*
    Parses a line of the input file and returns a pair of vector, unordered_set. The vector contains the numbers on the card. The set contains the winning numbers.
    Initially I used a vector for the winning numbers too, but then I realized that I don't need to keep track of the order of the winning numbers. So I switched to a set.
    This was done because later I will need to find each element in the vector of my numbers in the set of winning numbers. This is O(n) for a vector and θ(1) for an unordered_set.
    Inserting into the set is also θ(1) as we are expecting zero collisions so there is no performance penalty for using a set instead of a vector. Inserting into a vector is O(1) amortized.
*/
    vector<int> my_numbers;
    unordered_set<int> winning_numbers;
    int number = 0;
    bool encountered_colon = false;
    bool encountered_separator = false;
    // First 5 characters are "Card ". Skip them. After that we have a number for the card followed by a colon. Skip them too.
    for (int i = 5; i <= line.length(); i++){
        if (line[i] == ':'){
            encountered_colon = true;        
        }
        if (line[i] == '|'){
            encountered_separator = true;
        }

        if (encountered_colon && !encountered_separator){
            if (isdigit(line[i])){
                number = number * 10 + (line[i] - '0');
            }
            else if (line[i] == ' ' && number != 0){
                winning_numbers.insert(number);
                number = 0;
            }
        }

        if (encountered_separator){
            if (isdigit(line[i])){
                number = number * 10 + (line[i] - '0');
            }
            else if (line[i] == ' ' && number != 0){
                my_numbers.push_back(number);
                number = 0;
            }
        }

    }
    my_numbers.push_back(number);   // The last number on the line is not followed by a space. So we need to add it to the vector.
    return make_pair(my_numbers, winning_numbers);
}

int get_num_winning_numbers(vector<int> &my_numbers, unordered_set<int> &winning_numbers){
    /*
    Returns the number of winning numbers on the card.
    Iterating over the vector is O(n). Finding an element in the unordered_set is θ(1). Time complexity O(n). 
    */
    int num_winning_numbers = 0;
    for (int i = 0; i < my_numbers.size(); i++){
        // cout << "Checking number:" << my_numbers[i] << endl; // For debugging purposes
        if (winning_numbers.find(my_numbers[i]) != winning_numbers.end()){
            // cout << "Found winning number: " << my_numbers[i] << endl; // For debugging purposes
            num_winning_numbers++;
        }
    }
    return num_winning_numbers;
}

int calculate_points(int num_winning_numbers){
    /*
    Returns the number of points for the card.
    θ(1) as we are doing a bitwise left shift.
    */
    if (num_winning_numbers == 0){
        // cout << "Points for this line: 0" << endl; // For debugging purposes
        return 0;
    }
    // Calculate 2^n using bitwise left shift
    int points = 1 << (num_winning_numbers - 1);
    // cout << "Points for this line: " << points << endl; // For debugging purposes
    return points;
}

int total_points(deque<string> &lines){
    /*
    Returns the total number of points for all the cards.
    Let m be the number of lines and n be the number of characters in each line.
    Iterating over all lines is O(m). Parsing each line is O(n). Calculating the number of winning numbers is O(numbers_on_line) which is O(n). Calculating the points is θ(1).
    Time complexity: O(m*(n + n + 1)) = O(m*n)
    */
    int total_points = 0;
    for (auto i = lines.begin(); i != lines.end(); ++i){
        // cout << *i << endl; // For debugging purposes
        pair<vector<int>, unordered_set<int>> card = parse_line(*i);
        int num_winning_numbers = get_num_winning_numbers(card.first, card.second);
        total_points += calculate_points(num_winning_numbers);
    }
    return total_points;
}

void test_part1(deque<string> &lines){
    string line = lines.front();
    int num_lines = 0;
    int answer = 0;
    int i = 0;
    while (line[i] != ' ') {
        num_lines = num_lines * 10 + (line[i] - '0');
        i++;
    }
    cout << "num_lines: " << num_lines << endl;
    // breaks when line[i] == ' '
    // increase i by one to skip the space
    // then read the next number, till '/n'
    i++;
    while (isdigit(line[i])) {
        answer = answer * 10 + (line[i] - '0');
        i++;
    }
    // delete the first element of the since it was used to get the number of lines and the answer and wasn't part of the actual input.
    // initially I used a vector but then I realized that I should use a deque (double ended queue) instead.
    // I need to delete the first element of the deque. This is O(1) for a deque and O(n) for a vector all the elements will be shifted by one after it.
    lines.pop_front();
    int points = total_points(lines); 
    cout << "Expected answer: " << answer << endl;
    cout << "Calculated answer: " << points << endl;
    cout << "Difference: " << answer - points << endl;
}

int get_card_number(string line){
    /*
    Returns the card number. Constant time complexity θ(1), as it depends on the number of digits in card number only. Our card numbers are up to 3 digits. So the function is O(1).
    */
    for (int i = 5; i <= line.length(); i++){
        if (line[i] == ':'){
            return stoi(line.substr(5, i - 5));
        }
    }
    return -1; // error empty string
}

int get_cards_won(int card_num, int limit, int num_wins, unordered_map<int, int> &cards_won){
    /*
    Returns the number of cards won by this card. We use tabulation to get the number of cards won by this card instead of recursion.
    If card_num + num_wins > limit, then we only add the cards that this card wins up to the limit.
    Time complexity: O(num_wins * 1) as we are doing a num_wins number of lookups in our hash_map.
    This num_wins is a fraction of n, the total number of numbers on our card. So the time complexity is O(n).
    */
            // This card doesn't win anything. So we only add this card to the total.
            if (num_wins == 0){
                return 0;
            }
            int cards_won_by_this_card = num_wins;
            for (int i = card_num + 1; i <= card_num + num_wins; i++){
                if (i <= limit){
                    cards_won_by_this_card += cards_won[i];
                }
            }
            return cards_won_by_this_card;
            /* 
            This card wins some cards. We need to add them to the hash_table/map.
            Remember, we are going in reverse order. So the cards that this card wins are already in the hash_table/map.
            */
}

int get_total_cards(deque<string> &lines){
    /*
    Returns the total number of cards.
    Each card wins some cards after it. Those cards can also further win cards. This is a recursive process. I need to keep track of the cards that I have won so far.
    I should build a lookup for each card. The lookup should contain the cards the card wins. I can use a hash_table/hash_map.
    Naively, I can iterate over the cards and for each card, get the number of winning numbers. Then for the next num_winning_numbers cards, I repeat this and find their winning numbers.
    This keeps going until I reach a card with no winning numbers. All these cards are added to my total, even if they didn't win anything.
    This would be recursing too much.
    Instead, I can start iterating from the last card. I build a hash_table/map since it has θ(1) lookup and insert in this case since we will not get any collisions.
    Justification for no collisions: Key = card number. Value = int num_additional_cards. Our keys are uniformly distributed. Therefore we should get minimal collisions.

    Let m be the number of lines and n be the number of characters on each line.
    Iterating over all lines is O(m). Parsing each line is O(n). 
    Getting number of wins is O(n). Getting card numbers is θ(1).
    Getting cards won is O(num_wins * 1) = O(n) as we are doing a num_wins number of lookups in our hash_map.
    Time complexity: O(m*(n + n + 1 + n)) = O(m*n)
    Note: getting the card number didn't have to be a function in this case. However, if the card numbers were not in a sequence, then we would need to parse the line to get the card number.
    */
    int total_cards = lines.size();
    int limit = lines.size();
    unordered_map<int, int> cards_won;
    cards_won.reserve(total_cards); // Reserve space for the hash_table/map. 
    // This is not necessary but it is good practice to reserve space for the hash_table/map if we know the size beforehand.
    // This is because the hash_table/map will need to be resized if we don't reserve space. This is an expensive operation.
    // Resizing is O(n) where n is the number of elements in the hash_table/map.

    // Iterate over the cards in reverse order
    for (auto it = lines.rbegin(); it != lines.rend(); ++it){
        pair<vector<int>, unordered_set<int>> card = parse_line(*it);
        int num_winning_numbers = get_num_winning_numbers(card.first, card.second);
        int card_number = get_card_number(*it);
        int cards_won_by_this_card = get_cards_won(card_number, limit, num_winning_numbers, cards_won);        
        cards_won.insert({card_number, cards_won_by_this_card});
        total_cards += cards_won_by_this_card;   
    }
    return total_cards;
}

void test_part2(deque<string> &lines){
    /*
    Part 2 I can reuse some functions from part 1. I still need to parse the line and get the numbers. I also need to calculate the number of winning numbers.
    Therefore I can reuse parse_line and get_num_winning_numbers. I don't need to calculate the points anymore. Instead I need to make copies of num_winning_numbers cards after current card, capped at the last card.
    */
    string line = lines.front();
    int num_lines = 0;
    int part1_answer = 0;
    int part2_answer = 0;
    int i = 0;
    while (line[i] != ' ') {
        num_lines = num_lines * 10 + (line[i] - '0');
        i++;
    }
    cout << "num_lines: " << num_lines << endl;
    // breaks when line[i] == ' '
    // increase i by one to skip the space
    // then read the next number, till '/n'
    i++;
    while (isdigit(line[i])) {
        part1_answer = part1_answer * 10 + (line[i] - '0');
        i++;
    }
    i++;
    while (isdigit(line[i])) {
        part2_answer = part2_answer * 10 + (line[i] - '0');
        i++;
    }
    // delete the first element of the since it was used to get the number of lines and the answer and wasn't part of the actual input.
    // initially I used a vector but then I realized that I should use a deque (double ended queue) instead.
    // I need to delete the first element of the deque. This is O(1) for a deque and O(n) for a vector all the elements will be shifted by one after it.
    lines.pop_front();
    int cards = get_total_cards(lines); 
    cout << "Expected answer: " << part2_answer << endl;
    cout << "Calculated answer: " << cards << endl;
    cout << "Difference: " << part2_answer - cards << endl;
}

void solve_part1(deque<string> &lines){
    int points = total_points(lines); 
    cout << "Part 1 total points: " << points << endl;
}

void solve_part2(deque<string> &lines){
    int cards = get_total_cards(lines); 
    cout << "Part 2 total cards: " << cards << endl;
}

int main() {
    deque<string> lines;
    
    //readInput(lines, "inputs/sample_day4.txt");
    //test_part1(lines);
    //test_part2(lines);
    readInput(lines, "inputs/day4.txt");
    //solve_part1(lines);
    solve_part2(lines);
    return 0;
}