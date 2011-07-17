#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ruby/ruby.h>
#include "tnetstrings.h"

%%{
  machine tnetstrings;
  access parser->;

  action mark_ends {
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

  action collect_payload_size {
    parser->payload_size *= 10;
    parser->payload_size += CTOI(fc);
  }

  # -*- boolean (!) -*- #
  action wrap_true  { parser->result = TNETS_WRAP_TRUE;  }
  action wrap_false { parser->result = TNETS_WRAP_FALSE; }

  # -*- null (~) -*- #
  action wrap_null  { parser->result = Qnil;   }

  # -*- number (#) -*- #
  action neg {
    parser->seen_neg = 1;
  }

  action collect_num {
    parser->num_builder *= 10;
    parser->num_builder += CTOI(fc);
  }

  action wrap_num {
    if (parser->seen_neg) parser->num_builder *= -1;
    parser->result = TNETS_WRAP_NUM(parser->num_builder);
  }

  # -*- string (,) -*- #
  action wrap_str {
    parser->result = TNETS_WRAP_STR(p+1, parser->payload_size);
  }

  action parse_dict { }
  action parse_arr {
    parse_chunk(p, parser->payload_size);
  }

  action error {
    printf("error!\n"); // TODO: real error handling
  }

  # parses the size spec at the start of the payload
  tnets_size = digit{,10} $collect_payload_size;
  colon = ':' @mark_ends;

  # primitives
  tnets_num  = '#' ('-' @neg)? (digit+ $collect_num) %/wrap_num;
  tnets_str  = ',' @wrap_str;
  # NB: any string that is not "true" will return "false".
  tnets_bool = '!' ('true' %/wrap_true | !'true' %/wrap_false);
  tnets_null = '~' %/wrap_null;

  # recursive structures
  tnets_dict = '}' @parse_dict;
  tnets_arr  = ']' @parse_arr;

  main := tnets_size colon (
    tnets_num  |
    tnets_str  |
    tnets_dict |
    tnets_bool |
    tnets_null
  ) @err(error);
}%%

%% write data;

int tnets_parser_init(tnets_parser *parser) {
  %% write init;
}

int parse_chunk(tnets_parser *parser, char *str, int size) {
  char *p = str;
  // pe gets re-set once we've parsed the length.
  // set to 10 characters here because that's the maximum
  // length of the length spec.
  char *pe = p + 11;
  char *eof;

  %% write exec;

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
