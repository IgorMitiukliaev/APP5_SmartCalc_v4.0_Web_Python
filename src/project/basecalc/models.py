from django.db import models

# Create your models here.
class Calc(models.Model):
    command = models.CharField(max_length=255)
    result = models.CharField(max_length=255)

    def __str__(self) -> str:
        return self.command