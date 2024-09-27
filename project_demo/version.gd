extends Node

var sdk = SuiSDK.new()

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func onApiVersion():
	var version = sdk.apiVersion()
	self.get_node("result").text="Version: " + str(version)
	
func onCheckAPIVersion():
	var isSuccess = sdk.checkApiVersion()
	print(isSuccess)
	self.get_node("result").text="Success: " + str(isSuccess == 1)

func _on_check_version_pressed() -> void:
	onApiVersion()

func _on_return_pressed() -> void:
	get_tree().change_scene_to_file.bind("res://root.tscn").callv([111])


func _on_check_api_pressed() -> void:
	onCheckAPIVersion()


func _on_available_rpc_methods_pressed() -> void:
	sdk.availableRpcMethods()
