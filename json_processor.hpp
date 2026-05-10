#ifndef JSON_PROCESSOR_HPP
#define JSON_PROCESSOR_HPP

#include <QString>
#include <QTextEdit>
#include <filesystem>
#include <fstream>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;
namespace fs = std::filesystem;

class jsonProcessor{
protected:
    virtual ~jsonProcessor() = default;
public:
    //jsonProcessor() = default;
    virtual void output(const QString& path, QTextEdit *textEdit){
        Q_UNUSED(path); Q_UNUSED(textEdit);
        qDebug()<< "Base output was called called";
    }
};

class jsonOutput: jsonProcessor{
public:
    void output(const QString& path, QTextEdit *textEdit) override{
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
    //~jsonOutput() = {};
};
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
