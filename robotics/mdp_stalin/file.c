#include "mdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    SP *sp;
    double epsilon=1.e-6,**probs = allocate_Moore();
    map * m = read_problem("problem.mdp",probs);
    int i,j,a;
    printf("Mapa a resolver:\n");
    for(i=0;i<m->rows;i++){
        for(j=0;j<m->columns;j++){
            printf("[%d,%d] (%d,%.2f) ",i,j,
                   m->cells[i][j].type,
                   m->cells[i][j].reward);
        }
        printf("\n");
    }
    
    S_MDP *mdp = allocate_SMDP( m->rows*m->columns/*states*/,
                                4/*actions*/,
                                1/*gamma*/);
    wire_map(mdp,m,probs);
    for(i=0;i<m->rows;i++){
        for(j=0;j<m->columns;j++){
            printf("\nCell [%d,%d] (%s,%.2f) \n",i,j,
                   m->cells[i][j].type==INACCESS?"INACCESS":
                   m->cells[i][j].type==ACCESS?"ACCESS":"TERMINAL",
                   m->cells[i][j].reward);
            if(m->cells[i][j].type==INACCESS || m->cells[i][j].type==TERMINAL){
                continue;
            }
            printf("Sucesores: ");
            for(a=UP;a<=LEFT;a++){
                printf("\n%s\n",a==UP?"UP":a==RIGHT_S?"RIGHT":a==DOWN?"DOWN":"LEFT");
                for(link_ll *p=mdp->succs[i*m->columns+j][a]->first;
                p!=NULL;p=p->next){
                    sp = (SP *)p->data;
                    printf("([%d,%d],%.2f) ",
                    sp->s->index/m->columns,sp->s->index%m->columns,sp->prob);
                }
            }
        }
    }
    printf("\n");
    v_iteration_S(mdp,m,epsilon);
    printf("Optimal policy:\n");
    for(i=0;i<m->rows;i++){
        for(j=0;j<m->columns;j++){
            if(m->cells[i][j].type==ACCESS){
                a = m->cells[i][j].pi;
                printf("%s",ARROWS[m->cells[i][j].pi]);
            }
            else{
                printf("%s",m->cells[i][j].type==INACCESS?" ":"*");
            }
        }
        printf("\n");
    }
    delete_grid(m->cells,m->rows);
    deallocate_Moore(probs);
    release_S_MDP(mdp);
    free(m);
    return 0;
}
