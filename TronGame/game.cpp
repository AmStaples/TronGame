
//Game file

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

//axis-aligned bounding boxes - COLLISION DETECTION. Age is added here for the purpose of trails
struct AABB {
	float y, x, width, height, age;
};

bool CheckCollision(const AABB& a, const AABB& b) {
	return (a.x < b.x + b.width && a.x + a.width > b.x && a.y < b.y + b.height && a.y + a.height > b.y);
}
int gamestate = 2; //1 for menu, 2 for gameplay, 3 for p1 win, 4 for p2 win.

float player1_pos_x = 0;
float player1_pos_y = 50;
int p1Color = 0x00FFFF;
AABB p1Box; // Stores collision data for p1
list<AABB> p1Trail; //Stores the Trail
int p1Dir = 4; //Dir is direction. Moves clockwise. 1 is UP, 2 is Right, 3 is down, 4 is left. 

float player2_pos_x = 0;
float player2_pos_y = -50;
int p2Dir = 2;
int p2Color = 0xFF9900;
AABB p2Box;
list<AABB> p2Trail;

float trailAge = 0;
//while (gamestate = menu) {Render menu and options here.}




internal void
simulate_game(Input* input, float dt) {
	//Simulate the data
	clear_screen(); //Clears the previous frame by rendering a new background over the previouse frame "clearing" the screen
	//Gamestate controller
	if (gamestate == 1) {
		//Add code for menu
		
	}
	else if (gamestate == 2) {
		float speed = 30; //units per second

		//Player Movement
		if (is_down(BUTTON_UP) && p1Dir != 3) p1Dir = 1;
		if (is_down(BUTTON_DOWN) && p1Dir != 1) p1Dir = 3;
		if (is_down(BUTTON_LEFT) && p1Dir != 2) p1Dir = 4;
		if (is_down(BUTTON_RIGHT) && p1Dir != 4) p1Dir = 2;

		if (p1Dir == 1) player1_pos_x += speed * dt;
		else if (p1Dir == 3) player1_pos_x -= speed * dt;
		else if (p1Dir == 4) player1_pos_y -= speed * dt;
		else if (p1Dir == 2) player1_pos_y += speed * dt;

		p1Box.x = player1_pos_x;
		p1Box.y = player1_pos_y;
		p1Box.height = 1;
		p1Box.width = 1;

		if (is_down(BUTTON_W) && p2Dir != 3) p2Dir = 1;
		else if (is_down(BUTTON_S) && p2Dir != 1) p2Dir = 3;
		else if (is_down(BUTTON_A) && p2Dir != 2) p2Dir = 4;
		else if (is_down(BUTTON_D) && p2Dir != 4) p2Dir = 2;

		if (p2Dir == 1) player2_pos_x += speed * dt;
		else if (p2Dir == 3) player2_pos_x -= speed * dt;
		else if (p2Dir == 4) player2_pos_y -= speed * dt;
		else if (p2Dir == 2) player2_pos_y += speed * dt;

		p2Box.x = player2_pos_x;
		p2Box.y = player2_pos_y;
		p2Box.height = 1;
		p2Box.width = 1;

		//Verify Current Location is not in trail data.
		for (AABB Entity : p1Trail) {
			if (CheckCollision(p1Box, Entity)) {


				if ((Entity.age + 90) > trailAge) {

				}
				else gamestate = 4;
			}

			if (CheckCollision(p2Box, Entity)) {
				gamestate = 3;
			}
		}

		for (AABB Entity : p2Trail) {
			if (CheckCollision(p2Box, Entity)) {


				if ((Entity.age + 90) > trailAge) {

				}
				else gamestate = 3;
			}

			if (CheckCollision(p1Box, Entity)) {
				gamestate = 4;
			}
		}
		//Register current localtion into trail
		AABB NewSegment;

		NewSegment.height = 0.5;
		NewSegment.width = 0.5;
		NewSegment.age = trailAge;

		NewSegment.x = player1_pos_x;
		NewSegment.y = player1_pos_y;

		p1Trail.push_back(NewSegment);

		NewSegment.x = player2_pos_x;
		NewSegment.y = player2_pos_y;
		p2Trail.push_back(NewSegment);

		trailAge++;
		//Draw on screen
		for (AABB Entity : p1Trail) {
			draw_rect(Entity.y, Entity.x, 1, 1, 0x00caca);
		}
		for (AABB Entity : p2Trail) {
			draw_rect(Entity.y, Entity.x, 1, 1, 0xae6900);
		}

		draw_rect(player1_pos_y, player1_pos_x, 1, 1, p1Color);
		draw_rect(player2_pos_y, player2_pos_x, 1, 1, p2Color);
	}
	else if (gamestate == 3) {
		draw_rect(0, 0, 100, 100, p1Color);
		p1Trail.clear();
		p2Trail.clear();
		p1Dir = 4;
		p2Dir = 2;
		player1_pos_y = 50;
		player1_pos_x = 0;
		player2_pos_y = -50;
		player2_pos_x = 0;

		
		
		

	}
	else {
		draw_rect(0, 0, 100, 100, p2Color);
		p1Trail.clear();
		p2Trail.clear();
		p1Dir = 4;
		p2Dir = 2;
		player1_pos_y = 50;
		player1_pos_x = 0;
		player2_pos_y = -50;
		player2_pos_x = 0;

		
		
		
	}
}