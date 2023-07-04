#include "Hashtable.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>
#include <stdlib.h>

using namespace Godot;

const int NumOfKeys = 50;
int MaxNumOfCollisions = NumOfKeys * 7 / 10;
int filled = 0;

Hashtable::Hashtable(Variant key, int value, Variant type, Variant name, Variant text, Variant image_path) {
    this->key = key;
    this->value = value;
    this->type = type;
    this->name = name;
    this->text = text;
    this->image_path = image_path;
    this->state = 1;
};

Hashtable::hash_f(Variant key)
{
    int hashNum = 0;
    for (int j = 0; j < 6; j++)
        hashNum = hashNum + (key[j] * key[j]);
    hashNum = hashNum % NumOfKeys;
    return hashNum;
}

Hashtable::restructuring(Hashtable *&table)
{
    int oldNum = NumOfKeys;
    NumOfKeys *= 2;
    MaxNumOfCollisions = NumOfKeys * 7 / 10;
    filled = 0;
    Hashtable *newTable = new Hashtable[NumOfKeys];

    for (int i = 0; i < oldNum; i++)
    {
        if (table[i].state == 1)
            table.insert(newTable, table[i]);
    }

    Hashtable *tmp = table;
    delete[] tmp;
    table = newTable;
}

Hashtable::insert(Hashtable *&table, Hashtable e)
{
    int hashNum = table.hash_f(e.key);

    for (int j = 0; j < MaxNumOfCollisions; j++)
    {
        if (table[hashNum].state < 1)
        {
            table[hashNum] = e;
            filled += 1;
            if (filled > MaxNumOfCollisions)
            {
                table.restructuring(table);
                return table.insert(table, e);
            }
            return hashNum;
        }
        else if (table[hashNum].key == e.key)
        {
            if (table[hashNum].value != e.value)
            {
                table[hashNum] = e;
            }
            return hashNum;
        }

        hashNum += 1;
        if (hashNum >= NumOfKeys)
            hashNum -= NumOfKeys;
    }

    table.restructuring(table);
    return table.insert(table, e);
}

Hashtable::remove(Hashtable *&table, Variant key)
{
    int hashNum = table.hash_f(key);
    for (int j = 0; j < MaxNumOfCollisions; j++)
    {
        if (table[hashNum].state == 0)
            return false;
        else if (table[hashNum].state == 1 && table[hashNum].key == key)
        {
            table[hashNum].state = -1;
            filled -= 1;
            return true;
        }

        hashNum += 1;
        if (hashNum >= NumOfKeys)
            hashNum -= NumOfKeys;
    }
    return false;
}

void Hashtable::_ready() {
    UtilityFunctions::print("Hello");
}

void Hashtable::_bind_methods() {
    ClassDB::bind_method(D_METHOD("hashFunction", "key"), &Hashtable::hashFunction);
    ClassDB::bind_method(D_METHOD("insert", "key", "name", "text", "image_path"), &Hashtable::insert);
    ClassDB::bind_method(D_METHOD("remove", "key"), &Hashtable::remove);
}