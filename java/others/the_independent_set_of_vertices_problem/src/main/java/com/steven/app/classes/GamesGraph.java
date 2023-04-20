package com.steven.app.classes;

import java.util.List;

public class GamesGraph {
	private List<Game> games;

	public GamesGraph(List<Game> games) {
		this.games = games;
	}

	public List<Game> getGames() {
		return games;
	}

	public void addGame(Game game) {
		games.add(game);
	}

	// TODO: Greedy algorithm here
}
