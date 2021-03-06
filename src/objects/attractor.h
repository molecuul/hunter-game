#pragma once
#include <tds/object.h>

/*
 * obj_attractor
 * f0: distance to start pulling camera (in world units)
 * f1: camera pull factor (between 0 and 1, increase for stronger pull)
 */

#define HUNTER_ATTRACTOR_INDEX_DIST 0
#define HUNTER_ATTRACTOR_INDEX_FACTOR 1

struct tds_object_type obj_attractor_type;

void obj_attractor_init(struct tds_object* ptr);
void obj_attractor_destroy(struct tds_object* ptr);
void obj_attractor_update(struct tds_object* ptr);
void obj_attractor_draw(struct tds_object* ptr);
void obj_attractor_msg(struct tds_object* ptr, struct tds_object* sender, int msg, void* param);

struct obj_attractor_data {
	float dist, factor;
};
