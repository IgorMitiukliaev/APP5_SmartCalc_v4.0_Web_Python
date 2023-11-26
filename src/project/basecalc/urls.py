from django.urls import path
from .views import basecalc


urlpatterns = [
    path("", basecalc, name="calc"),
]