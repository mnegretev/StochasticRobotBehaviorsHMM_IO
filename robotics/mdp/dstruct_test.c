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
 * @file dstruct_test.c
 * @author Stalin Muñoz Gutiérrez
 * @date 3 March 2019
 * @brief Data Structures Library Test
 *
 * Basic Data Structures Library Test File
 * 
 */
#include "dstruct.h"
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char *argv[]){
    LLST *list = empty();
    void *p;
    for(int i=0;i<1000;i++){
        p = (int *)malloc(sizeof(int));
        *(int *)p = i;
        append(list,p);
    }
    printf("List size: %llu\n",list->size);
    printf("First element: %d\n",*((int *)list->first->data));
    printf("Second element: %d\n",*((int *)list->first->next->data));
    printf("Next to last element: %d\n",*((int *)list->last->previous->data));
    printf("Last element: %d\n",*((int *)list->last->data));
    printf("Printing list:\n");
    int *value;
    for(int i=0;i<1000;i++){
        value = (int *)head(list);
        printf("%d%s",*value,i<999?", ":"\n");
        free(value);
    }
    printf("List size: %llu\n",list->size);
    free(list);
    printf("\n");
    LLST *list1 = empty(),*list2=empty(),*list3,*list4;
    for(int i=0;i<1000;i++){
        p = (int *)malloc(sizeof(int));
        *(int *)p = i;
        append(list1,p);
        p = (int *)malloc(sizeof(int));
        *(int *)p = -i;
        append(list2,p);
    }
    printf("List concatenation.");
    list4 = concat(list1,list2);
    while(list4->size>0){
        value = (int *)head(list4);
        printf("%d%s",*value,list4->size!=0?", ":"\n");
    }    
    printf("List join.\n");
    join(list1,list2);
    printf("List size: %llu\n",list1->size);
    printf("\n");
    list3 = copy(list1);
    while(list1->size>0){
        value = (int *)head(list1);
        printf("%d%s",*value,list1->size!=0?", ":"\n");
    }
    printf("List size: %llu\n",list1->size);
    printf("\n");
    printf("Printing the copy:\n");
    while(list3->size>0){
        value = (int *)head(list3);
        printf("%d%s",*value,list3->size!=0?", ":"\n");
        free(value);
    }
    free(list1); 
    free(list3);
    printf("Testing a small BitArray.\n");
    BitArray *array = new_BitArray(3);
    set_bit(array,1,0);
    set_bit(array,0,1);
    set_bit(array,1,2);
    print_BitArray(array);
    free_BitArray(array);
    printf("Testing a one byte BitArray.\n");    
    array = new_BitArray(8);
    set_bit(array,1,0);
    set_bit(array,0,1);
    set_bit(array,1,2);
    set_bit(array,1,3);
    set_bit(array,0,4);
    set_bit(array,1,5);
    set_bit(array,1,6);
    set_bit(array,1,7);
    printf("Expected:\n%s\n","10110111");
    printf("Obtained:\n");
    print_BitArray(array);
    free_BitArray(array);    
    printf("Testing a big byte BitArray.\n");    
    array = new_BitArray(1000000000LLU);
    for(unsigned long long i=0;i<array->size;i++){
        set_bit(array,(i%3)!=0,i);
    }
    printf("One billion bits created and set.\n");
    for(unsigned long long i=0;i<array->size;i++){
        if(get_bit(array,i)!=((i%3)!=0)){
            printf("Error retrieving bit values");
            break;
        }
    }
    printf("Bit information retrieval has been successful.\n");
    free_BitArray(array);
}
