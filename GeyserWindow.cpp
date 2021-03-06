
#include <qgl.h>
#include "GeyserWindow.h"
#include "ui_GeyserWindow.h"

GeyserWindow::GeyserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GeyserWindow)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout(ui->geyserViewFrame);

    QGLFormat newformat;
    newformat.setSwapInterval(0); // turn off vertical sync
    m_particleEngineView = new ParticleEngineView(newformat, ui->geyserViewFrame);
    layout->setMargin(0);
    layout->addWidget(m_particleEngineView, 1);

    connect(m_particleEngineView, SIGNAL(statusUpdated(float, int)), SLOT(onStatusUpdated(float, int)));


    // Connect all spin boxes to update the particle engine when they have been edited.
    connect(ui->particlesPerSecSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->lifespanMinSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->lifespanMaxSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->speedMinSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->speedMaxSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->thetaMinSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->thetaMaxSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->phiMinSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->phiMaxSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->accelerationXSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->accelerationYSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->accelerationZSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->colorStartRedSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->colorStartGreenSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->colorStartBlueSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->colorEndRedSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->colorEndGreenSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->colorEndBlueSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->sizeStartSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));
    connect(ui->sizeEndSpinBox, SIGNAL(editingFinished()), SLOT(onEditingFinished()));

    connect(ui->showAxesCheckBox, SIGNAL(toggled(bool)), m_particleEngineView, SLOT(onShowAxesToggled(bool)));
    connect(ui->showBoxCheckBox, SIGNAL(toggled(bool)), m_particleEngineView, SLOT(onShowBoxToggled(bool)));
}


GeyserWindow::~GeyserWindow()
{
    delete ui;
}


void GeyserWindow::onEditingFinished()
{
    ParticleEngine::Configuration config;

    config.particlesPerSec = ui->particlesPerSecSpinBox->value();

    config.lifeSpanMin = ui->lifespanMinSpinBox->value();
    config.lifeSpanMax = ui->lifespanMaxSpinBox->value();

    config.speedMin = ui->speedMinSpinBox->value();
    config.speedMax = ui->speedMaxSpinBox->value();
    config.thetaMin = ui->thetaMinSpinBox->value() * DEG_TO_RAD;
    config.thetaMax = ui->thetaMaxSpinBox->value() * DEG_TO_RAD;
    config.phiMin = ui->phiMinSpinBox->value() * DEG_TO_RAD;
    config.phiMax = ui->phiMaxSpinBox->value() * DEG_TO_RAD;

    config.acceleration = Vector3f(
                ui->accelerationXSpinBox->value(),
                ui->accelerationYSpinBox->value(),
                ui->accelerationZSpinBox->value());

    config.colorStart[0] = ui->colorStartRedSpinBox->value();
    config.colorStart[1] = ui->colorStartGreenSpinBox->value();
    config.colorStart[2] = ui->colorStartBlueSpinBox->value();
    config.colorEnd[0] = ui->colorEndRedSpinBox->value();
    config.colorEnd[1] = ui->colorEndGreenSpinBox->value();
    config.colorEnd[2] = ui->colorEndBlueSpinBox->value();


    config.sizeStart = ui->sizeStartSpinBox->value();
    config.sizeEnd = ui->sizeEndSpinBox->value();


    m_particleEngineView->setConfig(config);
}


void GeyserWindow::onStatusUpdated(float fps, int count)
{
    QString fpsStr = "fps: " + QString::number((int)fps) + ", Count: " + QString::number(count);

    ui->statusBar->showMessage(fpsStr);
}
