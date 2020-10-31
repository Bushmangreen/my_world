#include "headers.h"

int rmBlock(GlobalNode* nodes, char* bid)
{
    Node* node = nodes->headNode;
    if(node == NULL)
    {
        NODE_NO_EXIST;
        return 1;
    }
    bool atLeastOnce = false;
    int ret;

    while(node != NULL)
    {
        ret = deleteBlock(nodes, node, bid);
        if(ret == 0) atLeastOnce = true;
        node = node->nextNode;
    }
    //depricated
    //nodes->headBlock=NULL;

    if(atLeastOnce) return 0;
    return 1;
}

int deleteBlock(GlobalNode* nodes, Node* node, char* bid)
{
    if( !bidExists(node, bid) )
    {
        BLOCK_NO_EXIST;
        return -1;
    }
    char* bidNow;
    //next->prev is curr
    Block* next=NULL;
    Block* curr=node->block;
    while(curr!=NULL)
    {
        bidNow = curr->bid;
        if(strcmp(bidNow, bid) == 0)
        {
            if(next == NULL)
            {//very first block is what we are looking for
                node->block = curr->prevBlock;
            }else
            {
                next->prevBlock=curr->prevBlock;
            }
            free(curr);
            
            nodes->bNbrById[node->id - nodes->idErr] = --node->blockNbr;
            //get time in seconds
            node->timestamp = time(NULL);
            if(node->blockNbr > 0) nodes->timeById[node->id - nodes->idErr] = node->timestamp;
            else nodes->timeById[node->id - nodes->idErr] = 0;

            break;
        }

        next=curr;
        curr=curr->prevBlock;
    }
    return 0;
}