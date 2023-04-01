package com.steven.student_management_system;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import com.steven.student_management_system.entity.Student;
import com.steven.student_management_system.repository.StudentRepository;

@SpringBootApplication
public class StudentManagementSystemApplication implements CommandLineRunner {

	public static void main(String[] args) {
		SpringApplication.run(StudentManagementSystemApplication.class, args);
	}

	@Autowired
	private StudentRepository studentRepository;

	@Override
	public void run(String... args) throws Exception {
		Student student1 = new Student("punpun", "onodera", "sorelatable@geemail.com");
		studentRepository.save(student1);

		Student student2 = new Student("momo", "thecat", "surelynotstolen@jahoo.com");
		studentRepository.save(student2);

		Student student3 = new Student("mein", "gott", "ichhabevielehausaufgaben@outlook.lookout");
		studentRepository.save(student3);
	}

}
