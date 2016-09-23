#include "docparser.h"

DocParser::DocParser(): files(vector<string>()), docObjects(vector<Document>()), line(""), oneDot("."),
twoDot(".."), check(""), page("page"), title("title"), id("id"), revision("revision"), text("text"), idNum(0){
}

// directory function which retrieves the directory from which we want to get files from
int DocParser::getdir(string dir, vector<string> &files)
{
    // construct a director object
    DIR *dp;
    struct dirent *dirp;

    // if there is nothing in the directory then it was not opened
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << BOLDRED << "!!ERROR: Could not open '" << dir << "' - Supply a different path\n" << RESET << endl;
        return errno;
    }

    // if we can open directroy, go ahead and get all the names of the text files
    while ((dirp = readdir(dp)) != NULL)
    {
        files.push_back(string(dirp->d_name));
    }

    closedir(dp);
    return 0;
}

void DocParser::parseDocuments(string dirName)
{
    // get the name of the directory
    dir = string(dirName);

    // get the strings of the file names
    getdir(dir, files);
    
    // create a file path in order to access the files in the directory
    string filepath = " ";

    xml_document<> doc;

    // xml nodes so that way we are not redeclaring all the way through the program
    xml_node<> *mediaWikiNode = NULL;
    xml_node<> *pageNode = NULL;
    xml_node<> *titleNode = NULL;
    xml_node<> *idNode = NULL;
    xml_node<> *revisionNode = NULL;
    xml_node<> *textNode = NULL;

    // file object to parse the files
    ifstream theFile;

    // go through the files
    for (unsigned int i = 0; i < files.size(); i++)
    {
        // create a file path in order to access the filepath
        filepath = dir + "/" + files[i];

        // the first two file names are . and .. so the if statements get rid of that
        if(files[i].compare(oneDot) != 0 && files[i].compare(twoDot) != 0)
        {
            // parse the file and turn it into an xml doc
            theFile.open(filepath.c_str());
            vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            doc.parse<0>(&buffer[0]);


            // BIG NOTE: EVERY FILE STARTS WITH WIKIMEDIA
            // get the mediaWikiNode
            mediaWikiNode = doc.first_node();

            // find the page Node
            pageNode = mediaWikiNode->first_node();
            // check string is used to find the required nodes
            check = pageNode->name();
            while(page.compare(check) != 0)
            {
                pageNode = pageNode->next_sibling();
                check = pageNode->name();
            }

            // Okay, encountered an issue, if the node doesn't exist then it seg faults, so we need to account for that
            // else we will be in a shit ton of trouble
            while(pageNode != NULL)
            {
                //put in the titlenode
                titleNode = pageNode->first_node();
                check = titleNode->name();
                while(title.compare(check) != 0)
                {
                    titleNode = titleNode->next_sibling();
                    check = titleNode->name();
                }
                
                if(titleNode != NULL)
                {
                    //assign title value
                    title = titleNode->value();
                }
                
                // after the title comes the id node so we need to get the id node
                idNode = pageNode->first_node();
                check = idNode->name();
                while(id.compare(check) != 0)
                {
                    idNode = idNode->next_sibling();
                    check = idNode->name();
                }

                if(idNode != NULL)
                {
                    // assign id to the value so we can push it on
                    id = idNode->value();
                }

                // store in the pageNumber
                idNum = atoi(id.c_str());

                // after id, we have to find the revision node in order to determine where the
                // contributor's name is
                revisionNode = idNode->next_sibling();
                check = revisionNode->name();
                while(revision.compare(check) != 0)
                {
                    revisionNode = revisionNode->next_sibling();
                    check = revisionNode->name();
                }

                // now that we have the username, we need to get the text
                textNode = revisionNode->first_node();
                check = textNode->name();
                while(text.compare(check) != 0)
                {
                    textNode = textNode->next_sibling();
                    check = textNode->name();
                }

                if(textNode != NULL)
                {
                    // assign the text node value
                    text = textNode->value();
                }

                // push docObject onto the docObject stack
                docObjects.push_back(Document(text, idNum));
                //make a docObjectCopy
                docObjectsCopy.push_back(Document(text, idNum, title));

                // get the next page
                pageNode = pageNode->next_sibling();
                // reset id and text and title
                title = "title";
                id = "id";
                text = "text";
            }

            theFile.close();
            theFile.clear();
        }
    }
}

void DocParser::cleanDocObjects()
{
    // here we need to get the page numbers and print them
    for(int i = 0; i < int(docObjects.size()); i++)
    {
        docObjects[i].cleanStrings();
    }
}

vector<Document>& DocParser::getDocObjects()
{
    return docObjects;
}

void DocParser::printResults(vector<Page> &pages)
{
    for(int i = 0; i < int(pages.size()); i++)
    {
        Document result("", pages[i].getPageNum());
        vector<Document>::iterator finder = find(docObjectsCopy.begin(), docObjectsCopy.end(), result);
        if(finder != docObjectsCopy.end())
        {
                cout << "\t" << i+1 << ".) Document " << pages[i].getPageNum() << ", '" << finder->getTitle() << "'" <<  endl;
        }
    }
    cout << "\n***** Input the number of the document you wish to view or input '-1' to end search session *****" << endl;
}

void DocParser::printPage(int pageNumber)
{
    Document result("", pageNumber);
    vector<Document>::iterator finder = find(docObjectsCopy.begin(), docObjectsCopy.end(), result);
    if(finder != docObjectsCopy.end())
    {
        cout << "Document " << pageNumber << ", '" << finder->getTitle() << "'" << endl;
        cout << BOLDBLUE << "======================================================================================================================================================" << RESET << endl;
        cout << finder->returnText() << endl;
        cout << BOLDBLUE << "======================================================================================================================================================\n" << RESET << endl;
    }
    else
    {
        cout << BOLDRED << "!!ERROR: Requested page number is not in the query list of document results\n" << RESET << endl;
    }
}

// function empties out the vectors
void DocParser::emptyVectors()
{
    // variables that need to be set during parsing must be cleared afterwards each time
    files.clear();
    docObjects.clear();

   // dir = "";
    line = "";
    idNum = 0;
}

void DocParser::printSelectedPage(int pageNum, string dirName)
{
    bool foundPage = false; 
    
    // get the name of the directory
    dir = string(dirName);

    // get the strings of the file names
    getdir(dir, files);
    
    // create a file path in order to access the files in the directory
    string filepath = " ";

    xml_document<> doc;

    // xml nodes so that way we are not redeclaring all the way through the program
    xml_node<> *mediaWikiNode = NULL;
    xml_node<> *pageNode = NULL;
    xml_node<> *titleNode = NULL;
    xml_node<> *idNode = NULL;
    xml_node<> *revisionNode = NULL;
    xml_node<> *textNode = NULL;

    // file object to parse the files
    ifstream theFile;
    
    int fileCounter = 0;
    //filepath string
    filepath = dir + "/" + files[0];
    
    while(foundPage != true && fileCounter <= files.size())
    {
        // the first two file names are . and .. so the if statements get rid of that
        if(files[fileCounter].compare(oneDot) != 0 && files[fileCounter].compare(twoDot) != 0)
        {
            // parse the file and turn it into an xml doc
            theFile.open(filepath.c_str());
            vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            doc.parse<0>(&buffer[0]);
            
             // BIG NOTE: EVERY FILE STARTS WITH WIKIMEDIA
            // get the mediaWikiNode
            mediaWikiNode = doc.first_node();

            // find the page Node
            pageNode = mediaWikiNode->first_node();
            // check string is used to find the required nodes
            check = pageNode->name();
            while(page.compare(check) != 0)
            {
                pageNode = pageNode->next_sibling();
                check = pageNode->name();
            }
            
             // Okay, encountered an issue, if the node doesn't exist then it seg faults, so we need to account for that
            // else we will be in a shit ton of trouble
            while(pageNode != NULL)
            {
                //put in the titlenode
                titleNode = pageNode->first_node();
                check = titleNode->name();
                while(title.compare(check) != 0)
                {
                    titleNode = titleNode->next_sibling();
                    check = titleNode->name();
                }
                
                if(titleNode != NULL)
                {
                    //assign title value
                    title = titleNode->value();
                }
                
                // after the title comes the id node so we need to get the id node
                idNode = pageNode->first_node();
                check = idNode->name();
                while(id.compare(check) != 0)
                {
                    idNode = idNode->next_sibling();
                    check = idNode->name();
                }

                if(idNode != NULL)
                {
                    // assign id to the value so we can push it on
                    id = idNode->value();
                }

                // store in the pageNumber
                idNum = atoi(id.c_str());
                
                //if we find the page number
                if(idNum == pageNum)
                {
                    //set the boolean equal to true
                    foundPage = true;
                    
                    // contributor's name is
                    revisionNode = idNode->next_sibling();
                    check = revisionNode->name();
                    while(revision.compare(check) != 0)
                    {
                        revisionNode = revisionNode->next_sibling();
                        check = revisionNode->name();
                    }

                    // now that we have the username, we need to get the text
                    textNode = revisionNode->first_node();
                    check = textNode->name();
                    while(text.compare(check) != 0)
                    {
                        textNode = textNode->next_sibling();
                        check = textNode->name();
                    }

                    if(textNode != NULL)
                    {
                        // assign the text node value
                        text = textNode->value();
                    }
                    
                    cout << "Document " << pageNum << ", '" << title << "'" << endl;
                    cout << BOLDBLUE << "======================================================================================================================================================" << RESET << endl;
                    cout << text << endl;
                    cout << BOLDBLUE << "======================================================================================================================================================" << RESET << endl;
                
                    // get the next page
                    pageNode = pageNode->next_sibling();
                    // reset id and text and title
                    title = "title";
                    id = "id";
                    text = "text";
                }
            }
            
            theFile.close();
            theFile.clear();
            
            //increase the file counter
            fileCounter++;
            filepath = dir + "/" + files[fileCounter];
            
        }

    }
    
    if(foundPage == false)
    {
        cout << BOLDRED << "!!ERROR: Requested page number is not in the query list of document results\n" << RESET << endl;
    }
    
    
}
