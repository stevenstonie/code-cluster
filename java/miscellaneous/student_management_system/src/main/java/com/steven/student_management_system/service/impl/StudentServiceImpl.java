package com.steven.student_management_system.service.impl;

import java.util.List;

import org.springframework.stereotype.Service;

import com.steven.student_management_system.entity.Student;
import com.steven.student_management_system.repository.StudentRepository;
import com.steven.student_management_system.service.StudentService;

@Service
public class StudentServiceImpl implements StudentService {

	private StudentRepository studentRepository;

	public StudentServiceImpl(StudentRepository studentRepository) {
		super();
		this.studentRepository = studentRepository;
	}

	@Override
	public List<Student> getAllStudents() {
		return studentRepository.findAll();
	}

	@Override
	public Student saveStudent(Student student) {
		return studentRepository.save(student);
	}

}
