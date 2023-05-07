extends CanvasLayer

@onready var cards = $%cards
var card_scene = preload("res://Scenes/card.tscn")
var num_of_keys = 300
var f_filter = ""

var file_data = [
	{
		"type": "атомарная механика",
		"name": "ПЕРЕМЕЩАТЬ",
		"text": "Объект двигается в пространстве.",
		"image_path": "res://Assets/cards/move.png"
	}
]

func hashfunc(key):
	var hash_value = 0
	for n in range(key.length()):
		hash_value += key.unicode_at(n) ** 2
		hash_value *= 17
	hash_value = (hash_value*(hash_value/num_of_keys))%num_of_keys
	return hash_value
	
func add_to_hashtable(cards_list, card):
	var key = hashfunc(card.name)
	cards_list[key] = card;
	
func delete_from_hashtable(cards_list, card):
	var key = hashfunc(card.name)
	cards_list.erase(key)
	
func filter(type = ""):
	var new_card_list = {}
	for each in file_data:
		if type != "" and each.type == type:
			add_to_hashtable(new_card_list, each)
		elif type == "":
			add_to_hashtable(new_card_list, each)
	return new_card_list
	
func display_cards(card_list):
	for each in card_list:
		# создание сцены карточки и смена ей картинки на нужную, добавление карточки в хэш таблицу
		var card = card_scene.instantiate()
		var path = load(card_list[each].image_path)
		card.texture = path
		cards.add_child(card)

func hide_all_cards():
	for each in cards.get_children():
		cards.remove_child(each)

func save():
	var file = FileAccess.open("res://Assets/data.json", FileAccess.WRITE)
	file.store_line(JSON.stringify(file_data))

func load_json():
	if not FileAccess.file_exists("res://Assets/data.json"):
		save()
		return
	var file = FileAccess.open("res://Assets/data.json", FileAccess.READ)
	var data = JSON.parse_string(file.get_as_text())
	file_data = data
	for each in file_data:
		each.name = each.name.to_lower()

func _ready():
	f_filter = ""
	load_json()
	var cards_list = {}
	for each in file_data:
		add_to_hashtable(cards_list, each)
	display_cards(cards_list)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_mech_pressed():
	f_filter = "атомарная механика"
	hide_all_cards()
	display_cards(filter("атомарная механика"))


func _on_space_pressed():
	f_filter = "игровое пространство"
	hide_all_cards()
	display_cards(filter("игровое пространство"))


func _on_eye_pressed():
	f_filter = "перспектива игрока"
	hide_all_cards()
	display_cards(filter("перспектива игрока"))


func _on_experience_pressed():
	hide_all_cards()
	f_filter = "вид игрового опыта"
	display_cards(filter("вид игрового опыта"))


func _on_all_pressed():
	hide_all_cards()
	f_filter = ""
	display_cards(filter())


func _on_search_text_changed():
	hide_all_cards()
	var new_text = $Search.text
	var new_card_list = {}
	var filtered_list = filter(f_filter)
	
	for each in filtered_list:
		if new_text == '':
			add_to_hashtable(new_card_list, filtered_list[each])
		elif new_text in filtered_list[each].name:
			add_to_hashtable(new_card_list, filtered_list[each])
	display_cards(new_card_list)
