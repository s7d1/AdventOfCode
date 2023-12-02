/*
--- Day 2: Cube Conundrum ---
You're launched high into the atmosphere! The apex of your trajectory just barely reaches the surface of a large island floating in the sky. You gently land in a fluffy pile of leaves. It's quite cold, but you don't see much snow. An Elf runs over to greet you.

The Elf explains that you've arrived at Snow Island and apologizes for the lack of snow. He'll be happy to explain the situation, but it's a bit of a walk, so you have some time. They don't get many visitors up here; would you like to play a game in the meantime?

As you walk, the Elf shows you a small bag and some cubes which are either red, green, or blue. Each time you play this game, he will hide a secret number of cubes of each color in the bag, and your goal is to figure out information about the number of cubes.

To get information, once a bag has been loaded with cubes, the Elf will reach into the bag, grab a handful of random cubes, show them to you, and then put them back in the bag. He'll do this a few times per game.

You play several games and record the information from each game (your puzzle input). Each game is listed with its ID number (like the 11 in Game 11: ...) followed by a semicolon-separated list of subsets of cubes that were revealed from the bag (like 3 red, 5 green, 4 blue).

For example, the record of a few games might look like this:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
In game 1, three sets of cubes are revealed from the bag (and then put back again). The first set is 3 blue cubes and 4 red cubes; the second set is 1 red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.

The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration. However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once; similarly, game 4 would also have been impossible because the Elf showed you 15 blue cubes at once. If you add up the IDs of the games that would have been possible, you get 8.

Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?
*/

#include <stdio.h>
#include <string.h>
#include<ctype.h>

#define BUFFER_SIZE 256
#define max(a,b) ((a) > (b) ? (a) : (b))

// Create arrays for the colours. There are only 100 games provided so we will use 100 as the max size.
int reds[100] = {0};
int blues[100] = {0};
int greens[100] = {0};


int get_game_id(char  line[]){
    int game_id = 0;
    for (int i = 5; i < strlen(line); i++) {   // Start at index 5 to skip the word "Game "
        if (isdigit(line[i])) {
            game_id = game_id * 10 + (line[i] - '0');
        }
        if (line[i] == ':') {   // Get the game number and store it as an int. Game ID is always before the colon.
            return game_id;
        }
    }
    return -1;  // Could not find game ID
}

int get_reds(char line[]){
    int reds = 0;
    int temp = 0;
    char red[3] = "red";
    for (int i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            temp = temp * 10 + (line[i] - '0'); // Convert the char to an int and add it to the temp variable to get the count of cubes
        }
        else if (line[i] == 'r' && strncmp(line+i, red, 3) == 0) {   // We found an instance of the word "red", so the temp number is a count of red cubes.
            reds = max(temp, reds); // To determine whether a given game is possible, we need to know the max count of each colour's cubes. 
            temp = 0;   // reset temp
        }
        else if (!isdigit(line[i]) && line[i] != ' ') { // Non space or digit characters are not useful for determining the count of red cubes.
            temp = 0;   // reset temp
        }
        }
    
    return reds;  // Return the total number of red cubes

}

int get_blues(char line[]){
    int blues = 0;
    int temp = 0;
    char blue[4] = "blue";

    for (int i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            temp = temp * 10 + (line[i] - '0'); // Convert the char to an int and add it to the temp variable to get the count of cubes
        }
        else if (line[i] == 'b' && strncmp(line+i, blue, 4) == 0) {   // We found an instance of the word "blue", so the temp number is a count of blue cubes.
            blues = max(temp, blues);   // To determine whether a given game is possible, we need to know the max count of each colour's cubes.
            temp = 0;   // reset temp
        }
        else if (!isdigit(line[i]) && line[i] != ' ') { // Non space or digit characters are not useful for determining the count of blue cubes.
            temp = 0;   // reset temp
        }
    }
    return blues;   // Return the total number of blue cubes
}

int get_greens(char line[]){
    int greens = 0;
    int temp = 0;
    char green[5] = "green";
    for (int i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            temp = temp * 10 + (line[i] - '0');
        }
        else if (line[i] == 'g' && strncmp(line+i, green, 4) == 0) {  // We found an instance of the word "green", so the temp number is a count of green cubes.
            greens = max(temp, greens); // To determine whether a given game is possible, we need to know the max count of each colour's cubes.
            temp = 0;   // reset temp
        }
        else if (!isdigit(line[i]) && line[i] != ' ') { // Non space or digit characters are not useful for determining the count of green cubes.
            temp = 0;   // reset temp
        }
    }
    return greens;  // Return the total number of green cubes
}

int main() {
    FILE *file = fopen("inputs/day2.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    char line[BUFFER_SIZE]; // Arbitrary buffer size.
    int sum = 0;
    int power = 0;  // num red * green * blue
    int array_index = 0;
    int part1_config[] = {12, 13, 14};  // The configuration of cubes for part 1. 12 reds, 13 greens, 14 blues.
    while (!feof(file)) {
        if (fgets(line, BUFFER_SIZE, file)) {
            // printf("%s\n", line);

            array_index = get_game_id(line) - 1; 
            reds[array_index] += get_reds(line);
            blues[array_index] += get_blues(line);
            greens[array_index] += get_greens(line);

            if (reds[array_index] <= part1_config[0] && greens[array_index] <= part1_config[1] && blues[array_index] <= part1_config[2]) {  // If the max count of each colour's cubes is less than or equal to the part 1 configuration, the game is possible.
                sum += array_index + 1; // Add the game ID to the sum.
            }
            power += reds[array_index] * greens[array_index] * blues[array_index]; // Part 2: Multiply the max count of each colour's cubes for each game. The max count of each colour forms the minimum count of cubes for each game to be possible.
        }
    }
    fclose(file);

    printf("Part 1: %d\nPart 2: %d\n", sum, power);
    return 0;
}
