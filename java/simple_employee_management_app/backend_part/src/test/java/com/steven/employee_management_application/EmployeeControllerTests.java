package com.steven.employee_management_application;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.List;
import java.util.Map;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.ResponseEntity;

import com.steven.employee_management_application.controller.EmployeeController;
import com.steven.employee_management_application.model.Employee;

@SpringBootTest
public class EmployeeControllerTests {
	Employee employee;
	Employee newEmployee;

	@Autowired
	private EmployeeController employeeController;

	@BeforeEach
	public void setUp() {
		employee = createNewEmployeeGicaDude();

		newEmployee = employeeController.createEmployee(employee);
	}

	@Test
	public void testGetAllEmployees() {
		List<Employee> employees = employeeController.getAllEmployees();

		assertNotNull(employees);
	}

	@Test
	public void testCreateEmployee() {
		assertNotNull(newEmployee);

		assertEquals(employee.getId(), newEmployee.getId());
		assertEqualsOfTwoEmployees(employee, newEmployee);
	}

	@Test
	public void testGetEmployeeById() {
		ResponseEntity<Employee> responseEntity = employeeController.getEmployeeById(newEmployee.getId());
		Employee foundEmployee = responseEntity.getBody();

		assertNotNull(foundEmployee);

		assertEquals(newEmployee.getId(), foundEmployee.getId());
		assertEqualsOfTwoEmployees(newEmployee, foundEmployee);
	}

	@Test
	public void testUpdateEmployee() {
		Employee updatedEmployee = new Employee();
		updatedEmployee.setFirstName("Marian");
		updatedEmployee.setLastName("SaVie");
		updatedEmployee.setEmailId("telefonulmeu@unde.e");

		ResponseEntity<Employee> responseEntity = employeeController.updateEmployee(newEmployee.getId(),
				updatedEmployee);
		Employee updatedEmployeeResponse = responseEntity.getBody();

		assertNotNull(updatedEmployeeResponse);

		assertEquals(newEmployee.getId(), updatedEmployeeResponse.getId());
		assertEqualsOfTwoEmployees(updatedEmployee, updatedEmployeeResponse);
	}

	@Test
	public void testDeleteEmployee() {
		ResponseEntity<Map<String, Boolean>> responseEntity = employeeController
				.deleteEmployee(newEmployee.getId());
		Map<String, Boolean> response = responseEntity.getBody();

		assertNotNull(response);
		assertTrue(response.get("deleted"));
	}

	//

	private void assertEqualsOfTwoEmployees(Employee employee, Employee newEmployee) {
		assertEquals(employee.getFirstName(), newEmployee.getFirstName());
		assertEquals(employee.getLastName(), newEmployee.getLastName());
		assertEquals(employee.getEmailId(), newEmployee.getEmailId());
	}

	private Employee createNewEmployeeGicaDude() {
		Employee employee = new Employee();
		employee.setFirstName("Gica");
		employee.setLastName("Dude");
		employee.setEmailId("gigadude@ceva.altceva");
		return employee;
	}
}
