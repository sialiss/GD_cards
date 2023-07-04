extends CanvasLayer

var menu_scene = load("res://Scenes/Menu/Menu.tscn")

@onready var cards = $%cards
var card_scene = preload("res://Scenes/card.tscn")
var f_filter = "all"
var f_sort = "standart"
var f_search_on = false

static func sort_ascending(a, b):
	if a.name < b.name:
		return true
	return false
	
static func sort_descending(a, b):
	if a.name > b.name:
		return true
	return false

var file_data = [
	{
		"type": "атомарная механика",
		"name": "ПЕРЕМЕЩАТЬ",
		"text": "Объект двигается в пространстве.",
		"image_path": "res://Assets/cards/move.png"
	}
]
	
func filter():
	var card_list = Custom_hashtable.new()
	for each in file_data:
		if f_filter != "all" and each.type == f_filter:
			card_list.add_to_hashtable(each)
		elif f_filter == "all":
			card_list.add_to_hashtable(each)
	return card_list
	
func display_cards(card_list):
	for each in card_list.list:
		# создание сцены карточки и смена ей картинки на нужную, добавление карточки
		var card = card_scene.instantiate()
		var path = load(card_list.list[each].image_path)
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
	load_json()
	var card_list = Custom_hashtable.new()
	for each in file_data:
		card_list.add_to_hashtable(each)
	display_cards(card_list)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func search(list, text):
	var new_card_list = Custom_hashtable.new()
	for each in list.list:
		if text == '':
			new_card_list.add_to_hashtable(list.list[each])
		elif text in list.list[each].name:
			new_card_list.add_to_hashtable(list.list[each])
	return new_card_list
	
func sort_list(current_list):
	var sorted_list = Custom_hashtable.new()
	var sorted_names = current_list.list.values()
	
	if f_sort == "standart":
		for each in current_list.list:
			sorted_list.add_to_hashtable(current_list.list[each])
	elif f_sort == "ascending":
		sorted_names.sort_custom(sort_ascending)
		for each in sorted_names:
			sorted_list.add_to_hashtable(each)
	elif f_sort == "descending":
		sorted_names.sort_custom(sort_descending)
		for each in sorted_names:
			sorted_list.add_to_hashtable(each)
		
	if f_search_on:
		sorted_list = search(sorted_list, $Search.text.to_lower())
			
	return sorted_list
	
func _on_search_text_changed():
	hide_all_cards()
	var new_text = $Search.text.to_lower()
	
	if new_text == '':
		f_search_on = false
	else:
		f_search_on = true
		
	var filtered_list = sort_list(filter())
	display_cards(filtered_list)

func _on_sort_item_selected(index):
	hide_all_cards()
	var sorted_list = filter()
	if index == 0:
		f_sort = "standart"
		sorted_list = sort_list(sorted_list)
	elif index == 1:
		f_sort = "ascending"
		sorted_list = sort_list(sorted_list)
	elif index == 2:
		f_sort = "descending"
		sorted_list = sort_list(sorted_list)
			
	display_cards(sorted_list)

func _on_mech_pressed():
	f_filter = "атомарная механика"
	hide_all_cards()
	display_cards(sort_list(filter()))

func _on_space_pressed():
	f_filter = "игровое пространство"
	hide_all_cards()
	display_cards(sort_list(filter()))

func _on_eye_pressed():
	f_filter = "перспектива игрока"
	hide_all_cards()
	display_cards(sort_list(filter()))

func _on_experience_pressed():
	hide_all_cards()
	f_filter = "вид игрового опыта"
	display_cards(sort_list(filter()))

func _on_all_pressed():
	hide_all_cards()
	f_filter = "all"
	display_cards(sort_list(filter()))


func _on_back_pressed():
	get_tree().change_scene_to_packed(menu_scene)
