#include "myhead.h"

int mygrep(char *command, char *pwd)
{
    if (command[6] != ' ')
    {
        printf("error : command not found \n");
        return 0;
    }
    char *newcommand = removeBlanks(command);
    char *cmdarray[100];
    int k = 0;
    cmdarray[k] = strtok(newcommand, " ");
    while (cmdarray[k] != NULL)
        cmdarray[++k] = strtok(NULL, " ");
    // for (int j = 0; j < 3 /*strlen(cmdarray)*/; j++)
    // {
    //     // printf("%s",basename(cmdarray[i]));
    //     basename(cmdarray[j]);
    // }
    // printf("the number of diff tokens is : %d\n", k);
    if (cmdarray[1][0] != '-')
    {

        // Open the file for reading
        FILE *file = fopen(cmdarray[2], "r");
        if (file == NULL)
        {
            perror(cmdarray[2]);
            return 0;
        }

        // Read each line of the file and search for the pattern
        char line[1000];
        while (fgets(line, 1000, file))
        {
            if (strstr(line, cmdarray[1]))
            {

                printf("%s", line);
            }
        }
        printf("\n");
        // Close the file and exit
        fclose(file);
        return 0;
    }
    else
    {
        // Check for correct usage
        // if (k < 3)
        // {
        //     fprintf(stderr, "Usage: %s [-incw] pattern filename\n", cmdarray[0]);
        //     return 0;
        // }

        // Check which options are set
        int ignore_case = 0;
        int show_line_numbers = 0;
        int count_matches_only = 0;
        int match_whole_word_only = 0;
        int pattern_index = 2;
        for (int i = 1; /*cmdarray[1][i]!=' '*/; i++)
        {
            if (cmdarray[1][i] == 'i')
            {
                ignore_case = 1;
            }
            else if (cmdarray[1][i] == 'n')
            {
                show_line_numbers = 1;
            }
            else if (cmdarray[1][i] == 'c')
            {
                count_matches_only = 1;
            }
            else if (cmdarray[1][i] == 'w')
            {
                match_whole_word_only = 1;
            }
            else if (cmdarray[1][i] == ' ')
            {
                break;
            }
            else if (cmdarray[1][i] == '\0')
            {
                break;
            }
            else
            {
                printf("error : command not found\n");
                return 0;
            }
        }

        // Open the file for reading
        FILE *file = fopen(cmdarray[3], "r");
        if (file == NULL)
        {
            perror(cmdarray[3]);
            return 0;
        }

        // Read each line of the file and search for the pattern
        char line[1000];
        int num_matches = 0;
        int line_number = 0;
        while (fgets(line, 1000, file))
        {
            line_number++;
            char *match;
            if (ignore_case)
            {
                match = strcasestr(line, cmdarray[pattern_index]);
            }
            else
            {
                match = strstr(line, cmdarray[pattern_index]);
            }

            if (match)
            {
                int word_only = 0;
                if (match_whole_word_only)
                {
                    // Check if the match is a whole word
                    int match_start = match - line;
                    int match_end = match_start + strlen(cmdarray[pattern_index]);
                    if ((match_start == 0 || !isalnum(line[match_start - 1])) &&
                        (match_end == strlen(line) || !isalnum(line[match_end])))
                    {
                        num_matches++;
                        word_only = 1;

                    }
                }
                else
                {
                    num_matches++;
                }

                if (show_line_numbers && (match_whole_word_only == 1 && word_only == 1))
                {
                    printf("%d:", line_number);
                }
                if (show_line_numbers && (match_whole_word_only == 0))
                {
                    printf("%d:", line_number);
                }

                if (match_whole_word_only == 1 && word_only == 1 && count_matches_only==0)
                {
                    printf("%s", line);
                }
                
                if (match_whole_word_only == 0 && count_matches_only==0)
                {
                    printf("%s", line);
                }
            }
            
        }

        // Print the number of matches if -c option is set
        if (count_matches_only)
        {
            printf("\n%d\n", num_matches);
        }

        // Close the file and exit
        fclose(file);
        return 0;
    }
}