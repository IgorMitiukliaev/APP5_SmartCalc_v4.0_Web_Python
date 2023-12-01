import ctypes
from django.shortcuts import render
from basecalc.models import Calc
from ctypes import cdll
import re
calc_core = cdll.LoadLibrary('./cpp/calc.so')
makeCalc = calc_core.makeCalc
# makeCalc.argtypes = (ctypes.c_char_p,)
# makeCalc.restype = ctypes.POINTER(ctypes.c_char)
makeCalc.restype = ctypes.c_char_p

# Create your views here.


def basecalc(request):
    c = {'result': ''}
    if request.method == "POST":
        inp = request.POST.get('comm')
        hist, expr = extract_expr(inp)
        print('hist = ', hist, ' expr = ', expr)
        expr, corr = subst_var(expr)
        if corr:
            res = eval_expr(expr)
            print(res)
            c['result'] = inp+'\n'+res.decode("utf-8")
        else:
            c['result'] = inp+expr
    return render(request, './basecalc.html', context=c)


def extract_expr(inp):
    *a, b = inp.splitlines()
    return '\n'.join(a), b


def subst_var(expr):
    corr = True
    regex = r"(^[\s\w\+\-\*\/\^\.\(\)]+)[\s:;]+[xX]\s*=\s*(\d*\.?\d*)$"
    m = re.search(regex, expr, re.IGNORECASE)
    print('checking ', m)
    if m:
        expr = re.sub(r'[xX]',  m.group(2), m.group(1))
        expr = re.sub(r'[\s]', '', expr)
    elif re.search(r'x', expr, re.IGNORECASE):
            expr = ' x = '
            corr = False
    print(expr)
    return expr, corr


def eval_expr(inp):
    return makeCalc(ctypes.create_string_buffer(str.encode(inp)))
