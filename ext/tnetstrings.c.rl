#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ruby/ruby.h>
#include "tnetstrings.h"

static VALUE eTnetsParserError;

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

    if (pe > str + size) {
      TNETS_ERROR("Holy crap we overfloweded the buffer");
    }
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

  action wrap_dict_key {
    parser->result = TNETS_WRAP_DICT_KEY(p+1, parser->payload_size);
  }

  action parse_dict {
    TNETS_T dict = TNETS_NEW_DICT;
    TNETS_T key;
    tnets_parser* sub_parser = tnets_parser_new();
    char* sub_data = parser->payload;
    int sub_size = parser->payload_size;

    // TODO: seriously DRY this up, if only with #defines
    do {
      // XXX HACK.  Ask the ragel guys for a better way to do this.
      // This sets the "current state" to the entry point for the
      // dict_key machine, which only accepts strings.
      sub_parser->cs = tnetstrings_en_dict_key;
      tnets_parser_chunk(sub_parser, sub_data, sub_size);
      key = sub_parser->result;

      sub_data += (sub_parser->payload_size + 2 + 1);
      sub_size -= (sub_parser->payload_size + 2 + 1);
      tnets_parser_clear(sub_parser);

      tnets_parser_chunk(sub_parser, sub_data, sub_size);
      TNETS_DICT_ADD(dict, key, sub_parser->result);

      sub_data += (sub_parser->payload_size + 2 + 1);
      sub_size -= (sub_parser->payload_size + 2 + 1);
      tnets_parser_clear(sub_parser);
    } while(sub_size > 0);

    free(sub_parser);

    parser->result = dict;
  }

  action parse_arr {
    TNETS_T arr = TNETS_NEW_ARR;
    tnets_parser* sub_parser = tnets_parser_new();
    char* sub_data = parser->payload;
    int sub_size = parser->payload_size;
    do {
      tnets_parser_chunk(sub_parser, sub_data, sub_size);
      TNETS_ARR_PUSH(arr, sub_parser->result);

      sub_data += (sub_parser->payload_size + 2 + 1);
      sub_size -= (sub_parser->payload_size + 2 + 1);
      // reset current state and such
      tnets_parser_clear(sub_parser);

    } while(sub_size > 0);
    free(sub_parser);

    parser->result = arr;
  }

  action error {
    printf("error!\n");
    printf("p: [%s]\n", p);
    printf("pe: [%s]\n", pe);
    printf("str: [%s]\n", str);
    TNETS_ERROR("parse error"); // TODO: more helpful messages
  }

  # kind of a hack, but represents the end of the chunk.
  end = (any @error)?;

  # parses the size spec at the start of the payload
  tnets_size = digit+ $collect_payload_size;
  colon = ':' @mark_ends;

  # primitives
  tnets_num  = '#' (('-' @neg)? (digit+ $collect_num)) %/wrap_num <: end;
  tnets_str  = ',' @wrap_str;
  tnets_dict_key = ',' @wrap_dict_key;
  # NB: any string that is not "true" will return "false".
  tnets_bool = '!' ('true' %/wrap_true | !'true' %/wrap_false);
  tnets_null = ('~' %/wrap_null) end;

  # recursive structures
  tnets_dict = '}' @parse_dict;
  tnets_arr  = ']' @parse_arr;

  main := (
    tnets_size colon (
      tnets_dict |
      tnets_arr  |
      tnets_num  |
      tnets_str  |
      tnets_bool |
      tnets_null
    )
  ) @err(error);

  dict_key := (tnets_size colon tnets_dict_key) @err(error);
}%%

%% write data;

int tnets_parser_init(tnets_parser *parser) {
  %% write init;
}

int tnets_parser_clear(tnets_parser *parser) {
  tnets_parser_init(parser);
  parser->num_builder = 0;
  parser->seen_neg = 0;
  parser->result = TNETS_WRAP_NULL;
  parser->payload = NULL;
  parser->payload_size = 0;
}

int tnets_parser_chunk(tnets_parser *parser, char *str, int size) {
  char *p = str;
  // pe gets re-set once we've parsed the length.
  // set to 10 characters here because that's the maximum
  // length of the length spec.  Also add one for the colon.
  char *pe = p + ( (size < 11) ? size : 11 );
  char *eof = pe;

  %% write exec;

  return 0;
}

tnets_parser *tnets_parser_new(void) {
  tnets_parser *parser = calloc(sizeof(tnets_parser), 1);
  tnets_parser_init(parser);
  return parser;
}

tnets_parser *parse_str(char *str, int size) {
  tnets_parser *parser = tnets_parser_new();
  tnets_parser_chunk(parser, str, size);
  return parser;
}

VALUE rb_parse_tnets(VALUE self, VALUE rbstr) {
  char *tnets = RSTRING_PTR(rbstr);
  int len = RSTRING_LEN(rbstr);

  tnets_parser *parser = parse_str(RSTRING_PTR(rbstr), len);

  VALUE result = parser->result;
  free(parser);

  return result;
}

void Init_tnetstrings() {
  VALUE mTnetstrings = rb_define_module("TNETS");

  rb_define_method(mTnetstrings, "c_parse", rb_parse_tnets, 1);
  eTnetsParserError = rb_define_class_under(mTnetstrings, "ParserError", rb_eIOError);
}
