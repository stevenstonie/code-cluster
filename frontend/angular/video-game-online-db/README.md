# VideoGameOnlineDb

This project was generated with [Angular CLI](https://github.com/angular/angular-cli) version 16.2.4.

## Before

Before running. in order for it to work, you need to get the necessary api keys from:
https://rapidapi.com/accujazz/api/rawg-video-games-database/details and https://rawg.io/apidocs. create accounts, follow the links, get the three necessary keys and add them to an environment.hidden.ts file in the environments directory. the template is:
```
export const environment = {
	production: false,
	BASE_URL: 'https://rawg-video-games-database.p.rapidapi.com',
	rapidApiKey: 'get this',
	rapidApiHost: 'and this from https://rapidapi.com/accujazz/api/rawg-video-games-database',
	apiKey: 'get this from the https://rawg.io/apidocs site',
};
```


## Development server

Run `ng serve` for a dev server. Navigate to `http://localhost:4200/`. The application will automatically reload if you change any of the source files.

## Code scaffolding

Run `ng generate component component-name` to generate a new component. You can also use `ng generate directive|pipe|service|class|guard|interface|enum|module`.

## Build

Run `ng build` to build the project. The build artifacts will be stored in the `dist/` directory.

## Running unit tests

Run `ng test` to execute the unit tests via [Karma](https://karma-runner.github.io).

## Running end-to-end tests

Run `ng e2e` to execute the end-to-end tests via a platform of your choice. To use this command, you need to first add a package that implements end-to-end testing capabilities.

## Further help

To get more help on the Angular CLI use `ng help` or go check out the [Angular CLI Overview and Command Reference](https://angular.io/cli) page.
