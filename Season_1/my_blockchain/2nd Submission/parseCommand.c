#include "headers.h"

int parseCommand(GlobalNode* nodes, Command* commands, int len)
{
    //extern const fnx FNX;
    //fnx* fnx;
    int ret = INT_MAX;
    int firstCommand = commands[0].i;
    int secondCommand = commands[1].i;

    //printf("commands: ");
    //for(int i=0; i<len; i++) printf("%d ", commands[i]);

    if(len == 1 && firstCommand != LS)
    {
        if ( firstCommand == SYNC )
        {
            ret = syncNodes(nodes);
            if(ret == 0)  printf("ok\n");
        }else if (firstCommand == QUIT)
        {
            return QUIT;
        }
    }else if(firstCommand==ADD)
    {
        //fnx = FNX[0][0];
        //add node nid
        if(secondCommand == NODE)
        {
            if(len < 3)
            {
                COMMAND_NOT_FOUND("node");
            };
            for(int i=2; i<len; i++)
            {
                ret = createNode(nodes, commands[i].i);
                if(ret == 0)  printf("ok\n");
            }
        }
        else if(secondCommand == BLOCK)
        {
            //add block bid nid*
            if(len < 4)
            {
                COMMAND_NOT_FOUND("node");
            }
            for(int i=3; i<len; i++)
            {
                ret = createBlock(nodes, commands[i].i, commands[2].c);
                if(ret == 0)  printf("ok\n");
            }
            //inside createBlock, setSyncd runs only if * is given as arguments
                //therefore need to make sure if instead of *, user provides
                //all nodes manually
            if(len > 4) setSyncd(nodes);
        }
    }else if(firstCommand==RM)
    {   //rm node nid*
        if(len < 3)
        {
            COMMAND_NOT_FOUND("node or block");
        }
        for(int i=2; i<len; i++)
        {
            if(secondCommand==NODE)
            {
                ret = rmNode(nodes, commands[i].i);
                if(ret == 0)  printf("ok\n");
            }
            else if(secondCommand==BLOCK)
            {
                //rm block bid
                ret = rmBlock(nodes, commands[i].c);
                if(ret == 0)  printf("ok\n");
            }
        }
    }else if (firstCommand == LS)
    {
        Command* flag = NULL;
        if(len > 1 && secondCommand == L_NBR) flag = commands+1;
        ret = listNodes(nodes, flag);
        if(ret == 0)  printf("ok\n");
    }else
    {
        COMMAND_NOT_FOUND("command");
    }
    return 0;
}