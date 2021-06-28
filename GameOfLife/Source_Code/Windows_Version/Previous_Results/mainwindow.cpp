#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <QString>
#include <algorithm>

#include "Log_Struct.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh_results();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_results()
{
    std::vector<log> logs;

//    std::ifstream get_log(app_path + "SingleThread\\logs.txt");
    std::ifstream get_log("..\\SingleThread\\logs.txt");
    if (!get_log.fail())
    {
        while (!get_log.eof())
        {
            log tmp;
            std::string str1, str2, str3;
            getline(get_log, str1, ',');
            getline(get_log, str2, ',');
            getline(get_log, str3);
            if (str1.empty()) break;
            //std::cout << str1 << " " << str2 << " " << str3 << "\n";
            tmp.timestamp = str1;
            tmp.mode = "Single-Thread";
            tmp.num_generations = str2;
            tmp.time_taken = str3;
            logs.push_back(tmp);
        }
    }
    get_log.close();

    //get_log.open(app_path + "MultiThread\\logs.txt");
    get_log.open("..\\MultiThread\\logs.txt");
    if (!get_log.fail())
    {
        while (!get_log.eof())
        {
            log tmp;
            std::string str1, str2, str3;
            getline(get_log, str1, ',');
            getline(get_log, str2, ',');
            getline(get_log, str3);
            if (str1 == "\n")
                break;
            //std::cout << str1 << " " << str2 << " " << str3 << "\n";
            if (str1.empty()) break;
            tmp.timestamp = str1;
            tmp.mode = "Multi-Thread";
            tmp.num_generations = str2;
            tmp.time_taken = str3;
            logs.push_back(tmp);
        }
    }
    get_log.close();

    std::sort(logs.begin(), logs.end(), [](log&a, log&b) {
        return a.timestamp > b.timestamp;
    });

    QString res = "<center><table border=\"1\"><tr><th>Timestamp</th><th>Mode</th><th># Generations</th><th>Time Taken</th></tr>";

    for (size_t i = 0; i < logs.size(); ++i)
    {
        std::string tmp = "<tr><td>" + logs[i].timestamp + "</td><td>" + logs[i].mode + "</td><td>"
+ logs[i].num_generations + "</td><td>" + logs[i].time_taken + "</td></tr>";
        res.append(QString::fromStdString(tmp));
    }
    res.append("</table></center>");
    ui->prev_results->setText(res);
}
