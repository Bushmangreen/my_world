#include "headers.h"
int interval_atoi(char* buff, int beg, int end);

int main(int ac, char** av)
{

    int ret, n;
    char c;

    GlobalNode* nodes = createNewSession();
    int* commands;


    if( nodes == NULL)
    {
        NO_RESOURCE;
        printf("errors\n");
        return 1;
    }

    if (ac > 1)
        readBackup(nodes, av[1]); // read from backup file: backup.txt

    do
    {
        
        commands = getCommand(nodes, &ret);
        //printCommand(commands, ret);
        ret = parseCommand(nodes, commands, ret);
        free(commands);
        //printNodes(nodes);
    } while (ret != QUIT);

    if (ac > 1)
        createBackup(nodes, av[1]); // update the backupfile with new entries: backup.txt
    else 
        createBackup(nodes, "newBackup.txt"); // if not backfile given we create new backup file:newBackup.txt

    freeThemAll(nodes, ALL_MODE);
    return 0;
}