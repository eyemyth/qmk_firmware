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
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 * DOCS: https://docs.qmk.fm/#/hardware_avr?id=ltkeyboardgth
 */

#define LAYOUT( \
            k31,k71, k41, k12, k52,              k20, k40, k10, k62,      k60, k61,                                 \
    k54,  k6d, k68, k76, k55, k57,  k59, k73, k65, k6a, k2a, k24, k23,   k63, k21, k22,                             \
    k66, k27,  k2d, k28,  k29, k69,  k6b, k2b,  k2c, k26,  k25, k64, k6c,     k78,                                  \
    k74,    k44, k49,  k45, k46,  k77, k79,  k47, k48,   k43, k42, k72, k7a,   k37,                                 \
    k7b,     k34, k3a,  k35, k36,  k56,  k58, k38,  k39, k33,  k32, k53,    k19,                                    \
    k75,       k14,  k1c, k17,  k18, k06,   k08, k1a,  k1b, k13,  k05,     k15,                                     \
         k67,  k70, k50,             k07,              k00, k30, k16,                                               \
                                                                        k11, k51, k02,                              \
                                                                        k01, k04, k03                               \
) {                                                                                                                 \
    { k00,   k01,   k02,   k03,   k04, k05,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k06, k07,   k08, KC_NO, KC_NO },   \
    { KC_NO, k10,   k11,   KC_NO, k12, KC_NO, k13,   k14,   k15,   k16,   k17,   k18, k19,   k1a, k1b,   k1c },     \
    { k20,   k21,   k22,   k23,   k24, k25,   k26,   k27,   KC_NO, KC_NO, k28,   k29, k2a,   k2b, k2c,   k2d },     \
    { KC_NO, KC_NO, k30,   KC_NO, k31, k32,   k33,   k34,   KC_NO, KC_NO, k35,   k36, k37,   k38, k39,   k3a },     \
    { k40,   KC_NO, KC_NO, KC_NO, k41, k42,   k43,   k44,   KC_NO, KC_NO, k45,   k46, KC_NO, k47, k48,   k49 },     \
    { k50,   k51,   KC_NO, KC_NO, k52, k53,   KC_NO, k54,   KC_NO, KC_NO, k55,   k56, k57,   k58, k59,   KC_NO },   \
    { KC_NO, k60,   k61,   k62,   k63, k64,   k65,   k66,   KC_NO, k67,   k68,   k69, k6a,   k6b, k6c,   k6d },     \
    { KC_NO, KC_NO, KC_NO, k70,   k71, k72,   k73,   k74,   k75,   KC_NO, k76,   k77, k78,   k79, k7a,   k7b },     \
}


/*        [1        2     3      4       5       6    7    20   21   22   24   25  26     31  32  33]  */
/* 8     { RALT     LEFT  DOCR   RIGHT   DOWN    /    xxx  xxx  xxx  xxx  xxx  B   SPACE  N   xxx xxx  }  0 \ */
/* 9     { xxx      PAUSE DOCL   xxx     PLAY    xxx  .    Z    RSH  RCL  C    V   ENTER  M   ,   X    }  1 \ */
/* 10    { PRINTSC  END   PDOWN  F12     F11     0    9    1    xxx  xxx  3    4   F10    7   8   2    }  2 \ */
/* 11    { xxx      xxx   MENU   xxx     MUTE    ;    L    A    xxx  xxx  D    F   \      J   K   S    }  3 \ */
/* 12    { NUML     xxx   xxx    xxx     VOLUP   P    O    Q    xxx  xxx  E    R   xxx    U   I   W    }  4 \ */
/* 15    { LALT     UP    xxx    xxx     THINK   '    xxx  ESC  xxx  xxx  F4   G   F5     H   F6  xxx  }  5 \ */
/* 16    { xxx      HOME  PUP    INSERT  DELETE  -    F8   ~    xxx  LCL  F2   5   f9     6   =   F1   }  6 \ */
/* 17    { xxx      xxx   xxx    GUI     VolDN   [    F7   TAB  LSH  xxx  F3   T   BCKSP  Y   ]   CAPS }  7 \ */
/*         0        1     2      3       4       5    6    7    8    9    a    b   c      d   e   f */


/* Qwerty
 * ,------------------------------------------------------------------------------------ -------------.
 * |      |  MUTE|   VDN|   VUP|   MIC|   THV|   PWR|PRNTSC|SCRLOK| PAUSE|INSERT|      |  HOME | PGUP |
 * |      |---------------------------------------------------------------------| DEL  |- ------------|
 * | Esc  |   F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F8 |   F9 |   F10|   F11|      |  END  | PGDN |
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
