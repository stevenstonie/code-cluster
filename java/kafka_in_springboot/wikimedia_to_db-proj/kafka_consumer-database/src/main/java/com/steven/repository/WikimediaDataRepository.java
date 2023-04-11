package com.steven.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.steven.entity.WikimediaData;

public interface WikimediaDataRepository extends JpaRepository<WikimediaData, Long> {
	// inherited all of the JpaRepository's crud operations
}
