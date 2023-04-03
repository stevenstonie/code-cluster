import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class EmployeeService {

  private baseURL = "localhost:8081/api/v1/employees"
  constructor(private httpClient: HttpClient) { }
}
