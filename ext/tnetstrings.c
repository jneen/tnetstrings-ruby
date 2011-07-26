#include "tnetstrings.h"

static TNETS_VALUE
eTnetsParserError;

#define TNETS_PARSER_ERROR(msg) rb_raise(eTnetsParserError, msg)

TNETS_VALUE tnets_render_number(char* payload, size_t len);
TNETS_VALUE tnets_render_string(char* payload, size_t len);
TNETS_VALUE tnets_render_bool  (char* payload, size_t len);
TNETS_VALUE tnets_render_null  (char* payload, size_t len);
TNETS_VALUE tnets_render_list  (char* payload, size_t len);
TNETS_VALUE tnets_render_dict  (char* payload, size_t len);

size_t tnets_size_spec(char* data, size_t len, char** payload);

TNETS_VALUE tnets_parse_dict_key(char* data, size_t len, char** remain);
TNETS_VALUE tnets_parse(char* data, size_t len, char** remain);

TNETS_VALUE rb_tnets_parse(TNETS_VALUE self, TNETS_VALUE rbstr);

// since no checking is done on strings, just pass it right along
// to the wrapper.
#define tnets_render_string TNETS_WRAP_STRING

TNETS_VALUE tnets_render_number(char* payload, size_t len) {
  size_t i;
  int number = 0; // TODO: use a type that can handle
                  // larger numbers without wrapping.
  unsigned short int negative = 0;

  if (payload[0] == '-') {
    negative = 1;
    payload++;
    len--;
  }

  for(i = 0; i < len; i++) {
    if (IS_NUMERIC(payload[i])) {
      number *= 10;
      number += CTOI(payload[i]);
    }
    else {
      TNETS_PARSER_ERROR("Non-numeric character in a tnets number");
    }
  }

  if (negative) {
    number *= -1;
  }

  return TNETS_WRAP_NUMBER(number);
}

TNETS_VALUE tnets_render_bool(char* payload, size_t len) {
  // TODO: do this better.
  if (len != 4) return TNETS_WRAP_FALSE;
  size_t i;
  for (i = 0; i < len; i++) {
    if (payload[i] != "true"[i]) {
      return TNETS_WRAP_FALSE;
    }
  }

  return TNETS_WRAP_TRUE;
}

TNETS_VALUE tnets_render_null(char* payload, size_t len) {
  if (len != 0) TNETS_PARSER_ERROR("null must have an empty payload.");

  return TNETS_WRAP_NULL;
}

TNETS_VALUE tnets_render_list(char* payload, size_t len) {
  char *tmp_payload = payload;
  size_t sub_len;
  TNETS_VALUE list = TNETS_NEW_LIST();

  while (len > 0) {
    TNETS_LIST_PUSH(
      list,
      tnets_parse(payload, len, &tmp_payload)
    );

    len -= (tmp_payload - payload);
    payload = tmp_payload;
  }

  return list;
}

#define tnets_render_dict_key TNETS_WRAP_DICT_KEY

TNETS_VALUE tnets_render_dict(char* payload, size_t len) {
  char *tmp_payload = payload;
  TNETS_VALUE dict = TNETS_NEW_DICT();
  while(len > 0) {
    TNETS_VALUE key = tnets_parse_dict_key(payload, len, &tmp_payload);
    len -= (tmp_payload - payload);
    payload = tmp_payload;

    TNETS_DICT_SET(dict, key,
      tnets_parse(payload, len, &tmp_payload)
    );

    len -= (tmp_payload - payload);
    payload = tmp_payload;
  }

  return dict;
}

size_t
tnets_size_spec(char *data, size_t len, char **payload) {
  size_t i;
  size_t size = 0;

  // only scan 11 characters (10 for length spec + 1 for colon)
  size_t scan_limit = (len < 11) ? len : 11;

  for (i = 0; i < scan_limit; i++) {
    if (IS_NUMERIC(data[i])) {
      size *= 10;
      size += CTOI(data[i]);
    }
    else if (data[i] == ':') {
      if (i + size > len + 1) {
        TNETS_PARSER_ERROR("length spec longer than given string");
      }

      if (payload != NULL) {
        *payload = data + i + 1; // add one to skip over the colon
      }
      return size;
    }
    else {
      TNETS_PARSER_ERROR("non-numeric character in length spec");
    }
  }

  TNETS_PARSER_ERROR("length spec more than 10 characters");

  return 0;
}

TNETS_VALUE
tnets_parse_dict_key(char* data, size_t len, char** remain) {
  char* payload;
  size_t payload_len = tnets_size_spec(data, len, &payload);
  if (remain != NULL) *remain = payload + payload_len + 1;

  if (payload[payload_len] != tnets_tag_string) {
    TNETS_PARSER_ERROR("non-string dict keys are not supported");
  }

  return tnets_render_dict_key(payload, payload_len);
}

TNETS_VALUE
tnets_parse(char *data, size_t len, char** remain) {
  char *payload = NULL;
  size_t payload_len;
  tnets_type_tag type = tnets_tag_invalid;

  payload_len = tnets_size_spec(data, len, &payload);

  if (remain != NULL) *remain = payload + payload_len + 1;

  type = payload[payload_len];

  switch(type) {
    case tnets_tag_string: return tnets_render_string(payload, payload_len);
    case tnets_tag_number: return tnets_render_number(payload, payload_len);
    case tnets_tag_null:   return tnets_render_null(payload, payload_len);
    case tnets_tag_bool:   return tnets_render_bool(payload, payload_len);
    case tnets_tag_list:   return tnets_render_list(payload, payload_len);
    case tnets_tag_dict:   return tnets_render_dict(payload, payload_len);
    default:
      TNETS_PARSER_ERROR("Invalid type tag");
  }
}

VALUE rb_tnets_parse(VALUE self, VALUE rbstr) {
  char* data = RSTRING_PTR(rbstr);
  size_t len = RSTRING_LEN(rbstr);
  return tnets_parse(data, len, NULL);
}

void
Init_tnetstrings() {
  VALUE mTnetstrings = rb_define_module("TNETS");

  rb_define_method(mTnetstrings, "c_parse", rb_tnets_parse, 1);
  eTnetsParserError =
    rb_define_class_under(mTnetstrings, "ParserError", rb_eIOError);
}
