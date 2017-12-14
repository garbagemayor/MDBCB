#include "TableManager.h"

int runTestTableSystem() {
    BufPageManager * bufPageManager = new BufPageManager(new FileManager());
    TableManager * tableManager = new TableManager(bufPageManager);
    
    TableHeader * tableHeader = new TableHeader();
    tableHeader -> setName("Table1");
    
    
    
    
    
    
    
    
    
    
    
    
    delete bufPageManager;
    delete tableManager;
    delete tableHeader;
    
    
    
    return 0;
}
