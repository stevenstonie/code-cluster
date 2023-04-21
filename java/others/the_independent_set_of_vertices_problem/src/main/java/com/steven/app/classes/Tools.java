package com.steven.app.classes;

import java.util.Random;

public class Tools {
	public static GamesGraph createGames() {
		GamesGraph allGames = new GamesGraph();
		allGames.setNbOfGames(15);

		for (int i = 0; i < allGames.getNbOfGames(); i++) {
			allGames.addGame(new Game(i, "game" + i));
		}

		return allGames;
	}

	public static void addContestantsForTheFirstSubpoint(GamesGraph allGames) {
		Random random = new Random();

		for (Game game : allGames.getGames()) {
			int nbOfGamesWithConflicts = random.nextInt(allGames.getNbOfGames() / 4); // each game has a change of having from 0 to n/4 - 1 conflicts
			for (int j = 0; j < nbOfGamesWithConflicts; j++) {
				int gameWithConflict = random.nextInt(allGames.getNbOfGames());
				game.addGameWithRecurringParticipants(allGames.getGame(gameWithConflict));
			}
		}
	}

	public static void addContestantsForTheSecondSubpoint(GamesGraph allGames) {
		allGames.getGame(0).addGameWithRecurringParticipants(allGames.getGame(1));
		allGames.getGame(1).addGameWithRecurringParticipants(allGames.getGame(2));
		allGames.getGame(2).addGameWithRecurringParticipants(allGames.getGame(3));
		allGames.getGame(3).addGameWithRecurringParticipants(allGames.getGame(0));

		allGames.getGame(4).addGameWithRecurringParticipants(allGames.getGame(5));
		allGames.getGame(5).addGameWithRecurringParticipants(allGames.getGame(6));
		allGames.getGame(6).addGameWithRecurringParticipants(allGames.getGame(4));
	}
}
