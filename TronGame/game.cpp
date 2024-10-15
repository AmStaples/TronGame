
//Game file

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0;
float player_pos_y = 0;




internal void
simulate_game(Input* input, float dt) {
	clear_screen(); //Clears the previous frame by rendering a new background over the previouse frame "clearing" the screen
	float speed = 30; //units per second
	if (is_down(BUTTON_UP)) player_pos_x += speed*dt;
	if (is_down(BUTTON_DOWN)) player_pos_x -= speed * dt;
	if (is_down(BUTTON_LEFT)) player_pos_y -= speed * dt;
	if (is_down(BUTTON_RIGHT)) player_pos_y += speed * dt;

	draw_rect(player_pos_y, player_pos_x, 1, 1, 0xff0000);
}