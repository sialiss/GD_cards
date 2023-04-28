#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class HashNode
{
public:
    int key;
    String type;
    String name;
    String text;
    String image_path;
    HashNode(int key, String type, String name, String text, String image_path)
    {
        this->key = key;
        this->type = type;
        this->name = name;
        this->text = text;
        this->image_path = image_path;
    }
};