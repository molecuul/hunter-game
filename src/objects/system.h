#pragma once

#include <tds/object.h>

extern struct tds_object_type obj_system_type;

void obj_system_update(struct tds_object* ptr);
void obj_system_init(struct tds_object* ptr);
void obj_system_destroy(struct tds_object* ptr);
void obj_system_import(struct tds_object* ptr, struct tds_object_param* param_list);
struct tds_object_param* obj_system_export(struct tds_object* ptr);