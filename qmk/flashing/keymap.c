#include QMK_KEYBOARD_H

#define RIDER_GLOBAL_SEARCH LCTL(KC_T)        // ctrl + t
#define CHROME_DEV_TOOLS LCTL(LSFT(KC_I))     // ctrl + shift + i
#define WIN_SNIP LWIN(LSFT(KC_S))             // windows + shift + s

enum viterbi_layers {
  _QWERTY,
  _LOWER
};

 enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  MACRO1,
	MACRO2
};

/* _QWERTY
   ,------------------------------------------------,	,------------------------------------------------,
   | Esc  |   1  |   2  |   3  |   4  |   5  | BKSPC|	| PGUP |   6  |   7  |  8   |   9  |   0  | BKSPC|
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   | Tab  |   Q  |   W  |   E  |   R  |   T  |   	  | | VOL+ |   Y  |   U  |   I  |   O  |   P  |  Del |
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   |  |\  |   A  |   S  |   D  |   F  |   G  |    	| | VOL- |   H  |   J  |   K  |   L  |  ;:  |  "'  |
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   | Shift|   Z  |   X  |   C  |   V  |   B  |    	| | PGDWN|   N  |   M  |  <,  |  >.  |  ?/  | ENTER|
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   | Ctrl | Home | End  |  ALT | MO(1)| Spce | ENTER| | ENTER| Spce |  -_  |  +=  |  {[  |  }]  |  ~`  |
   `------------------------------------------------`	`------------------------------------------------`

	_LOWER
   ,------------------------------------------------,	,------------------------------------------------,
   |      |  F1  |  F2  |  F3  |  F4  |  F5  |MACRO1| |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   |      |      |  UP   |     |      |      |  W_S |	|      |      |      |      |      |      |      |
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   |      | LEFT | DOWN | RIGHT|      |      |MACRO2|	|      |      |      |      |      |      |      |
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   |CAPLK |      |      |      |      |      | R_G_S|	|      |      |      |      |      |      |      |
   |------+------+------+------+------+------+------|	|------+------+------+------+------+------+------|
   |      |      |      |      | LOWER|      | C_D_T|	|      |      |      |      |      |      |      |
   `------------------------------------------------`	`------------------------------------------------`
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
		KC_ESC,  KC_1,    KC_2,   KC_3,    KC_4,  KC_5,   KC_BSPC,                KC_PGUP, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
		KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,  KC_T,   KC_NO,                  KC_VOLU, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
		KC_BSLS, KC_A,    KC_S,   KC_D,    KC_F,  KC_G,   KC_NO,                  KC_VOLD, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
		KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,   KC_NO,                  KC_PGDN, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, 
		KC_LCTL, KC_HOME, KC_END, KC_LALT, LOWER, KC_SPC, KC_ENT,                 KC_ENT,  KC_SPC, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_GRV),
	[_LOWER] = LAYOUT(
		KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, MACRO1,               KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
		KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO, WIN_SNIP,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, 
		KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO, MACRO2,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, 
		KC_CAPS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, RIDER_GLOBAL_SEARCH,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, 
		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO, CHROME_DEV_TOOLS,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO)
};

bool execute_macro2 = false;

void matrix_init_user(void) { }

void matrix_scan_user(void) {
	if (execute_macro2) {
    tap_code(KC_MS_UP);
    tap_code(KC_MS_DOWN);
    tap_code(KC_MS_LEFT);
    tap_code(KC_MS_RIGHT);
    tap_code(KC_MS_WH_UP);
    tap_code(KC_MS_WH_DOWN);
  }
  else { }
}

void send_git_status(void) {
	SEND_STRING("git status");
  _delay_ms(100);
  SEND_STRING(SS_TAP(X_ENTER));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case MACRO1:
      if (record->event.pressed) {
        send_git_status();
      }
      return false;
      break;
    case MACRO2: 
      if (record->event.pressed) {
        execute_macro2 = !execute_macro2;
      }
      return false;
      break;
	}

  return true;
};
