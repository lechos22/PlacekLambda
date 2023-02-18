#include <gc.h>

typedef struct PlacekObject PlacekObject;
typedef struct PlacekArray {
    size_t len;
    PlacekObject** data;
} PlacekArray;
typedef PlacekObject* (*PlacekFn)(int, PlacekObject**);
typedef char PlacekBool;

typedef struct PlacekObject{
    enum {
        PLACEK_BOOL,
        PLACEK_INT,
        PLACEK_FLOAT,
        PLACEK_STR,
        PLACEK_ARRAY,
        PLACEK_DICT,
        PLACEK_FN,
    } type;
    union {
        PlacekBool b;
        int i;
        float f;
        char* s;
        PlacekArray* array;
        PlacekFn fn;
    };
} PlacekObject;

void placek_init(void);
PlacekObject* placek_bool(PlacekBool);
PlacekObject* placek_int(int);
PlacekObject* placek_float(float);
PlacekObject* placek_str(char*);
PlacekObject* placek_array(int, PlacekObject*[]);
PlacekObject* placek_fn(PlacekFn);
PlacekBool placek_truthy(PlacekObject*);
PlacekObject* placek_call(int, PlacekObject*[]);

PlacekObject* placek_print(int argc, PlacekObject *argv[]);
PlacekObject* placek_println(int argc, PlacekObject *argv[]);

PlacekObject* placek_add(int argc, PlacekObject *argv[]);
PlacekObject* placek_sub(int argc, PlacekObject *argv[]);
PlacekObject* placek_mul(int argc, PlacekObject *argv[]);
PlacekObject* placek_div(int argc, PlacekObject *argv[]);
PlacekObject* placek_mod(int argc, PlacekObject *argv[]);
PlacekObject* placek_eq(int argc, PlacekObject *argv[]);
PlacekObject* placek_neq(int argc, PlacekObject *argv[]);
PlacekObject* placek_gt(int argc, PlacekObject *argv[]);
PlacekObject* placek_lt(int argc, PlacekObject *argv[]);
PlacekObject* placek_gte(int argc, PlacekObject *argv[]);
PlacekObject* placek_lte(int argc, PlacekObject *argv[]);
PlacekObject* placek_and(int argc, PlacekObject *argv[]);
PlacekObject* placek_or(int argc, PlacekObject *argv[]);
PlacekObject* placek_not(PlacekObject *o);
