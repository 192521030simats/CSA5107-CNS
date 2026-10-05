#include <stdio.h>
#include <string.h>

int main()
{
    char text[100], key[26], result[100];
    int i;

    printf("Enter plaintext: ");
    scanf("%s", text);

    printf("Enter 26-letter substitution key: ");
    scanf("%s", key);

    for(i = 0; text[i] != '\0'; i++)
        result[i] = key[text[i] - 'A'];

    result[i] = '\0';

    printf("Ciphertext: %s", result);

    return 0;
}
