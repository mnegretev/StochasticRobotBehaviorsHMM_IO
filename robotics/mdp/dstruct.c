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
 * @file dstruct.c
 * @author Stalin Muñoz Gutiérrez
 * @date 3 March 2019
 * @brief Data Structures Library
 *
 * Basic Data Structures Library Implementation File
 * 
 */
 
#include "dstruct.h"
#include<stdlib.h>
#include<stdio.h>

LLST *empty(){
    LLST *list = (LLST *) malloc(sizeof(LLST));
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

void append(LLST *list,void *data){
    link_ll *l = new_link_ll(data,list->last,NULL);
    if(list->first==NULL){
        list->first=l;
        list->last=l;
    }else{
        list->last->next=l;
        list->last = l;
    }
    
    list->size++;
}

void join(LLST *a,LLST *b){
    a->last->next = b->first;
    b->first->previous = a->last;
    a->last = b->last;
    a->size += b->size;
    free(b);
}

LLST *concat(LLST *a,LLST *b){
    LLST *list1 = copy(a), *list2 = copy(b);
    join(list1,list2);
    return list1;
}

link_ll *new_link_ll(void *data,link_ll *previous,link_ll *next){
    link_ll *l = (link_ll *) malloc(sizeof(link_ll));
    l->data = data;
    l->previous = previous;
    l->next = next;
    return l;
}

LLST *copy(LLST *list){
    LLST *lst = empty();
    link_ll *p;
    p = list->first;
    for(int i=0;i<list->size;i++,p=p->next){
        append(lst,p->data);
    }
    return lst;
}

void *head(LLST *list){
    if(list->size==0){
        return NULL;
    }
    link_ll *p = list->first;
    void *data = p->data;
    list->first = p->next;
    if(list->first!=NULL){
        list->first->previous = NULL;
    }
    list->size--;
    free(p);
    return data;
}

void free_LLST(LLST *list){ 
    while(list->size>0){
        head(list);
    }
    free(list);
}

void free_data_LLST(LLST *list){
    for(link_ll *p = list->first;p!=NULL;p = p->next){
        free(p->data);
    }
}

BitArray *new_BitArray(unsigned long long n){
    unsigned long long b = (n>>3)+((n%8)!=0);
    BitArray *array = (BitArray *) malloc(sizeof(BitArray));
    array->size = n;
    //sets bits to zero
    array->bits = (unsigned char *) calloc(b,sizeof(unsigned char));
    return array;
}

void set_bit(BitArray *array,unsigned char bit, unsigned long long pos){
    unsigned long long byte = byteofbit(pos);
    unsigned char bits = array->bits[byte];
    unsigned char mask = 1U<<bitinbyte(pos);
    array->bits[byte] = bit?(bits|mask):(bits&(255U^mask));
}

unsigned char get_bit(BitArray *array,unsigned long long pos){
    unsigned long long byte = byteofbit(pos);
    unsigned char bits = array->bits[byte];
    unsigned char mask = 1U<<bitinbyte(pos);
    return (bits&mask)!=0;
}

void print_BitArray(BitArray *array){
    printf("BitArray:\n");
    for(unsigned long long i=0;i<array->size;i++){
        printf("%c",get_bit(array,i)?'1':'0');
    }
    printf("\n");
}

void free_BitArray(BitArray *array){
    free(array->bits);
    free(array);
}
