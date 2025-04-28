# -*- coding: utf-8 -*-
"""
Created on Fri Aug 26 09:22:10 2016

@author: stan
"""
class Individual:
    def __init__(self,genotype,phenotype=None):
        self.genotype = genotype
        if(genotype!=None):
            self.phenotype = phenotype
        
    def __str__(self):
        return str(self.genotype)
        