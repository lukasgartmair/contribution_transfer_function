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

    # contributions
    c1 = 1/A1
    c2 = 1/A2
    c3 = 1/A3
    c4 = 1/A4
    
    cs = np.array([c1, c2, c3, c4])
    
    cs_normalized = cs / np.sum(cs)
    
    css_total.append(cs_normalized)
    sts_total.append(sts)
    

if np.array(css_total).all() == np.array(sts_total).all():
    print("equal")



#### Volume case

# x axis = A | (L - A )
# y axis = (L - B) | B 
# z axis = (L - C) | C

css_total_volume = []
sts_total_volume = []

# dimensions
for i in range(2000):
    L = np.random.randint(3,high=50,size=1)
    A = np.random.randint(1,high=L-1,size=1)
    B = np.random.randint(1,high=L-1,size=1)
    C = np.random.randint(1,high=L-1,size=1)
    
    # 3d cube subdivision
    V1 = A * (L-B) * (L-C)
    V2 = (L-A) * (L-B) * (L-C)
    V3 = A * (L-B) * C
    V4 = (L-A) * (L-B) * C
    V5 = A * B * (L-C)
    V6 = (L-A) * B * (L-C)
    V7 = A * B * C
    V8 = (L-A) * B * C

    # sawtooth ctf 3d
    st1 =  V8 / (L**3)
    st2 =  V7 / (L**3)
    st3 =  V6 / (L**3)
    st4 =  V5 / (L**3)
    st5 =  V4 / (L**3)
    st6 =  V3 / (L**3)
    st7 =  V2 / (L**3)
    st8 =  V1 / (L**3)
    
    sts = np.array([st1,st2,st3,st4])

    # contributions
    c1 = 1/V1
    c2 = 1/V2
    c3 = 1/V3
    c4 = 1/V4
    c5 = 1/V1
    c6 = 1/V2
    c7 = 1/V3
    c8 = 1/V4
    
    cs = np.array([c1, c2, c3, c4, c5, c6, c7, c8])
    
    cs_normalized = cs / np.sum(cs)
    
    css_total_volume.append(cs_normalized)
    sts_total_volume.append(sts)
    

if np.array(css_total_volume).all() == np.array(sts_total_volume).all():
    print("equal")

