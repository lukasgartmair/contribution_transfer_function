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

# sawtooth point NM
st_nm = ((L-A)*(L-B))/ (L**2)

# 2d area point nm

A1 = (L-B)*A
A2 = (L-B) * (L-A)
A3 = B*A
A4 = (L-A) * B

c1 = 1/A1
c2 = 1/A2
c3 = 1/A3
c4 = 1/A4

cs = [c1, c2, c3, c4]
maxc = max(cs)

nc1 = c1/maxc
nc2 = c2/maxc
nc3 = c3/maxc
nc4 = c4/maxc


