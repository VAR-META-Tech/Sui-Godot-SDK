extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var tabs: TabContainer = get_node("TabContainer")
	print(Global.tabIndex)
	tabs.current_tab = Global.tabIndex

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _on_tab_container_tab_clicked(tab: int) -> void:
	Global.tabIndex = tab
