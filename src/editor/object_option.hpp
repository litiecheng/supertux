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

#ifndef HEADER_SUPERTUX_EDITOR_OBJECT_OPTION_HPP
#define HEADER_SUPERTUX_EDITOR_OBJECT_OPTION_HPP

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include "video/color.hpp"

#include "gui/menu_action.hpp"

enum ObjectOptionFlag {
  /** Set if the value is a hidden implementation detail that
      shouldn't be exposed to the user */
  OPTION_HIDDEN = (1 << 0),

  /** Set if the text should be saved as translatable */
  OPTION_TRANSLATABLE = (1 << 1)
};

class Color;
class Menu;
class Writer;

class ObjectOption
{
public:
  ObjectOption(const std::string& text, const std::string& key, unsigned int flags);
  virtual ~ObjectOption();

  virtual void save(Writer& write) const = 0;
  virtual std::string to_string() const = 0;
  virtual void add_to_menu(Menu& menu) const = 0;

  const std::string& get_key() const { return m_key; }
  const std::string& get_text() const { return m_text; }
  unsigned int get_flags() const { return m_flags; }

private:
  const std::string m_text;
  const std::string m_key;
  const unsigned int m_flags;

private:
  ObjectOption(const ObjectOption&) = delete;
  ObjectOption& operator=(const ObjectOption&) = delete;
};

class BoolObjectOption : public ObjectOption
{
public:
  BoolObjectOption(const std::string& text, bool* pointer, const std::string& key,
                   boost::optional<bool> default_value,
                   unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  bool* const m_pointer;
  const boost::optional<bool> m_default_value;

private:
  BoolObjectOption(const BoolObjectOption&) = delete;
  BoolObjectOption& operator=(const BoolObjectOption&) = delete;
};

class IntObjectOption : public ObjectOption
{
public:
  IntObjectOption(const std::string& text, int* pointer, const std::string& key,
                  boost::optional<int> default_value,
                  unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  int* const m_pointer;
  const boost::optional<int> m_default_value;

private:
  IntObjectOption(const IntObjectOption&) = delete;
  IntObjectOption& operator=(const IntObjectOption&) = delete;
};

class FloatObjectOption : public ObjectOption
{
public:
  FloatObjectOption(const std::string& text, float* pointer, const std::string& key,
                    boost::optional<float> default_value,
                    unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  float* const m_pointer;
  const boost::optional<float> m_default_value;

private:
  FloatObjectOption(const FloatObjectOption&) = delete;
  FloatObjectOption& operator=(const FloatObjectOption&) = delete;
};

class StringObjectOption : public ObjectOption
{
public:
  StringObjectOption(const std::string& text, std::string* pointer, const std::string& key,
                     unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  std::string* const m_pointer;

private:
  StringObjectOption(const StringObjectOption&) = delete;
  StringObjectOption& operator=(const StringObjectOption&) = delete;
};

class StringSelectObjectOption : public ObjectOption
{
public:
  StringSelectObjectOption(const std::string& text, int* pointer, const std::vector<std::string>& select,
                           boost::optional<int> default_value,
                           const std::string& key, unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  int* const m_pointer;
  const std::vector<std::string> m_select;
  const boost::optional<int> m_default_value;

private:
  StringSelectObjectOption(const StringSelectObjectOption&) = delete;
  StringSelectObjectOption& operator=(const StringSelectObjectOption&) = delete;
};

class EnumObjectOption : public ObjectOption
{
public:
  EnumObjectOption(const std::string& text, int* pointer,
                   const std::vector<std::string>& labels,
                   const std::vector<std::string>& symbols,
                   boost::optional<int> default_value,
                   const std::string& key, unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  int* const m_pointer;
  const std::vector<std::string> m_labels;
  const std::vector<std::string> m_symbols;
  const boost::optional<int> m_default_value;

private:
  EnumObjectOption(const EnumObjectOption&) = delete;
  EnumObjectOption& operator=(const EnumObjectOption&) = delete;
};

class ScriptObjectOption : public ObjectOption
{
public:
  ScriptObjectOption(const std::string& text, std::string* pointer, const std::string& key,
                     unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  std::string* const m_pointer;

private:
  ScriptObjectOption(const ScriptObjectOption&) = delete;
  ScriptObjectOption& operator=(const ScriptObjectOption&) = delete;
};

class FileObjectOption : public ObjectOption
{
public:
  FileObjectOption(const std::string& text, std::string* pointer, const std::string& key,
                   std::vector<std::string> filter, unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  std::string* const m_pointer;
  const std::vector<std::string> m_filter;

private:
  FileObjectOption(const FileObjectOption&) = delete;
  FileObjectOption& operator=(const FileObjectOption&) = delete;
};

class ColorObjectOption : public ObjectOption
{
public:
  ColorObjectOption(const std::string& text, Color* pointer, const std::string& key,
                    boost::optional<Color> default_value,
                    unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  Color* const m_pointer;
  const boost::optional<Color> m_default_value;

private:
  ColorObjectOption(const ColorObjectOption&) = delete;
  ColorObjectOption& operator=(const ColorObjectOption&) = delete;
};

class BadGuySelectObjectOption : public ObjectOption
{
public:
  BadGuySelectObjectOption(const std::string& text, std::vector<std::string>* pointer, const std::string& key,
                    unsigned int flags);

  virtual void save(Writer& write) const override;
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  std::vector<std::string>* const m_pointer;

private:
  BadGuySelectObjectOption(const BadGuySelectObjectOption&) = delete;
  BadGuySelectObjectOption& operator=(const BadGuySelectObjectOption&) = delete;
};

class RemoveObjectOption : public ObjectOption
{
public:
  RemoveObjectOption();

  virtual void save(Writer& write) const override {}
  virtual std::string to_string() const override;
  virtual void add_to_menu(Menu& menu) const override;

private:
  RemoveObjectOption(const RemoveObjectOption&) = delete;
  RemoveObjectOption& operator=(const RemoveObjectOption&) = delete;
};

#endif

/* EOF */
