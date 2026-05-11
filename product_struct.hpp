#ifndef PRODUCTSTRUCT_HPP
#define PRODUCTSTRUCT_HPP

#include <string>
#include <memory>
#include <QString>
#include <filesystem>
#include <fstream>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;
namespace fs = std::filesystem;

struct Product {
    Product(std::string category, const std::string& name, float price, long expiration_date, int id, int value)
        : category_(category), name_(name), price_(price), expiration_date_(expiration_date), id_(id), value_(value){}
    // Порядок для лучшего хранения
    std::string category_;
    std::string name_;
    float price_;
    long expiration_date_;
    int id_;
    int value_;
};

inline long dateToLong(const std::string& date) {
    // date = "0123-56-89"
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    return year * 10000L + month * 100 + day;
    // Результат: 20260407
}

inline std::unique_ptr<Product> createProductFromJson(const json& jsonObj) {
        // Правильный порядок
        int id =                  jsonObj.value("id", 0);
        std::string name =        jsonObj.value("name", "");
        int value =               jsonObj.value("value", 0);
        float price =             jsonObj.value("price", 0);
        std::string category =    jsonObj.value("category", "");
        long expDate = dateToLong(jsonObj.value("expiration_date", ""));

        return std::make_unique<Product>(category, name, price, expDate, id, value);
}

#endif // PRODUCTSTRUCT_H
