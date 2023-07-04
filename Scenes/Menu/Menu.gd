extends CanvasLayer

var game_scene = load("res://Scenes/Game/Game.tscn")
var cards_scene = load("res://Scenes/ListOfCards/ListOfCards.tscn")

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_list_of_cards_pressed():
	get_tree().change_scene_to_packed(cards_scene)
