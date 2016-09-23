#include <iostream>
#include <sstream>
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"



using namespace std;
using namespace rapidxml;

int main()
{
    xml_document<> doc;
    std::ifstream theFile ("WikiDumpPart1.xml");
    std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    xml_node<> *mediaWikiNode = doc.first_node();
    xml_node<> *pageNode = mediaWikiNode->first_node();
    string page = "page";
    string check = pageNode->name();
    while(page.compare(check) != 0)
    {
        pageNode = pageNode->next_sibling();
        check = pageNode->name();
    }

    if(page.compare(check) == 0)
        cout << "Found page node" << endl;

    //at this point we now have the page node, so now we need the title node
    string title = "title";
    xml_node<> *titleNode = pageNode->first_node();
    check = titleNode->name();
    while(title.compare(check) != 0)
    {
        titleNode = titleNode->next_sibling();
        check = titleNode->name();
    }

    if(title.compare(check) == 0)
    {
        cout << "Found title value" << endl;
        cout << titleNode->value() << endl;
    }

    //at this point we now have the title node, so we now need the id node
    string id = "id";
    xml_node<> *idNode = titleNode->next_sibling();
    check = idNode->name();
    while(id.compare(check) != 0)
    {
        idNode = idNode->next_sibling();
        check = idNode->name();
    }
    if(id.compare(check) == 0)
    {
        cout<<"ID Node found" << endl;
        cout<<"ID Value " << idNode->value() << endl;
    }

    //we have now gotten the ID Node, now need the revision node
    xml_node<> *revisionNode = idNode->next_sibling();
    string revision = "revision";
    check = revisionNode->name();
    while(revision.compare(check) != 0)
    {
        revisionNode = revisionNode->next_sibling();
        check = revisionNode->name();
    }

    if(revision.compare(check) == 0)
    {
        cout << "found revision node" << endl;
    }

    //now have the revision node, now we go inside to get the contributor node
    string contributor = "contributor";
    xml_node<> *contributorNode = revisionNode->first_node();
    check = contributorNode->name();
    while(contributor.compare(check) != 0)
    {
        contributorNode = contributorNode->next_sibling();
        check = contributorNode->name();
    }

    if(contributor.compare(check) == 0)
    {
        cout << "found contributor node" << endl;
    }

    //now have the contributor node, so we now need the username node
    string username = "username";
    xml_node<> *usernameNode = contributorNode->first_node();
    check = usernameNode->name();
    while(username.compare(check) != 0)
    {
        usernameNode = usernameNode->next_sibling();
        check = usernameNode->name();
    }

    if(username.compare(check) == 0)
    {
        cout << "Found username node" << endl;
        cout << "Username node value " << usernameNode->value() << endl;
    }

    //we now have username, we need to go back to contributor and get the text node
    string text = "text";
    xml_node<> *textNode = contributorNode->next_sibling();
    check = textNode->name();
    while(text.compare(check) != 0)
    {
        textNode = textNode->next_sibling();
        check = textNode->name();
    }
    if(text.compare(check) == 0)
    {
        cout << "Found text node" << endl;
        cout << "Text node value " << textNode->value() << endl;
    }

    //okay so we have now gotten the text node, so now we need to repeat the process, let's see if we can do it with just the
    //pageNode
    //determine the next sibling of page node
    pageNode = pageNode->next_sibling();
    check = pageNode->name();
    while(page.compare(check) != 0)
    {
        pageNode = pageNode->next_sibling();
        check = pageNode->name();
    }

    if(page.compare(check) == 0)
    {
        cout <<"Found page node" << endl;
    }

    titleNode = pageNode->first_node();
    check = titleNode->name();
    while(title.compare(check) != 0)
    {
        titleNode = titleNode->next_sibling();
        check = titleNode->name();
    }

    if(title.compare(check) == 0)
    {
        cout << "Found title node" << endl;
        cout << "title of page " << titleNode->value() << endl;
    }

    idNode = titleNode->next_sibling();
    check = idNode->name();
    while(id.compare(check) != 0)
    {
        idNode = idNode->next_sibling();
        check = idNode->name();
    }
    if(id.compare(check) == 0)
    {
        cout<<"ID Node found" << endl;
        cout<<"ID Value " << idNode->value() << endl;
    }

    revisionNode = idNode->next_sibling();
    check = revisionNode->name();
    while(revision.compare(check) != 0)
    {
        revisionNode = revisionNode->next_sibling();
        check = revisionNode->name();
    }

    if(revision.compare(check) == 0)
    {
        cout << "found revision node" << endl;
    }

    contributorNode = revisionNode->first_node();
    check = contributorNode->name();
    while(contributor.compare(check) != 0)
    {
        contributorNode = contributorNode->next_sibling();
        check = contributorNode->name();
    }

    if(contributor.compare(check) == 0)
    {
        cout << "found contributor node" << endl;
    }

    usernameNode = contributorNode->first_node();
    check = usernameNode->name();
    while(username.compare(check) != 0)
    {
        usernameNode = usernameNode->next_sibling();
        check = usernameNode->name();
    }

    if(username.compare(check) == 0)
    {
        cout << "Found username node" << endl;
        cout << "Username node value " << usernameNode->value() << endl;
    }


    textNode = contributorNode->next_sibling();
    check = textNode->name();
    while(text.compare(check) != 0)
    {
        textNode = textNode->next_sibling();
        check = textNode->name();
    }
    if(text.compare(check) == 0)
    {
        cout << "Found text node" << endl;
        cout << "Text node value " << textNode->value() << endl;
    }



    cout << "Hello World" << endl;
    return 0;
}

