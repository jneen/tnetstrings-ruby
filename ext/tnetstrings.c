
#line 1 "ext/tnetstrings.c.rl"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ruby/ruby.h>
#include "tnetstrings.h"


#line 89 "ext/tnetstrings.c.rl"



#line 15 "ext/tnetstrings.c"
static const char _tnetstrings_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10
};

static const char _tnetstrings_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 21, 21, 21, 7, 
	7, 7, 7, 7, 5, 15, 0, 9
};

static const int tnetstrings_start = 1;
static const int tnetstrings_first_final = 15;
static const int tnetstrings_error = 0;

static const int tnetstrings_en_main = 1;


#line 92 "ext/tnetstrings.c.rl"

int tnets_parser_init(tnets_parser *parser) {
  
#line 39 "ext/tnetstrings.c"
	{
	 parser->cs = tnetstrings_start;
	}

#line 95 "ext/tnetstrings.c.rl"
}

int parse_chunk(tnets_parser *parser, char *str, int size) {
  char *p = str;
  // pe gets re-set once we've parsed the length.
  // set to 10 characters here because that's the maximum
  // length of the length spec.
  char *pe = p + 11;
  char *eof;

  
#line 56 "ext/tnetstrings.c"
	{
	const char *_acts;
	unsigned int _nacts;

	if ( p == pe )
		goto _test_eof;
	if (  parser->cs == 0 )
		goto _out;
_resume:
	switch (  parser->cs ) {
case 1:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr0;
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr3;
	goto tr1;
case 3:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr4;
	goto tr1;
case 4:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr5;
	goto tr1;
case 5:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr6;
	goto tr1;
case 6:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr7;
	goto tr1;
case 7:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr8;
	goto tr1;
case 8:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr9;
	goto tr1;
case 9:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr10;
	goto tr1;
case 10:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr11;
	goto tr1;
case 11:
	if ( (*p) == 58 )
		goto tr2;
	goto tr1;
case 12:
	switch( (*p) ) {
		case 33: goto tr13;
		case 35: goto tr14;
		case 44: goto tr15;
		case 125: goto tr16;
		case 126: goto tr17;
	}
	goto tr12;
case 15:
	if ( (*p) == 116 )
		goto tr21;
	goto tr20;
case 16:
	goto tr20;
case 17:
	if ( (*p) == 114 )
		goto tr22;
	goto tr20;
case 18:
	if ( (*p) == 117 )
		goto tr23;
	goto tr20;
case 19:
	if ( (*p) == 101 )
		goto tr24;
	goto tr20;
case 20:
	goto tr20;
case 13:
	if ( (*p) == 45 )
		goto tr18;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr19;
	goto tr12;
case 14:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr19;
	goto tr12;
case 21:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr19;
	goto tr1;
case 22:
	goto tr1;
case 23:
	goto tr1;
	}

	tr1:  parser->cs = 0; goto _again;
	tr12:  parser->cs = 0; goto f2;
	tr0:  parser->cs = 2; goto f0;
	tr3:  parser->cs = 3; goto f0;
	tr4:  parser->cs = 4; goto f0;
	tr5:  parser->cs = 5; goto f0;
	tr6:  parser->cs = 6; goto f0;
	tr7:  parser->cs = 7; goto f0;
	tr8:  parser->cs = 8; goto f0;
	tr9:  parser->cs = 9; goto f0;
	tr10:  parser->cs = 10; goto f0;
	tr11:  parser->cs = 11; goto f0;
	tr2:  parser->cs = 12; goto f1;
	tr14:  parser->cs = 13; goto _again;
	tr18:  parser->cs = 14; goto f5;
	tr13:  parser->cs = 15; goto _again;
	tr20:  parser->cs = 16; goto _again;
	tr21:  parser->cs = 17; goto _again;
	tr22:  parser->cs = 18; goto _again;
	tr23:  parser->cs = 19; goto _again;
	tr24:  parser->cs = 20; goto _again;
	tr19:  parser->cs = 21; goto f6;
	tr15:  parser->cs = 22; goto f3;
	tr16:  parser->cs = 22; goto f4;
	tr17:  parser->cs = 23; goto _again;

	f1: _acts = _tnetstrings_actions + 1; goto execFuncs;
	f0: _acts = _tnetstrings_actions + 3; goto execFuncs;
	f5: _acts = _tnetstrings_actions + 11; goto execFuncs;
	f6: _acts = _tnetstrings_actions + 13; goto execFuncs;
	f3: _acts = _tnetstrings_actions + 17; goto execFuncs;
	f4: _acts = _tnetstrings_actions + 19; goto execFuncs;
	f2: _acts = _tnetstrings_actions + 21; goto execFuncs;

execFuncs:
	_nacts = *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 11 "ext/tnetstrings.c.rl"
	{
    // this marks the start of the payload -
    // move ahead 2 for the colon and the type spec.
    parser->payload = p + 2;

    // this is a bit hacky, but I think it's the only way to do it.
    // only now do we know where the end is, since we've parsed the payload_size.
    // This will cause EOF actions to be triggered at the end of the payload.
    // TODO: eventually, have an option to read this from a stream,
    // which is arguably the whole point.
    eof = pe = parser->payload + parser->payload_size;

    // assert(pe < str + size, "Holy crap we overfloweded the buffer");
  }
	break;
	case 1:
#line 26 "ext/tnetstrings.c.rl"
	{
    parser->payload_size *= 10;
    parser->payload_size += CTOI((*p));
  }
	break;
	case 5:
#line 39 "ext/tnetstrings.c.rl"
	{
    parser->seen_neg = 1;
  }
	break;
	case 6:
#line 43 "ext/tnetstrings.c.rl"
	{
    parser->num_builder *= 10;
    parser->num_builder += CTOI((*p));
  }
	break;
	case 8:
#line 54 "ext/tnetstrings.c.rl"
	{
    parser->result = TNETS_WRAP_STR(p+1, parser->payload_size);
  }
	break;
	case 9:
#line 58 "ext/tnetstrings.c.rl"
	{ }
	break;
	case 10:
#line 63 "ext/tnetstrings.c.rl"
	{
    printf("error!\n"); // TODO: real error handling
  }
	break;
#line 273 "ext/tnetstrings.c"
		}
	}
	goto _again;

_again:
	if (  parser->cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _tnetstrings_actions + _tnetstrings_eof_actions[ parser->cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 2:
#line 32 "ext/tnetstrings.c.rl"
	{ parser->result = TNETS_WRAP_TRUE;  }
	break;
	case 3:
#line 33 "ext/tnetstrings.c.rl"
	{ parser->result = TNETS_WRAP_FALSE; }
	break;
	case 4:
#line 36 "ext/tnetstrings.c.rl"
	{ parser->result = Qnil;   }
	break;
	case 7:
#line 48 "ext/tnetstrings.c.rl"
	{
    if (parser->seen_neg) parser->num_builder *= -1;
    parser->result = TNETS_WRAP_NUM(parser->num_builder);
  }
	break;
	case 10:
#line 63 "ext/tnetstrings.c.rl"
	{
    printf("error!\n"); // TODO: real error handling
  }
	break;
#line 315 "ext/tnetstrings.c"
		}
	}
	}

	_out: {}
	}

#line 106 "ext/tnetstrings.c.rl"

  return 0;
}

VALUE rb_parse_tnets(VALUE self, VALUE rbstr) {
  char *tnets = RSTRING_PTR(rbstr);
  int len = RSTRING_LEN(rbstr);

  tnets_parser *parser = calloc(sizeof(tnets_parser), 1);
  tnets_parser_init(parser);
  parse_chunk(parser, tnets, len);

  return parser->result;
}

void Init_tnetstrings() {
  VALUE module = rb_define_module("TnetstringsCMethods");

  rb_define_method(module, "c_parse", rb_parse_tnets, 1);
}
