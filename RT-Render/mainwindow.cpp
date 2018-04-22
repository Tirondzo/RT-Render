#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "render.h"
#include "vector3d.h"
#include "integrator.h"
#include "plane.h"
#include "sphere.h"
#include "material.h"
#include "color.h"

#include "defaultscenes.h"

#include <QStandardItemModel>
#include <QFileDialog>


void MainWindow::updateGUIfromSettings()
{
    if(!settings) return;
    ui->image_w->setText(QString::number(settings->getWidth()));
    ui->image_h->setText(QString::number(settings->getHeight()));

    ui->threads_n->setText(QString::number(settings->getThreadsCount()));
    ui->threads_ideal->setChecked(settings->getIsIdealThreadsCount());

    ui->max_samples->setText(QString::number(settings->getSamplesPerPixel()));
    ui->max_reflections->setText(QString::number(settings->getMaxReflections()));
}

void MainWindow::updateSettingsfromGUI()
{
    if(!settings) return;
    settings->setWidth(ui->image_w->text().toInt());
    settings->setHeight(ui->image_h->text().toInt());

    settings->setThreadsCount(ui->threads_n->text().toInt());
    settings->setIsIdealThreadsCount(ui->threads_ideal->isChecked());

    settings->setSamplesPerPixel(ui->max_samples->text().toInt());
    settings->setMaxReflections(ui->max_reflections->text().toInt());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    render = new Render();
    connect(render, SIGNAL(finished(int)), this, SLOT(render_finished(int)));

    ui->scene_selector->addItem(tr("Select from file..."));
    ui->scene_selector->insertSeparator(1);
    ui->scene_selector->addItem(tr("Spheres1"), QVariant(1));
    ui->scene_selector->addItem(tr("Spheres2"), QVariant(2));
    ui->scene_selector->addItem(tr("Corner1"), QVariant(3));

    QIntValidator *intValidator = new QIntValidator(0, 16384, this);
    ui->image_w->setValidator(intValidator);
    ui->image_h->setValidator(intValidator);

    ui->threads_n->setValidator(new QIntValidator(0, 64, this));
    ui->threads_ideal->setToolTip("Ideal threads count");

    ui->max_samples->setValidator(intValidator);
    ui->max_reflections->setValidator(intValidator);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(settings){
        updateSettingsfromGUI();
        QImage* img = render->startRender(settings->getScene(), settings->getCamera(),
                                          settings->getWidth(), settings->getHeight(),
                                          settings->getThreadsCount(),
                                          settings->getSamplesPerPixel(),
                                          settings->getMaxReflections());
        ui->graphicsView->setImage(img);
    }
}

void MainWindow::render_finished(int ms)
{
    int width = settings->getWidth();
    int height = settings->getHeight();
    int threads = settings->getThreadsCount();
    statusBar()->showMessage("Render image " + QString::number(width) + "x" + QString::number(height) +
                             " via " + QString::number(threads) + " threads, finished in: " +
                             QString::number(ms) + "ms");
}



void MainWindow::on_scene_selector_currentIndexChanged(int index)
{

}

void MainWindow::on_threads_ideal_toggled(bool checked)
{
    if(!settings) return;
    ui->threads_n->setEnabled(!checked);
    settings->setThreadsCount(QThread::idealThreadCount());
    ui->threads_n->setText(QString::number(settings->getThreadsCount()));
}

void MainWindow::on_scene_selector_activated(int index)
{
    delete [] settings;
    QVariant var = ui->scene_selector->itemData(index);
    if(index == 0){
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "", tr("Scene file (*.xml)"));

        if(!fileName.isEmpty()){
            XMLSceneParser parser{};
            settings = parser.loadScene(fileName);
        }
    }else if(var.isValid() && var.value<int>() == 1){
        settings = new Spheres1();
    }else if(var.isValid() && var.value<int>() == 2){
        settings = new Spheres2();
    }else if(var.isValid() && var.value<int>() == 3){
        settings = new Corner1();
    }

    updateGUIfromSettings();
}
