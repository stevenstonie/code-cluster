package com.steven.app.classes;

import java.util.List;
import java.util.ArrayList;

public class Game {
	private int id;
	private String name;
	private List<Game> neighbours;

	public Game(int id, String name) {
		this.id = id;
		this.name = name;
		this.neighbours = new ArrayList<>();
	}

	// getters and an addNeighbour method
}
