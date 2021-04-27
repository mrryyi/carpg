#pragma once

unsigned int next_item_container_id() {
	static unsigned int current_item_container_id = 0;
	return ++current_item_container_id;
};
unsigned int next_session_item_id() {
	static unsigned int current_session_item_id  = 0;
	return ++current_session_item_id;
};
