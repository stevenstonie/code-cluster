package com.steven.employee_management_application.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.steven.employee_management_application.model.Employee;
import com.steven.employee_management_application.repository.EmployeeRepository;

// This is the base path for all the endpoints in this controller
@CrossOrigin("*") // allow all origins to access this API. This is for development purposes only. In production, you should specify the origins that are allowed to access this API.
@RestController
@RequestMapping("/api/v1/") // standard REST API versioning. 1.0, 2.0, etc.
public class EmployeeController {

	@Autowired
	private EmployeeRepository employeeRepository;

	@GetMapping("/employees")
	public List<Employee> getAllEmployees() {
		return employeeRepository.findAll();
	}
}
