//
// st7789.h
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

#ifndef _st7789_h
#define _st7789_h

#include <circle/spimaster.h>
#include <circle/types.h>

#include "lcd/lcd.h"
#include <display/st7789display.h>
#include "synth/mt32synth.h"
#include "utility.h"

class CST7789 : public CLCD
{
public:
	CST7789(CSPIMaster* pSPIMaster, u8 nAddress = 0x00, u16 nWidth = 240, u16 nHeight = 280);

	// CLCD
	virtual bool Initialize() override;
	virtual TType GetType() const override { return TType::Graphical; };

	// Character functions
	virtual void Clear(bool bImmediate = false) override;
	virtual void Print(const char* pText, u8 nCursorX, u8 nCursorY, bool bClearLine = false, bool bImmediate = false) override;

	// Graphics functions
	virtual void SetPixel(u8 nX, u8 nY) override;
	virtual void ClearPixel(u8 nX, u8 nY) override;
	virtual void DrawFilledRect(u8 nX1, u8 nY1, u8 nX2, u8 nY2, bool bImmediate = false) override;
	virtual void DrawChar(char chChar, u8 nCursorX, u8 nCursorY, bool bInverted = false, bool bDoubleWidth = false) override;
	virtual void DrawImage(TImage Image, bool bImmediate = false) override;
	virtual void Flip() override;

	virtual void SetBacklightState(bool bEnabled) override;

protected:
	struct TFrameBufferUpdatePacket
	{
		u8 FrameBuffer[240 * 280];
	}
	PACKED;

	virtual void WriteFrameBuffer(bool bForceFullUpdate = false) const;
	void SwapFrameBuffers();

	CST7789Display m_Display;
	u8 m_nAddress;
	u16 m_nWidth;
	u16 m_nHeight;

	// Double framebuffers
	TFrameBufferUpdatePacket m_FrameBuffers[2];
	u8 m_nCurrentFrameBuffer;
};

#endif
