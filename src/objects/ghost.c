#include "ghost.h"
#include "player.h"

#include <tds/tds.h>

#include "../tds_game/game_input.h"
#include "../tds_game/game_msg.h"

struct tds_object_type obj_ghost_type = {
	.type_name = "obj_ghost",
	.default_sprite = "spr_ghost_left",
	.default_params = 0,
	.default_params_size = 0,
	.data_size = sizeof(struct obj_ghost_data),
	.func_init = obj_ghost_init,
	.func_destroy = obj_ghost_destroy,
	.func_update = obj_ghost_update,
	.func_draw = obj_ghost_draw,
	.func_msg = obj_ghost_msg,
	.func_import = obj_ghost_import,
	.func_export = obj_ghost_export,
	.save = 1
};

void obj_ghost_init(struct tds_object* ptr) {
	struct obj_ghost_data* data = (struct obj_ghost_data*) ptr->object_data;

	data->track = NULL;
	data->dt = 0.0f;
}

void obj_ghost_destroy(struct tds_object* ptr) {
}

void obj_ghost_update(struct tds_object* ptr) {
	/* We will not allow slower movement than normal, we will use the axis and implement a basic deadzone */
	struct obj_ghost_data* data = (struct obj_ghost_data*) ptr->object_data;
	struct tds_object* player = tds_engine_get_object_by_type(tds_engine_global, "obj_player");

	if (player) {
		if (sqrt(pow(player->x - ptr->x, 2) + pow(player->y - ptr->y, 2)) <= TDS_OBJ_GHOST_AGGRO_DIST) {
			data->track = player;
		} else {
			data->track = NULL;
		}
	}

	if (!data->track) {
		return;
	}

	if (ptr->x < data->track->x) {
		ptr->x += TDS_OBJ_GHOST_SPEED;
		data->facing = 1;
	} else if (ptr->x > data->track->x) {
		ptr->x -= TDS_OBJ_GHOST_SPEED;
		data->facing = -1;
	}

	if (ptr->y < data->track->y) {
		ptr->y += TDS_OBJ_GHOST_SPEED;
	} else if (ptr->y > data->track->y) {
		ptr->y -= TDS_OBJ_GHOST_SPEED;
	}

	if (tds_collision_get_overlap(ptr, player)) {
		tds_object_msg(player, ptr, TDS_GAME_MSG_PLAYER_HIT, NULL);
	}
}

void obj_ghost_draw(struct tds_object* ptr) {
	struct obj_ghost_data* data = (struct obj_ghost_data*) ptr->object_data;

	if (data->facing > 0) {
		tds_object_set_sprite(ptr, tds_sprite_cache_get(ptr->smgr, "spr_ghost_right"));
	} else {
		tds_object_set_sprite(ptr, tds_sprite_cache_get(ptr->smgr, "spr_ghost_left"));
	}
}

void obj_ghost_msg(struct tds_object* ptr, struct tds_object* sender, int msg, void* param) {
}

void obj_ghost_import(struct tds_object* ptr, struct tds_object_param* param) {
}

struct tds_object_param* obj_ghost_export(struct tds_object* ptr) {
	return 0;
}