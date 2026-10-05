#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[])
{
    int used[26] = {0}, i, j, k = 0;
    char ch;

    for(i = 0; key[i]; i++)
    {
        ch = toupper(key[i]);
        if(ch == 'J') ch = 'I';

        if(ch >= 'A' && ch <= 'Z' && !used[ch-'A'])
        {
            matrix[k/5][k%5] = ch;
            used[ch-'A'] = 1;
            k++;
        }
    }

    for(ch = 'A'; ch <= 'Z'; ch++)
    {
        if(ch == 'J') continue;

        if(!used[ch-'A'])
        {
            matrix[k/5][k%5] = ch;
            used[ch-'A'] = 1;
            k++;
        }
    }
}

void findPos(char ch, int *r, int *c)
{
    int i, j;
    if(ch == 'J') ch = 'I';

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
            if(matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
}

int main()
{
    char key[50], text[100], clean[200], result[200];
    int i, n = 0, r1, c1, r2, c2;

    printf("Enter key: ");
    scanf("%s", key);

    printf("Enter plaintext: ");
    scanf("%s", text);

    createMatrix(key);

    for(i = 0; text[i]; i++)
    {
        if(isalpha(text[i]))
        {
            clean[n++] = toupper(text[i]);
            if(clean[n-1] == 'J')
                clean[n-1] = 'I';
        }
    }

    if(n % 2 != 0)
        clean[n++] = 'X';

    for(i = 0; i < n; i += 2)
    {
        if(clean[i] == clean[i+1])
            clean[i+1] = 'X';

        findPos(clean[i], &r1, &c1);
        findPos(clean[i+1], &r2, &c2);

        if(r1 == r2)
        {
            result[i] = matrix[r1][(c1+1)%5];
            result[i+1] = matrix[r2][(c2+1)%5];
        }
        else if(c1 == c2)
        {
            result[i] = matrix[(r1+1)%5][c1];
            result[i+1] = matrix[(r2+1)%5][c2];
        }
        else
        {
            result[i] = matrix[r1][c2];
            result[i+1] = matrix[r2][c1];
        }
    }

    result[n] = '\0';

    printf("\nPlayfair Matrix:\n");
    for(i = 0; i < 5; i++)
        printf("%c %c %c %c %c\n",
               matrix[i][0], matrix[i][1], matrix[i][2],
               matrix[i][3], matrix[i][4]);

    printf("\nCiphertext: %s", result);

    return 0;
}
