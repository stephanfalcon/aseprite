// Aseprite
// Copyright (C) 2019  Igara Studio S.A.
// Copyright (C) 2001-2015  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/tools/stroke.h"

namespace app {
namespace tools {

void Stroke::reset()
{
  m_points.clear();
}

void Stroke::reset(int n, const gfx::Point& point)
{
  m_points.resize(n, point);
}

void Stroke::addPoint(const gfx::Point& point)
{
  m_points.push_back(point);
}

void Stroke::offset(const gfx::Point& delta)
{
  for (auto& p : m_points)
    p += delta;
}

void Stroke::erase(int index)
{
  ASSERT(0 <= index && index < m_points.size());
  if (0 <= index && index < m_points.size())
    m_points.erase(m_points.begin()+index);
}

gfx::Rect Stroke::bounds() const
{
  if (m_points.empty())
    return gfx::Rect();

  gfx::Point
    minpt(m_points[0]),
    maxpt(m_points[0]);

  for (std::size_t c=1; c<m_points.size(); ++c) {
    int x = m_points[c].x;
    int y = m_points[c].y;
    if (minpt.x > x) minpt.x = x;
    if (minpt.y > y) minpt.y = y;
    if (maxpt.x < x) maxpt.x = x;
    if (maxpt.y < y) maxpt.y = y;
  }

  return gfx::Rect(minpt.x, minpt.y,
                   maxpt.x - minpt.x + 1,
                   maxpt.y - minpt.y + 1);
}

} // namespace tools
} // namespace app
