
#line 1 "ext/tnetstrings.c.rl"
#include <string.h>
#include <stdio.h>
#include <ruby/ruby.h>

// // stolen from flori's json
// #define LEN(AT, FPC) (FPC - buffer - parser->AT)
// #define MARK(M,FPC) (parser->M = (FPC) - buffer)
// #define PTR_TO(F) (buffer + parser->F)

// struct fsm {
//   int cs;
//   int p;
//   int pe;
// };


#line 56 "ext/tnetstrings.c.rl"



#line 24 "ext/tnetstrings.c"
static const char _foo_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8
};

static const char _foo_eof_actions[] = {
	0, 17, 17, 17, 17, 17, 17, 17, 
	17, 17, 17, 17, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const int foo_start = 1;
static const int foo_first_final = 21;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 59 "ext/tnetstrings.c.rl"

VALUE parse_int(char* p, int size) {
  int out = 0, i;
  // TODO: this is totally unsafe...
  // check to make sure the things are actually digits.
  // or roll this into the parser?
  for (i=0; i<size; i++) {
    out *= 10;
    out += (p[i] - '0');
  }

  return INT2FIX(out);
}

VALUE parse(char* str) {
  int cs, size = 0;
  char* p = str;
  char* pe = p + strlen(p) + 1;
  char* eof;
  char* payload;

  VALUE out = Qnil;

  
#line 69 "ext/tnetstrings.c"
	{
	cs = foo_start;
	}

#line 83 "ext/tnetstrings.c.rl"
  
#line 76 "ext/tnetstrings.c"
	{
	const char *_acts;
	unsigned int _nacts;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	switch ( cs ) {
case 1:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr1;
	goto tr0;
case 0:
	goto _out;
case 2:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr3;
	goto tr0;
case 3:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr4;
	goto tr0;
case 4:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr5;
	goto tr0;
case 5:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr6;
	goto tr0;
case 6:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr7;
	goto tr0;
case 7:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr8;
	goto tr0;
case 8:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr9;
	goto tr0;
case 9:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr10;
	goto tr0;
case 10:
	if ( (*p) == 58 )
		goto tr2;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr11;
	goto tr0;
case 11:
	if ( (*p) == 58 )
		goto tr2;
	goto tr0;
case 12:
	switch( (*p) ) {
		case 33: goto tr12;
		case 35: goto tr14;
		case 44: goto tr15;
		case 125: goto tr16;
		case 126: goto tr17;
	}
	goto tr13;
case 13:
	switch( (*p) ) {
		case 102: goto tr18;
		case 116: goto tr19;
	}
	goto tr13;
case 14:
	if ( (*p) == 97 )
		goto tr20;
	goto tr13;
case 15:
	if ( (*p) == 108 )
		goto tr21;
	goto tr13;
case 16:
	if ( (*p) == 115 )
		goto tr22;
	goto tr13;
case 17:
	if ( (*p) == 101 )
		goto tr23;
	goto tr13;
case 21:
	goto tr13;
case 18:
	if ( (*p) == 114 )
		goto tr24;
	goto tr13;
case 19:
	if ( (*p) == 117 )
		goto tr25;
	goto tr13;
case 20:
	if ( (*p) == 101 )
		goto tr26;
	goto tr13;
	}

	tr13: cs = 0; goto _again;
	tr0: cs = 0; goto f0;
	tr1: cs = 2; goto f1;
	tr3: cs = 3; goto f1;
	tr4: cs = 4; goto f1;
	tr5: cs = 5; goto f1;
	tr6: cs = 6; goto f1;
	tr7: cs = 7; goto f1;
	tr8: cs = 8; goto f1;
	tr9: cs = 9; goto f1;
	tr10: cs = 10; goto f1;
	tr11: cs = 11; goto f1;
	tr2: cs = 12; goto f2;
	tr12: cs = 13; goto _again;
	tr18: cs = 14; goto _again;
	tr20: cs = 15; goto _again;
	tr21: cs = 16; goto _again;
	tr22: cs = 17; goto _again;
	tr19: cs = 18; goto _again;
	tr24: cs = 19; goto _again;
	tr25: cs = 20; goto _again;
	tr14: cs = 21; goto f3;
	tr15: cs = 21; goto f4;
	tr16: cs = 21; goto f5;
	tr17: cs = 21; goto f6;
	tr23: cs = 21; goto f7;
	tr26: cs = 21; goto f8;

	f2: _acts = _foo_actions + 1; goto execFuncs;
	f1: _acts = _foo_actions + 3; goto execFuncs;
	f3: _acts = _foo_actions + 5; goto execFuncs;
	f4: _acts = _foo_actions + 7; goto execFuncs;
	f5: _acts = _foo_actions + 9; goto execFuncs;
	f8: _acts = _foo_actions + 11; goto execFuncs;
	f7: _acts = _foo_actions + 13; goto execFuncs;
	f6: _acts = _foo_actions + 15; goto execFuncs;
	f0: _acts = _foo_actions + 17; goto execFuncs;

execFuncs:
	_nacts = *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 18 "ext/tnetstrings.c.rl"
	{ }
	break;
	case 1:
#line 20 "ext/tnetstrings.c.rl"
	{
    size *= 10;
    size += (*p - '0');
  }
	break;
	case 2:
#line 25 "ext/tnetstrings.c.rl"
	{
    out = parse_int(p, size);
  }
	break;
	case 3:
#line 28 "ext/tnetstrings.c.rl"
	{
    out = rb_str_new(p+1, size);
  }
	break;
	case 4:
#line 32 "ext/tnetstrings.c.rl"
	{ }
	break;
	case 5:
#line 34 "ext/tnetstrings.c.rl"
	{ out = Qtrue; }
	break;
	case 6:
#line 35 "ext/tnetstrings.c.rl"
	{ out = Qfalse; }
	break;
	case 7:
#line 36 "ext/tnetstrings.c.rl"
	{ out = Qnil; }
	break;
	case 8:
#line 40 "ext/tnetstrings.c.rl"
	{ printf("ERR"); }
	break;
#line 285 "ext/tnetstrings.c"
		}
	}
	goto _again;

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _foo_actions + _foo_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 8:
#line 40 "ext/tnetstrings.c.rl"
	{ printf("ERR"); }
	break;
#line 306 "ext/tnetstrings.c"
		}
	}
	}

	_out: {}
	}

#line 84 "ext/tnetstrings.c.rl"

  return out;
}

VALUE rb_parse(VALUE self, VALUE rbstr) {
  return parse(RSTRING_PTR(rbstr));
}

void Init_tnetstrings() {
  VALUE module = rb_define_module("TnetstringsCMethods");

  rb_define_method(module, "c_parse", rb_parse, 1);
}
