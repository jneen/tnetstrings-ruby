#include <ruby/ruby.h>
// #include <stdlib.h>
// #include <string.h>
#include <stdio.h>
#include <ruby/ruby.h>

typedef enum tnets_type_tag_e {
  tnets_tag_string  = ',',
  tnets_tag_number  = '#',
  // tnets_tag_float   = '^', // coming soon
  tnets_tag_bool    = '!',
  tnets_tag_null    = '~',
  tnets_tag_dict    = '}',
  tnets_tag_list    = ']',
  tnets_tag_invalid = 'Z',
} tnets_type_tag;

#define IS_NUMERIC(ch) ('0' <= ch && ch <= '9')
#define CTOI(ch) (ch - '0');

#define TNETS_VALUE VALUE

#define TNETS_WRAP_STRING(s,l) (rb_str_new(s,l))
#define TNETS_WRAP_NUMBER INT2FIX
#define TNETS_WRAP_NULL Qnil
#define TNETS_WRAP_TRUE Qtrue
#define TNETS_WRAP_FALSE Qfalse
// TODO: find a better way to symbolize length-specified
// strings.
#define TNETS_WRAP_DICT_KEY(k,size) (ID2SYM(rb_to_id(TNETS_WRAP_STRING(k,size))))

#define TNETS_NEW_LIST rb_ary_new
#define TNETS_LIST_PUSH(a,v) rb_ary_push(a,v)
#define TNETS_NEW_DICT rb_hash_new
#define TNETS_DICT_SET(dict,key,val) (rb_hash_aset(dict,key,val))

/**
*  Parse an object off the front of a tnetstring.
*  Returns a pointer to the parsed object, or NULL if an error occurs.
*  The third argument is an output parameter; if non-NULL it will
*  receive the unparsed remainder of the string.
*/
TNETS_VALUE
tnets_parse(char *data, size_t len, char** remain);
