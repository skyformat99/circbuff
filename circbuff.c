#include "circbuff.h"
#include "circbuffPrivate.h"

//public method definitions

static double fetch(struct circbuff *in){
    if ((in->tip==in->tail)&&!in->isfull)
        return -1;
    else{
        double retVal = *in->tail;
        moveTail(in);
        in->isfull = false;
        return retVal;
    }
}

static void push(struct circbuff *in,double val){
    *in->tip = val;
    moveTip(in);
    //need to fix this logic
    if (in->tip==in->tail)
        in->isfull = true;
}

struct circbuff *circbuff(struct circbuff *in){
    for (size_t i;i<Bufflen;i++){
        in->buff[i] = 0;
    }
    in->tip = in->buff;
    in->tail = in->buff;
    in->push = push;
    in->fetch = fetch;
    in->self = in;
    in->isfull = false;
    return in;
}

//private method definitions

// static double *peekTip(struct circbuff *in){
//     if (in->tip==&(in->buff[Bufflen-1]))
//         return in->buff;
//     else
//         return in->tip+1;
// }
static void moveTip(struct circbuff *in){
    //move the tip
    //wrap the tip back to the start of the buffer
    if (in->tip==&(in->buff[Bufflen-1]))
        in->tip = in->buff;
    else
        in->tip++;
    //if buffer is full, also move the tail      
    if (in->isfull)
        moveTail(in);
}

// static double *peekTail(struct circbuff *in){
//     if (in->tail==&(in->buff[Bufflen-1]))
//         return in->buff;
//     else
//         return in->tail+1;
// }

static void moveTail(struct circbuff *in){
    //refactor out tail+tip advancement code
    //wrap the tail back to the start of the buffer
    if (in->tail==&(in->buff[Bufflen-1]))
        in->tail = in->buff;
    else
        in->tail++;
}