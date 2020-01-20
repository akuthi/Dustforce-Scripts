#include "enable_disable_layers.cpp"

class script
{
	[checkbox] bool show_distance = true;
	scene@ g;
	camera@ cam;
	entity@ player;
	[text] float max_cam_dist = 1000;
	[hidden] int player_cam_dist = 0;
	uint player_id =0;
	textfield@ distance;
	[hidden] float distance_mult = 0;
	float x_offset = 0;
	
	script()
	{
		@g= get_scene();
		player_id = get_active_player();
		@cam = get_camera(player_id);
		@player = cam.puppet();
		@distance = create_textfield();
		distance.align_horizontal(-775);
	}
	
	void editor_step()
	{
		distance.text("Distance: ");
		x_offset = distance.text_width();
	}
	
	void step(int entities)
	{
		check_player();
		x_offset = distance.text_width();
	}
	
	void editor_draw(float sub_frame)
	{
		draw(sub_frame);
	}
	
	void draw(float sub_frame)
	{
		if(show_distance)
		{
			distance.draw_hud(2, 2, -775, -400, 1, 1, 0);
		}
	}
	
	void check_player()
	{
		@player = cam.puppet();
		if(@player != null)
		{
			float player_cam_dist_x = player.x() - cam.x();
			float player_cam_dist_y = player.y() - cam.y();
			player_cam_dist = int(sqrt((player_cam_dist_x*player_cam_dist_x) + (player_cam_dist_y*player_cam_dist_y)));
			distance.text("Distance: " + player_cam_dist);
			if(player_cam_dist > max_cam_dist)
			{
				player.as_dustman().kill(false);
			}
		}
	}
}