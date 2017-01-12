/*
 ============================================================================
 Name        : BibleReader.c
 Author      : MOULIN
 Version     :
 Copyright   : Your copyright notice
 Description : Bible Reader. User choice passage, get passage in API website, extractFile() to get only text pattern <text>passage...</text> and parse_output() to have only text "passage" without <text>
 TODO		 : Accent to bible french, check version and book input by user, choice version in new file : conf.xml
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>

#define VERSION	"kjv" //See bible-versions.xml to choice an other version. Exemple "darby" to french version


#if defined(LIBXML_READER_ENABLED) && defined(LIBXML_PATTERN_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)


/**
 * extractFile:
 * @filename: the file name to parse
 *
 * Parse and print information about an XML file.
 *
 * Returns the resulting doc with just the elements preserved.
 */
static xmlDocPtr
extractFile(const char *filename, const xmlChar *pattern) {
    xmlDocPtr doc;
    xmlTextReaderPtr reader;
    int ret;

    /*
     * build an xmlReader for that file
     */
    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        /*
	 * add the pattern to preserve
	 */
        if (xmlTextReaderPreservePattern(reader, pattern, NULL) < 0) {
            fprintf(stderr, "%s : failed add preserve pattern %s\n",
	            filename, (const char *) pattern);
	}
	/*
	 * Parse and traverse the tree, collecting the nodes in the process
	 */
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            ret = xmlTextReaderRead(reader);
        }
        if (ret != 0) {
            fprintf(stderr, "%s : failed to parse\n", filename);
	    xmlFreeTextReader(reader);
	    return(NULL);
        }
	/*
	 * get the resulting nodes
	 */
	doc = xmlTextReaderCurrentDoc(reader);
	/*
	 * Free up the reader
	 */
        xmlFreeTextReader(reader);
    } else {
        fprintf(stderr, "Unable to open %s\n", filename);
	return(NULL);
    }
    return(doc); //To parse_output
}

/**
 * parse_output:
 * doc: xml data with only text pattern
 *
 * Parse and print information about an XML file.
 *
 * Print in console passages.
 */
int parse_output(xmlDocPtr doc) {


    xmlNode        *root, *first_child, *node;


    root = xmlDocGetRootElement(doc);
        first_child = root->children;
        for (node = first_child; node; node = node->next) {
        		fprintf(stdout,"\t%s\n",  xmlNodeGetContent(node));
        }

     return 0;
}

/**
 * main:
 * @filename: the file name to parse
 *
 * Parse and print information about an XML file.
 *
 * Returns the resulting doc with just the elements preserved.
 */
int main(int argc,char *argv[]) {

	//default declaration
	char book[10] = "Gen";
	int chapter = 1;
	int verseStart = 1;
	int verseStop = 1;
	char c_response = 'y';

	char filename[80] = "http://api.preachingcentral.com/bible.php?passage=Jn3:16-16";
	const char *pattern = "text";
	xmlDocPtr doc;

//User interface
	printf("//----------Bible Reader-----------------//");

	for(;;) {
		printf("\nBook : ");
		scanf("%s",book);
		printf("Chapter : ");
		scanf("%d",&chapter);
		printf("Verse Start : ");
		scanf("%d",&verseStart);
		printf("Verse Stop : ");
		scanf("%d",&verseStop);


		printf(" %s %d:%d-%d \n",book,chapter,verseStart,verseStop);
		sprintf(filename,(char*) "http://api.preachingcentral.com/bible.php?passage=%s%d:%d-%d&version=%s",book,chapter,verseStart,verseStop,VERSION); //Creation query



	 /*
	     * this initialize the library and check potential ABI mismatches
	     * between the version it was compiled for and the actual shared
	     * library used.
	     */
	    LIBXML_TEST_VERSION

	    doc = extractFile(filename, (const xmlChar *) pattern); //Get xml file after query in website
	    if (doc != NULL) {
	        /*
		 * ouptut the result.
		 */
		parse_output(doc);	//Print only passages

		//Stop or re-aswser an other passage ?
		printf("\nDo you want read an other verse ? y/n : ");
		scanf(" %c", &c_response);
		if(c_response != 'y') {
			break;
		}
		/*
		 * don't forget to free up the doc
		 */
		xmlFreeDoc(doc);
	    }


	    /*
	     * Cleanup function for the XML library.
	     */
	    xmlCleanupParser();
	    /*
	     * this is to debug memory for regression tests
	     */
	    xmlMemoryDump();
	}
	return 0;
}

#else
int main(void) {
    fprintf(stderr, "Reader, Pattern or output support not compiled in\n");
    exit(1);
}
#endif
