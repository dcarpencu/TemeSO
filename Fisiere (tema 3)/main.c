#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void print_size(char* filename) {
    struct stat struct_stat;
    int stat_result = stat(filename, &struct_stat);
    if (stat_result) {
        off_t size = struct_stat.st_size;
        printf("%lld", size);
    } else {
        perror("stat function nu merge :(");
    }
}

void print_uid(char *filename){
    struct stat struct_stat;
    int stat_result = stat (filename,&struct_stat);
    if(stat_result){
        uid_t id = struct_stat.st_uid;
        printf("%lu\n",(unsigned long int) id);
    }else{
        perror("Error at uid printing!");
    }
}

void print_links(char *filename){
    struct stat struct_stat;
    int stat_result = stat(filename,&struct_stat);
    if(stat_result){
        nlink_t links =struct_stat.st_nlink;
        printf("%hu\n", links);
    }else{
        perror("Error at printing the number of links");
    }
}

void print_rights(char *filename){
    struct stat struct_stat;
    int stat_result =stat(filename,&struct_stat);
    if(stat_result){
        printf("%s\n","Utilizator:");
        if(S_IRUSR & struct_stat.st_mode){
            printf("%s\n","Read - Da");
        }else{
            printf("%s\n","Read - Nu");
        }
        if(S_IWUSR & struct_stat.st_mode){
            printf("%s\n","Write - Da");
        }else{
            printf("%s\n","Write - Nu");
        }
        if(S_IXUSR & struct_stat.st_mode){
            printf("%s\n","Execute - Da");
        }else{
            printf("%s\n","Execute - Nu");
        }
        printf("%s\n","Grup:");
        if(S_IRGRP & struct_stat.st_mode){
            printf("%s\n","Read - Da");
        }else{
            printf("%s\n","Read - Nu");
        }
        if(S_IWGRP & struct_stat.st_mode){
            printf("%s\n","Write - Da");
        }else{
            printf("%s\n","Write - Nu");
        }
        if(S_IXGRP & struct_stat.st_mode){
            printf("%s\n","Execute - Da");
        }else{
            printf("%s\n","Execute - Nu");
        }
        printf("%s\n","Other:");
        if(S_IROTH & struct_stat.st_mode){
            printf("%s\n","Read - Da");
        }else{
            printf("%s\n","Read - Nu");
        }
        if(S_IWOTH & struct_stat.st_mode){
            printf("%s\n","Write - Da");
        }else{
            printf("%s\n","Write - Nu");
        }
        if(S_IXOTH & struct_stat.st_mode){
            printf("%s\n","Execute - Da");
        }else{
            printf("%s\n","Execute - Nu");
        }
        printf("\n");
    }else{
        perror("Error at printing file permissions!");
    }
}

void action(char* option, char* filename) {
    switch(option[1]) {
        case 'n':
            printf("%s\n",filename);
            break;
        case 'u':
            print_uid(filename);
            break;
        case 'd':
            print_size(filename);
            break;
        case 'c':
            print_links(filename);
            break;
        case 'a':
            print_rights(filename);
            break;
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

int isCFile (char* fisier) {
    if ((strcmp(strrchr(fisier, '.'), ".c")) == 0)
        return 1;
    else
        return 0;
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        perror("Not enough args");
        exit(-1);
    }

    DIR* dirname = opendir(argv[1]); // se deschide directorul

    if (dirname != NULL) {
        struct dirent *dir;
        char* path_first = dirname;
        char* path_modified;
        while ((dir = readdir(dirname)) != NULL) {
            strcpy(path_modified, path_first);
            strcat()
            if (isCFile(dir->d_name)) {
                printf("%s ", dir->d_name);
                action(argv[2], dir->d_name);
            }
        }
    } else {
        perror("Huston, the directory has a problem!");
        exit(-1);
    }
    closedir(dirname);
    return 0;
}