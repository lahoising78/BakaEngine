#ifndef _BAKA_KEYCODES_H_
#define _BAKA_KEYCODES_H_

namespace baka
{

typedef int BakaKeycode;

/* these values were taken from SDL2 scancodes */
#define BAKA_KEYCODE_UNKNOWN 0
#define BAKA_KEYCODE_A 4
#define BAKA_KEYCODE_B 5
#define BAKA_KEYCODE_C 6
#define BAKA_KEYCODE_D 7
#define BAKA_KEYCODE_E 8
#define BAKA_KEYCODE_F 9
#define BAKA_KEYCODE_G 10
#define BAKA_KEYCODE_H 11
#define BAKA_KEYCODE_I 12
#define BAKA_KEYCODE_J 13
#define BAKA_KEYCODE_K 14
#define BAKA_KEYCODE_L 15
#define BAKA_KEYCODE_M 16
#define BAKA_KEYCODE_N 17
#define BAKA_KEYCODE_O 18
#define BAKA_KEYCODE_P 19
#define BAKA_KEYCODE_Q 20
#define BAKA_KEYCODE_R 21
#define BAKA_KEYCODE_S 22
#define BAKA_KEYCODE_T 23
#define BAKA_KEYCODE_U 24
#define BAKA_KEYCODE_V 25
#define BAKA_KEYCODE_W 26
#define BAKA_KEYCODE_X 27
#define BAKA_KEYCODE_Y 28
#define BAKA_KEYCODE_Z 29

#define BAKA_KEYCODE_1 30
#define BAKA_KEYCODE_2 31
#define BAKA_KEYCODE_3 32
#define BAKA_KEYCODE_4 33
#define BAKA_KEYCODE_5 34
#define BAKA_KEYCODE_6 35
#define BAKA_KEYCODE_7 36
#define BAKA_KEYCODE_8 37
#define BAKA_KEYCODE_9 38
#define BAKA_KEYCODE_0 39

#define BAKA_KEYCODE_RETURN 40
#define BAKA_KEYCODE_ESCAPE 41
#define BAKA_KEYCODE_BACKSPACE 42
#define BAKA_KEYCODE_TAB 43
#define BAKA_KEYCODE_SPACE 44

#define BAKA_KEYCODE_MINUS 45
#define BAKA_KEYCODE_EQUALS 46
#define BAKA_KEYCODE_LEFTBRACKET 47
#define BAKA_KEYCODE_RIGHTBRACKET 48
#define BAKA_KEYCODE_BACKSLASH 49 
#define BAKA_KEYCODE_NONUSHASH 50 
#define BAKA_KEYCODE_SEMICOLON 51
#define BAKA_KEYCODE_APOSTROPHE 52
#define BAKA_KEYCODE_GRAVE 53 
#define BAKA_KEYCODE_COMMA 54
#define BAKA_KEYCODE_PERIOD 55
#define BAKA_KEYCODE_SLASH 56

#define BAKA_KEYCODE_CAPSLOCK 57

#define BAKA_KEYCODE_F1 58
#define BAKA_KEYCODE_F2 59
#define BAKA_KEYCODE_F3 60
#define BAKA_KEYCODE_F4 61
#define BAKA_KEYCODE_F5 62
#define BAKA_KEYCODE_F6 63
#define BAKA_KEYCODE_F7 64
#define BAKA_KEYCODE_F8 65
#define BAKA_KEYCODE_F9 66
#define BAKA_KEYCODE_F10 67
#define BAKA_KEYCODE_F11 68
#define BAKA_KEYCODE_F12 69

#define BAKA_KEYCODE_PRINTSCREEN 70
#define BAKA_KEYCODE_SCROLLLOCK 71
#define BAKA_KEYCODE_PAUSE 72
#define BAKA_KEYCODE_INSERT 73 

#define BAKA_KEYCODE_HOME 74
#define BAKA_KEYCODE_PAGEUP 75
#define BAKA_KEYCODE_DELETE 76
#define BAKA_KEYCODE_END 77
#define BAKA_KEYCODE_PAGEDOWN 78
#define BAKA_KEYCODE_RIGHT 79
#define BAKA_KEYCODE_LEFT 80
#define BAKA_KEYCODE_DOWN 81
#define BAKA_KEYCODE_UP 82

#define BAKA_KEYCODE_NUMLOCKCLEAR 83

#define BAKA_KEYCODE_KP_DIVIDE 84
#define BAKA_KEYCODE_KP_MULTIPLY 85
#define BAKA_KEYCODE_KP_MINUS 86
#define BAKA_KEYCODE_KP_PLUS 87
#define BAKA_KEYCODE_KP_ENTER 88
#define BAKA_KEYCODE_KP_1 89
#define BAKA_KEYCODE_KP_2 90
#define BAKA_KEYCODE_KP_3 91
#define BAKA_KEYCODE_KP_4 92
#define BAKA_KEYCODE_KP_5 93
#define BAKA_KEYCODE_KP_6 94
#define BAKA_KEYCODE_KP_7 95
#define BAKA_KEYCODE_KP_8 96
#define BAKA_KEYCODE_KP_9 97
#define BAKA_KEYCODE_KP_0 98
#define BAKA_KEYCODE_KP_PERIOD 99

#define BAKA_KEYCODE_NONUSBACKSLASH 100 

#define BAKA_KEYCODE_APPLICATION 101 
#define BAKA_KEYCODE_POWER 102 

#define BAKA_KEYCODE_KP_EQUALS 103
#define BAKA_KEYCODE_F13 104
#define BAKA_KEYCODE_F14 105
#define BAKA_KEYCODE_F15 106
#define BAKA_KEYCODE_F16 107
#define BAKA_KEYCODE_F17 108
#define BAKA_KEYCODE_F18 109
#define BAKA_KEYCODE_F19 110
#define BAKA_KEYCODE_F20 111
#define BAKA_KEYCODE_F21 112
#define BAKA_KEYCODE_F22 113
#define BAKA_KEYCODE_F23 114
#define BAKA_KEYCODE_F24 115
#define BAKA_KEYCODE_EXECUTE 116
#define BAKA_KEYCODE_HELP 117
#define BAKA_KEYCODE_MENU 118
#define BAKA_KEYCODE_SELECT 119
#define BAKA_KEYCODE_STOP 120
#define BAKA_KEYCODE_AGAIN 121
#define BAKA_KEYCODE_UNDO 122
#define BAKA_KEYCODE_CUT 123
#define BAKA_KEYCODE_COPY 124
#define BAKA_KEYCODE_PASTE 125
#define BAKA_KEYCODE_FIND 126
#define BAKA_KEYCODE_MUTE 127
#define BAKA_KEYCODE_VOLUMEUP 128
#define BAKA_KEYCODE_VOLUMEDOWN 129

#define BAKA_KEYCODE_KP_COMMA 133
#define BAKA_KEYCODE_KP_EQUALSAS400 134

#define BAKA_KEYCODE_INTERNATIONAL1 135 

#define BAKA_KEYCODE_INTERNATIONAL2 136
#define BAKA_KEYCODE_INTERNATIONAL3 137 
#define BAKA_KEYCODE_INTERNATIONAL4 138
#define BAKA_KEYCODE_INTERNATIONAL5 139
#define BAKA_KEYCODE_INTERNATIONAL6 140
#define BAKA_KEYCODE_INTERNATIONAL7 141
#define BAKA_KEYCODE_INTERNATIONAL8 142
#define BAKA_KEYCODE_INTERNATIONAL9 143
#define BAKA_KEYCODE_LANG1 144 
#define BAKA_KEYCODE_LANG2 145 
#define BAKA_KEYCODE_LANG3 146 
#define BAKA_KEYCODE_LANG4 147 
#define BAKA_KEYCODE_LANG5 148 
#define BAKA_KEYCODE_LANG6 149 
#define BAKA_KEYCODE_LANG7 150 
#define BAKA_KEYCODE_LANG8 151 
#define BAKA_KEYCODE_LANG9 152 

#define BAKA_KEYCODE_ALTERASE 153 
#define BAKA_KEYCODE_SYSREQ 154
#define BAKA_KEYCODE_CANCEL 155
#define BAKA_KEYCODE_CLEAR 156
#define BAKA_KEYCODE_PRIOR 157
#define BAKA_KEYCODE_RETURN2 158
#define BAKA_KEYCODE_SEPARATOR 159
#define BAKA_KEYCODE_OUT 160
#define BAKA_KEYCODE_OPER 161
#define BAKA_KEYCODE_CLEARAGAIN 162
#define BAKA_KEYCODE_CRSEL 163
#define BAKA_KEYCODE_EXSEL 164

#define BAKA_KEYCODE_KP_00 176
#define BAKA_KEYCODE_KP_000 177
#define BAKA_KEYCODE_THOUSANDSSEPARATOR 178
#define BAKA_KEYCODE_DECIMALSEPARATOR 179
#define BAKA_KEYCODE_CURRENCYUNIT 180
#define BAKA_KEYCODE_CURRENCYSUBUNIT 181
#define BAKA_KEYCODE_KP_LEFTPAREN 182
#define BAKA_KEYCODE_KP_RIGHTPAREN 183
#define BAKA_KEYCODE_KP_LEFTBRACE 184
#define BAKA_KEYCODE_KP_RIGHTBRACE 185
#define BAKA_KEYCODE_KP_TAB 186
#define BAKA_KEYCODE_KP_BACKSPACE 187
#define BAKA_KEYCODE_KP_A 188
#define BAKA_KEYCODE_KP_B 189
#define BAKA_KEYCODE_KP_C 190
#define BAKA_KEYCODE_KP_D 191
#define BAKA_KEYCODE_KP_E 192
#define BAKA_KEYCODE_KP_F 193
#define BAKA_KEYCODE_KP_XOR 194
#define BAKA_KEYCODE_KP_POWER 195
#define BAKA_KEYCODE_KP_PERCENT 196
#define BAKA_KEYCODE_KP_LESS 197
#define BAKA_KEYCODE_KP_GREATER 198
#define BAKA_KEYCODE_KP_AMPERSAND 199
#define BAKA_KEYCODE_KP_DBLAMPERSAND 200
#define BAKA_KEYCODE_KP_VERTICALBAR 201
#define BAKA_KEYCODE_KP_DBLVERTICALBAR 202
#define BAKA_KEYCODE_KP_COLON 203
#define BAKA_KEYCODE_KP_HASH 204
#define BAKA_KEYCODE_KP_SPACE 205
#define BAKA_KEYCODE_KP_AT 206
#define BAKA_KEYCODE_KP_EXCLAM 207
#define BAKA_KEYCODE_KP_MEMSTORE 208
#define BAKA_KEYCODE_KP_MEMRECALL 209
#define BAKA_KEYCODE_KP_MEMCLEAR 210
#define BAKA_KEYCODE_KP_MEMADD 211
#define BAKA_KEYCODE_KP_MEMSUBTRACT 212
#define BAKA_KEYCODE_KP_MEMMULTIPLY 213
#define BAKA_KEYCODE_KP_MEMDIVIDE 214
#define BAKA_KEYCODE_KP_PLUSMINUS 215
#define BAKA_KEYCODE_KP_CLEAR 216
#define BAKA_KEYCODE_KP_CLEARENTRY 217
#define BAKA_KEYCODE_KP_BINARY 218
#define BAKA_KEYCODE_KP_OCTAL 219
#define BAKA_KEYCODE_KP_DECIMAL 220
#define BAKA_KEYCODE_KP_HEXADECIMAL 221

#define BAKA_KEYCODE_LCTRL 224
#define BAKA_KEYCODE_LSHIFT 225
#define BAKA_KEYCODE_LALT 226 
#define BAKA_KEYCODE_LGUI 227 
#define BAKA_KEYCODE_RCTRL 228
#define BAKA_KEYCODE_RSHIFT 229
#define BAKA_KEYCODE_RALT 230 
#define BAKA_KEYCODE_RGUI 231 

#define BAKA_KEYCODE_MODE 257    

#define BAKA_KEYCODE_AUDIONEXT 258
#define BAKA_KEYCODE_AUDIOPREV 259
#define BAKA_KEYCODE_AUDIOSTOP 260
#define BAKA_KEYCODE_AUDIOPLAY 261
#define BAKA_KEYCODE_AUDIOMUTE 262
#define BAKA_KEYCODE_MEDIASELECT 263
#define BAKA_KEYCODE_WWW 264
#define BAKA_KEYCODE_MAIL 265
#define BAKA_KEYCODE_CALCULATOR 266
#define BAKA_KEYCODE_COMPUTER 267
#define BAKA_KEYCODE_AC_SEARCH 268
#define BAKA_KEYCODE_AC_HOME 269
#define BAKA_KEYCODE_AC_BACK 270
#define BAKA_KEYCODE_AC_FORWARD 271
#define BAKA_KEYCODE_AC_STOP 272
#define BAKA_KEYCODE_AC_REFRESH 273
#define BAKA_KEYCODE_AC_BOOKMARKS 274

#define BAKA_KEYCODE_BRIGHTNESSDOWN 275
#define BAKA_KEYCODE_BRIGHTNESSUP 276
#define BAKA_KEYCODE_DISPLAYSWITCH 277 

#define BAKA_KEYCODE_KBDILLUMTOGGLE 278
#define BAKA_KEYCODE_KBDILLUMDOWN 279
#define BAKA_KEYCODE_KBDILLUMUP 280
#define BAKA_KEYCODE_EJECT 281
#define BAKA_KEYCODE_SLEEP 282

#define BAKA_KEYCODE_APP1 283
#define BAKA_KEYCODE_APP2 284

#define BAKA_KEYCODE_AUDIOREWIND 285
#define BAKA_KEYCODE_AUDIOFASTFORWARD 286

#define BAKA_KEYCODES_NUM 512

}

#endif