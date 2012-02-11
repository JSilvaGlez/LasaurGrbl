/*
  config.h - compile time configuration
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011 Sungeun K. Jeon
  Copyright (c) 2011 Stefan Hechenberger

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef config_h
#define config_h

#include <inttypes.h>
#include <stdbool.h>


#define LASAURGRBL_VERSION "v12.03-beta1"
#define BAUD_RATE 9600


#define LIMIT_OVERWRITE_DDR     DDRD
#define LIMIT_OVERWRITE_PORT    PORTD
#define LIMIT_OVERWRITE_BIT     7

#define SENSE_DDR               DDRD
#define SENSE_PORT              PORTD
#define POWER_BIT               2
#define CHILLER_BIT             3
#define DOOR_BIT                5
  
#define LIMIT_DDR               DDRC
#define LIMIT_PORT              PORTC
#define LIMIT_PIN               PINC
#define X1_LIMIT_BIT            0
#define X2_LIMIT_BIT            1
#define Y1_LIMIT_BIT            2
#define Y2_LIMIT_BIT            3

#define AIRGAS_DDR              DDRC
#define AIRGAS_PORT             PORTC
#define AIR_BIT                 4
#define GAS_BIT                 5

#define STEPPING_DDR            DDRB
#define STEPPING_PORT           PORTB
#define X_STEP_BIT              0
#define Y_STEP_BIT              1
#define Z_STEP_BIT              2
#define X_DIRECTION_BIT         3
#define Y_DIRECTION_BIT         4
#define Z_DIRECTION_BIT         5


#define LIMIT_MASK ((1<<X1_LIMIT_BIT)|(1<<X2_LIMIT_BIT)|(1<<Y1_LIMIT_BIT)|(1<<Y2_LIMIT_BIT))
#define STEPPING_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT))
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT))
#define INVERT_MASK 24U  // 0x00011000 invert direction pin 3 and 4, (1<<X_DIRECTION_BIT) | (1<<Y_DIRECTION_BIT)


#define CONFIG_X_STEPS_PER_MM 32.80839895 //microsteps/mm
#define CONFIG_Y_STEPS_PER_MM 32.80839895 //microsteps/mm
#define CONFIG_Z_STEPS_PER_MM 32.80839895 //microsteps/mm
#define CONFIG_PULSE_MICROSECONDS 5
#define CONFIG_FEEDRATE 20000.0 // in millimeters per minute
#define CONFIG_SEEKRATE 5000.0
#define CONFIG_ACCELERATION 1800000.0 // mm/min^2, typically 1000000-8000000, divide by (60*60) to get mm/sec^2
#define CONFIG_JUNCTION_DEVIATION 0.1 // mm


// The temporal resolution of the acceleration management subsystem. Higher number give smoother
// acceleration but may impact performance.
// NOTE: Increasing this parameter will help any resolution related issues, especially with machines 
// requiring very high accelerations and/or very fast feedrates. In general, this will reduce the 
// error between how the planner plans the motions and how the stepper program actually performs them.
// However, at some point, the resolution can be high enough, where the errors related to numerical 
// round-off can be great enough to cause problems and/or it's too fast for the Arduino. The correct
// value for this parameter is machine dependent, so it's advised to set this only as high as needed.
// Approximate successful values can range from 30L to 100L or more.
#define ACCELERATION_TICKS_PER_SECOND 100L

// Minimum planner junction speed. Sets the default minimum speed the planner plans for at the end
// of the buffer and all stops. This should not be much greater than zero and should only be changed
// if unwanted behavior is observed on a user's machine when running at very slow speeds.
#define ZERO_SPEED 0.0 // (mm/min)

// Minimum stepper rate. Sets the absolute minimum stepper rate in the stepper program and never runs
// slower than this value, except when sleeping. This parameter overrides the minimum planner speed.
// This is primarily used to guarantee that the end of a movement is always reached and not stop to
// never reach its target. This parameter should always be greater than zero.
#define MINIMUM_STEPS_PER_MINUTE 1600U // (steps/min) - Integer value only
// 1600 @ 32step_per_mm = 50mm/min


#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


#define clear_vector(a) memset(a, 0, sizeof(a))
#define clear_vector_double(a) memset(a, 0.0, sizeof(a))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))


#endif



// bit math
// see: http://www.arduino.cc/playground/Code/BitMath
// see: http://graphics.stanford.edu/~seander/bithacks.html
//
// y = (x >> n) & 1; // n=0..15. stores nth bit of x in y. y becomes 0 or 1.
//
// x &= ~(1 << n); // forces nth bit of x to be 0. all other bits left alone.
//
// x &= (1<<(n+1))-1; // leaves alone the lowest n bits of x; all higher bits set to 0.
//
// x |= (1 << n); // forces nth bit of x to be 1. all other bits left alone.
//
// x ^= (1 << n); // toggles nth bit of x. all other bits left alone.
//
// x = ~x; // toggles ALL the bits in x.

