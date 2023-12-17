#ifndef INTVEC_H
#define INTVEC_H
class IntVector {
    private:
        unsigned _size;
        unsigned _capacity;
        int *_data;

        void expand();
        void expand(unsigned amount);

    public:
        //Constructors
        IntVector(unsigned capacity = 0, int value = 0);
        
        //Destructors
        ~IntVector();

        //Accessors
        unsigned size() const;
        unsigned capacity() const;
        bool empty() const;
        const int & at(unsigned index) const;
        const int & front() const;
        const int & back() const;

        //Mutators
        int & at(unsigned index);
        int & front();
        int & back();
        void insert(unsigned index, int value);
        void erase(unsigned index);
        void assign(unsigned n, int value);
        void push_back(int value);
        void pop_back();


        //Methods
        void clear();
        void resize(unsigned size, int value = 0);
        void reserve(unsigned n);
};
#endif