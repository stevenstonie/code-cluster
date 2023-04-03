import { Component } from '@angular/core';
import { Employee } from '../employee';

@Component({
  selector: 'app-create-employee',
  templateUrl: './create-employee.component.html',
  styleUrls: ['./create-employee.component.css']
})
export class CreateEmployeeComponent {

  employee: Employee = new Employee();
  constructor() { }

  ngOnInit(): void {

  }

  onSubmit() {
    console.log(this.employee);
  }
}
