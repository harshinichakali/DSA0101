#include <iostream>
#include <string>

class Auditorium {
private:
    int rows;
    int seatsPerRow;
    int** seatMap;

public:
    Auditorium(int rowCount, int seats)
        : rows(rowCount), seatsPerRow(seats), seatMap(nullptr) {
        if (rows < 0 || seatsPerRow < 0) {
            throw std::invalid_argument("Rows and seats per row cannot be negative.");
        }

        if (rows > 0) {
            seatMap = new int*[rows]{};

            try {
                for (int i = 0; i < rows; ++i) {
                    seatMap[i] = new int[seatsPerRow]{};
                }
            } catch (...) {
                for (int i = 0; i < rows; ++i) {
                    delete[] seatMap[i];
                }
                delete[] seatMap;
                throw;
            }
        }

        std::cout << "Created auditorium: " << rows << " x "
                  << seatsPerRow << '\n';
    }

    // This example owns a raw pointer, so disable copying to avoid shallow-copy bugs.
    Auditorium(const Auditorium&) = delete;
    Auditorium& operator=(const Auditorium&) = delete;

    ~Auditorium() {
        for (int i = 0; i < rows; ++i) {
            delete[] seatMap[i];
        }
        delete[] seatMap;

        std::cout << "Destroyed auditorium: " << rows << " x "
                  << seatsPerRow << '\n';
    }

    void bookSeat(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
            throw std::out_of_range("Seat position is out of range.");
        }
        seatMap[row][seat] = 1;
    }

    void printSummary() const {
        int booked = 0;
        for (int r = 0; r < rows; ++r) {
            for (int s = 0; s < seatsPerRow; ++s) {
                booked += seatMap[r][s];
            }
        }

        std::cout << "Seat map: " << rows << " rows, "
                  << seatsPerRow << " seats per row, "
                  << booked << " booked\n";
    }
};

int main() {
    // Local object: destroyed when main exits.
    Auditorium local(2, 4);
    local.bookSeat(0, 1);

    // Heap object: must be deleted explicitly.
    Auditorium* heap = new Auditorium(3, 5);
    heap->bookSeat(2, 3);
    heap->printSummary();
    delete heap;

    // Block-scope object: destroyed at the closing brace.
    {
        Auditorium block(1, 3);
        block.bookSeat(0, 0);
        block.printSummary();
    }

    local.printSummary();
}
