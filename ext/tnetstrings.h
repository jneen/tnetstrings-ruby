// poor man's dependency injection.
// if you'd like to use the ragel parser
// for another language or framework,
// override these.
#define TNETS_WRAP_NUM(n) (INT2FIX(n))
#define TNETS_WRAP_TRUE (Qtrue)
#define TNETS_WRAP_FALSE (Qfalse)
#define TNETS_WRAP_NIL (Qnil)
#define TNETS_WRAP_STR(s,size) (rb_str_new(s,size))
 
#define TNETS_NEW_ARR (rb_arr_new())
#define TNETS_ARR_PUSH(arr,el) (rb_arr_push(arr,el))

#define TNETS_NEW_DICT (rb_hash_new())
#define TNETS_DICT_ADD(dict,key,val) (rb_hash_add(dict,rb_intern(key),val))
#define TNETS_T VALUE

typedef struct tnets_parser {
  int cs;
  int payload_size;
  char *payload;
  TNETS_T result;

  int num_builder;
  unsigned short int seen_neg;
} tnets_parser;

#define CTOI(c) (c-'0')

int parse_chunk(tnets_parser *parser, char *str, int size);
