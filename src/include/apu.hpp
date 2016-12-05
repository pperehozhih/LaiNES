#pragma once
#include "common.hpp"

namespace APU {

#define SAMPLE_RATE 16000
/*
 *  8000
 * 11025
 * 16000
 * 22050
 * 32000
 * 44100
 * 48000
 * 96000
 */
#define BUFFER_SIZE 4096
#define CLOCK_RATE 1789773

template <bool write> u8 access(int elapsed, u16 addr, u8 v = 0);
void run_frame(int elapsed);
void reset();
void init();


}
