// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/geometry/dom_rect.h"

#include "base/command_line.h"

#include "third_party/blink/renderer/bindings/core/v8/v8_dom_rect_init.h"
#include "third_party/blink/renderer/platform/wtf/math_extras.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/rect_conversions.h"
#include "ui/gfx/geometry/rect_f.h"

namespace blink {

DOMRect* DOMRect::Create(double x, double y, double width, double height) {
  return MakeGarbageCollected<DOMRect>(x, y, width, height);
}

DOMRect* DOMRect::FromRectF(const gfx::RectF& rect_in) {
  gfx::RectF rect = rect_in;

  // === ##SPOOF CLIENTRECT JITTER — DETERMINISTIC ===
  int seed = 0;

  // 1) Seed tamamen flag'den gelir
  {
    const base::CommandLine& cmd = *base::CommandLine::ForCurrentProcess();
    std::string seed_str = cmd.GetSwitchValueASCII("fp_clientrect_seed");

    if (!seed_str.empty()) {
      for (unsigned char c : seed_str) {
        seed = (seed * 131 + c) & 0x7fffffff;
      }
    } else {
      seed = 0x12345;  // fallback deterministic
    }
  }

  auto noise = [&](int mod) {
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return static_cast<float>(seed % mod) * 0.01f;  // deterministic jitter
  };

  rect.set_x(rect.x() + noise(50));
  rect.set_y(rect.y() + noise(50));
  rect.set_width(rect.width() + noise(25));
  rect.set_height(rect.height() + noise(25));
  // ======================================================

  return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), rect.width(),
                                       rect.height());
}

DOMRect* DOMRect::fromRect(const DOMRectInit* other) {
  return MakeGarbageCollected<DOMRect>(other->x(), other->y(), other->width(),
                                       other->height());
}

DOMRect::DOMRect(double x, double y, double width, double height)
    : DOMRectReadOnly(x, y, width, height) {}

gfx::Rect DOMRect::ToEnclosingRect() const {
  return gfx::ToEnclosingRect(
      gfx::RectF(ClampTo<float>(x()), ClampTo<float>(y()),
                 ClampTo<float>(width()), ClampTo<float>(height())));
}

}  // namespace blink
