# -*- coding: utf-8 -*-
"""
Created on Wed Aug 24 12:07:00 2016

@author: Lukas Gartmair
"""

import numpy as np
import matplotlib.pyplot as pl

L= 5

A = 2

B = 3


# 2d area point nm

A1 = (L-B)*A
A2 = (L-B) * (L-A)
A3 = B*A
A4 = (L-A) * B


# sawtooth point NM

st1 = A4 / (L**2)
st2 = A3 / (L**2)
st3 = A2 / (L**2)
st4 = A1 / (L**2)

sts = np.array([st1,st2,st3,st4])

sts_normalized = sts / np.sum(sts)

c1 = 1/A1
c2 = 1/A2
c3 = 1/A3
c4 = 1/A4

cs = np.array([c1, c2, c3, c4])

cs_normalized = cs / np.sum(cs)



