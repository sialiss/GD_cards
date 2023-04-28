#include "Hashtable.h"
#include <string>
#include <cstring>
#include <functional>
#include <iostream>
#include <fstream> // для файла
#include <vcpkg/packages/jsoncpp_x86-windows/include/json/json.h>
#include <algorithm> // для transform()
#include <cctype>    // для tolower()
#include <godot_cpp/variant/utility_functions.hpp>

using namespace std;

// function to fill hash table from JSON file
// void Hashtable::fillHashTableFromJSON(Hashtable &Hashtable, const string &filename)
// {
//     // open JSON file
//     ifstream file(filename);
//     if (!file.is_open())
//     {
//         cerr << "Failed to open file: " << filename << endl;
//         return;
//     }

//     // read JSON data from file
//     Json::Value root;
//     file >> root;

//     int i = 0;
//     // iterate through JSON data and insert into hash table
//     for (auto &element : root)
//     {
//         int key = i;
//         string type = element["type"].asString();
//         string name = element["name"].asString();
//         transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return tolower(c); });
//         string text = element["text"].asString();
//         string image_path = element["image_path"].asString();
//         Hashtable.insert(key, type.c_str(), name.c_str(), text.c_str(), image_path.c_str());
//         i++;
//     }

//     // close file
//     file.close();
// }

const int TABLE_SIZE = 200;

Hashtable::Hashtable()
{
    table = new HashNode *[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = nullptr;
    }
}

Hashtable::~Hashtable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] != nullptr)
        {
            delete table[i];
        }
    }
    delete[] table;
}

int Hashtable::hashFunction(int key)
{
    return key % TABLE_SIZE;
}

void Hashtable::insert(int key, String type, String name, String text, String image_path)
{
    int hash = hashFunction(key);
    while (table[hash] != nullptr && table[hash]->key != key)
    {
        hash = hashFunction(hash + 1);
    }
    if (table[hash] != nullptr)
    {
        delete table[hash];
    }
    table[hash] = new HashNode(key, type, name, text, image_path);
}

void Hashtable::remove(int key)
{
    int hash = hashFunction(key);
    while (table[hash] != nullptr)
    {
        if (table[hash]->key == key)
        {
            break;
        }
        hash = hashFunction(hash + 1);
    }
    if (table[hash] == nullptr)
    {
        return;
    }
    else
    {
        delete table[hash];
    }
}

// int Hashtable::search(const String  name) {
//     for (int i = 0; i < TABLE_SIZE; i++)
//     {
//         if (table[i] != nullptr)
//         {
//             HashNode *entry = table[i];
//             if (entry->name == name) return entry->key;
//         }
//     }
//     return -1;
// }

void Hashtable::display()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] != nullptr)
        {
            UtilityFunctions::print(table[i]->key);
        }
    }
}

// void Hashtable::sort()
// {
//     // create vector of hash table entries
//     vector<HashNode> entries;
//     for (int i = 0; i < TABLE_SIZE; i++)
//     {
//         if (table[i] != nullptr)
//         {
//             HashNode *entry = table[i];
//             while (entry != nullptr)
//             {
//                 entries.push_back(*entry);
//                 entry = entry->next;
//             }
//         }
//     }

//     // sort vector of entries
//     sort(entries.begin(), entries.end(), [](const HashNode &a, const HashNode &b)
//             { return a.key < b.key || (a.key == b.key && a.value.compare(b.value) < 0); });

//     // clear hash table
//     clear();

//     // re-insert sorted entries into hash table
//     for (auto &entry : entries)
//     {
//         insert(entry->key, entry->type, entry->name, entry->text, entry->image_path);
//     }
// }

// void Hashtable::filter(const String type)
// {
//     Hashtable filteredMap;
//     for (int i = 0; i < TABLE_SIZE; i++)
//     {
//         if (table[i] != nullptr)
//         {
//             HashNode *entry = table[i];
//             if (entry->type == type)
//             {
//                 filteredMap.insert(entry->key, entry->type, entry->name, entry->text, entry->image_path);
//             }
//         }
//     }
//     return filteredMap;
// }

void Hashtable::_ready() {
    UtilityFunctions::print("Hello");

    // Hashtable Hashtable;

    // // fill hash table from JSON file
    // fillHashTableFromJSON(Hashtable, "data.json");

    // // display elements
    // Hashtable.display();

    // // search element
    // string name = "перемещать";
    // int value = Hashtable.search(transform(name.begin(), name.end(), name.begin(), [](unsigned char c)
    //                                        { return tolower(c); }););
    // if (value == -1)
    // {
    //     UtilityFunctions::print("No element found at name ", name);
    // }
    // else
    // {
    //     UtilityFunctions::print("Element found at key ", name, ": ", value);
    // }

    // // remove element
    // key = 3;
    // Hashtable.remove(key);

    // // display elements after removal
    // UtilityFunctions::print("Hash Table after removal:");
    // Hashtable.display();

    // // filter elements by value
    // string type = "атомарная механика";
    // UtilityFunctions::print("Filtered Hash Table by type ", type, ":");
    // Hashtable.filter(type);
}


void Hashtable::_bind_methods() {
    ClassDB::bind_method(D_METHOD("hashFunction", "key"), &Hashtable::hashFunction);
    ClassDB::bind_method(D_METHOD("insert", "key", "name", "text", "image_path"), &Hashtable::insert);
    ClassDB::bind_method(D_METHOD("remove", "key"), &Hashtable::remove);
    // ClassDB::bind_method(D_METHOD("search", "name"), &Hashtable::search);
    ClassDB::bind_method(D_METHOD("display"), &Hashtable::display);
    // ClassDB::bind_method(D_METHOD("sort"), &Hashtable::sort);
    // ClassDB::bind_method(D_METHOD("filter", "type"), &Hashtable::filter);
}