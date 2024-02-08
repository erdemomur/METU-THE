#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{
    char* domain_name;
    char* domain_freq_str;
    int  domain_freq;
    char* row;
    char* video_name;
    char* video_size_str;
    int video_size;
    int i;
    int cacheLimit,mediaCount;
    Cache* new_cache;
    CacheNode* curr_nod;
    DomainFreqNode* curr_freq_nod;
    new_cache=(Cache*)malloc(sizeof(Cache));
    
    scanf("%d %d\n",&cacheLimit,&mediaCount);
    new_cache->cacheLimit = cacheLimit;
    new_cache->mediaCount = mediaCount;
    new_cache->currentSize = 0;
    new_cache->head = NULL;
    new_cache->tail = NULL;
    
    
    for (i=0; i< mediaCount; i++){
        DomainFreqList* curr_domain;
        DomainFreqNode* head_freq_nod;
        if(i==0){
            
            curr_nod = (CacheNode*)malloc(sizeof(CacheNode));
            curr_nod->media.name = (char*)malloc(100*sizeof(char));
            
            new_cache->head=curr_nod;
            curr_nod->prev=NULL;
            curr_nod->next=NULL;

        }
        else{
            if(i == mediaCount-1){
            CacheNode* new_nod;
            new_nod=(CacheNode*)malloc(sizeof(CacheNode));
            new_nod->media.name = (char*)malloc(100*sizeof(char));
            
            curr_nod->next=new_nod;
            new_nod->prev=curr_nod;
            new_nod->next=NULL;
            
            curr_nod=new_nod;
            
            new_cache->tail=curr_nod;
            }
            else{
            CacheNode* new_nod;
            new_nod=(CacheNode*)malloc(sizeof(CacheNode));
            new_nod->media.name = (char*)malloc(100*sizeof(char));
            
            curr_nod->next=new_nod;
            new_nod->prev=curr_nod;
            new_nod->next=NULL;
            
            curr_nod=new_nod;
            }
        }   
            
            row = (char*)malloc(1000*sizeof(char)); 
            fgets(row,1000,stdin);
                    
            video_name = strtok(row," ");
            video_size_str = strtok(NULL, " ");
            video_size = atoi(video_size_str);
            
            
                    
            curr_nod->media.name=video_name;
            curr_nod->media.size=video_size;
            new_cache->currentSize += curr_nod->media.size;
          
            
            curr_domain=(DomainFreqList*)malloc(sizeof(DomainFreqList));
            curr_nod->domainFreqList=curr_domain;
        
            
            
            curr_domain->head=NULL;
            curr_domain->tail=NULL;
            
            
            head_freq_nod = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            head_freq_nod->name=(char*)malloc(100*sizeof(char));
            curr_domain->head=head_freq_nod;
            curr_domain->tail=head_freq_nod;
            head_freq_nod->next=NULL;
            head_freq_nod->prev=NULL;
            
            domain_name=strtok(NULL, " ");
            domain_freq_str = (char*)malloc(100*sizeof(char));
            domain_freq_str = strtok(NULL, " ");
            domain_freq = atoi(domain_freq_str);
            
            head_freq_nod->name=domain_name;
            head_freq_nod->freq=domain_freq;
            
            while((domain_name = strtok(NULL, " "))!=NULL){
                
                curr_freq_nod = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
                curr_freq_nod->name=(char*)malloc(100*sizeof(char));
                curr_freq_nod->next=NULL;
                curr_freq_nod->prev=NULL;
                
                domain_freq_str = (char*)malloc(100*sizeof(char));
                domain_freq_str = strtok(NULL, " ");
                domain_freq = atoi(domain_freq_str);
                
                curr_freq_nod->name=domain_name;
                curr_freq_nod->freq=domain_freq;
            
                
                /*head_freq_nod=curr_domain->head;*/
                curr_domain->head=head_freq_nod;
                
                
                if(curr_domain->head==NULL){
                    /* if'e girmiyo hiçbir zaman */
                    curr_domain->head=curr_freq_nod;
                    curr_domain->tail=curr_freq_nod;
                    
                    curr_freq_nod->prev=NULL;
                    curr_freq_nod->next=NULL;
                    
                }
                else{
                     /*en başa ekleme*/
                    
                    if( (curr_freq_nod->freq>head_freq_nod->freq) || ((curr_freq_nod->freq==head_freq_nod->freq) && (strcmp(curr_freq_nod->name,head_freq_nod->name)<0)) ){
                        curr_domain->head=curr_freq_nod;
                        /*head_freq_nod->next=NULL;*/
                        head_freq_nod->prev=curr_freq_nod;
                        curr_freq_nod->next=head_freq_nod;
                        curr_freq_nod->prev=NULL;
                        head_freq_nod=curr_domain->head;
        
                        
                        /*head_freq_nod=curr_freq_nod;*/
                    }
                    else{
                        /* sona ekleme*/
                        if ((curr_freq_nod->freq<curr_domain->tail->freq) || (curr_freq_nod->freq==curr_domain->tail->freq && strcmp(curr_domain->tail->name,curr_freq_nod->name)<0)){
                            curr_domain->tail->next=curr_freq_nod;
                            curr_freq_nod->prev=curr_domain->tail;
                            curr_domain->tail=curr_freq_nod;
                            curr_freq_nod->next=NULL;
                            
                        }
                        /* ortaya ekleme */
                        else{
                            while(head_freq_nod->freq>curr_freq_nod->freq){
                                head_freq_nod=head_freq_nod->next;
                            }
                            if(head_freq_nod->freq==curr_freq_nod->freq){
                                while(strcmp(head_freq_nod->name,curr_freq_nod->name)<0){
                                    head_freq_nod=head_freq_nod->next;
                                }
                            }    
                            curr_freq_nod->prev=head_freq_nod->prev;
                            curr_freq_nod->next=head_freq_nod;
                            head_freq_nod->prev->next=curr_freq_nod;
                            head_freq_nod->prev=curr_freq_nod;
                            
                        }
                    }
                
                }      
                
            }
    }
return new_cache;

}

/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{
    int i;
    if(cache->head==NULL){
        printf("The Cache is Empty");
    }
    else{
        printf("-------------- Cache Information --------------\n");
        printf("Cache Limit: %d KB\n",cache->cacheLimit);
        printf("Current Size: %d KB\n",cache->currentSize);
        printf("Media Count: %d\n",cache->mediaCount);
        printf("Cache Media Info:\n");
        for (i=0;i<cache->mediaCount;i++){
            printf("    Name: %s    Size: %d KB\n",cache->head->media.name,cache->head->media.size);    
            printf("    ------- Media Domain Frequencies -------\n");
            while(cache->head->domainFreqList->head != NULL){
                printf("        Name: %s   Freq: %d\n",cache->head->domainFreqList->head->name,cache->head->domainFreqList->head->freq);    
            
                cache->head->domainFreqList->head=cache->head->domainFreqList->head->next;
            }
            printf("     ----------------------------------------\n");
            cache->head=cache->head->next;
        }
        printf("----------------------------------------------");
    }
}


/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{
    return NULL;
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    CacheNode* current;
    int a,b;
    b=0;
    current=cache->head;
    for(a=0;a<cache->mediaCount;a++){
        if(strcmp(current->media.name,name)==0){
            b=1;
            return current;
        }
        
        else{
            current=current->next;
        }
    }
    
    if (b==0){
        return NULL;
    }
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{
    int i,j;
    
    CacheNode* current;
    current=cache->head;
    j=cache->mediaCount;
    
    if(j==1){
        if(strcmp(current->media.name,name)==0){
            cache->currentSize = (cache->currentSize)-(current->media.size);
            cache->mediaCount = (cache->mediaCount)-1;
            cache->head=NULL;
            cache->tail=NULL;
        }
    }
    else{
        for (i=0 ; i<j ; i++){
            if(strcmp(current->media.name,name)==0){
                cache->currentSize = (cache->currentSize)-(current->media.size);
                cache->mediaCount = (cache->mediaCount)-1;
                if (current->prev==NULL){
                   current->next->prev=NULL;
                   cache->head=current->next;
                   current->next=NULL;
                   
                }
                else if (current->next==NULL){
                    current->prev->next=NULL;
                    cache->tail=current->prev;
                    current->prev=NULL;
                
                }
                else{
                    current->prev->next=current->next;
                    current->next->prev=current->prev;
                    current->next=NULL;
                    current->prev=NULL;                    
                }
                break;
            }
        current=current->next;
        }
    }
}    



