#ifndef GRAVITY_SCENE_H
#define GRAVITY_SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QTimer>

class gravity_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit gravity_scene();
    void initial();
    void keyPressEvent(QKeyEvent * keyEvent);
    void keyReleaseEvent(QKeyEvent * keyEvent);

public slots:
    void gp_update();

signals:
    void send_message(QString);

private:
    QGraphicsEllipseItem *gp_ball;
    QGraphicsRectItem *gp_pan1;
    QGraphicsRectItem *gp_pan2;
    QTimer *scene_timer;
    qreal time_step = 10;
    qreal g = 0.002;
    qreal Vx = 0.2;
    qreal Vy = 0;
    qreal Width = 720;
    qreal Hight = 540;
    qreal bz = 30;
    qreal pz = 250;
    qreal Ekx;
    qreal Eky;
    bool pan_up=false;
    bool pan_down=false;
    int score;

    void ball_update();
    void pan_update();

};

#endif // GRAVITY_SCENE_H
