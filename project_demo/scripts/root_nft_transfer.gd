extends Node2D

var suiSDK = SuiSDK.new()
var packageId = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0"

@onready var from:LineEdit = $Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender
@onready var fromError:Label = $Control/Panel/VBoxContainer/VBoxContainer/senderError
@onready var to:LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/to
@onready var toError:Label = $Control/Panel/VBoxContainer/VBoxContainer2/toError
@onready var nftId:LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/nftId
@onready var nftIdError:Label = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/nftIdError

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		from.text = Global.currentWallet


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
	
func returnRoot():
	Global.changeScene(Global.SCREEN.ROOT)

func _on_mint_pressed() -> void:
	
	
	if from.text == "":
		fromError.visible = true
		fromError.text = "From wallet address is required"
	else:
		fromError.visible = false
		fromError.text = ""
		
	if to.text == "":
		toError.visible = true
		toError.text = "To wallet address is required"
	else:
		toError.visible = false
		toError.text = ""

	if nftId.text == "":
		nftIdError.visible = true
		nftIdError.text = "Description NFT is required"
	else:
		nftIdError.visible = false
		nftIdError.text = ""

	if from.text == "" || to.text == "" || nftId.text == "":
		return
		
	var message = suiSDK.transferNft(packageId, from.text, nftId.text, to.text)
	Global.showToast(message)
	returnRoot()	


func _on_cancel_pressed() -> void:
	returnRoot()
