#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <godot_cpp/classes/node2d.hpp>
#include <HashNode.cpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Hashtable : public Node2D
{
    GDCLASS(Hashtable, Node2D);

public:
    Hashtable();
    ~Hashtable();
    int hashFunction(int key);
    void insert(int key, String type, String name, String text, String image_path);
    void remove(int key);
    // int search(const String name);
    void display();
    // void sort();
    // void filter(const Stringtype);
    void _ready();

protected:
    static void _bind_methods();

private:
    HashNode **table;
};

#endif