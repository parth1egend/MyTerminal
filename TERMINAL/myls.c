#include "myhead.h"

struct data
{
    char name[100];
    struct stat stats;
};

struct data metadata[100];
int cmprsize(const void *p, const void *q)
{
    int l = (((struct data *)p)->stats).st_size;
    int r = (((struct data *)q)->stats).st_size;
    return r - l;
}
int cmprtime(const void *p, const void *q)
{
    int l = (((struct data *)p)->stats).st_atime;
    int r = (((struct data *)q)->stats).st_atime;
    return r - l;
}
int cmprlexi(const void *p, const void *q)
{
    char *l = (((struct data *)p)->name);
    char *r = (((struct data *)q)->name);
    return strcmp(l, r);
}
int cmprlexiR(const void *p, const void *q)
{
    char *l = (((struct data *)p)->name);
    char *r = (((struct data *)q)->name);
    return strcmp(r, l);
}
void print_perms(mode_t perms)
{
    printf((S_ISDIR(perms)) ? "d" : "-");
    printf((perms & S_IRUSR) ? "r" : "-");
    printf((perms & S_IWUSR) ? "w" : "-");
    printf((perms & S_IXUSR) ? "x" : "-");
    printf((perms & S_IRGRP) ? "r" : "-");
    printf((perms & S_IWGRP) ? "w" : "-");
    printf((perms & S_IXGRP) ? "x" : "-");
    printf((perms & S_IROTH) ? "r" : "-");
    printf((perms & S_IWOTH) ? "w" : "-");
    printf((perms & S_IXOTH) ? "x" : "-");
    printf(" ");
}
char *formatdate(char *str, time_t val)
{
    strftime(str, 36, "   %b   %d   %H:%M:%S", localtime(&val));
    return str;
}
void myls(char *command, char *pwd)
{

    int l = 0, r = 0, S = 0, t = 0, a = 0;
    int error = 0;
    // printf("%s\n", command);
    // printf("%c\n", command[5]);
    for (int i = 4; command[i] != '\0' && error == 0; i++)
    {
        if (command[i] == ' ')
        {
            continue;
        }
        else if (command[i] == '\0')
        {
            break;
        }
        else if (command[i] != 'l' && command[i] != 'S' && command[i] != 'r' && command[i] != 't' && command[i] != '-')
        {
            error = 1;
            printf("error:command or options not found\n");
            break;
        }
        else if (command[i] == '-')
        {
            for (int j = i + 1; command[j] != '\0'; j++)
            {
                int exec = 0;
                if (command[j] == 'l')
                {
                    l = 1;
                    i = j;
                    // printf("l found\n");
                    exec++;
                    continue;
                }
                if (command[j] == 'S')
                {
                    S = 1;
                    t = 0;

                    i = j;
                    exec++;
                    continue;
                }
                if (command[j] == 'r')
                {
                    r = 1;

                    i = j;
                    exec++;
                    continue;
                }
                if (command[j] == 'a')
                {
                    a = 1;
                    i = j;
                    exec++;
                    continue;
                }
                if (command[j] == 't')
                {
                    t = 1;
                    S = 0;

                    i = j;
                    exec++;
                    continue;
                }
                if (command[j] == ' ')
                {
                    i = j;
                    break;
                    exec++;
                }

                if (exec == 0)
                {
                    error = 1;
                    printf("error:options not found\n");
                    break;
                }
            }
        }
        else
        {
            error = 1;
            printf("error :command not found \n");
            // printf("%c\n", command[i]);
            break;
        }
    }

    struct dirent *de;
    DIR *dr = opendir(pwd);
    if (dr == NULL)
    {
        printf("Cannot open current directory.\n");
    }
    int size = 0;
    while ((de = readdir(dr)) != NULL)
    {

        stat(de->d_name, &metadata[size].stats);
        strcpy(metadata[size].name, de->d_name);
        // printf("%s\n", de->d_name);
        size++;
    }
    closedir(dr);

    // for (int i = 0; i < size; i++)
    // {
    //     printf("%s\n", metadata[i].name);
    // }
    qsort(metadata, size, sizeof(metadata[0]), cmprlexi);
    if (S == 1)
    {
        qsort(metadata, size, sizeof(metadata[0]), cmprsize);
    }
    if (t == 1)
    {
        qsort(metadata, size, sizeof(metadata[0]), cmprtime);
    }
    // if (r == 1)
    // {
    //     qsort(metadata, size, sizeof(metadata[0]), cmprlexiR);
    // }
    if (l == 0)
    {
        if (r == 0)
        {
            for (int i = 0; i < size && error == 0; i++)
            {
                if (metadata[i].name[0] == '.' && a == 0)
                {
                    continue;
                }
                else
                    printf("%s\n", metadata[i].name);
            }
        }
        else
        {
            for (int i = size - 1; i >= 0 && error == 0; i--)
            {
                if (metadata[i].name[0] == '.' && a == 0)
                {
                    continue;
                }
                else
                    printf("%s\n", metadata[i].name);
            }
        }
    }
    else
    {
        if (r == 0)
        {

            for (int i = 0; i < size && error == 0; i++)
            {
                if (metadata[i].name[0] == '.' && a == 0)
                {
                    continue;
                }
                else
                {
                    print_perms(metadata[i].stats.st_mode);
                    char date[100]; /*file mode,
                      number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-
                      month file was last modified, hour file last modified, minute file last modified, and the
                      pathname*/

                    printf("    %d ", metadata[i].stats.st_nlink);
                    printf("    %s ", (getpwuid(metadata[i].stats.st_uid))->pw_name);
                    printf("    %s ", (getgrgid(metadata[i].stats.st_gid))->gr_name);
                    printf("    %lld ", metadata[i].stats.st_size);

                    printf("    %s ", formatdate(date, metadata[i].stats.st_mtime));
                    printf("    %s ", metadata[i].name);

                    printf("\n");
                }
            }
        }
        else
        {
            for (int i = size-1; i >= 0 && error == 0; i--)
            {
                if (metadata[i].name[0] == '.' && a == 0)
                {
                    continue;
                }
                else
                {
                    print_perms(metadata[i].stats.st_mode);
                    char date[100]; /*file mode,
                      number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-
                      month file was last modified, hour file last modified, minute file last modified, and the
                      pathname*/

                    printf("    %d ", metadata[i].stats.st_nlink);
                    printf("    %s ", (getpwuid(metadata[i].stats.st_uid))->pw_name);
                    printf("    %s ", (getgrgid(metadata[i].stats.st_gid))->gr_name);
                    printf("    %lld ", metadata[i].stats.st_size);

                    printf("    %s ", formatdate(date, metadata[i].stats.st_mtime));
                    printf("    %s ", metadata[i].name);

                    printf("\n");
                }
            }
        }
    }
}
