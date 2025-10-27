/// @file mcp2518fd.h
/// @author Leo Walker

#pragma once

#include <stdint.h>
#include "spi.h"

typedef struct mcp2518fd_device mcp2518fd_device_t;

mcp2518fd_device_t* mcp2518fd_device_init(spi_instance_t* spi_device);
void mcp2518fd_device_destroy(mcp2518fd_device_t* device);

void mcp2518fd_reset(mcp2518fd_device_t* device);