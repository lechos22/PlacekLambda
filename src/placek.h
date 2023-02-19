#include <stdlib.h>

typedef struct PlacekObject PlacekObject;
typedef struct PlacekArray {
    size_t len;
    PlacekObject** data;
} PlacekArray;
typedef PlacekObject* (*PlacekFn)(int, PlacekObject**);
typedef struct PlacekGeneric{
    const char* class;
    void* data;
}PlacekGeneric;
typedef char PlacekBool;

typedef struct PlacekObject{
    enum {
        PLACEK_BOOL,
        PLACEK_FLOAT,
        PLACEK_STR,
        PLACEK_ARRAY,
        PLACEK_DICT,
        PLACEK_FN,
        PLACEK_GENERIC,
        PLACEK_NULL,
    } type;
    union {
        PlacekBool b;
        double f;
        char* s;
        PlacekArray* array;
        PlacekFn fn;
        PlacekGeneric* generic;
    };
} PlacekObject;

void placek_init(void);
void placek_deinit(void);
PlacekObject* placek_bool(PlacekBool);
PlacekObject* placek_float(float);
PlacekObject* placek_str(char*);
PlacekObject* placek_array(int, PlacekObject*[]);
PlacekObject* placek_fn(PlacekFn);
#define PLACEK_FN(a) (PlacekObject){.type = PLACEK_FN, .fn = a,}
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

extern PlacekObject placek_false;
extern PlacekObject placek_true;
extern PlacekObject placek_null;
