#include <stdio.h>
#include "placek.h"

void placek_init(void)
{
    GC_INIT();
}

PlacekObject* placek_bool(PlacekBool b)
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = b;
    return o;
}

PlacekObject* placek_int(int i)
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_INT;
    o->i = i;
    return o;
}

PlacekObject* placek_float(float f)
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_FLOAT;
    o->f = f;
    return o;
}

PlacekObject* placek_str(char *s)
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_STR;
    o->s = s;
    return o;
}

PlacekObject* placek_array(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject) + sizeof(PlacekArray) + sizeof(PlacekObject*) * argc);
    o->type = PLACEK_ARRAY;
    o->array = (PlacekArray*)(o + 1);
    o->array->len = argc;
    o->array->data = (PlacekObject**)(o->array + 1);
    for (int i = 0; i < argc; i++)
        o->array->data[i] = argv[i];
    return o;
}

PlacekObject* placek_fn(PlacekFn fn)
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = 3;
    o->fn = fn;
    return o;
}

PlacekBool placek_truthy(PlacekObject *o)
{
    switch (o->type)
    {
        case PLACEK_BOOL:
            return o->b;
        case PLACEK_INT:
            return o->i != 0;
        case PLACEK_FLOAT:
            return o->f != 0;
        case PLACEK_STR:
            return o->s[0] != '\0';
        case PLACEK_FN:
            return 1;
        default:
            return 0;
    }
}

PlacekObject* placek_call(int argc, PlacekObject *argv[])
{
    return argv[0]->fn(argc, argv);
}

PlacekObject* placek_print(int argc, PlacekObject *argv[])
{
    for (int i = 1; i < argc; i++) {
        switch (argv[i]->type) {
            case PLACEK_INT:
                printf("%d", argv[i]->i);
                break;
            case PLACEK_FLOAT:
                printf("%f", argv[i]->f);
                break;
            case PLACEK_STR:
                printf("%s", argv[i]->s);
                break;
            case PLACEK_ARRAY:
                printf("[");
                for (int j = 0; j < argv[i]->array->len; j++) {
                    if(argv[i]->array->data[j]->type != PLACEK_STR)
                        placek_print(2, (PlacekObject*[]){placek_fn(placek_print), argv[i]->array->data[j]});
                    else
                        printf("\"%s\"", argv[i]->array->data[j]->s); // TODO: escape
                    if (j < argv[i]->array->len - 1)
                        printf(" ");
                }
                printf("]");
                break;
            case PLACEK_FN:
                printf("<function>");
                break;
            default:
                printf("<unknown>");
        }
        if (i < argc - 1)
            printf(" ");
    }
}

PlacekObject* placek_println(int argc, PlacekObject *argv[])
{
    placek_print(argc, argv);
    printf("\n");
}
