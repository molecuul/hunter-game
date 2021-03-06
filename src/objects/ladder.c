#include "ladder.h"
#include "camera.h"
#include "player.h"

#include <tds/tds.h>
#include <tds/render.h>

#include "../msg.h"
#include "../save.h"

#include <stdlib.h>

/* This is pretty much a complete copy of trigger_dialog, except with an index for a sprite. */

struct tds_object_type obj_ladder_type = {
	.type_name = "obj_ladder",
	.default_sprite = NULL,
	.data_size = sizeof(struct obj_ladder_data),
	.func_init = obj_ladder_init,
	.func_destroy = obj_ladder_destroy,
	.func_update = obj_ladder_update,
	.func_draw = obj_ladder_draw,
	.func_msg = obj_ladder_msg,
	.save = 1,
};

void obj_ladder_init(struct tds_object* ptr) {
	struct obj_ladder_data* data = (struct obj_ladder_data*) ptr->object_data;
}

void obj_ladder_destroy(struct tds_object* ptr) {
	struct obj_ladder_data* data = (struct obj_ladder_data*) ptr->object_data;
}

void obj_ladder_update(struct tds_object* ptr) {
	struct obj_ladder_data* data = (struct obj_ladder_data*) ptr->object_data;

	if (!data->player) {
		data->player = tds_engine_get_object_by_type(tds_engine_global, "obj_player");
	}

	if (!data->player) return;

	struct obj_player_data* pdata = (struct obj_player_data*) data->player->object_data;

	if (pdata->on_ladder) {
		if (!tds_collision_get_overlap(ptr, data->player)) {
			pdata->on_ladder = 0;
		}
	}
}

void obj_ladder_draw(struct tds_object* ptr) {
	struct obj_ladder_data* data = (struct obj_ladder_data*) ptr->object_data;

	/* debug cbox */
	/*
	tds_render_flat_set_mode(tds_engine_global->render_flat_overlay_handle, TDS_RENDER_COORD_WORLDSPACE);
	tds_render_flat_set_color(tds_engine_global->render_flat_overlay_handle, 1.0f, 0.0f, 0.0f, 0.5f);
	tds_render_flat_quad(tds_engine_global->render_flat_overlay_handle, ptr->x - ptr->cbox_width / 2.0f, ptr->x + ptr->cbox_width / 2.0f, ptr->y + ptr->cbox_height / 2.0f, ptr->y - ptr->cbox_height / 2.0f, NULL);
	*/
}

void obj_ladder_msg(struct tds_object* ptr, struct tds_object* sender, int msg, void* param) {
	struct obj_ladder_data* data = (struct obj_ladder_data*) ptr->object_data;

	switch (msg) {
	case MSG_PLAYER_ACTION:
		if (data->player && tds_collision_get_overlap(ptr, data->player)) {
			tds_engine_broadcast(tds_engine_global, MSG_LADDER_ACK, ptr);
		}
		break;
	}
}
