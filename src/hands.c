#include "hands.h"
#include "config.h"

static GPath *s_minute_arrow;
static GPath *s_hour_arrow;
static GPath *s_minute_arrow_round;
static GPath *s_hour_arrow_round;
static GPath *s_minute_arrow_chalk;
static GPath *s_hour_arrow_chalk;
static GPath *s_minute_arrow_emery;
static GPath *s_hour_arrow_emery;
static GPath *s_minute_arrow_gabbro;
static GPath *s_hour_arrow_gabbro;

// Hand path definitions
const GPathInfo MINUTE_HAND_POINTS = {
  4,
  (GPoint []) {
    { -4, 7 },
    { 4, 7 },
    { 4, -66 },
    { -4, -66 }
  }
};

const GPathInfo HOUR_HAND_POINTS = {
  4,
  (GPoint []) {
    { -5, 7 },
    { 5, 7 },
    { 5, -45 },
    { -5, -45 }
  }
};

const GPathInfo MINUTE_HAND_POINTS_ROUND = {
  4,
  (GPoint []) {
    { -4, 7 },
    { 4, 7 },
    { 4, -63 },
    { -4, -63 }
  }
};

const GPathInfo HOUR_HAND_POINTS_ROUND = {
  4,
  (GPoint []) {
    { -4, 7 },
    { 4, 7 },
    { 4, -44 },
    { -4, -44 }
  }
};

const GPathInfo MINUTE_HAND_POINTS_CHALK = {
  4,
  (GPoint []) {
    { -5, 8 },
    { 5, 8 },
    { 5, -79 },
    { -5, -79 }
  }
};

const GPathInfo HOUR_HAND_POINTS_CHALK = {
  4,
  (GPoint []) {
    { -5, 8 },
    { 5, 8 },
    { 5, -55 },
    { -5, -55 }
  }
};

const GPathInfo MINUTE_HAND_POINTS_EMERY = {
  4,
  (GPoint []) {
    { -5, 9 },
    { 5, 9 },
    { 5, -88 },
    { -5, -88 }
  }
};

const GPathInfo HOUR_HAND_POINTS_EMERY = {
  4,
  (GPoint []) {
    { -6, 9 },
    { 6, 9 },
    { 6, -60 },
    { -6, -60 }
  }
};

const GPathInfo MINUTE_HAND_POINTS_GABBRO = {
  4,
  (GPoint []) {
    { -6, 10 },
    { 6, 10 },
    { 6, -115 },
    { -6, -115 }
  }
};

const GPathInfo HOUR_HAND_POINTS_GABBRO = {
  4,
  (GPoint []) {
    { -7, 10 },
    { 7, 10 },
    { 7, -78 },
    { -7, -78 }
  }
};

void hands_init(GPoint center) {
  s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS);
  s_hour_arrow = gpath_create(&HOUR_HAND_POINTS);
  s_minute_arrow_round = gpath_create(&MINUTE_HAND_POINTS_ROUND);
  s_hour_arrow_round = gpath_create(&HOUR_HAND_POINTS_ROUND);
  s_minute_arrow_chalk = gpath_create(&MINUTE_HAND_POINTS_CHALK);
  s_hour_arrow_chalk = gpath_create(&HOUR_HAND_POINTS_CHALK);
  s_minute_arrow_emery = gpath_create(&MINUTE_HAND_POINTS_EMERY);
  s_hour_arrow_emery = gpath_create(&HOUR_HAND_POINTS_EMERY);
  s_minute_arrow_gabbro = gpath_create(&MINUTE_HAND_POINTS_GABBRO);
  s_hour_arrow_gabbro = gpath_create(&HOUR_HAND_POINTS_GABBRO);

  gpath_move_to(s_minute_arrow, center);
  gpath_move_to(s_hour_arrow, center);
  gpath_move_to(s_minute_arrow_round, center);
  gpath_move_to(s_hour_arrow_round, center);
  gpath_move_to(s_minute_arrow_chalk, center);
  gpath_move_to(s_hour_arrow_chalk, center);
  gpath_move_to(s_minute_arrow_emery, center);
  gpath_move_to(s_hour_arrow_emery, center);
  gpath_move_to(s_minute_arrow_gabbro, center);
  gpath_move_to(s_hour_arrow_gabbro, center);
}

void hands_deinit(void) {
  gpath_destroy(s_minute_arrow);
  gpath_destroy(s_hour_arrow);
  gpath_destroy(s_minute_arrow_round);
  gpath_destroy(s_hour_arrow_round);
  gpath_destroy(s_minute_arrow_chalk);
  gpath_destroy(s_hour_arrow_chalk);
  gpath_destroy(s_minute_arrow_emery);
  gpath_destroy(s_hour_arrow_emery);
  gpath_destroy(s_minute_arrow_gabbro);
  gpath_destroy(s_hour_arrow_gabbro);
}

void hands_get_current_paths(GPath **hour_path, GPath **minute_path) {
  #if PBL_DISPLAY_WIDTH == 260 && PBL_DISPLAY_HEIGHT == 260
    *hour_path = s_hour_arrow_gabbro;
    *minute_path = s_minute_arrow_gabbro;
  #elif PBL_DISPLAY_WIDTH == 200 && PBL_DISPLAY_HEIGHT == 228
    *hour_path = s_hour_arrow_emery;
    *minute_path = s_minute_arrow_emery;
  #elif PBL_DISPLAY_WIDTH == 180 && PBL_DISPLAY_HEIGHT == 180
    *hour_path = s_hour_arrow_chalk;
    *minute_path = s_minute_arrow_chalk;
  #else
    if (settings_is_round_mode()) {
      *hour_path = s_hour_arrow_round;
      *minute_path = s_minute_arrow_round;
    } else {
      *hour_path = s_hour_arrow;
      *minute_path = s_minute_arrow;
    }
  #endif
}

void hands_set_color_for_dial(GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_color(ctx, GColorBlack);
}

void hands_set_stroke_color_for_dial(GContext *ctx) {
  #ifdef PBL_COLOR
    graphics_context_set_stroke_width(ctx, 2);
  #endif
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_context_set_stroke_color(ctx, GColorBlack);
}

GColor hands_get_date_color(void) {
  return GColorBlack;
}

void hands_draw_date_box(GContext *ctx, GRect bounds) {
  if (!settings_show_date()) return;
  
  hands_set_stroke_color_for_dial(ctx);
  
  if (settings_is_round_mode()) {
    graphics_draw_rect(ctx, GRect(bounds.size.w / 2 + 25, bounds.size.h / 2 - 8, 22, 20));
  } else {
    graphics_draw_rect(ctx, GRect(102, 74, 22, 20));
  }

  #ifdef PBL_COLOR
    graphics_context_set_stroke_width(ctx, 1);
  #endif
}

void hands_draw_hour_hand(GContext *ctx, GPath *hour_path, struct tm *t) {
  graphics_context_set_fill_color(ctx, GColorFromHEX(0x090a4e));
  graphics_context_set_stroke_color(ctx, GColorFromHEX(0x090a4e));
  
  gpath_rotate_to(hour_path, (TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6));
  gpath_draw_filled(ctx, hour_path);
  gpath_draw_outline(ctx, hour_path);
}

void hands_draw_minute_hand(GContext *ctx, GPath *minute_path, struct tm *t) {
  graphics_context_set_fill_color(ctx, GColorFromHEX(0x090a4e));
  graphics_context_set_stroke_color(ctx, GColorFromHEX(0x090a4e));
  
  gpath_rotate_to(minute_path, TRIG_MAX_ANGLE * t->tm_min / 60);
  gpath_draw_filled(ctx, minute_path);
  gpath_draw_outline(ctx, minute_path);
}

void hands_draw_second_hand(GContext *ctx, GPoint center, struct tm *t) {
  if (!settings_second_hand_enabled()) return;
  
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorRed);
    graphics_context_set_stroke_color(ctx, GColorRed);
  #else
    hands_set_color_for_dial(ctx);
  #endif

  #ifdef PBL_COLOR
    #if PBL_DISPLAY_WIDTH == 260 && PBL_DISPLAY_HEIGHT == 260
      graphics_context_set_stroke_width(ctx, 5);
    #elif PBL_DISPLAY_WIDTH == 200 && PBL_DISPLAY_HEIGHT == 228
      graphics_context_set_stroke_width(ctx, 4);
    #elif PBL_DISPLAY_WIDTH == 180 && PBL_DISPLAY_HEIGHT == 180
      graphics_context_set_stroke_width(ctx, 4);
    #else
      graphics_context_set_stroke_width(ctx, 3);
    #endif
  #endif

  int16_t second_hand_length;
  int16_t second_hand_opp_length;
  int16_t second_circle_offset;
  
  #if PBL_DISPLAY_WIDTH == 260 && PBL_DISPLAY_HEIGHT == 260
    second_hand_length = 120;
    second_hand_opp_length = 10;
    second_circle_offset = 35;
  #elif PBL_DISPLAY_WIDTH == 200 && PBL_DISPLAY_HEIGHT == 228
    second_hand_length = 97;
    second_hand_opp_length = 9;
    second_circle_offset = 30;
  #elif PBL_DISPLAY_WIDTH == 180 && PBL_DISPLAY_HEIGHT == 180
    second_hand_length = 87;
    second_hand_opp_length = 8;
    second_circle_offset = 27;
  #else
    if (settings_is_round_mode()) {
      second_hand_length = 65;
      second_hand_opp_length = 7;
      second_circle_offset = 22;
    } else {
      GRect bounds = layer_get_bounds(window_get_root_layer(window_stack_get_top_window()));
      second_hand_length = (bounds.size.w / 2) + 7;
      second_hand_opp_length = 7;
      second_circle_offset = 22;
    }
  #endif
   
  double second_angle = 0;
  
  if (settings_is_quartz()) {
    second_angle = TRIG_MAX_ANGLE * t->tm_sec / 60;
  } else if (settings_is_stop2go()) {
    time_t sec;
    uint16_t ms;
    time_ms(&sec, &ms);
    struct tm *now = localtime(&sec);
    
    if (now->tm_sec < 58) {
      double fractional_sec = now->tm_sec + ms / 1000.0;
      second_angle = TRIG_MAX_ANGLE * fractional_sec / 58.0;
    } else {
      second_angle = 0;
    }
  }
  
  int32_t angle = (int32_t)second_angle;
  
  // Calculate circle position - offset from tip toward center
  int16_t circle_distance = second_hand_length - second_circle_offset;
  GPoint second_circle = {
    .x = (int16_t)(sin_lookup(angle) * (int32_t)circle_distance / TRIG_MAX_RATIO) + center.x,
    .y = (int16_t)(-cos_lookup(angle) * (int32_t)circle_distance / TRIG_MAX_RATIO) + center.y,
  };

  // Determine circle radius based on display
  int16_t circle_radius;
  #if PBL_DISPLAY_WIDTH == 260 && PBL_DISPLAY_HEIGHT == 260
    circle_radius = 12;
  #elif PBL_DISPLAY_WIDTH == 200 && PBL_DISPLAY_HEIGHT == 228
    circle_radius = 10;
  #elif PBL_DISPLAY_WIDTH == 180 && PBL_DISPLAY_HEIGHT == 180
    circle_radius = 9;
  #else
    circle_radius = 7;
  #endif

  // Calculate line segment points - stop before circle and resume after
  int16_t line_start_distance = circle_distance + circle_radius + 2;
  int16_t line_end_distance = circle_distance - circle_radius - 2;
  
  GPoint line_start = {
    .x = (int16_t)(sin_lookup(angle) * (int32_t)second_hand_length / TRIG_MAX_RATIO) + center.x,
    .y = (int16_t)(-cos_lookup(angle) * (int32_t)second_hand_length / TRIG_MAX_RATIO) + center.y,
  };
  
  GPoint line_before_circle = {
    .x = (int16_t)(sin_lookup(angle) * (int32_t)line_start_distance / TRIG_MAX_RATIO) + center.x,
    .y = (int16_t)(-cos_lookup(angle) * (int32_t)line_start_distance / TRIG_MAX_RATIO) + center.y,
  };
  
  GPoint line_after_circle = {
    .x = (int16_t)(sin_lookup(angle) * (int32_t)line_end_distance / TRIG_MAX_RATIO) + center.x,
    .y = (int16_t)(-cos_lookup(angle) * (int32_t)line_end_distance / TRIG_MAX_RATIO) + center.y,
  };
  
  // Draw line from tip to before circle, and from after circle to center
  graphics_draw_line(ctx, line_start, line_before_circle);
  graphics_draw_line(ctx, line_after_circle, center);
  
  GPoint second_hand_opp = {
    .x = (int16_t)(-sin_lookup(angle) * (int32_t)second_hand_opp_length / TRIG_MAX_RATIO) + center.x,
    .y = (int16_t)(cos_lookup(angle) * (int32_t)second_hand_opp_length / TRIG_MAX_RATIO) + center.y,
  };
  
  graphics_draw_line(ctx, second_hand_opp, center);

  // Draw the hollow circle
  graphics_draw_circle(ctx, second_circle, circle_radius);
  
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorFromHEX(0x090a4e));
    graphics_context_set_stroke_color(ctx, GColorFromHEX(0x090a4e));
  #else
    hands_set_color_for_dial(ctx);
  #endif
  
  #if PBL_DISPLAY_WIDTH == 260 && PBL_DISPLAY_HEIGHT == 260
    graphics_fill_circle(ctx, GPoint(center.x, center.y), 10);
  #elif PBL_DISPLAY_WIDTH == 200 && PBL_DISPLAY_HEIGHT == 228
    graphics_fill_circle(ctx, GPoint(center.x, center.y), 9);
  #elif PBL_DISPLAY_WIDTH == 180 && PBL_DISPLAY_HEIGHT == 180
    graphics_fill_circle(ctx, GPoint(center.x, center.y), 8);
  #else
    graphics_fill_circle(ctx, GPoint(center.x, center.y), 7);
  #endif
}

void hands_draw(Layer *layer, GContext *ctx, struct tm *t) {
  GRect bounds = layer_get_bounds(layer);
  GPoint center = grect_center_point(&bounds);
  
  GPath *hour_path;
  GPath *minute_path;
  hands_get_current_paths(&hour_path, &minute_path);
  
  hands_draw_date_box(ctx, bounds);
  hands_draw_hour_hand(ctx, hour_path, t);
  hands_draw_minute_hand(ctx, minute_path, t);
  hands_draw_second_hand(ctx, center, t);
}
