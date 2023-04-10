package com.steven;

import java.net.URI;
import java.util.concurrent.TimeUnit;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

import com.launchdarkly.eventsource.EventHandler;
import com.launchdarkly.eventsource.EventSource;

@Service
public class WikimediaChangesProducer {
	private static final Logger LOGGER = LoggerFactory.getLogger(WikimediaChangesProducer.class);

	private KafkaTemplate<String, String> kafkaTemplate;

	public WikimediaChangesProducer(KafkaTemplate<String, String> kafkaTemplate) {
		this.kafkaTemplate = kafkaTemplate;
	}

	public void sendMessage() {
		String topic = "wikimedia_recent_changes";

		// to read real-time stream data from a site, we use event source
		EventHandler eventHandler = new WikimediaChangesHandler(kafkaTemplate, topic);
		String url = "https://stream.wikimedia.org/v2/stream/recentchange";
		EventSource.Builder builder = new EventSource.Builder(eventHandler, URI.create(url));
		EventSource eventSource = builder.build();
		eventSource.start();

		try {
			TimeUnit.MINUTES.sleep(10);
		} catch (InterruptedException e) {
			System.out.println(e.getMessage() + " in method: " + e.getStackTrace()[0].getMethodName());
		}
	}
}
