class Point {
private:
    int x;
    int y;

public:
    Point() {
        x = 0;
        y = 0;
    }

    Point& operator++() {
        ++x;
        ++y;
        return *this;
    }

    Point& operator--() {
        --x;
        --y;
        return *this;
    }

    Point operator++(int) {
        Point temp = *this;
        ++(*this);
        return temp;
    }

    Point operator--(int) {
        Point temp = *this;
        --(*this);
        return temp;
    }
};
