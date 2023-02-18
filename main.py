#!/usr/bin/env python3

import argparse
import re

from hashlib import md5
from base64 import b32encode

import pson

ops = {
    '+': 'placek_add',
    '-': 'placek_sub',
    '*': 'placek_mul',
    '/': 'placek_div',
    '%': 'placek_mod',
    '==': 'placek_eq',
    '!=': 'placek_neq',
    '>': 'placek_gt',
    '<': 'placek_lt',
    '>=': 'placek_gte',
    '<=': 'placek_lte',
    '&&': 'placek_and',
    '||': 'placek_or',
}


def codegen(code, scope: dict = {}) -> tuple[str, str]:
    '''Generate C code from a PSON object
        returns (to_prepend, to_insert)
        to_prepend is code that must be prepended to the current scope, like function definitions
        to_insert is code that can be inserted into the current scope, like function calls
    '''
    if type(code) is int: # int
        return '', 'placek_int(' + str(code) + ')'
    elif type(code) is float: # float
        return '', 'placek_float(' + str(code) + ')'
    elif type(code) is str: # variable or string
        if code[0] == "'":
            return '', 'placek_str("' + code[1:] + '")' # TODO: escape here, unescape in parser
        return '', scope[code]
    elif code[0] == 'fn': # function definition
        my_hash = b32encode(md5(str(code).encode()).digest()).decode().replace('=', '')
        fn_name = 'fn_' + str(my_hash)
        arg_names = [code[1], *code[2]] if type(code[1]) is str else code[2]
        body = codegen(code[3], scope=dict(zip(arg_names, ['argv[' + str(i) + ']' for i in range(len(arg_names))])))
        return (
            body[0] + 'PlacekObject* ' + fn_name +
            '(int argc, PlacekObject** argv){return ' + body[1] + ';}',
            'placek_fn(' + fn_name + ')'
        )
    elif code[0] == '?': # if
        condition = codegen(code[1], scope)
        if_true = codegen(code[2], scope)
        if_false = codegen(code[3], scope)
        return (
            condition[0] + if_true[0] + if_false[0],
            f'(placek_truthy({condition[1]})?({if_true[1]}):({if_false[1]}))'
        )
    elif code[0] == '!': # not
        arg = codegen(code[1], scope)
        return arg[0], 'placek_not(' + arg[1] + ')'
    elif code[0] == '$': # constant definition
        arg = codegen(code[2], scope)
        scope[code[1]] = arg[1]
        return arg
    elif type(code[0]) is str and code[0] in ops.keys(): # operator
        args = [codegen(i, scope) for i in code[1:]]
        return (
            ''.join(i[0] for i in args),
            ops[code[0]] + '(' + str(len(args)) +
            ',(PlacekObject*[]){' + ','.join(i[1] for i in args) + '})'
        )
    elif code[0] == "'": # list
        args = [codegen(i, scope) for i in code[1:]]
        return (
            ''.join(i[0] for i in args),
            'placek_array(' + str(len(args)) +
            ',(PlacekObject*[]){' + ','.join(i[1] for i in args) + '})'
        )
    else: # function call
        args = [codegen(i, scope) for i in code]
        return (
            ''.join(i[0] for i in args),
            'placek_call(' + str(len(args)) +
            ',(PlacekObject*[]){' + ','.join(i[1] for i in args) + '})'
        )

main_scope = {
    'println': 'placek_fn(placek_println)',
    'print': 'placek_fn(placek_print)',
}


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('file', type=str)
    parser.add_argument('-o', '--output', type=str, default='a.out.c')
    args = parser.parse_args()

    with open(args.file) as f, open(args.output, 'w') as out:
        code = pson.loads(f.read())
        c = [codegen(i, scope=main_scope) for i in code]
        out.write('#include <placek.h>\n')
        out.write(''.join(i[0] for i in c))
        out.write('int main(int argc, char** argv){')
        out.write('placek_init();')
        out.writelines(i[1] + ';' for i in c)
        out.write('}')
