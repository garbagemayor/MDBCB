#include "Calculator.h"

void Calculator::visitCol(Filter::Col * col) {
    Table * table = tableManager -> getTableByName(col -> tableName);
    if (table == NULL) {
        col -> valGrid -> setNull();
        return;
    }
    TableRow * tableRow = table -> getRow(pageId, slotId);
    if (tableRow == NULL) {
        col -> valGrid -> setNull();
        return;
    }
    TableGrid * tableGrid = tableRow -> getGridByName(col -> tableColumn -> getName());
    if (tableGrid == NULL) {
        col -> valGrid -> setNull();
        return;
    }
    col -> valGrid -> setDataByGrid(tableGrid);
}
