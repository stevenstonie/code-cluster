package com.steven.app;

import java.util.List;
import java.util.Set;

import com.steven.app.classes.Game;
import com.steven.app.classes.GamesGraph;

public class App {
    public static void main(String[] args) {
        GamesGraph allGames = createGames();

        Set<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM();

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }

        allGames = createGamesWhereEachConflictsWithExactlyTwo();

        maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM_2conflictsEach();

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }

    private static GamesGraph createGames() {
        Game basketball = new Game(1, "basketball");
        Game volleyball = new Game(2, "volleyball");
        Game football = new Game(3, "football");
        Game tennis = new Game(4, "tennis");
        Game badminton = new Game(5, "badminton");
        Game baseball = new Game(6, "baseball");
        Game fusball = new Game(7, "fusball");
        GamesGraph allGames = new GamesGraph(
                List.of(basketball, volleyball, football, tennis, badminton, baseball, fusball));

        basketball.addGameWithRecurringParticipants(baseball);
        basketball.addGameWithRecurringParticipants(tennis);
        basketball.addGameWithRecurringParticipants(football);
        baseball.addGameWithRecurringParticipants(badminton);
        baseball.addGameWithRecurringParticipants(football);

        return allGames;
    }

    private static GamesGraph createGamesWhereEachConflictsWithExactlyTwo() {
        Game basketball = new Game(1, "basketball");
        Game volleyball = new Game(2, "volleyball");
        Game football = new Game(3, "football");
        Game tennis = new Game(4, "tennis");
        Game badminton = new Game(5, "badminton");
        Game baseball = new Game(6, "baseball");
        Game fusball = new Game(7, "fusball");
        GamesGraph allGames = new GamesGraph(
                List.of(basketball, volleyball, football, tennis, badminton, baseball, fusball));

        basketball.addGameWithRecurringParticipants(volleyball);
        volleyball.addGameWithRecurringParticipants(football);
        football.addGameWithRecurringParticipants(tennis);
        tennis.addGameWithRecurringParticipants(basketball);
        badminton.addGameWithRecurringParticipants(baseball);
        baseball.addGameWithRecurringParticipants(fusball);
        fusball.addGameWithRecurringParticipants(badminton);

        return allGames;
    }
}
