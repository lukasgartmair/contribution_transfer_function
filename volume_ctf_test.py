# -*- coding: utf-8 -*-
"""
Created on Aug 23 13:50:02 2016

@author: Lukas Gartmair
"""

import numpy as np
import matplotlib.pyplot as pl
from mpl_toolkits.mplot3d import Axes3D

vertices= [
# bottom
    (0, 0, 0),
    (1, 0, 0),
    (1, 1, 0),
    (0, 1, 0),
# top
    (0, 0, 1),
    (1, 0, 1),
    (1, 1, 1),
    (0, 1, 1)
    ]

def calc_volumes_of_subcuboids(cube_edge_length, atom_position, volume_cube):

    volumes_of_subcuboids = []
    
    # bottom
    #(000)
    edgde1_subcuboid1 = 0 + atom_position[0]
    edgde2_subcuboid1 = 0 + atom_position[1] 
    edgde3_subcuboid1 = 0 + atom_position[2] 
    
    volume_subcuboid1 = edgde1_subcuboid1 * edgde2_subcuboid1 * edgde3_subcuboid1
    volumes_of_subcuboids.append(volume_subcuboid1)
    
    #(100)
    edgde1_subcuboid2 = 1 - atom_position[0]
    edgde2_subcuboid2 = 0 + atom_position[1] 
    edgde3_subcuboid2 = 0 + atom_position[2] 
    
    volume_subcuboid2 = edgde1_subcuboid2 * edgde2_subcuboid2 * edgde3_subcuboid2
    volumes_of_subcuboids.append(volume_subcuboid2)
    
    #(110)
    edgde1_subcuboid3 = 1 - atom_position[0]
    edgde2_subcuboid3 = 1 - atom_position[1] 
    edgde3_subcuboid3 = 0 + atom_position[2] 
    
    volume_subcuboid3 = edgde1_subcuboid3 * edgde2_subcuboid3 * edgde3_subcuboid3
    volumes_of_subcuboids.append(volume_subcuboid3)
    
    #(010)
    edgde1_subcuboid4 = 0 + atom_position[0]
    edgde2_subcuboid4 = 1 - atom_position[1] 
    edgde3_subcuboid4 = 0 + atom_position[2] 
    
    volume_subcuboid4 = edgde1_subcuboid4 * edgde2_subcuboid4 * edgde3_subcuboid4
    volumes_of_subcuboids.append(volume_subcuboid4)
    
    # top    
    #(001)
    edgde1_subcuboid5 = 0 + atom_position[0]
    edgde2_subcuboid5 = 0 + atom_position[1] 
    edgde3_subcuboid5 = 1 - atom_position[2] 
    
    volume_subcuboid5 = edgde1_subcuboid5 * edgde2_subcuboid5 * edgde3_subcuboid5
    volumes_of_subcuboids.append(volume_subcuboid5)
    
    #(101)
    edgde1_subcuboid6 = 1 - atom_position[0]
    edgde2_subcuboid6 = 0 + atom_position[1] 
    edgde3_subcuboid6 = 1 - atom_position[2] 
    
    volume_subcuboid6 = edgde1_subcuboid6 * edgde2_subcuboid6 * edgde3_subcuboid6
    volumes_of_subcuboids.append(volume_subcuboid6)
    
    #(111)
    edgde1_subcuboid7 = 1 - atom_position[0]
    edgde2_subcuboid7 = 1 - atom_position[1] 
    edgde3_subcuboid7 = 1 - atom_position[2] 
    
    volume_subcuboid7 = edgde1_subcuboid7 * edgde2_subcuboid7 * edgde3_subcuboid7
    volumes_of_subcuboids.append(volume_subcuboid7)
    
    #(011)
    edgde1_subcuboid8 = 0 + atom_position[0]
    edgde2_subcuboid8 = 1 - atom_position[1] 
    edgde3_subcuboid8 = 1 - atom_position[2] 
    
    volume_subcuboid8 = edgde1_subcuboid8 * edgde2_subcuboid8 * edgde3_subcuboid8
    volumes_of_subcuboids.append(volume_subcuboid8)
    
    return volumes_of_subcuboids

cube_edge_length = 1
atom_position = (0.7,0.7,0.1)

volume_cube = cube_edge_length**3

# volume of subcuboids
vosc =  calc_volumes_of_subcuboids(cube_edge_length, atom_position, volume_cube)

atom_vertex_contribution = 1/np.array(vosc)
normalized_atom_vertex_contribution = atom_vertex_contribution/max(atom_vertex_contribution)
# should be 1
test_vol = sum(vosc)

x = []
y = []
z = []
c = []
for i in range(8):
    x.append(vertices[i][0])
    y.append(vertices[i][1])
    z.append(vertices[i][2])
    c.append(normalized_atom_vertex_contribution[i])

fig = pl.figure()
ax = fig.add_subplot(111, projection='3d')

for i in range(8):
    ax.scatter(x,y,z,c='b',s=normalized_atom_vertex_contribution *2000)
    ax.scatter(atom_position[0],atom_position[1],atom_position[2],c='red',s=500)
pl.show()











































