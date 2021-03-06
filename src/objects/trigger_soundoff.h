#pragma once

#include <tds/object.h>
#include <tds/clock.h>

#define HUNTER_TRIGGERSOFF_INDEX_NAME 0

struct tds_object_type obj_trigger_soundoff_type;

void obj_trigger_soundoff_init(struct tds_object* ptr);
void obj_trigger_soundoff_destroy(struct tds_object* ptr);
void obj_trigger_soundoff_update(struct tds_object* ptr);
void obj_trigger_soundoff_draw(struct tds_object* ptr);
void obj_trigger_soundoff_msg(struct tds_object* ptr, struct tds_object* sender, int msg, void* param);

struct obj_trigger_soundoff_data {
	struct tds_object* player;
	int activated;
	char* name;
};
