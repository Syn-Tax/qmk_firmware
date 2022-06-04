#include QMK_KEYBOARD_H


#define _DVORAK 0
#define _GAMING 1
#define _RAISE 2
#define _LOWER 3

// Fillers to make layering more clear

#define ____ KC_TRNS
#define XXXX KC_NO

// Mod Tap
#define ALT_ESC  ALT_T(KC_ESC)

// Home row mods
#define SFT_U LSFT_T(KC_U)
#define CTL_E LCTL_T(KC_E)

#define SFT_H LSFT_T(KC_H)
#define CTRL_T LCTL_T(KC_T)

// Mod keys
#define SFT_INS  LSFT(KC_INS)

// Mouse keys
#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN2

#define DVORAK DF(_DVORAK)
#define GAMING DF(_GAMING)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DVORAK
 * ,----------------------------------,                             ,----------------------------------,
 * |   '  |   ,  |   .  |   p  |   y  |                             |   f  |   g  |   c  |   r  |   l  |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |   a  |   o  |   e  |   u  |   i  |                             |   d  |   h  |   t  |   n  |   s  |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |   ;  |   q  |   j  |   k  |   x  |                             |   b  |   m  |   w  |   v  |   z  |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |  [   |   ]  |                                                         |   (  |   )  |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      | ESC  |  BS  |                             | SPACE|ENTER |
 *                      |      |      |                             |      |      |
 *                      | ALT  |      |                             |      |      |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    | GUI  | SHIFT| | LOWER| RAISE|
 *                                    '------+------' '------+------'
 *                                    | =    |  CTRL| | /    | TAB  |
 *                                    '------+------' '------+------'
 */

[_DVORAK] = LAYOUT( \
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                                       KC_F, KC_G,    KC_C,    KC_R,   KC_L,    \
  KC_A,    KC_O,    CTL_E,    SFT_U,    KC_I,                                       KC_D, SFT_H,    CTRL_T,    KC_N,   KC_S, \
  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                                       KC_B, KC_M,    KC_W,    KC_V,   KC_Z, \
              KC_LBRC, KC_RBRC,                                                   KC_LPRN, KC_RPRN,                   \
                                      ALT_ESC, KC_BSPC,   KC_SPC,  KC_ENT,                                          \
                                      KC_LSFT, KC_LGUI  ,   RAISE, LOWER,                                           \
                                      KC_LCTL,   KC_EQL,  KC_TAB,  KC_SLSH
),

/* GAMING
 * ,----------------------------------,                             ,----------------------------------,
 * |      |      |   w  |      |      |                             |   f  |   g  |   c  |   r  |   l  |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |      |   a  |   s  |   d  |      |                             |   d  |   h  |   t  |   n  |   s  |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |      |      |      |      |      |                             |   b  |   m  |   w  |   v  |   z  |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |  [   |   ]  |                                                         |   (  |   )  |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      | ESC  | SPACE|                             | SPACE|ENTER |
 *                      |      |      |                             |      |      |
 *                      | ALT  |      |                             |      |      |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    | GUI  | SHIFT| | LOWER| RAISE|
 *                                    '------+------' '------+------'
 *                                    | =    |  CTRL| | /    | TAB  |
 *                                    '------+------' '------+------'
 */

[_GAMING] = LAYOUT( \
  ____,    ____,    KC_W,    ____,    ____,                                       KC_F, KC_G,    KC_C,    KC_R,   KC_L,    \
  ____,    KC_A,    KC_S,    KC_D,    ____,                                       KC_D, KC_H,    KC_T,    KC_N,   KC_S, \
  ____,    ____,    ____,    ____,    ____,                                       KC_B, KC_M,    KC_W,    KC_V,   KC_Z, \
              KC_LBRC, KC_RBRC,                                                   KC_LPRN, KC_RPRN,                   \
                                      ALT_ESC, KC_SPC,   KC_SPC,  KC_ENT,                                          \
                                      KC_LSFT, KC_LGUI  ,   RAISE, LOWER,                                           \
                                      KC_LCTL,   KC_EQL,  KC_TAB,  KC_SLSH
),

/* Raise
 * ,------------------------------------,                             ,----------------------------------,
 * | F1   | F2   | F3   | F4    | F5    |                             | VOL+ |      |      |      |      |
 * |------+------+------+-------+-------|                             |------+------+------+------+------|
 * | F6   | F7   | F8   | F9    | F10   |                             | left | down | up   | right|      |
 * |------+------+------+-------+-------|                             |------+------+------+------+------|
 * | F11  | F12  | F13  | F14   | F15   |                             | VOL- |      |      |      |      |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |DVORAK|GAMING|                                                         |      |      |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      |      |      |                             |      |      |
 *                      |      |      |                             |      |      |
 *                      |      |      |                             |      |      |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    |      |      | |      |      |
 *                                    '------+------' '------+------'
 *                                    |      | RESET| | RESET|      |
 *                                    '------+------' '------+------'
 */

[_RAISE] = LAYOUT( \
  KC_F1,  KC_F2,  KC_F3,     KC_F4,  KC_F5,                          ____,    ____,    ____,    ____,  ____,   \
  KC_F6,  KC_F7,  KC_F8,     KC_F9,  KC_F10,                         KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,  ____, \
  KC_F11, KC_F12, KC_F13,    KC_F14, KC_F15,                        ____,    ____,    ____,    ____,  ____,      \
        DVORAK,  GAMING,                                                            ____,    ____,              \
                                   ____, ____,  ____, ____,                                                 \
                                   ____, ____,  ____, ____,                                                 \
                                   RESET,____,  ____, RESET                                                  \
),
/* Lower
 * ,----------------------------------,                             ,----------------------------------,
 * |      | &    | *    |SFTINS| \    |                             |      |  7   |  8   |  9   |      |
 * |------+------+------+------+------|                             |------+------+------+------+------|
 * |      | $    | %    | ^    | |    |                             |      |  4   |  8   |  9   |      |
 * |------+------+------+------+------|                             |------+------+------+------+------|
 * |      | !    | @    | #    | ~    |                             | 0    |  1   |  2   |  3   |      |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        | ~    | -    |                                                         |      |      |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      |      |      |                             |      |      |
 *                      |      |      |                             |      |      |
 *                      |      |      |                             |      |      |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    |      |      | |      |      |
 *                                    '------+------' '------+------'
 *                                    |      |      | |      |      |
 *                                    '------+------' '------+------'
 */

[_LOWER] = LAYOUT( \
  ____,    KC_AMPR,KC_ASTR, SFT_INS, KC_BSLS,                       ____,    KC_7,     KC_8,    KC_9,    ____,  \
  ____,    KC_DLR, KC_PERC, KC_CIRC, KC_PIPE,                       ____,    KC_4,     KC_5,    KC_6,    ____,    \
  ____,    KC_EXLM, KC_AT,  KC_HASH, ____,                          KC_0,    KC_1,     KC_2,    KC_3,    ____, \
           KC_GRV, KC_MINS,                                                               ____,    ____,             \
                                             ____, ____,  ____, ____,                                               \
                                             ____, ____,  ____, ____,                                               \
                                             ____, ____,  ____, ____                                                \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
