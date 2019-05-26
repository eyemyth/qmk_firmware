/* Copyright 2019 Jay Thompson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "lenovo_t420.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
         KC__MUTE, KC__VOLDOWN, KC__VOLUP, KC_MEDIA_PLAY_PAUSE, KC_ESC,    KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,      KC_HOME, KC_PGUP,
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC, KC_END, KC_PGDN,
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS,   KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,    KC_ENT,
    KC_LSFT,     KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPACE,          KC_RALT, KC_APP, KC_RCTL,
                                                           KC_WBAK, KC_UP, KC_WFWD,
                                                           KC_LEFT, KC_DOWN, KC_RIGHT
  ),
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}


/* Qwerty
 * ,------------------------------------------------------------------------------------ -------------.
 * |      |  MUTE|   VDN|   VUP|   MIC|   THV|   PWR|PRNTSC|SCRLOK| PAUSE|INSERT|      |  HOME | PGUP |
 * |      |---------------------------------------------------------------------| DEL  |- ------------|
 * | Esc  |   F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F8 |   F9 |   10|   F11|      |  END  | PGDN |
 * |------+------+------+------+------+-------------+------+------+------+------+------+ ------+------|
 * | ~    |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | -    |  =    | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------+ ------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | [    | ]     | |    |
 * |------+------+------+------+------+-------------+------+------+------+------+------+ ------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |  Return      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+ ------+------|
 * | Shift       |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift        |
 * |------+------+------+------+------+------+------+------+------+------+------+------+ ------+------|
 * | Fn   | Ctrl | Alt  | GUI  |           Space                  | GUI  | Alt  | Ctrl |              |
 * |------+------+------+------+------+------+------+------+------+------+------+------+ ------+------|
 * |                                                                            |      | Up    |      |
 * |                                                                            +------+ ------+------|
 * |                                                                            | Left | Down  | Right|
 * `------------------------------------------------------------------------------------ -------------'
 */
/* need keyboards/lenovo_t420/lenovo_t420.h before this can really happen */
