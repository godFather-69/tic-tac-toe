#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function to generate random number between 1 and 100
int getRandomNumber() {
    return (rand() % 100) + 1;
}

// Function to validate user input
int validateInput(int min, int max) {
    int input;
    while (1) {
        printf("\nEnter number: ");
        if (scanf("%d", &input) == 1 && input >= min && input <= max) {
            return input;
        } else {
            printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
            while (getchar() != '\n'); // Clear input buffer
        }
    }
}

int main() {
    int num, guess;
    char ch = 'y';

    printf(".....Welcome to Number Guessing Game.....\n");
    printf("Guess a number between 1 to 100\n");
    printf("You have only 10 chances to guess the number\n");

    srand(time(NULL)); // Seed random number generator

    while (tolower(ch) == 'y') {
        num = getRandomNumber();
        int noOfGuess = 10;

        printf("\nNew game started! Guess the number.\n");
        while (noOfGuess > 0) {
            guess = validateInput(1, 100); // Validate user input
            if (guess > num) {
                printf("Too High!\n");
            } else if (guess < num) {
                printf("Too Low!\n");
            } else {
                printf("Congratulations!! You found it!\n");
                break;
            }
            noOfGuess--;
            printf("Chances left: %d\n", noOfGuess);
        }

        if (noOfGuess == 0) {
            printf("Oh no! The number was %d.\n", num);
        }

        printf("\nDo you want to play again? [y/n]: ");
        while (getchar() != '\n'); // Clear input buffer
        // scanf(" %c", &ch);
        ch = getch();
    }

    printf("Thank you for playing!\n");
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
// #include <ctype.h>

// int getRandomNumber()
// {
//     return (rand() % 100);
// }

// int main()
// {
//     int num, guess;
//     char ch = 'y';
//     printf(".....Welcome to Number Guessing Game.....\n");
//     printf("Guess a number between 1 to 100\n");
//     printf("You have only 10 chances to guess the number\n");

//     srand(time(NULL));
//     while (ch == 'y')
//     {
//         num = getRandomNumber();
//         int noOfGuess = 10;

//         while (noOfGuess != 0)
//         {
//             printf("\nEnter number: ");
//             scanf("%d", &guess);
//             if (guess > num)
//             {
//                 printf("Too High!\n");
//                 noOfGuess--;
//                 printf("Chances left: %d\n", noOfGuess);
//             }

//             else if (guess < num)
//             {
//                 printf("Too Low!\n");
//                 noOfGuess--;
//                 printf("Chances left: %d", noOfGuess);
//             }

//             else if (guess == num)
//             {
//                 printf("Congratulations!! You find it\n");
//                 noOfGuess--;
//                 break;
//             }
//         }
//         if (noOfGuess == 0)
//         {
//             printf("Oh!! The number was %d\n", num);
//         }

//         printf("Do you want to play again?[y/n]: ");
//         getchar();
//         scanf(" %c", &ch);
//         {
//             printf("Thank you for playing\n");
//             exit(0);
//         }
//     }

//     return 0;
// }