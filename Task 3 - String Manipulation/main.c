#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverse_string(char* str) {

    const int SIZE = (int) strlen(str);
    for (int i = 0; i < SIZE / 2; ++i) {
        char temp = str[i];
        str[i] = str[SIZE - 1 - i];
        str[SIZE - 1 - i] = temp;
    }
    return str;

}


int count_vowels(const char* str) {
    int count = 0;
    const int SIZE = (int) strlen(str);

    for (int i = 0; i < SIZE; ++i) {
        const char ch = *(str + i);

        if (ch == 'a' || ch == 'A' ||
            ch == 'e' || ch == 'E' ||
            ch == 'i' || ch == 'I' ||
            ch == 'o' || ch == 'O' ||
            ch == 'u' || ch == 'U')
            ++count;
    }

    return count;
}

int is_polyndrome(const char* str) {
    const int SIZE = (int) strlen(str);

    for (int i = 0; i < SIZE / 2; ++i) {
        if (*(str + i) != *(str + SIZE - 1 - i))
            return 0;
    }

    return 1;
}

int main(void) {
    char str[50];

    printf("Enter string: ");
    if (scanf("%49s", str) != 1)
        return 1;

    printf("Enter operation you want to perform:\n");
    printf("1 for counting vowels\n");
    printf("2 for reversing the string\n");
    printf("3 for checking if string is palindrome: ");

    int digit;
    if (scanf("%d", &digit) != 1)
        return 1;

    switch (digit) {
        case 1: {
            const int vowels = count_vowels(str);
            printf("There are %d vowels in the string\n", vowels);
            break;
        }

        case 2: {
            const char* reverse = reverse_string(str);
            printf("Reversed string: %s\n", reverse);
            break;
        }

        case 3:
            if (is_polyndrome(str))
                printf("String is palindrome\n");
            else
                printf("String is not palindrome\n");
            break;

        default:
            printf("Invalid operation\n");
            break;
    }

    return 0;
}


// int count_vowels(const char* str) {
//     int count = 0;
//     const int SIZE = (int) strlen(str);
//     for (int i = 0; i < SIZE; ++i) {
//         const char ch = *(str + i);
//         // A, E, I, O, U
//         if( ch == 'a' || ch == 'A' ||
//             ch == 'e' || ch == 'E' ||
//             ch == 'i' || ch == 'I' ||
//             ch == 'o' || ch == 'O' ||
//             ch == 'u' || ch == 'U' )   
//             ++count;
//     }
//     return count;
// }

// char* reverse_string(char* str) {

//     const int SIZE = (int) strlen(str);
//     for (int i = 0; i < SIZE / 2; ++i) {
//         str[i] = str[SIZE - 1 - i];
//     }
//     return str;

// }

// int is_polyndrome(const char* str) {
//     const int SIZE = (int)strlen(str);
//     for (int i = 0; i < SIZE / 2; ++i) {
//         if (*(str + i) != *(str + SIZE - 1 - i)) return 0;
//     }
//     return 1;
// }

// int main(void) {

//     printf("Enter string: ");
//     char str[50];
//     scanf("%s", str);

//     printf("Enter operation you want to perform \n");
//     printf("1 for counting vowels \n");
//     printf("2 for reversing the string \n");
//     printf("3 for checking if string is polyndrome: ");
//     int digit;
//     scanf("%d", &digit);

//     switch (digit) {
//         case 1: 
//             const int vowels = count_vowels(str);
//             printf("There are %n vowels in the string", &vowels);
        
//         case 2:
//             const char* reverse = reverse_string(str);
//             printf("Reversed string: %s", reverse);

//         case 3: 
//             if(is_polyndrome(str)) printf("String is polyndrome");
//             else printf("String is not polyndrome");

//     }

//     return 0;
// }