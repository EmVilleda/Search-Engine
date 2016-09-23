#include "datacrunch.h"

DataCrunch::DataCrunch()
{
    dParser = new DocParser();
    iHandler = new IndexHandler();
    qHandler = new QueryHandler();
}

DataCrunch::~DataCrunch()
{
    delete dParser;
    delete iHandler;
    delete qHandler;
}

// =============== Maintenance Mode Functions ===============
// adding documents to the index (can already be existing or create new)
void DataCrunch::addToIndex()
{
    cout << "****** Would you like to add to an already existing index file or create a new index? *****" << endl;
    cout << BOLDBLACK << "\t'old'" << RESET " - Add to existing index file" << endl;
    cout << BOLDBLACK << "\t'new'" << RESET " - Add to new index file" << endl;

    string addTo = "";
    while(addTo != "old" && addTo != "new")
    {
        cout << ":: ";
        getline(cin, addTo);
        cout << endl;

        if(addTo == "old")
        {
            iHandler->deleteIndex();
            supplyDocuments();
            if(dParser->getDocObjects().empty() == false)
            {
                loadDocToIndex();
                std::chrono::time_point<std::chrono::system_clock> start, end;
                start = std::chrono::system_clock::now();
                iHandler->writeToIndex();
                end = std::chrono::system_clock::now();
                unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

                cout << BOLDGREEN << "Wrote to Index (" << seconds << " seconds)\n" << RESET << endl;
                // after each add we delete data structure
                iHandler->deleteIndex();
            }
            // after each search we empty dParser data
            dParser->emptyVectors();
        }
        else if(addTo == "new")
        {
            iHandler->deleteFileAndIndex();
            supplyDocuments();
            if(dParser->getDocObjects().empty() == false)
            {
                loadDocToIndex();
                std::chrono::time_point<std::chrono::system_clock> start, end;
                start = std::chrono::system_clock::now();
                iHandler->writeToIndex();
                end = std::chrono::system_clock::now();
                unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

                cout << BOLDGREEN << "Wrote to Index  (" << seconds << " seconds)\n" << RESET <<endl;
                // after each add we delete data structure
                iHandler->deleteIndex();
            }
            // after each search we empty dParser data
            dParser->emptyVectors();
        }
        else
        {
            cout << BOLDRED << "!!ERROR: Incorrect command input\n" << RESET << endl;
            cout << "***** Input one of the following commands *****" << endl;
            cout << BOLDBLACK << "\t'old'" << RESET " - Add to existing index file" << endl;
            cout << BOLDBLACK << "\t'new'" << RESET " - Add to new index file" << endl;
        }
    }
}

// clearing index file and, if it exists, index data structure
void DataCrunch::clearIndex()
{
    iHandler->deleteFileAndIndex();
}

// parsing documents and cleaning words
void DataCrunch::supplyDocuments()
{
    cout << "***** Supply a path to the XML documents you wish to add or input " << BOLDBLACK << "'default'" << RESET << " to add the default documents *****" << endl;

    string suppliedPath;
    cout << ":: ";
    getline(cin, suppliedPath);
    cout << endl;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    if(suppliedPath == "default")
    {
        start = std::chrono::system_clock::now();
        dParser->parseDocuments("WikiDump2000");
    }
    else
    {
        start = std::chrono::system_clock::now();
        dParser->parseDocuments(suppliedPath);
    }

    dParser->cleanDocObjects();
    end = std::chrono::system_clock::now();
    unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

    cout << BOLDGREEN << "Parsed/Cleaned Documents (" << seconds << " seconds)\n" << RESET << endl;
}

// loading data from documents to index data structure
void DataCrunch::loadDocToIndex()
{
    cout << "***** Storing to data structure...input which of the following structures you would like to use *****" << endl;
    cout << BOLDBLACK << "\t'avl'" << RESET << " - Load index to AVL Tree" << endl;
    cout << BOLDBLACK << "\t'hash'" << RESET << " -  Load index to Hash Table" << endl;

    string dataStruct = "";
    while(dataStruct != "avl" && dataStruct != "hash")
    {
        cout << ":: ";
        getline(cin, dataStruct);
        cout << endl;

        if(dataStruct == "avl" || dataStruct == "hash")
        {
           std::chrono::time_point<std::chrono::system_clock> start, end;
           start = std::chrono::system_clock::now();
           iHandler->storeDocToStruct(dataStruct, dParser->getDocObjects());
           end = std::chrono::system_clock::now();
           unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

           cout << BOLDGREEN << "Loaded Documents to Data Structure (" << seconds << " seconds)\n" << RESET << endl;
        }
        else
        {
            cout << BOLDRED << "!!ERROR: Incorrect data structure request\n" << RESET << endl;
            cout << "***** Input one of the following types *****" << endl;
            cout << BOLDBLACK << "\t'avl'" << RESET << " - Load index to AVL Tree" << endl;
            cout << BOLDBLACK << "\t'hash'" << RESET << " -  Load index to Hash Table" << endl;
        }
    }
}

// =============== Interactive Mode Functions ===============
// loading data from index file to index data structure
void DataCrunch::loadFileToIndex()
{
    cout << "***** Storing to data structure...input which of the following structures you would like to use *****" << endl;
    cout << BOLDBLACK << "\t'avl'" << RESET << " - Load index to AVL Tree" << endl;
    cout << BOLDBLACK << "\t'hash'" << RESET << " -  Load index to Hash Table" << endl;

    string dataStruct = "";
    while(dataStruct != "avl" && dataStruct != "hash")
    {
        cout << ":: ";
        getline(cin, dataStruct);
        cout << endl;

        if(dataStruct == "avl" || dataStruct == "hash")
        {
            ifstream indexFile("index.txt");
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            iHandler->storeIndexToStruct(dataStruct, indexFile);
            end = std::chrono::system_clock::now();
            unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

            cout << BOLDGREEN << "Loaded Index to Data Structure (" << seconds << " seconds)\n" << RESET << endl;
        }
        else
        {
            cout << BOLDRED << "!!ERROR: Incorrect data structure request\n" << RESET << endl;
            cout << "***** Input one of the following types *****" << endl;
            cout << BOLDBLACK << "\t'avl'" << RESET << " - Load index to AVL Tree" << endl;
            cout << BOLDBLACK << "\t'hash'" << RESET << " -  Load index to Hash Table" << endl;
        }
    }
}

// searching index data structure for list of documents containing match to query
void DataCrunch::searchQuery(string kweree)
{
    qHandler->getWords(kweree);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    iHandler->findResults(qHandler->getQue());
    end = std::chrono::system_clock::now();
    unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

    cout << BOLDGREEN << "Returned Results (" << seconds << " seconds)\n" << RESET << endl;

    // followng to be implemented when fixed
    if(qHandler->getQue()->getDocList().empty() == false)
    {
        cout << "***** Resulting documents containing " << qHandler->getQue()->getOriginal() << " *****" << endl;
        dParser->printResults(qHandler->getQue()->getDocList());

        string pageNum;
        cout << ":: ";
        getline(cin, pageNum);
        int pgNum = atoi(pageNum.c_str());
        cout << endl;

        while(pgNum != -1)
        {
            dParser->printPage(pgNum);

            cout << "***** Resulting documents containing " << qHandler->getQue()->getOriginal() << " *****" << endl;
            dParser->printResults(qHandler->getQue()->getDocList());
            cout << ":: ";
            getline(cin, pageNum);
            pgNum = atoi(pageNum.c_str());
            cout << endl;
        }
    }
    else if(iHandler->isNull() == false)
    {
        cout << "***** Your search for - " << qHandler->getQue()->getOriginal() << " - could not be found *****" << endl;
        cout << "Suggestions:" << endl;
        cout << "\t• Make sure all words are spelled correctly\n\t• Queries with multiple words need a boolean operator" << endl;
        cout << "\t• Use AND and OR as prefixes only\n\t• Don't try to use NOT by itself\n\t• Don't look up stop words\n" << endl;
    }

    // after each search we get reset and empty the que
    qHandler->emptyVectors();
}

// =============== Stress Test Mode Function ===============
void DataCrunch::runCommands(string path)
{
    ifstream commands(path.c_str());

    if(commands.is_open())
    {
        cout << "***** Resulting time to complete each command *****" << endl;
        string comm;
        while(getline(commands, comm) && comm != "exit")
        {
            if(comm == "mmode")
            {
                while(getline(commands, comm) && comm != "return")
                {
                    if(comm == "add")
                    {
                        getline(commands, comm);
                        if(comm == "old")
                        {
                            iHandler->deleteIndex();

                            // supplyDocuments() portion
                            getline(commands, comm);
                            std::chrono::time_point<std::chrono::system_clock> start, end;
                            start = std::chrono::system_clock::now();
                            dParser->parseDocuments(comm);
                            dParser->cleanDocObjects();
                            end = std::chrono::system_clock::now();
                            unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
                            cout << BOLDGREEN << "Parsed/Cleaned " << comm << " Documents in (" << seconds << " seconds)\n" << RESET <<endl;


                            // loadDocToIndex() portion
                            getline(commands, comm);
                            start = std::chrono::system_clock::now();
                            iHandler->storeDocToStruct(comm, dParser->getDocObjects());
                            end = std::chrono::system_clock::now();
                            seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

                            string dStruct;
                            if(comm == "avl")
                            {
                                dStruct = "AVL Tree";
                            }
                            else
                            {
                                dStruct = "Hash Table";
                            }
                            cout << BOLDGREEN << "Loaded Documents to " << dStruct << " in (" << seconds << " seconds)\n" << RESET <<endl;

                            start = std::chrono::system_clock::now();
                            iHandler->writeToIndex();
                            end = std::chrono::system_clock::now();
                            seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
                            cout << BOLDGREEN << "Wrote to Index in (" << seconds << " seconds)\n" << RESET <<endl;

                            iHandler->deleteIndex();
                            dParser->emptyVectors();
                        }
                        else if(comm == "new")
                        {
                            iHandler->deleteFileAndIndex();

                            // supplyDocuments() portion
                            getline(commands, comm);
                            std::chrono::time_point<std::chrono::system_clock> start, end;
                            start = std::chrono::system_clock::now();
                            dParser->parseDocuments(comm);
                            dParser->cleanDocObjects();
                            end = std::chrono::system_clock::now();
                            unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
                            cout << BOLDGREEN << "Parsed/Cleaned " << comm << " Documents in (" << seconds << " seconds)\n" << RESET <<endl;

                            // loadDocToIndex() portion
                            getline(commands, comm);
                            start = std::chrono::system_clock::now();
                            iHandler->storeDocToStruct(comm, dParser->getDocObjects());
                            end = std::chrono::system_clock::now();
                            seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

                            string dStruct;
                            if(comm == "avl")
                            {
                                dStruct = "AVL Tree";
                            }
                            else
                            {
                                dStruct = "Hash Table";
                            }
                            cout << BOLDGREEN << "Loaded Documents to " << dStruct << " in (" << seconds << " seconds)\n" << RESET <<endl;

                            start = std::chrono::system_clock::now();
                            iHandler->writeToIndex();
                            end = std::chrono::system_clock::now();
                            seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
                            cout << BOLDGREEN << "Wrote to Index in (" << seconds << " seconds)\n" << RESET <<endl;

                            iHandler->deleteIndex();
                            dParser->emptyVectors();
                        }
                    }
                    else if(comm == "clear")
                    {
                        std::chrono::time_point<std::chrono::system_clock> start, end;
                        start = std::chrono::system_clock::now();
                        iHandler->deleteFileAndIndex();
                        end = std::chrono::system_clock::now();
                        unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
                        cout << BOLDGREEN << "Cleared Index in (" << seconds << " seconds)\n" << RESET <<endl;
                    }
                }

            }
            else if(comm == "imode")
            {
                while(getline(commands, comm) && comm != "return")
                {
                    if(comm == "load")
                    {
                        getline(commands, comm);
                        ifstream indexFile("index.txt");
                        std::chrono::time_point<std::chrono::system_clock> start, end;
                        start = std::chrono::system_clock::now();
                        iHandler->storeIndexToStruct(comm, indexFile);
                        end = std::chrono::system_clock::now();
                        unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

                        string dStruct;
                        if(comm == "avl")
                        {
                            dStruct = "AVL Tree";
                        }
                        else
                        {
                            dStruct = "Hash Table";
                        }
                        cout << BOLDGREEN << "Loaded Index to " << dStruct << " in (" << seconds << " seconds)\n" << RESET <<endl;
                    }
                    else if(comm == "search")
                    {
                        getline(commands, comm);
                        qHandler->getWords(comm);

                        std::chrono::time_point<std::chrono::system_clock> start, end;
                        start = std::chrono::system_clock::now();
                        iHandler->findResults(qHandler->getQue());
                        end = std::chrono::system_clock::now();
                        unsigned int seconds = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();

                        cout << BOLDGREEN << "Returned Results in (" << seconds << " seconds)\n" << RESET << endl;

                        qHandler->emptyVectors();
                    }
                }
            }
        }
    }
    else
    {
        cout << BOLDRED << "!!ERROR: Could not read from commands file\n" << RESET << endl;
    }
}
