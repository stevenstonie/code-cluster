package com.steven.app;

import java.util.List;

import com.steven.app.classes.Game;
import com.steven.app.classes.GamesGraph;

public class App {
    public static void main(String[] args) {
        Game basketball = new Game(1, "basketball");
        Game volleyball = new Game(2, "volleyball");
        Game football = new Game(3, "football");
        Game tennis = new Game(4, "tennis");
        Game badminton = new Game(5, "badminton");
        Game baseball = new Game(6, "baseball");
        GamesGraph allGames = new GamesGraph(List.of(basketball, volleyball, football, tennis, badminton, baseball));

        basketball.addGameWithRecurringParticipants(baseball);
        basketball.addGameWithRecurringParticipants(tennis);
        basketball.addGameWithRecurringParticipants(football);
        baseball.addGameWithRecurringParticipants(badminton);
        baseball.addGameWithRecurringParticipants(football);

        List<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM();

        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }
}
