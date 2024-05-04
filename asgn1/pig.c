#include "names.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SEED 2023

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

int main(void) {

    //initalizing needed variables
    int num_players = 2;
    int scanf_result = 0;
    int num_assignments = 0;
    unsigned seed = 2023;

    printf("Number of players (2 to 10)? ");
    scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 2 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        num_players = 2;
    }

    printf("Random-number seed? ");
    //reading in seed
    num_assignments = scanf("%u", &seed);

    //if scanf failed -> setting seed
    if (num_assignments < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
        seed = SEED;
    }

    //using seed scanned in by the user
    srandom(seed);

    int player_score[num_players];

    //iterates and sets points for each player to 0
    for (int i = 0; i < num_players; i++) {
        player_score[i] = 0;
    }

    bool player_won = false;

    int roll = 0;
    int points = 0;
    while (!player_won) {
        for (int i = 0; i < num_players; i++) {
            if (player_won == true) {
                break;
            }
            bool round_won = true;
            printf("%s\n", player_name[i]);
            while (round_won == true && player_won != true) {
                roll = random() % 7;
                switch (pig[roll]) {
                case JOWLER:
                    points = 5;
                    player_score[i] = player_score[i] + 5;
                    printf(" rolls %d, has %d\n", points, player_score[i]);
                    round_won = true;
                    break;

                case RAZORBACK:
                    points = 10;
                    player_score[i] = player_score[i] + 10;
                    printf(" rolls %d, has %d\n", points, player_score[i]);
                    round_won = true;
                    break;

                case TROTTER:
                    points = 10;
                    player_score[i] = player_score[i] + 10;
                    printf(" rolls %d, has %d\n", points, player_score[i]);
                    round_won = true;
                    break;

                case SNOUTER:
                    points = 15;
                    player_score[i] = player_score[i] + 15;
                    printf(" rolls %d, has %d\n", points, player_score[i]);
                    round_won = true;
                    break;

                case SIDE:
                    points = 0;
                    printf(" rolls %d, has %d\n", points, player_score[i]);
                    round_won = false;
                    break;
                }

                if (player_score[i] >= 100) {
                    printf("%s won! \n", player_name[i]);
                    round_won = true;
                    player_won = true;
                    break;
                }
            }
        }
    }

    return 0;
}
