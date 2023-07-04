#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Hashtable : public Node2D
{
    GDCLASS(Hashtable, Node2D);

public:
    Hashtable();
    ~Hashtable() {};
    int hash_f(Variant key);
    void insert(Variant key, Variant type, Variant name, Variant text, Variant image_path);
    void restructuring(Hashtable *&table);
    bool remove(int key);
    void _ready();

protected:
    static void _bind_methods();

private:
    Variant key = "";
    Variant type = "";
    Variant name = "";
    Variant text = "";
    Variant image_path = "";
    int state = 0;
};

#endif