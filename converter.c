#include "libxml/parser.h"
#include <stdio.h>



int main(int argc, char **argv)
{
    if (argc != 3)
	{
        fprintf(stderr, "Usage: %s infile.xml outfile.bin\n", argv[0]);
        return 1;
    }

	xmlDoc * inputFile = xmlReadFile(argv[1], NULL, 0);
	if (! inputFile)
	{
		fprintf(stderr, "Cannot load input file %s\n", argv[1]);
		return 1;
	}

	FILE * outFile = fopen(argv[2], "wb");
	if (! outFile)
	{
		fprintf(stderr, "Cannot open output file %s\n", argv[2]);
		xmlFreeDoc(inputFile);
		return 1;
	}


	xmlNode * root = xmlDocGetRootElement(inputFile);
	if (root)	// input is not empty
	{
		for (xmlNode * node = root->children; node; node = node->next)
		{
			if (node->type != XML_ELEMENT_NODE) continue;

			printf("node name=%s type=%d content=%s\n", node->name, node->type, node->content);
			xmlNode *child = node->children;
			if (child)
			{
				printf("child name=%s type=%d content=%s\n", child->name, child->type, child->content);

				// TODO found! needs to save

			}
		}
	}

	fclose(outFile);
	xmlFreeDoc(inputFile);
	return 0;
}
