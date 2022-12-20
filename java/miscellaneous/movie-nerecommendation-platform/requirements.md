### description

movie platform. an user can like movies from an available dataset (database / file).
then, depending on the choice, the user will be recommended similar movies.
we have two types of users: normal users and admin users.
-the user can:

- search all the movies in the database
- like a movie
- can look at his feed

-the admin can:

- add movies in the database / file by console or file

the initial feed (when no movies are liked) is a random list of movies.

##### scenario

the given movies are:

| Movie                  | Genre   | Release date     | Likes |
|------------------------|---------|------------------|-------|
| Adventure Time         | Cartoon | 5 april 2010     | 100   |
| GOT                    | Fantasy | 17 april 2011    | 80    |
| The Promised Neverland | Anime   | 1 september 2020 | 78    |
| Witcher                | Fantasy | 23 august 2021   | 56    |
| FullMetal Alchemist    | Anime   | 4 october 2003   | 100   |
| Parasyte               | Anime   | 23 august 2021   | 125   |

1. an user x is given.
2. the feed, at the start, is random.
3. the user x likes The Promised Neverland.
4. now the movies with the same genre will have priority, sorted by likes or release date (the user can choose which one to use).

below is the table sorted based on the user's choice:

| Movie                  | Genre   | Release date     | Likes |Priority |
|------------------------|---------|------------------|-------|---------|
| Parasyte               | Anime   | 23 august 2021   | 125   |    x    |
| FullMetal Alchemist    | Anime   | 4 october 2003   | 100   |    x    |
| The Promised Neverland | Anime   | 1 september 2020 | 78    |    x    |
| Adventure Time         | Cartoon | 5 april 2010     | 100   | random  |
| GOT                    | Fantasy | 17 april 2011    | 80    | random  |
| Witcher                | Fantasy | 23 august 2021   | 56    | random  |
