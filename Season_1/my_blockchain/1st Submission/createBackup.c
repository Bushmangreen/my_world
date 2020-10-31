
#include "headers.h"

void my_putchar(char letter,int fd)
{
    write(fd,&letter,1);
}

void my_putnbr(int number, int fd)
{
    if(number < 0)
    {
        my_putchar('-', fd);
        number = - number;
    }

    if(number/10)
        my_putnbr(number/10, fd);
    my_putchar(number % 10 + '0', fd);

}

void my_putstr(char* str, int fd)
{
    if (str != NULL)
    {
        while(*str)
        {
            write(fd, str, 1);
            str++;
        }
    }
}

int my_atoi(char* str) 
{ 
    // Initialize result 
    int res = 0; 
  
    // Iterate through all characters 
    // of input string and update result 
    for (int i = 0; str[i] != '\0'; ++i) 
        res = res * 10 + str[i] - '0'; 
  
    // return result. 
    return res; 
} 

void createBackup(GlobalNode *nodes, char* backupName)
{
    int fd = open(backupName,O_WRONLY|O_CREAT|O_TRUNC, 0644);

    if (fd < 0)
        printf("Error, could not create new backup\n");

    Node* node = nodes->headNode;
    if (node == NULL)
    {
        return;
    }
    Block* block = node->block;
    
   // my_putnbr(nodes->nbrNodes, fd);
   // my_putchar('\n', fd);
    while(node)
    {   
        my_putnbr(node->nid, fd);
        block = node->block;
        while(block)
        {
            my_putchar(' ', fd);
            my_putstr(block->bid, fd);
            block = block->prevBlock;
        }
        my_putchar('\n', fd);
        node = node->nextNode;
    }

    close(fd);
}

void readBackup(GlobalNode* nodes, char* backupName)
{
    int fd = open(backupName, O_RDONLY);
    char* token;
    char* line;
    int nid;
    
    if (fd == -1)
    {
        printf("Backup does not exists\n");
        return;
    }
    
    while ((line = my_readline(fd)))
    {
        int nid = 0;
        int bid = 0;
   
        // get the NID 
        token = strtok(line, " ");
        nid = my_atoi(token);
        createNode(nodes, nid); // create node from backup
        // get the 1st block
        token = strtok(NULL, " ");
        // walk through blocks 
        while( token != NULL ) 
        {
            bid = my_atoi(token);
            createBlock(nodes, nid, bid); // add block to the node created above
            token = strtok(NULL, " ");
        }
    
        free(line);
    }
    
    close(fd);
}
