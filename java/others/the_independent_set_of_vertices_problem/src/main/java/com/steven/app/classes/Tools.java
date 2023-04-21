package com.steven.app.classes;

public class Tools {
	public static GamesGraph createGames() {
		GamesGraph allGames = new GamesGraph();

		for (int i = 0; i < 7; i++) {
			allGames.addGame(new Game(i, "game" + i));
		}

		return allGames;
	}
}
