#include "myhead.h"

int mymv(char *command, char *pwd)
{
    if (command[4] != ' ')
    {
        printf("error : command not found \n");
        return 0;
    }
    int i = 0, n = 0, v = 0;
    char *newcommand = removeBlanks(command);
    char *cmdarray[100];
    int k = 0;
    cmdarray[k] = strtok(newcommand, " ");
    while (cmdarray[k] != NULL)
        cmdarray[++k] = strtok(NULL, " ");
    for (int j = 0; j < 3 /*strlen(cmdarray)*/; j++)
    {
        // printf("%s",basename(cmdarray[i]));
        basename(cmdarray[i]);
    }

    if (cmdarray[1][0] != '-')
    {
        int overwrite = 1;
        char *source_path = cmdarray[1];
        char *destination_path = cmdarray[2];

        // Get the base name of the source file or directory
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file or directory
        char destination_path_full[1024];
        struct stat destination_stat;
        if (stat(destination_path, &destination_stat) == 0 && S_ISDIR(destination_stat.st_mode))
        {
            snprintf(destination_path_full, sizeof(destination_path_full), "%s/%s", destination_path, source_basename);
        }
        else
        {
            strcpy(destination_path_full, destination_path);
        }

        // Check if the destination file or directory already exists
        int result = access(destination_path_full, F_OK);
        // if (result == 0)
        // {
        //     if (overwrite)
        //     {
        //         // Prompt the user for confirmation before overwriting the destination file or directory
        //         printf("overwrite '%s'? (y/n): ", destination_path_full);
        //         char response = getchar();
        //         if (response != 'y' && response != 'Y')
        //         {
        //             exit(EXIT_SUCCESS);
        //         }
        //     }
        //     else
        //     {
        //         // Don't overwrite the destination file or directory
        //         printf("'%s' already exists\n", destination_path_full);
        //         exit(EXIT_SUCCESS);
        //     }
        // }

        // Rename the source file or directory to the destination file or directory
        result = rename(source_path, destination_path_full);
        if (result != 0)
        {
            perror("Error moving file or directory");
            return 0;
        }

        // Display verbose output
        // printf("'%s' -> '%s'\n", source_path, destination_path_full);

        return 0;
    }
    else
    {

        for (int j = 1; cmdarray[1][j] != '\0'; j++)
        {
            if (cmdarray[1][j] == 'n')
            {
                n = 1;
                i = 0;
                v = 0;
            }
            if (cmdarray[1][j] == 'i')
            {
                i = 1;
                v = 0;
                n = 0;
            }
            if (cmdarray[1][j] == 'v')
            {
                v = 1;
                i = 0;
                n = 0;
            }
            if (cmdarray[1][j] != 'i' && cmdarray[1][j] != 'n' && cmdarray[1][j] != 'v')
            {
                printf("Error: command not found \n");
                return 0;
            }
        }
    }

    if (i == 1)
    {

        char *source_path = cmdarray[2];
        char *destination_path = cmdarray[3];

        // Parse command line options

        // Get the base name of the source file or directory
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file or directory
        char destination_path_full[1024];
        struct stat destination_stat;
        if (stat(destination_path, &destination_stat) == 0 && S_ISDIR(destination_stat.st_mode))
        {
            snprintf(destination_path_full, sizeof(destination_path_full), "%s/%s", destination_path, source_basename);
        }
        else
        {
            strcpy(destination_path_full, destination_path);
        }

        // Check if the destination file or directory already exists
        int result = access(destination_path_full, F_OK);
        if (result == 0)
        {

            // Prompt the user for confirmation before overwriting the destination file or directory
            printf("overwrite '%s'? (y/n): ", destination_path_full);
            char response = getchar();
            if (response != 'y' && response != 'Y')
            {
                return 0;
            }
        }

        // Rename the source file or directory to the destination file or directory
        result = rename(source_path, destination_path_full);
        if (result != 0)
        {
            perror("Error moving file or directory");
            return 0;
        }

        return 0;
    }
    else if (n == 1)
    {

        char *source_path = cmdarray[2];
        char *destination_path = cmdarray[3];

        // Parse command line options

        // Get the base name of the source file or directory
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file or directory
        char destination_path_full[1024];
        struct stat destination_stat;
        if (stat(destination_path, &destination_stat) == 0 && S_ISDIR(destination_stat.st_mode))
        {
            snprintf(destination_path_full, sizeof(destination_path_full), "%s/%s", destination_path, source_basename);
        }
        else
        {
            strcpy(destination_path_full, destination_path);
        }

        // Check if the destination file or directory already exists
        int result = access(destination_path_full, F_OK);
        if (result == 0)
        {

            // Don't overwrite the destination file or directory
            printf("'%s' already exists\n", destination_path_full);
            return 0;
        }

        // Rename the source file or directory to the destination file or directory
        result = rename(source_path, destination_path_full);
        if (result != 0)
        {
            perror("Error moving file or directory");
            return 0;
        }

        return 0;
    }
    else if (v == 1)
    {
        
        char *source_path = cmdarray[2];
        char *destination_path = cmdarray[3];

        // Parse command line options
        

        // Get the base name of the source file or directory
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file or directory
        char destination_path_full[1024];
        struct stat destination_stat;
        if (stat(destination_path, &destination_stat) == 0 && S_ISDIR(destination_stat.st_mode))
        {
            snprintf(destination_path_full, sizeof(destination_path_full), "%s/%s", destination_path, source_basename);
        }
        else
        {
            strcpy(destination_path_full, destination_path);
        }

        // Check if the destination file or directory already exists
        int result = access(destination_path_full, F_OK);
        

        // Rename the source file or directory to the destination file or directory
        result = rename(source_path, destination_path_full);
        if (result != 0)
        {
            perror("Error moving file or directory");
            return 0;
        }

        // Display verbose output
        printf("'%s' -> '%s'\n", source_path, destination_path_full);

        return 0;
    }
    else
    {
        printf("error : command not found\n");
        return 0;
    }
}