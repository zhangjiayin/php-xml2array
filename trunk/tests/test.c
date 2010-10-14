#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

static void print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node =
         cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n",
                   cur_node->name);
            if(cur_node->children && (cur_node->children->type == XML_CDATA_SECTION_NODE || cur_node->children->type == XML_TEXT_NODE )) {
                char *z = xmlNodeGetContent(cur_node);
                printf("content: %s\n", z);
            }
        }
        print_element_names(cur_node->children);
    }
}

int main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    xmlKeepBlanksDefault(0); 

    if (argc != 2)  return(1);

    LIBXML_TEST_VERSION    // Macro to check API for match with
        // the DLL we are using

        /*parse the file and get the DOM */
        if ((doc = xmlReadFile(argv[1], NULL, 0)) == NULL){
            printf("error: could not parse file %s\n", argv[1]);
            exit(-1);
        }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element);
    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    return 0;
}
