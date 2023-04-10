package com.steven;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.kafka.core.KafkaTemplate;

import com.launchdarkly.eventsource.EventHandler;
import com.launchdarkly.eventsource.MessageEvent;

public class WikimediaChangesHandler implements EventHandler {
	private static final Logger LOGGER = LoggerFactory.getLogger(WikimediaChangesHandler.class);
	private KafkaTemplate<String, String> kafkaTemplate;
	private String topic;

	public WikimediaChangesHandler(KafkaTemplate<String, String> kafkaTemplate, String topic) {
		this.kafkaTemplate = kafkaTemplate;
		this.topic = topic;
	}

	@Override
	public void onClosed() throws Exception {
		throw new UnsupportedOperationException("Unimplemented method 'onClosed'");
	}

	@Override
	public void onComment(String arg0) throws Exception {
		throw new UnsupportedOperationException("Unimplemented method 'onComment'");
	}

	@Override
	public void onError(Throwable arg0) {
		throw new UnsupportedOperationException("Unimplemented method 'onError'");
	}

	@Override
	public void onMessage(String arg0, MessageEvent messageEvent) throws Exception {
		LOGGER.info(String.format("event data -> %s", messageEvent.getData()));

		kafkaTemplate.send(topic, messageEvent.getData());
	}

	@Override
	public void onOpen() throws Exception {
		throw new UnsupportedOperationException("Unimplemented method 'onOpen'");
	}

}
