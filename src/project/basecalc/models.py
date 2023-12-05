from django.db import models

# Create your models here.
class Calc(models.Model):
    comm_line = models.CharField(max_length=255, default='0')
    res_line = models.CharField(max_length=255, default='0')

    def __str__(self) -> str:
        return "{0}\n{1}".format(self.comm_line, self.res_line)