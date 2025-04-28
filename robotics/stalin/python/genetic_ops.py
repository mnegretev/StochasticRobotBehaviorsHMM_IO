# -*- coding: utf-8 -*-
"""
Created on Fri Aug 19 10:49:31 2016

@author: stan
"""
from random import randint
from genotype import Genotype
from numpy import random
from population import Population
from individual import Individual
from selection import Selection
import numpy as np
class GeneticOperators: 
    
    selections={"tournament.selection":Selection.tournament,
                "roulettewheel.selection":Selection.roulettewheel,
                "ranking.selection":Selection.ranking,
                "pareto.tournament":Selection.pareto_tournament}  
    
    @staticmethod
    def crossover(population):
        #assumes individuals are shuffled
        new_pop = []
        for i in range(0,population.size>>1):
            individual1 = population.individuals[i]
            individual2 = population.individuals[population.size-i-1]
            if(random.uniform() < population.parameters['p.crossover']):
                children = GeneticOperators.permutation_crossover_individuals(\
                individual1,individual2) \
                if(population.parameters['type']=='permutation') else \
                GeneticOperators.crossover_individuals(\
                individual1,individual2)
            else:
                children = [individual1,individual2]
            new_pop = new_pop + children
        return \
        Population(population.environment, population.parameters,new_pop)
    
    @staticmethod
    def crossover_individuals(individual1,individual2,type = 'single'):
        genotype1 = individual1.genotype
        genotype2 = individual2.genotype
        crossp = randint(1,genotype1.n-1)
        mask1 = ((1<<(genotype1.n-crossp))-1)<< crossp
        mask2 = (1<<crossp)-1
        ch1 = mask1&genotype1.chromosome|mask2&genotype2.chromosome
        ch2 = mask1&genotype2.chromosome|mask2&genotype1.chromosome
        child1 = Genotype(genotype1.n,ch1)
        child2 = Genotype(genotype1.n,ch2)
        return [Individual(child1),Individual(child2)]
        
    @staticmethod
    def permutation_crossover_individuals(individual1,individual2):
        n = len(individual1.phenotype)
        child1 = np.zeros(n)
        child2 = np.zeros(n)
        
        i,f = random.randint(0,n,2).sort()
        i_central = range(i,f+1)
        i_sides = [i%n for i in range(f+1,n+f)]

        p1_central = set(individual1[i_central])
        p2_central = set(individual2[i_central])

        child1[i_central]= individual1[i_central]
        child2[i_central]= individual2[i_central]
        child1[i_sides] = filter(lambda x:x not in p1_central,\
        individual2[i_sides])
        child2[i_sides] = filter(lambda x:x not in p2_central,\
        individual1[i_sides])
        return [Individual(phenotype=child1),Individual(phenotype=child2)]
        
    @staticmethod
    def mutate_in_place(population):
        length = population.environment.get_chromosome_length();
        mutations = random.binomial(length*population.size,\
        population.parameters['p.mutation'])
        to_mutate = [(randint(0,population.size-1),randint(0,length-1)) \
        for i in range(0,mutations)]
        for ind,pos in to_mutate:
            population.individuals[ind].genotype.chromosome = \
            population.individuals[ind].genotype.chromosome^(1<<pos)
            
    @staticmethod
    def select(population):
        selection_method = \
        GeneticOperators.selections[population.parameters['selection.type']]
        return selection_method(population)
            
                
                
            
            
            
            
        
        
