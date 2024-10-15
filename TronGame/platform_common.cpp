struct Button_state {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_COUNT, //this should be the Last item
};

struct Input {
	Button_state buttons[BUTTON_COUNT];
};