#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_map_cell_info.h"

#include "bn_regular_bg_items_bg.h"
#include "bn_regular_bg_items_borders.h"
#include "bn_sprite_items_spaceship.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"


// find what map cell player is in based on current player coords
int getCurrentMapCellX(int x)
    {
        return (x + 128) / 8;
    }

int getCurrentMapCellY(int y)
    {
        return (y + 128) / 8;
    }

int main()
{
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0,0);
    bg.set_priority(1);
    bn::regular_bg_ptr borders = bn::regular_bg_items::borders.create_bg(0,0);
    borders.set_priority(0);
    bn::sprite_ptr spaceship = bn::sprite_items::spaceship.create_sprite(0, 0);
    spaceship.set_bg_priority(0);
    bn::point spaceship_map_position(16, 16);

    const bn::regular_bg_map_item& borders_item = bn::regular_bg_items::borders.map_item();
    bn::regular_bg_map_cell valid_map_cell = borders_item.cell(0, 0);
    int valid_tile_index = bn::regular_bg_map_cell_info(valid_map_cell).tile_index();

    while(true)
    {
        // initialize new map position
        bn::point new_spaceship_map_position = spaceship_map_position;

        // basic movement keys
        if (bn::keypad::up_held() && new_spaceship_map_position.y() > -72)
        {
            new_spaceship_map_position.set_y(new_spaceship_map_position.y() - 1);
        }
        else if (bn::keypad::down_held() && new_spaceship_map_position.y() < 72)
        {
            new_spaceship_map_position.set_y(new_spaceship_map_position.y() + 1);
        }
        if (bn::keypad::left_held() && new_spaceship_map_position.x() > -112)
        {
            new_spaceship_map_position.set_x(new_spaceship_map_position.x() - 1);
        }
        else if (bn::keypad::right_held() && new_spaceship_map_position.x() < 112)
        {
            new_spaceship_map_position.set_x(new_spaceship_map_position.x() + 1);
        }

        // find the player's current map cell using the functions defined above
        bn::regular_bg_map_cell current_cell = borders_item.cell(getCurrentMapCellX(new_spaceship_map_position.x()), getCurrentMapCellY(new_spaceship_map_position.y()));

        // grab the current cell's tile index
        int spaceship_tile_index = bn::regular_bg_map_cell_info(current_cell).tile_index();

        //compare if current tile index is valid (aka you can move there)
        if(spaceship_tile_index == valid_tile_index)
        {
            spaceship_map_position = new_spaceship_map_position;
        }        

        //draw spaceship on screen
        spaceship.set_position(spaceship_map_position);

        bn::core::update();
    }

}
