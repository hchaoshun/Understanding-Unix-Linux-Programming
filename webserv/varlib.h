static struct var *find_item(char *name);
static char *new_string(char *name, char *val);

int VLstore(char *name, char *val);
char *VLookup(char *name);
void VList();

int VLexport(char *name); /* 1 for no, 0 for ok */
int VLenviron2table(char *env[]);  /* 1 for no, 0 for ok */
char **VLtable2environ();
