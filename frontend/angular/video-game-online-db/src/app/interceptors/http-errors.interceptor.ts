import { HttpEvent, HttpHandler, HttpInterceptor, HttpRequest } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, catchError, throwError as observableThrowError } from 'rxjs';

@Injectable()
export class HttpErrorsInterceptor implements HttpInterceptor {
	intercept(
		req: HttpRequest<any>,
		next: HttpHandler): Observable<HttpEvent<any>> {
		return next.handle(req).pipe(
			catchError((err) => {
				console.log(err);
				return observableThrowError(err);
				// TODO: handle the deprecated method
			})
		)
	}
}