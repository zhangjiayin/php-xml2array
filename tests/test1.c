#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

xmlNodePtr currentNode;
xmlDocPtr doc;
xmlNodePtr parseDoc(char *docname) {

    //xmlDocPtr doc;

    xmlNodePtr cur;
    
    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(docname);
    
    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }
    
    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return;
    }
    
    return cur;
}

void printChildrenNames(xmlNodePtr cur) {
    if (cur != NULL) {
        cur = cur->xmlChildrenNode;
        
        while (cur != NULL){
            if(cur->type == XML_ELEMENT_NODE){
                printf("Current Node: %s\n", cur->name);
            }
            printChildrenNames(cur);
            cur = cur->next;
        }
        
        return;
    }else{
        fprintf(stderr, "ERROR: Null Node!");
        return;
    }
}

int main(int argc, char **argv) {

    char *docname;
        
    if (argc <= 1) {
        printf("Usage: %s docname\n", argv[0]);
        return(0);
    }

    docname = argv[1];
    currentNode = parseDoc (docname);
    //printf("Root Node: %s\n", currentNode->name);

    printChildrenNames(currentNode);
    return (1);
}
