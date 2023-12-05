from django.shortcuts import render, redirect
from django.http import HttpResponse

def root(request):
    return render(request, 'main.html')

def help_calc(request):
    return render(request, 'help.html')