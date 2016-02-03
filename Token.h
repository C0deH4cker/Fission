//
//  Token.h
//  Fission
//
//  Created by C0deH4cker on 3/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef FSN_TOKENS_H
#define FSN_TOKENS_H

namespace fsn {
	enum class Token: char {
		EMPTY                   = ' ',
		
		SPAWNER_UP              = 'U',
		SPAWNER_LEFT            = 'L',
		SPAWNER_DOWN            = 'D',
		SPAWNER_RIGHT           = 'R',
		
		DIR_UP                  = 'W',
		DIR_LEFT                = ']',
		DIR_DOWN                = 'M',
		DIR_RIGHT               = '[',
		
		MIRROR_URDL             = '/',
		MIRROR_ULDR             = '\\',
		MIRROR_VERTICAL         = '|',
		MIRROR_HORIZONTAL       = '-',
		MIRROR_TURN_LEFT        = 'Z',
		MIRROR_TURN_RIGHT       = 'S',
		MIRROR_RANDOM           = '#',
		MIRROR_ENERGY_URDL      = '%',
		MIRROR_ENERGY_ULDR      = '&',
		
		PARTIAL_CLONER          = 'X',
		PARTIAL_SPLITTER        = ':',
		
		STACK                   = 'K',
		QUEUE                   = 'Q',
		ARRAY_DATA              = 'E', //TODO
		ARRAY_CODE              = 'P', //TODO
		
		CLONER_UP               = 'A',
		CLONER_LEFT             = '{',
		CLONER_DOWN             = 'Y',
		CLONER_RIGHT            = '}',
		
		WEDGE_UP                = '^',
		WEDGE_LEFT              = '<',
		WEDGE_DOWN              = 'V',
		WEDGE_RIGHT             = '>',
		
		IO_NEWLINE              = 'N',
		IO_OUTCHAR              = '!',
		IO_ENDCHAR              = 'O',
		IO_INCHAR               = '?',
		IO_OUTSTR               = '"',
		
		TERMINATOR              = '*',
		DESTROY                 = ';',
		
		INCMASS                 = '+',
		DECMASS                 = '_',
		INCENERGY               = '$',
		DECENERGY               = '~',
		INVENERGY               = 'I',
		SWAP                    = '@',
		
		JUMP                    = 'J',
		LITERAL                 = '\'',
		
		CLEAR                   = 'C',
		SKIP                    = '`',
		
		TP_0                    = '0',
		TP_1                    = '1',
		TP_2                    = '2',
		TP_3                    = '3',
		TP_4                    = '4',
		TP_5                    = '5',
		TP_6                    = '6',
		TP_7                    = '7',
		TP_8                    = '8',
		TP_9                    = '9'
	};
}

#endif /* FSN_TOKENS_H */
