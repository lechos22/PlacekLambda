#include "placek.h"

PlacekObject* placek_add(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_INT;
    o->i = 0;
    for (int i = 0; i < argc; i++)
        o->i += argv[i]->i;
    return o;
}

PlacekObject* placek_sub(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_INT;
    o->i = argv[0]->i;
    for (int i = 1; i < argc; i++)
        o->i -= argv[i]->i;
    return o;
}

PlacekObject* placek_mul(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_INT;
    o->i = 1;
    for (int i = 0; i < argc; i++)
        o->i *= argv[i]->i;
    return o;
}

PlacekObject* placek_div(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_INT;
    o->i = argv[0]->i;
    for (int i = 1; i < argc; i++)
        o->i /= argv[i]->i;
    return o;
}

PlacekObject* placek_mod(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_INT;
    o->i = argv[0]->i;
    for (int i = 1; i < argc; i++)
        o->i %= argv[i]->i;
    return o;
}

PlacekObject* placek_eq(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 1; i < argc; i++)
        o->b &= argv[i - 1]->i == argv[i]->i;
    return o;
}

PlacekObject* placek_neq(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 1; i < argc; i++)
        o->b &= argv[i - 1]->i != argv[i]->i;
    return o;
}

PlacekObject* placek_lt(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 1; i < argc; i++)
        o->b &= argv[i - 1]->i < argv[i]->i;
    return o;
}

PlacekObject* placek_gt(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 1; i < argc; i++)
        o->b &= argv[i - 1]->i > argv[i]->i;
    return o;
}

PlacekObject* placek_lte(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 1; i < argc; i++)
        o->b &= argv[i - 1]->i <= argv[i]->i;
    return o;
}

PlacekObject* placek_gte(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 1; i < argc; i++)
        o->b &= argv[i - 1]->i >= argv[i]->i;
    return o;
}

PlacekObject* placek_not(PlacekObject *o)
{
    PlacekObject *r = GC_MALLOC(sizeof(PlacekObject));
    r->type = PLACEK_BOOL;
    r->b = !placek_truthy(o);
    return r;
}

PlacekObject* placek_and(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 1;
    for (int i = 0; i < argc; i++)
        o->b &= placek_truthy(argv[i]);
    return o;
}

PlacekObject* placek_or(int argc, PlacekObject *argv[])
{
    PlacekObject *o = GC_MALLOC(sizeof(PlacekObject));
    o->type = PLACEK_BOOL;
    o->b = 0;
    for (int i = 0; i < argc; i++)
        o->b |= placek_truthy(argv[i]);
    return o;
}
