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

    const QString default_description_format =
            "RT-Render {date} | " \
            "{width}x{height} | " \
            "{samples_px} samples | " \
            "{reflects_max} reflections | " \
            "{threads}/{threads_ideal} threads | " \
            "{proc_progress} {render_time}";
    QString description_format{};
    const std::vector<std::pair<QString, QString>> get_description_info() const;

    QString generateDescription() const;
    QImage generateFinalImage() const;
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

    void on_graphicsView_customContextMenuRequested(const QPoint &pos);

    void on_actionSave_triggered();

    void on_actionCopy_in_buffer_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
