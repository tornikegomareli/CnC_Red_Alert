/*
**	Command & Conquer Red Alert(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* $Header: /CounterStrike/CRC.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CRC.H                                                        *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 03/02/96                                                     *
 *                                                                                             *
 *                  Last Update : March 2, 1996 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#ifndef CRC_H
#define CRC_H

#include	<stdlib.h>

/*
**	The "bool" integral type was defined by the C++ comittee in
**	November of '94. Until the compiler supports this, use the following
**	definition.
*/
#ifndef __BORLANDC__
#ifndef TRUE_FALSE_DEFINED
#define TRUE_FALSE_DEFINED
enum {false=0,true=1};
typedef int bool;
#endif
#endif

/*
**	This is a CRC engine class. It will process submitted data and generate a CRC from it.
**	Well, actually, the value returned is not a true CRC. However, it shares the same strength
**	characteristic and is faster to generate than the traditional CRC. This object is treated like
**	a method class. If it is called as a function (using the function operator), it will return
**	the CRC value. There are other function operators to submit data for processing.
*/
class CRCEngine {
	public:

		// Constructor for CRC engine (it can have an override initial CRC value).
		CRCEngine(long initial=0) : CRC((int32_t)initial), Index(0) {
			StagingBuffer.Composite = 0;
		};

		// Fetches CRC value.
		long operator() (void) const {return((long)Value());};

		// Submits one byte sized datum to the CRC accumulator.
		void operator() (char datum);

		// Submits an arbitrary buffer to the CRC accumulator.
		long operator() (void const * buffer, int length);

		// Implicit conversion operator so this object appears like a 'long integer'.
		operator long(void) const {return((long)Value());};

	protected:

		bool Buffer_Needs_Data(void) const {
			return(Index != 0);
		};

		int32_t Value(void) const {
			if (Buffer_Needs_Data()) {
				/* 32-bit rotate left by 1 + staging buffer */
				uint32_t v = (uint32_t)CRC;
				v = (v << 1) | (v >> 31);
				return((int32_t)(v + (uint32_t)StagingBuffer.Composite));
			}
			return(CRC);
		};

		/*
		**	Current CRC accumulator — MUST be 32-bit to match MIX file format.
		*/
		int32_t CRC;

		int Index;

		/*
		**	Staging buffer for partial data. MUST be 4 bytes (32-bit) to match
		**	the original Watcom long size used in MIX file CRC computation.
		*/
		union {
			int32_t Composite;
			char Buffer[4];
		} StagingBuffer;
};

#endif

