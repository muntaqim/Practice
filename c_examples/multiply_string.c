#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiply_string(char *string, int value);
int main(int argc, char **argv)
{
    for (int x = 0; x < argc; x++)
    {
        printf("string #%d is %s\n", x, argv[x]);
    }

    if (argc < 3)
    {
        printf("not enough arguments\n");
        return 0;
    }
    char *string = argv[1];
    int mult = atoi(argv[2]);
    multiply_string(string, mult);

    return 0;
}

void multiply_string(char *string, int value)
{
    int length = strlen(string);
    char *newString = (char *)malloc(length*value*sizeof(char) + sizeof(char));

    char *temp = newString;
    for (int x = 0; x < value; x++)
    {
        snprintf(temp, length+1, string);
        temp += length;
    }
    printf ("The final string is: %s", newString);


}

