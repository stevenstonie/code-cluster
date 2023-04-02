package com.steven.student_management_system.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

import com.steven.student_management_system.entity.Student;
import com.steven.student_management_system.service.StudentService;

@Controller
public class StudentController {

	private StudentService studentService;

	public StudentController(StudentService studentService) {
		super();
		this.studentService = studentService;
	}

	@GetMapping("/students")
	public String listStudents(Model model) {
		model.addAttribute("students", studentService.getAllStudents());
		return "students";
	}

	@GetMapping("/students/add")
	public String addStudentForm(Model model) {
		model.addAttribute("student", new Student());
		return "add_student";
	}

	@PostMapping("/students")
	public String addStudent(@ModelAttribute("student") Student student) {
		studentService.saveStudent(student);
		return "redirect:/students";
	}

	@GetMapping("/students/edit/{id}")
	public String editStudentForm(@PathVariable Long id, Model model) {
		model.addAttribute("student", studentService.getStudentById(id));
		return "edit_student";
	}

	@PostMapping("/students/{id}")
	public String updateStudent(@PathVariable Long id, @ModelAttribute("student") Student student, Model model) {
		Student existingStudent = studentService.getStudentById(id);

		updateStudentCredentials(existingStudent, student);

		studentService.updateStudent(existingStudent);
		return "redirect:/students";
	}

	@GetMapping("/students/{id}")
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
