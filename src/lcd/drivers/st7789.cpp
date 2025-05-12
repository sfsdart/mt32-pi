//
// st7789.cpp
//
// mt32-pi - A baremetal MIDI synthesizer for Raspberry Pi
// Copyright (C) 2020-2023 Dale Whinham <daleyo@gmail.com>
//
// This file is part of mt32-pi.
//
// mt32-pi is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// mt32-pi is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// mt32-pi. If not, see <http://www.gnu.org/licenses/>.
//

#include <circle/logger.h>
#include <circle/timer.h>

#include "lcd/barchars.h"
#include "lcd/drivers/hd44780.h"

CST7789::CST7789(CSPIMaster* pSPIMaster, u8 nAddress, u8 nWidth, u8 nHeight, TLCDRotation Rotation)
        : CSSD1306(pI2CMaster, nAddress, nWidth, nHeight, Rotation)
{
}


bool CST7789::Initialize()
{

}

void CST7789::Print(const char* pText, u8 nCursorX, u8 nCursorY, bool bClearLine, bool bImmediate)
{
	;
}

void CST7789::Clear(bool bImmediate)
{
	if (!bImmediate)
		return;

	WriteCommand(0b0001);
	CTimer::SimpleMsDelay(50);
}

