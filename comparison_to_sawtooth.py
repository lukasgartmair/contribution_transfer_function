# -*- coding: utf-8 -*-
"""
Created on Wed Aug 24 12:07:00 2016

@author: Lukas Gartmair
"""

import numpy as np
import matplotlib.pyplot as pl

# comparison between cube subdivison and the sawtooth ctf (Hellman, Seidman)

#Efficient sampling for three-dimensional atom probe
#microscopy data
#Olof C. Hellman, John Blatz du Rivage, David N. Seidman*

#   1 ----- 2
#   |       |
#   |       |
#   4------ 3
#
# distance 4-3 is A + (L - A)
# distance 4-1 is B + (L - B)

css_total = []
sts_total = []

# dimensions
for i in range(2000):
    L = np.random.randint(3,high=1000,size=1)
    A = np.random.randint(1,high=L-1,size=1)
    B = np.random.randint(1,high=L-1,size=1)
    
    # 2d cube subdivision
    A1 = (L-B)*A
    A2 = (L-B) * (L-A)
    A3 = (L-A) * B 
    A4 = B*A
    
    # sawtooth ctf
    st1 = A3 / (L**2)
    st2 = A4 / (L**2)
    st3 = A1 / (L**2)
    st4 = A2 / (L**2)
    
    sts = np.array([st1,st2,st3,st4])
    
    sts_normalized = sts / np.sum(sts)
    
    c1 = 1/A1
    c2 = 1/A2
    c3 = 1/A3
    c4 = 1/A4
    
    cs = np.array([c1, c2, c3, c4])
    
    cs_normalized = cs / np.sum(cs)
    
    css_total.append(cs_normalized)
    sts_total.append(sts_normalized)
    

if np.array(css_total).all() == np.array(sts_total).all():
    print("equal")



