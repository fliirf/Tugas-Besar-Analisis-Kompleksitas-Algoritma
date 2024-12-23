#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#define NMAX 350

// Struktur data produk
struct Product {
    std::string name;
    std::string category;
    float price;
    int rating;
};

// Fungsi untuk menghasilkan nama produk secara acak
std::string generateRandomName(int id) {
    std::string productNames[] = {
        "Samsung Galaxy S21", "iPhone 14", "MacBook Pro", "Sony Bravia TV", "Bose Headphones",
        "Asus ROG Laptop", "Dell XPS", "Apple iPad", "Huawei MatePad", "LG OLED TV",
        "Xiaomi Redmi Note", "OnePlus Nord", "HP Spectre x360", "Lenovo ThinkPad", "Acer Predator",
        "Canon EOS Camera", "Nikon DSLR", "Sony Alpha", "JBL Speaker", "Logitech Mouse",
        "Razer Keyboard", "Corsair Headset", "GoPro Hero", "DJI Drone", "Microsoft Surface"
    };
    return productNames[id % 25];
}

// Fungsi untuk menghasilkan kategori produk secara acak
std::string generateRandomCategory() {
    std::string categories[] = {"Smartphone", "Laptop", "Tablet", "TV", "Headphone", "Camera", "Accessory"};
    return categories[rand() % 7];
}

// Fungsi untuk menghasilkan data produk secara acak
void generateProducts(std::vector<Product>& products, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        Product p;
        p.name = generateRandomName(i);
        p.category = generateRandomCategory();
        p.price = (rand() % 1000 + 1) * 10; // Harga antara 10 - 10000
        p.rating = rand() % 5 + 1;          // Rating antara 1 - 5
        products.push_back(p);
    }
}

// Fungsi untuk mencetak data produk
void printProducts(const std::vector<Product>& products) {
    for (const auto& p : products) {
        std::cout << "Name: " << p.name
                  << ", Category: " << p.category
                  << ", Price: " << p.price
                  << ", Rating: " << p.rating << std::endl;
    }
}

// Insertion Sort untuk mengurutkan data berdasarkan rating (descending)
void insertionSort(std::vector<Product>& products) {
    int n = products.size();
    for (int i = 1; i < n; ++i) {
        Product key = products[i];
        int j = i - 1;
        while (j >= 0 && products[j].rating < key.rating) {
            products[j + 1] = products[j];
            --j;
        }
        products[j + 1] = key;
    }
}

// Merge Sort untuk mengurutkan data berdasarkan rating (descending)
void merge(std::vector<Product>& products, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Product> L(n1);
    std::vector<Product> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = products[left + i];
    for (int i = 0; i < n2; ++i) R[i] = products[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].rating >= R[j].rating) {
            products[k] = L[i];
            ++i;
        } else {
            products[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        products[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        products[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<Product>& products, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(products, left, mid);
        mergeSort(products, mid + 1, right);
        merge(products, left, mid, right);
    }
}

int main() {
    std::vector<Product> products;
    generateProducts(products, NMAX);

    std::cout << "Original Products:\n";
    printProducts(products);

    //Menggunakan Insertion Sort
    std::vector<Product> insertionSorted = products;
    insertionSort(insertionSorted);
    std::cout << "\nProducts Sorted by Insertion Sort:\n";
    printProducts(insertionSorted);

    //Menggunakan Merge Sort
    std::vector<Product> mergeSorted = products;
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    std::cout << "\nProducts Sorted by Merge Sort:\n";
    printProducts(mergeSorted);
    return 0;
}
