#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

//=======================//
// Implemented Functions //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::PRIMES[3] = {102523, 100907, 104659};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintLine(int tableIndex) const
{
    const HashData& data = table[tableIndex];

    // Using printf here it is easier to format
    if(data.sentinel == SENTINEL_MARK)
    {
        printf("[%03d]         : SENTINEL\n", tableIndex);
    }
    else if(data.sentinel == EMPTY_MARK)
    {
        printf("[%03d]         : EMPTY\n", tableIndex);
    }
    else
    {
        printf("[%03d] - [%03d] : ", tableIndex, data.lruCounter);
        printf("(%-5s) ", data.isCostWeighted ? "True" : "False");
        size_t sz = data.intArray.size();
        for(size_t i = 0; i < sz; i++)
        {
            if(i % 2 == 0)
                printf("[%03d]", data.intArray[i]);
            else
                printf("/%03d/", data.intArray[i]);

            if(i != sz - 1)
                printf("-->");
        }
        printf("\n");
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintTable() const
{
    printf("____________________\n");
    printf("Elements %d\n", elementCount);
    printf("[IDX] - [LRU] | DATA\n");
    printf("____________________\n");
    for(int i = 0; i < MAX_SIZE; i++)
    {
        PrintLine(i);
    }
}

//=======================//
//          TODO         //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Hash(int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int hash=0;
    int iCW=0;
    if (isCostWeighted) iCW=1;
    hash = PRIMES[0]*startInt + PRIMES[1]*endInt + PRIMES[2]*iCW;
    return hash%MAX_SIZE;
}
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::getStartInt(int& index)
{
    return table[index].intArray[0];
}
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::getEndInt(int& index)
{
    return table[index].intArray[table[index].intArray.size()-1];
}


template<int MAX_SIZE>
HashTable<MAX_SIZE>::HashTable()
{
    /* TODO */
    for (int i=0; i<MAX_SIZE;i++){
        
        table[i].sentinel = EMPTY_MARK;
        
        table[i].lruCounter = 0;
        
        table[i].isCostWeighted = false;
        
        table[i].intArray.clear();
    }
    elementCount=0;
}

template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Insert(const std::vector<int>& intArray, bool isCostWeighted)
{
    /* TODO */
    
    if (intArray.size()==0) throw InvalidTableArgException();
    
    if (elementCount > MAX_SIZE*0.5) throw TableCapFullException(elementCount);
    
    for (int i=0; i<MAX_SIZE;i++){
        if (!table[i].intArray.empty() &&
            table[i].intArray[0] == intArray[0] && 
            table[i].intArray[table[i].intArray.size()-1] == intArray[intArray.size()-1] && 
            table[i].isCostWeighted == isCostWeighted){
                table[i].lruCounter++;
                return table[i].lruCounter;
            }
    }
    
    int startInt = intArray[0];
    int endInt = intArray[intArray.size()-1];
    int x = 1;
    int hash = Hash(startInt,endInt,isCostWeighted);
    int hash_sabit = Hash(startInt,endInt,isCostWeighted);
    
    
    while(table[hash].sentinel == OCCUPIED_MARK){
        hash = (hash_sabit+x*x)%MAX_SIZE;
        x++;
    }
    
    table[hash].startInt = intArray[0];
    table[hash].endInt = intArray[intArray.size()-1];
    table[hash].lruCounter = 1;
    table[hash].isCostWeighted = isCostWeighted;
    table[hash].sentinel = OCCUPIED_MARK;
    table[hash].intArray = intArray;
    elementCount++;
    
    return 0;
}

template<int MAX_SIZE>
bool HashTable<MAX_SIZE>::Find(std::vector<int>& intArray,
                               int startInt, int endInt, bool isCostWeighted,
                               bool incLRU)
{
    /* TODO */
    
    intArray.clear();
    for (int i=0; i<MAX_SIZE ; i++){
        if (!table[i].intArray.empty() &&
            startInt == table[i].intArray[0] && 
            endInt == table[i].intArray[table[i].intArray.size()-1] && 
            table[i].isCostWeighted == isCostWeighted &&
            table[i].sentinel==OCCUPIED_MARK){
            int size = table[i].intArray.size() ;
                for (int k = 0 ; k<size ; k++){
                    intArray.push_back(table[i].intArray[k]);
                }
                if (incLRU) table[i].lruCounter++;
                return true;
            }
    }
    return false;
    
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */
    for (int i=0 ; i<MAX_SIZE ; i++){
    
        table[i].sentinel = EMPTY_MARK;
        
        table[i].lruCounter = 0;
        
        table[i].isCostWeighted = false;
        
        table[i].intArray.clear();
        
        table[i].startInt = 0;
        
        table[i].endInt = 0;
        
    }
    elementCount=0;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
    if (elementCount == 0 ) return;
    intArray.clear();
    int GMI = 0; 
    for (int i=1 ;i<MAX_SIZE ; i++){
        if (table[GMI].lruCounter<table[i].lruCounter) GMI = i;
    }
    
    int size = table[GMI].intArray.size() ;
    for (int k = 0 ; k<size ; k++){
        intArray.push_back(table[GMI].intArray[k]);
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    
    for (int i=0; i<MAX_SIZE ; i++){
        if (!table[i].intArray.empty() &&
            startInt == table[i].intArray[0] && 
            endInt == table[i].intArray[table[i].intArray.size()-1] && 
            table[i].isCostWeighted == isCostWeighted &&
            table[i].sentinel==OCCUPIED_MARK){
            intArray.clear();
            int size = table[i].intArray.size() ;
                for (int k = 0 ; k<size ; k++){
                    intArray.push_back(table[i].intArray[k]);
                }
                table[i].sentinel=SENTINEL_MARK;
                table[i].lruCounter=0;
                table[i].isCostWeighted = false;
                table[i].startInt = 0;
                table[i].endInt = 0;
                table[i].intArray.clear();
                elementCount--;
            }
    }
    return;
    
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
    for (int i = 0; i<lruElementCount ; i++){
        if(elementCount==0) return;
        
        int GMI = -1;
        
        int a=0;
         
        while(GMI==-1){
            if(table[a].sentinel == OCCUPIED_MARK) GMI=a;
            a++;
        }
        
        
        for (int k = 1; k<MAX_SIZE ; k++){
            if (table[k].sentinel == OCCUPIED_MARK && table[GMI].sentinel == OCCUPIED_MARK){
                if(table[k].lruCounter<table[GMI].lruCounter) GMI = k;
            }
        }
            table[GMI].sentinel=SENTINEL_MARK;
            table[GMI].lruCounter=0;
            table[GMI].isCostWeighted = false;
            table[GMI].startInt = 0;
            table[GMI].endInt = 0;
            table[GMI].intArray.clear();
            elementCount--;
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
    
    MaxPairHeap<int,int> maxHeap;
    for (int i=0; i<MAX_SIZE;i++){
        if(table[i].lruCounter!=0) maxHeap.push({table[i].lruCounter,i});
    }
    while (!maxHeap.empty()){
        auto s = maxHeap.top();
        maxHeap.pop();
        PrintLine(s.value);
    }
    
}

#endif // HASH_TABLE_HPP