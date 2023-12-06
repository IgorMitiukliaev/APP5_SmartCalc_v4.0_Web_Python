import ctypes
from django.shortcuts import redirect, render
from basecalc.models import Calc
from ctypes import cdll
import re
import json


calc_core = cdll.LoadLibrary('./cpp/calc.so')
makeCalc = calc_core.makeCalc
makeCalc.restype = ctypes.c_char_p

# Create your views here.


def basecalc(request):
    if request.method == "POST":
        if request.POST.get('graph'):
            return makegraph(request)
    return makecalc(request)


def clear_hist():
    Calc.objects.all().delete()


def makecalc(request):
    c = {'result': ''}
    inp = request.POST.get('comm')
    res = ''
    db_hist = ''
    for h in Calc.objects.all():
        db_hist += '{0}\n{1}\n'.format(h.comm_line, h.res_line)
    if len(db_hist) == 0:
        db_hist = '0'
    if not inp or len(inp) == 0:
        c['result'] = db_hist
    else:
        hist, expr = extract_expr(inp)
        expr, corr = subst_var(expr)
        if corr:
            res = eval_expr(expr)
            new_db_rec = Calc(comm_line=expr, res_line=res.decode("utf-8"))
            new_db_rec.save()
            c['result'] = inp.strip()+'\n'+res.decode("utf-8")
        else:
            c['result'] = inp+expr
    return render(request, './basecalc.html', context=c)


def extract_expr(inp):
    if inp and len(inp) > 0:
        *a, b = inp.splitlines()
        return a, b
    else:
        return '', '0'


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
    return expr, corr


def subst_var_gr(expr, val):
    expr = re.sub(r'[\s]', '', expr)
    if re.search(r'x', expr, re.IGNORECASE):
        expr = re.sub(r'[xX]',  str(val), expr)
    return expr


def eval_expr(inp):
    return makeCalc(ctypes.create_string_buffer(str.encode(inp)))


def makegraph(request):
    _points = 501
    x_min = -1
    x_max = 1
    if request.method == "POST":
        if request.POST.get("x_min"):
            x_min = float(request.POST.get("x_min"))
            x_max = float(request.POST.get("x_max"))
    data = []
    inp = request.POST.get('comm')
    _, expr = extract_expr(inp)
    for i in range(0, _points + 1):
        x = x_min + i * (x_max - x_min)/_points
        expr_ = subst_var_gr(expr, x)
        res = eval_expr(expr_)
        data.append({'x': x, 'y': res.decode('utf-8')})
    data_json = json.dumps(data)
    return render(request, './graph.html', context={'expr': expr, 'data_json': data_json, 'x_min': x_min, 'x_max': x_max})


def view_hist(request):
    hist = Calc.objects.all()
    if request.POST.get('clear_hist'):
        clear_hist()
        return redirect(basecalc)
    return render(request, './history.html', {'hist': hist})
