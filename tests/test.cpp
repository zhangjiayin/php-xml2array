#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
using namespace std;

int main(int argc,char** argv)
{
    xmlDocPtr doc=NULL;
    xmlNodePtr cur=NULL;
    char* name=NULL;
    char* value=NULL;

    xmlKeepBlanksDefault (0);

    if(argc<2)
    {
        cout<<"argc must be 2 or above."<<endl;
        return -1;
    }

    doc=xmlParseFile(argv[1]);//创建Dom树
    if(doc==NULL)
    {
        cout<<"Loading xml file failed."<<endl;
        exit(1);
    }

    cur=xmlDocGetRootElement(doc);//获取根节点
    if(cur==NULL)
    {
        cout<<"empty file"<<endl;
        xmlFreeDoc(doc);
        exit(2);
    }

    //walk the tree
    cur=cur->xmlChildrenNode;//get sub node
    while(cur !=NULL)
    {
        name=(char*)(cur->name);
        value=(char*)xmlNodeGetContent(cur);
        cout<<"name is: "<<name<<", value is: "<<value<<endl;
        xmlFree(value);
        cur=cur->next;
    }

    xmlFreeDoc(doc);//释放xml解析库所用资源
    xmlCleanupParser();
    return 0;
}
