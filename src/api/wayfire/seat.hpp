#pragma once

#include <memory>
#include <wayfire/scene.hpp>
#include <wayfire/nonstd/wlroots.hpp>
#include <wayfire/nonstd/wlroots-full.hpp>

namespace wf
{
/**
 * A seat represents a group of input devices (mouse, keyboard, etc.) which logically belong together.
 * Each seat has its own keyboard, touch, pointer and tablet focus.
 * Currently, Wayfire supports only a single seat.
 */
class seat_t
{
  public:
    // A pointer to the wlroots seat wlr_seat *const seat;
    wlr_seat*const seat;

    /**
     * Get the xkb_state of the currently active keyboard.
     * Note: may be null if there is no keyboard connected to the seat.
     */
    xkb_state *get_xkb_state();

    /**
     * Get a list of all currently pressed keys.
     */
    std::vector<uint32_t> get_pressed_keys();

    /**
     * Get a bitmask of the pressed modifiers on the current keyboard.
     * The returned value is a bitmask of WLR_MODIFIER_*.
     */
    uint32_t get_keyboard_modifiers();

    /**
     * Figure out whether the given keycode is a modifier on the current keyboard's keymap.
     * If yes, return the modifier as a WLR_MODIFIER_* bitmask, otherwise, return 0.
     */
    uint32_t modifier_from_keycode(uint32_t keycode);

    /**
     * Set the keyboard focus node. Note that this changes only the focus state
     * and does not reorder nodes or anything like this.
     */
    void set_active_node(wf::scene::node_ptr node);

    /**
     * Create and initialize a new seat.
     */
    seat_t(wl_display *display, std::string name);
    ~seat_t();

    struct impl;
    std::unique_ptr<impl> priv;
};
}
