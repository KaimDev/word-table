#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>


bool NewWordTable(
    char**** word_table,
    const size_t matriz_count,
    const size_t array_count
)
{
    char*** table = (char***)malloc(sizeof(char **) * matriz_count);

    if (table == NULL)
    {
        return false;
    }

    for (size_t i = 0 ; i < matriz_count ; ++i)
    {
        table[i] = (char**)malloc(sizeof(char*) * array_count);

        if (table[i] == NULL)
        {
            for (; i  > 0 ;)
            {
                free(table[--i]);
            }

            free(table);

            return false;
        }
    }

    *word_table = table;

    return true;
}

void ViewTable(const char*** word_table, size_t rows, size_t columns)
{
    size_t lenght = 0;

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t column = 0; column < columns; ++column)
        {
            if (strlen(word_table[row][column]) > lenght)
            {
                lenght = strlen(word_table[row][column]);
            }
        }
    }

    for (size_t i = 0; i < (lenght * columns + columns + 1); ++i)
    {
        printf("-");
    }

    puts("");

    for (size_t row = 0; row < rows; ++row)
    {
        printf("|");
        for (size_t column = 0; column < columns; ++column)
        {
            printf("%s", word_table[row][column]);
            size_t temp = lenght - strlen(word_table[row][column]);

            for (size_t i = 0; i < temp; ++i)
            {
                printf(" ");
            }

            printf("|");
        }
        puts("");
        for (size_t i = 0; i < (lenght * columns + columns + 1); ++i)
        {
            printf("-");
        }
        puts("");
    }
}

void FreeMemory(char*** word_table, size_t rows, size_t columns)
{
    for (size_t row = (rows - 1); row == 0; --row)
    {
        for (size_t column = (columns - 1); column == 0; --column)
        {
            free(word_table[row][column]);
        }
    }

    for (size_t row = (rows - 1); row == 0; --row)
    {
        free(word_table[row]);
    }

    free(word_table);
}

void ClearBuffer()
{
    char buffer[1024];
    fgets(buffer, 1024, stdin);
}

int32_t main(void)
{
    char*** word_table;
    size_t rows, columns;

    puts("---> Enter the numbers of rows");
    scanf("%lu", &rows);

    puts("---> Enter the numbers of columns");
    scanf("%lu", &columns);

    if(!NewWordTable(&word_table, rows, columns))
    {
        puts("Error in memory");
        return EXIT_FAILURE;
    }

    ClearBuffer();

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t column = 0; column < columns; ++column)
        {
            printf("---> Enter some text\n");
            char text[1024];
            fgets(text, 1024, stdin);
            size_t length = strlen(text);
            text[length - 1] = '\0';
            word_table[row][column] = malloc(sizeof(char) * length);
            strcpy(word_table[row][column], text);
        }
    }

    ViewTable(word_table, rows, columns);
    FreeMemory(word_table, rows, columns);
    return EXIT_SUCCESS;
}