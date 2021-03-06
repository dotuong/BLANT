#include <stdio.h>
#include "misc.h"
#include "smallgraph.h"

int main(int argc, char *argv[])
{
    int BFSsize;
    SMALL_GRAPH *G = SmallGraphReadAdjMatrix(stdin);
    SMALL_GRAPH *Gbar = SmallGraphComplement(NULL, G);
    SMALL_GRAPH *GG = SmallGraphComplement(NULL, Gbar);
    GG->n = 64;
    puts("Complement of the complement:");
    SmallGraphPrintAdjMatrix(stdout, GG);

    while(1)
    {
	int root, distance, nodeArray[MAX_SSET], distArray[MAX_SSET], i;
	printf("enter BSF start node, distance: "); fflush(stdout);
	if(scanf("%d%d", &root, &distance) != 2)
	    break;
	BFSsize = SmallGraphBFS(G, root, distance, nodeArray, distArray);
	for(i=0; i<BFSsize; i++)
	    printf("%d(%d) ", nodeArray[i], distArray[nodeArray[i]]);
	printf("\n");
    }

    return 0;
}
