extends Node

@onready var scoreLabel = $scoreLabel;
var coins = 0;

func add_point():
	coins += 1;
	if coins >= 27:
		scoreLabel.text = "congrats. you collected all the coins";
		return;
	scoreLabel.text = "congrats. you collected " + str(coins) + " coins.";
