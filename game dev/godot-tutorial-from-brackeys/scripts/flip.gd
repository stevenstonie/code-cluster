extends Node2D

@onready var object = $AnimatedSprite2D;
# Called when the node enters the scene tree for the first time.
func _ready():
	object.flip_h = true;

