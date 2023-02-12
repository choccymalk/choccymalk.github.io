/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - game_controller.h                                       *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2014 Bobby Smiles                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef M64P_SI_GAME_CONTROLLER_H
#define M64P_SI_GAME_CONTROLLER_H

#include <stdint.h>
#include <stddef.h>

#include "mempak.h"
#include "rumblepak.h"
#include "transferpak.h"

enum pak_type
{
    PAK_NONE,
    PAK_MEM,
    PAK_RUMBLE,
    PAK_TRANSFER
};

enum cont_type
{
    CONT_NONE = 0,
    CONT_JOYPAD = 1,
    CONT_MOUSE = 2
};

struct game_controller
{
    /* external controller input */
    void* user_data;
    int (*is_connected)(void*,enum pak_type*);
    uint32_t (*get_input)(void*);

    struct mempak mempak;
    struct rumblepak rumblepak;
    struct transferpak transferpak;
};

void init_game_controller(struct game_controller *cont,
      void *cont_user_data,
      int (*cont_is_connected)(void*,enum pak_type*),
      uint32_t (*cont_get_input)(void*),
      void* mpk_user_data,
      void (*mpk_save)(void*),
      uint8_t* mpk_data,
      void* rpk_user_data,
      void (*rpk_rumble)(void*,enum rumble_action));

int game_controller_is_connected(struct game_controller* cont, enum pak_type* pak);
uint32_t game_controller_get_input(struct game_controller* cont);

void process_controller_command(struct game_controller* cont, uint8_t* cmd);
void read_controller(struct game_controller* cont, uint8_t* cmd);

#endif