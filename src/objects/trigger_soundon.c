#include "trigger_soundon.h"
#include "camera.h"

#include <tds/tds.h>
#include <tds/render.h>

#include "../tds_game/game_msg.h"
#include "../save.h"

#include <stdlib.h>

struct tds_object_type obj_trigger_soundon_type = {
	.type_name = "obj_trigger_soundon",
	.default_sprite = NULL,
	.data_size = sizeof(struct obj_trigger_soundon_data),
	.func_init = obj_trigger_soundon_init,
	.func_destroy = obj_trigger_soundon_destroy,
	.func_update = obj_trigger_soundon_update,
	.func_draw = obj_trigger_soundon_draw,
	.func_msg = obj_trigger_soundon_msg,
	.save = 1,
};

void obj_trigger_soundon_init(struct tds_object* ptr) {
	struct obj_trigger_soundon_data* data = (struct obj_trigger_soundon_data*) ptr->object_data;

	int* cid = tds_object_get_ipart(ptr, HUNTER_TRIGGERSON_INDEX_CONTROL);

	if (cid) {
		data->control_id = *cid;
	} else {
		data->control_id = 0;
	}

	data->activated = 1;
}

void obj_trigger_soundon_destroy(struct tds_object* ptr) {
}

void obj_trigger_soundon_update(struct tds_object* ptr) {
	struct obj_trigger_soundon_data* data = (struct obj_trigger_soundon_data*) ptr->object_data;

	if (!data->activated) {
		return;
	}

	if (!data->player) {
		data->player = tds_engine_get_object_by_type(tds_engine_global, "obj_player");

		if (!data->player) {
			tds_logf(TDS_LOG_WARNING, "Failed to locate player object. Will try again next frame.\n");
			return;
		}
	}

	if (tds_collision_get_overlap(ptr, data->player)) {
		tds_logf(TDS_LOG_DEBUG, "Triggered, sending BGM start with control index %d\n", data->control_id);
		tds_engine_broadcast(tds_engine_global, TDS_GAME_MSG_BGM_START, &data->control_id);
		data->activated = 0;
	}
}

void obj_trigger_soundon_draw(struct tds_object* ptr) {
}

void obj_trigger_soundon_msg(struct tds_object* ptr, struct tds_object* sender, int msg, void* param) {
	struct obj_trigger_soundon_data* data = (struct obj_trigger_soundon_data*) ptr->object_data;

	switch(msg) {
	case TDS_GAME_MSG_BGM_STOP:
		data->activated = 1;
		break;
	}
}