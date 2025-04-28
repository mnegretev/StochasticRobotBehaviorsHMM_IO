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
#include <double.h>
#include <math.h>
#include "mdp.h"

void ryn_chapter_17(){
  int i;
  MDP *mdp = allocate_MDP(11,4,1);

  /*terminal states*/
  mdp->t[6]=(unsigned char)1;
  mdp->t[10]=(unsigned char)1;

  /*rewards*/
  for(i=0;i<mdp->s;i++){
    mdp->r[i] =  -0.04;
  }
  mdp->r[6] =  -1;
  mdp->r[10] =  1;

  /*up from state 0*/
  mdp->P[4][0][0]=0.8;
  mdp->P[0][0][0]=0.1;
  mdp->P[1][0][0]=0.1;

  /*right from state 0*/
  mdp->P[4][0][1]=0.1;
  mdp->P[0][0][1]=0.1;
  mdp->P[1][0][1]=0.8;

  /*down from state 0*/
  mdp->P[0][0][2]=0.9;
  mdp->P[1][0][2]=0.1;

  /*left from state 0*/
  mdp->P[4][0][3]=0.1;
  mdp->P[0][0][3]=0.9;

  /*up from state 1*/
  mdp->P[0][1][0]=0.1;
  mdp->P[1][1][0]=0.8;
  mdp->P[2][1][0]=0.1;

  /*right from state 1*/
  mdp->P[1][1][1]=0.2;
  mdp->P[2][1][1]=0.8;

  /*down from state 1*/
  mdp->P[0][1][2]=0.1;
  mdp->P[1][1][2]=0.8;
  mdp->P[2][1][2]=0.1;

  /*left from state 1*/
  mdp->P[0][1][3]=0.8;
  mdp->P[1][1][3]=0.2;

  /*up from state 2*/
  mdp->P[5][2][0]=0.8;
  mdp->P[1][2][0]=0.1;
  mdp->P[3][2][0]=0.1;

  /*right from state 2*/
  mdp->P[5][2][1]=0.1;
  mdp->P[3][2][1]=0.8;
  mdp->P[2][2][1]=0.1;

  /*down from state 2*/
  mdp->P[1][2][2]=0.1;
  mdp->P[2][2][2]=0.8;
  mdp->P[3][2][2]=0.1;

  /*left from state 2*/
  mdp->P[5][2][3]=0.1;
  mdp->P[1][2][3]=0.8;
  mdp->P[2][2][3]=0.1;

  /*up from state 3*/
  mdp->P[6][3][0]=0.8;
  mdp->P[2][3][0]=0.1;
  mdp->P[3][3][0]=0.1;

  /*right from state 3*/
  mdp->P[6][3][1]=0.1;
  mdp->P[3][3][1]=0.9;

  /*down from state 3*/
  mdp->P[2][3][2]=0.1;
  mdp->P[3][3][2]=0.9;

  /*left from state 3*/
  mdp->P[6][3][3]=0.1;
  mdp->P[2][3][3]=0.8;
  mdp->P[3][3][3]=0.1;

  /*up from state 4*/
  mdp->P[7][4][0]=0.8;
  mdp->P[4][4][0]=0.2;

  /*right from state 4*/
  mdp->P[7][4][1]=0.1;
  mdp->P[4][4][1]=0.8;
  mdp->P[0][4][1]=0.1;

  /*down from state 4*/
  mdp->P[0][4][2]=0.8;
  mdp->P[4][4][2]=0.2;

  /*left from state 4*/
  mdp->P[7][4][4]=0.1;
  mdp->P[4][4][4]=0.8;
  mdp->P[0][4][4]=0.1;

  /*up from state 5*/
  mdp->P[9][5][0]=0.8;
  mdp->P[5][5][0]=0.1;
  mdp->P[6][5][0]=0.1;

  /*right from state 5*/
  mdp->P[9][5][1]=0.1;
  mdp->P[2][5][1]=0.1;
  mdp->P[6][5][1]=0.8;

  /*down from state 5*/
  mdp->P[2][5][2]=0.8;
  mdp->P[5][5][2]=0.1;
  mdp->P[6][5][2]=0.1;

  /*left from state 5*/
  mdp->P[9][5][3]=0.1;
  mdp->P[5][5][3]=0.8;
  mdp->P[2][5][3]=0.1;

  /*up from state 7*/
  mdp->P[7][7][0]=0.9;
  mdp->P[8][7][0]=0.1;

  /*right from state 7*/
  mdp->P[8][7][1]=0.8;
  mdp->P[7][7][1]=0.1;
  mdp->P[4][7][1]=0.1;

  /*down from state 7*/
  mdp->P[4][7][2]=0.8;
  mdp->P[7][7][2]=0.1;
  mdp->P[8][7][2]=0.1;

  /*left from state 7*/
  mdp->P[7][7][3]=0.9;
  mdp->P[4][7][3]=0.1;

  /*up from state 8*/
  mdp->P[7][8][0]=0.1;
  mdp->P[8][8][0]=0.8;
  mdp->P[9][8][0]=0.1;

  /*right from state 8*/
  mdp->P[8][8][1]=0.2;
  mdp->P[9][8][1]=0.8;

  /*down from state 8*/
  mdp->P[7][8][2]=0.1;
  mdp->P[8][8][2]=0.8;
  mdp->P[9][8][2]=0.1;

  /*left from state 8*/
  mdp->P[8][8][3]=0.2;
  mdp->P[7][8][3]=0.8;

  /*up from state 9*/
  mdp->P[10][9][0]=0.1;
  mdp->P[8][9][0]=0.1;
  mdp->P[9][9][0]=0.8;

  /*right from state 9*/
  mdp->P[10][9][1]=0.8;
  mdp->P[9][9][1]=0.1;
  mdp->P[5][9][1]=0.1;

  /*down from state 9*/
  mdp->P[10][9][2]=0.1;
  mdp->P[8][9][2]=0.1;
  mdp->P[5][9][2]=0.8;

  /*left from state 9*/
  mdp->P[8][9][3]=0.8;
  mdp->P[9][9][3]=0.1;
  mdp->P[5][9][3]=0.1;

  printf("Russell y Norvig MDP example (Chapter 17)");
  v_iteration_compute(mdp,1.e-3);
  print_MDP(mdp);
  release_MDP(mdp);
}

/**
* @brief Runs the Russell & Norvig chapter 17 example
* Russell, Stuart J., and Peter Norvig.
* Artificial intelligence: a modern approach. 
* Pearson Education Limited, 2016.
*
* @param argc number of command line params
* @param argv no params for this example
*
*/
int main(int argc, char **argv){
  ryn_chapter_17();
}
