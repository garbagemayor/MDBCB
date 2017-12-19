#ifndef INDEX_STRUCTURE_H_
#define INDEX_STRUCTURE_H_

/**
 *  索引的结构类型
 *  其中，treeIndex是B+树索引，hashIndex是散列索引
 */
enum IndexStructure {
    in_baseIndex = 0,
    in_treeIndex = 1,
    in_hashIndex = 2,
};

#endif // INDEX_STRUCTURE_H_
