#ifndef CELVIEW_H
#define CELVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include "d1cel.h"
#include "d1cl2.h"

#define CEL_SCENE_SPACING 8

namespace Ui {
class CelScene;
class CelView;
}

class CelScene : public QGraphicsScene
{

protected:
    void mousePressEvent( QGraphicsSceneMouseEvent *event );

};

class CelView : public QWidget
{
    Q_OBJECT

public:
    explicit CelView( QWidget *parent = 0 );
    ~CelView();

    void initialize( D1CelBase* );
    D1CelBase* getCel();
    QString getCelPath();
    quint32 getCurrentFrameIndex();
    quint8 getColorIndexFromCoordinates( QPointF );

    void displayFrame();
    bool checkGroupNumber();
    void setGroupNumber();

signals:
    void frameChanged();

private slots:
    void on_firstFrameButton_clicked();
    void on_previousFrameButton_clicked();
    void on_nextFrameButton_clicked();
    void on_lastFrameButton_clicked();
    void on_frameIndexEdit_returnPressed();

    void on_firstGroupButton_clicked();
    void on_previousGroupButton_clicked();
    void on_groupIndexEdit_returnPressed();
    void on_nextGroupButton_clicked();
    void on_lastGroupButton_clicked();

    void on_zoomOutButton_clicked();
    void on_zoomInButton_clicked();
    void on_zoomEdit_returnPressed();

    void on_playButton_clicked();
    void on_stopButton_clicked();
    void playGroup();

private:
    Ui::CelView *ui;
    QGraphicsScene *celScene;

    D1CelBase *cel;
    quint16 currentGroupIndex;
    quint32 currentFrameIndex;
    quint8 currentZoomFactor;

    QTimer playTimer;
};

#endif // CELVIEW_H
