#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    int random = rand() % 1001;

    int guess;
    printf("Guess the number (0 to 1000, enter -1 whenever to exit the programm): ");
    scanf("%d", &guess);
    while(guess != random) {
        if (-1 == guess) return 0;
        if (guess < random) {
            printf("Too low, try something above %d: ", guess);
            scanf("%d", &guess);
            continue;
        }
        if (guess > random) {
            printf("Too large, try something below %d: ", guess);
            scanf("%d", &guess);
            continue;
        }
    }
    printf("Congratulations, you guessed the number! : %d ", guess);

    return 0;
}