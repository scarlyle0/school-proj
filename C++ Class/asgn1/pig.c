#include "names.h"

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 10
#define MIN_PLAYERS 2

void game(int8_t players, int64_t seed);
int64_t get_seed(void);

// Purpose: Takes player input then gets the seed and calls the game function
// Return value: Returns
// Parameters accepted: Accepts no parameters
int main(void) {

    int8_t input = 0;
    int64_t real_seed = 0;
    // Takes user input for number of players then checks if its between min and max players
    printf("How many players? ");
    // Comparing scanfs output to 0 checks if scanf successfully read a value
    if ((scanf("%hhd", &input) == 0) || (input < MIN_PLAYERS) || (input > MAX_PLAYERS)) {
        // If player input is not between min and max players set players to 2, get seed and start game
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        input = 2;
        real_seed = get_seed();
        game(input, real_seed);
    } else { // Else use player input and get seed then start game
        real_seed = get_seed();
        game(input, real_seed);
    }
    return 0;
}
// Purpose: gets the seed from user
// Return value: Returns the seed as an int64_t
// Parameters accepted: Accepts no parameters
int64_t get_seed(void) {
    int64_t seed = 0;
    // Takes user input for seed, if unsigned int return
    // If not unsigned int, make seed 2021 then return
    printf("Random seed: ");
    if ((scanf("%ld", &seed) == 0) || (seed < 0) || seed > UINT_MAX) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
        return seed;
    } else {
        return seed;
    }
}

//Purpose: Runs the main pig game
//Return value: Returns nothing
//Parameters accepted: Accepts an int8_t of the amount of players and a int64_t seed
void game(int8_t players, int64_t seed) {
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = {
        SIDE,
        SIDE,
        RAZORBACK,
        TROTTER,
        SNOUTER,
        JOWLER,
        JOWLER,
    };
    srandom(seed);
    uint8_t score[players];
    uint8_t final_score;
    bool game_done = false;
    char winner[15];
    uint8_t roll;
    for (uint8_t j = 0; j < players; j++) { // This loop sets all players score to zero
        score[j] = 0;
    }
    while (game_done != true) { // This loop loops the entire game until it is finished
        for (uint8_t i = 0; i < players; i++) { // This loop loops each players turn every round
            if (game_done == true) {
                break;
            }
            printf("%s rolls the pig... ", names[i]);
            while (true) { // This while loop simulates a single person's turn
                roll = random() % 7; // Rolls a number between 0-6
                // The players turn checks what they position they roll and keeps going until a side is rolled
                if (pig[roll] == SIDE) {
                    printf("pig lands on side\n");
                    break;
                } else if (pig[roll] == RAZORBACK) {
                    printf("pig lands on back");
                    score[i] += 10;
                    if (score[i] < 100) {
                        printf(" ");
                    }
                } else if (pig[roll] == TROTTER) {
                    printf("pig lands upright");
                    score[i] += 10;
                    if (score[i] < 100) {
                        printf(" ");
                    }
                } else if (pig[roll] == SNOUTER) {
                    printf("pig lands on snout");
                    score[i] += 15;
                    if (score[i] < 100) {
                        printf(" ");
                    }
                } else if (pig[roll] == JOWLER) {
                    printf("pig lands on ear");
                    score[i] += 5;
                    if (score[i] < 100) {
                        printf(" ");
                    }
                }
                if (score[i] >= 100) { // When a player hits a score > 100 the game is won
                    game_done = true;
                    strcpy(winner, names[i]);
                    final_score = score[i];
                    break;
                }
            }
        }
    }
    printf("\n%s wins with %d points!\n", winner, final_score);
    return;
}
