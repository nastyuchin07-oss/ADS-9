// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <iomanip>
#include "../include/tree.h"

using namespace std::chrono;

void printPermutation(const std::vector<char>& perm) {
    for (char c : perm) {
        std::cout << c;
    }
}

void printAllPermutations(const std::vector<std::vector<char>>& perms) {
    for (size_t i = 0; i < perms.size(); ++i) {
        std::cout << std::setw(3) << (i + 1) << ": ";
        printPermutation(perms[i]);
        std::cout << std::endl;
    }
}

template<typename Func>
long long measureTime(Func func, const std::string& name) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    std::cout << name << ": " << duration << " мкс" << std::endl;
    return duration;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   ДЕРЕВО ПЕРЕСТАНОВОК - ДЕМОНСТРАЦИЯ   " << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // ========== ТЕСТ 1: 3 элемента ==========
    std::cout << "ТЕСТ 1: Набор из 3 элементов {1, 2, 3}" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::vector<char> elements3 = {'1', '2', '3'};
    Tree tree3(elements3);
    
    std::cout << "\nЗадание №2: getAllPerms()" << std::endl;
    auto allPerms3 = getAllPerms(tree3);
    std::cout << "Всего перестановок: " << allPerms3.size() << std::endl;
    printAllPermutations(allPerms3);
    
    // Задание №3: getPerm1 и getPerm2
    std::cout << "\nЗадание №3: getPerm1() и getPerm2()" << std::endl;
    std::cout << "Сравнение результатов:" << std::endl;
    
    for (int num : {1, 2, 3, 4, 5, 6}) {
        auto perm1 = getPerm1(tree3, num);
        auto perm2 = getPerm2(tree3, num);
        
        std::cout << "  Номер " << num << ": ";
        printPermutation(perm1);
        std::cout << " (getPerm1) = ";
        printPermutation(perm2);
        std::cout << " (getPerm2)";
        
        if (perm1 == perm2) {
            std::cout << " ✓" << std::endl;
        } else {
            std::cout << " ✗ ОШИБКА!" << std::endl;
        }
    }
    
    std::cout << "\n\nТЕСТ 2: Набор из 4 элементов {1, 3, 5, 7}" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::vector<char> elements4 = {'1', '3', '5', '7'};
    Tree tree4(elements4);
    
    auto allPerms4 = getAllPerms(tree4);
    std::cout << "\nВсего перестановок: " << allPerms4.size() << " (4! = 24)" << std::endl;
    
    std::cout << "\nПервые 5 перестановок:" << std::endl;
    for (int i = 0; i < 5 && i < (int)allPerms4.size(); ++i) {
        std::cout << "  " << (i + 1) << ": ";
        printPermutation(allPerms4[i]);
        std::cout << std::endl;
    }
    
    std::cout << "\nПроверка getPerm2 для 4 элементов:" << std::endl;
    for (int num : {1, 2, 3, 24}) {
        auto perm = getPerm2(tree4, num);
        std::cout << "  Перестановка №" << num << ": ";
        printPermutation(perm);
        std::cout << std::endl;
    }
    
    std::cout << "\n\nТЕСТ 3: Набор из 5 элементов {A, B, C, D, E}" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::vector<char> elements5 = {'A', 'B', 'C', 'D', 'E'};
    Tree tree5(elements5);
    
    auto allPerms5 = getAllPerms(tree5);
    std::cout << "\nВсего перестановок: " << allPerms5.size() << " (5! = 120)" << std::endl;
    
    std::cout << "\nПервые 10 перестановок:" << std::endl;
    for (int i = 0; i < 10 && i < (int)allPerms5.size(); ++i) {
        std::cout << "  " << std::setw(3) << (i + 1) << ": ";
        printPermutation(allPerms5[i]);
        std::cout << std::endl;
    }
    
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "   ЭКСПЕРИМЕНТ: ЗАМЕР ВРЕМЕНИ ВЫПОЛНЕНИЯ   " << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    std::vector<int> sizes = {3, 4, 5, 6, 7};
    
    std::cout << std::setw(10) << "Размер" 
              << std::setw(20) << "getAllPerms (мкс)"
              << std::setw(20) << "getPerm1 (мкс)"
              << std::setw(20) << "getPerm2 (мкс)"
              << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    for (int size : sizes) {
        std::vector<char> testElements;
        for (int i = 1; i <= size; ++i) {
            testElements.push_back('0' + i);
        }
        
        Tree testTree(testElements);
        
        long long timeGetAllPerms = 0;
        std::vector<std::vector<char>> perms;
        measureTime([&]() {
            perms = getAllPerms(testTree);
        }, "");
        
        int middleNum = perms.size() / 2;
        long long timeGetPerm1 = measureTime([&]() {
            auto p = getPerm1(testTree, middleNum);
        }, "");
        
        long long timeGetPerm2 = measureTime([&]() {
            auto p = getPerm2(testTree, middleNum);
        }, "");
        
        std::cout << std::setw(10) << size 
                  << std::setw(20) << timeGetAllPerms
                  << std::setw(20) << timeGetPerm1
                  << std::setw(20) << timeGetPerm2
                  << std::endl;
        
        if (timeGetPerm1 > 0) {
            double speedup = (double)timeGetPerm1 / timeGetPerm2;
            std::cout << std::setw(10) << " "
                      << std::setw(20) << " "
                      << std::setw(20) << " "
                      << "Ускорение: ~" << std::fixed << std::setprecision(2) 
                      << speedup << "x" << std::endl;
        }
    }
    
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "   ДЕТАЛЬНЫЙ АНАЛИЗ ДЛЯ 7 ЭЛЕМЕНТОВ   " << std::endl;
    std::cout << "========================================" << std::endl;
    
    std::vector<char> elements7 = {'1', '2', '3', '4', '5', '6', '7'};
    Tree tree7(elements7);
    
    std::cout << "\nКоличество перестановок: 7! = 5040" << std::endl;
    
    std::vector<int> positions = {1, 1000, 2520, 4000, 5040};
    
    std::cout << "\nСравнение времени для разных номеров перестановок:" << std::endl;
    std::cout << std::setw(10) << "Номер"
              << std::setw(20) << "getPerm1 (мкс)"
              << std::setw(20) << "getPerm2 (мкс)"
              << std::setw(15) << "Ускорение"
              << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    
    for (int pos : positions) {
        long long time1 = measureTime([&]() {
            auto p = getPerm1(tree7, pos);
        }, "");
        
        long long time2 = measureTime([&]() {
            auto p = getPerm2(tree7, pos);
        }, "");
        
        double speedup = (double)time1 / time2;
        
        std::cout << std::setw(10) << pos
                  << std::setw(20) << time1
                  << std::setw(20) << time2
                  << std::setw(14) << std::fixed << std::setprecision(2) << speedup << "x"
                  << std::endl;
    }
    
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "                 ВЫВОДЫ                 " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\n1. getAllPerms() генерирует все перестановки обходом дерева DFS" << std::endl;
    std::cout << "2. getPerm1() - медленный способ: генерирует ВСЕ перестановки," << std::endl;
    std::cout << "   затем выбирает нужную. Время растет пропорционально n!" << std::endl;
    std::cout << "3. getPerm2() - быстрый способ: навигация по дереву без генерации" << std::endl;
    std::cout << "   всех перестановок. Время растет пропорционально O(n)" << std::endl;
    std::cout << "4. Ускорение getPerm2 относительно getPerm1 становится" << std::endl;
    std::cout << "   значительным при больших n (в десятки и сотни раз)" << std::endl;
    std::cout << "5. Для n=7 ускорение достигает ~" 
              << (double)measureTime([&]() { getPerm1(tree7, 2520); }, "") /
                 measureTime([&]() { getPerm2(tree7, 2520); }, "")
              << "x" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "              ВЫПОЛНЕНИЕ ЗАВЕРШЕНО        " << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
