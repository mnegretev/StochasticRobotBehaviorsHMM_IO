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
 * @file random_example.c
 * @author Stalin Muñoz Gutiérrez
 * @date 27 may 2018
 * @brief Example with a random instance of a 3 state MDP.
 *
 * 
 */
#include <stdio.h>
#include "mdp.h"

void random_example(){
  MDP *mdp = allocate_MDP(3,3,0.9);
  random_MDP(mdp);
  print_MDP(mdp);
  v_iteration_compute(mdp,1.e-3);
  print_MDP(mdp);
  release_MDP(mdp);
}

/**
* @brief Simple invocation of a random instance of an MDP
*
* @param argc number of command line params
* @param argv no params for this example
*
*/
int main(int argc, char **argv){
  random_example();
}


