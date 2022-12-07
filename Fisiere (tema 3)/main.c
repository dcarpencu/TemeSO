#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void forkFunction(char *option, char *filename);

void print_size(char *filename)
{
    struct stat struct_stat;
    int stat_result = stat(filename, &struct_stat);
    if (stat_result == 0)
    {
        off_t size = struct_stat.st_size;
        printf("\nsize: %llu\n", size);
    }
    else
    {
        perror("stat function nu merge :(");
    }
}

void print_uid(char *filename)
{
    struct stat struct_stat;
    int stat_result = stat(filename, &struct_stat);
    if (stat_result == 0)
    {
        uid_t id = struct_stat.st_uid;
        printf("%lu\n", (unsigned long int) id);
    }
    else
    {
        perror("Error at uid printing!");
    }
}

void print_links(char *filename)
{
    struct stat struct_stat;
    int stat_result = stat(filename, &struct_stat);
    if (stat_result == 0)
    {
        nlink_t links = struct_stat.st_nlink;
        printf("%hu\n", links);
    }
    else
    {
        perror("Error at printing the number of links");
    }
}

void create_links(char *filename)
{
    struct stat struct_stat;
    int stat_result = stat(filename, &struct_stat);
    if (stat_result == 0)
    {
        if (struct_stat.st_size < 100000)
        {
            char aux[256] = "", file[256] = "";
            memcpy(aux, filename, strlen(filename) - 2);
            char *p;
            p = strtok(aux, "/");
            int ct = 0;
            while (p != NULL)
            {
                if (strlen(p) > 0)
                {
                    ct++;
                }
                if (ct == 2)
                {
                    memcpy(file, p, strlen(p) + 1);
                }
                p = strtok(NULL, "/");
            }
            if (symlink(filename, file) == 0)
            {
                printf("%s", "Legatura a fost creata!\n");
            }
        }
    }
    else
    {
        perror("Error at printing the number of links");
    }
}

void print_rights(char *filename)
{
    struct stat struct_stat;
    int stat_result = stat(filename, &struct_stat);
    if (stat_result == 0)
    {
        printf("%s\n", "Utilizator:");
        if (S_IRUSR & struct_stat.st_mode)
        {
            printf("%s\n", "Read - Da");
        }
    else
        {
            printf("%s\n", "Read - Nu");
        }
        if (S_IWUSR & struct_stat.st_mode)
        {
            printf("%s\n", "Write - Da");
        }
    else
        {
            printf("%s\n", "Write - Nu");
        }
        if (S_IXUSR & struct_stat.st_mode)
        {
            printf("%s\n", "Execute - Da");
        }
    else
        {
            printf("%s\n", "Execute - Nu");
        }
        printf("%s\n", "Grup:");
        if (S_IRGRP & struct_stat.st_mode)
        {
            printf("%s\n", "Read - Da");
        }
    else
        {
            printf("%s\n", "Read - Nu");
        }
        if (S_IWGRP & struct_stat.st_mode)
        {
            printf("%s\n", "Write - Da");
        }
    else
        {
            printf("%s\n", "Write - Nu");
        }
        if (S_IXGRP & struct_stat.st_mode)
        {
            printf("%s\n", "Execute - Da");
        }
    else
        {
            printf("%s\n", "Execute - Nu");
        }
        printf("%s\n", "Other:");
        if (S_IROTH & struct_stat.st_mode)
        {
            printf("%s\n", "Read - Da");
        }
    else
        {
            printf("%s\n", "Read - Nu");
        }
        if (S_IWOTH & struct_stat.st_mode)
        {
            printf("%s\n", "Write - Da");
        }
    else
        {
            printf("%s\n", "Write - Nu");
        }
        if (S_IXOTH & struct_stat.st_mode)
        {
            printf("%s\n", "Execute - Da");
        }
    else
        {
            printf("%s\n", "Execute - Nu");
        }
        printf("\n");
    }
    else
    {
        perror("Error at printing file permissions!");
    }
}

void action(char *option, char *filename)
{
    struct stat status;
    for (int i = 1; i < strlen(option); i++)
    {
        switch (option[i])
        {
            case 'n':
                printf("%s\n", filename);
                break;
            case 'u':
                print_uid(filename);
                break;
            case 'd':
                printf("\n --- %s ---\n", filename);
                print_size(filename);
                break;
            case 'c':
                printf("Numar de legaturi - %d\n", status.st_nlink);
                break;
            case 'a':
                print_rights(filename);
                break;
                //            default:
                //                printf("INVALID INPUT");
                //                break;
        }
    }

    //    if(strcmp(option,"-n")==0){
    //        printf("%s\n",filename);
    //    }
    //    if(strcmp(option,"-u")==0){
    //        print_uid(filename);
    //    }
    //    if(strcmp(option,"-d")==0){
    //        print_size(filename);
    //    }
    //    if(strcmp(option,"-c")==0){
    //        print_links(filename);
    //    }
    //    if(strcmp(option,"-a")==0){
    //        print_rights(filename);
    //    }
}

int isCFile(char *fisier)
{
    if ((strcmp(strrchr(fisier, '.'), ".c")) == 0)
        return 1;
    else
        return 0;
}

void forkFunction(char *option, char *filename)
{
    pid_t pid;
    int i;
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        int status;
        if (pid == -1)
        {
            perror("eroare");
            exit(0);
        }
        if (pid == 0)
        {
            if (i == 0)
            {
                printf("child[1] --> pid = %d and ppid = %d\n", getpid(), getppid());
                // compile the file
                char *lst[] = {"/usr/bin/gcc", "-o", "executabil", filename, NULL};
                if (execv("/usr/bin/gcc", lst) < 0)
                {
                    printf("error occured\n");
                }
            }
            if (i == 1)
            {
                printf("child[2] --> pid = %d and ppid = %d\n", getpid(), getppid());
                // apel doar daca avem si altceva dupa -g
                if (option != NULL)
                {
                    action(option, filename);
                }
            }
            if (i == 2)
            {
                printf("child[3] --> pid = %d and ppid = %d\n", getpid(), getppid());
                create_links(filename);
            }
            // nu mai ajunge aici
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                printf("Procesul fiu cu PID %d s-a terminat cu codul %d.\n", getpid(),
                       exit_status);
            }
            exit(1);
        }
    }
    for (i = 0; i < 3; i++)
    {
        wait(NULL);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        perror("Not enough args");
        exit(-1);
    }

    DIR *dirname = opendir(argv[1]); // se deschide directorul

    if (dirname != NULL)
    {
        struct dirent *dir;
        // char path_first = dirname;
        char path_modified[30];
        while ((dir = readdir(dirname)) != NULL)
        {
            sprintf(path_modified, "%s/", argv[1]);
            strcat(path_modified, dir->d_name);

            if (isCFile(dir->d_name))
            {
                for (int i = 1; i < strlen(argv[2]); i++)
                {
                    if (argv[2][i] == 'g')
                    {
                        char aux[20] = "";
                        memmove(aux, argv[2] + i + 1, (strlen(argv[2]) - (i + 1)));
                        forkFunction(aux, dir->d_name);
                    }
    else
                    {
                        action(argv[2], path_modified);
                    }
                }
            }
        }
    }
    else
    {
        perror("Huston, the directory has a problem!");
        exit(-1);
    }
    closedir(dirname);
    return 0;
}
