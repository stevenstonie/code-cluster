package com.steven.student_management_system.service;

import java.util.List;

import com.steven.student_management_system.entity.Student;

public interface StudentService {
	List<Student> getAllStudents();

	Student saveStudent(Student student);

	Student getStudentById(Long id);

	Student updateStudent(Student student);
}
