#include "lib.h"

#define SCREEN_WIDTH 127
#define SCREEN_HEIGHT 63

typedef struct {
	Point position;
	u8 direction;
	/*
	# DIRECTION #	
	0: top-right
	1: top:left
	2: bottom-left
	3: bottom-right
	*/
} Ball;

typedef struct {
	i16 center_y_position, x_position;
	u8 offset;
	Line line;
} PLayer;

void draw_line(Line line, i32 color) {
	dline(line.x1, line.y1, line.x2, line.y2, color);
}

int main(void) {
	u8 key;

	u32 score = 0;
	
	Ball ball;
	ball.position = new_point(
		(u16) SCREEN_WIDTH / 2,
		(u16) SCREEN_HEIGHT / 2
	);
	ball.direction = 2;

	PLayer player, bot;

	player.x_position = 5;
	bot.x_position = SCREEN_WIDTH - 5;

	player.offset = 7;
	bot.offset = 7;
	
	player.center_y_position = (i16) SCREEN_HEIGHT / 2;
	bot.center_y_position = (i16) SCREEN_HEIGHT / 2;

	f32 timer = 0;
	f32 timeout = 0.009;
	bool added = false;

	while ((key = pollevent().key) != KEY_DEL) {
		//movements
		switch (key) {
			case KEY_UP:
				player.center_y_position -= 2;
				key = 0;
				break;
			case KEY_DOWN:
				player.center_y_position += 2;
				key = 0;
				break;
			default:
				break;
		}
		bot.center_y_position = ball.position.y;

		//ball movement
		if ((timer += timeout) >= 1) {
			switch (ball.direction) {
				case 0:
					if (ball.position.x >= bot.x_position - 1 && ball.position.y <= bot.center_y_position + bot.offset && ball.position.y >= bot.center_y_position - bot.offset) {
						ball.direction = 1;
					}
					else if (ball.position.y <= 1) {
						ball.direction = 3;
					}
					else {
						ball.position.x++;
						ball.position.y--;
					}
					break;
				case 1:
					if (ball.position.x <= player.x_position - 1 && ball.position.y <= player.center_y_position + player.offset && ball.position.y >= player.center_y_position - player.offset) {
						ball.direction = 0;
						score += 1;
						added = false;
					}
					else if (ball.position.y <= 1) {
						ball.direction = 2;
					}
					else {
						ball.position.x--;
						ball.position.y--;
					}
					break;
				case 2:
					if (ball.position.x <= player.x_position - 1 && ball.position.y <= player.center_y_position + player.offset && ball.position.y >= player.center_y_position - player.offset) {
						ball.direction = 3;
						score += 1;
						added = false;
					}
					else if (ball.position.y >= SCREEN_HEIGHT - 1) {
						ball.direction = 1;
					}
					else {
						ball.position.x--;
						ball.position.y++;
					}
					break;
				case 3:
					if (ball.position.x >= bot.x_position - 1 && ball.position.y <= bot.center_y_position + bot.offset && ball.position.y >= bot.center_y_position - bot.offset) {
						ball.direction = 2;
					}
					else if (ball.position.y >= SCREEN_HEIGHT - 1) {
						ball.direction = 0;
					}
					else {
						ball.position.x++;
						ball.position.y++;
					}
					break;
				default:
					break;
			}
			timer = 0;
		}

		//add speed
		if (score > 0 && score % 2 == 0 && added == false) {
			timeout += 0.002;
			added = true;
		}

		//death
		if (ball.position.x <= 0 || ball.position.x >= SCREEN_WIDTH) break;

		//assign line to players
		player.line = new_vert_line(player.x_position, player.center_y_position - player.offset, player.center_y_position + player.offset);
		bot.line = new_vert_line(bot.x_position, bot.center_y_position - bot.offset, bot.center_y_position + bot.offset);

		//draw
		dclear(C_WHITE);
		draw_line(player.line, C_BLACK);	
		draw_line(bot.line, C_BLACK);	
		drect(ball.position.x - 1, ball.position.y - 1, ball.position.x + 1, ball.position.y + 1, C_BLACK);
		dprint(1, 1, C_BLACK, "Score: %d ", score);
		dupdate();
		
		key = 0;
	}

	dclear(C_WHITE);
	dtext(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, C_BLACK, "GAME OVER!");
	dprint(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, C_BLACK, "YOUR SCORE: %d", (i32)score);
	dupdate();
	getkey();

	return 0;
}