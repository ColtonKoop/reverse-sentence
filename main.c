#include <stdio.h>
#include <stdlib.h>

/* Function to count the number of words in a string. */
int countWords(char* str) {
    /* Check for empty string */
    if (str[0] == '\0') {
        printf("There are 0 words\n\n");
        return 0;
    }

    int i = 0, word_counter = 0, in_word = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' && !in_word) {
            /* Transition from space to character marks the start of a new word. */
            word_counter++;
            in_word = 1;
        } else if (str[i] == ' ' && in_word) {
            /* Transition from character to space marks the end of a word. */
            in_word = 0;
        }
        i++;
    }

    printf("There are %d words\n\n", word_counter);
    return word_counter;
}

/* Function to count the number of letters in each word of a string. */
int* countLetters(char* str, int word_count) {
    if (word_count == 0) {
        printf("The string is empty or only contains spaces.\n\n");
        return NULL;
    }

    int* word_lengths = malloc(sizeof(int) * word_count);
    if (word_lengths == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int i = 0, j = 0, letter_counter = 0, in_word = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && !in_word) {
            /* Start of a new word */
            in_word = 1;
            letter_counter = 1; /* Start counting letters for the new word */
        } else if (str[i] != ' ' && in_word) {
            /* Inside a word */
            letter_counter++;
        } else if (str[i] == ' ' && in_word) {
            /* End of a word */
            word_lengths[j++] = letter_counter;
            letter_counter = 0;
            in_word = 0;
        }
    }

    if (in_word) {
        /* Account for the last word in case the string doesn't end with a space. */
        word_lengths[j] = letter_counter;
    }

    printf("The word lengths are:\n");
    for (i = 0; i < word_count; i++) {
        printf("word %d: %d\n", i, word_lengths[i]);
    }
    printf("\n");

    return word_lengths;
}

/* Function to reverse the words in a sentence. */
void reverseSentence(char* str) {
    int word_count = countWords(str);
    int* word_lengths = countLetters(str, word_count);

    if (word_lengths != NULL) {
        char** words = malloc(sizeof(char*) * word_count);

        int i;
        for (i = 0; i < word_count; i++) {
            words[i] = malloc(sizeof(char) * (word_lengths[i] + 1));
        }

        int j, pos = 0;
        for (i = 0; i < word_count; i++) {
            for (j = 0; j < word_lengths[i]; j++) {
                while (str[pos] == ' ') pos++; /* Skip any spaces. */
                words[i][j] = str[pos++];
            }
            words[i][j] = '\0'; /* Null-terminate each word */
            printf("%s\n", words[i]);
        }

        pos = 0;
        for (i = word_count - 1; i >= 0; i--) {
            for (j = 0; j < word_lengths[i]; j++) {
                str[pos++] = words[i][j];
            }
            if (i > 0) str[pos++] = ' '; /* Add spaces for all but the last word */
        }
        str[pos] = '\0'; /* Ensure the reconstructed string is null-terminated */

        for (i = 0; i < word_count; i++) {
            free(words[i]); /* Free each word */
            words[i] = NULL;
        }

        free(words); /* Free the array of words */
        free(word_lengths); /* Free the array of word lengths */
    }
}

int main() {
    char str[] = "Lorem ipsum dolor sit amet";
    reverseSentence(str);
    printf("The sentence reversed is:\n%s", str);
    return 0;
}