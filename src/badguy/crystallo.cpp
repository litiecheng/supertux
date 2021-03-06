//  SuperTux - Crystallo
//  Copyright (C) 2008 Wolfgang Becker <uafr@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "badguy/crystallo.hpp"

#include "util/reader_mapping.hpp"

Crystallo::Crystallo(const ReaderMapping& reader) :
  WalkingBadguy(reader, "images/creatures/crystallo/crystallo.sprite", "left", "right"),
  m_radius()
{
  walk_speed = 80;
  max_drop_height = 16;

  reader.get("radius", m_radius, 100.0f);
}

ObjectSettings
Crystallo::get_settings()
{
  ObjectSettings result = WalkingBadguy::get_settings();
  result.add_float(_("Radius"), &m_radius, "radius");
  return result;
}

void
Crystallo::active_update(float dt_sec)
{
  if (get_pos().x > (m_start_position.x + m_radius)) {
    if (m_dir != Direction::LEFT){
      turn_around();
    }
  }

  if (get_pos().x < (m_start_position.x - m_radius)) {
    if (m_dir != Direction::RIGHT){
      turn_around();
    }
  }

  BadGuy::active_update(dt_sec);
}

bool
Crystallo::collision_squished(GameObject& object)
{
  set_action(m_dir == Direction::LEFT ? "shattered-left" : "shattered-right", /* loops = */ -1, ANCHOR_BOTTOM);
  kill_squished(object);
  return true;
}

bool
Crystallo::is_flammable() const
{
  return false;
}

/* EOF */
