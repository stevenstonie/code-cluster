package com.steven.employee_management_application.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.steven.employee_management_application.model.Employee;

public interface EmployeeRepository extends JpaRepository<Employee, Long> {
	// all operations are already implemented by Spring Data JPA
}
