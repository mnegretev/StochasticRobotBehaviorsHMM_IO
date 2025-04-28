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
/*! \mainpage Simple MMDP Library - A simple Markov Decision Process Library.
*/
/**
 * @file mdp.h
 * @author Stalin Muñoz Gutiérrez
 * @date 27 may 2018
 * @brief Simple MDP library.
 *
 * Simple Markov Decision Process library header file
 * 
 */
/**
 * @brief A Markov Decision Process.
 *
 * Structure containing all parameters, infinite horizon expected rewards and optimal policy.
 */
typedef struct{
  int s; /**< number of states*/
  int a; /**< number of actions*/
  float gamma; /**< discount factor */
  float ***P; /**< transition probabilities, 
              P(s'|s,a)(access: P[s'][s][a])*/
  unsigned char *t; /**< terminal states*/
  float *r; /**< the reward r(s)*/
  float *v; /**< the infinite horizon expected rewards*/
  int *pi; /**< the optimal policy*/
} MDP;

/**
* @brief Allocates memory for an MDP
* @param s the number of states
* @param a the number of actions
* @param gamma the discount factor for future rewards
*/
MDP *allocate_MDP(int s, int a, float gamma);

/**
* @brief Releases memory for an MDP
* @param the MDP to release
*/
void release_MDP(MDP *mdp);
/**
* @brief Prints the MDP parameters
* @param mdp the MDP to print
*/
void print_MDP(MDP *mdp);
/**
* @brief Set random probabilities for the state transitions
* @param mdp the MDP
*/
void random_MDP(MDP *mdp);
/**
* @brief Compute v*(s) using value iteration
* @param mdp the MDP
* @param epsilon the maximum allowed error for the computation of v(s)
*/
void v_iteration_compute(MDP *mdp, float epsilon);
/**
* @brief Computes the best expected utility value for the state s
* @param mdp the MDP
* @param s the state for the computation
*/
float best_expected_u(MDP *mdp, int s);
/**
* @brief Computes the action for the best expected utility value for the state s
* @param mdp the MDP
* @param s the state for the computation
*/
int best_expected_action(MDP *mdp, int s);
/**
* @brief Computes the expected utility value for the state s when taking action a
* @param mdp the MDP
* @param s the state for the computation
* @param a the action to take
*/
float expected_u(MDP *mdp,int s, int a);
/**
* @brief Computes the maximum error between the values of the MDP and the given vector v
* @param mdp the MDP
* @param v the vector of values for the computation
*/
float error(MDP *mdp,float *v);
/**
* @brief Computes the optimal policy for the given MDP
* @param mdp the MDP
*/
void compute_optimal_policy(MDP *mdp);
