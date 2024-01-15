#include "myhead.h"

int mycp(char *command, char *pwd)
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

    if (cmdarray[1][0] != '-')
    {
        for (int j = 0; j < 3 /*strlen(cmdarray)*/; j++)
        {
            // printf("%s",basename(cmdarray[i]));
            basename(cmdarray[j]);
        }
    }
    else if(cmdarray[1][0] == '-')
    {
        for (int j = 0; j < 4 /*strlen(cmdarray)*/; j++)
        {
            // printf("%s",basename(cmdarray[i]));
            basename(cmdarray[j]);
        }
    }
    else
    {
        printf("error:command not found\n");
        return 0;
    }

    if (cmdarray[1][0] != '-')
    {

        //   for (i = 0; i < 100; ++i)
        //     printf("%s\n", cmdarray[i]);
        FILE *fptr1, *fptr2;
        fptr1 = fopen(cmdarray[1], "rb");
        fptr2 = fopen(cmdarray[2], "wb");
        if (fptr1 == NULL)
        {
            printf("Cannot open file %s \n", cmdarray[1]);
            return 0;
        }
        // if (fptr2 == NULL)
        // {
        //     printf("Cannot open file %s \n", cmdarray[2]);
        //     return 0;
        // }

        if (fptr1 != NULL && fptr2 != NULL)
        {
            int c = fgetc(fptr1);
            while (c != EOF)
            {
                fputc(c, fptr2);
                c = fgetc(fptr1);
            }
            fclose(fptr1);
            fclose(fptr2);
            return 0;
        }
        else
        {
            fclose(fptr1);
            fclose(fptr2);
            const char *input_file_path = cmdarray[1];
            const char *output_directory_path = cmdarray[2];
            FILE *input_file = fopen(input_file_path, "rb");
            if (input_file == NULL)
            {
                perror("Error opening input file");
                return 0;
            }
            // Extract the filename from the input file path
            const char *input_filename = strrchr(input_file_path, '/');
            if (input_filename == NULL)
            {
                input_filename = input_file_path;
            }
            else
            {
                input_filename++;
            }
            char output_file_path[1024];
            snprintf(output_file_path, sizeof(output_file_path), "%s/%s", output_directory_path, input_filename);
            FILE *output_file = fopen(output_file_path, "wb");
            if (output_file == NULL)
            {
                perror("Error opening output file");
                return 0;
            }

            // Copy the contents of the input file to the output file
            char buffer[1024];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, 1024, input_file)) > 0)
            {
                fwrite(buffer, 1, bytes_read, output_file);
            }

            // Close the input and output files
            fclose(input_file);
            fclose(output_file);
            return 0;
        }
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

        // Get the base name of the source file
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file
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

        // Check if the destination file already exists
        FILE *destination_file = fopen(destination_path_full, "r");
        if (destination_file != NULL)
        {
            // Prompt the user for confirmation before overwriting the destination file
            printf("overwrite '%s'? (y/n): ", destination_path_full);
            char response = getchar();
            if (response != 'y' && response != 'Y')
            {
                fclose(destination_file);
                return 0;
            }
            fclose(destination_file);
        }

        // Open the source file for reading
        FILE *source_file = fopen(source_path, "rb");
        if (source_file == NULL)
        {
            perror("Error opening source file");
            return 0;
        }

        // Open the destination file for writing
        destination_file = fopen(destination_path_full, "wb");
        if (destination_file == NULL)
        {
            perror("Error opening destination file");
            return 0;
        }

        // Copy the contents of the source file to the destination file
        char buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, 1024, source_file)) > 0)
        {
            fwrite(buffer, 1, bytes_read, destination_file);
        }

        // Close the source and destination files
        fclose(source_file);
        fclose(destination_file);

        // Display verbose output
        // printf("'%s' -> '%s'\n", source_path, destination_path_full);

        return 0;
    }
    else if (n == 1)
    {
        int overwrite = 0;
        char *source_path = cmdarray[2];
        char *destination_path = cmdarray[3];

        // Get the base name of the source file
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file
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

        // Check if the destination file already exists
        FILE *destination_file = fopen(destination_path_full, "r");
        if (destination_file != NULL)
        {

            // Don't overwrite the destination file
            fclose(destination_file);
            printf("'%s' already exists\n", destination_path_full);
            return 0;
        }

        // Open the source file for reading
        FILE *source_file = fopen(source_path, "rb");
        if (source_file == NULL)
        {
            perror("Error opening source file");
            return 0;
        }

        // Open the destination file for writing
        destination_file = fopen(destination_path_full, "wb");
        if (destination_file == NULL)
        {
            perror("Error opening destination file");
            return 0;
        }

        // Copy the contents of the source file to the destination file
        char buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, 1024, source_file)) > 0)
        {
            fwrite(buffer, 1, bytes_read, destination_file);
        }

        // Close the source and destination files
        fclose(source_file);
        fclose(destination_file);

        // Display verbose output
        // printf("'%s' -> '%s'\n", source_path, destination_path_full);

        return 0;
    }
    else if (v == 1)
    {
        int overwrite = 1;
        char *source_path = cmdarray[2];
        char *destination_path = cmdarray[3];

        // Get the base name of the source file
        char *source_basename = strrchr(source_path, '/');
        if (source_basename == NULL)
        {
            source_basename = source_path;
        }
        else
        {
            source_basename++;
        }

        // Construct the full path of the destination file
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

        // Check if the destination file already exists
        FILE *destination_file = fopen(destination_path_full, "r");

        // Open the source file for reading
        FILE *source_file = fopen(source_path, "rb");
        if (source_file == NULL)
        {
            perror("Error opening source file");
            return 0;
        }

        // Open the destination file for writing
        destination_file = fopen(destination_path_full, "wb");
        if (destination_file == NULL)
        {
            perror("Error opening destination file");
            return 0;
        }

        // Copy the contents of the source file to the destination file
        char buffer[1000];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, 1000, source_file)) > 0)
        {
            fwrite(buffer, 1, bytes_read, destination_file);
        }

        // Close the source and destination files
        fclose(source_file);
        fclose(destination_file);

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