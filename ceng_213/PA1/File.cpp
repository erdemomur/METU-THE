#include "File.h"

Block File::getBlock(int index) const
{
    /* TODO */
    if (index>=0 && index<blocks.getSize()) return blocks.getNodeAtIndex(index)->data;
    return Block();
}

size_t File::fileSize() const
{
    /* TODO */
    Node<Block>* current = blocks.getFirstNode();
    if (current == NULL) return 0;
    size_t total=0;
    while (current){
        total = total + current->data.getSize();
        current = current->next;
    }
    return total;
}

int File::numBlocks() const
{
    /* TODO */
    return blocks.getSize();
}

bool File::isEmpty() const
{
    /* TODO */
    Node<Block>* current = blocks.getFirstNode();
    if (current==NULL) return true;
    return false;
}

bool File::operator==(const File &rhs) const
{
    /* TODO */
    Node<Block>* current_gezen = blocks.getFirstNode();
    Node<Block>* rhs_gezen = rhs.blocks.getFirstNode();
    while (current_gezen != NULL && rhs_gezen != NULL){
        if ( (current_gezen->next == NULL && rhs_gezen->next != NULL) || (current_gezen->next != NULL && rhs_gezen->next == NULL) ) return false;
        if(current_gezen->data == rhs_gezen->data) ;
        else return false;
        current_gezen = current_gezen->next;
        rhs_gezen = rhs_gezen->next;
    }
    return true;
}

void File::newBlock(const Block &block)
{
    /* TODO */
    blocks.append(block);
}

void File::removeBlock(int index)
{
    /* TODO */
    blocks.removeNodeAtIndex(index);
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
    /* TODO */
    blocks.mergeNodes(sourceIndex,destIndex);
}

void File::printContents() const{
    if(isEmpty()){
        std::cout << "File is empty" << std::endl;
    }
    else{
        for(int i = 0; i < blocks.getSize(); i++){
            Node<Block> *block = blocks.getNodeAtIndex(i);
            std::cout << block->data.getContent();
        }
        std::cout << std::endl << fileSize() << std::endl;
    }
}
