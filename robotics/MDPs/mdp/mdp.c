/*******************************************************************************
 *
 * Simple MDP Library,  
 * Copyright (c) 2018
 * Laboratorio de Biorobótica
 * https://biorobotics.fi-p.unam.mx/.
 * Universidad Nacional Autónoma de México.
 * All rights reserved.
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *  
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *  
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *******************************************************************************/
/**
 * @file mdp.c
 * @author Stalin Muñoz Gutiérrez
 * @date 27 may 2018
 * @brief Simple MDP library.
 *
 * Simple Markov Decision Process library implementation
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include "mdp.h"

MDP *allocate_MDP(int s,int a,float gamma){
  int i,j;
  MDP *mdp = (MDP *) malloc(sizeof(MDP));
  mdp->s = s;
  mdp->a = a;
  mdp->gamma = gamma;
  mdp->t = (unsigned char *) calloc(s,sizeof(unsigned char));
  mdp->r = (float *) calloc(s,sizeof(float));
  mdp->P = (float ***) malloc(sizeof(float *)*s);
  mdp->v = (float *) calloc(s,sizeof(float));
  mdp->pi = (int *) calloc(s,sizeof(int));
  for(i=0;i<s;i++){
    mdp->P[i] = (float **) malloc(sizeof(float *)*s);
    for(j=0;j<s;j++){
      mdp->P[i][j] = (float *) calloc(a,sizeof(float));
    }
  }
  return mdp;
}

void release_MDP(MDP *mdp){
  int i,j;
  for(i=0;i<mdp->s;i++){
    for(j=0;j<mdp->s;j++){
      free(mdp->P[i][j]);
    }
    free(mdp->P[i]);
  }
  free(mdp->t);
  free(mdp->r);
  free(mdp->P);
  free(mdp->v);
  free(mdp->pi);
  free(mdp);
}

void print_MDP(MDP* mdp){
  int i,j,k;
  printf("Markov Decision Process \n");
  printf("%d states.\n",mdp->s);
  printf("%d actions.\n",mdp->a);
  printf("gamma = %.4f\n",mdp->gamma);
  printf("Terminal states: ");
  for(i=0;i<mdp->s;i++){
    if(mdp->t[i]){
      printf("%d ",i);
    }
  }
  printf("\nTransition probabilities:\n");
  for(i=0;i<mdp->s;i++){
    for(j=0;j<mdp->s;j++){
      for(k=0;k<mdp->a;k++){
        printf("P(s'=%d|s=%d,a=%d) = %.2f\n",i,j,k,mdp->P[i][j][k]);
      }
    }
  }
  printf("State rewards:\n");
  for(i=0;i<mdp->s;i++){
    printf("r(s=%d) = %.2f\n",i,mdp->r[i]);
  }
  printf("Infinite horizon expected rewards:\n");
  for(i=0;i<mdp->s;i++){
    printf("v*(s=%d) = %.2f\n",i,mdp->v[i]);
  }
  printf("Optimal policy:\n");
  for(i=0;i<mdp->s;i++){
    printf("pi*(s=%d) = %d\n",i,mdp->pi[i]);
  }
}

void random_MDP(MDP *mdp){
  int i,j,k;
  float sum;
  srand((unsigned int)time(NULL));
  for(j=0;j<mdp->s;j++){
    for(k=0;k<mdp->a;k++){
      for(i=0,sum=0;i<mdp->s;i++){
        mdp->P[i][j][k]=((float)rand()/(float)(RAND_MAX));
        sum += mdp->P[i][j][k];
      }
      for(i=0;i<mdp->s;i++){
        mdp->P[i][j][k] /= sum;
      }
    }
    mdp->r[j] = ((float)rand()/(float)(RAND_MAX))-0.5;
  }
}

void v_iteration_compute(MDP *mdp, float epsilon){
  int i;
  float *v, max_error;
  v = (float *) malloc(sizeof(float)*mdp->s);
  for(i=0;i<mdp->s;i++){
    v[i]=mdp->r[i];
  }
  do{
    for(i=0;i<mdp->s;i++){
      if(!mdp->t[i]){
        v[i]=mdp->r[i]+mdp->gamma*best_expected_u(mdp,i);
      }
    }
    max_error = error(mdp,v);
    for(i=0;i<mdp->s;i++){
      mdp->v[i] = v[i];
    }
  }while(max_error>(epsilon*(1-mdp->gamma)/mdp->gamma));
  compute_optimal_policy(mdp);
  free(v);
}

float best_expected_u(MDP *mdp,int s){
  int a;
  float u,best = FLT_MIN;
  for(a=0;a<mdp->a;a++){
    u = expected_u(mdp,s,a);
    if(u > best){
      best = u;
    }
  }
  return best;
}

int best_expected_action(MDP *mdp,int s){
  int a, best_action;
  float u,best = FLT_MIN;
  for(a=0;a<mdp->a;a++){
    u = expected_u(mdp,s,a);
    if(u > best){
      best = u;
      best_action = a;
    }
  }
  return best_action;
}

float expected_u(MDP *mdp,int s, int a){
  int i;
  float u=0;
  for(i=0;i<mdp->s;i++){
    u+=mdp->P[i][s][a]*mdp->v[i];
  }
  return u;
}

float error(MDP *mdp,float *v){
  int i;
  float diff, maximum = 0;
  for(i=0;i<mdp->s;i++){
    diff = fabs(mdp->v[i]-v[i]);
    if(diff > maximum){
      maximum = diff;
    }
    //printf("v(s=%d)=%.2f ",i,v[i]);
  }
  printf("\n");
  return maximum;
}
void compute_optimal_policy(MDP *mdp){
  int i;
  for(i=0;i<mdp->s;i++){
    mdp->pi[i] = best_expected_action(mdp,i);
  }
}
