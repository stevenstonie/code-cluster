extends Node

@onready var coinsLabel = $coinsLabel;
var coins = 0;

func add_point():
	coins += 1;
	coinsLabel.text = "you collected " + str(coins) + " coins.";
