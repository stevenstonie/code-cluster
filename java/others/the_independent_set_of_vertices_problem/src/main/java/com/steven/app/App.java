package com.steven.app;

import java.util.List;

import com.steven.app.classes.Game;
import com.steven.app.classes.GamesGraph;

public class App {
    public static void main(String[] args) {
        // create the games (basketball, volleyball, football, tennis, etc.)
        Game basketball = new Game(1, "basketball");
        Game volleyball = new Game(2, "volleyball");
        Game football = new Game(3, "football");
        Game tennis = new Game(4, "tennis");
        Game badminton = new Game(5, "badminton");
        Game baseball = new Game(7, "baseball");
        GamesGraph allGames = new GamesGraph(List.of(basketball, volleyball, football, tennis, badminton, baseball));

        // add the recurring participants to each sport (if 1->2,3 then 2->1 and 3->1)
        basketball.addGameWithRecurringParticipants(baseball);
        basketball.addGameWithRecurringParticipants(tennis);
        basketball.addGameWithRecurringParticipants(football);
        baseball.addGameWithRecurringParticipants(basketball);
        tennis.addGameWithRecurringParticipants(basketball);
        football.addGameWithRecurringParticipants(basketball);
        baseball.addGameWithRecurringParticipants(badminton);
        baseball.addGameWithRecurringParticipants(football);
        badminton.addGameWithRecurringParticipants(baseball);
        football.addGameWithRecurringParticipants(baseball);

        // run the algorithm
        List<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM();

        // yippie!!
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }
}
