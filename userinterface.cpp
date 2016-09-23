#include "userinterface.h"

// default cstr
UserInterface::UserInterface()
{
    cout << "***************************************************************************" << endl;
    cout << "\tNow running the 'Kwirē Search Engine' by Team ZombieCoders" << endl;
    cout << "***************************************************************************\n" << endl;

    dCrunch = new DataCrunch();
}

// overloaded dstr
UserInterface::~UserInterface()
{
    cout << "***************************************************************************" << endl;
    cout << "\tShutting down 'Kwirē Search Engine' - Goodbye" << endl;
    cout << "***************************************************************************" << endl;
    delete dCrunch;
}

// allows user to select either of the 3 search engine modes
void UserInterface::setMode(string mode)
{
    if(mode == "mmode")
    {
        enterMaintenance();
    }
    else if(mode == "imode")
    {
        enterInteractive();
    }
    else if(mode == "stmode")
    {
        enterStressTest();
    }
    else
    {
        cout << BOLDRED << "!!ERROR: Incorrect mode type\n" << RESET << endl;
    }
}

// users in maintenance mode may add to the index or clear the index file/structure
void UserInterface::enterMaintenance()
{
    cout << "***** Entering Maintenance Mode...input one of the following commands *****" << endl;
    cout << BOLDBLACK << "\t'add'" << RESET << " - Add document(s) to index" << endl;
    cout << BOLDBLACK << "\t'clear'" << RESET << " - Clear index file/structure" << endl;
    cout << BOLDBLACK << "\t'return'" << RESET << " - Return to mode selection" << endl;

    string command;
    cout << ":: ";
    getline(cin, command);
    cout << endl;

    while(command != "return")
    {
        if(command == "add")
        {
            dCrunch->addToIndex();
        }
        else if(command == "clear")
        {
            dCrunch->clearIndex();
        }
        else
        {
            cout << BOLDRED << "!!ERROR: Incorrect command input\n" << RESET << endl;
        }

        cout << "***** Input one of the following commands *****" << endl;
        cout << BOLDBLACK << "\t'add'" << RESET << " - Add document(s) to index" << endl;
        cout << BOLDBLACK << "\t'clear'" << RESET << " - Clear index file/structure" << endl;
        cout << BOLDBLACK << "\t'return'" << RESET << " - Return to mode selection" << endl;
        cout << ":: ";
        getline(cin, command);
        cout << endl;
    }
}

// users in interatice mode may load the index in a data structure of their choosing or make a search query
void UserInterface::enterInteractive()
{
    cout << "***** Entering Interactive Mode...input one of the following commands *****" << endl;
    cout << BOLDBLACK << "\t'load'" << RESET << " - Load index to data structure" << endl;
    cout << BOLDBLACK << "\t'search'" << RESET << " - Request a search query" << endl;
    cout << BOLDBLACK << "\t'return'" << RESET << " - Return to mode selection" << endl;

    string command;
    cout << ":: ";
    getline(cin, command);
    cout << endl;

    while(command != "return")
    {
        if(command == "load")
        {
            dCrunch->loadFileToIndex();
        }
        else if(command == "search")
        {
            cout << "***** Enter your query - You may use the following boolean expressions in your search *****" << endl;
            cout << BOLDBLACK << "\t'AND'" << RESET << " - (Prefix) Searches must include both terms" << endl;
            cout << BOLDBLACK << "\t'OR'" << RESET << " - (Prefix) Searches may include one or both terms" << endl;
            cout << BOLDBLACK << "\t'NOT'" << RESET << " - Searches must exclude the term" << endl;

            string search;
            cout << ":: ";
            getline(cin, search);
            cout << endl;

            dCrunch->searchQuery(search);
        }
        else
        {
            cout << BOLDRED << "!!ERROR: Incorrect command input\n" << RESET << endl;
        }

        cout << "****** Input one of the following commands *****" << endl;
        cout << BOLDBLACK << "\t'load'" << RESET << " - Load index to data structure" << endl;
        cout << BOLDBLACK << "\t'search'" << RESET << " - Request a search query" << endl;
        cout << BOLDBLACK << "\t'return'" << RESET << " - Return to mode selection" << endl;
        cout << ":: ";
        getline(cin, command);
        cout << endl;
    }
}

// users in stress test mode may supply a command file to test the different fucntions/data structures
void UserInterface::enterStressTest()
{
    cout << "***** Entering Stress Test Mode...supply your command file or enter " << BOLDBLACK << "'return'" << RESET << " to return to mode selection *****" << endl;

    string file;
    cout << ":: ";
    getline(cin, file);
    cout << endl;

    while(file != "return")
    {
        dCrunch->runCommands(file);

        cout << "***** Stress Test completed...supply a new command file or enter " << BOLDBLACK << "'return'" << RESET << " to return to mode selection *****" << endl;
        cout << ":: ";
        getline(cin, file);
        cout << endl;
    }
}
