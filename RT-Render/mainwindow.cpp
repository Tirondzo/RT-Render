#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "render.h"
#include "vector3d.h"
#include "integrator.h"
#include "plane.h"
#include "sphere.h"
#include "material.h"
#include "color.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Scene *scene = new Scene();
    Camera *camera = new Camera(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(1.0f, 0.0f, 1.0f), 1.0f, 9.5f, 2.0f);

    Material *whiteMat = new Material(Color(255,255,255), 1.f, .0f, .0f);
    Material *redMat = new Material(Color(255,0,0));
    Material *greenMat = new Material(Color(0,255,0));
    Material *yellowMat = new Material(Color(255,255,0));
    Material *light = new Material(Color(255,255,255));
    Material *glass = new Material(Color(255,255,255), 0,0,1);
    light->setIsLight(true);

    scene->addObject(new Plane(light, Vector3D(50.0f, 0.0f, 0.0f), Vector3D(-1.0f, 0.0f, 0.0f)));
    scene->addObject(new Plane(whiteMat, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f)));

    scene->addObject(new Sphere(glass, Vector3D(10.0f, -0.5f, 1.5f), 1.5f));
    scene->addObject(new Sphere(yellowMat, Vector3D(12, -4.8, 2.15), 2.15f));
    scene->addObject(new Sphere(redMat, Vector3D(5.5, -2.6, 0.83), 0.83f));
    scene->addObject(new Sphere(glass, Vector3D(6.6, 1, 0.5), 0.5f));
    scene->addObject(new Sphere(redMat, Vector3D(8.5, 2.2, 0.5), 0.5f));
    scene->addObject(new Sphere(yellowMat, Vector3D(4.6, 2.15, 0.9), 0.9f));
    //scene->addObject(new Sphere(light, Vector3D(0,0,1), 100.f));

    Render *render = new Render();
    connect(render, SIGNAL(finished()), this, SLOT(render_finished()));
    timer.start();
    width = 512;
    height = 512;
    threads = 4;
    QImage* img = render->startRender(scene, camera, width, height, threads);
    ui->graphicsView->setImage(img);
}

void MainWindow::render_finished()
{
    int ms = timer.elapsed();
    QString message = "T";
    statusBar()->showMessage("Render image " + QString::number(width) + "x" + QString::number(height) +
                             " via " + QString::number(threads) + " threds, finished in: " +
                             QString::number(ms) + "ms");
}


