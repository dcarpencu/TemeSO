#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int isDir (const char* fileN) {
struct stat path;

stat(fileN, &path);

return S_ISDIR(path.st_mode);
}

int isCFile (const char* fileN) {
    FILE *file;
    char* ext = strrchr(fileN, '.');
    if ((strcmp(ext, ".c")) == 0)
        return 1;
    else
        return 0;
}

int isNUA (const char* cases) {
    int valid = 0;
    int contor = -1;
    char copie = cases[0];
    while (copie) {
        valid = 0;
        contor++;

        if (copie == 'n' || copie == 'a' || copie == 'u' || copie == 'c' || copie == 'd' || copie == '-') {
            valid = 1;
        }

        if (valid == 0) {
            return 0;
        }
        copie = cases[contor+1];
    }

    if (contor == 0)
        return 0;
    return 1;
}

void showPermissions (struct stat status) {
    showUserPermissions(status);
    showGroupPermissions(status);
    showOthersPermissions(status);
}

void showUserPermissions (struct stat status) {
    printf("USER:\n");
    printf("READ - ");
    if (status.st_mode & S_IRUSR)
        printf("DA\n");
    else
        printf("NU\n");

    printf("WRITE - ");
    if (status.st_mode & S_IWUSR)
        printf("DA\n");
    else
        printf("NU\n");

    printf("EXE - ");
    if (status.st_mode & S_IXUSR)
        printf("DA\n");
    else
        printf("NU\n");
}

void showGroupPermissions (struct stat status) {
    printf("GROUP:\n");
    printf("READ - ");
    if (status.st_mode & S_IRGRP)
        printf("DA\n");
    else
        printf("NU\n");

    printf("WRITE - ");
    if (status.st_mode & S_IWGRP)
        printf("DA\n");
    else
        printf("NU\n");

    printf("EXE - ");
    if (status.st_mode & S_IXGRP)
        printf("DA\n");
    else
        printf("NU\n");
}

void showOthersPermissions (struct stat status) {
    printf("OTHERS:\n");
    printf("READ - ");
    if (status.st_mode & S_IROTH)
        printf("DA\n");
    else
        printf("NU\n");

    printf("WRITE - ");
    if (status.st_mode & S_IWOTH)
        printf("DA\n");
    else
        printf("NU\n");


    printf("EXE - ");
    if (status.st_mode & S_IXOTH)
        printf("DA\n");
    else
        printf("NU\n");
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments\n");
        return 0;
    }

    if (isDir(argv[1]) == 0) {
        printf("The argument is not a director\n");
        return 0;
    }

    if (argv[2][0] != '-' || !isNUA(argv[2])) {
        printf("The argument is not valid!\n");
        return 0;
    }

    DIR* directory = opendir(argv[1]);
    struct dirent *dir;

    if (directory == NULL) {
        printf("ERROR! when trying to open the directory");
        return 0;
    }

    int i;
    char dir2[99] = "test_dir4/";

    while ((dir = readdir(directory)) != NULL) {
        if (isCFile(dir->d_name)) {
            struct stat status;
            char path[99];
            for(i=0 ; i path[i] = argv[1][i];
        }
        strcat(path, "/");
        strcat(path, dir->d_name);
        printf("%s\n", path);
        stat(dir->d_name, &status);

        char pathCopy[99];
        strcpy(pathCopy, dir->d_name);

        path[strlen(argv[1])+1] = '\0';

        for (i=1 ; i if (argv[2][i] == 'n') {
            printf("%s\n", dir->d_name);
        }
        if (argv[2][i] == 'u') {
            printf("%d\n", status.st_uid);
        }
        if (argv[2][i] == 'a') {
            showPermissions(status);
        }
        if (argv[2][i] == 'd') {
            printf("Dimensiunea in octeti - %d\n", status.st_size);
        }
        if (argv[2][i] == 'c') {
            printf("Numar de legaturi - %d\n", status.st_nlink);
        }
    }
    if (status.st_size < 1024 * 100) {
        strcat(dir2, dir->d_name);
        char symlinkP[99] = "../";
        strcat(symlinkP, pathCopy);
        printf("%s\n", symlinkP);
        symlink(symlinkP, dir2);
        dir2[3] = '\0';
    }
}
}
}