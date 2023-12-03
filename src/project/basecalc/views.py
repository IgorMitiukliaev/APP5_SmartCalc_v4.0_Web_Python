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
    if request.method == "POST":
        if request.POST.get('graph'):
            return makegraph(request)
    return makecalc(request)


def makecalc(request):
    c = {'result': ''}
    inp = request.POST.get('comm')
    if not inp or len(inp) == 0:
        inp = '0'
    hist, expr = extract_expr(inp)
    print('hist = ', hist, ' expr = ', expr)
    expr, corr = subst_var(expr)
    if corr:
        res = eval_expr(expr)
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
    if m:
        expr = re.sub(r'[xX]',  m.group(2), m.group(1))
        expr = re.sub(r'[\s]', '', expr)
    elif re.search(r'x', expr, re.IGNORECASE):
        expr = re.sub(r'[\s]', '', expr)
        expr = '\tx = '
        corr = False
    # print(expr)
    return expr, corr


def subst_var_gr(expr, val):
    expr = re.sub(r'[\s]', '', expr)
    if re.search(r'x', expr, re.IGNORECASE):
        expr = re.sub(r'[xX]',  str(val), expr)
    return expr


def eval_expr(inp):
    return makeCalc(ctypes.create_string_buffer(str.encode(inp)))


def makegraph(request):
    _points = 33
    x_min, x_max = -2, 2
    data = []
    print('graph')
    inp = request.POST.get('comm')
    _, expr = extract_expr(inp)
    print('expr ----> ', expr)
    for i in range(0, _points + 1):
        x = i* (x_max - x_min)/_points
        expr_ = subst_var_gr(expr, x)
        res = eval_expr(expr_)
        data.append((x, res.decode('utf-8')))
        # print(expr, ' = ', res.decode("utf-8"))
    print(data)
    return render(request, './graph.html', context={'expr': data})
