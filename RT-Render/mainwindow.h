#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

#include "render.h"
#include "rendersettings.h"
#include "xmlsceneparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Render* render{};
    RenderSettings *settings{};

    void updateGUIfromSettings();
    void updateSettingsfromGUI();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void render_finished(int ms);

    void on_scene_selector_currentIndexChanged(int index);

    void on_threads_ideal_toggled(bool checked);

    void on_scene_selector_activated(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
