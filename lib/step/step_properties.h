/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_PROPERTIES_HEADER
#define STEP_PROPERTIES_HEADER

#include <algorithm>
#include <map>
#include <string>

#include "step_api.h"
#include "step_color.h"
#include "step_property.h"
#include "step_types.h"
#include "step_utils.h"

namespace step {

/**
 * The Properties class is a helper for managing a collection of Property
 * instances.
 *
 * @see Property
 * @since 0.1.0
 */
class Properties final {
 public:
  STEP_API friend void from_json(const JSON&, Properties&);

  /**
   * Iterates over all of the properties store in this instance.
   *
   * @tparam Lambda the type of the lambda object.
   * @param lambda the lambda that takes one argument, std::pair&lt;std::string,
   * Property&gt;, either by value or const reference.
   * @since 0.1.0
   */
  template <typename Lambda>
  void each(Lambda&& lambda) const
  {
    std::for_each(m_properties.cbegin(), m_properties.cend(), lambda);
  }

  /**
   * Indicates whether or not there is a property associated with the
   * specified name.
   *
   * @param name the name of the property to look for.
   * @return true if there is a property associated with the specified name;
   * false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool has(const std::string& name) const;

  /**
   * Returns the property associated with the specified name. This method
   * will throw an exception if the desired property doesn't exist.
   *
   * @param name the name of the desired property.
   * @return the property associated with the specified name.
   * @throws StepException if the desired property doesn't exist.
   * @since 0.1.0
   */
  STEP_QUERY const Property& get(const std::string& name) const;

  /**
   * Indicates whether or not the specified property is equal to the supplied
   * value. This method does not throw any exceptions by itself and is the
   * preferred way to check the value of a property. The returned value is
   * always <b>false</b> if the property doesn't exist or if the property
   * has another type. A compile-time error will be raised if the type of the
   * supplied value isn't one of: <b>bool</b>, <b>int</b>, <b>float</b>,
   * <b>Color</b> or <b>std::string</b> (accepts anything that is convertible
   * to <b>std::string</b>).
   *
   * @tparam T the type of the value that will be compared to the value of
   * the specified property. An unsupported type will cause a compile-time
   * error.
   * @param name the name of the property to check the value of.
   * @param value the value that will be compared with the value of the
   * specified property.
   * @return true if the specified property had a value and it turned out to
   * be equal to the supplied value; false otherwise.
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] bool is(const std::string& name, const T& value) const
  {
    if (!has(name)) {
      return false;
    }

    const auto& property = get(name);

    if constexpr (std::is_same_v<T, bool>) {
      return property.as_bool().value_or(false);

    } else if constexpr (std::is_same_v<T, int>) {
      return property.is_int() && property.as_int().value() == value;

    } else if constexpr (std::is_same_v<T, float>) {
      return property.is_float() && property.as_float().value() == value;

    } else if constexpr (std::is_same_v<T, Color>) {
      return property.is_color() && property.as_color().value() == value;

    } else if constexpr (std::is_convertible_v<T, std::string>) {
      return property.is_string() && property.as_string().value() == value;
    }

    return false;
  }

  /**
   * Returns the amount of Property instances handled by this instance.
   *
   * @return the amount of Property instances handled by this instance.
   * @since 0.1.0
   */
  STEP_QUERY int amount() const noexcept;

  /**
   * Indicates whether or not there are any Property instances handled by
   * this instance.
   *
   * @return true if there are properties handled by this instance; false
   * otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool empty() const noexcept;

 private:
  std::map<std::string, Property> m_properties;
};

STEP_API void from_json(const JSON& json, Properties& props);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_properties.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_PROPERTIES_HEADER
