//
//  tokens.h
//  Fission
//
//  Created by C0deH4cker on 3/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FSN_TOKENS_H_
#define _FSN_TOKENS_H_

#define TOK_SPAWNER_UP				'U'
#define TOK_SPAWNER_LEFT			'L'
#define TOK_SPAWNER_DOWN			'D'
#define TOK_SPAWNER_RIGHT			'R'

#define TOK_DIR_UP					'W'
#define TOK_DIR_LEFT				']'
#define TOK_DIR_DOWN				'M'
#define TOK_DIR_RIGHT				'['

#define TOK_MIRROR_URDL				'/'
#define TOK_MIRROR_ULDR				'\\'
#define TOK_MIRROR_VERTICAL			'|'
#define TOK_MIRROR_HORIZONTAL		'-'
#define TOK_MIRROR_TURN_LEFT		'Z'
#define TOK_MIRROR_TURN_RIGHT		'S'
#define TOK_MIRROR_RANDOM			'#'
#define TOK_MIRROR_ENERGY_URDL		'%'
#define TOK_MIRROR_ENERGY_ULDR		'&'

#define TOK_PARTIAL_CLONER			'X'
#define TOK_PARTIAL_SPLITTER		':'

#define TOK_STACK					'K'

#define TOK_QUEUE					'Q'

#define TOK_CLONER_UP				'A'
#define TOK_CLONER_LEFT				'{'
#define TOK_CLONER_DOWN				'Y'
#define TOK_CLONER_RIGHT			'}'

#define TOK_WEDGE_UP				'^'
#define TOK_WEDGE_LEFT				'<'
#define TOK_WEDGE_DOWN				'V'
#define TOK_WEDGE_RIGHT				'>'

#define TOK_IO_NEWLINE				'N'
#define TOK_IO_OUTCHAR				'!'
#define TOK_IO_ENDCHAR				'O'
#define TOK_IO_INCHAR				'?'
#define TOK_IO_OUTSTR				'"'

#define TOK_TERMINATOR				'*'

#define TOK_DESTROY					';'
#define TOK_INCMASS					'+'
#define TOK_DECMASS					'_'
#define TOK_INCENERGY				'$'
#define TOK_DECENERGY				'~'
#define TOK_SWAP					'@'
#define TOK_JUMP					'J'
#define TOK_LITERAL					'\''

#endif /* _FSN_TOKENS_H_ */
