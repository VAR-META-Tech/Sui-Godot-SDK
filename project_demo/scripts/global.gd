extends Node

var tabIndex = 0
var currentWallet: String = ""


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func getCurrentWallet():
	return currentWallet
	
func setCurrentWallet(wallet):
	currentWallet = wallet

func showToast(message: String):
	ToastParty.show({
		"text": message,                  # Text (emojis can be used)
		"bgcolor": Color(0, 0, 0, 1),     # Background Color
		"color": Color(1, 1, 1, 1),       # Text Color
		"gravity": "top",                 # top or bottom
		"direction": "center",            # left or center or right
		"text_size": 16,                  # [optional] Text (font) size // experimental (warning!)
		"use_font": false                 # [optional] Use custom ToastParty font // experimental (warning!)
	})
