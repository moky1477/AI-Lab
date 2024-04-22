#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int player_hand = 0;
    int dealer_hand = 0;
    int bet_amount = 0;
    int balance = 10000; // Starting balance

    printf("Welcome to the Blackjack game!\n");
    printf("Let's see if you can beat the dealer and win big!\n\n");

    // Play the game until the player runs out of balance
    while (balance > 0) {
        printf("+--------------------------------------------------+\n");
        printf("¦                Your current balance: %-4d          ¦\n", balance);
        printf("+--------------------------------------------------+\n");

        // Get the bet amount from the player
        printf("Enter your bet amount: ");
        scanf("%d", &bet_amount);

        // Check if the bet amount is valid
        if (bet_amount > balance) {
            printf("Sorry, you don't have enough balance to place that bet.\n");
            continue;
        }

        // Deal initial cards
        player_hand = 0;
        dealer_hand = 0;
        player_hand += rand() % 10 + 1;
        player_hand += rand() % 10 + 1;
        dealer_hand += rand() % 10 + 1;
        dealer_hand += rand() % 10 + 1;

        printf("\n");
        printf("+--------------------------------------------------+\n");
        printf("¦                Let's play some Blackjack!         ¦\n");
        printf("+--------------------------------------------------+\n");
        printf("\n");
        printf("Your hand: %d\n", player_hand);
        printf("Dealer's up card: %d\n", dealer_hand - (dealer_hand % 10));

        // Check for insurance
        int dealer_up_card = dealer_hand - (dealer_hand % 10);
        if (dealer_up_card == 11) {
            char insurance_choice;
            printf("Dealer's up card is an Ace. Do you want to take insurance? (y/n): ");
            scanf(" %c", &insurance_choice);

            if (insurance_choice == 'y') {
                int insurance_bet = bet_amount / 2;
                balance -= insurance_bet;

                if (dealer_hand == 21) {
                    printf("\n");
                    printf("+--------------------------------------------------+\n");
                    printf("¦             Dealer has a blackjack. You win!       ¦\n");
                    printf("+--------------------------------------------------+\n");
                    balance += insurance_bet * 3;
                    continue;
                } else {
                    printf("\n");
                    printf("+--------------------------------------------------+\n");
                    printf("¦             Dealer does not have a blackjack.      ¦\n");
                    printf("+--------------------------------------------------+\n");
                }
            }
        }

        // Player's turn
        char choice;
        do {
            printf("\n");
            printf("Do you want to hit or stand? (h/s): ");
            scanf(" %c", &choice);

            if (choice == 'h') {
                player_hand += rand() % 10 + 1;
                printf("Your hand: %d\n", player_hand);
            }
        } while (choice == 'h' && player_hand <= 21);

        // AI Player's turn
        while (dealer_hand < 17) {
            if (dealer_up_card >= 7 && dealer_up_card <= 10) {
                // Stand
                break;
            } else if (dealer_up_card >= 2 && dealer_up_card <= 6) {
                // Hit
                dealer_hand += rand() % 10 + 1;
                printf("Dealer's hand: %d\n", dealer_hand);
            } else {
                // Stand
                break;
            }
        }

        // Determine winner and adjust the balance accordingly
        if (player_hand > 21) {
            printf("\n");
            printf("+--------------------------------------------------+\n");
            printf("¦             You busted! Dealer wins.              ¦\n");
            printf("+--------------------------------------------------+\n");
            balance -= bet_amount;
        } else if (dealer_hand > 21) {
            printf("\n");
            printf("+--------------------------------------------------+\n");
            printf("¦             Dealer busted! You win.                ¦\n");
            printf("+--------------------------------------------------+\n");
            balance += bet_amount;
        } else if (player_hand > dealer_hand) {
            printf("\n");
            printf("+--------------------------------------------------+\n");
            printf("¦                  You win! Congratulations!         ¦\n");
            printf("+--------------------------------------------------+\n");
            balance += bet_amount;
        } else if (dealer_hand > player_hand) {
            printf("\n");
            printf("+--------------------------------------------------+\n");
            printf("¦             Dealer wins. Better luck next time!    ¦\n");
            printf("+--------------------------------------------------+\n");
            balance -= bet_amount;
        } else {
            printf("\n");
            printf("+--------------------------------------------------+\n");
            printf("¦                  You and dealer tie.                ¦\n");
            printf("+--------------------------------------------------+\n");
        }

        // Check if the player wants to continue playing
        char play_again;
        printf("\n");
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &play_again);

        if (play_again == 'n') {
            break;
        }
    }

    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("¦             Game over. You have run out of balance. ¦\n");
    printf("+--------------------------------------------------+\n");

    return 0;
}
