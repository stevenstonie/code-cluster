package com.steven.student_management_system.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import com.steven.student_management_system.entity.Student;
import com.steven.student_management_system.service.StudentService;

@Controller
@RequestMapping("/students")
public class StudentController {

	private StudentService studentService;

	public StudentController(StudentService studentService) {
		this.studentService = studentService;
	}

	// handles HTTP GET requests to '/students' and returns a list of all the students
	@GetMapping("")
	public String listStudents(Model model) {
		model.addAttribute("students", studentService.getAllStudents());
		return "students";
	}

	// handles GET requests to '/students/add' which returns a form to add a new student
	@GetMapping("/add")
	public String addStudentForm(Model model) {
		model.addAttribute("student", new Student());
		return "add_student";
	}

	// handles the submission of the form to add a new student via a POST request to '/students'
	@PostMapping("")
	public String addStudent(@ModelAttribute("student") Student student) {
		studentService.saveStudent(student);
		return "redirect:/students";
	}

	// handles GET requests to '/students/edit/{id}' which returns a form to edit an existing student
	@GetMapping("/edit/{id}")
	public String editStudentForm(@PathVariable Long id, Model model) {
		model.addAttribute("student", studentService.getStudentById(id));
		return "edit_student";
	}

	// handles the submission of the form to edit a student via a POST request to '/students/{id}'
	@PostMapping("/{id}")
	public String updateStudent(@PathVariable Long id, @ModelAttribute("student") Student student, Model model) {
		Student existingStudent = studentService.getStudentById(id);

		updateStudentCredentials(existingStudent, student);

		studentService.updateStudent(existingStudent);
		return "redirect:/students";
	}

	// handles GET requests to '/students/{id}' to delete an existing student
	@GetMapping("/{id}")
	public String deleteStudent(@PathVariable Long id) {
		studentService.deleteStudentById(id);
		return "redirect:/students";
	}

	private void updateStudentCredentials(Student existingStudent, Student student) {
		existingStudent.setId(student.getId());
		existingStudent.setFirstName(student.getFirstName());
		existingStudent.setLastName(student.getLastName());
		existingStudent.setEmail(student.getEmail());
	}
}
