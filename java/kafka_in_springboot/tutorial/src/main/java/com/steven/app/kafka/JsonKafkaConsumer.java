package com.steven.app.kafka;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

import com.steven.app.model.User;

@Service
public class JsonKafkaConsumer {
	private static final Logger LOGGER = LoggerFactory.getLogger(JsonKafkaConsumer.class);

	@KafkaListener(topics = "steven_json", groupId = "myGroup")
	public void consume(User user) { // spring kafka provides JsonDeserializer to convert the JSON User object into a Java User Object
		LOGGER.info(String.format("json message received -> %s", user.toString()));
	}

}
