#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

#include "varlib.h"

#define MAXVARS 200

struct var{
    char *str;
    int global;
};

static struct var tab[MAXVARS];

static struct var *find_item(char *name) {
    int i;
    int len = strlen(name);
    char *s;

    for(i = 0; i < MAXVARS && tab[i].str != NULL; i++) {
        s = tab[i].str;
        if(strncmp(s, name, len) == 0)
            return &tab[i];
    }
    
    if(i < MAXVARS)
        return &tab[i];

    return NULL;
}

static char *new_string(char *name, char *val) {
    char *s;
    s = (char *)malloc(strlen(name) + strlen(val) + 2);
    
    if(s != NULL)
        sprintf(s, "%s=%s\n", name, val);

    return s;
}

int VLstore(char *name, char *val) {
    struct var *itemp;
    char *s;
    int rv = 1;

    if((itemp = find_item(name)) != NULL && (s = new_string(name, val)) != NULL) {
        if(itemp->str != NULL)
            free(itemp->str);
        itemp->str = s;

        rv = 0;
    }

    return rv;
}

char *VLookup(char *name) {
    struct var *itemp;

    if((itemp = find_item(name)) != NULL)
        return itemp->str;

    return (char *)"";
}

void VList() {
    int i;

    for(i = 0; i < MAXVARS && tab[i].str != NULL; i++) {
        if(tab[i].global)
            printf("* %s\n", tab[i].str);
        else
            printf(" %s\n", tab[i].str);
    }
}

int VLexport(char *name) {
    struct var *itemp;
    int rv = 1;

    if((itemp = find_item(name)) != NULL) {
        itemp->global = 1;
        rv = 0;
    }

    return rv;
}

int VLenviron2table(char *env[]) {
    int i;
    char *string;

    for(i = 0; i < MAXVARS && env[i] != NULL; i++) {
        if(i == MAXVARS)
            return 1;

        string = (char *)malloc(strlen(env[i]) + 1);
        string = env[i];
        strcpy(tab[i].str, string);
        tab[i].global = 1;
    }
    while(i < MAXVARS) {
        tab[i].str = NULL;
        tab[i].global = 0;
    }

    return 0;
}

char **VLtable2environ() {
    int i, j;
    int n = 0;

    extern char **env;

    for(i = 0; i < MAXVARS && tab[i].str != NULL; i++) {
        if(tab[i].global == 1)
            n++;
    }

    env = (char **)malloc((n + 1) * sizeof(char *));
    if(env == NULL)
        return NULL;
    
    for(i = 0, j = 0; i < MAXVARS && tab[i].str != NULL; i++)
        if(tab[i].global == 1)
            env[j++] = tab[i].str;
    env[j] = NULL;

    return env;

}






