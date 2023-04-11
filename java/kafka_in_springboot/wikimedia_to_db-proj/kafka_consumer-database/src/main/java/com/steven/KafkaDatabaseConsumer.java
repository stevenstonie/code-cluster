package com.steven;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

import com.steven.entity.WikimediaData;
import com.steven.repository.WikimediaDataRepository;

@Service
public class KafkaDatabaseConsumer {
	private static final Logger LOGGER = LoggerFactory.getLogger(KafkaDatabaseConsumer.class);

	private WikimediaDataRepository wikimediaDataRepository;

	// the class spring bean contains only one parameterized constructor so there is no need to add @Autowired here
	public KafkaDatabaseConsumer(WikimediaDataRepository wikimediaDataRepository) {
		this.wikimediaDataRepository = wikimediaDataRepository;
	}

	@KafkaListener(topics = "wikimedia_recent_changes", groupId = "myGroup")
	public void consume(String eventMessage) {
		LOGGER.info(String.format("event message received -> %s", eventMessage));

		WikimediaData wikimediaData = new WikimediaData();
		wikimediaData.setWikiEventData(eventMessage);

		wikimediaDataRepository.save(wikimediaData);
	}
}
