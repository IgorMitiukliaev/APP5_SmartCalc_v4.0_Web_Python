from django.urls import path
from .views import basecalc, view_hist


urlpatterns = [
    path("", basecalc, name="calc"),
    path("history", view_hist, name="history"),
]