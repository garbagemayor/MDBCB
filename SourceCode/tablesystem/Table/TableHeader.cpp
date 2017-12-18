#include "TableHeader.h"
#include "TableRow.h"

int TableHeader::getPossibleMaxSize() {
    return TableRow::getPossibleSize(this, 1);
}

int TableHeader::getPossibleMinSize() {
    return TableRow::getPossibleSize(this, 0);
}
