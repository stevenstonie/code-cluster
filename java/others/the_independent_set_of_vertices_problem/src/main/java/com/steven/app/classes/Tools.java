package com.steven.app.classes;

import java.util.Random;

public class Tools {
	public static GamesGraph createGames(Integer nbOfGames) {
		GamesGraph allGames = new GamesGraph();
		if (nbOfGames != null) {
			allGames.setNbOfGames(nbOfGames);
		}

		for (int i = 0; i < allGames.getNbOfGames(); i++) {
			allGames.addGame(new Game(i, "game" + i));
		}

		return allGames;
	}

	public static void addContestantsForTheFirstSubpoint(GamesGraph allGames) {
		if (allGames.getNbOfGames() < 2) {
			return;
		}
		int limitOfGamesWithConflicts = allGames.getNbOfGames() / 4;
		if (allGames.getNbOfGames() < 8) {
			limitOfGamesWithConflicts = 2;
		}

		Random random = new Random();

		for (Game game : allGames.getGames()) {
			int nbOfGamesWithConflicts = random.nextInt(limitOfGamesWithConflicts); // each game has a chance of having from 0 to n/4 - 1 conflicts
			for (int j = 0; j < nbOfGamesWithConflicts; j++) {
				int gameWithConflict = random.nextInt(allGames.getNbOfGames());
				game.addConflictingGame(allGames.getGame(gameWithConflict));
			}
		}
	}

	public static void addContestantsForTheSecondSubpoint(GamesGraph allGames) {
		if (allGames.getNbOfGames() < 3) {
			return;
		}
		if (allGames.getNbOfGames() < 6) {
			allGames.getGame(0).addConflictingGame(allGames.getGame(1));
			allGames.getGame(1).addConflictingGame(allGames.getGame(2));
			allGames.getGame(2).addConflictingGame(allGames.getGame(3));
			allGames.getGame(3).addConflictingGame(allGames.getGame(4));
			allGames.getGame(4).addConflictingGame(allGames.getGame(0));
		} else {
			allGames.getGame(0).addConflictingGame(allGames.getGame(1));
			allGames.getGame(1).addConflictingGame(allGames.getGame(2));
			allGames.getGame(2).addConflictingGame(allGames.getGame(0));

			for (int i = 3; i < allGames.getNbOfGames() - 1; i++) {
				allGames.getGame(i).addConflictingGame(allGames.getGame(i + 1));
			}
			allGames.getGame(allGames.getNbOfGames() - 1).addConflictingGame(allGames.getGame(3));
		}
	}
}
