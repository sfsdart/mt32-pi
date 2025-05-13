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
#include "lcd/drivers/st7789.h"

#define FORE_COLOR                ST7789_COLOR (31, 31, 15)       // any color
#define BACK_COLOR		ST7789_COLOR (0, 0, 0)


CST7789::CST7789(CSPIMaster* pSPIMaster, u8 nAddress, u16 nWidth, u16 nHeight)
        : CLCD(nWidth, nHeight),
	  m_Display(pSPIMaster, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          m_nAddress(nAddress),
	  m_nWidth(nWidth),
	  m_nHeight(nHeight),

          m_FrameBuffers{{0x40, {0}}, {0x40, {0}}},
          m_nCurrentFrameBuffer(0)
{
}



bool CST7789::Initialize()
{
	bool bOk = TRUE;

	bOk = m_Display.Initialize();

	return bOk;
}

void CST7789::Print(const char* pText, u8 nCursorX, u8 nCursorY, bool bClearLine, bool bImmediate)
{
	;
}

void CST7789::WriteFrameBuffer(bool bForceFullUpdate) const
{
        // Reset start line
        //WriteCommand(SetStartLine | 0x00);

        // Compare two framebuffers
        //const size_t nFrameBufferSize = m_nWidth * m_nHeight / 8;
        //const bool bNeedsUpdate = bForceFullUpdate || memcmp(m_FrameBuffers[0].FrameBuffer, m_FrameBuffers[1].FrameBuffer, nFrameBufferSize) != 0;

        // Copy entire framebuffer
        //if (bNeedsUpdate)
        //        m_pI2CMaster->Write(m_nAddress, &m_FrameBuffers[m_nCurrentFrameBuffer], sizeof(TFrameBufferUpdatePacket::DataControlByte) + nFrameBufferSize);
}

void CST7789::SwapFrameBuffers()
{
        // Make other framebuffer current
        m_nCurrentFrameBuffer = (m_nCurrentFrameBuffer + 1) % 2;
}


void CST7789::SetPixel(u8 nX, u8 nY)
{
        nX %= m_nWidth;
        nY %= m_nHeight;

	m_Display.SetPixel(nX, nY, MY_COLOR);
}

void CST7789::ClearPixel(u8 nX, u8 nY)
{
        // Ensure range is within 0-127 for x, 0-63 for y
        nX &= 0x7F;
        nY &= 0x3F;

        u8* pFrameBuffer = m_FrameBuffers[m_nCurrentFrameBuffer].FrameBuffer;
        pFrameBuffer[((nY & 0xF8) << 4) + nX] &= ~(1 << (nY & 7));
}

void CST7789::DrawFilledRect(u8 nX1, u8 nY1, u8 nX2, u8 nY2, bool bImmediate)
{


}

void CST7789::DrawChar(char chChar, u8 nCursorX, u8 nCursorY, bool bInverted, bool bDoubleWidth)
{

}

void CST7789::Flip()
{
        WriteFrameBuffer();
        SwapFrameBuffers();
}

void CST7789::DrawImage(TImage Image, bool bImmediate)
{

}

void CST7789::Clear(bool bImmediate)
{
	if (!bImmediate)
		return;

	CTimer::SimpleMsDelay(50);
}

void CST7789::SetBacklightState(bool bEnabled)
{

}

