#include "myhead.h"

void trimLeadingandTrailing(char *s)
{
    int i, j;

    for (i = 0; s[i] == ' ' || s[i] == '\t'; i++)
        ;

    for (j = 0; s[i]; i++)
    {
        s[j++] = s[i];
    }
    s[j] = '\0';
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != ' ' && s[i] != '\t')
            j = i;
    }
    s[j + 1] = '\0';
}
char *removeBlanks(const char *str)
{
    int i, j;
    char *newString;

    newString = (char *)malloc(20);

    i = 0;
    j = 0;

    while (str[i] != '\0')
    {
        /* If blank space is found */
        if (str[i] == ' ')
        {
            newString[j] = ' ';
            j++;

            /* Skip all consecutive spaces */
            while (str[i] == ' ')
                i++;
        }

        newString[j] = str[i];

        i++;
        j++;
    }
    // NULL terminate the new string
    newString[j] = '\0';

    return newString;
}

int main()
{

    while (1)
    {

        char *prompt = (char *)malloc(sizeof(char) * 1000);
        char *prompt1 = (char *)malloc(sizeof(char) * 1000);
        char *hostname = (char *)malloc(sizeof(char) * 1000);
        char *pwd = (char *)malloc(sizeof(char) * 1000);
        // printf("\x1B[31m");
        strcat(prompt,"\x1B[32m");
        getlogin_r(prompt1, 1000);
        strcat(prompt,prompt1);
        // printf("%s\n", prompt);
        // strcat(prompt,"\x1B[31m");
        //  strcat(prompt,"\033[0m");

        gethostname(hostname, 1000);
        // printf("%s\n", hostname);

        getcwd(pwd, 1000);
        // printf("%s\n", pwd);
        
        strcat(prompt, "\x1B[32m @ \033[32m");
        strcat(prompt, hostname);
        strcat(prompt, "\x1B[32m : \033[31m");
        // printf("\x1B[32m");
        strcat(prompt, pwd);
        strcat(prompt, "$ \033[0m");
        // printf("\033[0m");
        // printf("%s\n", prompt);
        // gcc terminal.c -lreadline -o a.out
        char *input = readline(prompt);
        if (strcmp(input, "") != 0)
            add_history(input);

        // char *exit="exit";
        // printf("%s", exit);
        //  if(strcmp(command,exit)==0)
        //  {
        //      break;
        //  }

        char command[1000];
        // printf("%c\n", command[500]);
        char *cd = command + 3;
        // char exit[1000];
        // char guidance[1000];

        strcpy(command, input);
        // strcpy(exit,input);
        // strcpy(guidance,input);
        trimLeadingandTrailing(command);
        removeBlanks(command);
        // printf("%s\n", command);
        // trimLeadingandTrailing(exit);
        // trimLeadingandTrailing(guidance);
        if (strcmp(command, "cd ~") == 0 || strcmp(command, "cd") == 0)
        {
            chdir("/Users/parthajit");
        }
        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting the terminal...\n");
            break;
        }
        if (strcmp(command, "quit") == 0)
        {
            printf("Exiting the terminal...\n");
            break;
        }
        int cmdcount = 0;

        if (strcmp(command, "help") == 0)
        {
            cmdcount = 1;
            printf("\nTHIS ARE THE BASIC COMMANDS THE SHELL WILL EXECUTE VIA system() COMMAND : \n");
            printf("--------------------------------------------------------------------------\n");
            printf("ls - The most frequently used command in Linux to list directories\n");
            printf("pwd - Print working directory command in Linux\n");
            printf("mkdir - Command used to create directories in Linux\n");
            printf("cat - Display file contents on the terminal\n");
            printf("man - Access manual pages for all Linux commands\n");
            printf("cd - change directory\n");
            printf("cp - copy the contents of file1 to file2 or directory\n");
            printf("mv - move the file1 to the directory or the location of file2\n");
            printf("grep - find a particulalr pattern in a file and print the respective line\n");
            printf("ps - shows the different process currently running\n\n\n");

            printf("TO KNOW ABOUT THE myshell COMMANDS TYPE \"help myshell\" \n");
        }

        if (strcmp(command, "help myls") == 0)
        {
            cmdcount = 1;
            // system("cat ls_help.txt");
            printf("NAME\n");
            printf("    myls - list directory contents\n");
            printf("\n");
            printf("DESCRIPTION\n");
            printf("    For each operand that names a file of a type other than directory, ls displays its name as well as any\n");
            printf("    requested, associated information.  For each operand that names a file of type directory, ls displays the\n");
            printf("    names of files contained within that directory, as well as any requested, associated information.\n");
            printf("\n");
            printf("    If no operands are given, the contents of the current directory are displayed.  If more than one operand is\n");
            printf("    given, non-directory operands are displayed first; directory and non-directory operands are sorted\n");
            printf("    separately and in lexicographical order.\n");
            printf("\n");
            printf("    The following options are available:\n");
            printf("\n");
            printf("    -S  Sort by size (largest file first)\n");
            printf("\n");
            printf("    -a  Include directory entries whose names begin with a dot ('.')\n");
            printf("\n");
            printf("    -l  List files in the long format\n");
            printf("\n");
            printf("    -r  Reverse the order of the sort. Can be used with -t or -S options.\n");
            printf("\n");
            printf("    -t  Sort by descending time modified(most recently modified first)\n");
            printf("\n");
            printf("\n");
            printf("IMPLEMENTATION\n");
            printf("\n");
            printf("    myls -{options}\n");
            printf("    OR\n");
            printf("    myls -{options} -{options}\n");
            printf("    would give a proper output\n");
            printf("\n");
            printf("    If the options are other than S,a,l,r,t then it will give error.\n");
            printf("    Any propmt in format other than the above would give an error.\n");
            printf("\n");
            printf("    If S and t options occur together than the latter options dominates the other.\n");
            printf("    So myls -St executes myls -t.\n");
            printf("\n");
            printf("    Commands like:\n");
            printf("    myls -l -l\n");
            printf("    myls -ll -S\n");
            printf("    myls -llSr\n");
            printf("    would give proper result.\n");
            printf("\n");
            printf("-----------------------------------------END------------------------------------------------\n");
        }
        if (strcmp(command, "help myshell") == 0)
        {
            cmdcount = 1;
            // system("cat myshell_help.txt");
            printf("                          General Commands Manual\n");
            printf("                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Created by Parth Kansagra\n");
            printf("-------------------------\n");
            printf("\n");
            printf("myshell runs the 5 basic commands:\n");
            printf("1.myl\n");
            printf("2.mycp\n");
            printf("3.mymv\n");
            printf("4.mygrep\n");
            printf("5.myps\n");
            printf("        ls:\n");
            printf("        list directory contents\n");
            printf("        To know more type \"help myls\"\n");
            printf("\n");
            printf("        cp:\n");
            printf("        copy files\n");
            printf("        To know more type \"help mycp\"\n");
            printf("\n");
            printf("        mv:\n");
            printf("        move files\n");
            printf("        To know more type \"help mymv\"\n");
            printf("\n");
            printf("        grep:\n");
            printf("        file pattern searcher\n");
            printf("        To know more type \"help mygrep\"\n");
            printf("\n");
            printf("        ps:\n");
            printf("        process status\n");
            printf("        To know more type \"help myps\"\n");
            printf("\n");
            printf("\n");
        }
        if (strcmp(command, "help mycp") == 0)
        {
            cmdcount = 1;
            // system("cat cp_help.txt");
            printf("NAME\n");
            printf("    mycp - copy files\n");
            printf("DESCRIPTION\n");
            printf("    In the first synopsis form, the cp utility copies the contents of the source_file to the target_file.  In\n");
            printf("    the second synopsis form, the contents of each named source_file is copied to the destination\n");
            printf("    target_directory.  The names of the files themselves are not changed.  If cp detects an attempt to copy a\n");
            printf("    file to itself, the copy will fail.\n");
            printf("\n");
            printf("    The following options are available:\n");
            printf("\n");
            printf("    -i  Cause cp to write a prompt to the standard error output before copying a file that would overwrite an\n");
            printf("        existing file.  If the response from the standard input begins with the character ‘y’ or ‘Y’, the file\n");
            printf("        copy is attempted.  (The -i option overrides any previous -n option.)\n");
            printf("\n");
            printf("    -n  Do not overwrite an existing file.  (The -n option overrides any previous -i options.)\n");
            printf("\n");
            printf("    -v  Cause cp to be verbose , showing files as they are copied.\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("IMPLEMENTATION\n");
            printf("\n");
            printf("    mycp -{option} file file/directory\n");
            printf("    Above is the format in which the command shall be executed.\n");
            printf("\n");
            printf("    In case of more than 1 option , the last one would be dominative.\n");
            printf("    If any option other than n,i,v is used , error will be prompted.\n");
            printf("\n");
            printf("    mycp -nn file1 file2 would work;\n");
            printf("    mycp -n -n file1 file2 would give error.\n");
            printf("\n");
            printf("    The command works on strtok() function which will break the prompt string into pieces(max 4).\n");
            printf("    The string tokens are then stored in an array.\n");
            printf("    So the code considers array[2] as file1 and array[3] as file2 or directory.\n");
            printf("    In case of -n -n type command array[3] would be file1 and array[2] would be '-n'.\n");
            printf("    It would try to open the first file , here '-n'.Unable to do so, it will give error and code would not work.\n");
            printf("\n");
            printf("    mycp -n text1.txt text2.txt\n");
            printf("    mycp file1.txt file2.txt\n");
            printf("    mycp file1 dir\n");
            printf("    mycp -i file1 dir\n");
            printf("    These are some examples of code that work.\n");
            printf("\n");
            printf("-----------------------------------------END------------------------------------------------\n");
            printf("\n");
            printf("\n");
        }
        if (strcmp(command, "help mymv") == 0)
        {
            cmdcount = 1;
            // system("cat mv_help.txt");
            printf("NAME\n");
            printf("    mymv - move files\n");
            printf("\n");
            printf("DESCRIPTION \n");
            printf("    In its first form, the mv utility renames the file named by the source operand to the destination path named\n");
            printf("    by the target operand.  This form is assumed when the last operand does not name an already existing\n");
            printf("    directory.\n");
            printf("\n");
            printf("    In its second form, mv moves each file named by a source operand to a destination file in the existing\n");
            printf("    directory named by the directory operand.  The destination path for each operand is the pathname produced by\n");
            printf("    the concatenation of the last operand, a slash, and the final pathname component of the named file.\n");
            printf("\n");
            printf("    The following options are available:\n");
            printf("\n");
            printf("    -i  Cause mv to write a prompt to standard error before moving a file that would overwrite an existing\n");
            printf("        file.  If the response from the standard input begins with the character ‘y’ or ‘Y’, the move is\n");
            printf("        attempted.  (The -i option overrides any previous -n options.)\n");
            printf("\n");
            printf("    -n  Do not overwrite an existing file.  (The -n option overrides any previous -i options.)\n");
            printf("\n");
            printf("    -v  Cause mv to be verbose , showing files as they are removed.\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("IMPLEMENTATION\n");
            printf("\n");
            printf("    mymv -{option} file file/directory\n");
            printf("    Above is the format in which the command shall be executed.\n");
            printf("\n");
            printf("    In case of more than 1 option , the last one would be dominative.\n");
            printf("    If any option other than n,i,v is used , error will be prompted.\n");
            printf("\n");
            printf("    mymv -nn file1 file2 would work;\n");
            printf("    mymv -n -n file1 file2 would give error.\n");
            printf("\n");
            printf("    The command works on strtok() function which will break the prompt string into pieces(max 4).\n");
            printf("    The string tokens are then stored in an array.\n");
            printf("    So the code considers array[2] as file1 and array[3] as file2 or directory.\n");
            printf("    In case of -n -n type command array[3] would be file1 and array[2] would be '-n'.\n");
            printf("    It would try to open the first file , here '-n'.Unable to do so, it will give error and code would not work.\n");
            printf("\n");
            printf("    mymv -n text1.txt text2.txt\n");
            printf("    mymv file1.txt file2.txt\n");
            printf("    mymv file1 dir\n");
            printf("    mymv -i file1 dir\n");
            printf("    These are some examples of code that work.\n");
            printf("\n");
            printf("-----------------------------------------END------------------------------------------------\n");
            printf("\n");
            printf("\n");
        }
        if (strcmp(command, "help mygrep") == 0)
        {
            cmdcount = 1;
            // system("cat grep_help.txt");
            printf("NAME\n");
            printf("    grep - file pattern searcher\n");
            printf("\n");
            printf("DESCRIPTION\n");
            printf("    The grep utility searches any given input files, selecting lines that match one or more patterns.  By\n");
            printf("    default, a pattern matches an input line if the regular expression (RE) in the pattern matches the input\n");
            printf("    line without its trailing newline.  An empty expression matches every line.  Each input line that matches at\n");
            printf("    least one of the patterns is written to the standard output.\n");
            printf("\n");
            printf("    The following options are available:\n");
            printf("\n");
            printf("    -c Only a count of selected lines is written to standard output.\n");
            printf("\n");
            printf("    -i Perform case insensitive matching. By default,grep is case sensitive.\n");
            printf("\n");
            printf("    -n Each output line is preceded by its relative line number in the file, starting at line 1.  The line\n");
            printf("       number counter is reset for each file processed.\n");
            printf("\n");
            printf("    -w The expression is searched for as a word (as if surrounded by '[[:<:]]' and '[[:>:]]').\n");
            printf("\n");
            printf("\n");
            printf("IMPLEMENTATION\n");
            printf("\n");
            printf("    mygrep -{options} pattern file\n");
            printf("    Above is the format in which the command shall be executed.\n");
            printf("\n");
            printf("    In case of more than options, standard dominance rule will be followed i.e. if there is -c then it will dominate all other options.\n");
            printf("    If there is no -c then all the options will do their work.\n");
            printf("\n");
            printf("    mygrep -in pattern file       would work.\n");
            printf("    mygrep -i -n pattern file     would not work.\n");
            printf("\n");
            printf("    The command works on strtok() function which will break the prompt string into pieces(max 4).\n");
            printf("    The string tokens are then stored in an array.\n");
            printf("    So the code considers array[2] as pattern and array[3] as file.\n");
            printf("    In case of -i -n type command array[3] would be pattern and array[2] would be '-n'.\n");
            printf("    So it would take -n as the pattern and search it in the file named 'patern' which if it doesn't exist, gives an error.\n");
            printf("\n");
            printf("    mygrep -i parth text5.txt\n");
            printf("    mygrep advait text1.txt\n");
            printf("    mygrep -in parth text3.txt\n");
            printf("    These are some example of codes that work.\n");
            printf("\n");
            printf("--------------------------------------END------------------------------------------------\n");
            printf("\n");
            printf("\n");
            printf("\n");
        }
        if (strcmp(command, "help myps") == 0)
        {
            cmdcount = 1;
            // system("cat ps_help.txt");
            printf("NAME\n");
            printf("    ps - process status\n");
            printf("\n");
            printf("\n");
            printf("DESCRIPTION\n");
            printf("    The ps utility displays a header line, followed by lines containing information about all of your processes\n");
            printf("    that have controlling terminals.\n");
            printf("\n");
            printf("    The options are as follows:\n");
            printf("\n");
            printf("    -a Display information about other users' processes as well as your own.\n");
            printf("\n");
            printf("    -e Display information about other users' processes, including those without controlling terminals.\n");
            printf("\n");
            printf("    -f Display the uid, pid, parent pid, recent CPU usage, process start time, controlling tty, elapsed CPU\n");
            printf("       usage, and the associated command.When used with -af and -ef it adds to the effect of the options.\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("IMPLEMENTATION\n");
            printf("\n");
            printf("    myps -{options}\n");
            printf("    Aboove is the format in which the command should be executed.\n");
            printf("\n");
            printf("    myshell will execute the following 5 ps commands:\n");
            printf("    1.myps\n");
            printf("    2.myps -a\n");
            printf("    3.myps -e\n");
            printf("    4.myps -af \n");
            printf("    5.myps -ef\n");
            printf("\n");
            printf("    Adding -f with the other options just increase the amount of details getting printed.\n");
            printf("\n");
            printf("    myps -af      would work.\n");
            printf("    myps -a -f    would not work.\n");
            printf("\n");
            printf("    The command uses strtok() function which breaks the command string into different tokens.\n");
            printf("    It stores the different strings into an array. The second element of the array is accessed to check for the options.\n");
            printf("    So if their are more than 2 tokens it will give an error.\n");
            printf("    Giving options other than the mentioned ones will also give an error.\n");
            printf("\n");
            printf("\n");
            printf("-------------------------------------END---------------------------------\n");
            printf("\n");
            printf("\n");
        }
        // if(strcmp(command,"cd ..")==0)
        // {
        //     chdir("..");
        // }
        // if(strcmp(command,"cd /")==0)
        // {
        //     chdir("/");
        // }
        if (command[0] == 'c' && command[1] == 'd')
        {
            chdir(cd);
            cmdcount = 1;
        }

        if (command[0] == 'm' && command[1] == 'y' && command[2] == 'l' && command[3] == 's')
        {
            myls(command, pwd);
            cmdcount = 1;
        }
        if (command[0] == 'm' && command[1] == 'y' && command[2] == 'c' && command[3] == 'p')
        {
            mycp(command, pwd);
            cmdcount = 1;
        }
        if (command[0] == 'm' && command[1] == 'y' && command[2] == 'm' && command[3] == 'v')
        {
            mymv(command, pwd);
            cmdcount = 1;
        }
        if (command[0] == 'm' && command[1] == 'y' && command[2] == 'p' && command[3] == 's')
        {
            myps(command, pwd);
            cmdcount = 1;
        }
        if (command[0] == 'm' && command[1] == 'y' && command[2] == 'g' && command[3] == 'r' && command[4] == 'e' && command[5] == 'p')
        {
            mygrep(command, pwd);
            cmdcount = 1;
        }
        if (cmdcount == 0)
            system(command);
        free(hostname);
        free(prompt);
        free(pwd);
    }

    return 0;
}
