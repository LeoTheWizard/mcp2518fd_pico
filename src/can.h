#pragma once

#include <stdint.h>

#define CAN_SFF_MASK 0x000007FFUL// Standard Identifier Mask
#define CAN_EFF_MASK 0x1FFFFFFFUL// Extended Identifier Mask

///
/// @struct can_fd_frame
/// @brief Represents a CAN FD frame.
///
typedef struct __attribute__((packed))
{
    uint32_t id;      // Frame Identifier.
    bool eff;         // Is Extended Frame Format.
    bool fd;          // Is Flexible Data rate frame.
    bool brs;         // Bit Rate Switch bit.
    bool esi;         // Error State Indicator bit.
    uint8_t dlc;      // Data length code, past 8 bytes does not match the length of the frame itself. refer to dlc_map.
    uint8_t data[64]; // Frame payload data buffer.
} can_fd_frame_t;

// DLC to fd frame byte length
// 0-8 -> 0-8 - Same as standard can frame.
// 9   -> 12
// 10  -> 16
// 11  -> 20
// 12  -> 24
// 13  -> 32
// 14  -> 48
// 15  -> 64

///
/// @brief Decodes a frames Data Length Code into a useful byte length.
/// @param frame The CAN FD frame.
/// @return The data byte length of the frame provided.
///
static inline uint8_t can_fd_frame_get_length(const can_fd_frame_t* frame)
{
    static const uint8_t dlc_map[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64 };

    if(frame->dlc > 15) return 255; // Error value as DLC is invalid.
    return dlc_map[frame->dlc];
}