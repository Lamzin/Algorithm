#include <iostream>

using namespace std;

class Set{
protected:
    int size;
    double *arr;

public:
    Set();
    ~Set();

    bool push(double item);
    bool erase(double item);
    bool find(double item);

    Set intersection(Set &a, Set &b);
    Set union(Set &a, Set &b);

    bool operator = (Set &tmp);
    double operator[](int i);
    int getSize();

    void print();
};

Set::Set(){
    size = 0;
    arr = NULL;
}

Set::~Set(){
    if (arr != NULL) delete[] arr;
}

bool Set::push(double item){
    if (find(item)){
        return true; // item is PUSHed
    }

    bool push_item = false;
    double *new_arr = new double[size + 1];
    for (int i = 0; i < size; i++){
        if (arr[i] < item) new_arr[i] = arr[i];
        else{
            if (!push_item){
                new_arr[i] = item;
                push_item = true;
            }
            new_arr[i + push_item] = arr[i];
        }
    }

    delete[] arr;
    arr = new_arr;
    size++;

    return true;
}

bool Set::erase(double item){
    int i;
    for (i = 0; i < size && arr[i] != item; i++){
        if (arr[i] > item) i = size; // NOT FOUND -> arr - sorted!
    }

    if (i == size){
        return false; // NOT FOUND!
    }

    double *new_arr = new double[size - 1];
    for (int j = 0; j < size; j++){
        if (j < i) new_arr[j] = arr[i];
        else if (j > i) new_arr[j - 1] = arr[i];
    }
    size--;
    delete[] arr;
    arr = new_arr;

    return true;
}

bool Set::find(double item){
    for (int i = 0; i < size; i++)
        if (arr[i] == item) return true;
    return false;
}
//*********************************************************

double Set::operator[](int i){
    if (i < 0 || i >= size) return 0.0f;
    return arr[i];
}

int Set::getSize(){
    return size;
}

Set Set::intersection(Set &a, Set &b){
    Set result;
    for (int i = 0; i < a.getSize(); i++){
        if (b.find(a[i])){
            result.push(a[i]);
        }
    }

    return result;
}

Set Set::union(Set &a, Set &b){
    Set result;
    for (int i = 0; i < a.getSize(); i++){
        result.push(a[i]);
    }

    for (int i = 0; i < b.getSize(); i++){
        result.push(b[i]);
    }

    return result;
}

bool Set::operator = (Set &tmp){
    if (this->size != tmp.size) return false;
    else{
        for (int i = 0; i < this->size; i++)
            if (arr[i] != tmp[i]) return fasel;
        return true;
    }
}

void Set::print(){
    cout << "Set: " << endl;
    cout << "    size = " << size << endl;
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}


int main(){


}
