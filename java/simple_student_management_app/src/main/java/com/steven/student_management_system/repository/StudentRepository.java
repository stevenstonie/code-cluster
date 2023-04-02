package com.steven.student_management_system.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.steven.student_management_system.entity.Student;

// handles all the CRUD operations for the Student entity
public interface StudentRepository extends JpaRepository<Student, Long> {
	// extends JpaRepo which provides out of the box CRUD methods operations (such as save(), findById(), findAll(), deleteById()), so we don't have to implement them
}
