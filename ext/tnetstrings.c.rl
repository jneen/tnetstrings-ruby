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

%%{
  machine foo;
  action read_buf { }

  action collect_size {
    size *= 10;
    size += (*p - '0');
  }

  action parse_int {
    out = parse_int(p, size);
  }
  action parse_str {
    out = rb_str_new(p+1, size);
  }

  action parse_dict { }
  action parse_arr { }
  action parse_true  { out = Qtrue; }
  action parse_false { out = Qfalse; }
  action parse_null  { out = Qnil; }

  # parses the size spec at the start of the payload
  tnets_size = digit{,10} $collect_size;
  colon = ':' @read_buf @err{ printf("ERR"); };

  tnets_int  = '#' @parse_int;
  tnets_str  = ',' @parse_str;
  tnets_dict = '}' @parse_dict;
  tnets_arr  = ']' @parse_arr;
  tnets_bool = '!' ('true' @parse_true | 'false' @parse_false);
  tnets_null = '~' @parse_null;

  main := tnets_size colon (
    tnets_int  |
    tnets_str  |
    tnets_dict |
    tnets_bool |
    tnets_null
  );
}%%

%% write data;

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

  %% write init;
  %% write exec;

  return out;
}

VALUE rb_parse(VALUE self, VALUE rbstr) {
  return parse(RSTRING_PTR(rbstr));
}

void Init_tnetstrings() {
  VALUE module = rb_define_module("TnetstringsCMethods");

  rb_define_method(module, "c_parse", rb_parse, 1);
}
