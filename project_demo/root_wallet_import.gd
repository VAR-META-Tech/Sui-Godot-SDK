extends Node2D

var suiSDK = SuiSDK.new()

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func backToWallet():
	get_tree().change_scene_to_file("res://root.tscn")

func _on_button_pressed() -> void:
	var privateKey: LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/privateKey")
	var privateKeyError: Label = get_node("Control/Panel/VBoxContainer/VBoxContainer/privateKeyError")
	if privateKey.text.length() == 0:
		privateKeyError.text = "Private key is requred"
		privateKeyError.visible = true
		return
	else:
		privateKeyError.text = ""
		privateKeyError.visible = false
	
	suiSDK.importFromPrivateKey(privateKey.text)
	backToWallet()


func _on_import_mnemonic_button_pressed() -> void:
	var mnemonic: LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/LineEdit")
	var mnemonicError: Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/mnemonicError")
	if mnemonic.text.length() == 0:
		mnemonicError.text = "Mnemonic is requred"
		mnemonicError.visible = true
		return
	else:
		mnemonicError.text = ""
		mnemonicError.visible = false

	suiSDK.importFromMnemonic(mnemonic.text)
	backToWallet()


func _on_cancel_pressed() -> void:
	backToWallet()
