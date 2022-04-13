#include "libxml/parser.h"
#include "tlvStruct.h"
#include <stdio.h>
#include <stdlib.h>



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

			//printf("node name=%s type=%d content=%s\n", node->name, node->type, node->content);

			const xmlNode *child = node->children;
			if (child && child->content)
			{
				//printf("child name=%s type=%d content=%s\n", child->name, child->type, child->content);

				// found! needs to save
				const xmlChar *name = node->name;
				const xmlChar *value = child->content;

				if (xmlStrcmp(name, "text") == 0)
				{
					// found text record
					size_t textLen = xmlStrlen(value);
					struct T_TlvStructHdr hdr = {
						.type = TypeText,
						.length = sizeof(hdr) + textLen,
					};
					fwrite(&hdr, sizeof(hdr), 1, outFile);
					fwrite(value, textLen, 1, outFile);
				}
				else if (xmlStrcmp(name, "numeric") == 0)
				{
					// found numeric record
					int32_t number = atoi(value);
					struct T_TlvStructHdr hdr = {
						.type = TypeNumeric,
						.length = sizeof(hdr) + sizeof(number),
					};
					fwrite(&hdr, sizeof(hdr), 1, outFile);
					fwrite(&number, sizeof(number), 1, outFile);
				}
				else
				{
					fprintf(stderr, "Record <%s> unknown\n", name);
				}
			}
		}
	}

	fclose(outFile);
	xmlFreeDoc(inputFile);
	return 0;
}
