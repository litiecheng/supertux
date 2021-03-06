//  SuperTux
//  Copyright (C) 2015 Hume2 <teratux.mail@gmail.com>
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

#include "editor/object_settings.hpp"

#include <assert.h>

#include "util/gettext.hpp"
#include "video/color.hpp"

ObjectSettings::ObjectSettings(const std::string& name) :
  m_name(name),
  m_options()
{
}

void
ObjectSettings::add_option(std::unique_ptr<ObjectOption> option)
{
  m_options.push_back(std::move(option));
}

void
ObjectSettings::add_badguy(const std::string& text, std::vector<std::string>* value_ptr,
                           const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<BadGuySelectObjectOption>(text, value_ptr, key, flags));
}

void
ObjectSettings::add_color(const std::string& text, Color* value_ptr,
                          const std::string& key,
                          boost::optional<Color> default_value,
                          unsigned int flags)
{
  add_option(std::make_unique<ColorObjectOption>(text, value_ptr, key, default_value, flags));
}

void
ObjectSettings::add_bool(const std::string& text, bool* value_ptr,
                         const std::string& key,
                         boost::optional<bool> default_value,
                         unsigned int flags)
{
  add_option(std::make_unique<BoolObjectOption>(text, value_ptr, key, default_value, flags));
}

void
ObjectSettings::add_float(const std::string& text, float* value_ptr,
                          const std::string& key,
                          boost::optional<float> default_value,
                          unsigned int flags)
{
  add_option(std::make_unique<FloatObjectOption>(text, value_ptr, key, default_value, flags));
}

void
ObjectSettings::add_int(const std::string& text, int* value_ptr,
                        const std::string& key,
                        boost::optional<int> default_value,
                        unsigned int flags)
{
  add_option(std::make_unique<IntObjectOption>(text, value_ptr, key, default_value, flags));
}

void
ObjectSettings::add_direction(const std::string& text, Direction* value_ptr,
                              boost::optional<Direction> default_value,
                              const std::string& key, unsigned int flags)
{
  add_string_select(_("Direction"), reinterpret_cast<int*>(value_ptr),
                    {_("auto"), _("left"), _("right"), _("up"), _("down")},
                    default_value ? static_cast<int>(*default_value) : boost::optional<int>(),
                    key, flags);
}

void
ObjectSettings::add_worldmap_direction(const std::string& text, worldmap::Direction* value_ptr,
                                       boost::optional<worldmap::Direction> default_value,
                                       const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<StringSelectObjectOption>(
               text, reinterpret_cast<int*>(value_ptr),
               std::vector<std::string>{_("None"), _("West"), _("East"), _("North"), _("South")},
               boost::none, key, 0));
}

void
ObjectSettings::add_walk_mode(const std::string& text, WalkMode* value_ptr,
                              boost::optional<WalkMode> default_value,
                              const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<StringSelectObjectOption>(
               text, reinterpret_cast<int*>(value_ptr),
               std::vector<std::string>{_("One shot"), _("Ping-pong"), _("Circular"), _("Unordered")},
               boost::none, key, 0));
}

void
ObjectSettings::add_remove()
{
  add_option(std::make_unique<RemoveObjectOption>());
}

void
ObjectSettings::add_script(const std::string& text, std::string* value_ptr,
                           const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<ScriptObjectOption>(text, value_ptr, key, flags));
}

void
ObjectSettings::add_text(const std::string& text, std::string* value_ptr,
                         const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<StringObjectOption>(text, value_ptr, key, flags));
}

void
ObjectSettings::add_translatable_text(const std::string& text, std::string* value_ptr,
                                      const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<StringObjectOption>(text, value_ptr, key, flags | OPTION_TRANSLATABLE));
}

void
ObjectSettings::add_string_select(const std::string& text, int* value_ptr, const std::vector<std::string>& select,
                                  boost::optional<int> default_value,
                                  const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<StringSelectObjectOption>(text, value_ptr, select, default_value, key, flags));
}

void
ObjectSettings::add_enum(const std::string& text, int* value_ptr,
                         const std::vector<std::string>& labels,
                         const std::vector<std::string>& symbols,
                         boost::optional<int> default_value,
                         const std::string& key, unsigned int flags)
{
  add_option(std::make_unique<EnumObjectOption>(text, value_ptr, labels, symbols, default_value, key, flags));
}

void
ObjectSettings::add_file(const std::string& text, std::string* value_ptr, const std::string& key,
                         const std::vector<std::string>& filter, unsigned int flags)
{
  add_option(std::make_unique<FileObjectOption>(text, value_ptr, key, filter, flags));
}

void
ObjectSettings::add_level(const std::string& text, std::string* value_ptr, const std::string& key,
                          unsigned int flags)
{
  add_file(text, value_ptr, key, {".stl"}, flags);
}

void
ObjectSettings::add_sprite(const std::string& text, std::string* value_ptr, const std::string& key,
                           unsigned int flags)
{
  add_file(text, value_ptr, key, {".jpg", ".png", ".sprite"}, flags);
}

void
ObjectSettings::add_surface(const std::string& text, std::string* value_ptr, const std::string& key,
                            unsigned int flags)
{
  add_file(text, value_ptr, key, {".jpg", ".png", ".surface"}, flags);
}

void
ObjectSettings::add_sound(const std::string& text, std::string* value_ptr, const std::string& key,
                          unsigned int flags)
{
  add_file(text, value_ptr, key, {".wav", ".ogg"}, flags);
}

void
ObjectSettings::add_music(const std::string& text, std::string* value_ptr, const std::string& key,
                          unsigned int flags)
{
  add_file(text, value_ptr, key, {".ogg", ".music"}, flags);
}

void
ObjectSettings::add_worldmap(const std::string& text, std::string* value_ptr, const std::string& key,
                            unsigned int flags)
{
  add_file(text, value_ptr, key, {".stwm"}, flags);
}

void
ObjectSettings::reorder(const std::vector<std::string>& order)
{
  std::vector<std::unique_ptr<ObjectOption> > new_options;

  // put all items not in 'order' into 'new_options'
  for(auto& option : m_options) {
    if (option) {
      auto it = std::find(order.begin(), order.end(), option->get_key());
      if (it == order.end())
      {
        new_options.push_back(std::move(option));
      }
    }
  }

  // put all other items in 'order' into 'new_options' in the order of 'order'
  for(const auto& option_name : order) {
    auto it = std::find_if(m_options.begin(), m_options.end(),
                           [option_name](const std::unique_ptr<ObjectOption>& option){
                             return option && option->get_key() == option_name;
                           });
    if (it != m_options.end()) {
      new_options.push_back(std::move(*it));
    }
  }

  assert(m_options.size() == new_options.size());

  m_options = std::move(new_options);
}

/* EOF */
