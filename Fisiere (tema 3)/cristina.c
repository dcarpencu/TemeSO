#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void indeitifcatorUtilizator(char * FileName);
void dimensiuneOcteti(char *FileName);
void drepturiAcces(char *FileName);
void legaturiFisier(char *FileName);

void performAction(char *option,char *FileName){
    if(strcmp(option,"-n") == 0){
        printf("%s\n", FileName);
    }
    if(strcmp(option,"-u") == 0){
        indeitifcatorUtilizator(FileName);
    }
    if(strcmp(option,"-d") == 0){
        dimensiuneOcteti(FileName);
    }
    if(strcmp(option,"-c") == 0){
        legaturiFisier(FileName);
    }
    if(strcmp(option,"-a") == 0){
        drepturiAcces(FileName);
    }
}

void dimensiuneOcteti(char *FileName){
    struct stat struct_stat;
    int stat_result = stat(FileName, &struct_stat);

    if(!stat_result) {
        perror("Eroare la printarea dimensiunii in octeti");
        exit(-1);
    }

    off_t dimensiune = struct_stat.st_size;
    printf("%lld\n", dimensiune);
}

void indeitifcatorUtilizator(char *FileName){
    struct stat struct_stat;
    int stat_result = stat(FileName, &struct_stat);

    if(!stat_result) {
        perror("Eroare la indetificarea identificatorului utilizatorului.");
        exit(-1);
    }

// uid_t id = struct_stat.st_uid;
    printf("%lu\n",(unsigned long int )struct_stat.st_uid);
}


void legaturiFisier(char *FileName){
    struct stat struct_stat;
    int stat_result = stat(FileName,&struct_stat);

    if(!stat_result) {
        perror("Eroare la identificarea legaturilor din fisier.");
        exit(-1);
    }

// nlink_t legaturi = struct_stat.st_nlink;
    printf("%hu\n", struct_stat.st_nlink);
}

void drepturiAcces(char *FileName){
    struct stat struct_stat;
    int stat_result = stat(FileName, &struct_stat);

    if(!stat_result) {
        perror("Eroare la afisarea permisiunilor.");
        exit(-1);
    }

    printf("%s\n","Utilizator:");
    if(S_IRUSR & struct_stat.st_mode)
        printf("%s\n","Read: DA");
    else
        printf("%s\n","Read: Nu");

    if(S_IWUSR & struct_stat.st_mode)
        printf("%s\n","Write: DA");
    else
        printf("%s\n","Write: NU");

    if(S_IXUSR & struct_stat.st_mode)
        printf("%s\n","Execute: DA");
    else
        printf("%s\n","Execute: NU");


    printf("%s\n","Grup:");

    if(S_IRGRP & struct_stat.st_mode)
        printf("%s\n","Read: DA");
    else
        printf("%s\n","Read: NU");

    if(S_IWGRP & struct_stat.st_mode)
        printf("%s\n","Write: DA");
    else
        printf("%s\n","Write: NU");

    if(S_IXGRP & struct_stat.st_mode)
        printf("%s\n","Execute: DA");
    else
        printf("%s\n","Execute: NU");


    printf("%s\n","Other:");

    if(S_IROTH & struct_stat.st_mode)
        printf("%s\n","Read: DA");
    else
        printf("%s\n","Read: NU");

    if(S_IWOTH & struct_stat.st_mode)
        printf("%s\n","Write: DA");
    else
        printf("%s\n","Write: NU");

    if(S_IXOTH & struct_stat.st_mode)
        printf("%s\n","Execute: DA");
    else
        printf("%s\n","Execute: NU");
//printf("\n");
}


// void create_links(char *FileName){
// struct stat struct_stat;
// int stat_result = stat(FileName,&struct_stat);
// if(stat_result){
// ///to do file links
// }else{
// perror("Error at printing the number of links");
// }
// }

int checkIfC(char *FileName){
    //printf("checkC");
    if(strcmp(".c", strchr(FileName,'.')) == 0)
        return 1;
    else
        return 0;
}

int main(int argc,char **argv){

    if(argc != 3){
        perror("Not enough arguments!\n");
        exit(-1);
    }
    DIR *director=opendir(argv[1]);

    if(director == NULL){
        perror("Error at director!");
        exit(-1);
    }

    struct dirent *read;
    while((read = readdir(director)) != NULL){
        char fileName[256];
        strcpy(fileName, read->d_name);
        //printf("%s", fileName);
int ifC = checkIfC(fileName);

//char *fileName = read->d_name;

if (ifC == 1){
//printf("ceva");
performAction(argv[2], fileName);
}
    }

closedir(director);
    return 0;
}

