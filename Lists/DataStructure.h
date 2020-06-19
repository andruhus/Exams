class DataStructure {
public:
    double x;
    double y;
    double z;

    DataStructure() = default;

    DataStructure(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getValue() {
        return sqrt(x * x + y * y + z * z);
    }

    string toString() {
        return to_string(getValue()) + " = (" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
    }

    static DataStructure createRandomPosition() {
        const double max = 100;
        const double min = 0;
        const int accuracy = 6;

        DataStructure position;
        position.x = (rand() % (int) ((max - min) * pow(10, accuracy))) / pow(10, accuracy) + min;
        position.y = (rand() % (int) ((max - min) * pow(10, accuracy))) / pow(10, accuracy) + min;
        position.z = (rand() % (int) ((max - min) * pow(10, accuracy))) / pow(10, accuracy) + min;
        return position;
    }

    bool equals(DataStructure &dataStructure) {
        return (x == dataStructure.x && y == dataStructure.y && z == dataStructure.z);
    }
};
