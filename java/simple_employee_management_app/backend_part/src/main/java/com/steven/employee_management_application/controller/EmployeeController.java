package com.steven.employee_management_application.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.steven.employee_management_application.exception.ResourceNotFoundException;
import com.steven.employee_management_application.model.Employee;
import com.steven.employee_management_application.repository.EmployeeRepository;

// This is the base path for all the endpoints in this controller
@CrossOrigin("http://localhost:4200/") // allows the Angular app to access this API
@RestController
@RequestMapping("/api/v1/") // standard REST API versioning. 1.0, 2.0, etc.
public class EmployeeController {

	@Autowired
	private EmployeeRepository employeeRepository;

	@GetMapping("/employees")
	public List<Employee> getAllEmployees() {
		return employeeRepository.findAll();
	}

	@PostMapping("/employees")
	public Employee createEmployee(@RequestBody Employee employee) {
		return employeeRepository.save(employee);
	}

	@GetMapping("/employees/{id}")
	public ResponseEntity<Employee> getEmployeeById(@PathVariable Long id) { // @PathVariable is used to get the id from the URL
		Employee employee = employeeRepository.findById(id)
				.orElseThrow(() -> new ResourceNotFoundException("Employee not found with id: " + id));

		return ResponseEntity.ok(employee);
	}

	@PutMapping("/employees/{id}")
	public ResponseEntity<Employee> updateEmployee(@PathVariable Long id, @RequestBody Employee employeeNewDetails) {
		Employee employee = employeeRepository.findById(id)
				.orElseThrow(() -> new ResourceNotFoundException("Employee with id : " + id + " does not exist."));

		setCredentialsOfEmployee(employee, employeeNewDetails);

		Employee updatedEmployee = employeeRepository.save(employee);
		return ResponseEntity.ok(updatedEmployee);
	}

	private void setCredentialsOfEmployee(Employee employee, Employee employeeNewDetails) {
		employee.setFirstName(employeeNewDetails.getFirstName());
		employee.setLastName(employeeNewDetails.getLastName());
		employee.setEmailId(employeeNewDetails.getEmailId());
	}
}
