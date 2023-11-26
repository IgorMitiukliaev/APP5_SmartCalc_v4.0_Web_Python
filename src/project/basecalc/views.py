import ctypes
from django.shortcuts import render
from basecalc.models import Calc
from ctypes import cdll
calc_core = cdll.LoadLibrary('./cpp/calc.so')
makeCalc = calc_core.makeCalc
# makeCalc.argtypes = (ctypes.c_char_p,)
makeCalc.restype = ctypes.POINTER(ctypes.c_char)


# Create your views here.

def basecalc(request):
    c = {}
    if request.method == "POST":
        comm = request.POST.get('comm')
        res = makeCalc(ctypes.create_string_buffer(str.encode(comm)))
        print(res)
    return render(request, './basecalc.html', context=c)
