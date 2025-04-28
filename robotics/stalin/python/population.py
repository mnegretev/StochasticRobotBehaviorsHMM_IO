# -*- coding: utf-8 -*-
"""
Created on Fri Aug 26 09:21:41 2016

@author: stan
"""

from genotype import Genotype
from individual import Individual

class Population:
    def __init__(self,environment,parameters,individuals=None):
        self.environment = environment
        self.parameters = parameters
        
        if individuals==None:
            self.individuals = [self.create_individual() \
            for i in range(0,self.parameters['n.individuals'])]
        else:
            self.individuals = individuals
        self.size = len(self.individuals)
        
    def create_individual(self):
        genotype = Genotype(self.environment.get_chromosome_length())
        return Individual(genotype)
        
    def __str__(self):
        return "\n".join([str(i) for i in self.individuals])