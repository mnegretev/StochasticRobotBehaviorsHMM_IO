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
 * @file ryn_chapter_17.c
 * @author Stalin Muñoz Gutiérrez
 * @date 28 may 2018
 * @brief Simple MDP library.
 *
 * Simple Markov Decision Process library implementation.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include "mdp.h"

void train_announcement(){

  /*3 states, 2 actions, gamma = 0.9*/
  MDP *mdp = allocate_MDP(3,2,0.9);

  /*No terminal states in this problem*/

  /*rewards*/
  mdp->r[0] =  0;
  mdp->r[1] =  10;
  mdp->r[2] =  27;

  /*train announcement at state 0*/
  mdp->P[0][0][0]=0.7;
  mdp->P[1][0][0]=0.1;
  mdp->P[2][0][0]=0.2;

  /*no train announcement at state 0*/
  mdp->P[0][0][1]=0.5;
  mdp->P[1][0][1]=0.3;
  mdp->P[2][0][1]=0.2;

  /*train announcement at state 1*/
  mdp->P[0][1][0]=0.4;
  mdp->P[1][1][0]=0.4;
  mdp->P[2][1][0]=0.2;

  /*no train announcement at state 1*/
  mdp->P[0][1][1]=0.2;
  mdp->P[1][1][1]=0.7;
  mdp->P[2][1][1]=0.1;

  /*train announcement at state 2*/
  mdp->P[0][2][0]=0.2;
  mdp->P[1][2][0]=0.2;
  mdp->P[2][2][0]=0.6;

  /*train no announcement at state 0*/
  mdp->P[0][2][1]=0.1;
  mdp->P[1][2][1]=0.1;
  mdp->P[2][2][1]=0.8;


  printf("Train announcement example");
  v_iteration_compute(mdp,1.e-6);
  print_MDP(mdp);
  release_MDP(mdp);
}

/**
* @brief Runs the 3 vagon intelligent 
* train announcement example
*
* @param argc number of command line params
* @param argv no params for this example
*
*/
int main(int argc, char **argv){
  train_announcement();
}
