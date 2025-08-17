#include <iostream>



// آرایه سراسری دو بعدی
int myarr[5][7]; // مثال — طول واقعی ممکن است هر عددی باشد

void print() {
    // به‌دست آوردن تعداد سطر و ستون بدون دانستن طول
    size_t rows = sizeof(myarr) / sizeof(myarr[0]);
    size_t cols = sizeof(myarr[0]) / sizeof(myarr[0][0]);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << myarr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    print();
}

