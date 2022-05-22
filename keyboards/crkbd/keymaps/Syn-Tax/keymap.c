/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdio.h>

// Layer definitions

#define _DVORAK 0
#define _STENO 1
#define _RAISE 2
#define _LOWER 3
#define _ADJUST 4

#define DVORAK DF(_DVORAK)
#define STENO DF(_STENO)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define ADJUST DF(_ADJUST)

// Filler

#define ____ KC_TRNS
#define XXXX KC_NO

// Mod Tap

#define ALT_ESC ALT_T(KC_ESC)
#define CTL_ENT CTL_T(KC_ENT)
#define CTL_BSPC LCTL(KC_BSPC)

// Mouse Keys

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN2
#define KC_MB3 KC_MS_BTN3

// Tap dance definitions
typedef struct {
    bool is_press_action;
    int  state;
} tap;

enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5, // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7
};

// Tap dance enums
enum {
CTL_BSP = 0,
PRN = 1,
BRC = 2
};

int cur_dance(qk_tap_dance_state_t *state);

// for the x tap dance. Put it here so it can be used in any keymap
// CTRL_BSPC
void ctl_bspc_finished(qk_tap_dance_state_t *state, void *user_data);
void ctl_bspc_reset(qk_tap_dance_state_t *state, void *user_data);

// Paren
void paren_finished(qk_tap_dance_state_t *state, void *user_data);
void paren_reset(qk_tap_dance_state_t *state, void *user_data);

// Brackets
void bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void bracket_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* DVORAK
      ,-----------------------------------------------------.                    ,-----------------------------------------------------.
      |  /     |   '    |   ,    |   .    |   p    |   y    |                    |   f    |   g    |   c    |   r    |   l    |    =   |
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      |  GUI   |   a    |   o    |   e    |   u    |   i    |                    |   d    |   h    |   t    |   n    |   s    |    [   |
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      | SHIFT  |   ;    |   q    |   j    |   k    |   x    |                    |   b    |   m    |   w    |   v    |   z    |    (   |
      |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          | RAISE  |   ESC  |   BS   |  | SPACE  | ENTER  | LOWER  |
                                          |        |        |        |  |        |        |        |
                                          |        |   ALT  |        |  |        |  CTRL  |        |
                                          `--------------------------'  `--------------------------'
    */
[_DVORAK] = LAYOUT_split_3x6_3(
    XXXX,    KC_QUOT, KC_COMMM, KC_DOT, KC_P, KC_Y,                                   KC_F,  KC_G,  KC_C,  KC_R,  KC_L,  KC_SLSH, \
    KC_LGUI, KC_A,    KC_O,     KC_E,   KC_U, KC_I,                                   KC_D,  KC_H,  KC_T,  KC_N,  KC_S,  KC_EQL, \
    KC_LSFT, KC_SCLN, KC_Q,     KC_J,   KC_K, KC_X,                                   KC_B,  KC_M,  KC_W,  KC_V,  KC_Z,  KC_LPRN, \
                                 RAISE, ALT_ESC, KC_BSPC,               KC_SPC, CTL_ENT, LOWER

                                   ),
/*
    [1] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, _______, KC_SPC, KC_ENT, MO(3), KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [2] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, MO(3), KC_SPC, KC_ENT, _______, KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [3] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, _______, KC_SPC, KC_ENT, _______, KC_RALT
        //`--------------------------'  `--------------------------'
        )
        */
        };

int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8; // magic number. At some point this method will expand to work for more presses
}

// instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {.is_press_action = true, .state = 0};


// CTRL BSPC
void ctl_bspc_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_BSPC); break;
        case SINGLE_HOLD: register_code(CTL_BSPC); break;
        case DOUBLE_TAP: register_code(KC_BSPC); break;
        case DOUBLE_HOLD: register_code(CTL_BSPC); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_BSPC); unregister_code(KC_BSPC); register_code(KC_BSPC);
            // Last case is for fast typing. Assuming your key is `f`:
            // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
            // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void ctl_bspc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_BSPC); break;
        case SINGLE_HOLD: unregister_code(CTL_BSPC); break;
        case DOUBLE_TAP: unregister_code(KC_BSPC); break;
        case DOUBLE_HOLD: unregister_code(CTL_BSPC);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_BSPC);
    }
    xtap_state.state = 0;
}


// PAREN
void paren_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LPRN); break;
        case SINGLE_HOLD: register_code(KC_LPRN); break;
        case DOUBLE_TAP: register_code(KC_RPRN); break;
        case DOUBLE_HOLD: register_code(KC_RPRN); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_LPRN); unregister_code(KC_LPRN); register_code(KC_LPRN);
            // Last case is for fast typing. Assuming your key is `f`:
            // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
            // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void paren_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LPRN); break;
        case SINGLE_HOLD: unregister_code(KC_LPRN); break;
        case DOUBLE_TAP: unregister_code(KC_RPRN); break;
        case DOUBLE_HOLD: unregister_code(KC_RPRN);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_LPRN);
    }
    xtap_state.state = 0;
}


// BRACKET
void bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LBRC); break;
        case SINGLE_HOLD: register_code(KC_LBRC); break;
        case DOUBLE_TAP: register_code(KC_RBRC); break;
        case DOUBLE_HOLD: register_code(KC_RBRC); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_LBRC); unregister_code(KC_LBRC); register_code(KC_LBRC);
            // Last case is for fast typing. Assuming your key is `f`:
            // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
            // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_RBRC); break;
        case DOUBLE_HOLD: unregister_code(KC_RBRC);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_LBRC);
    }
    xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CTL_BSP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_bspc_finished, ctl_bspc_reset),
    [PRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren_finished, paren_reset),
    [BRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bracket_finished, bracket_reset)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST | L_LOWER:
        case L_ADJUST | L_RAISE:
        case L_ADJUST | L_LOWER | L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}
#endif // OLED_ENABLE
