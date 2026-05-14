#ifndef JSON_PROCESSOR_HPP
#define JSON_PROCESSOR_HPP

#include <QString>
#include <QTextEdit>
#include <QTableWidget>
#include <QFile>
#include <filesystem>
#include <fstream>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;
namespace fs = std::filesystem;

class jsonProcessor{
public:
    //jsonProcessor() = default;
    /*
    virtual void output(const QString& path, QTextEdit *textEdit){
        Q_UNUSED(path); Q_UNUSED(textEdit);
        qDebug()<< "Base output was called called";
    }*/

    void saveToJSON(json& data, const QString& filepath){
        //std::error_code ec;
        fs::path jsonPath = filepath.toStdString();
        fs::path directoryPath = jsonPath.parent_path();
        /*if (!fs::is_regular_file(jsonPath, ec)) {
            std::cerr << "ERROR: " << ec.message() << std::endl;
            return;}*/
        if (!directoryPath.empty() && !fs::exists(directoryPath)) {
            qDebug() << "ERROR: Parent directory does not exist";
            return;
        }
        if (!fs::exists(jsonPath)) {
            qDebug() << "The file created";
            std::ofstream file(jsonPath);
            file.close();}
        std::ofstream o(jsonPath);
        if (o.is_open()){
            o<<data.dump(4);
            o.close();}
        qDebug()<<"File: "+filepath+" saved successfully";
    }
    void outputtingJsonToATable(const QString& filepath, QTableWidget *table){
        json data = loadFromFile(filepath);
        table->setRowCount(0);
        int row = 0;

        for (const auto& item : data){
            table->insertRow(row);

            int id = item["id"];
            QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
            itemId->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, 0, itemId);

            QString originalName = QString::fromStdString(item["name"]);
            QString modifiedName = convertVowelsToUppercase(originalName);
            QTableWidgetItem *itemName = new QTableWidgetItem(modifiedName);
            table->setItem(row, 1, itemName);

            float price = item["price"];
            QTableWidgetItem *itemPrice = new QTableWidgetItem(QString::number(price, 'f', 2));
            itemPrice->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            table->setItem(row, 2, itemPrice);

            QString expiritionDate = QString::fromStdString(item["expiration_date"]); //!!!
            QTableWidgetItem *itemDate = new QTableWidgetItem(expiritionDate);
            itemDate->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, 3, itemDate);

            row++;
        }
    }
    void outputtingJsonToATextField(const QString& path, QTextEdit *textEdit){
        fs::path jsonPath = path.toStdString();
        if (!fs::exists(jsonPath)) {
            qDebug() << "The file doesn't exist";
            return;}
        //std::ofstream file(jsonPath);
        //file.close();}
        ordered_json j;
        std::ifstream i(jsonPath);
        if (i.is_open() and fs::file_size(jsonPath) > 0){
            i>>j;
            i.close();
        }
        textEdit->setText(QString::fromStdString(j.dump(4)));
    }
    QString convertVowelsToUppercase(QString& line){
        // Список гласных (русский + английский)
        QString vowels = "aeiouyаеёиоуыэюя";
        for (int i = 0; i < line.length(); ++i) {
            if (vowels.contains(line[i], Qt::CaseInsensitive)) {
                line[i] = line[i].toUpper();
            }
        }
        return line;
    }
    /*void jsonUpperVowelsInName(json& data) {
        for (auto& item : data) {  // важно: не const auto&, а auto&
            if (item.contains("name") && item["name"].is_string()) {
                std::string name = item["name"];
                QString qstr = QString::fromStdString(name);
                convertVowelsToUppercase(qstr);
                item["name"] = qstr.toStdString();
            }
        }
    }*/
    QString jsonUpperVowelsInName(QString& text) {
        json data = json::parse(text.toStdString());
        for (auto& item : data) {  // важно: не const auto&, а auto&
            if (item.contains("name") && item["name"].is_string()) {
                std::string name = item["name"];
                QString qstr = QString::fromStdString(name);
                convertVowelsToUppercase(qstr);
                item["name"] = qstr.toStdString();
            }
        }
        return QString::fromStdString(data.dump(4));
    }
private:
    json loadFromFile(const QString& filepath) {
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file:" << filepath;
            return json::array();
        }

        QTextStream stream(&file);
        QString content = stream.readAll();

        return json::parse(content.toStdString());
    }
};

class jsonOutput: public jsonProcessor{};
class jsonParser: public jsonProcessor{};
/*
json loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << filename;
        return json::array();
    }

    QTextStream stream(&file);
    QString content = stream.readAll();
    return json::parse(content.toStdString());
}
// Использование:
// json products = loadFromFile("products.json");
// printTable(products);
*/

#endif // JSON_PROCESSOR_HPP
