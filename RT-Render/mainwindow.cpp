#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "render.h"
#include "integrator.h"
#include "plane.h"
#include "sphere.h"
#include "material.h"
#include "color.h"

#include "defaultscenes.h"

#include <QStandardItemModel>
#include <QFileDialog>
#include <QInputDialog>
#include <QClipboard>


const std::vector<std::pair<QString, QString> > MainWindow::get_description_info() const{
    return std::vector<std::pair<QString, QString>> {
    {"width", (settings ? QString::number(settings->getWidth()) : "")},
    {"height", (settings ? QString::number(settings->getHeight()) : "")},
    {"samples_px", (settings ? QString::number(settings->getSamplesPerPixel()) : "")},
    {"reflects_max", (settings ? QString::number(settings->getMaxReflections()) : "")},
    {"threads", (settings ? QString::number(settings->getThreadsCount()) : "")},
    {"threads_ideal", (QString::number(QThread::idealThreadCount()))},
    {"curr_progress", (render ? QString::number(render->getCurrentProgress()) : "")},
    {"targ_progress", (render ? QString::number(render->getTargetProgress()) : "")},
    {"proc_progress", (render ? QString::number((double)render->getCurrentProgress() / render->getTargetProgress() * 100.,'f',2) + '%' : "")},
    {"render_time",(render ? QString::number(render->getRenderedTime()) + "ms" : "-")},
    {"date",QDate::currentDate().toString(tr("dd.MM.yyyy"))}
};
}

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
    description_format(default_description_format),
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

QString MainWindow::generateDescription() const{
    QString ans = description_format;
    if(!ans.length()) return QString{};
    auto info = get_description_info();
    for(auto &it : info){
        ans.replace("{"+it.first+"}", it.second);
    }
    return ans;
}

QImage MainWindow::generateFinalImage() const
{
    if(!render || !settings) return QImage();
    QString description = generateDescription();
    bool description_line = description.length() != 0;
    const int descr_height = description_line ? 16 : 0;
    int width=settings->getWidth(), height=settings->getHeight();
    if(description_line){
        width = std::max(512,width);
        height = std::max(512, height + descr_height);
    }

    QImage new_img = QImage(width, height, QImage::Format::Format_RGB888);
    QPainter painter(&new_img);
    int cy = ((height - descr_height) - settings->getHeight())/2;
    int cx = (width - settings->getWidth())/2;
    painter.setBackground(QBrush(Qt::GlobalColor::black));
    painter.drawImage(cx,cy, *render->getImage());
    if(description_line){
        painter.setBrush(QBrush(Qt::GlobalColor::white));
        painter.setPen(QPen(Qt::GlobalColor::white,1));
        painter.drawLine(0,height-descr_height,width,height-descr_height);
        const int margin = 3;
        QFont font = painter.font();
        font.setPixelSize(descr_height-margin*2);
        painter.setFont(font);
        const QRect rect = QRect(margin, height-descr_height, width-margin*2, descr_height);
        painter.drawText(rect,Qt::TextSingleLine | Qt::AlignVCenter,description);
    }

    return new_img;
}

void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint &pos)
{
    ui->menuPicture->exec(mapToGlobal(pos));
}

void MainWindow::on_actionSave_triggered()
{
    QImage img = generateFinalImage();
    QString image_path = QFileDialog::getSaveFileName(this,
                                                     tr("Save File"), "",
                                                     tr("PNG (*.png);;JPEG (*.jpg *.jpeg)" ));

    img.save(image_path);
}

void MainWindow::on_actionCopy_in_buffer_triggered()
{
    QImage img = generateFinalImage();
    if(img.width()){
        QApplication::clipboard()->setImage(img, QClipboard::Clipboard);
    }
}

void MainWindow::on_actionSettings_triggered()
{
    bool ok;
    const std::vector<std::pair<QString,QString>> info = get_description_info();
    QString label = tr("<p>Format of description line at the bottom of the pic. Fill it empty for plain image. " \
                       "<p> Available parameters: <ul>");
    for(auto &it : info){
        label += "<li>" + it.first + "</li>";
    }
    label += tr("</ul>");

    QString new_format = QInputDialog::getText(this, "Image description format",
                          label,
                          QLineEdit::Normal, description_format, &ok);
    if(ok) description_format = new_format;
}
