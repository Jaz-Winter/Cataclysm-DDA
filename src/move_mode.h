#pragma once
#ifndef CATA_SRC_MOVE_MODE_H
#define CATA_SRC_MOVE_MODE_H

#include <cstdint>
#include <iosfwd>
#include <map>
#include <vector>

#include "color.h"
#include "translations.h"
#include "type_id.h"

class JsonObject;
template<typename T>
class generic_factory;

enum class steed_type : int {
    NONE,
    ANIMAL,
    MECH,
    NUM
};

enum class move_mode_type : int {
    PRONE,
    CROUCHING,
    WALKING,
    RUNNING
};

class move_mode
{

        friend class generic_factory<move_mode>;
        friend struct mod_tracker;

        bool was_loaded = false;
        move_mode_id id;
        std::vector<std::pair<move_mode_id, mod_id>> src;

        std::map<steed_type, translation> change_messages_success;
        std::map<steed_type, translation> change_messages_fail;

        bool _stop_hauling = false;

        // Mutable because I couldn't figure out how to set this after it had been loaded
        // Which was necessary, because I needed to know the values of the other ones
        // before I could set it
        mutable move_mode_id cycle_to;
        move_mode_type _type = move_mode_type::WALKING;

        float _exertion_level = 0.0f;
        float _move_speed_mult = 0.0f;
        float _sound_multiplier = 0.0f;
        float _stamina_multiplier = 0.0f;

        int _mech_power_use = 0;
        int _swim_speed_mod = 0;

        nc_color _panel_color;
        nc_color _symbol_color;
        uint32_t _panel_letter;
        uint32_t _letter;
        translation _name;

    public:
        static void load_move_mode( const JsonObject &jo, const std::string &src );
        void load( const JsonObject &jo, const std::string &src );
        static void finalize();
        static void reset();

        move_mode() = default;

        // name: walk, run, crouch, prone
        std::string name() const;
        std::string change_message( bool success, steed_type steed ) const;

        move_mode_id cycle() const;
        move_mode_id ident() const;

        float sound_mult() const;
        float stamina_mult() const;
        float exertion_level() const;
        float move_speed_mult() const;

        int mech_power_use() const;
        int swim_speed_mod() const;

        nc_color panel_color() const;
        nc_color symbol_color() const;

        char panel_letter() const;
        char letter() const;
        bool stop_hauling() const;
        move_mode_type type() const;

        // Const because it's modifying a mutable
        void set_cycle( const move_mode_id &mode ) const;
};

const std::vector<move_mode_id> &move_modes_by_speed();

#endif // CATA_SRC_MOVE_MODE_H
