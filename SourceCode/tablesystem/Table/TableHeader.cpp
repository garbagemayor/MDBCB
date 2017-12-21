#include "TableHeader.h"
#include "TableRow.h"

/**
 *  中午呢
 */

int TableHeader::getPossibleMaxSize() {
    return TableRow::getPossibleSize(this, 1);
}

int TableHeader::getPossibleMinSize() {
    return TableRow::getPossibleSize(this, 0);
}
