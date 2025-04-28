/*******************************************************************************
 *
 * Simple Random Boolean Network Complexity Metrics,  
 * Copyright (c) 2019
 * Centro de Ciencias de la Complejidad
 * http://c3.unam.mx
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
 * @file mdpnav.c
 * @author Stalin Muñoz Gutiérrez
 * @date 3 March 2019
 * @brief Map Navigation with MDPs
 *
 * Basic Map Navigation with Markov Decision Processes
 * 
 */
#include "mdpnav.h"
#include "mdp.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void report_file(map *m,char *output_file){

    FILE *fp = (output_file!=NULL)?fopen(output_file, "w"):stdout;
    
    printf("\nResult in %s\n",output_file);
    printf("\nNotation North=N, North-East=A, East=E, South-East=I, South=S, South-West=O, West=W, North-West=U, Terminal=X\n");  

    for(int i=0;i<m->rows;i++){
        for(int j=0;j<m->columns;j++){
            if(m->cells[i][j].type==ACCESS){
                fprintf(fp,"%s",ARROWS[m->cells[i][j].pi]);
                printf("%s ",ARROWS[m->cells[i][j].pi]);
            }
            else{
		if(m->cells[i][j].type==INACCESS){
                	fprintf(fp,"%s","Z");
                	printf("%s ","Z");
                	//fprintf(fp,"%s",m->cells[i][j].type==INACCESS?"[▓▓▓]":"X");
                	//printf("%s ",m->cells[i][j].type==INACCESS?"[▓▓▓]":"X");
		}
		else{
			fprintf(fp,"%s","X");
                        printf("%s ","X");
		}
            }
        }
        fprintf(fp,"\n");
        printf("\n");
    }
    if(output_file!=NULL){
        fclose(fp);
    }
}

void parse_params(int argc, char *argv[], nav_spec *p){
    int opt;
    char *range = NULL;
    const char sep[2] = ":";
    while((opt = getopt(argc, argv, "foeg")) != -1){
        switch(opt){
            case 'f':
                p->input_file = argv[optind];
                break;
            case 'o':
                p->output_file = argv[optind]; 
                break;
            case 'g':
                p->gamma = atof(argv[optind]);
                break;
            case 'e':
                p->epsilon = atof(argv[optind]); 
                break;
        }
    }
}


int main(int argc, char *argv[]){
    // the number of possible actions
    int actions = 8;
    // allocate space for probability distributions
    double ***probs = malloc(sizeof(double **)*actions);
    for(int action = UP;action<=UP_LEFT;action++){
        probs[action] = allocate_Moore();
    }
    

    nav_spec p;
    // defaults
    p.epsilon=1.e-6;
    p.gamma=0.99;
    p.input_file = "map.mdp";
    p.output_file = "policy.txt";
    // parse command line parameters
    parse_params(argc,argv,&p);
    map * m = read_problem(p.input_file,probs);
    
    // create sparsed MDP
    S_MDP *mdp = allocate_SMDP( m->rows*m->columns/*states*/,
                                actions,/*number of actions*/
                                p.gamma/*gamma*/);
    wire_map(mdp,m,probs);
    // solve using value iteration
    v_iteration_S(mdp,m,p.epsilon);
    // write results
    report_file(m,p.output_file);
    
    // release resources
    delete_grid(m->cells,m->rows);
    for(int action = UP;action<=UP_LEFT;action++){
        deallocate_Moore(probs[action]);
    }
    free(probs);
    release_S_MDP(mdp);
    free(m);
    return 0;
}
