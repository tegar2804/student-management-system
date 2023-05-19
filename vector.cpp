#include <bits/stdc++.h>

using namespace std;

class Mahasiswa{
    private:
    string nama;
    string nim;
    public:
    Mahasiswa(){
        nama="";
        nim="";
    }
    void Mahasiswa(string name, string id){
        nama=name;
        nim=id;
    }
    string getNama(){
        return nama;
    }
    string getNim(){
        return nim;
    }
    void input(string name, string id){
        nama=name;
        nim=id;
    }
    void editNama(string name){
        nama=name;
    }
    void editNim(double id){
        nim=id;
    }
};

template <typename T> class vectorMahasiswa{
    T* arr;
    int capacity;
    int current;
    public:
    vectorMahasiswa(){
        arr=new T[1];
        capacity=1;
        current=0;
    }
    ~vectorMahasiswa(){
        delete []arr;
    }
    void push(T data){
        if (current == capacity) {
            T* temp = new T[2 * capacity];
 
            // copying old array elements to new array
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
 
            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
 
        // Inserting data
        arr[current] = data;
        current++;
    }
    void push(T data, int index)
    {
 
        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }
 
    // function to extract element at any index
    T get(int index)
    {
 
        // if index is within the range
        if (index < current)
            return arr[index];
    }
    void pop() { current--; }
 
    // function to get size of the vector
    int size() { return current; }
 
    // function to get capacity of the vector
    int getcapacity() { return capacity; }
 
    // function to print array elements
    void print()
    {
        for (int i = 0; i < current; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    vectorMahasiswa<Mahasiswa> daftarMahasiswa;
    daftarMahasiswa.push(Mahasiswa("anton", "g640"));
    for (int i = 0; i < daftarMahasiswa.size(); i++) {
        cout << "Nama: " << daftarMahasiswa[i].getNama() << endl << "NIM: " << daftarMahasiswa[i].getNim() << endl;
    }
}
