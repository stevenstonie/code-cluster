extends Area2D

@onready var gameManager = %gameManager;
@onready var animationPlayer = $AnimationPlayer;

func _on_body_entered(_body):
	gameManager.add_point();	
	animationPlayer.play("pickup");
