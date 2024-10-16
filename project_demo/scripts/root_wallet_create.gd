extends Node2D

var suiSDK = SuiSDK.new()
var wallet: WalletWrapper

@onready var tree: Tree = $Control/Panel/VBoxContainer/panelResult/VBoxContainer/walletTree
@onready var panelResult: Panel = $Control/Panel/VBoxContainer/panelResult
@onready var schemeErrorLabel: Label = $Control/Panel/VBoxContainer/VBoxContainer/schemeError
@onready var scheme: OptionButton = $Control/Panel/VBoxContainer/VBoxContainer/scheme
@onready var wordErrorLabel: Label = $Control/Panel/VBoxContainer/VBoxContainer2/wordError
@onready var word: OptionButton = $Control/Panel/VBoxContainer/VBoxContainer2/word

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass


func _on_generate_pressed() -> void:
	var schemeIndex = scheme.get_selected_id()
	
	var wordIndex = word.get_selected_id()
	var isError = false
	panelResult.visible = false

	if schemeIndex == -1:
		schemeErrorLabel.text = "Scheme is requred"
		schemeErrorLabel.visible = true
		isError = true
	else:
		schemeErrorLabel.text = ""
		schemeErrorLabel.visible = false
	
	if (wordIndex == -1):
		wordErrorLabel.text = "Word is requred"
		wordErrorLabel.visible = true
		isError = true
	else:
		wordErrorLabel.visible = false
		wordErrorLabel.text = ""
		
	if isError == true:
		return
		
	var schemeValue = scheme.get_item_text(schemeIndex)
	var wordValue = word.get_item_text(wordIndex)
	
	wallet = suiSDK.generateWallet(schemeValue, wordValue)
	
	var buttonCopy: Texture2D = load("res://icons/copy.svg")
	var root = tree.create_item()
	tree.hide_root = true
	tree.set_column_title(0, 'Address')
	tree.set_column_custom_minimum_width(0, 0)
	tree.set_column_custom_minimum_width(1, 200)
	var rowAddress: TreeItem = tree.create_item(root)
	var rowMnemonic: TreeItem = tree.create_item(root)
	var rowPublicKey: TreeItem = tree.create_item(root)
	var rowPrivateKey: TreeItem = tree.create_item(root)
	var rowScheme: TreeItem = tree.create_item(root)
	rowAddress.set_text(0, "Address")
	rowAddress.set_text(1, wallet.get_address())
	rowMnemonic.set_text(0, "Mnemonic")
	rowMnemonic.set_text(1, wallet.get_mnemonic())
	rowPublicKey.set_text(0, "Public key")
	rowPublicKey.set_text(1, wallet.get_public_base64_key())
	rowPrivateKey.set_text(0, "Private key")
	rowPrivateKey.set_text(1, wallet.get_private_key())
	rowScheme.set_text(0, "Schema")
	rowScheme.set_text(1, wallet.get_key_scheme())
	rowAddress.add_button(1, buttonCopy, 0, false, "Copy")
	rowMnemonic.add_button(1, buttonCopy, 0, false, "Copy")
	rowPublicKey.add_button(1, buttonCopy, 0, false, "Copy")
	rowPrivateKey.add_button(1, buttonCopy, 0, false, "Copy")
	rowScheme.add_button(1, buttonCopy, 0, false, "Copy")
	
	panelResult.visible = true
	
	Global.showToast("Generate wallet successfully")

func _on_cancel_pressed() -> void:
	Global.changeScene(Global.SCREEN.ROOT)


func _on_wallet_tree_button_clicked(item: TreeItem, column: int, id: int, mouse_button_index: int) -> void:
	var label = item.get_text(column)
	DisplayServer.clipboard_set(label)
	Global.showToast("Copied")


func _on_button_pressed() -> void:
	if wallet == null:
		return
	var importResult = suiSDK.importFromMnemonic(wallet.get_mnemonic(), wallet.get_key_scheme(), wallet.get_key_scheme())
	if importResult.get_status() == 0:
		Global.showToast("Import wallet " + importResult.get_address() + " successfully")
		_on_cancel_pressed()
	else:
		Global.showToast(importResult.get_error())
