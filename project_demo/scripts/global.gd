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

enum SCREEN {
	ROOT,
	ROOT_BALACNE_SEND,
	ROOT_NFT_MINT,
	ROOT_NFT_TRANSFER,
	ROOT_WALLET_CREATE,
	ROOT_WALLET_IMPORT
}

func changeScene(scene):
	var path = ""
	match scene:
		SCREEN.ROOT: path = "res://scenes/root.tscn"
		SCREEN.ROOT_BALACNE_SEND: path = "res://scenes/root_balance_send.tscn"
		SCREEN.ROOT_NFT_MINT: path = "res://scenes/root_nft_mint.tscn"
		SCREEN.ROOT_NFT_TRANSFER: path = "res://scenes/root_nft_transfer.tscn"
		SCREEN.ROOT_WALLET_CREATE: path = "res://scenes/root_wallet_create.tscn"
		SCREEN.ROOT_WALLET_IMPORT: path = "res://scenes/root_wallet_import.tscn"
	
	get_tree().change_scene_to_file(path)
