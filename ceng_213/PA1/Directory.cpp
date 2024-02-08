#include "Directory.h"

File Directory::getFile(int index) const
{
    /* TODO */
    if (index>=0 && index<files.size()) return files[index];
    return File();
}

size_t Directory::directorySize() const
{
    /* TODO */
    size_t total_file = 0;
    for (int i=0 ; i<files.size() ; i++){
        total_file = total_file + files[i].fileSize();
    }
    return total_file;
}

bool Directory::isEmpty() const
{
    /* TODO */
    if (files.size()==0) return true;
    return false;
}

size_t Directory::numFiles() const
{
    /* TODO */
    return files.size();
}

void Directory::newFile(const File &file)
{
    /* TODO */
    files.push_back (file);
}

void Directory::removeFile(int index)
{
    /* TODO */
    if (index>=0 && index<files.size()) files.erase (files.begin()+index);
}

void Directory::removeFile(File &file)
{
    /* TODO */
    for (int i=0 ; i<files.size() ; i++){
        if(files[i]==file){
            files.erase (files.begin()+i);
            return;
        }
    }
    
}

void Directory::removeBiggestFile()
{
    /* TODO */
    if(files.size() > 0){
        int k=0;
        size_t big_file_size = files[0].fileSize();
        for (int i=1 ; i<files.size() ; i++){
            if ( big_file_size<files[i].fileSize() ) k=i;
        }
        files.erase (files.begin()+k);
    }
}
