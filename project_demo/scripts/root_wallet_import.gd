extends Node2D

var suiSDK = SuiSDK.new()

@onready var privateKey: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/privateKey
@onready var privateKeyError: Label = $Control/Panel/VBoxContainer/VBoxContainer/privateKeyError
@onready var mnemonic: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/mnemonic
@onready var mnemonicError: Label = $Control/Panel/VBoxContainer/VBoxContainer2/mnemonicError
@onready var scheme: OptionButton = $Control/Panel/VBoxContainer/VBoxContainer3/scheme
@onready var schemeError: Label = $Control/Panel/VBoxContainer/VBoxContainer3/schemeError
@onready var alias: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer4/alias
@onready var aliasError: Label = $Control/Panel/VBoxContainer/VBoxContainer4/aliasError

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func backToWallet():
	Global.changeScene(Global.SCREEN.ROOT)

func _on_button_pressed() -> void:
	if privateKey.text.length() == 0:
		privateKeyError.text = "Private key is requred"
		privateKeyError.visible = true
		return
	else:
		privateKeyError.text = ""
		privateKeyError.visible = false
	
	var importResult = suiSDK.importFromPrivateKey(privateKey.text)
	if importResult.get_status() == 0:
		Global.showToast("Import wallet " + importResult.get_address() + " successfully")
		backToWallet()
	else:
		Global.showToast(importResult.get_error())

func _on_import_mnemonic_button_pressed() -> void:
	var schemeIndex = scheme.get_selected_id()
	
	var isError = false

	if schemeIndex == -1:
		schemeError.text = "Scheme is requred"
		schemeError.visible = true
		isError = true
	else:
		schemeError.text = ""
		schemeError.visible = false
	
	if mnemonic.text.length() == 0:
		mnemonicError.text = "Mnemonic is requred"
		mnemonicError.visible = true
		return
	else:
		mnemonicError.text = ""
		mnemonicError.visible = false
	
	if alias.text.length() == 0:
		aliasError.text = "Alias wallet is requred"
		aliasError.visible = true
		return
	else:
		aliasError.text = ""
		aliasError.visible = false
		
	if isError == true:
		return
		
	var schemeValue = scheme.get_item_text(schemeIndex)
	
	print(mnemonic.text)
	print(schemeValue)
	print(alias.text)
	
	var importResult = suiSDK.importFromMnemonic(mnemonic.text, schemeValue, alias.text)
	
	if importResult.get_status() == 0:
		Global.showToast("Import wallet " + importResult.get_address() + " successfully")
		backToWallet()
	else:
		Global.showToast(importResult.get_error())

func _on_cancel_pressed() -> void:
	backToWallet()
