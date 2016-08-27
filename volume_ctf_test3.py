# -*- coding: utf-8 -*-
"""
Created on Aug 23 13:50:02 2016

@author: Lukas Gartmair
"""

import numpy as np
import matplotlib.pyplot as pl
from mpl_toolkits.mplot3d import Axes3D

vertices = [
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


def calc_volumes_of_subcuboids_longversion(atom_position):

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


def generate_random_atom_positions(number_of_atoms):
    
    rnd_atom_positions = []
    rnd_atom_positions_x = np.random.uniform(0, 1, size=number_of_atoms)
    rnd_atom_positions_y = np.random.uniform(0, 1, size=number_of_atoms)
    rnd_atom_positions_z = np.random.uniform(0, 1, size=number_of_atoms)
    
    for i in range(number_of_atoms):
        rnd_atom_positions.append([rnd_atom_positions_x[i], rnd_atom_positions_y[i], rnd_atom_positions_z[i]])
        
    return rnd_atom_positions
    
def calc_volumes_of_subcuboids(atom_position, vertices):
    volumes_of_subcuboids = []
    for v in vertices:
        
        edges_subcuboid = []
        for i,index in enumerate(v): 
            if index == 1:
                edgde_subcuboid = 1 - atom_position[i]
            else:
                edgde_subcuboid = 0 + atom_position[i]
                
            edges_subcuboid.append(edgde_subcuboid)
            
        volume_subcuboid = np.prod(np.array(edges_subcuboid))  
        volumes_of_subcuboids.append(volume_subcuboid)
        
    return volumes_of_subcuboids


cube_edge_length = 1
volume_cube = cube_edge_length**3
atom_positions = [(0.25, 0.25, 0.25)]

normalized_avcs = []
n = 1

#random_atom_positions = np.arange(0)
#random_atom_positions = generate_random_atom_positions(n)


for ap in atom_positions:
     
    # volume of subcuboids
    vosc = calc_volumes_of_subcuboids(ap , vertices)
    atom_vertex_contribution = 1/np.array(vosc)
    
    # normnalization to add up to one
    
    normalized_atom_vertex_contribution = atom_vertex_contribution/ np.sum(atom_vertex_contribution)
    normalized_avcs.append(np.array(normalized_atom_vertex_contribution))
    
    normalized_avcs_array = np.array(normalized_avcs)

# get the means of each vertex for all the runs

#    size_x = np.arange(n)
#pl.plot(size_x,normalized_avcs_array[:,0])
#pl.hist(normalized_avcs_array[:,2])

#    # should be 1
#    test_vol = sum(vosc)
#    
#    x = []
#    y = []
#    z = []
#    c = []
#    for i in range(8):
#        x.append(vertices[i][0])
#        y.append(vertices[i][1])
#        z.append(vertices[i][2])
#        c.append(normalized_atom_vertex_contribution[i])
#    
#    fig = pl.figure()
#    ax = fig.add_subplot(111, projection='3d')
#    ax.scatter(x,y,z,c='b',s=normalized_atom_vertex_contribution *2000)
#    ax.scatter(ap[0],ap[1],ap[2],c='red',s=500)
#    pl.show()
    
    

### TESTS 

import unittest

class TestSubcuboidsMethods(unittest.TestCase):

# volumes of subcuboids
    

    def test_volume_of_subcuboids_midpoint(self):
        expected_vosc = [0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125]
        test_atom_position = (0.5, 0.5, 0.5)
        test_vosc = calc_volumes_of_subcuboids(test_atom_position , vertices)
        self.assertEqual(expected_vosc, test_vosc)
        
    def test_volume_of_subcuboids_midpoint_longversion(self):
        expected_vosc = [0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125]
        test_atom_position = (0.5, 0.5, 0.5)
        test_vosc = calc_volumes_of_subcuboids_longversion(test_atom_position)
        self.assertEqual(expected_vosc, test_vosc)

    def test_volume_of_subcuboids_shifted(self):
        expected_vosc = [0.015625, 0.046875, 0.140625, 0.046875, 0.046875, 0.140625, 0.421875, 0.140625]
        test_atom_position = (0.25, 0.25, 0.25)
        test_vosc = calc_volumes_of_subcuboids(test_atom_position , vertices)
        self.assertEqual(expected_vosc, test_vosc)



if __name__ == '__main__':
    unittest.main()


        

