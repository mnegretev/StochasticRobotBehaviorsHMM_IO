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
 * @author Jesús Savage Carmona
 * @date March 2019
 * @brief Simple MDP library.
 *
 * Simple Markov Decision Process library implementation
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include "mdp.h"
#include "dstruct.h"

#define MDP_NUM_MAX_ITERATIONS 500


//char *ARROWS[8] = {"[ N ]","[ NE]","[ E ]","[ SE]","[ S ]","[ SW]","[ W ]","[ NW]"}; 
char *ARROWS[8] = {"N","A","E","I","S","O","W","U"}; 

MDP *allocate_MDP(int s,int a,double gamma){
    int i,j;
    MDP *mdp = (MDP *) malloc(sizeof(MDP));
    mdp->s = s;
    mdp->a = a;
    mdp->gamma = gamma;
    mdp->t = (unsigned char *) calloc(s,sizeof(unsigned char));
    mdp->r = (double *) calloc(s,sizeof(double));
    mdp->P = (double ***) malloc(sizeof(double *)*s);
    mdp->v = (double *) calloc(s,sizeof(double));
    mdp->pi = (int *) calloc(s,sizeof(int));
    for(i=0;i<s;i++){
        mdp->P[i] = (double **) malloc(sizeof(double *)*s);
        for(j=0;j<s;j++){
            mdp->P[i][j] = (double *) calloc(a,sizeof(double));
        }
    }
    return mdp;
}

S_MDP *allocate_SMDP(int s,int a, double gamma){
    int i,j;
    S_MDP *mdp = (S_MDP *) malloc(sizeof(S_MDP));
    mdp->s = s;
    mdp->a = a;
    mdp->gamma = gamma;
    mdp->succs = (LLST ***) malloc(sizeof(LLST **)*s);
    for(i=0;i<s;i++){
        mdp->succs[i] = (LLST **) malloc(sizeof(LLST *)*a);
        for(j=0;j<a;j++){
            // creates an empty list for (next state,probability) pairs
            mdp->succs[i][j] = empty();  
        }
    }
    return mdp;
}

void release_S_MDP(S_MDP *mdp){
    for(int s=0;s<mdp->s;s++){
        for(int a=0;a<mdp->a;a++){
            free_data_LLST(mdp->succs[s][a]);
            free_LLST(mdp->succs[s][a]);
        }
        free(mdp->succs[s]);
    }
    free(mdp->succs);   
    free(mdp);
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
    double sum;
    srand((unsigned int)time(NULL));
    for(j=0;j<mdp->s;j++){
        for(k=0;k<mdp->a;k++){
            for(i=0,sum=0;i<mdp->s;i++){
                mdp->P[i][j][k]=((double)rand()/(double)(RAND_MAX));
                sum += mdp->P[i][j][k];
            }
            for(i=0;i<mdp->s;i++){
                mdp->P[i][j][k] /= sum;
            }
        }
        mdp->r[j] = ((double)rand()/(double)(RAND_MAX))-0.5;
    }
}

void v_iteration_S(S_MDP *mdp,map *m,double epsilon){
    int i,j;
    int k = 0;
    double **v, max_error;
    v = (double **) malloc(sizeof(double *)*m->rows);
    for(i=0;i<m->rows;i++){
        v[i] = (double *) calloc(m->columns,sizeof(double));
        for(j=0;j<m->columns;j++){
            v[i][j] = m->cells[i][j].reward;
            m->cells[i][j].v =v[i][j];
        }
    }
    do{
        for(i=0;i<m->rows;i++){
            for(j=0;j<m->columns;j++){
                if(m->cells[i][j].type==ACCESS){
                    v[i][j]=m->cells[i][j].reward+
                    mdp->gamma*best_expected_u_S(mdp->succs[i*m->columns+j]);
                }
            }
        }
        max_error = error_S(m,v);
        for(i=0;i<m->rows;i++){
            for(j=0;j<m->columns;j++){
                m->cells[i][j].v = v[i][j];
            }
        }
	k++;
	if(k > MDP_NUM_MAX_ITERATIONS) break;
    }while(max_error>(epsilon*(1-mdp->gamma)/mdp->gamma));
    printf("\nKKK %d\n",k);
    compute_optimal_policy_S(mdp,m);
    // releasing allocated resources
    for(i=0;i<m->rows;i++){
        free(v[i]);
    }
    free(v);
}

void v_iteration_compute(MDP *mdp, double epsilon){
    int i;
    double *v, max_error;
    v = (double *) malloc(sizeof(double)*mdp->s);
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

double best_expected_u_S(LLST **succs){
    int a;
    double u, best = -DBL_MAX;
    for(a=UP;a<=UP_LEFT;a++){
        u = expected_u_S(succs,a);
        if(u > best){
            best = u;
        }
    }
    return best;
}

double best_expected_u(MDP *mdp,int s){
    int a;
    double u,best = -DBL_MAX;
    for(a=0;a<mdp->a;a++){
        u = expected_u(mdp,s,a);
        if(u > best){
            best = u;
        }
    }
    return best;
}

int best_expected_action_S(LLST **succs){
    int a, best_action;
    double u, best = -DBL_MAX;
    for(a=UP;a<=UP_LEFT;a++){
        u = expected_u_S(succs,a);
        if(u > best){
            best = u;
            best_action = a;
        }
    }
    return best_action;
}

int best_expected_action(MDP *mdp,int s){
    int a, best_action;
    double u,best = -DBL_MAX;
    for(a=0;a<mdp->a;a++){
        u = expected_u(mdp,s,a);
        if(u > best){
            best = u;
            best_action = a;
        }
    }
    return best_action;
}

double expected_u_S(LLST **succs,int a){
    double u=0;
    SP *sp;
    for(link_ll *p=succs[a]->first;p!=NULL;p=p->next){
        sp = (SP *) p->data;
        u += sp->prob*sp->s->v;       
    }
    return u;
}

double expected_u(MDP *mdp,int s, int a){
    int i;
    double u=0;
    for(i=0;i<mdp->s;i++){
        u+=mdp->P[i][s][a]*mdp->v[i];
    }
    return u;
}

double error_S(map *m,double **v){
    int i,j;
    double diff, maximum = 0;
    for(i=0;i<m->rows;i++){
        for(j=0;j<m->columns;j++){
            diff = fabs(m->cells[i][j].v-v[i][j]);
            if(diff > maximum){
                maximum = diff;
            }
        }
    }
    return maximum;
}

double error(MDP *mdp,double *v){
    int i;
    double diff, maximum = 0;
    for(i=0;i<mdp->s;i++){
        diff = fabs(mdp->v[i]-v[i]);
        if(diff > maximum){
            maximum = diff;
        }
    }
    return maximum;
}

void compute_optimal_policy_S(S_MDP *mdp,map *m){
    int i,j;
    for(i=0;i<m->rows;i++){
        for(j=0;j<m->columns;j++){
            m->cells[i][j].pi = 
            best_expected_action_S(mdp->succs[i*m->columns+j]);
        }
    }
}

void compute_optimal_policy(MDP *mdp){
    int i;
    for(i=0;i<mdp->s;i++){
        mdp->pi[i] = best_expected_action(mdp,i);
    }
}

void delete_grid(state **grid,int n){
    int i=0;
    for(i=0;i<n;i++){
        free(grid[i]);
    }
    free(grid);
}

state **create_empty_grid(int n, int m){
    int i = 0;
    state** grid = (state **) malloc(sizeof(state*)*n);
    for(i=0;i<n;i++){
        grid[i] = (state *) malloc(sizeof(state)*m);
    }
    return grid;
}

double **allocate_Moore(){
    int i = 0;
    double** neigh = (double **) malloc(sizeof(double*)*3);
    for(i=0;i<3;i++){
        neigh[i] = (double *) malloc(sizeof(double)*3);
    }
    return neigh;
}

void deallocate_Moore(double **neigh){
    int i = 0;
    for(i=0;i<3;i++){
        free(neigh[i]);
    }
    free(neigh);
}

FILE *open_map(char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error reading file: %s\n",filename);
        return NULL;
    }
    return fp;
}

map *read_problem(char *filename,double ***probs){
    map *m = (map *) malloc(sizeof(map));
    FILE *fp = open_map(filename);
    if(!fp){
        exit(1);
    }
    fscanf(fp,"%d %d\n",&(m->rows),&(m->columns));
    m->cells = create_empty_grid(m->rows,m->columns);
    for(int i=0;i<m->rows;i++){
        for(int j=0;j<m->columns;j++){
             fscanf(fp,"%d",&(m->cells[i][j].type));
             fscanf(fp,"%lf",&(m->cells[i][j].reward));
             m->cells[i][j].index = i*m->columns+j;
             m->cells[i][j].v = 0.0;
        }
    }
    for(int action = UP;action<=UP_LEFT;action++){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                fscanf(fp,"%lf",&probs[action][i][j]);
            }
        }
    }
    fclose(fp);
    return m;
}

void add_or_acc(S_MDP *mdp,map *m,int i,int j,int ip,int jp,int a,double prob){
    SP *sp;
    int found = 0;
    if(m->cells[ip][jp].type==INACCESS){
        //target cell inaccessible
        //agent remains in its location
        ip = i;
        jp = j;
    }
    for(link_ll *p=mdp->succs[i*m->columns+j][a]->first;p!=NULL;p=p->next){
        sp = (SP *)p->data;
        //state already in the list
        if(sp->s->index==ip*m->columns+jp){
            //update its probability
            sp->prob += prob;
            found = 1;
            break;
        }
    }
    if(!found){
        // create a new state probability pair
        sp = (SP *) malloc(sizeof(SP));
        sp->s = &(m->cells[ip][jp]);
        sp->prob = prob;
        // adds pair to list
        append(mdp->succs[i*m->columns+j][a],sp);
    }
}


void wire_map(S_MDP *mdp,map *m,double ***probs){
    double prob;
    for(int i=0;i<m->rows;i++){
        for(int j=0;j<m->columns;j++){
            if(m->cells[i][j].type==INACCESS || m->cells[i][j].type==TERMINAL){
                //cell is inaccessible or terminal
                continue;
            }
            //actions
            for(int a=UP;a<=UP_LEFT;a++){ 
                // explore Moore's neighborhood
                for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        prob = probs[a][k][l];
                        // if probability is not zero
                        if(prob){
                            add_or_acc(
                            mdp,
                            m,
                            i,
                            j,
                            (i+k-1<0)?0:(i+k-1)>=m->rows?m->rows-1:i+k-1,
                            (j+l-1<0)?0:(j+l-1)>=m->columns?m->columns-1:j+l-1,
                            a,
                            prob);
                        }
                        //else nothing to do
                    }
                }
            }
        }
    }
}
