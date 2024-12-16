#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

// Function to convert a string to uppercase
void to_uppercase(char *str)
{
    while (*str)
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

// Function to convert a string to lowercase
void to_lowercase(char *str)
{
    while (*str)
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <source_file> <short_file> <long_file>\n", argv[0]);
        return 1;
    }

    // Open the source file for reading
    FILE *source = fopen(argv[1], "r");
    if (!source)
    {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination files for writing
    FILE *short_file = fopen(argv[2], "w");
    if (!short_file)
    {
        perror("Error opening short file");
        fclose(source);
        return 1;
    }

    FILE *long_file = fopen(argv[3], "w");
    if (!long_file)
    {
        perror("Error opening long file");
        fclose(source);
        fclose(short_file);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int short_count = 0, long_count = 0;

    // Read the source file line by line
    while (fgets(line, sizeof(line), source))
    {
        // Remove the newline character if present
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) < 20)
        {
            to_uppercase(line);
            fprintf(short_file, "%s\n", line);
            short_count++;
        }
        else
        {
            to_lowercase(line);
            fprintf(long_file, "%s\n", line);
            long_count++;
        }
    }

    // Close all files
    fclose(source);
    fclose(short_file);
    fclose(long_file);

    // Display the results
    printf("%d lines written to %s\n", short_count, argv[2]);
    printf("%d lines written to %s\n", long_count, argv[3]);

    return 0;
}
