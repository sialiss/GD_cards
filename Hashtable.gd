extends Node
class_name Custom_hashtable

var num_of_keys = 300
var list = {}

func hashfunc(key):
	var hash_value = 0
	for n in range(key.length()):
		hash_value += key.unicode_at(n) ** 2
		hash_value *= 17
	hash_value = (hash_value*(hash_value/num_of_keys))%num_of_keys
	return hash_value
	
func add_to_hashtable(card):
	var key = hashfunc(card.name)
	list[key] = card;
	
func delete_from_hashtable(card):
	var key = hashfunc(card.name)
	list.erase(key)
