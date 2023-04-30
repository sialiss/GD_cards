extends CanvasLayer

@onready var cards = $%cards
var card_scene = preload("res://Scenes/card.tscn")

var file_data = [
	{
		"type": "атомарная механика",
		"name": "ПЕРЕМЕЩАТЬ",
		"text": "Объект двигается в пространстве.",
		"image_path": "res://Assets/cards/move.png"
	}
]

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

	for each in file_data:
		# создание сцены карточки и смена ей картинки на нужную, добавление карточки в хэш таблицу
		var card = card_scene.instantiate()
		var path = load(each.image_path)
		card.texture = path
		cards.add_child(card)
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
