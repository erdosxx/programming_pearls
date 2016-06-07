#include "List.h"

#ifndef ALGORITHM_ANALYSIS_QUEUE_H
#define ALGORITHM_ANALYSIS_QUEUE_H

template <typename Object>
class Queue {
public:
    Queue(){ }

    ~Queue(){
        list_obj.clear();
    }

    void enqueue(const Object & x){
        list_obj.push_back(x);
    }

    Object & dequeue2(){
        Object & retObj = list_obj.front();
        list_obj.pop_front_without_delete();
        return retObj;
    }

    Object & dequeue(){
        Object & retObj = list_obj.front();
        list_obj.pop_front();
        return retObj;
    }

    Object & front() {
        return list_obj.front();
    }

    const Object & front() const {
        return list_obj.front();
    }

    Object & back() {
        return list_obj.back();
    }

    const Object & back() const {
        return list_obj.back();
    }

    int size() const {
        return list_obj.size();
    }

    bool isEmpty() const {
        return size() == 0;
    }

    void makeEmpty() {
        list_obj.clear();
    }

private:
    List<Object> list_obj;
};

#endif //ALGORITHM_ANALYSIS_QUEUE_H
