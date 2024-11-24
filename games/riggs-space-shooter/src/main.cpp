#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_regular_bg_map_cell_info.h"

#include "bn_regular_bg_items_bg.h"
#include "bn_regular_bg_items_borders.h"
#include "bn_sprite_items_spaceship.h"

#include "common_info.h"

int main()
{
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::bg.create_bg(0,0);
    bg.set_priority(1);
    bn::regular_bg_ptr borders = bn::regular_bg_items::borders.create_bg(0,0);
    borders.set_priority(0);
    bn::sprite_ptr spaceship = bn::sprite_items::spaceship.create_sprite(0, 0);
    spaceship.set_bg_priority(0);

    const bn::regular_bg_map_item& borders_item = bn::regular_bg_items::borders.map_item();
    bn::regular_bg_map_cell valid_map_cell = borders_item.cell(0, 0);
    int valid_tile_index = bn::regular_bg_map_cell_info(valid_map_cell).tile_index();
    bn::point spaceship_map_position(0, 0);
    bn::point new_spaceship_map_position = spaceship_map_position;

    bool canMove = 0;

    while(true)
    {
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

        spaceship.set_position(new_spaceship_map_position);

        bn::core::update();
    }

}
