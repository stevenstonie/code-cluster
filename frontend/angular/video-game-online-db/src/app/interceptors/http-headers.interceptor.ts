import { HttpEvent, HttpHandler, HttpInterceptor, HttpRequest } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable } from "rxjs";
import { environment as env } from 'src/environments/environment.development';

@Injectable()
export class HttpHeadersInterceptor implements HttpInterceptor {
	intercept(
		req: HttpRequest<any>,
		next: HttpHandler
	): Observable<HttpEvent<any>> {
		req = req.clone({
			setHeaders: {
				'x-rapidapi-key': env.rapidApiKey,
				'x-rapidapi-host': env.rapidApiHost,
			},
			setParams: {
				key: env.apiKey,
			},
		});
		return next.handle(req);
	}
}